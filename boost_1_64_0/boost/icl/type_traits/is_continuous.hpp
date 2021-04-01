/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910
#define BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910

#include <string>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_continuous
    {
        typedef is_continuous type;
        BOOST_STATIC_CONSTANT(bool, 
            value = mpl::not_<is_discrete<Type> >::value);
    };

}} // namespace boost icl

#endif



/* is_continuous.hpp
xG+LSE5dI10MTxK163E5E5TLZj3/8CN2y+IRV0OgPirBqJIuAJSfVadDJjETCs1QKVbT5BXt6+jcb9hMfb6QPGCvNMEK08wW5qLZTnri3YLProQCxxqWMZQEJev/ppqItARuAm2nbYSBhvbKSr7dWtu53qY18UKoRRgDF2Ir2jh2FyofB1i/4kLu3JA4OZzZVZu+/1K34s3M14Gfg+qbKWiky0ONLgKIFQPNaGNVYQrRHTO8DErktxIfe99x6YLyHtZ7b0K8fxqMHZiNj2ECrynjxJtr396W+/8L+iJ+3l+Bilvh846/Zu8T8b97m1HkvIoGnNSgki74L347TMqVTG2PTgYZTAb2nXNNCP6arxYaYv1do/FJ2DOfJd3VR+BlzR3MV0tjE9eg5tPDL2GCjg+xn+fu4mLd2e5qIHtnHtePUeatZBhYxu1almYtdb+y445Sf57RYQKdoqEut/G3eaAp+d46Yw7RW2+13CBBvPc2f6ov18pdOb6I31G/kL8QjcMwcbCls5/jMUUieQwNwh0ivf0ocvGCammMW6VzgfAHlkK9LAspATTdmw==
*/