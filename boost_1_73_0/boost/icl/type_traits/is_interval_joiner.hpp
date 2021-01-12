/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_joiner
    { 
        typedef is_interval_joiner<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_joiner.hpp
iZPMyw2eibiNzgJASmySRey47iw7noHKDHz3qyxv2YEkLCAHJ15LgvfNBsvFYVBeUUa3vsHy+FhVLrRzMXZBFmMW1i79UXlX34VjM+Wt39fAH/R5cWxioHU635nIwcRuiaXlB3WvEJeSsoUQf61cj35t2L4FsoAgQ09tI3scyCQ2NikgrOBNgNvYIctxLQ+i1uyg2kltk3a8Cq+cBc7/hNInz/Eale+vktdL83Coywd3hgBA
*/