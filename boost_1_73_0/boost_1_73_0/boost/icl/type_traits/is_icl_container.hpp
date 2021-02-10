/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ICL_CONTAINER_HPP_JOFA_100831
#define BOOST_ICL_TYPE_TRAITS_IS_ICL_CONTAINER_HPP_JOFA_100831

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_element_container.hpp> 
#include <boost/icl/type_traits/is_interval_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template <class Type> 
    struct is_icl_container
    { 
        typedef is_icl_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<  is_element_container<Type>
                     , is_interval_container<Type> >::value));
    };

}} // namespace boost icl

#endif



/* is_icl_container.hpp
RRILUrHOmz3p3SxlmYgUJBKi5ZKQ6OLGiHDAIfB64Vfmc7ADGPneld3lXTBYgPcGMLerg9g4HHg+dO2g4zAbLWaOA4jymRvaPCCur3Y4AJ/3mY8QD1HI98Ttdpxx13b7GmgPR46NWZ4IwOsRx5D7nQE+YRe2Y4fXOn3PDl0eBBZygOsBv+JuCMGAeGrKLjg4NrtwOPQ8n6iYew3BiHds5pio2+ed0ESKzS+EdDw34H+NkQ5joMuGrE9CfA2tbnVhAxYGHub1sbxg7IRURs/HxnK8gJTDOOCYg4WM0OghSg5MxHEU6JNu5mpJndD2XAJg6tBnpMPlfcfuc7fDCetpQOj5GDgOKoAJzLcDSuqNQ+JBAk/TIo3L16TaffIDtWgV3EcjhkwT93Z3Y7P7n389vizlsT4Dl1a98+H0BJeWuPT5tL4EMM5mUbHu6g6eaPjNOm0j4Px/+lsrIwV996rRd8eQzEEKgccAVdPNvFEouZSrI6OKMD6BJX7kFhgGRuAxkXgBeIDzndixYRqOO2zQbODDSUi9YnzSocj6UOeAJxb6u1cJVpw/5g08rBmeV8oMqzIvYIrPaaThIcVpNRVoS3X+6zOn4hEPSQFfvuh7IXF66F8zMU+kaCF9IVYt8SDiVoETID+PUxlvXWg+
*/