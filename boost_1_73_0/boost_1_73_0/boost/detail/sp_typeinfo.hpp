#ifndef BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED
#define BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/sp_typeinfo.hpp
//
//  Deprecated, please use boost/core/typeinfo.hpp
//
//  Copyright 2007 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/core/typeinfo.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED( "<boost/core/typeinfo.hpp>" )

namespace boost
{

namespace detail
{

typedef boost::core::typeinfo sp_typeinfo;

} // namespace detail

} // namespace boost

#define BOOST_SP_TYPEID(T) BOOST_CORE_TYPEID(T)

#endif  // #ifndef BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

/* sp_typeinfo.hpp
Cz1/tt2RmTPjVtYoKgQim56dM+lW1IuzyK2oh/6xVuE1+x77Oy9dPjVxRkZuY9m9dxXGBzfb5j4xA0Sbp2G+6Y4/WI19cvrMrMxUiFXScyF+uNna6nQkatsb7RF5+q+xUvqFxTfT51kzZ95oERFkXG8hMTVOT89NxdMNjRXyvEI64/rq1xtViFHDrOw5jW3Cu9zEnEa7Nytthr2xPPVYx37DewL/wY2Wybjpge45NG8ZmcmHPd9sTXV9D/KKRyk=
*/