//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SORT_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_SORT_BY_KEY_HPP

#include <iterator>

#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_cpu.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class KeyIterator, class ValueIterator>
inline void
dispatch_gpu_sort_by_key(KeyIterator keys_first,
                         KeyIterator keys_last,
                         ValueIterator values_first,
                         less<typename std::iterator_traits<KeyIterator>::value_type> compare,
                         command_queue &queue,
                         typename boost::enable_if_c<
                             is_radix_sortable<
                                 typename std::iterator_traits<KeyIterator>::value_type
                             >::value
                         >::type* = 0)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
    }
    else {
        detail::radix_sort_by_key(
            keys_first, keys_last, values_first, queue
        );
    }
}

template<class KeyIterator, class ValueIterator>
inline void
dispatch_gpu_sort_by_key(KeyIterator keys_first,
                         KeyIterator keys_last,
                         ValueIterator values_first,
                         greater<typename std::iterator_traits<KeyIterator>::value_type> compare,
                         command_queue &queue,
                         typename boost::enable_if_c<
                             is_radix_sortable<
                                 typename std::iterator_traits<KeyIterator>::value_type
                             >::value
                         >::type* = 0)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
    }
    else {
        // radix sorts in descending order
        detail::radix_sort_by_key(
            keys_first, keys_last, values_first, false, queue
        );
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void dispatch_gpu_sort_by_key(KeyIterator keys_first,
                                     KeyIterator keys_last,
                                     ValueIterator values_first,
                                     Compare compare,
                                     command_queue &queue)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
    } else {
        detail::merge_sort_by_key_on_gpu(
            keys_first, keys_last, values_first, compare, queue
        );
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void dispatch_sort_by_key(KeyIterator keys_first,
                                 KeyIterator keys_last,
                                 ValueIterator values_first,
                                 Compare compare,
                                 command_queue &queue)
{
    if(queue.get_device().type() & device::gpu) {
        dispatch_gpu_sort_by_key(keys_first, keys_last, values_first, compare, queue);
        return;
    }
    ::boost::compute::detail::merge_sort_by_key_on_cpu(
        keys_first, keys_last, values_first, compare, queue
    );
}

} // end detail namespace

/// Performs a key-value sort using the keys in the range [\p keys_first,
/// \p keys_last) on the values in the range [\p values_first,
/// \p values_first \c + (\p keys_last \c - \p keys_first)) using \p compare.
///
/// If no compare function is specified, \c less is used.
///
/// Space complexity: \Omega(2n)
///
/// \see sort()
template<class KeyIterator, class ValueIterator, class Compare>
inline void sort_by_key(KeyIterator keys_first,
                        KeyIterator keys_last,
                        ValueIterator values_first,
                        Compare compare,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<KeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<ValueIterator>::value);
    ::boost::compute::detail::dispatch_sort_by_key(
        keys_first, keys_last, values_first, compare, queue
    );
}

/// \overload
template<class KeyIterator, class ValueIterator>
inline void sort_by_key(KeyIterator keys_first,
                        KeyIterator keys_last,
                        ValueIterator values_first,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<KeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<ValueIterator>::value);
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;

    ::boost::compute::sort_by_key(
        keys_first, keys_last, values_first, less<key_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SORT_BY_KEY_HPP

/* sort_by_key.hpp
GQt34Xq9jaX04HVjgPJbTp0Hya4+cx5qLFiBvqMUYzHvC89rvS2coYnqUZkg2FTV+zvzmyU2jbkkpJU7M1pgLBHgNWKJ+pabzxbL1XN3VvqGauvKOXhbOeel7wfKuT81WGMsNNyd/4m14qxtUS7bOEPbNM/uvcFO5VKSMfZJ5+30PSR2lOyY5sCdhZ9WXPeuKEO1uXdF30nnqDv/k28NXp9/0/xVps5/qA73rHxNvteo33+qrTXnJVs+i7vLnf8Zi7/Fa3t+YyHnW8hYuCb3QjH5fskZutNY1M1fOWNpbg/ebSwzK3WpaizpnuHCxiJnGKOectlD1lhxX3Pnf4rbzJ3/SYPK1OohY8Ek+9Zedm69x4ylu2tOZ9mdpqbdVVsprveU8rtG1l+1NXHnf2JVqcEQ5edyHqkeuc8QY5WLe26PG0tZ5c7/jAUOcA/OVIxyZHPEIlxvvph7ZlisORjHeX7NWOqDjLtS/WjF2t4yFhvAPf2+6rhO9rF8q3Pu1yuXplnANms2ljHuVmOJBe78T7rk5fztVc67OKfp6uUw1nZUcbfyenBK/f2Pdufku5575oL624F2P0k/99n+V/Woq/v+n3yfou/fihunpjdkt4f5Zc1vGrh6cxkL9mS9+YxluHPlgsZSF1DnorJbxB6VMha6zPxCxpLu3n2X2NdkVcRKue//GUv7g+vVNRapzpwbiSWoVXNj6b3o29JY+HPGfVB2Tpd20uoVrtdBtR0l6yRdXD+6yXcI6+hlLOUt7pl+Wq+fO/+T70hqGlNt7vsbI7Tes8xljPRzcSfIdyT7NsVYdFlRsBmKez9zmS2t3uR+e1kx3NnhK+rRctot01xN59yvkM6bef1701isEq9r7xnLvMEYH8nuCnu0zli8I69Nn0oX9+ydpjq+4bx8Kd/j1GqPct5Cu4NaL8B9dESaVmSMk2IR1va16thAu2+1nrvu/qh+1GAdl6Tp19TvinIeQN+/lPOr7Nu/qvd1xs1yu2nfk3Y5jQXcrN1mLKUX7YLGUsOc8SJiBTlDJY3F7mbcsrIbyJwrGgu69z33KG5FrlfDWGQpc6kju0c59w1l14HXq2bGkms4k/ep3uys9wHlV5/Xzrayy2AvHxXry9noKE37cm89qfyWMEbUWNxdn/sqvwWs7Wlj0ZlkzxoLuXdAw8WitHvOWIZ7bzVeufRgzpPFnKbTjZ2ZR+1fUr2LaDdPdaSzl4uk/UXGXar+tuXeet1YIp12q6X9cMZ4V7U9Q99UY5kLc4J9olnLzuvGJvXjIuv9XL7u89F2+Y7hnO42FnbPcAfEfuB16Cv1yO3pE9IlzPzOKpet7Pk3sttH3x/UjzrU9KI0eJ2+l1XHPl4P/hQ74c7/NAcJ7tVAAbNrT+1zGAu5713nNRZ90Z3/GUsUoKaFjaU5uxLGkh1ZRxnZHWB+FYzF7+H9t7KxWIKsurEU9wxSW7n0ZowGquNTxmiq9RYyv3uNBd3n0NZarzivEW2kVZL1RpSzW+8JY4E/eB3qaiy9Fe16SoNZ7Fsf+bq/3RyouIPIBhuLuDPLYcbCa5jfaGl/hjM+Trm4Z4ZJ0nQHc55m7MKL3PsvKkYVd/6n9c4zxkLp4up9Vbm0IUuKrWPOq9S3F3g/f0d23dnfD6XBIbK1yuVF9/0/9bw+Z+gzxZhEuy+k8/uMu0vruefY/epbEeZ8WOuVZo+Oy24TrxtnxHpyds8r7mX6fm8sw83VL+qR//tfze7bXO+qeuTuM9e13jjWe1N2fVhH9qDV68538xhL60W7243FzjPnO2TnfIsbS7hnqdLybUC78sYyhpNVkt0GzmQ1YwF3fakl35PMpb6xeFvaNTGWjNAuxVg=
*/