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
EJYgJBWY/BqA6fL2+cg7xDDJZ9+pZl/pkc//7/xSFQQTIU+hXAvjgedu+1nc7dz5VEY/2WRW3J5CMAs676g8l93Rb1u9KQ6blUHvzNi9M+V9r947UckpMiUaqKWqE/Wc6cSZn/5yEAuYs93LFXbNeS+YefQDBXzOvOYsDjLlPMF4NcnXe6JusMYmXvVDXnybZcPI9mWUU790XowQvDRujmcs9jZ5cF6OSVxNRIfVkYp7BxrAjv8o06hStgU2OlEsYSlD/iRnS5br1yknoHocy3vhxZWY3oqbYbRpLXkSWTTcyGVWEudvmb24RZ8C8y3NLItsq2RXaMGWkfFOYENbBwbkndZeGR5g1Mz54tFwvnhnoBN2X5ywSl6rUKGZ0tXxzKzj9XR9ccIqeRJNxIM+PzcB9sXZe9J2r7kY3q72wOxy0Hsvhmcxs8uhVU8mPAeayEw0mANNRjr8cds3dPjJZl3m2vLFqbV1cRouqj+dXtK50EVmoeMSz4znUguuDmukvvNXLmKL2BUGCMMsC10O1mcKAIZB9cRkiVw+PAGVrFDSLpzNk/fufHgyHEsn0pkUHMZDm1xaNhN63I9Dp/FXM3fz3cBXALZ/RPmuwrBPpEkcK/8pMy9fF6gdjvE1BFrOGjk4YBoMx+URuxy3TNH5VL2dk/bFua1oO3vG7RMp5M7IVugIAE6Hi+/A/XaghEMYph+MHCHkA6FD8kzgT8PTdQ2PyiiV/GD+ctnnka+aTkm4KlUcJGCqP27zQ0X4qwaeJxATuTvG6xPk8IDXIc+43TPi0ELTUVy7Y8U6kqzmGjgEwn40G14s0eUXJQN5UN0v3B2ccxa6/43zX+LpiYpjbWAYw0p8by3HxVnkCVBxtBbgwUpgVfwZQ+/Ga0vFSUY1mJ55D4e+2SRKx9G8S7RK4ASTzKpwnpM1waZgOVwvGM/x2Es7iQRNusd6N+dJlEbXr1LWt6ngk5QPgGQFx3CMqXKbhtOH+AueAOM9NcSX2mjsGrLAP7tubcMEesX5KHVo20P+LoHgAfZL+vE4BaWVp2sLPR+fpbolPVlK3Spp+eN5MrZXSOSHoR1/pqpedb7AM7DhgwfjxNfo2jX2Eqo4mitLm6lwrgOPY8ZviYREp2HdNyyafPvKoLS9zPnjPYXV8apXWfeJCkbtZ3Obr2MSe8lzfOz8XTIPzUHn+j2G8NCMQ+UZgu6TA2fO/KC/1DSpj6g84jeiAfSKsO0+ahvDTRFGoo6+CU9xZfyqS5JvWZecp9qucFN9L0SYj7DzQZcFT1B48GVBgsuvPeLEDcN5dq9ynrWH4unz2/kwB558OJ4io+2yYPdqJ36pd664+dYanWAy9xJ7DW57dlY1szWxUfSc4lmZzLHEVjOM11/0AbOlw2A3YTMJqK6LeJyRNp4WtzvvJZStjn7z39TNJZwvZx7UQdW6VN25lO+ghAeYS84btZdeITe++YVX7X/28+529mufve+Zr396WToZb11576UPvOnIwdWrHnK3K3dsGXxgdyy2YEVw0YqVl1/2oOSW6L3/cf70xlO3fmHxzlzsijZjUVu8O95iGAHj+pe/5IHnzp0wzv3o1oeeOnFqUeuyuy+/4c3Pu/Lgc192r8CCBQumrM2POv7BFz8quGzBsjNfu/XyO3/05TW1Wnf7wX0Hl2zsuNdjbzxyoK09Mj9y+1e/9MA//v6z6xq1eOed506vvu7lz7vPogX3vGc6tWn5juTAyu2pzQ+4+f0veXRg3rx5q4yWVSuDS1bWrFjH4UMHVgSDgeDpE6eXnP/9rZHbvvr5+602lqz+yY8/9/BavSey77nPXXD4lS9+wJmv3nLv/c95/sJTt3z+Hjt3dhs=
*/