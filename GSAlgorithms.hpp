#pragma once

#include "GSKits.hpp"
#include "types.hpp"

template <typename Type>
void skyline_2d(const std::vector<std::vector<Type>>& data, 
    IMAP& skylines, ADJ& duplicate, 
    sint k, sint r) {
    std::vector<Type> tail_list(k);
    sint layer = 0;
    skylines[layer][0] = 1;
    skylines[layer][1] = 0;
    tail_list[0] = data[0][2];
    if (duplicate.empty()) {
        for (sint i = 1; i < r; ++ i) {
            #ifdef DBG_SKYLINE
            std::cout << std::endl << "Skyline 2D inner" << std::endl;
            std::cout << i << "y = " << data[i][2] << " tail0 = " << tail_list[0] << " tailmax = " << tail_list[layer] << std::endl;
            #endif
            if (data[i][2] < tail_list[0]) { // layer 0 can not
                skylines[0][++ skylines[0][0]] = i;
                tail_list[0] = data[i][2];
            } else if (data[i][2] >= tail_list[layer]) { // layer max can 
                if (layer == k - 1) 
                    continue;
                tail_list[++ layer] = data[i][2];
                skylines[layer][0] = 1;
                skylines[layer][1] = i;
            } else { // layer j
                sint j = bin_search<Type>(tail_list, data[i][2], 0, layer);
                skylines[j][++ skylines[j][0]] = i;
                tail_list[j] = data[i][2];
            }
        }
    } else {
        sint i_layer;
        for (sint i = 1; i < r; ++ i) {
            if (data[i][2] < tail_list[0]) { // layer 0
                skylines[0][++ skylines[0][0]] = i;
                tail_list[0] = data[i][2];
                i_layer = 0;
            } else if (data[i][2] >= tail_list[layer]) { // layer max
                if (layer == k - 1)
                    continue;
                tail_list[++ layer] = data[i][2];
                skylines[layer][0] = 1;
                skylines[layer][1] = i;
                i_layer = layer;
            } else { // layer j
                sint j = bin_search<Type>(tail_list, data[i][2], 0, layer);
                skylines[j][++ skylines[j][0]] = i;
                tail_list[j] = data[i][2];
                i_layer = j;
            }
            if (duplicate.find(i) != duplicate.end()) {
                for (auto& x : duplicate[i]) {
                    skylines[i_layer][++ skylines[i_layer][0]] = x;
                }
            }
        }
    }
}

template <typename Type>
void skyline_nd(const std::vector<std::vector<Type>>& data, 
    IMAP& skylines, ADJ& duplicate, 
    sint k, sint r) {
    sint layer = 0;
    skylines[layer][0] = 1;
    skylines[layer][1] = 0;
    bool plus, flag;
    if (duplicate.empty()) {
        for (sint i = 1; i < r; ++ i) {
            plus = true;
            for (sint lid = 0; lid <= layer; ++ lid) {
                flag = true;
                for (sint j = 1; j <= skylines[lid][0]; ++ j) {
                    if (dominate<Type>(data[skylines[lid][j]], data[i])) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    skylines[lid][++ skylines[lid][0]] = i;
                    plus = false;
                    break;
                }
            }
            if (plus && (layer < k - 1)) {
                skylines[++ layer][0] = 1;
                skylines[layer][1] = i;
            }
        }
    } else {
        sint i_layer;
        for (sint i = 1; i < r; ++ i) {
            i_layer = -1;
            plus = true;
            for (sint lid = 0; lid <= layer; ++ lid) {
                flag = true;
                for (sint j = 1; j <= skylines[lid][0]; ++ j) {
                    if (dominate<Type>(data[skylines[lid][j]], data[i])) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    skylines[lid][++ skylines[lid][0]] = i;
                    i_layer = lid;
                    plus = false;
                    break;
                }
            }
            if (plus && (layer < k - 1)) {
                skylines[++ layer][0] = 1;
                skylines[layer][1] = i;
                i_layer = layer;
            }
            if (i_layer >= 0) {
                if (duplicate.find(i) != duplicate.end()) {
                    for (auto& x : duplicate[i]) {
                        skylines[i_layer][++ skylines[i_layer][0]] = x;
                    }
                }
            }
        }
    }
}

/*
 * Input:  data, [[]]
 *         k, literaly
 * Output: skylines, [[]] (id in sorted data), no need to init
 *         duplicate, map: id -> []
 *         data_idx, last_idx+1 in sorted no duplicate data
 */
template <typename Type>
void k_skyline(std::vector<std::vector<Type>>& data, 
    IMAP& skylines, 
    ADJ& duplicate, 
    sint k) {
    // sort by x axis
    std::vector<std::vector<Type>> copy_data(data);
    std::sort(copy_data.begin(), copy_data.end(), [](std::vector<Type> a, std::vector<Type> b) {
        return a[1] < b[1];
    });
    // remove duplicate
    // duplicate : 
    // { id: [id, ... ] }
    sint length = data.size();
    sint column = data[0].size();
    sint data_idx = 1;
    sint data_last = data.size() - 1;
    // copy_vector<Type>(data[0], copy_data[0], 0, column);
    std::copy(copy_data[0].begin(), copy_data[0].end(), data[0].begin());
    for (sint i = 1; i < length; ++ i) {
        if (same<Type>(copy_data[i], copy_data[i-1])) {
            int key = data_idx - 1;
            duplicate[key] = std::vector<int>();
            while (same<Type>(copy_data[i], copy_data[i-1])) {
                duplicate[key].push_back(data_last);
                // copy_vector<Type>(data[data_last --], copy_data[i], 0, column);
                std::copy(copy_data[i].begin(), copy_data[i].end(), data[data_last --].begin());
                ++ i;
            }
            i --;
        } else {
            // copy_vector<Type>(data[data_idx ++], copy_data[i], 0, column);
            std::copy(copy_data[i].begin(), copy_data[i].end(), data[data_idx ++].begin());
        }
    }
    #ifdef DEBUG
    std::cout << (duplicate.size() > 0 ? "Has Duplicate" : "No Duplicate") << ". ";
    std::cout << "Data size (" << length << ") = " << data_idx << std::endl;
    #endif
    // resize skylines
    // skylines: 
    // [i, j]: id j in data at layer i
    // layer: from 0
    skylines.resize(k);
    for (sint i = 0; i < k; ++ i) {
        skylines[i].resize(data_idx + 1);
    }
    // tackle 2D and ND respectively
    if (data.size() > 0 && data[0].size() == 3) {
        skyline_2d(data, skylines, duplicate, k, data_idx);
    } else {
        skyline_nd(data, skylines, duplicate, k, data_idx);
    }
    #ifdef DBG_SKYLINE
    std::cout << "[K-Skyline] skylines: " << std::endl;
    for (sint i = 0; i < k; ++ i) {
        for (sint j = 1; j <= skylines[i][0]; ++ j) {
            std::cout << data[skylines[i][j]][0] << " ";
        }
        std::cout << std::endl;
    }
    #endif
}

/*
 * Input:  data, [[]], sorted data
 *         skylines, [[]], id in sorted data
 * Output: graph, DSG
 */
template <typename Type>
void build_dsg(std::vector<std::vector<Type>>& data, 
    IMAP& skylines, DSG& graph) {
    int a, b;
    sint k = skylines.size();
    sint layer_size, pl_size;
    for (sint i = 1; i < k; ++ i) {
        layer_size = skylines[i][0];
        for (sint cur = 1; cur <= layer_size; ++ cur) {
            a = skylines[i][cur];
            for (sint pe = 0; pe < i; ++ pe) {
                pl_size = skylines[pe][0];
                for (sint pre = 1; pre <= pl_size; ++ pre) {
                    b = skylines[pe][pre];
                    if (dominate<Type>(data[b], data[a])) {
                        graph.parents[a].insert(b);
                        graph.children[b].insert(a);
                    }
                }
            }
        }
    }
    #ifdef DBG_DSG
    std::cout << std::endl << "[Function Build_Dsg] " << std::endl;
    for (sint i = 0; i < k; ++ i) {
        layer_size = skylines[i][0];
        for (sint j = 1; j <= layer_size; ++ j) {
            std::cout << data[skylines[i][j]][0] << " parents: ";
            for (auto& _ : graph.parents[skylines[i][j]]) {
                std::cout << data[_][0] << " ";
            }
            std::cout << std::endl;
        }
    }
    #endif
}

/*
 * Input:  as below
 * Output: as below
 * Return: last skyline
 */
template <typename Type>
sint pre_processing(std::vector<std::vector<Type>>& data, 
    IMAP& skylines, DSG& graph,
    ISETS& groups, sint k) {
    sint ans = skylines.size();
    sint sky_k = ans;
    int ij_elem, ij_size, temp, layer_size;
    #ifdef DBG_PP
    std::cout << "[Function Pre_Processing]" << std::endl;
    #endif
    for (sint i = 1; i < sky_k; ++ i) {
        layer_size = skylines[i][0];
        for (sint j = 1; j > 0 && j <= layer_size; ++ j) {
            ij_elem = skylines[i][j];
            ij_size = graph.parents[ij_elem].size() + 1;
            if (ij_size >= k) {
                temp = skylines[i][j];
                skylines[i][j] = skylines[i][layer_size];
                skylines[i][layer_size] = temp;
                layer_size --;
                j --;
                if (ij_size == k) {
                    std::unordered_set<int> lucky = graph.parents[ij_elem];
                    lucky.insert(ij_elem);
                    groups.push_back(lucky);
                    #ifdef DBG_PP
                    std::cout << "lucky group: ";
                    for (auto& _ : lucky) {
                        std::cout << data[_][0] << " ";
                    }
                    std::cout << std::endl;
                    #endif
                }
            }
        }
        skylines[i][0] = layer_size;
        if (layer_size == 0) {
            ans = i;
            break;
        }
    }
    #ifdef DBG_PP
    std::cout << "Skylines: " << std::endl;
    for (sint i = 0; i < ans; ++ i) {
        for (sint j = 1; j <= skylines[i][0]; ++ j) {
            std::cout << data[skylines[i][j]][0] << " ";
        }
        std::cout << std::endl;
    }
    #endif
    return ans;
}

/*
 * Input:  as below
 * Output: as below
 * Return: last skyline
 */
template <typename Type>
sint _pre_processing_(std::vector<std::vector<Type>>& data, 
    IMAP& skylines, DSG& graph,
    AnsGroups& groups, sint k) {
    sint ans = skylines.size();
    sint sky_k = ans;
    int ij_elem, ij_size, temp, layer_size;
    #ifdef DBG_PP
    std::cout << "[Function Pre_Processing]" << std::endl;
    #endif
    for (sint i = 1; i < sky_k; ++ i) {
        layer_size = skylines[i][0];
        for (sint j = 1; j > 0 && j <= layer_size; ++ j) {
            ij_elem = skylines[i][j];
            ij_size = graph.parents[ij_elem].size() + 1;
            if (ij_size >= k) {
                temp = skylines[i][j];
                skylines[i][j] = skylines[i][layer_size];
                skylines[i][layer_size] = temp;
                layer_size --;
                j --;
                if (ij_size == k) {
                    std::unordered_set<int> lucky = graph.parents[ij_elem];
                    lucky.insert(ij_elem);
                    groups.push_back(lucky);
                    #ifdef DBG_PP
                    std::cout << "lucky group: ";
                    for (auto& _ : lucky) {
                        std::cout << data[_][0] << " ";
                    }
                    std::cout << std::endl;
                    #endif
                }
            }
        }
        skylines[i][0] = layer_size;
        if (layer_size == 0) {
            ans = i;
            break;
        }
    }
    #ifdef DBG_PP
    std::cout << "Skylines: " << std::endl;
    for (sint i = 0; i < ans; ++ i) {
        for (sint j = 1; j <= skylines[i][0]; ++ j) {
            std::cout << data[skylines[i][j]][0] << " ";
        }
        std::cout << std::endl;
    }
    #endif
    return ans;
}

/*
 * Input:  skylines, [[]], id in sorted data
 *         graph, DSG
 *         k, group size, literaly
 * Output: groups, [set()] IMAP, g-skyline groups
 */
template <typename Type>
void point_wise_gs(std::vector<std::vector<Type>>& data, 
    IMAP& skylines, DSG& graph, 
    AnsGroups& groups, sint k) {
    // pre-processing
    sint sky_k = _pre_processing_(data, skylines, graph, groups, k);
    #ifdef DBG_PW
    std::cout << "sky_k = " << sky_k << std::endl;
    #endif
    int layer, posit, lp_elem, max_layer;
    bool flag;
    sint p, sets_size, layer_size, cur_set_size, cur_status_size;
    // next processing
    // initiate groups size == 1
    ISETS pre;
    IMAP pre_status, cur_status;
    ISETS pre_children;
    layer_size = skylines[0][0];
    for (sint i = 1; i <= layer_size; ++ i) {
        lp_elem = skylines[0][i];
        pre.push_back({ lp_elem });
        // std::vector<int> a_vec(sky_k + 1, 0);
        // a_vec[0] = 1;
        // a_vec[1] = (int)i;
        pre_status.push_back( {0, (int)i} );
        // pre_status.push_back({ 0, (int)i });
        pre_children.push_back( graph.children[lp_elem] );
    }
    cur_status_size = pre_status.size();
    // references
    ISETS* ref_pre = &pre;
    IMAP* ref_prestatus = &pre_status;
    IMAP* ref_curstatus = &cur_status;
    IMAP* ref_statustmp;
    ISETS* ref_prechild = &pre_children;

    ISETS curs[k - 2];
    // IMAP statuss[k - 2];
    ISETS childrens[k - 2];
    #ifdef DBG_PW
    std::cout << "skyline size = " << (*ref_prestatus).size() << std::endl;
    #endif
    for (sint i = 1; i < k - 1; ++ i) {
        ISETS* cur = &curs[i - 1];
        // IMAP* cur_status = &statuss[i - 1];
        cur_status_size = (*ref_curstatus).size();
        cur_set_size = 0;
        ISETS* cur_children = &childrens[i - 1];
        sets_size = (*ref_pre).size();
        for (sint j = 0; j < sets_size; ++ j) { // select a group (i) ref_pre[j]
            int last_layer = (*ref_prestatus)[j][0];
            max_layer = _min_(last_layer + 1, sky_k - 1);
            for (sint tl = last_layer; tl <= max_layer; ++ tl) {
                // layer = (*ref_prestatus)[j][0];
                layer = tl;
                // posit = (*ref_prestatus)[j][1];
                posit = (tl == last_layer) ? (*ref_prestatus)[j][1] : 0;
                // at layer
                layer_size = skylines[layer][0];
                for (p = posit + 1; p <= layer_size; ++ p) {
                    lp_elem = skylines[layer][p];
                    if ((*ref_prechild)[j].size() > 0 &&
                        (*ref_prechild)[j].find(lp_elem) == (*ref_prechild)[j].end() &&
                        layer > 0) { // not in children set or in skyline
                        continue;
                    }
                    flag = true;
                    for (auto& anc : graph.parents[lp_elem]) {  // verify group (i+1), all its parents in it
                        if ((*ref_pre)[j].find(anc) == (*ref_pre)[j].end()) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        std::unordered_set<int> c_set((*ref_pre)[j]);
                        c_set.insert(lp_elem);
                        (*cur).push_back(c_set);
                        // (*cur).push_back((*ref_pre)[j]);
                        // (*cur)[(*cur).size() - 1].insert(lp_elem);

                        // (*cur_status).push_back({ layer, (int)p });
                        if (cur_status_size <= cur_set_size) {
                            // std::vector<int> a_vec(sky_k + 1);
                            // std::copy((*ref_prestatus)[j].begin(), (*ref_prestatus)[j].end(), a_vec.begin());
                            // a_vec[tl + 1] = p;
                            // a_vec[0] = _max_(a_vec[0], tl + 1);
                            // (*ref_curstatus).push_back(a_vec);
                            (*ref_curstatus).push_back({ _max_(last_layer, (int)tl), (int)p });
                        } else {
                            // too much references, will be in trouble !!!
                            // std::vector<int>& a_vec = (*ref_curstatus)[cur_set_size];
                            // a_vec[0] = _max_(last_layer, (int)tl);
                            // a_vec[1] = p;

                            // change it
                            (*ref_curstatus)[cur_set_size][0] = _max_(last_layer, (int)tl);
                            (*ref_curstatus)[cur_set_size][1] = p;

                            // std::copy((*ref_prestatus)[j].begin(), (*ref_prestatus)[j].end(), a_vec.begin());
                            // a_vec[tl + 1] = p;
                            // a_vec[0] = _max_(a_vec[0], tl + 1);
                        }
                        cur_set_size ++;

                        std::unordered_set<int> a_set((*ref_prechild)[j]);
                        a_set.insert(graph.children[lp_elem].begin(), graph.children[lp_elem].end());
                        (*cur_children).push_back(a_set);
                        // (*cur_children)[(*cur_children).size() - 1].insert(graph.children[lp_elem].begin(), graph.children[lp_elem].end());
                    }
                }
            }
        }
        ref_pre = cur;
        // ref_prestatus = cur_status;
        ref_statustmp = ref_prestatus;
        ref_prestatus = ref_curstatus;
        ref_curstatus = ref_statustmp;
        
        ref_prechild = cur_children;
    }
    // generate groups (k)
    sets_size = (*ref_pre).size();
    #ifdef DBG_PW
    std::cout << "Last - 1 : group size = " << sets_size << "  status size = " << (*ref_prestatus).size() << "  children size =  " << (*ref_prechild).size() << std::endl;
    #endif
    for (sint j = 0; j < sets_size; ++ j) {
        int last_layer = (*ref_prestatus)[j][0];
        max_layer = _min_(last_layer + 1, sky_k - 1);
        for (sint tl = last_layer; tl <= max_layer; ++ tl) {
            // layer = (*ref_prestatus)[j][0];
            layer = tl;
            // posit = (*ref_prestatus)[j][1];
            // posit = (*ref_prestatus)[j][tl + 1];
            posit = (tl == last_layer) ? (*ref_prestatus)[j][1] : 0;
            // at layer
            layer_size = skylines[layer][0];
            for (p = posit + 1; p <= layer_size; ++ p) { 
                lp_elem = skylines[layer][p];
                if ((*ref_prechild)[j].size() > 0 &&
                    (*ref_prechild)[j].find(lp_elem) == (*ref_prechild)[j].end() &&
                    layer > 0) { // not in children set
                    continue;
                }
                flag = true;
                for (auto& anc : graph.parents[lp_elem]) {
                    if ((*ref_pre)[j].find(anc) == (*ref_pre)[j].end()) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    // groups.push_back((*ref_pre)[j]);
                    // groups[groups.size() - 1].insert(lp_elem);
                    #ifdef DBG_PW
                    if (j == 50221 && p == 286) 
                        std::cout << "alloc a set begin" << std::endl;
                    #endif 
                    std::unordered_set<int> a_set((*ref_pre)[j]);
                    #ifdef DBG_PW
                    if (j == 50221 && p == 286) 
                        std::cout << "aclloc a set done" << std::endl;
                    #endif 
                    a_set.insert(lp_elem);
                    #ifdef DBG_PW
                    if (j == 50221 && p == 286) {
                        std::cout << "insert done" << std::endl;
                        std::cout << groups.size() << std::endl;
                    }
                    #endif 
                    groups.push_back(a_set);
                    #ifdef DBG_PW
                    if (j == 50221 && p == 286) 
                        std::cout << "push_back done" << std::endl;
                    #endif 
                }
            }
        }
    } // end groups (k)
}

/*
 * Describe: Superset Pruning, Tail Set Prunning, 
 *           Unit Group Reordering, Subset Pruning
 * Input:  as above
 * Output: as above
 */
template <typename Type>
void unit_group_gs(std::vector<std::vector<Type>>& data,
    IMAP& skylines, DSG& graph, 
    ISETS& groups, sint k) {
    // pre-processing
    sint sky_k = pre_processing(data, skylines, graph, groups, k);
    #ifdef DBG_UGW
    std::cout << "[Function Unit_Group_Gs] " << std::endl;
    #endif
    // 1. build unit groups, from tail to head 
    sint points_number = 0;
    sint alayer_size, ij_size, last_size, last_index, pre_index, iterk, usize;
    int ij_elem, init_size;
    for (sint i = 0; i < sky_k; ++ i) {
        points_number += skylines[i][0];
    }
    std::vector<int> unit_groups(points_number);
    points_number = 0;
    for (sint i = 0; i < sky_k; ++ i) {
        alayer_size = skylines[i][0];
        for (sint j = 1; j <= alayer_size; ++ j) {
            unit_groups[points_number ++] = skylines[i][j];
        }
    }
    #ifdef DBG_UGW
    std::cout << "unit_groups content: ";
    for (auto& _ : unit_groups) {
        std::cout << data[_][0] << " ";
    }
    std::cout << std::endl;
    #endif
    // 2. loop through 1-unit groups, from tail to head
    std::unordered_set<int> g_last;
    for (sint i = 0; i < k; ++ i) { // subset pruning
        ij_elem = unit_groups[i];
        g_last.insert(ij_elem);
        g_last.insert(graph.parents[ij_elem].begin(), graph.parents[ij_elem].end());
        if (g_last.size() == k) {
            groups.push_back(g_last);
            #ifdef DBG_UGW
            std::cout << "lucky group: ";
            for (auto& _ : g_last) {
                std::cout << data[_][0] << " ";
            }
            std::cout << std::endl;
            #endif
            last_index = i;
            break;
        } else if (g_last.size() > k) {
            last_index = i - 1;
            break;
        }
    }
    #ifdef DBG_UGW
    std::cout << "Last_Index = " << last_index << std::endl;
    #endif
    // build 1-unit group
    init_size = points_number - 1 - last_index;
    IMAP pre(init_size);
    ISETS pre_members(init_size);
    pre_index = 0;
    for (sint i = points_number - 1; i > last_index; -- i) {
        pre[pre_index] = { (int)i, unit_groups[i] };
        pre_members[pre_index ++] = graph.parents[unit_groups[i]];
    }
    IMAP* ref_pre = &pre;
    ISETS* ref_premem = &pre_members;
    // iteration
    iterk = k - 2;
    usize = 3;
    IMAP curs[k-1];
    ISETS members[k-1];
    while ((*ref_pre).size() > 0) {
        IMAP* cur = &curs[usize - 3];
        ISETS* cur_members = &members[usize - 3];
        pre_index = (*ref_pre).size();
        for (sint i = 0; i < pre_index; ++ i) { // gruop i: (*ref_pre)[i]
            std::unordered_set<int> items((*ref_premem)[i]); // ui's parents
            for (int j = (*ref_pre)[i][0] - 1; j >= 0; -- j) { // check unit_groups[j] in parents set
                ij_elem = unit_groups[j];
                if (items.empty() || items.find(ij_elem) == items.end()) { // ij_elem not in parent set
                    std::unordered_set<int> new_item(items);
                    new_item.insert(graph.parents[ij_elem].begin(), graph.parents[ij_elem].end());
                    if (new_item.size() == iterk) { // find a result
                        #ifdef DBG_UGW
                        std::cout << "Find ";
                        for (auto& _ : (*ref_pre)[i]) 
                            std::cout << data[_][0] << " ";
                        std::cout << " | " << data[ij_elem][0] << " | ";
                        for (auto& _ : new_item) 
                            std::cout << data[_][0] << " ";
                        std::cout << std::endl;
                        #endif
                        new_item.insert(ij_elem);
                        new_item.insert((*ref_pre)[i].begin() + 1, (*ref_pre)[i].end());
                        groups.push_back(new_item);
                    } else if (new_item.size() < iterk) { // next iteration
                        #ifdef DBG_UGW
                        std::cout << "New ";
                        for (auto& _ : (*ref_pre)[i])
                            std::cout << data[_][0] << " ";
                        std::cout << " | " << data[ij_elem][0] << std::endl;
                        #endif
                        std::vector<int> new_vec(usize);
                        std::copy((*ref_pre)[i].begin() + 1, (*ref_pre)[i].end(), new_vec.begin() + 1);
                        new_vec[0] = j;
                        new_vec[usize - 1] = ij_elem;
                        (*cur).push_back(new_vec);
                        (*cur_members).push_back(new_item);
                    }
                    #ifdef DBG_UGW 
                    else { 
                    std::cout << "Prune ";
                    for (auto& _ : (*ref_pre)[i])
                        std::cout << data[_][0] << " ";
                    std::cout << " | " << data[ij_elem][0] << std::endl;
                    }
                    #endif
                }
            }
        }
        ref_pre = cur;
        ref_premem = cur_members;
        iterk --;
        usize ++;
    }
}

template <typename Type>
void base_line(std::vector<std::vector<Type>>& data,
    IMAP& skylines, DSG& graph, 
    ISETS& groups, sint k) {
    // pre-processing
    sint sky_k = pre_processing(data, skylines, graph, groups, k);
    sint points_number = 0, alayer_size;
    for (sint i = 0; i < sky_k; ++ i) {
        points_number += skylines[i][0];
    }
    std::vector<int> unit_groups(points_number);
    points_number = 0;
    for (sint i = 0; i < sky_k; ++ i) {
        alayer_size = skylines[i][0];
        for (sint j = 1; j <= alayer_size; ++ j) {
            unit_groups[points_number ++] = skylines[i][j];
        }
    }
    // generate combinations
    std::vector<bool> comb(points_number);
    std::fill(comb.begin(), comb.begin() + k, true);
    do {
        std::unordered_set<int> candidate;
        for (int i = 0; i < points_number; ++ i) {
            if (comb[i]) {
                candidate.insert(unit_groups[i]);
            }
        }
        bool flag = true;
        for (auto& _ : candidate) {
            for (auto& p : graph.parents[_]) {
                if (candidate.find(p) == candidate.end()) {
                    flag = false;
                    break;
                }
            }
            if (!flag) 
                break;
        }
        if (flag) 
            groups.push_back(candidate);
    } while (std::prev_permutation(comb.begin(), comb.end()));
}