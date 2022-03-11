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