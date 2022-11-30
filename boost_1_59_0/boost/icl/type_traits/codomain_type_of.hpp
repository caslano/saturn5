/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_CODOMAIN_TYPE_OF_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_CODOMAIN_TYPE_OF_HPP_JOFA_100829

#include <set>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(codomain_type)
    }

    template <class Type>
    struct has_codomain_type 
      : mpl::bool_<detail::has_codomain_type<Type>::value>
    {};

    template <class Type, bool has_codomain_type, bool is_std_set> 
    struct get_codomain_type;

    template <class Type>
    struct get_codomain_type<Type, false, false>
    {
        typedef no_type type;
    };

    template <class Type, bool is_std_set>
    struct get_codomain_type<Type, true, is_std_set>
    {
        typedef typename Type::codomain_type type;
    };

    template <class Type>
    struct get_codomain_type<Type, false, true>
    {
        typedef typename Type::value_type type;
    };

    template <class Type>
    struct codomain_type_of
    {
        typedef typename 
            get_codomain_type< Type
                             , has_codomain_type<Type>::value
                             , is_std_set<Type>::value
                             >::type type;
    };

}} // namespace boost icl

#endif



/* codomain_type_of.hpp
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
*/