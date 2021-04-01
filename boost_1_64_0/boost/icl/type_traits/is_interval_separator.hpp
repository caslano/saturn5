/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SEPARATOR_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SEPARATOR_HPP_JOFA_081004

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_separator
    { 
        typedef is_interval_separator<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_separator.hpp
dUeAaGGTnhbDa01ZO8dQ/U3nOGGEYcBfNEr4mxHeitO+r1kc7hKAR1LZlP4x36kHQYamY3T6G4n+9Z+/enW+R6jJVXsuJCwvdgut26DmhqtbGHxGI53CBX1L+h5+ofLec/2oIGVSQrAaNFhuURvAtXaHMBXzyw4tzC6Y2/TLP2XBlz7RAgJECzBnvFUuqJZuVvNsnpsTfAhr4O0cJi/+0OsTgbqrsblDpszUPP0OXIjxgvBbYYCeSR1NBsMxNHeIkmvlJgwb1ArSmsM4bwUZRm3ivar/JhbpjiZk5OFRHIfGAT8DSGHGXIdi3h44pTCb32knyL4TgLgcAmULqybiBq2YY6cahAzWi7N/GNBTwcIkRZct7UR1s6uMf6DT2xdbn03lkAGSEQq2EIjTmvJ+v4qdaZrS7LsqoB1U+OGG/AZbiQUvOTKziF8bDIxkb3+ypA+FDuG+0dXS8qY1F7Y7x20cRW/3SPcoBj8gZLbWbImmO2nRAiOYhIFZbIUfiVyRT5GYKtcbbg5y92slxkLkxyIkmlqebS7uMZXQJun3IgohccFi0tG/rTagIg==
*/