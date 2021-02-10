//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) for which \p predicate returns \c false.
///
/// Space complexity: \Omega(1)
///
/// \see find_if()
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_not(InputIterator first,
                                 InputIterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(
               first,
               last,
               not1(predicate),
               queue
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

/* find_if_not.hpp
n+jQf3g0mQ5DvtpPdLTj9LfwYjaOcPh8xyH0cPJil1p0Nprh7OWOs+lkPDivPb7yqf8MDIFySWKuvGf9h/KfJuNfa/HXO6xFJ+8HYTjk4x92HQ/xYDhDxUbTyTmH9GaH1OCP+pJHh08J6MPx8LSR3wXZh2E0GI/CMz7fhdrxsL3+0YtONrfJRO30WKcpwIc1uXe/VnqoFt/pfX3kdaupR1xPT9K6V2/cwb2aXKm3/xbtk0lX/afD6OR8NJ2NJqHnCCarVMIczY4zuazACkzFZaWsXIma+x/rK6/pq4DumQI1aYXWXgiWdTqm7lCcdI1plTT8Kq23qnBzqCRxUUDpKjteiEyX4iqb4suoC7JU0u692MdJ4Hk8XFqD7BomZCoQfwZao8XG8SwMyBTy3p4IlgEb391kENmv51XXpJtVsGvWIqnNXsuY7Xqwy0niGDH/8AnsToiaYigCJ4khq4y0GJIYVRZg7q1jY6Ra0sERT802MHgdZd5Cg67aRw6YjgOeA7cR+O212tMbWRTu7ksF0MDn3igj1fD9rUmc4cv0KyZv0+gMZlxCLtkNXtFwNr8Iz8LJp3DeYOfi5D5oInJ15xDRUjEeyD9jFV6Mxwc8/aRynYuR7BaG7RLQYG7qDDx87uK1uTbCs3ls61WD
*/