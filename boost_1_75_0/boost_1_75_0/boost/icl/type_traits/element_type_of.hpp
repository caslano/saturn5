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
7mbP4up64Nedgzb+yekU37S4uVag+Wqg398qpTTSbziJylt9LvT03z6ntBZPtcddQ/GVtL8NjKZ4Q+3TsrfXYty+sXY5Ub/QyWsJ/4lanJ/LasC4W9TauJDNUqoK2px5eEfpIUagvZPiO6thB8/s4Hhtr8H8Wg97bu+poN9zm4netJjTi+fBhznNYaU3187jZd1aCb3jvjbQ3YeiqrhP7XA16vbeClLWmur6+hpSIxRfeQrKWbi0pmbJvOoWD2gUf5CuH82bQvCkE9fUA5dK+3zeDQTX0FLTVN1CuIFvn4557JlLCJ4hSTmAL54Lftf3wF8t8NdDjzn+eFYNat9FX0n5q+aj/m8MoCxNemkYrW0Wnrn4d3jm/BbjmaM1KP/tK/COJpUWleK3u6g9MI3hjXcjp3Cy47NcWqY2Vl/rzkLb/npzBzHiO3q6+4A7Ohd1+PtVrING2HiFrst5/xKOa8Shc1rfE4muytk2qYdMq/jtxNpYzv13dbRgULNnt2Avdc7v7tf6PaZx4PfXQGbOtpVAcCVdT/ThiXnQ6Vd8RtqLay5VRYwkcQLmzRlfMG/OprwDbuiLi6/tgWmlsufHz8b7eu8ICps98D6HG2P5FmEOOoPiT6Lf5Dz/tFZuYmpQ/Ib5GONbk1cShDa3FCAWUItyD/aycrMBAfze0RiPSSkEuYT0WPciMu4WEXsLtCOno2337gaND0eKLz8D
*/