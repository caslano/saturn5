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
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
*/