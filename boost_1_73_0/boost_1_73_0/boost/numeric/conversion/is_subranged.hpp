//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/is_subranged.hpp"

namespace boost { namespace numeric {

template<class T, class S>
struct is_subranged
  : convdetail::get_is_subranged<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                  ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                >::type {} ;

} } // namespace boost::numeric

#endif



/* is_subranged.hpp
dyw5x7wP/+8NdmZwi32OJcCR2EZIq5ZKDZhF+BSM0M6n0xVbvWRj8yReqrEjpHXdrqQcz/Ly5zXQbTn7/KjlbkIHw+u6GXgo8FYgL+8220HdDpwH/DKQSwB3ATuAdwM58f9GYGL17Xao4+zUlDOlMuvJcs84Li5nrgqOyZQzX8zeYHF3ppzj4t0gfR4o3gHS308t87HGizTmzB3fkiWas0RThhg3OUu0ZolsGq1Zk9ZJWWJClhifJcZliWy2rdk=
*/