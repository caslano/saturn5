//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/replace.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies the value in the range [\p first, \p last) to the range
/// beginning at \p result while replacing each instance of \p old_value
/// with \p new_value.
///
/// Space complexity: \Omega(1)
///
/// \see replace()
template<class InputIterator, class OutputIterator, class T>
inline OutputIterator
replace_copy(InputIterator first,
             InputIterator last,
             OutputIterator result,
             const T &old_value,
             const T &new_value,
             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    difference_type count = std::distance(first, last);
    if(count == 0){
        return result;
    }

    // copy data to result
    ::boost::compute::copy(first, last, result, queue);

    // replace in result
    ::boost::compute::replace(result,
                              result + count,
                              old_value,
                              new_value,
                              queue);

    // return iterator to the end of result
    return result + count;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP

/* replace_copy.hpp
qJS3kdML8Xu60UxqCOmvKS/dgNfZ4DUcy3b0M6ZeCStGl6If37IYcJwlFsSlORDqo2umyGjHK/zbf6+3NsKuIFadGAZv1SEgfdH9dFTVQv9FCmuOzsAwUGk7Kbu8CZZ7DNNwlG/2DejkAzZ7AmrJdevV9EQh2bX8hcMMT2cVjMATZI/LfwPaKYTIlOxKYABF1pyxdbx3GBSwkbTWaK16myK8e/JL8iT7hvydXCV1YqyPKRKMgfK7reDa7tjuI+Cx4Z+z+e4p9a5H5ONAlmG5d5HVnzQmyj42Oh7u+ANeXORH0JT38yf5vduE/rhlMdWHqoUggCnhdlFe+YhI4flDSV7mfVGh3USqh6P5f0OFT9lQWquI3p9Kwn8RYHWY5wquwgGxb08fHZiDgsckfcjw8IVKDQSARYhAXFWt6XftgP1PqglsLgAIStEzJlhF5hltOa/5lgfC3qFeMnzz67oYsuKLxwMFWCj1P3Cvl8nY0VN9K0JOasDPbmcrmHkSvmfndAvlVw+9KmUkWSpX1AHsWBTxHRQkSWJLS9iGmBAgbK8qUyrqAlr4/CDXzQ==
*/