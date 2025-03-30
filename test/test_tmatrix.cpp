#include "utmatrix.h"
//#include "Trees.cpp"
#include <map>
#include <random>
#include <gtest.h>
#include <ctime>
#include "SimpleTree.cpp"

//TEST(TMatrix, can_create_matrix_with_positive_length)
//{
//    ASSERT_NO_THROW(TMatrix<int> m(5));
//}
//
//TEST(TMatrix, cant_create_too_large_matrix)
//{
//    const int s = 65536;
//    ASSERT_ANY_THROW(TMatrix<int>m(s));
//}
//
//TEST(TMatrix, throws_when_create_matrix_with_negative_length)
//{
//    ASSERT_ANY_THROW(TMatrix<int> m(-5));
//}
//
//TEST(TMatrix, can_create_copied_matrix)
//{
//    TMatrix<int> m(2);
//
//    ASSERT_NO_THROW(TMatrix<int>m2(m));
//}
//
//TEST(TMatrix, copied_matrix_is_equal_to_source_one)
//{
//    TMatrix<int> m(3);
//    m[0][0] = 1; m[0][1] = 1; m[0][2] = 1; m[1][1] = 1; m[1][2] = 1; m[2][2] = 1;
//
//    TMatrix<int> mc(m);
//
//    EXPECT_EQ(m, mc);
//}
//
//TEST(TMatrix, copied_matrix_has_its_own_memory)
//{
//    TMatrix<int> m(3);
//    m[0][0] = 1; m[0][1] = 1; m[0][2] = 1; m[1][1] = 1; m[1][2] = 1; m[2][2] = 1;
//    TMatrix<int> mc(m);
//
//    mc[2][2] = 3;
//    EXPECT_NE(m, mc);
//}
//
//TEST(TMatrix, can_get_size)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 1; m[0][1] = 1; m[1][1] = 1;
//
//    EXPECT_EQ(2, m.getSize());
//}
//
//TEST(TMatrix, can_set_and_get_element)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 1; m[0][1] = 1; m[1][1] = 1;
//    m[0].setElement(0, 1);
//
//    EXPECT_EQ(1, m[0].getElement(0));
//
//}
//
//TEST(TMatrix, throws_when_set_element_with_negative_index)
//{
//    TMatrix<int> m(2);
//
//    ASSERT_ANY_THROW(m[0].setElement(-1, 7));
//}
//
//TEST(TMatrix, throws_when_set_element_with_too_large_index)
//{
//    TMatrix<int> m(2);
//
//    ASSERT_ANY_THROW(m[0].setElement(3, 7));
//}
//
//TEST(TMatrix, can_assign_matrix_to_itself)
//{
//    TMatrix<int> m(2);
//    
//    ASSERT_NO_THROW(m = m);
//}
//
//TEST(TMatrix, can_assign_matrices_of_equal_size)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 0; m[0][1] = 2; m[1][1] = 3;
//    TMatrix<int> mt(2);
//    mt[0][0] = 1; mt[0][1] = 1; mt[1][1] = 1;
//
//    ASSERT_NO_THROW(m = mt);
//}
//
//TEST(TMatrix, assign_operator_change_matrix_size)
//{
//    TMatrix<int> m(2);
//    TMatrix<int> mt(3);
//
//    m = mt;
//
//    EXPECT_EQ(3, m.getSize());
//}
//
//TEST(TMatrix, can_assign_matrices_of_different_size)
//{
//    TMatrix<int> m(2);
//    TMatrix<int> mt(3);
//
//    ASSERT_NO_THROW(m = mt);
//}
//
//TEST(TMatrix, compare_equal_matrices_return_true)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 1; m[0][1] = 1; m[1][1] = 1;
//    TMatrix<int> mt(2);
//    mt[0][0] = 1; mt[0][1] = 1; mt[1][1] = 1;
//
//    EXPECT_EQ(true, m == mt);
//}
//
//TEST(TMatrix, compare_matrix_with_itself_return_true)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 1; m[0][1] = 1; m[1][1] = 1;
//
//    EXPECT_EQ(true, m == m);
//}
//
//TEST(TMatrix, matrices_with_different_size_are_not_equal)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 1; m[0][1] = 1; m[1][1] = 1;
//    TMatrix<int> mt(3);
//    mt[0][0] = 1; mt[0][1] = 1; mt[1][1] = 1;
//
//    EXPECT_EQ(true, m != mt);
//}
//
//TEST(TMatrix, can_add_matrices_with_equal_size)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 1; m[0][1] = 1; m[1][1] = 1;
//    TMatrix<int> mt(2);
//    mt[0][0] = 1; mt[0][1] = 1; mt[1][1] = 1;
//    
//    m = m + mt;
//
//    TMatrix<int> res(2);
//    res[0][0] = 2; res[0][1] = 2; res[1][1] = 2;
//
//    EXPECT_EQ(res, m);
//}
//
//TEST(TMatrix, cant_add_matrices_with_not_equal_size)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 1; m[0][1] = 1; m[1][1] = 1;
//    TMatrix<int> mt(3);
//    mt[0][0] = 1; mt[0][1] = 1; mt[1][1] = 1;
//
//    ASSERT_ANY_THROW(m + mt);
//}
//
//TEST(TMatrix, can_subtract_matrices_with_equal_size)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 2; m[0][1] = 2; m[1][1] = 2;
//    TMatrix<int> mt(2);
//    mt[0][0] = 1; mt[0][1] = 1; mt[1][1] = 1;
//
//    TMatrix<int> res(2);
//    m[0][0] = 1; m[0][1] = 1; m[1][1] = 1;
//
//    EXPECT_EQ(res, m - mt);
//}
//
//TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
//{
//    TMatrix<int> m(2);
//    m[0][0] = 2; m[0][1] = 2; m[1][1] = 2;
//    TMatrix<int> mt(3);
//    mt[0][0] = 1; mt[0][1] = 1; mt[1][1] = 1;
//
//    ASSERT_ANY_THROW(m - mt);
//}
//
//TEST(TMatrix, can_subtract_matrices_with_equal_size_2)
//{
//    TMatrix<int> m1(3), m2(3), res(3);
//    m1[0][1] = 1;
//    m1[2][2] = 2;
//    m2[1][1] = 3;
//    m2[2][2] = 4;
//    res[0][1] = m1[0][1] - m2[0][1];
//    res[2][2] = m1[2][2] - m2[2][2];
//    res[1][1] = m1[1][1] - m2[1][1];
//    EXPECT_EQ(m1 - m2, res);
//}
/*
TEST(AVLTreeTest, 1000elem)
{
    AVLTree<int, int> t;
    std::map<int, int> m;
    int n = 2500;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    auto r = std::default_random_engine{};
    shuffle(v.begin(), v.end(), r);

    double start = clock();
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.insert(v[i], 0));
    }
    double end = clock();
    double st1 = clock();
    for (int i = 0; i < n; i++) {
        m.insert({ v[i], 0 });
    }
    double end1 = clock();

    //cout << endl << end0 - start << " " << end1 - end0 << endl;


    cout << endl << "AVL: " << (end - start) << " map: " << (end1 - st1) << endl;
}

TEST(AVLTreeTest, VersusTestHesh2000) {
    AVLTree<int, int> t;
    std::map<int, int> m;
    int n = 2000;
    vector<int> v;
    vector<int> vc;
    vector<int> vcc;
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    auto r = std::default_random_engine{};
    shuffle(v.begin(), v.end(), r);
    vc = v;
    shuffle(vc.begin(), vc.end(), r);
    vcc = vc;
    shuffle(vcc.begin(), vcc.end(), r);

    double start = clock();
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.insert(v[i], 0));
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.find(vc[i]));
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.remove(vcc[i]));
    }
    double end0 = clock();

    for (int i = 0; i < n; i++) {
        m.insert({ v[i], 0 });
    }
    for (int i = 0; i < n; i++)
    {
        m.find(vc[i]);
    }
    for (int i = 0; i < n; i++)
    {
        m.erase(vcc[i]);
    }
    double end1 = clock();

    cout << endl << "AVL: " << (end0 - start) << " map: " << (end1 - end0) << endl;
}


TEST(AVLTreeTest, VersusTestHesh8000) {
    AVLTree<int, int> t;
    std::map<int, int> m;
    int n = 8000;
    vector<int> v;
    vector<int> vc;
    vector<int> vcc;
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    auto r = std::default_random_engine{};
    shuffle(v.begin(), v.end(), r);
    vc = v;
    shuffle(vc.begin(), vc.end(), r);
    vcc = vc;
    shuffle(vcc.begin(), vcc.end(), r);

    double start = clock();
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.insert(v[i], 0));
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.find(vc[i]));
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.remove(vcc[i]));
    }
    double end0 = clock();

    for (int i = 0; i < n; i++) {
        m.insert({ v[i], 0 });
    }
    for (int i = 0; i < n; i++)
    {
        m.find(vc[i]);
    }
    for (int i = 0; i < n; i++)
    {
        m.erase(vcc[i]);
    }
    double end1 = clock();

    cout << endl << "AVL: " << (end0 - start) << " map: " << (end1 - end0) << endl;
}


TEST(AVLTreeTest, VersusTestHesh16000) {
    AVLTree<int, int> t;
    std::map<int, int> m;
    int n = 16000;
    vector<int> v;
    vector<int> vc;
    vector<int> vcc;
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    auto r = std::default_random_engine{};
    shuffle(v.begin(), v.end(), r);
    vc = v;
    shuffle(vc.begin(), vc.end(), r);
    vcc = vc;
    shuffle(vcc.begin(), vcc.end(), r);

    double start = clock();
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.insert(v[i], 0));
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.find(vc[i]));
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.remove(vcc[i]));
    }
    double end0 = clock();

    for (int i = 0; i < n; i++) {
        m.insert({ v[i], 0 });
    }
    for (int i = 0; i < n; i++)
    {
        m.find(vc[i]);
    }
    for (int i = 0; i < n; i++)
    {
        m.erase(vcc[i]);
    }
    double end1 = clock();

    cout << endl << "AVL: " << (end0 - start) << " map: " << (end1 - end0) << endl;
}

TEST(AVLTreeTest, VersusTestHesh64000) {
    AVLTree<int, int> t;
    std::map<int, int> m;
    int n = 64000;
    vector<int> v;
    vector<int> vc;
    vector<int> vcc;
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    auto r = std::default_random_engine{};
    shuffle(v.begin(), v.end(), r);
    vc = v;
    shuffle(vc.begin(), vc.end(), r);
    vcc = vc;
    shuffle(vcc.begin(), vcc.end(), r);

    double start = clock();
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.insert(v[i], 0));
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.find(vc[i]));
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_NO_THROW(t.remove(vcc[i]));
    }
    double end0 = clock();

    for (int i = 0; i < n; i++) {
        m.insert({ v[i], 0 });
    }
    for (int i = 0; i < n; i++)
    {
        m.find(vc[i]);
    }
    for (int i = 0; i < n; i++)
    {
        m.erase(vcc[i]);
    }
    double end1 = clock();

    cout << endl << "AVL: " << (end0 - start) << " map: " << (end1 - end0) << endl;
}
*/
TEST(TreeTest, MegaPuperTest)
{
    int n = 5000000;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    auto r = std::default_random_engine{};
    shuffle(v.begin(), v.end(), r);
    Tree<int, int> t;
    int st = clock();
    for (int i = 0; i < n; i++)
    {
        t.insert(v[i], 0);
    }
    int st1 = clock();
    for (int i = 0; i < n; i++)
    {
        t.remove(v[i]);
    }
    int end = clock();
    cout <<endl<< st1 - st << " " << end - st1<<endl;
    
}