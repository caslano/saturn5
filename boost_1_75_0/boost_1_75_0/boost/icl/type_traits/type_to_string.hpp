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
w96PhLjQ+5E+aCFaRN0VLYATFjzx/Qfop2qvfZjnhA1ba5wIxyX4QBnZXM/AvP0yr7H/oIXWpDgv38e+W0xFSR7Zpur9EWjk81ZqRz88/Aq+XwFcrVWxiDEO8dtqzkeawPUv5CvfQOpUdsJZSB8sCsWXs9eyPlL7/GNrWeb+6s+2kb/CsWHur/g+ma+dvKdaKDbdJKRuuNcP6eIw5eV1E/c8CXefUKUH+Dng4fdZ/XFY96i8va9S3hqUMw/pC3h37at2vWadsfMkQvHLet0YxTtt+mkR+gyLK7/RdeJaUMqPAGOm3VhWzI8A836/LOVDosfbXs/PIs6v9q4o7kfgn8cd9yPwz+OO+xF80u7iPu5HgHnNcwf+78WUflDp/1Hp/1UJY0Zh4nU89gOVHbbUpo/Qeh7HEQj5SH/TF/fJ/q4vHq/yxz7ff5r3U3Q96u+14P0U3Y9Sl7lz+Hu/BfqAdBXSdUg//pba5e5tQF+on6tPk+/THPdp8n2a4+vdvg9MfL3b9YFZKF/plP/qx4+6skzcfxXzmrLMP1xC6R9B+scqfajSP1Hpv1Hpv1UpeNaS8sFmXx72xb74p5Sor8v7+f1caRv3f7e1FqNtzItGliK0/d5uF944bWPeorTtz09x2vbnpzht+/6Fcdp2/Qv/1yWUMD7Jv1bp36j0b1X6UqV/p1KIti+9QekjlXjeacSHNbSHh+eg/t3xOWhg
*/