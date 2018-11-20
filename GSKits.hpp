#pragma once 

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "types.hpp"
#include "micro.hpp"

template <typename Type>
Type string_to_num(const std::string& str) {
    std::stringstream ss(str);
    Type ans;
    ss >> ans;
    return ans;
}

template <typename datatype>
void read_data(const char* filename, 
    std::vector<std::vector<datatype>>& contain, 
    char delim = ' ') {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "Can not open file " << filename << std::endl;
        return;
    }
    char newline = '\n';
    sint column_number = 1;
    sint row_no = 1; // row number from 1
    sint col_i;
    std::string one_line = "";
    std::string one_col = "";
    std::getline(fin, one_line, newline);
    std::istringstream iss(one_line);
    while (std::getline(iss, one_col, delim)) {
        column_number ++;
    }
    #ifdef DEBUG
    std::cout << "[Read Data] column number: " << column_number-1 << std::endl;
    #endif
    fin.seekg(0, std::ios::beg);
    while (std::getline(fin, one_line, newline)) {
        std::vector<datatype> one_row(column_number);
        iss.clear();
        iss.str(one_line);
        col_i = 0;
        one_row[col_i ++] = row_no ++;
        while (std::getline(iss, one_col, delim)) {
            one_row[col_i ++] = string_to_num<datatype>(one_col);
        }
        if (col_i > 1) {
            contain.push_back(one_row);
        }
    }
    fin.close();
}

template <typename Type>
void show_2d_vector(const std::vector<std::vector<Type>>& vec2d) {
    for (auto& x : vec2d) {
        for (auto& e : x) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}

template <typename Type>
bool dominate(const std::vector<Type>& a, const std::vector<Type>& b) { // if a dominate b
    bool ans = true;
    bool lt = false;
    sint length = a.size();
    for (sint i = 1; i < length; ++ i) {
        if (a[i] > b[i]) {
            ans = false;
            break;
        }
        if (a[i] < b[i]) {
            lt = true;
        }
    }
    return (ans && lt);
}

template <typename Type>
sint bin_search(const std::vector<Type>& list,
    const Type& elem,
    sint l = 0, sint r = -1) {
    if (-1 == r) {
        r = list.size() - 1;
    }
    sint mid;
    while (l < r) {
        mid = (l + r) / 2;
        if (list[mid] <= elem) { // list[mid] dominated elem
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

template <typename Type>
inline void copy_vector(std::vector<Type>& a, std::vector<Type>& b, 
    sint l, sint r) { // a = b
    for (sint i = l; i < r; ++ i) {
        a[i] = b[i];
    }
}

template <typename Type>
bool same(const std::vector<Type>& a, const std::vector<Type>& b) {
    bool ans = true;
    for (sint i = 0; i < a.size(); ++ i) {
        if (a[i] != b[i]) {
            ans = false;
            break;
        }
    }
    return ans;
}

template <typename Type>
void save_groups(const char* filename, const ISETS& data, 
    const std::vector<std::vector<Type>>& map_data) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cout << "can not open file " << filename << std::endl;
        return;
    }
    for (auto& row : data) {
        for (auto& e : row) {
            fout << map_data[e][0] << " ";
        }
        fout << "\n";
    }
    fout.close();
}

void c_combination(int n, int m) { // select m elems from n
    std::vector<bool> v(n);
    std::fill(v.begin(), v.begin() + m, true);
    do {
        for (int i = 0; i < n; ++ i) {
            if (v[i]) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    } while (std::prev_permutation(v.begin(), v.end()));
}
