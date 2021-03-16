/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_INTERVAL_HPP_JOFA_100327

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_discrete_interval
{ 
    typedef is_discrete_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_discrete_interval.hpp
wHSkITlDDnSmAPsAU4EFwLQMufkhPUNufsgA0rvKBJJ1YhaQTmq1ypCbIFoDyWY8G/gAMAdIa0m5GXLQMw/4NrANcDOwLZDW0dpRh0DvNUMcfe6RIZe0dwHmALsCewHxbcTPAnbPEDfNGN3F5wB7UnqAvTKkB6IL3aUHopAcnLw5ag5O3sy0zZbvA8vX0oUC4uXKOZvTw3pAtqRs7y80wrN4yXxKVrDxpVJzWoqj+BxicfLGKDFy87OpeKlzHIY=
*/