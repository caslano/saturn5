/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_discrete_interval
{ 
    typedef is_discrete_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_discrete_interval.hpp
Z/AbVZUdbNDTaPZO/i5REcDfs8hgFHG/sDyBuGPxbws1Tc9Lcq/02vCo4Znkp5kQ8c70zRsxWpst/rXTz613k1ybO/oDHU/Uo8qyWVTPTtR21j2AMxbcExu5pW4nhLYigCg8ik79OBRtzIJKws9C0KeFh1iE1Mc9zTIxSiYnpXaix7at/T1hO4FteLObOjVYfm3F6OGdbWKg34sTlqVaaaNOkFH0kK9GpERu3wR77zfuxXPR2d/j8L4/5LP+oaPj4+bZ8RF/n6fvi/R9mb6v0vd1+v6Svr8eH2Xin7+4QZjBzGnAmQ7V+u2bsTIVIUH8O8ve2jgcUkkOy9ZVkUpCOlzGSbqyFboaBZ1+qwiUuMqCuJPvl+KpbQQlfvxBnODnid9koiwqjubvb4Qz+ikmY6Fr6JI7jMDHDkO3EyvBy1Vap9JKghliHmhqkDAedGvWYjmourQkiSKFSVO+7JYKgHCk2c8mL4eJ4gTEULlJ3xI8nyLN4+5zVEJC90epm+lIxQ1GdvvbsICR5I95tYEK4bqnbsK5QumLjTQ09bxNGhg6dRukEH9OSxmaSeM/iWWwm/Ss0fwSp4A0GZN7hcUskH6IONdZks5PZ/NPTwS4y+3BqO0D+VKtJ9GXjgsBpVIWoWVtopnS+q4KhJWz
*/