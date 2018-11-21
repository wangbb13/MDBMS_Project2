#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

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
