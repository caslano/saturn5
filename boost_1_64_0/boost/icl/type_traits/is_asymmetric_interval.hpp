/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ASYMMETRIC_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_ASYMMETRIC_INTERVAL_HPP_JOFA_100327

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_asymmetric_interval
{ 
    typedef is_asymmetric_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_interval<Type>
                    ,   has_static_bounds<Type>
                    ,   has_asymmetric_bounds<Type>
                    >::value)
                );
};

template <class Type> struct is_continuous_asymmetric
{ 
    typedef is_continuous_asymmetric<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_asymmetric_interval<Type>
                    ,   is_continuous<typename domain_type_of<interval_traits<Type> >::type>
                    >::value)
                );
};

template <class Type> struct is_discrete_asymmetric
{ 
    typedef is_discrete_asymmetric<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_asymmetric_interval<Type>
                    ,   mpl::not_<is_continuous<typename domain_type_of<interval_traits<Type> >::type> >
                    >::value)
                );
};

}} // namespace boost icl

#endif



/* is_asymmetric_interval.hpp
F6g2FTuYyblIPXBmIPVajXuZ85m3URXTUsBjLbySelpWBABsle4Ysx9ugxrQo2S94fwxaxmq2Fx5tw6wapBw8Q4sn2IfrPW61CkeTh1rtysnmaf9qoK42QtBn5H2UePLRroSfXCJjlIAe4ZUXgBhCQqXGhbMWrHS6h9mR32SBxWxniJ+yCTADNnnxkQfu+gGhohY/GH7cBwRaq0qMH6BL3gd7knnDvaE8JgHHgZrpN1v7IG4OsrLu4oNhVFNCEPc1TOgSQoKv8rmUnmQDLP/UvAu5UWJhG7iXkuzqDqbOTG9UDAUVLYnGZskRGWkwMe+ThCV5FtLX7icBqS5V+HdpqQ1ekJ2Btn4RDh5NhxSAitCNWN18zIuZ4IzcInfMYxlkdqBf/FraL7Fikft/2DR0hTA6jqi+WHigXnN+3+uG+pWa3xAbnvRkhxcV6VXKlBNRFq9HlszaxcCNLV16NhReNsEtbeOulWyeDmrMsvHoIRSKK7O7CCjo7iChJSJSCca2bzZERWcwIXfn8HP3QjSaLZFu3SIKIOoI0swjj5bNVC65SuPCKMmBsC+JA==
*/