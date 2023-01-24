/*
 [auto_generated]
 boost/numeric/odeint/integrate/check_adapter.hpp

 [begin_description]
 Adapters to add checking facility to stepper and observer
 [end_description]

 Copyright 2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_CHECK_ADAPTER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_CHECK_ADAPTER_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>


namespace boost {
namespace numeric {
namespace odeint {

template<class Stepper, class Checker,
         class StepperCategory = typename base_tag<typename Stepper::stepper_category>::type>
class checked_stepper;


/**
 * \brief Adapter to combine basic stepper and checker.
 */
template<class Stepper, class Checker>
class checked_stepper<Stepper, Checker, stepper_tag>
{

public:
    typedef Stepper stepper_type;
    typedef Checker checker_type;
    // forward stepper typedefs
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;

private:
    stepper_type &m_stepper;
    checker_type &m_checker;

public:
    /**
     * \brief Construct the checked_stepper.
     */
    checked_stepper(stepper_type &stepper, checker_type &checker)
            : m_stepper(stepper), m_checker(checker) { }

    /**
     * \brief forward of the do_step method
     */
    template<class System, class StateInOut>
    void do_step(System system, StateInOut &state, const time_type t, const time_type dt)
    {
        // do the step
        m_stepper.do_step(system, state, t, dt);
        // call the checker
        m_checker();
    }
};


/**
 * \brief Adapter to combine controlled stepper and checker.
 */
template<class ControlledStepper, class Checker>
class checked_stepper<ControlledStepper, Checker, controlled_stepper_tag>
{

public:
    typedef ControlledStepper stepper_type;
    typedef Checker checker_type;
    // forward stepper typedefs
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;

private:
    stepper_type &m_stepper;
    checker_type &m_checker;

public:
    /**
     * \brief Construct the checked_stepper.
     */
    checked_stepper(stepper_type &stepper, checker_type &checker)
            : m_stepper(stepper), m_checker(checker) { }

    /**
     * \brief forward of the do_step method
     */
    template< class System , class StateInOut >
    controlled_step_result try_step( System system , StateInOut &state , time_type &t , time_type &dt )
    {
        // do the step
        if( m_stepper.try_step(system, state, t, dt) == success )
        {
            // call the checker if step was successful
            m_checker();
            return success;
        } else
        {
            // step failed -> return fail
            return fail;
        }
    }
};


/**
 * \brief Adapter to combine dense out stepper and checker.
 */
template<class DenseOutStepper, class Checker>
class checked_stepper<DenseOutStepper, Checker, dense_output_stepper_tag>
{

public:
    typedef DenseOutStepper stepper_type;
    typedef Checker checker_type;
    // forward stepper typedefs
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;

private:
    stepper_type &m_stepper;
    checker_type &m_checker;

public:
    /**
     * \brief Construct the checked_stepper.
     */
    checked_stepper(stepper_type &stepper, checker_type &checker)
            : m_stepper(stepper), m_checker(checker) { }


    template< class System >
    std::pair< time_type , time_type > do_step( System system )
    {
        m_checker();
        return m_stepper.do_step(system);
    }

    /* provide the remaining dense out stepper interface */
    template< class StateType >
    void initialize( const StateType &x0 , time_type t0 , time_type dt0 )
    { m_stepper.initialize(x0, t0, dt0); }


    template< class StateOut >
    void calc_state( time_type t , StateOut &x ) const
    { m_stepper.calc_state(t, x); }

    template< class StateOut >
    void calc_state( time_type t , const StateOut &x ) const
    { m_stepper.calc_state(t, x); }

    const state_type& current_state( void ) const
    { return m_stepper.current_state(); }

    time_type current_time( void ) const
    { return m_stepper.current_time(); }

    const state_type& previous_state( void ) const
    { return m_stepper.previous_state(); }

    time_type previous_time( void ) const
    { return m_stepper.previous_time(); }

    time_type current_time_step( void ) const
    { return m_stepper.current_time_step(); }

};


/**
 * \brief Adapter to combine observer and checker.
 */
template<class Observer, class Checker>
class checked_observer
{
public:
    typedef Observer observer_type;
    typedef Checker checker_type;

private:
    observer_type &m_observer;
    checker_type &m_checker;

public:
    checked_observer(observer_type &observer, checker_type &checker)
            : m_observer(observer), m_checker(checker)
    {}

    template< class State , class Time >
    void operator()(const State& state, Time t) const
    {
        // call the observer
        m_observer(state, t);
        // reset the checker
        m_checker.reset();
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif
/* check_adapter.hpp
2FPKjCW6yp8vrlUwsfMQfP3ThAiBxSACvg8gDnDwxnwL4b5UPBSJHe2N6T4JclpZf4H1UgWl6YuFKL2eN9M71t6Y/sy/SvUPZP55qt/K/NPIr+E/eySiaozIQZ2hMQt90EIdoc6l7JjJnVFoMLEHn/I45e6VNjKCdIyfpQv4Jgt8cg2E/GlabLx2JH8UqULL+1aW94a7Ke8eofKO5Hnna3n/ns7yPpeu5g31WI1tM4V4ofG/L1PWmA75s9HL/D+r/k3M/12D+K9U/5fM/7nqX8f8O1X/T8y/TfXvY/7Nqt+8nvzvNsjv36r/ehb/UoP0z6j+GOZ/XPX/xb5fofovM/+iBvg8ovqN7PuHGpSfx/zEJGJ2OVi7t1KpXn1fdsmQqQ7W4r93ps9GgNfZHj4Zrn6imGfHajS/Hd9CpzzND2IC93bZXaXUmMqHxrplw+LWotSGT8YajRaOwb5y43t6///vn/xVr29L8DsOf+cw7BUGJ7zLoMjhTRz25rA9h7v/y+BRDk9xWM+h+vd4A387BpbEcBjNYRsOeeolavqc11lIAYcrOHyew9c5/IDDMg6PcljDYdgbDMZxeB2HQzkcw+FkDvuVMtiNw2gO27zP4LmNDJ7kcC+Hmzm08XJXcv88DvM4nMChhcMBHL79Gm9v7u/AYf17DP7I4W4O3+XweQ4XcJjI83Fw/wAOr+IwisMzvD+jePpq7t/G4The
*/