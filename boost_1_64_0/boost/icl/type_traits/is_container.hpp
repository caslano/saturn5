/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828
#define BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/element_type_of.hpp> 
#include <boost/icl/type_traits/segment_type_of.hpp> 
#include <boost/icl/type_traits/size_type_of.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
    }

    template <class Type>
    struct is_container 
      : mpl::bool_<
            detail::has_value_type<Type>::value &&
            detail::has_iterator<Type>::value &&
            detail::has_size_type<Type>::value &&
            detail::has_reference<Type>::value>
    {};

    template <class Type>
    struct is_std_set
    {
        typedef is_std_set type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::and_< is_container<Type> 
                              , detail::has_key_type<Type>
                              , boost::is_same< typename key_type_of<Type>::type
                                              , typename value_type_of<Type>::type >
                              , mpl::not_<detail::has_segment_type<Type> >
                              >::value )
        ); 
    };

}} // namespace boost icl

#endif



/* is_container.hpp
8nmAvp1j0QqO4IG1PI7DvwgPj+gmhpvSoXspV7NA80gHkP8g4wyPDoqPKkAI0efEO0MQZ8B7kmDqP7f9ORG7j0KqlV5fRIQVoAQHCC9T6brJq+0GUl3i48kS8sTv+JbUBoXMKmZhOAN/afhBF4DzQQVN5fmTcFNJ0xD+F5rKsN5DSHIpUQ4/Xp+8cOFJD6WKI87IepRyDIiizaTMTAMEhHppJ9zKtqSFMHT4OCY2DLc7fTsGs19NAPh3P8YMwg+V8pKyCAqp7vtJTQyJDH2UvcixGsPS9X9B0+6UC8XBOjZr8VSYj5w8A333foxZMqybJhi2llb4fKgN8sjUQRSVioD+R/gvjUbz4EcMuQH8VYLm3dm81SVY0IWsmJ7U4hAcohs6EAMtmzvyinzycPfX1uj++WF+Ad99datkc5xeeWnxtNyxrAHU23yn+EJRE2qLRr1C8gag45WhEF4oF4ojY2kG6oAZq25bTvOA7I4K2wbVQTNi1ihNVlH/efhdXo8HyF2Y6Inq++G8kp8rC8FHWi/RdIShHALLyE+iNvuhOE+yZP2Tamr0UilA/Q==
*/