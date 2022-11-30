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
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
*/