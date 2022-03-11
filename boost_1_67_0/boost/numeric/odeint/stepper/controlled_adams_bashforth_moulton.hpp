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