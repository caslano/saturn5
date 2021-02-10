/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_DOMAIN_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_DOMAIN_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(domain_type)
    }

    template <class Type>
    struct has_domain_type 
      : mpl::bool_<detail::has_domain_type<Type>::value>
    {};


    template <class Type, bool has_domain_type> 
    struct get_domain_type;

    template <class Type>
    struct get_domain_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_domain_type<Type, true>
    {
        typedef typename Type::domain_type type;
    };

    template <class Type>
    struct domain_type_of
    {
        typedef typename 
            get_domain_type<Type, has_domain_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* domain_type_of.hpp
C3Z4JohKFzH0L+w1pKMtkpqh0iTJjknG0TWXKPIT/oXtJkjgkiUzJJx9yrV7x5sQkL2jmzhbcrarVEa4PaUPKuv6m9oH+jOeI9FuGTLBVbAT+u7QPd/doo5Z86sVSy5AVVvKstfaN3adiGTHeCT0FgmqSOQDETY0+P2AdJgGboWtPi+LEyX+OuPaoVBMJZ9HaERlrRk6Ut+3/1dHegz8f3EwlR1C9Heq5Ki6jdaMSh0aX0HN5x3OVXymyrxcsG73QRlEyBi1S/mBuBORLHMkDWLfcTBCIwwjmF5TfqNXajeKEGJ7W7+25N8Z2EHfd0ZItbuNwtg2rLBz4gztaGBfbu8d32sQMgd7zQj8POpbgR29GaK4HD/oRZWqj2vp6JxLoX9fyQ4IbrRyHYK1tlOJzw+vPkHTipL69ejTgU5MkKs+9XEXwCQnI3kUhD7KyvEaEeSrisjKpk5X2Hxeydfaf9mS4Oi4u9FwPjI4lTYOSE+3JOw12qLXdFh83zW2NTboAMfRooD2OAm5q82+Z8A3QI+jibxbEOdB0N95Gw3Cq5EdhRshkyzGBamCRKsTBFFg5NW2wmYrBz1XYcmet1zoeR1QDBdzdf69SktTtruDogm9W+EFPi76fXQ2u5ry3h7qzVYzdNhn7pKihxq6
*/