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
k5NTEuSETIg26M0szkkx56RYt0LFFT2CjVUxNVaH6sRRi/WK4Z3pazjbu1GfmiDqKYi66RTn/ejmobK1XRtokoGO7xVlL9jL/065pGsa+HH2AuroIV6pVJjJKelaucZvg/aVylmfxFmfVCePkKNJ2UsXh9XgpU1q6aVB7c2idqpVO5XVTtWlNLVin2CJTqUSHSKS3B/RljW92+fw+VaqymhzctPZO3bskL92Wh/SvWWVYJtLRjPafJimSjRK5CQ=
*/