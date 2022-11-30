/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TO_STRING_HPP_JOFA_080416
#define BOOST_ICL_TYPE_TO_STRING_HPP_JOFA_080416

#include <stdio.h>
#include <string>
#include <sstream>

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/mpl/if.hpp>

namespace boost{ namespace icl
{
    //--------------------------------------------------------------------------
    template<class Type>
    struct type_to_string
    {
        /** Convert the type to it's typestring */
        static std::string apply();
    };


    //--------------------------------------------------------------------------
    template<>inline std::string type_to_string<bool>::apply() { return "bool"; }
    template<>inline std::string type_to_string<char>::apply() { return "char"; }
    template<>inline std::string type_to_string<short>::apply(){ return "short"; }
    template<>inline std::string type_to_string<int>::apply()  { return "int"; }
    template<>inline std::string type_to_string<long>::apply() { return "long"; }
    template<>inline std::string type_to_string<long long>::apply(){ return "Long"; }

    template<>inline std::string type_to_string<unsigned char>::apply(){ return "char+"; }
    template<>inline std::string type_to_string<unsigned short>::apply(){ return "short+"; }
    template<>inline std::string type_to_string<unsigned int>::apply()  { return "int+"; }
    template<>inline std::string type_to_string<unsigned long>::apply() { return "long+"; }
    template<>inline std::string type_to_string<unsigned long long>::apply(){ return "Long+"; }

    template<>inline std::string type_to_string<float>::apply() { return "flt"; }
    template<>inline std::string type_to_string<double>::apply() { return "dbl"; }

    //-------------------------------------------------------------------------
    template<template<class> class Templ>
    struct unary_template_to_string
    {
        static std::string apply();
    };

    template <template<class>class Unary, class Type>
    struct type_to_string<Unary<Type> >
    {
        static std::string to_string()
        { 
            return unary_template_to_string<Unary>::apply()+"<"+type_to_string<Type>::apply()+">"; 
        }
    };

    // ---------------------------------------------------------------------------
    template<template<class,class>class Templ>
    struct binary_template_to_string
    {
        static std::string apply();
    };

    template <template<class Type1, class Type2>class Binary, class Type1, class Type2>
    struct type_to_string<Binary<Type1, Type2> >
    {
        static std::string apply()
        { 
            return binary_template_to_string<Binary>::apply()+
                "<"+type_to_string<Type1>::apply()+","+type_to_string<Type2>::apply()+">"; 
        }
    };

    // ---------------------------------------------------------------------------
    template<>
    struct type_to_string<std::string>
    {
        static std::string apply() { return "string"; }
    };

}} // namespace boost icl

#endif



/* type_to_string.hpp
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
*/