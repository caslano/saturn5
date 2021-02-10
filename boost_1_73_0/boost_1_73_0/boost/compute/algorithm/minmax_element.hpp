//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP

#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/max_element.hpp>
#include <boost/compute/algorithm/min_element.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators with the first pointing to the minimum
/// element and the second pointing to the maximum element in the range
/// [\p first, \p last).
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element(), min_element()
template<class InputIterator, class Compare>
inline std::pair<InputIterator, InputIterator>
minmax_element(InputIterator first,
               InputIterator last,
               Compare compare,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        // empty range
        return std::make_pair(first, first);
    }

    return std::make_pair(min_element(first, last, compare, queue),
                          max_element(first, last, compare, queue));
}

///\overload
template<class InputIterator>
inline std::pair<InputIterator, InputIterator>
minmax_element(InputIterator first,
               InputIterator last,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        // empty range
        return std::make_pair(first, first);
    }

    return std::make_pair(min_element(first, last, queue),
                          max_element(first, last, queue));
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP

/* minmax_element.hpp
fm5ZFgz7XpG34UKhkRUTe0tU16N8FoqTEjnlrQF3u3VnRGMLcIPZgXgOm2rWSS2ahhlD/atK31DZroKFr/KKuegsDXK6QVvSrUMLZ+d1iwLWoNBsEhq6iFuWhAi5Gp9bZdhHiYGxD+6TxBCAIAReDfYwIg/V2UnLSh3u5WTVf77ijXZMI5TjNQc8yxAOztB5IAROnV2iHgeW0WHeYUckYHSNUcqNNFRnrdbyMGgBEwJB/DEBLy18mUCuUM0WH+slulEozVLeYQQBsrJtPlku5Ol8fu7HkJH87sMANzQ8S7lis6BmkN9pb3fQbhgZuPHqeYmhgUw4KO5b6fW4DAuVsEEgkS8zA/QTAV0p/ZAOR+nb4Wg4v2TNV5pjWZ7XlWQzr7zCQ4xpdgag4IKxcWSIC8M9TyiFJv37Rejuwfd0ML+YjulDOroYRNxeB4vJezYXxHcEJnDje267xsgr8LIADhMKe6eD9GQxmE4nUw7ls8PpVU2uMsHvHfdFwoXeIG0uJwN7yQXtDlF35NGqtOefZce9DOWLCVN356jmoQWLWuTy1tVWMr6o0nQ1jkDRBq9KTR4A4Al21VtyB/+kZ+ejQZQ0RbQbK3TE36/2VsJU4e9XUUR9vKogLL/DBHV1/o/6Ubj/c29EAYY7YBSH
*/