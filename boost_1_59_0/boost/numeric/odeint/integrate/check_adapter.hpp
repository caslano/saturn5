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
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
*/