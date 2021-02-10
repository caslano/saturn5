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
qJghT+S24M+Xl+Ju+3swnF9dWqWOhhFlhidU55WtMOCSQI/CsWRO3Em27Cg9oeqSqQ9Wk6ZmzxaAIrhvdAioNxkXkbZxPQjqSdb6i+2apM+SDiYCmyRdqBKyvgmn9wsfkr46hlwoCxIWLNWrQroyhoqggzV6W7BaPMbZqejmbhy/U8/suHAKVtmzLkzGTcUzyFHzQSZbDgbLnx/649HNKJrN+UwGshbU2xHQWTwFDBGctFXnQAxcgwn9/I+I42vUlAD9PCc0pVUlVI8UcL6XRUYubUq37iGDp5pNpn93TRNOa+hcaOf8mk/YBH7X7vAHcVaW6RkD09rAvb+6LC4OeWX+yMoNrJjrP7Ly9+6iGtGlyedIkwTQ7pjeDRAbnziQGVI71VzZYLmzK5SClJAeejZvOG+igKqo1nAqpyq5oCpR1ngOv2iqR4su1NySN1KX9uhpo0wvyxq7A6XZfjaUGHIdzP41j0u9hAxJHVc88mRyWBQEKDvtGjsF7b500cCx3sRKm2TsYAhvaDZQcFXWnRKRGMPB2EHNyTY7ONFcqlEC7WS2ZlzBG7u+zHEfcK/u8+xK4fxPKvc1EA1XnNhfPTN3+rZ7bQP9uN7hQi6gCE0UQdjKBjijNJCXSoCVwk7WL9HuMEMV+sqz5bpO
*/