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
z/ckw3qasOpDEqhIvpfpGfo8Q/u6GPRCo1hWTiUPnRYHXYfi1lCx+s1olJvyWcZCZEcttOTjW9xaEiG9FVCRQVvcdpq7JKlujwcAH9Z+ixpqld+iBxYtWnjhrtq/9qfey5tzzgfz4iliqnSwNJ7/kXO516MnwlOoXOw7oO/3KwuGU2gY7aPZMMoee6NLHh1EM9MvMvwN7q586sTmby3PADiXi7764n2l8U99WEhoT+bXK/65
*/