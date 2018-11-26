#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "GSKits.hpp"
#include "types.hpp"
#include <algorithm>

TEST_CASE("test string to number", "[gskits.hpp] string_to_num") {
    std::string test1 = "121.1";
    float test1_a = string_to_num<float>(test1);
    REQUIRE( test1_a == 121.1f );
    std::string test2 = ".123";
    float test2_a = string_to_num<float>(test2);
    REQUIRE( test2_a == 0.123f );
}

TEST_CASE("test read data from file", "[gskits.hpp] read_data") {
    // std::vector<std::vector<double>> container;
    // read_data<double>("data.txt", container);
    // show_2d_vector<double>(container);
}

TEST_CASE("test combinatins", "[GSKits.hpp] c_combination") {
    int a = 100, b = 3;
    // c_combination(a, b);
}

TEST_CASE("ohters", "[]") {
    std::cout << "Test initiate vector" << std::endl;
    ADJ a;
    a[1] = { 2 };
    a[2] = std::vector<int>();
    std::vector<int> x = a[1];
    std::vector<int> y = a[2];
    std::cout << x.size() << " " << y.size() << std::endl;

    std::cout << "Test DSG" << std::endl;
    DSG graph;
    std::cout << graph.parents.empty() << std::endl;
    graph.parents[1].insert(2);
    std::cout << graph.parents.empty() << std::endl;

    std::cout << "Test vector reference" << std::endl;
    std::vector<int> one_vec(5, 1);
    std::vector<int>& vec_ref = one_vec;
    std::cout << one_vec[0] << std::endl;
    vec_ref[0] = 0;
    std::cout << one_vec[0] << std::endl;

    std::cout << "Test null set" << std::endl;
    std::unordered_set<int> t_uset;
    t_uset = {};
    for (auto& x : t_uset) {
        std::cout << x << " ";
    }

    std::cout << "Test struct pug" << std::endl;
    std::unordered_set<int> pug_set;
    pug_set.insert(1);
    pug_set.insert(2);
    pug_set.insert(3);
    pug_set.insert(4);
    std::vector<PUG> vec_pug_0(1);
    std::vector<PUG_NR> vec_pug_1(1);
    vec_pug_0[0] = {0, &pug_set};
    // vec_pug_0[0].point = 0;
    // vec_pug_0[0].unit_group = pug_set;
    vec_pug_1[0].point = 0;
    vec_pug_1[0].unit_group = pug_set;
    vec_pug_0[0].unit_group->insert(5);
    std::cout << "pug_set size: " << pug_set.size() << std::endl;
    std::cout << "reference vector set size: " << vec_pug_0[0].unit_group->size() << std::endl;
    vec_pug_1[0].unit_group.erase(4);
    std::cout << "common vector set size: " << vec_pug_1[0].unit_group.size() << std::endl;
    std::cout << "pug_set size: " << pug_set.size() << std::endl;
    std::cout << "Test AC" << std::endl;

    std::cout << "Test unordered_set erase methods" << std::endl;
    std::unordered_set<int> erase_set = { 1, 2, 3, 4, 5 };
    std::unordered_set<int> _set = { 4, 5 };
    std::cout << "erase_set size: " << erase_set.size() << std::endl;
    std::cout << "Test AC" << std::endl;

    std::cout << "Test IMAP initiate" << std::endl;
    IMAP imap_test(10);
    std::cout << imap_test.size() << std::endl;
    std::cout << "Test AC" << std::endl;

    std::cout << "Test vector initiate" << std::endl;
    std::vector<int> vec_init = { 7,8,9 };
    std::cout << vec_init.size() << std::endl;
    std::cout << "Test AC" << std::endl;

    std::cout << "Test vector pointer" << std::endl;
    std::vector<int>* vec_p = &vec_init;
    std::cout << (*vec_p)[1] << (*vec_p).size() << std::endl;
    std::cout << "Test AC" << std::endl;

    std::cout << "Test set insert vector" << std::endl;
    std::cout << erase_set.size() << std::endl;
    erase_set.insert(vec_init.begin() + 1, vec_init.end());
    std::cout << erase_set.size() << std::endl;
    REQUIRE( erase_set.size() == 7 );
    std::vector<int> copy_vec(3);
    std::copy(vec_init.begin() + 1, vec_init.end(), copy_vec.begin() + 1);
    std::cout << copy_vec[0] << "," << copy_vec[1] << "," << copy_vec[2] << std::endl;
    std::sort(copy_vec.begin(), copy_vec.end(), [](int a, int b) {
        return a > b;
    });
    std::cout << copy_vec[0] << "," << copy_vec[1] << "," << copy_vec[2] << std::endl;
    std::cout << "Test AC" << std::endl;
}

TEST_CASE("test class", "abc") {
    AnsGroups group;
    sint index = 0;
    std::cout << "size = " << group.size() << std::endl;
    std::unordered_set<int> a( {1, 2} );
    group.push_back(a);
    std::cout << "size = " << group.size() << std::endl;
    std::cout << "3 in set ? " << (group[index].find(3) == group[index].end()) << std::endl;
    std::unordered_set<int> b(group[index]);
    b.insert(3);
    std::cout << "b size = " << b.size() << " size = " << group[index].size() << std::endl;
}

TEST_CASE("test stack", "abc") {
    std::stack<std::vector<int>> my_stack;
    my_stack.push( { 1, 2, 3 } );
    std::cout << "stack size = " << my_stack.size() << std::endl;
    std::vector<int> fetch = my_stack.top();
    my_stack.pop();
    fetch.push_back(4);
    std::cout << "stack size = " << my_stack.size() << " fetch size = " << fetch.size() << std::endl;
}
