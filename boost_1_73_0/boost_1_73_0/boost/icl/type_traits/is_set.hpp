/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004

#include <boost/config.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_set
    { 
        typedef is_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = is_std_set<Type>::value); 
    };

}} // namespace boost icl

#endif



/* is_set.hpp
HcshiV+O7xPWcyzz3ByRHlqkgnqOYx4z/jmo69fzw3pGMk+ak6/jQnq4BYvQshWNqIadckGPsJ7jmWeTU86jQnpOYB5aMMtB6P0r330grKeEeUqi0tOLVFAP98gRWrCiEcM+Nw4aHdZzEvOscsrnxJCek5mHFgnbINTlgrMSpGc084yLeek5OaTnFOahpUN6p72OXflsWM+pzEMLXOb7OSWk5zTmOUQ/7/DPmWnh72IM82xU3vs6LaTndOb5l34=
*/