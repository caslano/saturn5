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
/uStf98TTs8ZIT2nh/ScyTw0FSbphvhp74T1nMU8bn96ZkjP2cxD3wTl5pxvur0Qztc5zLPC0XN2SM/Y3dAzjnlWOnrGhvSMZ54OWs+Odkc+FtYzgXmWOXrGh/SUql2nZ6IK5qs0pKeMeUx/MXnWa4eG9ZzLPG5/URbSw196ZG+tp8fTX/UJ65kU0nNeSM9ktet8na+C+Zoc0jNF7To9U1UwPVNCeqapXadnugqmZ1pIzwy16/SUq2B6ZoT0XKA=
*/