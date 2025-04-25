#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

//This version of multiset works exactly as standard multiset with additional features
template <typename T>
using ordered_multiset = tree<pair<T, int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

//This version of multiset will behave differently a bit(can store multi values) but erase have different effect
//Like lower bound function will erase element greater than the value(It's fine how we defined it,less equal)
//template <typename T>
//using ordered_multiset = tree<pair<T, int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T, typename U>
using mp = tree<T, U, less<>, rb_tree_tag, tree_order_statistics_node_update>;