/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct is_total
    { 
        typedef is_total<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_total.hpp
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
*/