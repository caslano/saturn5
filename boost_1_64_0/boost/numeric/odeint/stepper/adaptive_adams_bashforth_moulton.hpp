/*
 boost/numeric/odeint/stepper/detail/adaptive_adams_bashforth_moulton.hpp

 [begin_description]
 Implemetation of an adaptive adams bashforth moulton stepper.
 Used as the stepper for the controlled adams bashforth moulton stepper.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ADAPTIVE_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ADAPTIVE_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/detail/adaptive_adams_coefficients.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/stepper/base/algebra_stepper_base.hpp>
#include <boost/numeric/odeint/stepper/detail/rotating_buffer.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template<
size_t Steps,
class State,
class Value = double,
class Deriv = State,
class Time = Value,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type,
class Resizer = initially_resizer 
>
class adaptive_adams_bashforth_moulton: public algebra_stepper_base< Algebra , Operations >
{
public:
    static const size_t steps = Steps;

    typedef unsigned short order_type;
    static const order_type order_value = steps;

    typedef State state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;

    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;

    typedef algebra_stepper_base< Algebra , Operations > algebra_stepper_base_type;
    typedef typename algebra_stepper_base_type::algebra_type algebra_type;
    typedef typename algebra_stepper_base_type::operations_type operations_type;
    typedef Resizer resizer_type;
    typedef error_stepper_tag stepper_category;

    typedef detail::adaptive_adams_coefficients< Steps , Deriv , Value , Time , Algebra , Operations , Resizer > coeff_type;
    typedef adaptive_adams_bashforth_moulton< Steps , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;

    order_type order() const { return order_value; };
    order_type stepper_order() const { return order_value + 1; };
    order_type error_order() const { return order_value; };

    adaptive_adams_bashforth_moulton( const algebra_type &algebra = algebra_type() )
    :algebra_stepper_base_type( algebra ), m_coeff(),
    m_dxdt_resizer(), m_xnew_resizer(), m_xerr_resizer()
    {};

    template< class System >
    void do_step(System system, state_type &inOut, time_type t, time_type dt )
    {
        m_xnew_resizer.adjust_size( inOut , detail::bind( &stepper_type::template resize_xnew_impl< state_type > , detail::ref( *this ) , detail::_1 ) );
    
        do_step(system, inOut, t, m_xnew.m_v, dt, m_xerr.m_v);
        boost::numeric::odeint::copy( m_xnew.m_v , inOut);
    };

    template< class System >
    void do_step(System system, const state_type &in, time_type t, state_type &out, time_type dt )
    {    
        do_step(system, in, t, out, dt, m_xerr.m_v);
    };

    template< class System >
    void do_step(System system, state_type &inOut, time_type t, time_type dt, state_type &xerr)
    {
        m_xnew_resizer.adjust_size( inOut , detail::bind( &stepper_type::template resize_xnew_impl< state_type > , detail::ref( *this ) , detail::_1 ) );
    
        do_step(system, inOut, t, m_xnew.m_v, dt, xerr);
        boost::numeric::odeint::copy( m_xnew.m_v , inOut);
    };

    template< class System >
    void do_step(System system, const state_type &in, time_type t, state_type &out, time_type dt , state_type &xerr)
    {
        do_step_impl(system, in, t, out, dt, xerr);
        
        system(out, m_dxdt.m_v, t+dt);
        m_coeff.do_step(m_dxdt.m_v);
        m_coeff.confirm();

        if(m_coeff.m_eo < order_value)
        {
            m_coeff.m_eo ++;
        }
    };

    template< class ExplicitStepper, class System >
    void initialize(ExplicitStepper stepper, System system, state_type &inOut, time_type &t, time_type dt)
    {
        reset();
        dt = dt/static_cast< time_type >(order_value);

        m_dxdt_resizer.adjust_size( inOut , detail::bind( &stepper_type::template resize_dxdt_impl< state_type > , detail::ref( *this ) , detail::_1 ) );

        system( inOut , m_dxdt.m_v , t );
        for( size_t i=0 ; i<order_value; ++i )
        {
            stepper.do_step_dxdt_impl( system, inOut, m_dxdt.m_v, t, dt );
            
            system( inOut , m_dxdt.m_v , t + dt);
            
            m_coeff.predict(t, dt);
            m_coeff.do_step(m_dxdt.m_v);
            m_coeff.confirm();
            
            t += dt;

            if(m_coeff.m_eo < order_value)
            {
                ++m_coeff.m_eo;
            }
        }
    };

    template< class System >
    void initialize(System system, state_type &inOut, time_type &t, time_type dt)
    {
        reset();
        dt = dt/static_cast< time_type >(order_value);

        for(size_t i=0; i<order_value; ++i)
        {
            this->do_step(system, inOut, t, dt);
            t += dt;
        };
    };

    template< class System >
    void do_step_impl(System system, const state_type & in, time_type t, state_type & out, time_type &dt, state_type &xerr)
    {
        size_t eO = m_coeff.m_eo;

        m_xerr_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_xerr_impl< state_type > , detail::ref( *this ) , detail::_1 ) );
        m_dxdt_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_dxdt_impl< state_type > , detail::ref( *this ) , detail::_1 ) );

        m_coeff.predict(t, dt);
        if (m_coeff.m_steps_init == 1)
        {
            system(in, m_dxdt.m_v, t);
            m_coeff.do_step(m_dxdt.m_v, 1);
        }

        boost::numeric::odeint::copy( in , out );
        for(size_t i=0; i<eO; ++i)
        {
            this->m_algebra.for_each3(out, out, m_coeff.phi[1][i].m_v,
                typename Operations::template scale_sum2<double, double>(1.0, dt*m_coeff.g[i]*m_coeff.beta[0][i]));
        }

        system(out, m_dxdt.m_v, t+dt);
        m_coeff.do_step(m_dxdt.m_v);

        this->m_algebra.for_each3(out, out, m_coeff.phi[0][eO].m_v,
            typename Operations::template scale_sum2<double, double>(1.0, dt*m_coeff.g[eO]));

        // error for current order
        this->m_algebra.for_each2(xerr, m_coeff.phi[0][eO].m_v, 
            typename Operations::template scale_sum1<double>(dt*(m_coeff.g[eO])));
    };

    const coeff_type& coeff() const { return m_coeff; };
    coeff_type & coeff() { return m_coeff; };

    void reset() { m_coeff.reset(); };
    const deriv_type & dxdt() const { return m_dxdt.m_v; };

private:
    template< class StateType >
    bool resize_dxdt_impl( const StateType &x )
    {
        return adjust_size_by_resizeability( m_dxdt, x, typename is_resizeable<deriv_type>::type() );
    };
    template< class StateType >
    bool resize_xnew_impl( const StateType &x )
    {
        return adjust_size_by_resizeability( m_xnew, x, typename is_resizeable<state_type>::type() );
    };
    template< class StateType >
    bool resize_xerr_impl( const StateType &x )
    {
        return adjust_size_by_resizeability( m_xerr, x, typename is_resizeable<state_type>::type() );
    };

    coeff_type m_coeff;

    resizer_type m_dxdt_resizer;
    resizer_type m_xnew_resizer;
    resizer_type m_xerr_resizer;

    wrapped_deriv_type m_dxdt;
    wrapped_state_type m_xnew;
    wrapped_state_type m_xerr;
};

} // odeint
} // numeric
} // boost

#endif
/* adaptive_adams_bashforth_moulton.hpp
TezlqvVjr/vcdBolpzFYiwkRnil5FBn7Xb5tfPba5/ITBhaFFYM7RsSeQ4mE889GRtIhMJwX92lyuJ5Yz6L/K3KeBwqHcraJ4NW6bmIxOu39GfnEcCsGx6d55n3W450ivjspDc/ZZze7VvQtHKA/XEoPVepPV9FXD9TapLr8HPWQcDfuhrXH6d+etc1DrV94wd9qysc8wKsTn6NikSmxPrqF/iU+7JsCQ9rgw6tq5Gc6YB7vXW/36Xvuu4oGhm+lauvD4dtjnNyL59fbfAd8aqwx8t9r/bLAlb+tYzva/B4uxm2d8MnPdHQ7fJuGx1pxvz2NbnyRjeaMozLInft066teH4zff4Pv2W7TZvC2rmv/Qjf/nQBXn1RLVdXXBfGaK98u6+uj6Ch/otPrn3DzKz/xpXh8pxrw0orR61d9Rsx+s75RwXNEuWB1E3EN6c9a0StypIe1mNBPbuDBRqPDfm+Bud02pgnuf4QX4nsm5tGCj+6oa+v9AZ1ahWYbs8la1JOHy50t2GrdjtP2uL1pK3ul2fSxCawvX6hRNhrnGg4wp7Aaz/x/vXcS/xa7xr/uj9d7BjXO40qtH6M9/njEA55JM3st/VVaPwZmwt5htaxHTve+ZS1HwsCjcGMb/Oos9hnVaypYBUs/uIXDrfUnPeXDUe+frl8M/PUrNL9c+Sy5c0sr1VVr648v5jkz+P1SvqIYTJTnz/WcRZ7xFcvrqf8W7848gn9pOJ7FvU/EfA38/FbuwZdifKGaSc1Lfd3YKh5w8Q/8fulbfVnYvfH4odq8jFnwkC/+UVuYREdOe1ffTydH02qnP7GeJcVOTv7XuYzrgYeg15+WTS9XNYTH7FHD8l/L4v07MF99jkmgh/+U9ywn4931HVnlrcH7cju1e2/nVelHRu2Hk/nsy2SxHo34PvJvKNz8OLc+G4fE12c8ipRfdWByUbjhnNTi+OpJzZ6jX3/vpO4q6Nuy0Om7rdFpePc7bUfbd4Pjk2HSAmNNuJZ3RiecaQPr29LFmekA9VKvvZ6hJp0VpWbgwnPrcZT3eGm1NboH+y/E7S2n4VPPlrMhddl7H2zcSQcexOsrxPYIrW5eWWmRenJx0AA9cG/apiocsiaJ1EtberbjcucDasjp9Mb+PQ6ebX+BZv1gCJyClzdq0XA0Rocw/d9a76F3+8MeYrii5xSy6bff4Y/Bt7MZ6dkJMLA9X76PuuwntyaJpTNfFTrIk94w1Vovcs+7eqX3+xrTLWvQGrbByzP6vJTy9zBtHualvMLbK55Dna91zdVia/0W4Ia5rWl3uu5qJn5uBb6YOswdRaPAjICP6zYMO3sk79V1s9/kWzp+AyxPtyHwtPRLi/Cb10fpZdZ9THtY66zwMP5zsYDXJfFhO58fPkXuWotgn+Nd9Vf8N55bf57KJtuzuGzD9gjaDpaJX559+oY3nReHNe3v0zn5xLK7WpNvhce55+vGRFcdaIS7SuqFD6nXHXLgJJ2iXjbspbkmitlmdWpNR8Cay8G5qA1ic0yNFKYD37Kekc6cNBfDsTijDe14kjYP4aEP8OxQGoruXVSCXvxMzHaqWWO7g6ean4UndMxo7y+sL+siz2oG361AMyQ9B9vNK9zYPlx1nJU87vtfW8PEdnquonA29wB16LzajykiY3uzyu3l4VA6/mtrpp67ZocT9GZT+i9z8P2Wvfz7B17gf9RexVCsf/r3ZbVVR+4OsffrWj0r6athyxTr2eIhD6wP/0Ft5Njl2o18Zqi9v63WNDLCWUL4IX9ivH+pvua8Me0EEpVfh/3iMSOTuDfF5ftoHxr+yRvyg49Qwzgz93ROBvaUqumMidg0aSlfjGFWI+/rhqs=
*/