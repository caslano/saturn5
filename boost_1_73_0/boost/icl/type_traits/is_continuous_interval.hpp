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
aUcjlyArto80ya7Aug0MLI2mFWhU47ujqlWojinZr6TsqUFFZDHcPf3cFLL4imJxFdWBdRX3aRZ/8rluWYamKBb1jkYusmJfS1PrCjS7f9Ey09Y2dUf1iwBRHdO5LvZAxUAb1QcMqnd3R/WhRFTDPVAx0Eb1rEHV/tluqCZrVKoG91DlKZO9RuUPdc+SFUiowaEeNchAuwbvMP3qiu6ojvhVDepcQ7xQDXGjutOgGtENFefG
*/