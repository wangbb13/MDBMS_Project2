#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

#define _max_(a, b) ((a) > (b) ? (a) : (b))
#define _min_(a, b) ((a) < (b) ? (a) : (b))

typedef std::unordered_map<int, std::vector<int>> ADJ;

typedef std::vector<std::vector<int>> IMAP;

typedef std::size_t sint;

typedef struct dsg {
    std::unordered_map<int, std::unordered_set<int>> parents;
    std::unordered_map<int, std::unordered_set<int>> children;
} DSG;

typedef std::vector<std::unordered_set<int>> ISETS;

typedef struct pug {
    int point;
    std::unordered_set<int>* unit_group;
} PUG;

typedef struct pug_ {
    int point;
    std::unordered_set<int> unit_group;
} PUG_NR;


class AnsGroups
{
private:
    sint total_size;
    sint row;
    sint offset;
    std::vector<ISETS*> all_group;
    sint block;
    
    sint flush_threshold;
    bool flush_able;
    bool has_flush;
    const char* filename;
    std::vector<int>* map_f;

public:
    AnsGroups(int _block_ = 100000, int _thre_ = 10) {
        total_size = 0;
        row = 0;
        offset = 0;
        block = _block_;
        
        flush_threshold = _thre_;
        flush_able = false;
        has_flush = false;
    }
    ~AnsGroups() {
        
    }

    void enableFlush(const char* flushfile, const std::vector<int>& _map_f_) {
        filename = flushfile;
        map_f = &_map_f_;
        flush_able = true;
    }

    std::unordered_set<int>* get(sint i) {
        if (i < total_size) {
            sint h = i / block;
            sint w = i % block;
            ISETS* r_data = all_group[h];
            std::unordered_set<int>* ans = &((*r_data)[w]);
            return ans;
        }
        return NULL;
    }

    sint size() {
        return total_size;
    }

    void push_back(std::unordered_set<int>& item) {
        total_size ++;
        if (all_group.size() == 0) {
            all_group.push_back(new ISETS(block));
        }
        if (offset == (all_group[row])->size()) {
            row ++;
            
            if (flush_able && row == flush_threshold) {
                std::ofstream fout;
                if (has_flush)
                    fout.open(filename, std::ios_base::app);
                else
                    fout.open(filename);
                write(fout);
                for (sint i = 0; i < row; ++ i) 
                    delete all_group[i];
                all_group.clear();
                row = 0;
                has_flush = true;
            }
            
            all_group.push_back(new ISETS(block));
            offset = 0;
        }
        (*(all_group[row]))[offset ++] = item;
    }

    std::unordered_set<int>& operator [] (sint i) {
        std::unordered_set<int>* item = get(i);
        if (item != NULL) 
            return *item;
        std::unordered_set<int> temp;
        std::unordered_set<int>& ans = temp;
        return ans;
    }

    void write(std::ofstream& fout) {
        sint group_size = all_group.size();
        for (sint i = 0; i < group_size - 1; ++ i) {
            ISETS* data = all_group[i];
            for (auto& row : (*data)) {
                for (auto& e : row) {
                    fout << map_f[e] << " ";
                }
                fout << "\n";
            }
        }
        ISETS* data = all_group[group_size - 1];
        for (auto& row : (*data)) {
            if (row.size() == 0) 
                break;
            for (auto& e : row) {
                fout << map_f[e] << " ";
            }
            fout << "\n";
        }
        fout.close();
    }

    void flush() {
        std::ofstream fout(filename);
        if (has_flush) 
            fout.open(filename, std::ios_base::app);
        else
            fout.open(filename);
        if (!fout.is_open()) {
            std::cout << "can not open file " << filename << std::endl;
            return;
        }
        write(fout);
    }
};

class Matrix {
private:
    sint total_size;
    sint row;
    sint offset;
    sint block;
    std::vector<IMAP*> mat;

public:
    Matrix() {
        total_size = 0;
        row = 0;
        offset = 0;
        block = 100000;
    }
    ~Matrix() {

    }

    sint size() {
        return total_size;
    }

    std::vector<int>* get(sint i) {
        if (i < total_size) {
            sint h = i / block;
            sint w = i % block;
            IMAP* r_data = mat[h];
            std::vector<int>* ans = &((*r_data)[w]);
            return ans;
        }
        return NULL;
    }

    void push_back(std::vector<int>& item) {
        total_size ++;
        if (mat.size() == 0) {
            mat.push_back(new IMAP(block));
        }
        if (offset == block) {
            mat.push_back(new IMAP(block));
            row ++;
            offset = 0;
        }
        (*(mat[row]))[offset ++] = item;
    }

    std::vector<int>& operator [] (sint i) {
        std::vector<int>* item = get(i);
        if (item != NULL)
            return *item;
        std::vector<int> temp;
        std::vector<int>& ans = temp;
        return ans;
    }
};
