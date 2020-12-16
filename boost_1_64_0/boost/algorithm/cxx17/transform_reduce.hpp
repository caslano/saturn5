/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_reduce.hpp
/// \brief Combine the (transformed) elements of a sequence (or two) into a single value.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator1, class InputIterator2, class T,
         class BinaryOperation1, class BinaryOperation2>
T transform_reduce(InputIterator1 first1, InputIterator1 last1,
                   InputIterator2 first2, T init,
                 BinaryOperation1 bOp1, BinaryOperation2 bOp2)
{
    for (; first1 != last1; ++first1, (void) ++first2)
        init = bOp1(init, bOp2(*first1, *first2));
    return init;
}

template<class InputIterator, class T,
         class BinaryOperation, class UnaryOperation>
T transform_reduce(InputIterator first, InputIterator last,
                   T init, BinaryOperation bOp, UnaryOperation uOp)
{
    for (; first != last; ++first)
        init = bOp(init, uOp(*first));
    return init;
}

template<class InputIterator1, class InputIterator2, class T>
T transform_reduce(InputIterator1 first1, InputIterator1 last1,
                   InputIterator2 first2, T init)
{
    return boost::algorithm::transform_reduce(first1, last1, first2, init,
                            std::plus<T>(), std::multiplies<T>());
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

/* transform_reduce.hpp
EXUKMjEFlCQjAe3kczamgvUtUq3iq25J1qMH8lSl5vJUYabuJ+quOIdHeu6Pmijv+UQGXiSObne/kpQAUaZUEGef1Ffj7EN/qXL2om0cZKuI6J/etXkjl7l6nVNZMZZZ/l5+oNumHEUhon2b4qGUXCiP0OeSkUmzsCDskYD/bfRlLHuCksvZPV2Z7z6mKt3Hkv1jQ8p4y8n+O+11/8ru0s1kUjZJQM9CAjKLtZ3Ah2vC2P0F/gcfAADqz++k18mQdTrrdV4UD6EOdaf6b6jntiO6olUy5EgUEr8PY/9Zjf9/a5MYkcUY8QuJEVYxiNqdGyYjeEwi5jpJaz+T2SWGhwhVYfTlS9eNTCYQdRFZGowTloKSi1IwYzEUhFwT5tmm7IH9o3ewubLjc21axxuInclo9CzSJeefsq2mgfLbSQBkGbND2Ub+mgM7yBeGFg8mt5+4xdhsbpJjSwEcMhCiIUZmy1JjUUrZhm4ViMwOahQ3lBb7m9Z5+BVgCL0FdoqksBmy8HKVplNBYMnkDCimDJHS+gxuInubM+MzVyMeGQ1V7LPQTE6Gx9ynEP2s6Vcm1dsnM9PTXUeoI1sHBd0np8muz8rirpf0R9edNgpjRgUyixdtQ2YMxsWt/c6i5SD1jSw1tdg3tV+2WabOscgJGDNI7qyYAXgrctaH8HQWM9Op54JPFw8ZeHAF2WlUbjmTKrzLyD93SxcW4mdqG7ENbpIyezdlPx2vuiznjUyyUX6mw8QZU3tzRk+qZ0I1QpqacB6QAlJxYir5VSQVnBiQQeWplGXI98rZ1ZnUJfRFzMMesjoOv3gNp+MXgY+JQaq+CiORCqh2RN7riBm0vrXMKB2cT4LuiFu5t5nk3t3Vznu30PZuDoo57r/Lb/dy/UEe9vLPUmLoIrmXxjebu72OR8TiDUZimyQY1xok38TXE3ycQ1RwZpT0djU79hBjciqfyzOnclIlQ2wjzD35kQry/BmULUlvmdRHaI50u+jol9jKwIqAV9h54qRB0n+mtAkuGKJ5i8HODGnW0lPU+V/IZNYQGzj5NCUPRzL3C23qnU3k/nBXxFrpbl8grjtT6z0FN3ayLbQHgNz2x8TrubR96g5SG7IZz4oNvnjGnlK3S7BjaYT7WtfJB01AKRAXaDOhjkDW5T7QWOkJBaE0Z2JqrSATPp5WRK3lV7cdJW3eVRmxK95a2lDykqR+chrm5xBfiJWJFiRSk5ORWOSh0haZcbyvjC42OIdIpfqGf6EDVAjyjm+8Tpb0oPCT+tpDVhJ0TlLQk55p+x1KuTW9RT3eW5BucB0hhutQtmd8bBn6sTOvQhz/daQBfmNvsSYEUy8ecfDpDN+x6N2r+sSSGTpeT6glOaUSulW4yu4v/CJc+UCLszNYvoeBfDEtwWDASvwio2LRFHa89sQ/em+8Grjtgz7yfbYHsQcBDrUA0NIt7XcMKv/t1ZPVvZAYHsXv6UN74QrshVFiw1XEotfJN7Bs6HfhevxGn5kS+IkL9vT9ET4Om0OXN1VPh/bdvf4d+/RtZx66jUjyFDbvpFnfjqTHpdATyI63r4xY9wES2e2y0qpsSG+U33Tq8qUnvWtXbks3u47YsKp0XLG6w6fxjrloAiTOosOLrUq50x2/KSPWQNk23PyYKpfj/QS7OzPMXl4dbncvMfa3rGp4RbH9rN2yZqin8IBF/Q3F1SGj64Msd0O7Pa+8Mjw1mh5QyltfGd7VcDm8Ws/9p6oWysJJ/5+mMdIt9+uqheU0RYW9oMreblXwb60Tp06KhA9mKQXvk65o6ad4G4llJU8nlaIKabhX4pN07M+y9IqgQZaiPShH1JGlVDmUDdb6Z8HM9F7a6w0=
*/