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
VLVjLrrC0fxWWIkVVoK8YutU6XrzshPHHVbiDiuRluS9oa7MtUkF39AvaZ6OlVbHSqujtcSaG1G5w4XLHV31shK9rETbkEQ3R6K3lehtJfYQiXYR1U5L7O9I9LESfaxE95BEX0eir5XoayX67FSin5XoZyX2E4k9ImoP/U6HOxL7WIl9rMRAkeiZpHpGclX78nbjiPNJp7btZ6X2s1IFIuW0n7OdePa3EvtbicO9mqBTdp0jcYCVOMBKFElN6B8=
*/