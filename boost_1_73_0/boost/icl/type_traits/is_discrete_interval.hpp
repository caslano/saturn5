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
zaw2NYHe+wFMoFd/jhNodX0j43Nm70r8VO1HvHnX8TeAT2r414CPa/gk4PdePU48rOGfb+H7oz7v+Z/FZ9Jdqxu6K8O2REB8pmT79Yp+6EEEXy9fVZfWYUsjiysQezlxm0YUQE68tz7VzoJVhF8SXMtMElw/I8DidM48OLLpYu76inQ/gJiFi1xdWLJvnA9exh70nE/TJTduDGErPQw6U0oAl/kznmdSE496DSdsaQStQ005
*/