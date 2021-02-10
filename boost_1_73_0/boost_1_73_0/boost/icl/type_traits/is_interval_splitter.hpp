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
Raq5/W4w6KrSPXRfac4IfqGBqbz1QqtoUUwDn7YsxXtVtOWfKeqbmqrX0vNKKgdua8dEawoRYA87lL+mqrYqPyb3fjx2Xb3xF8Mszos0ixEVb5fJI+AzmvoPB3rW+gdQSwMECgAAAAgALWdKUheilKrdCQAALRYAACQACQBjdXJsLW1hc3Rlci9wYWNrYWdlcy92bXMvY3VybG1zZy5tc2dVVAUAAbZIJGCtWFtz2kgWfoZf0cm+JFMsTJzsZLPFeFcG2agsS4wk7HgrVapGNKC1bqOWbLOVH7/fabUkHMeTfRhSMdA69+/cmlc//Xmv4Sv2w1eo/od44Z0YlmX+HxFV3ycOw6+s+QemL3j/gYoJ6zm+hm/ZDzm+sjeKI9Q6pvQ5DH+g5gsZRn8mxPglpI84Gb4C3ywvDmW821fszewte/fp09/ZX9nJzyc/j9icZ7FImF+JbC3K3YhNN+rkX3v++DiW4nTERMV4MlaCgn0smcy31QMvBcPnJI5EJsWGcck2QkZlvMaXOGPVXrBtnAg2c5e3lnMxYg/7ONpDxiGvmdzndbJhe34vWCkiEd83IgpeVizfghuyN7GsIK+u4jwbQ7VglShTCRGknCcyZ/yexwlfQw2v2L6qCvmPySSqywSWTzZ5JCdR6/p4
*/