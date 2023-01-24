/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_INTERVAL_HPP_JOFA_100331
#define BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_INTERVAL_HPP_JOFA_100331

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_continuous_interval
{ 
    typedef is_continuous_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_continuous_interval.hpp
PbjTpgqRwWH6d5gPgGGK00DAIgK4ixE/IHTnbgKfATLqorIROXSbsZ0zVptN0dj8wM3DNXlSpADulnwiVBtnM3RIWpXv4KC3K2TT7Dn7j2VE9uNxeX9NB+cdEG1U6ckMfU35dFlZVwRwB1NxSAAfkRtFSFQOetItzx0qr1xZxetBizBaWZ+SVumrHa5+pY7R3kStXKLaGuLQ7NBIC6/Cb3RIDj7uunBEVaM/Tu5v/11PU+soRLADny8dhhypbL3sIzw4AqbS0X0rCwWGs8e2Y7IUf3OzrHS9Df+Xk8eXCi0yy5Z/BC3ZO1BotmOUwCMq5zRh3taPjQ5O/DkMQrwb2VFqjhSng5UJ0OaffAfXkrUHoXIriEDydRrkOEKc3h47TFgOm1u5hyqkh3rTCun2I1DCMmIq4FjTmm7quB8bwb0jt1XTg1DL4IW+pSdQ/7ZOFq/FxLW8B2h1xKsJkhN+EHBhzP3+iweSySdLYHQ87wtAvMUG9rPSIMkE3AF4JfIo+IgpGXZ5lAoVkdLe0ik6mUWrC0pYQgTimPH0pyaRZvCLptQzQaM6Yxdk6bzZhBWsEIi8w384cTLXDkQ7ukmbjl9GCByRIce2PP7QZYt+xECZCUL7zckaGWiFUGiXCu0zq0p+7gpPKdMgY3Eas09TxpYwhT1DbyJ/HQBl6OQBr0R2tcgdflDAevMqQbsTA32t7aCQQIYeF7DadqSP
*/