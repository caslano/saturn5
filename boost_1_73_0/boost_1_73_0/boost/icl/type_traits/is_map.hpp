/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_MAP_HPP_JOFA_081107
#define BOOST_ICL_TYPE_TRAITS_IS_MAP_HPP_JOFA_081107

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_map
    {
        typedef is_map<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_map.hpp
v7CeXipYD3uG9PRmnpOUlPP5o0onhvX0UcFy7h3S05d5JimRHls/ZEhYTz/m+drR0zekZ2/mqdV66o5e1RTWsw/z/ODo2TukZ1/moQUhylfr9rO6hvXsp4Lls29Iz/7Mk62f16656JSwnv7Ms9rRs39IzwHMQ8sCVA+/mJ19ZFhPPvNsdvQcENIzQJnvgnualV8PDOsZGNIzIKRnEPNQ7kh6xIPNe4T1DGaeRkfPoJCeA5mnr9aztvPku8N6Dgo=
*/