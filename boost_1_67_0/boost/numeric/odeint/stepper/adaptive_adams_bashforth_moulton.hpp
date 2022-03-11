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