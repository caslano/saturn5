/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_HPP_JOFA_100327

#include <boost/mpl/or.hpp>
#include <boost/icl/interval_bounds.hpp>
#include <boost/icl/interval_traits.hpp>

namespace boost{ namespace icl
{

template <class Type>
struct interval_bound_type
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = (interval_bounds::undefined)); 
};

template <class Type> struct is_interval
{ 
    typedef is_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, 
        value = ((interval_bound_type<Type>::value) < interval_bounds::undefined)); 
};


template <class Type> struct has_static_bounds
{ 
    typedef has_static_bounds<Type> type;
    BOOST_STATIC_CONSTANT(bool, 
        value = ((interval_bound_type<Type>::value) < interval_bounds::dynamic)); 
};

template <class Type> struct has_dynamic_bounds
{ 
    typedef has_dynamic_bounds<Type> type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (interval_bound_type<Type>::value == interval_bounds::dynamic));
};

template <class Type> struct has_asymmetric_bounds
{ 
    typedef has_asymmetric_bounds<Type> type;
    BOOST_STATIC_CONSTANT(bound_type, bounds = (interval_bound_type<Type>::value)); 
    BOOST_STATIC_CONSTANT(bool, 
        value = (   bounds == interval_bounds::static_left_open 
                 || bounds == interval_bounds::static_right_open)); 
};

template <class Type> struct has_symmetric_bounds
{ 
    typedef has_symmetric_bounds<Type> type;
    BOOST_STATIC_CONSTANT(bound_type, bounds = (interval_bound_type<Type>::value)); 
    BOOST_STATIC_CONSTANT(bool, 
        value = (   bounds == interval_bounds::static_closed 
                 || bounds == interval_bounds::static_open)); 
};

//------------------------------------------------------------------------------
template <class Type> struct is_discrete_static
{ 
    typedef is_discrete_static type;
    typedef typename interval_traits<Type>::domain_type domain_type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (mpl::and_< has_static_bounds<Type>
                          , is_discrete<domain_type> >::value) ); 
};

//------------------------------------------------------------------------------
template <class Type> struct is_continuous_static
{ 
    typedef is_continuous_static type;
    typedef typename interval_traits<Type>::domain_type domain_type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (mpl::and_< has_static_bounds<Type>
                          , is_continuous<domain_type>
                          , has_asymmetric_bounds<Type> >::value) ); 
};

//------------------------------------------------------------------------------
template <class Type> struct is_static_right_open
{ 
    typedef is_static_right_open<Type> type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (interval_bound_type<Type>::value == interval_bounds::static_right_open)); 
};

template <class Type> struct is_static_left_open
{ 
    typedef is_static_left_open<Type> type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (interval_bound_type<Type>::value == interval_bounds::static_left_open)); 
};

template <class Type> struct is_static_open
{ 
    typedef is_static_open<Type> type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (interval_bound_type<Type>::value == interval_bounds::static_open)); 
};

template <class Type> struct is_static_closed
{ 
    typedef is_static_closed<Type> type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (interval_bound_type<Type>::value == interval_bounds::static_closed)); 
};

template <class Type> struct is_discrete_static_closed
{ 
    typedef is_static_closed<Type> type;
    typedef typename interval_traits<Type>::domain_type domain_type;
    
    BOOST_STATIC_CONSTANT( bool, 
        value = (mpl::and_< is_static_closed<Type>
                          , is_discrete<domain_type> >::value) ); 
};

template <class Type> struct is_discrete_static_open
{ 
    typedef is_static_closed<Type> type;
    typedef typename interval_traits<Type>::domain_type domain_type;
    
    BOOST_STATIC_CONSTANT( bool, 
        value = (mpl::and_< is_static_open<Type>
                          , is_discrete<domain_type> >::value) ); 
};

//------------------------------------------------------------------------------
template <class Type> struct is_continuous_right_open
{ 
    typedef is_continuous_right_open<Type> type;
    typedef typename interval_traits<Type>::domain_type domain_type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (mpl::and_<is_static_right_open<Type>, is_continuous<domain_type> >::value)); 
};

template <class Type> struct is_continuous_left_open
{ 
    typedef is_continuous_left_open<Type> type;
    typedef typename interval_traits<Type>::domain_type domain_type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (mpl::and_<is_static_left_open<Type>, is_continuous<domain_type> >::value)); 
};

//------------------------------------------------------------------------------

template <class Type> struct is_singelizable
{
    typedef is_singelizable type;
    typedef typename interval_traits<Type>::domain_type domain_type;

    BOOST_STATIC_CONSTANT(bool, 
        value =
            (mpl::or_< has_dynamic_bounds<Type>
                     , is_discrete<domain_type> 
                     >::value)
    );
};

}} // namespace boost icl

#endif



/* is_interval.hpp
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
*/