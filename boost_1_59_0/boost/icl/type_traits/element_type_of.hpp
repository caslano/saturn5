/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ELEMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_ELEMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(key_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_element_type 
      : mpl::bool_<detail::has_element_type<Type>::value>
    {};

    template <class Type, bool has_element_type> 
    struct get_element_type;

    template <class Type>
    struct get_element_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_element_type<Type, true>
    {
        typedef typename Type::element_type type;
    };

    template <class Type>
    struct element_type_of
    {
        typedef typename 
            get_element_type<Type, has_element_type<Type>::value>::type type;
    };

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_value_type 
      : mpl::bool_<detail::has_value_type<Type>::value>
    {};

    template <class Type, bool has_value_type> 
    struct get_value_type;

    template <class Type>
    struct get_value_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_value_type<Type, true>
    {
        typedef typename Type::value_type type;
    };

    template <class Type>
    struct value_type_of
    {
        typedef typename 
            get_value_type<Type, has_value_type<Type>::value>::type type;
    };

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_key_type 
      : mpl::bool_<detail::has_key_type<Type>::value>
    {};

    template <class Type, bool has_key_type> 
    struct get_key_type;

    template <class Type>
    struct get_key_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_key_type<Type, true>
    {
        typedef typename Type::key_type type;
    };

    template <class Type>
    struct key_type_of
    {
        typedef typename 
            get_key_type<Type, has_key_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* element_type_of.hpp
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
*/