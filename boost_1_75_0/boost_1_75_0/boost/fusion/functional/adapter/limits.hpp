/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_LIMITS_HPP_INCLUDED)
#   define BOOST_FUSION_FUNCTIONAL_ADAPTER_LIMITS_HPP_INCLUDED

#   include <boost/fusion/container/vector/detail/config.hpp>
#   if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#       include <boost/fusion/container/vector/detail/cpp03/limits.hpp>
#   endif

#   if !defined(BOOST_FUSION_UNFUSED_MAX_ARITY)
#       define BOOST_FUSION_UNFUSED_MAX_ARITY 6
#   elif !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) && \
         (BOOST_FUSION_UNFUSED_GENERIC_MAX_ARITY > FUSION_MAX_VECTOR_SIZE)
#       error "BOOST_FUSION_UNFUSED_GENERIC_MAX_ARITY > FUSION_MAX_VECTOR_SIZE"
#   endif
#   if !defined(BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY)
#       define BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY 6
#   elif !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) && \
         (BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY > FUSION_MAX_VECTOR_SIZE)
#       error "BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY > FUSION_MAX_VECTOR_SIZE"
#   endif

#endif


/* limits.hpp
ez1x7HGSUd+hGDXwaexDG4fi1jj0DXYi+mxkz/2QPa9hURgP7uJTgx7O3fJDhHTY82fPa0zsWT+cU3klrkX2vIbY89/Ans8J9ixYwHY48PT8mVrMxh3Zih2WXuOwrJfscE0Q3jzge3OVSvUq6bw5lXkz70nXMG/+G9jhOWCH6Fl4A7JDrInbXBOHuSaBjHn5d+aaLNRrYmbMvJWEbap8GVCTCtxCIxGkq5ogV54uWEbiWsmVp2MIZhlQ3TKLuLJXcuU85srTZaRm4MpwA/ni48T8vyVX/gW48rHkoqPsegMUtcAauNJLeapbGFHOYpZ3Y01MlD5APkrhkIiHznDXYx76shODrrom8ZM873x4kiq5KjJr8TzO26MJPC9BT4FdBPn3TWP42BOjNCGJIzj0Yob3rwYczTXOe0z+zPN+L3/Ger9qYDeJKEXPIe1vAYONjinFCZE643L4XNaryI4WZ+K59oGQ+7WwwcCjVcn6BFdc0t6h5p9aSOvz7CV+eKPPtag9q+MBfKNqqNjfi0JyAYs6NwpNfdbqg4B7Q1gYxI6Eu/9V+O5ahDgZF4y3btJ5a/nxGnjrsf6So/7Qn9jjwf5yg/B5fwp8e38qXSfx9c5U5Kg7vKOZCQ8ZRNdB4t67Y7dino/1R6bq6R+wj8uG+C9L1b4ik48zIb4QAYhIK7WxV+pWasgq4xPi1xGrrLAyYWM8dvFdBrPIDCTt
*/