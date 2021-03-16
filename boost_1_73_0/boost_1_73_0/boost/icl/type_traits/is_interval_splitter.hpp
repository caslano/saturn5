/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SPLITTER_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SPLITTER_HPP_JOFA_081004

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_splitter
    { 
        typedef is_interval_splitter<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_splitter.hpp
ZMcOiq7w3LLxlf3z8+sjKi6U/hNnlpVWziqjZFKrH4s4b1b/+k8sm1B1Xq+TOVvMs/zAFnhGUzjGPNVBFtV/JvsR4l8S8zj9jPNLchAprCyrruw1jTZqVDJLmcHfHsfOXSkpclOYwjzbHD3JLOfqSWWeE5WkdeA7/9kW1pPGPFsdPakhPenM01o/P+aXM2vCejKYZ5WjJz2kJ5N5aJhC6Vl/3HWnh/VkMc/njp7MkJ5WypQP6Wkz9I2vw3paM88=
*/