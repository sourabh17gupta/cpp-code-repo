#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

//insert and find index of element in O(logn) time

int main() {
    ordered_set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(15);

    cout<<*s.find_by_order(0)<<"\n"; // 10 (0-th smallest)
    cout << *s.find_by_order(2) << "\n"; // 20 (2nd smallest)
    cout << s.order_of_key(15) << "\n";  // 1 (elements < 15)
    cout << s.order_of_key(17) << "\n";  // 2 (elements < 17)
}
