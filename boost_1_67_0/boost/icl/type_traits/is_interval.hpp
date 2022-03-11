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