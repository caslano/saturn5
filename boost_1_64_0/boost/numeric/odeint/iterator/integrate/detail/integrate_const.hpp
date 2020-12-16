/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_const.hpp

 [begin_description]
 integrate const implementation
 [end_description]

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_CONST_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_CONST_HPP_INCLUDED

#include <boost/range/algorithm/for_each.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/iterator/const_step_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_adaptive.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer , controlled_stepper_tag
);


template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag 
)
{
    size_t obs_calls = 0;

    boost::for_each( make_const_step_time_range( stepper , system , start_state ,
                                                 start_time , end_time , dt ) ,
                     // should we use traits<Stepper>::state_type here instead of State? NO!
                     obs_caller< Observer >( obs_calls , observer ) );

    // step integration steps gives step+1 observer calls
    return obs_calls-1;
}



template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , controlled_stepper_tag 
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    
    Time time = start_time;
    const Time time_step = dt;
    int step = 0;
    
    while( less_eq_with_sign( static_cast<Time>(time+time_step) , end_time , dt ) )
    {
        obs( start_state , time );
        detail::integrate_adaptive( stepper , system , start_state , time , time+time_step , dt ,
                                    null_observer() , controlled_stepper_tag() );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        ++step;
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * time_step;
    }
    obs( start_state , time );
    
    return step;
}


template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , dense_output_stepper_tag 
)
{
    size_t obs_calls = 0;

    boost::for_each( make_const_step_time_range( stepper , system , start_state ,
                                                 start_time , end_time , dt ) ,
                     obs_caller< Observer >( obs_calls , observer ) );
    return obs_calls-1;
}


} } } }

#endif

/* integrate_const.hpp
Psv97Q7iS1tt8+a9DqGLUvAlgc53gvHwWaiBCOuKLaPrvT7UuN5mDkAA4/4uHCfex/phx5nUxxg7/Jq4kkF8/h7+mXCQOnkLeF4NsIG8xAIPeh1bPniBtjbAht8ivuyBYzM3P/k0HBvueWgkfK0MuPmToKbH/FzimWcYvBGO//4DMNYdO/jaZicdmsLJXyLvwCam/0A/aOdHnhzjvaHknq1m8zf4Pug2fN4K125FHh2ADjpjt+QwiVfwm4b4FuO4sYyvLigCn4BTdyFvGpNKm3/jneDCVf5dg56Ooo9lHahtfkTc4HnHLYzBIaOaC8Dayug9P/iKfIaCHZHE0Blr4BnEsvDrAvnjewN4Bjy5Ti/0eF6Lh/gCsTAoiNx6In0oD55rtY6tjMGjm+lfI2/wq854npGBXxBTO3/JnJs22ji2gG8x370/9gDPKraM8Qq4mlMHwTwkah6bwXDqOF+AlacmgwMvEZPgvsfqo2fidO/H9OEl8tZP4ZH9wZLX2S+NtpQsQX4P3mrjKzWxDf8u6Ir+O8chk3PkWXCepuBa3zvgGTafN4I6KfPA0vuQlzCPs+19sK4e2LWa+eMHVOwGPTMuu34gYxT7yZ+oifkOBF+xlWLYwbgI6nfwMytcrvY2+AjyrTKBORX++OBi4uHfwWjmG7qHouc5cHUwtgwYfCIDnjqX3Jk++NH2g9hhtTj0hT/O7gBegAda3WtrEnaIrO9cVnRMWtGJuE3MbFYMbg4ulmjLWEkczwonrliph79Dn7CF+fPIXc5yvA8yg0/f49pjDbGFjfQHv91NjXP+eWwKXK9O3dH1KrlTAdpfjP0YiH/XkY/HE+YskHesiiKWklcHPAJjEpDrEp7lDe98B/xCF7O19SXIXoFjuiNz95Fg/Tr8dTZxHA72Kn5xrQLjX7PgnYxPraZ9m+ehQ66NnoiNIPcweH6hcRadG2z1ppY9AFwqTo54C/7VD4zHd0qeQ/a8cxZrc2qD1Zdj4DmHiXPEu8LkPs5gd2/4ePUy3Mv5+tjLZ3B193vgOL89WxPf8eeT4FMY42nh9Oc9eEpmCGMYZ7mG58yhDeP3w+3yE4M7M9eHetExeO8o9HyF8a9iM/B38uUSlRjzmIcNFQbfrdR3uL7A+4xD+MIl4B4jHqLrxcwHg+9ntEZvtM33fTj+ZWIU50cjk0ZgtF8VfK4IzwLzh13CVmnnsFLkPgsFdWrsujY1+qFw4RvMp1nEuSXgWDB2Aafz5J3rLcTTu8i7EZgFf3gE9hWGv/uHgI/w8iWd4Xs98AtqXe8RF4vB11sTm/3R3/gB8AXm1TZdwFyt0XAe7OG7ndgMfUzvjZ4Pwv0YP7KOFHrtwQu+Vh6brwoXjYIPRQ2FW4zB73tSE/aHnwtyhQy4ALpoge8vYswxvRb2xFiEM7a8mPHVMOoAnbDDIZmcQ+ZTGF8uQk2zLc+4fQnOOgg/TxS0j9wVrEnYSF/Jc7zDyU3zUHNKwzfmwA0+ggPCpQKxm1bUUmJpTxXwpM135NTE5HzYfcuLFmwXzk1bjvG8OhpHhGv2plbYvi/jaSuxH/hdKvWhtLG0kbw5gJzicSzxmTY0W2Fbx9d3PjkVOaqq4qtu3IMtb64LRkSj45nUO+Gcv6Gn/ujEdQk2Ds6dJQ7t7gn2Y1Pamp5Vn3Mt7UpnTGpkX2KbBz7wLnoDE16nndWRcc8w8lcrcVOrqweh17HETXLVP+YQQ9vR5kpwk6/AoG7488fgzXyeDX97RP2qIP/u2kNuvoH4k8icCXLQDlbGbX2RWSr1uJPcO5V6CzqvHUJOdJd4nAwXws9Kw2Va1YIL4g99ySE9wqhzlkLngdTCv6UOS92uQRX8Gww=
*/