//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/mismatch.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the range [\p first1, \p last1) and the range
/// beginning at \p first2 are equal.
///
/// Space complexity: \Omega(1)
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    return ::boost::compute::mismatch(first1,
                                      last1,
                                      first2,
                                      queue).first == last1;
}

/// \overload
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  InputIterator2 last2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    if(std::distance(first1, last1) != std::distance(first2, last2)){
        return false;
    }

    return ::boost::compute::equal(first1, last1, first2, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

/* equal.hpp
TzmyAS0+t/PFZgHMKlc8iXpqgC0UIiI01T23wHmkqe6qBYE0mznlqGSnvF1otYXcRqqBjKVFWmmRruvyybMgaPLUU4lXnDUHB8sP3LxjWu64TDK9jISrcv4O+tUffx3jvzLx1yH+6yb8VX0HacmLe5HNhS5PwWWXYsMq7/Mqnl5o1Tl/JxQu5oX5veia18vgX8rT09eb1vc106Z1SvX9bXbaTzDF5aFpFeO/FdMyNQ/n9O0w7efhMvX+OJC3N3jvsoKVg26FOXZgHPdtHJecmUNXCV6ggWye6MfwIhRxU0fXOM11E0zDFBHclZyv2m8qRqPDPH3gJI7gJowIb02m9tJcNMx/xw1+xEvqMF/PEh1mQywhUL/DnJqvOVl2MnaXbnp1MQ7rXSVJPJR3wYg2NpYsPgzwR2dZsKFynVLlglKZfG/gNqxufx4CnouIlYzhrS6ndGB6QixjFi3WeX6HpjNrb2LvPoDv7lIOd8J3rtLegc7SROssLnpH0pqB4CJQ5Rph3Vbtb88MhBg7L26PvMiUndpkveaMhmrWDLukqsBvzMKRynWmcZClDWZUcythkTt7mYkbtI7zuyTlR7yzvzePRsoi5creOFJOh5R0YPByosGL27FFmNo/Z9BIaY3Btx/W3lbuQosa5HU1mMuC3l7J396OyaTtkvb2u3dh2w+B8162CRvfUf/1Iv76Qnq9ifb6g/Q6wzyHjUb4
*/