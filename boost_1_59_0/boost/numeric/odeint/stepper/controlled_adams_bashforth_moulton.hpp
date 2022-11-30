/*
 boost/numeric/odeint/stepper/detail/controlled_adams_bashforth_moulton.hpp

 [begin_description]
 Implemetation of an controlled adams bashforth moulton stepper.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>

#include <boost/numeric/odeint/stepper/adaptive_adams_bashforth_moulton.hpp>
#include <boost/numeric/odeint/stepper/detail/pid_step_adjuster.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/util/copy.hpp>
#include <boost/numeric/odeint/util/bind.hpp>

#include <iostream>

namespace boost {
namespace numeric {
namespace odeint {

template<
size_t MaxOrder,
class State,
class Value = double,
class Algebra = typename algebra_dispatcher< State >::algebra_type
>
class default_order_adjuster
{
public:
    typedef State state_type;
    typedef Value value_type;
    typedef state_wrapper< state_type > wrapped_state_type;

    typedef Algebra algebra_type;

    default_order_adjuster( const algebra_type &algebra = algebra_type() )
    : m_algebra( algebra )
    {};

    size_t adjust_order(size_t order, size_t init, boost::array<wrapped_state_type, 4> &xerr)
    {
        using std::abs;

        value_type errc = abs(m_algebra.norm_inf(xerr[2].m_v));

        value_type errm1 = 3*errc;
        value_type errm2 = 3*errc;

        if(order > 2)
        {
            errm2 = abs(m_algebra.norm_inf(xerr[0].m_v));
        }
        if(order >= 2)
        {
            errm1 = abs(m_algebra.norm_inf(xerr[1].m_v));
        }

        size_t o_new = order;

        if(order == 2 && errm1 <= 0.5*errc)
        {
            o_new = order - 1;
        }
        else if(order > 2 && errm2 < errc && errm1 < errc)
        {
            o_new = order - 1;
        }

        if(init < order)
        {
            return order+1;
        }
        else if(o_new == order - 1)
        {
            return order-1;
        }
        else if(order <= MaxOrder)
        {
            value_type errp = abs(m_algebra.norm_inf(xerr[3].m_v));

            if(order > 1 && errm1 < errc && errp)
            {
                return order-1;
            }
            else if(order < MaxOrder && errp < (0.5-0.25*order/MaxOrder) * errc)
            {
                return order+1;
            }
        }

        return order;
    };
private:
    algebra_type m_algebra;
};

template<
class ErrorStepper,
class StepAdjuster = detail::pid_step_adjuster< typename ErrorStepper::state_type, 
    typename ErrorStepper::value_type,
    typename ErrorStepper::deriv_type,
    typename ErrorStepper::time_type,
    typename ErrorStepper::algebra_type,
    typename ErrorStepper::operations_type,
    detail::H211PI
    >,
class OrderAdjuster = default_order_adjuster< ErrorStepper::order_value,
    typename ErrorStepper::state_type,
    typename ErrorStepper::value_type,
    typename ErrorStepper::algebra_type
    >,
class Resizer = initially_resizer
>
class controlled_adams_bashforth_moulton
{
public:
    typedef ErrorStepper stepper_type;

    static const typename stepper_type::order_type order_value = stepper_type::order_value;
    
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;

    typedef typename stepper_type::algebra_type algebra_type;
    typedef typename stepper_type::operations_type operations_type;
    typedef Resizer resizer_type;

    typedef StepAdjuster step_adjuster_type;
    typedef OrderAdjuster order_adjuster_type;
    typedef controlled_stepper_tag stepper_category;

    typedef typename stepper_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_type::wrapped_deriv_type wrapped_deriv_type;
    typedef boost::array< wrapped_state_type , 4 > error_storage_type;

    typedef typename stepper_type::coeff_type coeff_type;
    typedef controlled_adams_bashforth_moulton< ErrorStepper , StepAdjuster , OrderAdjuster , Resizer > controlled_stepper_type;

    controlled_adams_bashforth_moulton(step_adjuster_type step_adjuster = step_adjuster_type())
    :m_stepper(),
    m_dxdt_resizer(), m_xerr_resizer(), m_xnew_resizer(),
    m_step_adjuster( step_adjuster ), m_order_adjuster()
    {};

    template< class ExplicitStepper, class System >
    void initialize(ExplicitStepper stepper, System system, state_type &inOut, time_type &t, time_type dt)
    {
        m_stepper.initialize(stepper, system, inOut, t, dt);
    };

    template< class System >
    void initialize(System system, state_type &inOut, time_type &t, time_type dt)
    {
        m_stepper.initialize(system, inOut, t, dt);
    };

    template< class ExplicitStepper, class System >
    void initialize_controlled(ExplicitStepper stepper, System system, state_type &inOut, time_type &t, time_type &dt)
    {
        reset();
        coeff_type &coeff = m_stepper.coeff();

        m_dxdt_resizer.adjust_size( inOut , detail::bind( &controlled_stepper_type::template resize_dxdt_impl< state_type > , detail::ref( *this ) , detail::_1 ) );

        controlled_step_result res = fail;

        for( size_t i=0 ; i<order_value; ++i )
        {
            do
            {
                res = stepper.try_step( system, inOut, t, dt );
            }
            while(res != success);

            system( inOut , m_dxdt.m_v , t );
            
            coeff.predict(t-dt, dt);
            coeff.do_step(m_dxdt.m_v);
            coeff.confirm();

            if(coeff.m_eo < order_value)
            {
                ++coeff.m_eo;
            }
        }
    }

    template< class System >
    controlled_step_result try_step(System system, state_type & inOut, time_type &t, time_type &dt)
    {
        m_xnew_resizer.adjust_size( inOut , detail::bind( &controlled_stepper_type::template resize_xnew_impl< state_type > , detail::ref( *this ) , detail::_1 ) );

        controlled_step_result res = try_step(system, inOut, t, m_xnew.m_v, dt);

        if(res == success)
        {
            boost::numeric::odeint::copy( m_xnew.m_v , inOut);
        }

        return res;
    };

    template< class System >
    controlled_step_result try_step(System system, const state_type & in, time_type &t, state_type & out, time_type &dt)
    {
        m_xerr_resizer.adjust_size( in , detail::bind( &controlled_stepper_type::template resize_xerr_impl< state_type > , detail::ref( *this ) , detail::_1 ) );
        m_dxdt_resizer.adjust_size( in , detail::bind( &controlled_stepper_type::template resize_dxdt_impl< state_type > , detail::ref( *this ) , detail::_1 ) );

        m_stepper.do_step_impl(system, in, t, out, dt, m_xerr[2].m_v);

        coeff_type &coeff = m_stepper.coeff();

        time_type dtPrev = dt;
        dt = m_step_adjuster.adjust_stepsize(coeff.m_eo, dt, m_xerr[2].m_v, out, m_stepper.dxdt() );

        if(dt / dtPrev >= step_adjuster_type::threshold())
        {
            system(out, m_dxdt.m_v, t+dtPrev);

            coeff.do_step(m_dxdt.m_v);
            coeff.confirm();

            t += dtPrev;

            size_t eo = coeff.m_eo;

            // estimate errors for next step
            double factor = 1;
            algebra_type m_algebra;

            m_algebra.for_each2(m_xerr[2].m_v, coeff.phi[1][eo].m_v, 
                typename operations_type::template scale_sum1<double>(factor*dt*(coeff.gs[eo])));

            if(eo > 1)
            {
                m_algebra.for_each2(m_xerr[1].m_v, coeff.phi[1][eo-1].m_v, 
                    typename operations_type::template scale_sum1<double>(factor*dt*(coeff.gs[eo-1])));
            }
            if(eo > 2)
            {
                m_algebra.for_each2(m_xerr[0].m_v, coeff.phi[1][eo-2].m_v, 
                    typename operations_type::template scale_sum1<double>(factor*dt*(coeff.gs[eo-2])));
            }
            if(eo < order_value && coeff.m_eo < coeff.m_steps_init-1)
            {
                m_algebra.for_each2(m_xerr[3].m_v, coeff.phi[1][eo+1].m_v, 
                    typename operations_type::template scale_sum1<double>(factor*dt*(coeff.gs[eo+1])));
            }

            // adjust order
            coeff.m_eo = m_order_adjuster.adjust_order(coeff.m_eo, coeff.m_steps_init-1, m_xerr);

            return success;
        }
        else
        {
            return fail;
        }
    };

    void reset() { m_stepper.reset(); };

private:
    template< class StateType >
    bool resize_dxdt_impl( const StateType &x )
    {
        return adjust_size_by_resizeability( m_dxdt, x, typename is_resizeable<deriv_type>::type() );
    };
    template< class StateType >
    bool resize_xerr_impl( const StateType &x )
    {
        bool resized( false );

        for(size_t i=0; i<m_xerr.size(); ++i)
        {
            resized |= adjust_size_by_resizeability( m_xerr[i], x, typename is_resizeable<state_type>::type() );
        }
        return resized;
    };
    template< class StateType >
    bool resize_xnew_impl( const StateType &x )
    {
        return adjust_size_by_resizeability( m_xnew, x, typename is_resizeable<state_type>::type() );
    };

    stepper_type m_stepper;

    wrapped_deriv_type m_dxdt;
    error_storage_type m_xerr;
    wrapped_state_type m_xnew;

    resizer_type m_dxdt_resizer;
    resizer_type m_xerr_resizer;
    resizer_type m_xnew_resizer;

    step_adjuster_type m_step_adjuster;
    order_adjuster_type m_order_adjuster;
};

} // odeint
} // numeric
} // boost

#endif
/* controlled_adams_bashforth_moulton.hpp
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
*/