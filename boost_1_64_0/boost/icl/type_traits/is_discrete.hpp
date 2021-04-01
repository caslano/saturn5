/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_HPP_JOFA_100410
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_HPP_JOFA_100410

#include <string>
#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4913) // user defined binary operator ',' exists but no overload could convert all operands, default built-in binary operator ',' used
#endif                        

#include <boost/detail/is_incrementable.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/icl/type_traits/rep_type_of.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_discrete
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, 
            value = 
                (mpl::and_
                 < 
                     boost::detail::is_incrementable<Type>
                   , mpl::or_
                     < 
                         mpl::and_
                         <
                             mpl::not_<has_rep_type<Type> >
                           , is_non_floating_point<Type>
                         >
                       , mpl::and_
                         <
                             has_rep_type<Type>
                           , is_discrete<typename rep_type_of<Type>::type>
                         >
                     >
                 >::value
                )
            );
    };

}} // namespace boost icl

#endif



/* is_discrete.hpp
ZRqSQ6vlJlOKaV7hd2WQZQwO6SHM1q7pRJKSpDCkqfyjQA2Tc3PTGmSSN3k/1yKUiuWVzx7hoFmvR7k8OYA0mapPLxxiGUTD7y5w2bJsglSgNzh56GbvZoULaBx6PaaU8DsccGTlwRDvgRkWip06yjkHf8aU1mbZeP7R65O+IUU0DiOSt2qpz81zbofi2e0icoqPY+HSykzKhihRZcMnCA8ewe2zljgUGrHfUwwXz39gw+B6X6/UthlaHPJpXf3U9nUV+nk8MAwoa1Q+e9mA5edQJni42FMqhDcgbywFFfGfcgwxubdw3t/INeHtbSS0vq77K+fTmfX7XxXZTXtnSv7M0k0SWMnI8Z+Hc83pegU6YJSUaH6qRY4tlnzhAYAvDLNyC2ymEd3lp1lkqrjemiCFxz+aI2BbeftJEswoegJtf1jpu9MhmmoagcFKsFmCeLy3nG4gnOV/mncYChbyJnkI8GDQRkqahRkceaaHdAxGNKnrIOSP65R0fHu0xwU+yKRFHXJUVJhIfYBVJfcn9xsvnOlidQGLwBqVoLQvfImJTb0gn1ijpav8WQ==
*/