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
n+c6lyff/5gi95q0Pjeq9dJ6M65tQFjWmXK/tIvjzZNqLdjt+PP+Im2gR2wA2M72RDzmd0KUXMJ55+2DpHHfZ4xeNyGMX2js6UNYn0m29DTCds+zxPHi3q/Z89ws4yXxlif8P0n/lZdn2gvvJ58wiByC5z06Va6qkAz0CYVwT/Q44t7nK0DYX2HrOPjkc1EM+/7fGTbjyPp0dh1bAWMu9eO5bh2JzE9Wdf+1Qd4fl36edwcH6edPmRI+yzZCvaF1Um3w0+3qCzKXI01s/Iucu61Xb5p/yczdTqdeIZ9L82WGTzLv46YVTy2PnZt9VdkP6Cyj8UEFDPfbgKFeqCO9X3qumudZXNWY8L70eSbfqP2Pb7BsiM+WtSGPDY0rdmdk01zLOZ6lPAudWT+er+cP3qJljfPNOKxj8t1jHkI6v94unDLQN4jEFrdyasUNvWzvaeK41/Vt9m+zYVeD+FpvXhObj0tQTY3BEcXDowjZtcvFlC/TZ16CMPSZSHfgnB37zEv1uDlEmd37V2NkP/TP/PvYkJ9W3Onr0mebEWa9XTbF3bVLHO8unkncaHV/zY+7HHFFuC+dJC7zjekKJXOpljlC5MxaTt+52Ah5/zjGvKnN8RR1kb0X0UcfmXU8u4qwvQeHsgX8dF98nbRH5BPg9Frr+9LvOloJ+UAHKHPwrz7Td6MOkz9lQN4ih8ZsZ5qrzTgMG9D3pGAj0g/92PRDt5h16K2qXD6ffrPmus3Qoa9Qv3iHkht0yC2YPvqnvUvxuIUY0h2Pe1Tfel9JuG+9l/IiPlTGn5VIGe83ZXzAlPHnkj/4U6/6LW0pA+iie/3940HhAf659b8Dcfp9e73OqDa/nPUbJH9YdIB+3PgFE/n4fnLAR9vnY2J/4M+8BC88aX9PAL98kH7piJVB77isuWXRigXsm6KJ2f7pKdXWHi+XtpaR7fxy7SfG2Dll+y3b7S3lcsfzNv7t48DD6eWCcp6BUbhLFO6wYsGxrhimPpU81hfAH1R9gw/HQeaN+t4pdKTPpf9xismjIPdb3p+FBzC5969fM3b8RLnyvYS/od8Q/g3iEc/+wekEYdPHce6o07u3tan3S4nXef3DzAvfJvbiCOw/DfZfxN5aLuPL7VompnsXuPfMHPg/THuRSntlRFqvHiWuN+9k1wf4m/PgCwx+t3qWQ2F0OUaR3+V5+O1u+O1B/PVK9hsj0o4Gbk+Tdi+mvSZPXkUGX0z89jz8xxh8KcOgB/P8snDZLzW2VWZ0c7Ghjwdd5+nX9e3GvvYxGL9OrzSYfSMwNxvM/kaWi4wsB0TwuNzwqDYYv45uNJgJEXyuMZiJEXy2G8wkhXnL/65TLn0BwsFescKwvyGGfQowU1nHF7o+TnTw9BS2ZTWmTa+X8eRl0oAL9o0V7WmzXp8Z0NCPy/g6C3G6jX+0XmRDvsFeMe3pItU3677Nnjn4eL2m59bhJwz99NJw+k9SF5eV6/fXpS9+kfrT7683KZ6bq8HX5Lmg3vgUI06PCwuZ7/fUmPMj9ffVRp55ZTIPsG/hL1H53V0ua3qd37J67gEQ01Ac+NQDDvhAL2mzF7yinnMBlYb6wL9WjpHeYcb2ouaeq1nuKWVS1vHq75nq7zn8W4+5k8vU+/kIf4zhW0rD4WcN/Q1NZ92Vlsl8BuVxdXdsffhO9of20eO30ivpceJBC/lL3Y+y67TWdhP1Yfozpu2tN/RbjO12GvqzJv1GQ3/DpO829RW1Bu81mOKiCP/m9SpMHdNuWW5rC/RvXm9xlj/fJyaOPv1Rb4LVuC2Cg02Lrdr2cgJwDXnfrE+2Zj8oZ4Nyt/XEeunPPlMvtnqS6ds+Wx/8tL5Ppu1/jlg=
*/