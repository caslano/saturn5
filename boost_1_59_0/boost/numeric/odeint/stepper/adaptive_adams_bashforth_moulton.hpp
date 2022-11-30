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
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
*/