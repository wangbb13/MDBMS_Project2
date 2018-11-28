#include "GSAlgorithms.hpp"
#include <chrono>
using namespace std::chrono;

/*
 * Input:  in-data file name
 *         out-data filename
 *         k
 *         algorithm: 0-baseline, 1-point-wise, 2-unit-group-wise
 */
int main(int argc, char const *argv[])
{
    if (argc != 5) {
        std::cout << "Usage: ./main input-filename output-filename k alg-code\n0: baseline, 1: point-wise, 2: unit-group-wise+, 3: PWise-DFS, 4: UWise+-DFS" << std::endl;
        return 0;
    }
    const char* input_file = argv[1];
    const char* output_file = argv[2];
    std::string strk = argv[3];
    std::string stra = argv[4];
    std::string algorithms[5] = { "BaseLine", "PWise[BFS]", "UWise+[BFS]", "PWise[DFS]", "UWise+[DFS]" };
    // algorithm 
    sint k = string_to_num<sint>(strk);
    int code = string_to_num<int>(stra);
    if (!(code >= 0 && code < 5)) {
        std::cout << "Algorithm code should be 0, 1, 2, 3, or 4" << std::endl;
        return 0;
    }

    auto start = high_resolution_clock::now();
    std::vector<std::vector<double>> origin_data;
    read_data<double>(input_file, origin_data);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "[Function read_data] \t running time: " << duration.count() << " us" << std::endl;

    start = high_resolution_clock::now();
    IMAP skylines;
    ADJ duplicate;
    k_skyline<double>(origin_data, skylines, duplicate, k);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    std::cout << "[Function k_skyline] \t running time: " << duration.count() << " us" << std::endl;
    auto alg_time = duration.count();

    start = high_resolution_clock::now();
    DSG graph;
    build_dsg<double>(origin_data, skylines, graph);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    std::cout << "[Function build_dsg] \t running time: " << duration.count() << " us" << std::endl;
    alg_time += duration.count();

    // construct map function
    sint data_size = origin_data.size();
    std::vector<int> map_f(data_size);
    for (sint i = 0; i < data_size; ++ i) 
        map_f[i] = (int)origin_data[i][0];

    // algorithms
    start = high_resolution_clock::now();
    AnsGroups groups;
    if (code == 0)
        base_line(origin_data, skylines, graph, groups, k);
    else if (code == 1)
        point_wise_gs(origin_data, skylines, graph, groups, k);
    else if (code == 2)
        unit_group_gs(origin_data, skylines, graph, groups, k);
    else if (code == 3)
        PWiseDfs(origin_data, skylines, graph, groups, k);
    else
        UWiseDfs(origin_data, skylines, graph, groups, k);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    std::cout << "[Algorithm " << algorithms[code] << "] \t running time: " << duration.count() << " us" << std::endl;
    alg_time += duration.count();

    groups.flush(output_file, map_f);

    std::cout << "[Total] \t\t running time: " << alg_time << "us" << std::endl;
    return 0;
}