/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205
#define BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205

#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost{ namespace icl
{

    template <class Type> struct has_inverse
    { 
        typedef has_inverse<Type> type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (   boost::is_signed<Type>::value 
                     || is_floating_point<Type>::value ) ); 
    };

}} // namespace boost icl

#endif // BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205



/* has_inverse.hpp
uSLSjXdj6K99SnGJki14/Hm1w5c5J5excDWAcghXIl/whDYqg2xONXrlrVJ1N6O4hxeav/PtwdaD8cF5LffYUHr26c5vF8XC2X6gwJE6Ef9MxBUrOW5fsxak3UwSithgYiqojm6ajP8Ix3c+ixbCK7JdHTJVBwvI/xRIaKWcanO9gt59yR3PxezwMD8fGLCREyv1tQUtsmArlPgQADEIt2W2zbIRU5qja05lMTuvzW6Qv9mjN9WGmFtJ+6uBytHbLd9YULDQEIKV9aKkbXDq18War9bgfuEn7oZOj/89cw3xLBWTdcMPOAUih4fPq6NlcVbFPHLxdApzyyVuzUcSGAPtobQ8KAj6KbayCnnhv04G8R0WxjFLM6dUElf2EcevDwkK656krxV7IZfSZo1if/NjeVWsRs+u4fbLXbp+i5cJttK8Uv6Mi+WguROnMtgzT0hCX99TYb9gLW3beBIaRGkTSkWfrPJm7DBusrkEe6CTyhWOrTgc1AJG4EIP7S5fzULLQK7DIMRPWWU/VB/I2cJXTROkygj+V/AhJnaAR8l4iNaZ1mrPhVHmZA==
*/