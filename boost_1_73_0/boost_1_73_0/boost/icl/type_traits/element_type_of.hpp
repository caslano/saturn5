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
PNa3VXiFuhZQSOlaTNHSoLx40k8LRdn4g7blJ5ztm49H32jNfNWyGIaVo35VoX1W3FI3bCI5Qe9P4j0WxYB7QhS3d3QNMIGbqoqnCsfxOiia5SRSZsApVBijDyPtRqEqcg9HZoPdxOd9sEbcNcBWdJpM2ERol/69TtyCO74Pbz1SGqC9e7EeDIKN8A+FQksF95+lE5GrGI/F+yr8g/KvAz8kfGOedsY0UlRdxxrgg5mzS1Bnz0oPnSzaAqwzqXsxHK6JtjGVtjbX06kJDZOfTENBtJGSugbGQktjPaaBOvW7Ffl1yCH0tygrBdLM9tSwhsYLJ+ZSri76JichTWztA5hLUY0ldDjrC3F1kd9S14VW92pyhmqdqU2sWkZDY63B7HXSQCdhNDlnV0NWxv1qOt7/nlfTmLaSkmpfKwuqNvj1Pf3xrvHwuhpo8J/Z0V6dke9vlFWTfNQ9hu6N7zmI2KWVtqjtfkOda4nbXyRmPMsiku3Dq++++9S0J0vBIw1RTeNes5er5bBp0Ha3T93LnQvXeR8FZ/ZwuN1rytnKzwrfHmrJLxw+tbLOXrysghHa+ssjxbMmvkHso05VO6TLOKFXA+xkxpPPWBvq8ahUM/E7uutWBXaTg2xTCOwAK9LUov6Z3X+73TNXqMrS
*/