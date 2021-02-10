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
GvJh6jdDA9JxT8e5Fk1wLRsAJ46a0GGabThI1Jq4iAcQWIQW0Ji6REraR30AL8SFboMiRhohvt62RiUS3n08/9WPzjEMXvza3XH+n/+qP4qYFoaQIf10vsI0kWFAQaKfp/EqoRwy55goZXhAmlv6GCQZT3xMVZDi15APfZW2+5h6ZdoVM/aEQQXeHXGAW8YppZyI/QSSArmM/cxanRb7gSUX8I96fV++/li+fpCvm3n0gO//KkE+lq//Ll9/KibKtCFjl4HAIFEAS1SxzlGuFMskhOzBQLQMFgnFpiehf2azNp+K/Ay/dVhraN1BWGiO3npN2CUorMIICM95viBQOQraOJu1QZXZWpy1BnfeyOrrw9Zr1g3zLrt49/4DwIGeo5dtxkC8YOFh1kQV3WqfgX8eZnx/rLX3qXz/oWC4pKtBHHumNgKeQYLJuGAfcCCD5dwu/yPrAvrXmOCibZoT8xPyAyXDrPDYKM6yEMbe4esikT8uXraLV/gOi4iYRpv3LFu8LyaEUz8p3v8LY8X7A0/B6+NM/pbVhUih2AkWPHggi2GKnjHHGWKmhmTv34d8ioF03uwPGQbMFQfgy2etDgnSaXVYaXhloo15SSGFwBeEoAs5vSu/FUYkbhl8aL8Bb5uLAJZttuR+lLHB
*/