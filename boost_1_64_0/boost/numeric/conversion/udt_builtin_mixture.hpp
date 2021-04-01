//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/udt_builtin_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct udt_builtin_mixture
  : convdetail::get_udt_builtin_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                         ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                       >::type {} ;

} } // namespace boost::numeric

#endif



/* udt_builtin_mixture.hpp
EleBB8XCeWGYNewIzX1JHw6d/tyguWNTwN49rgWrjwCGWMN3/FEzVAmFx0FoDly4Q//E1A2bsWIIqdsciFNYEohQJl3sPV4um4bXtHWIsnXzo/KuPAlTn7owHYxPM7QnjDomA4NRjpbimLqXnbx/0Znfy3Bl8glOoRQYmyZkS6uuEumWnf1r0DsTffpLRivtSo/f9jxJEeEJDELQhzIlS4sQvUT/xrk1I1lPWG2YRL1kCpuJWEMwxXiyrqnetjrTzOtIKzpJkhKbXpt/EK3by/GZ5DLhHCCdYsu6RNmhfDS7BWwscrbcF0LqoZ2u+3WnlXYbgat5pdhcheiDvuUaScULdMqB1+S3ff2H2YUcGxtMLvaB13GeDiN7j+Dh3XgGYxya19Fwf9aGoyhDCESWgbWY8yMrX7tu/QQk2RNSgBDjUPW3/Ci982ijjLQJqiYNn4tcFO7Utb0SPXXvG0hXAEt4+aKb6kFWvOvrZyJN5GHpB6eSuuhiW6X/TAhIPYpY7BU7k60TrPmWMLWCJAq8eCOucKNIWmdrdwXclyOZCHZ4OD+vaPLOGCy3bQ==
*/