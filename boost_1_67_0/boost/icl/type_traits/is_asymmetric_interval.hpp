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