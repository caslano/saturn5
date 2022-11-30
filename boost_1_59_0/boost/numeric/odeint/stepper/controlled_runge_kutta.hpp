/* [auto_generated]
 boost/numeric/odeint/stepper/controlled_runge_kutta.hpp

 [begin_description]
 The default controlled stepper which can be used with all explicit Runge-Kutta error steppers.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2015 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED



#include <cmath>

#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template
<
class Value ,
class Algebra ,
class Operations
>
class default_error_checker
{
public:

    typedef Value value_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;

    default_error_checker(
            value_type eps_abs = static_cast< value_type >( 1.0e-6 ) ,
            value_type eps_rel = static_cast< value_type >( 1.0e-6 ) ,
            value_type a_x = static_cast< value_type >( 1 ) ,
            value_type a_dxdt = static_cast< value_type >( 1 ))
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt )
    { }


    template< class State , class Deriv , class Err, class Time >
    value_type error( const State &x_old , const Deriv &dxdt_old , Err &x_err , Time dt ) const
    {
        return error( algebra_type() , x_old , dxdt_old , x_err , dt );
    }

    template< class State , class Deriv , class Err, class Time >
    value_type error( algebra_type &algebra , const State &x_old , const Deriv &dxdt_old , Err &x_err , Time dt ) const
    {
        using std::abs;
        // this overwrites x_err !
        algebra.for_each3( x_err , x_old , dxdt_old ,
                typename operations_type::template rel_error< value_type >( m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt * abs(get_unit_value( dt )) ) );

        // value_type res = algebra.reduce( x_err ,
        //        typename operations_type::template maximum< value_type >() , static_cast< value_type >( 0 ) );
        return algebra.norm_inf( x_err );
    }

private:

    value_type m_eps_abs;
    value_type m_eps_rel;
    value_type m_a_x;
    value_type m_a_dxdt;

};


template< typename Value, typename Time >
class default_step_adjuster
{
public:
    typedef Time time_type;
    typedef Value value_type;

    default_step_adjuster(const time_type max_dt=static_cast<time_type>(0))
            : m_max_dt(max_dt)
    {}


    time_type decrease_step(time_type dt, const value_type error, const int error_order) const
    {
        // returns the decreased time step
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        using std::pow;

        dt *= max
        BOOST_PREVENT_MACRO_SUBSTITUTION(
                static_cast<value_type>( static_cast<value_type>(9) / static_cast<value_type>(10) *
                                         pow(error, static_cast<value_type>(-1) / (error_order - 1))),
                static_cast<value_type>( static_cast<value_type>(1) / static_cast<value_type> (5)));
        if(m_max_dt != static_cast<time_type >(0))
            // limit to maximal stepsize even when decreasing
            dt = detail::min_abs(dt, m_max_dt);
        return dt;
    }

    time_type increase_step(time_type dt, value_type error, const int stepper_order) const
    {
        // returns the increased time step
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        using std::pow;

        // adjust the size if dt is smaller than max_dt (providede max_dt is not zero)
        if(error < 0.5)
        {
            // error should be > 0
            error = max BOOST_PREVENT_MACRO_SUBSTITUTION (
                    static_cast<value_type>( pow( static_cast<value_type>(5.0) , -static_cast<value_type>(stepper_order) ) ) ,
                    error);
            // time_type dt_old = dt;   unused variable warning 
            //error too small - increase dt and keep the evolution and limit scaling factor to 5.0
            dt *= static_cast<value_type>(9)/static_cast<value_type>(10) *
                  pow(error, static_cast<value_type>(-1) / stepper_order);
            if(m_max_dt != static_cast<time_type >(0))
                // limit to maximal stepsize
                dt = detail::min_abs(dt, m_max_dt);
        }
        return dt;
    }

    bool check_step_size_limit(const time_type dt)
    {
        if(m_max_dt != static_cast<time_type >(0))
            return detail::less_eq_with_sign(dt, m_max_dt, dt);
        return true;
    }

    time_type get_max_dt() { return m_max_dt; }

protected:
    time_type m_max_dt;
};



/*
 * error stepper category dispatcher
 */
template<
class ErrorStepper ,
class ErrorChecker = default_error_checker< typename ErrorStepper::value_type ,
    typename ErrorStepper::algebra_type ,
    typename ErrorStepper::operations_type > ,
class StepAdjuster = default_step_adjuster< typename ErrorStepper::value_type ,
    typename ErrorStepper::time_type > ,
class Resizer = typename ErrorStepper::resizer_type ,
class ErrorStepperCategory = typename ErrorStepper::stepper_category
>
class controlled_runge_kutta ;



/*
 * explicit stepper version
 *
 * this class introduces the following try_step overloads
    * try_step( sys , x , t , dt )
    * try_step( sys , x , dxdt , t , dt )
    * try_step( sys , in , t , out , dt )
    * try_step( sys , in , dxdt , t , out , dt )
 */
/**
 * \brief Implements step size control for Runge-Kutta steppers with error 
 * estimation.
 *
 * This class implements the step size control for standard Runge-Kutta 
 * steppers with error estimation.
 *
 * \tparam ErrorStepper The stepper type with error estimation, has to fulfill the ErrorStepper concept.
 * \tparam ErrorChecker The error checker
 * \tparam Resizer The resizer policy type.
 */
template<
class ErrorStepper,
class ErrorChecker,
class StepAdjuster,
class Resizer
>
class controlled_runge_kutta< ErrorStepper , ErrorChecker , StepAdjuster, Resizer ,
        explicit_error_stepper_tag >
{

public:

    typedef ErrorStepper stepper_type;
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;
    typedef typename stepper_type::algebra_type algebra_type;
    typedef typename stepper_type::operations_type operations_type;
    typedef Resizer resizer_type;
    typedef ErrorChecker error_checker_type;
    typedef StepAdjuster step_adjuster_type;
    typedef explicit_controlled_stepper_tag stepper_category;

#ifndef DOXYGEN_SKIP
    typedef typename stepper_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_type::wrapped_deriv_type wrapped_deriv_type;

    typedef controlled_runge_kutta< ErrorStepper , ErrorChecker , StepAdjuster ,
            Resizer , explicit_error_stepper_tag > controlled_stepper_type;
#endif //DOXYGEN_SKIP


    /**
     * \brief Constructs the controlled Runge-Kutta stepper.
     * \param error_checker An instance of the error checker.
     * \param stepper An instance of the underlying stepper.
     */
    controlled_runge_kutta(
            const error_checker_type &error_checker = error_checker_type( ) ,
            const step_adjuster_type &step_adjuster = step_adjuster_type() ,
            const stepper_type &stepper = stepper_type( )
    )
        : m_stepper(stepper), m_error_checker(error_checker) , m_step_adjuster(step_adjuster)
    { }



    /*
     * Version 1 : try_step( sys , x , t , dt )
     *
     * The overloads are needed to solve the forwarding problem
     */
    /**
     * \brief Tries to perform one step.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. Overwritten if 
     * the step is successful.
     * \param t The value of the time. Updated if the step is successful.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateInOut >
    controlled_step_result try_step( System system , StateInOut &x , time_type &t , time_type &dt )
    {
        return try_step_v1( system , x , t, dt );
    }

    /**
     * \brief Tries to perform one step. Solves the forwarding problem and 
     * allows for using boost range as state_type.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. Overwritten if 
     * the step is successful. Can be a boost range.
     * \param t The value of the time. Updated if the step is successful.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateInOut >
    controlled_step_result try_step( System system , const StateInOut &x , time_type &t , time_type &dt )
    {
        return try_step_v1( system , x , t, dt );
    }



    /*
     * Version 2 : try_step( sys , x , dxdt , t , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    /**
     * \brief Tries to perform one step.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. Overwritten if 
     * the step is successful.
     * \param dxdt The derivative of state.
     * \param t The value of the time. Updated if the step is successful.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateInOut , class DerivIn >
    controlled_step_result try_step( System system , StateInOut &x , const DerivIn &dxdt , time_type &t , time_type &dt )
    {
        m_xnew_resizer.adjust_size( x , detail::bind( &controlled_runge_kutta::template resize_m_xnew_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) );
        controlled_step_result res = try_step( system , x , dxdt , t , m_xnew.m_v , dt );
        if( res == success )
        {
            boost::numeric::odeint::copy( m_xnew.m_v , x );
        }
        return res;
    }

    /*
     * Version 3 : try_step( sys , in , t , out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     *
     * the disable is needed to avoid ambiguous overloads if state_type = time_type
     */
    /**
     * \brief Tries to perform one step.
     *
     * \note This method is disabled if state_type=time_type to avoid ambiguity.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved.
     * \param t The value of the time. Updated if the step is successful.
     * \param out Used to store the result of the step.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateIn , class StateOut >
    typename boost::disable_if< boost::is_same< StateIn , time_type > , controlled_step_result >::type
    try_step( System system , const StateIn &in , time_type &t , StateOut &out , time_type &dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_dxdt_resizer.adjust_size( in , detail::bind( &controlled_runge_kutta::template resize_m_dxdt_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );
        sys( in , m_dxdt.m_v , t );
        return try_step( system , in , m_dxdt.m_v , t , out , dt );
    }


    /*
     * Version 4 : try_step( sys , in , dxdt , t , out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    /**
     * \brief Tries to perform one step.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved.
     * \param dxdt The derivative of state.
     * \param t The value of the time. Updated if the step is successful.
     * \param out Used to store the result of the step.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateIn , class DerivIn , class StateOut >
    controlled_step_result try_step( System system , const StateIn &in , const DerivIn &dxdt , time_type &t , StateOut &out , time_type &dt )
    {
        unwrapped_step_adjuster &step_adjuster = m_step_adjuster;
        if( !step_adjuster.check_step_size_limit(dt) )
        {
            // given dt was above step size limit - adjust and return fail;
            dt = step_adjuster.get_max_dt();
            return fail;
        }

        m_xerr_resizer.adjust_size( in , detail::bind( &controlled_runge_kutta::template resize_m_xerr_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        // do one step with error calculation
        m_stepper.do_step( system , in , dxdt , t , out , dt , m_xerr.m_v );

        value_type max_rel_err = m_error_checker.error( m_stepper.algebra() , in , dxdt , m_xerr.m_v , dt );

        if( max_rel_err > 1.0 )
        {
            // error too big, decrease step size and reject this step
            dt = step_adjuster.decrease_step(dt, max_rel_err, m_stepper.error_order());
            return fail;
        } else
        {
            // otherwise, increase step size and accept
            t += dt;
            dt = step_adjuster.increase_step(dt, max_rel_err, m_stepper.stepper_order());
            return success;
        }
    }

    /**
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */
    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_m_xerr_impl( x );
        resize_m_dxdt_impl( x );
        resize_m_xnew_impl( x );
        m_stepper.adjust_size( x );
    }

    /**
     * \brief Returns the instance of the underlying stepper.
     * \returns The instance of the underlying stepper.
     */
    stepper_type& stepper( void )
    {
        return m_stepper;
    }

    /**
     * \brief Returns the instance of the underlying stepper.
     * \returns The instance of the underlying stepper.
     */
    const stepper_type& stepper( void ) const
    {
        return m_stepper;
    }

private:


    template< class System , class StateInOut >
    controlled_step_result try_step_v1( System system , StateInOut &x , time_type &t , time_type &dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_dxdt_resizer.adjust_size( x , detail::bind( &controlled_runge_kutta::template resize_m_dxdt_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) );
        sys( x , m_dxdt.m_v ,t );
        return try_step( system , x , m_dxdt.m_v , t , dt );
    }

    template< class StateIn >
    bool resize_m_xerr_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xerr , x , typename is_resizeable<state_type>::type() );
    }

    template< class StateIn >
    bool resize_m_dxdt_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }

    template< class StateIn >
    bool resize_m_xnew_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xnew , x , typename is_resizeable<state_type>::type() );
    }



    stepper_type m_stepper;
    error_checker_type m_error_checker;
    step_adjuster_type m_step_adjuster;
    typedef typename unwrap_reference< step_adjuster_type >::type unwrapped_step_adjuster;

    resizer_type m_dxdt_resizer;
    resizer_type m_xerr_resizer;
    resizer_type m_xnew_resizer;

    wrapped_deriv_type m_dxdt;
    wrapped_state_type m_xerr;
    wrapped_state_type m_xnew;
};










/*
 * explicit stepper fsal version
 *
 * the class introduces the following try_step overloads
    * try_step( sys , x , t , dt ) 
    * try_step( sys , in , t , out , dt )
    * try_step( sys , x , dxdt , t , dt )
    * try_step( sys , in , dxdt_in , t , out , dxdt_out , dt )
 */
/**
 * \brief Implements step size control for Runge-Kutta FSAL steppers with 
 * error estimation.
 *
 * This class implements the step size control for FSAL Runge-Kutta 
 * steppers with error estimation.
 *
 * \tparam ErrorStepper The stepper type with error estimation, has to fulfill the ErrorStepper concept.
 * \tparam ErrorChecker The error checker
 * \tparam Resizer The resizer policy type.
 */
template<
class ErrorStepper ,
class ErrorChecker ,
class StepAdjuster ,
class Resizer
>
class controlled_runge_kutta< ErrorStepper , ErrorChecker , StepAdjuster , Resizer , explicit_error_stepper_fsal_tag >
{

public:

    typedef ErrorStepper stepper_type;
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;
    typedef typename stepper_type::algebra_type algebra_type;
    typedef typename stepper_type::operations_type operations_type;
    typedef Resizer resizer_type;
    typedef ErrorChecker error_checker_type;
    typedef StepAdjuster step_adjuster_type;
    typedef explicit_controlled_stepper_fsal_tag stepper_category;

#ifndef DOXYGEN_SKIP
    typedef typename stepper_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_type::wrapped_deriv_type wrapped_deriv_type;

    typedef controlled_runge_kutta< ErrorStepper , ErrorChecker , StepAdjuster , Resizer , explicit_error_stepper_tag > controlled_stepper_type;
#endif // DOXYGEN_SKIP

    /**
     * \brief Constructs the controlled Runge-Kutta stepper.
     * \param error_checker An instance of the error checker.
     * \param stepper An instance of the underlying stepper.
     */
    controlled_runge_kutta(
            const error_checker_type &error_checker = error_checker_type() ,
            const step_adjuster_type &step_adjuster = step_adjuster_type() ,
            const stepper_type &stepper = stepper_type()
    )
    : m_stepper( stepper ) , m_error_checker( error_checker ) , m_step_adjuster(step_adjuster) , 
      m_first_call( true )
    { }

    /*
     * Version 1 : try_step( sys , x , t , dt )
     *
     * The two overloads are needed in order to solve the forwarding problem
     */
    /**
     * \brief Tries to perform one step.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. Overwritten if 
     * the step is successful.
     * \param t The value of the time. Updated if the step is successful.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateInOut >
    controlled_step_result try_step( System system , StateInOut &x , time_type &t , time_type &dt )
    {
        return try_step_v1( system , x , t , dt );
    }


    /**
     * \brief Tries to perform one step. Solves the forwarding problem and 
     * allows for using boost range as state_type.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. Overwritten if 
     * the step is successful. Can be a boost range.
     * \param t The value of the time. Updated if the step is successful.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateInOut >
    controlled_step_result try_step( System system , const StateInOut &x , time_type &t , time_type &dt )
    {
        return try_step_v1( system , x , t , dt );
    }



    /*
     * Version 2 : try_step( sys , in , t , out , dt );
     *
     * This version does not solve the forwarding problem, boost::range can not be used.
     * 
     * The disabler is needed to solve ambiguous overloads
     */
    /**
     * \brief Tries to perform one step.
     *
     * \note This method is disabled if state_type=time_type to avoid ambiguity.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved.
     * \param t The value of the time. Updated if the step is successful.
     * \param out Used to store the result of the step.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateIn , class StateOut >
    typename boost::disable_if< boost::is_same< StateIn , time_type > , controlled_step_result >::type
    try_step( System system , const StateIn &in , time_type &t , StateOut &out , time_type &dt )
    {
        if( m_dxdt_resizer.adjust_size( in , detail::bind( &controlled_runge_kutta::template resize_m_dxdt_impl< StateIn > , detail::ref( *this ) , detail::_1 ) ) || m_first_call )
        {
            initialize( system , in , t );
        }
        return try_step( system , in , m_dxdt.m_v , t , out , dt );
    }


    /*
     * Version 3 : try_step( sys , x , dxdt , t , dt )
     *
     * This version does not solve the forwarding problem, boost::range can not be used.
     */
    /**
     * \brief Tries to perform one step.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. Overwritten if 
     * the step is successful.
     * \param dxdt The derivative of state.
     * \param t The value of the time. Updated if the step is successful.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateInOut , class DerivInOut >
    controlled_step_result try_step( System system , StateInOut &x , DerivInOut &dxdt , time_type &t , time_type &dt )
    {
        m_xnew_resizer.adjust_size( x , detail::bind( &controlled_runge_kutta::template resize_m_xnew_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) );
        m_dxdt_new_resizer.adjust_size( x , detail::bind( &controlled_runge_kutta::template resize_m_dxdt_new_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) );
        controlled_step_result res = try_step( system , x , dxdt , t , m_xnew.m_v , m_dxdtnew.m_v , dt );
        if( res == success )
        {
            boost::numeric::odeint::copy( m_xnew.m_v , x );
            boost::numeric::odeint::copy( m_dxdtnew.m_v , dxdt );
        }
        return res;
    }


    /*
     * Version 4 : try_step( sys , in , dxdt_in , t , out , dxdt_out , dt )
     *
     * This version does not solve the forwarding problem, boost::range can not be used.
     */
    /**
     * \brief Tries to perform one step.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved.
     * \param dxdt The derivative of state.
     * \param t The value of the time. Updated if the step is successful.
     * \param out Used to store the result of the step.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */
    template< class System , class StateIn , class DerivIn , class StateOut , class DerivOut >
    controlled_step_result try_step( System system , const StateIn &in , const DerivIn &dxdt_in , time_type &t ,
            StateOut &out , DerivOut &dxdt_out , time_type &dt )
    {
        unwrapped_step_adjuster &step_adjuster = m_step_adjuster;
        if( !step_adjuster.check_step_size_limit(dt) )
        {
            // given dt was above step size limit - adjust and return fail;
            dt = step_adjuster.get_max_dt();
            return fail;
        }

        m_xerr_resizer.adjust_size( in , detail::bind( &controlled_runge_kutta::template resize_m_xerr_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        //fsal: m_stepper.get_dxdt( dxdt );
        //fsal: m_stepper.do_step( sys , x , dxdt , t , dt , m_x_err );
        m_stepper.do_step( system , in , dxdt_in , t , out , dxdt_out , dt , m_xerr.m_v );

        // this potentially overwrites m_x_err! (standard_error_checker does, at least)
        value_type max_rel_err = m_error_checker.error( m_stepper.algebra() , in , dxdt_in , m_xerr.m_v , dt );

        if( max_rel_err > 1.0 )
        {
            // error too big, decrease step size and reject this step
            dt = step_adjuster.decrease_step(dt, max_rel_err, m_stepper.error_order());
            return fail;
        }
        // otherwise, increase step size and accept
        t += dt;
        dt = step_adjuster.increase_step(dt, max_rel_err, m_stepper.stepper_order());
        return success;
    }


    /**
     * \brief Resets the internal state of the underlying FSAL stepper.
     */
    void reset( void )
    {
        m_first_call = true;
    }

    /**
     * \brief Initializes the internal state storing an internal copy of the derivative.
     *
     * \param deriv The initial derivative of the ODE.
     */
    template< class DerivIn >
    void initialize( const DerivIn &deriv )
    {
        boost::numeric::odeint::copy( deriv , m_dxdt.m_v );
        m_first_call = false;
    }

    /**
     * \brief Initializes the internal state storing an internal copy of the derivative.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The initial state of the ODE which should be solved.
     * \param t The initial time.
     */
    template< class System , class StateIn >
    void initialize( System system , const StateIn &x , time_type t )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        sys( x , m_dxdt.m_v , t );
        m_first_call = false;
    }

    /**
     * \brief Returns true if the stepper has been initialized, false otherwise.
     *
     * \return true, if the stepper has been initialized, false otherwise.
     */
    bool is_initialized( void ) const
    {
        return ! m_first_call;
    }


    /**
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */
    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_m_xerr_impl( x );
        resize_m_dxdt_impl( x );
        resize_m_dxdt_new_impl( x );
        resize_m_xnew_impl( x );
    }


    /**
     * \brief Returns the instance of the underlying stepper.
     * \returns The instance of the underlying stepper.
     */
    stepper_type& stepper( void )
    {
        return m_stepper;
    }

    /**
     * \brief Returns the instance of the underlying stepper.
     * \returns The instance of the underlying stepper.
     */
    const stepper_type& stepper( void ) const
    {
        return m_stepper;
    }



private:


    template< class StateIn >
    bool resize_m_xerr_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xerr , x , typename is_resizeable<state_type>::type() );
    }

    template< class StateIn >
    bool resize_m_dxdt_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }

    template< class StateIn >
    bool resize_m_dxdt_new_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdtnew , x , typename is_resizeable<deriv_type>::type() );
    }

    template< class StateIn >
    bool resize_m_xnew_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xnew , x , typename is_resizeable<state_type>::type() );
    }


    template< class System , class StateInOut >
    controlled_step_result try_step_v1( System system , StateInOut &x , time_type &t , time_type &dt )
    {
        if( m_dxdt_resizer.adjust_size( x , detail::bind( &controlled_runge_kutta::template resize_m_dxdt_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) ) || m_first_call )
        {
            initialize( system , x , t );
        }
        return try_step( system , x , m_dxdt.m_v , t , dt );
    }


    stepper_type m_stepper;
    error_checker_type m_error_checker;
    step_adjuster_type m_step_adjuster;
    typedef typename unwrap_reference< step_adjuster_type >::type unwrapped_step_adjuster;

    resizer_type m_dxdt_resizer;
    resizer_type m_xerr_resizer;
    resizer_type m_xnew_resizer;
    resizer_type m_dxdt_new_resizer;

    wrapped_deriv_type m_dxdt;
    wrapped_state_type m_xerr;
    wrapped_state_type m_xnew;
    wrapped_deriv_type m_dxdtnew;
    bool m_first_call;
};


/********** DOXYGEN **********/

/**** DEFAULT ERROR CHECKER ****/

/**
 * \class default_error_checker
 * \brief The default error checker to be used with Runge-Kutta error steppers
 *
 * This class provides the default mechanism to compare the error estimates 
 * reported by Runge-Kutta error steppers with user defined error bounds.
 * It is used by the controlled_runge_kutta steppers.
 *
 * \tparam Value The value type.
 * \tparam Time The time type.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 */

    /**
     * \fn default_error_checker( value_type eps_abs , value_type eps_rel , value_type a_x , value_type a_dxdt ,
     * time_type max_dt)
     * \brief Constructs the error checker.
     *
     * The error is calculated as follows: ???? 
     *
     * \param eps_abs Absolute tolerance level.
     * \param eps_rel Relative tolerance level.
     * \param a_x Factor for the weight of the state.
     * \param a_dxdt Factor for the weight of the derivative.
     * \param max_dt Maximum allowed step size.
     */
    
    /**
     * \fn error( const State &x_old , const Deriv &dxdt_old , Err &x_err , time_type dt ) const
     * \brief Calculates the error level.
     *
     * If the returned error level is greater than 1, the estimated error was
     * larger than the permitted error bounds and the step should be repeated
     * with a smaller step size.
     *
     * \param x_old State at the beginning of the step.
     * \param dxdt_old Derivative at the beginning of the step.
     * \param x_err Error estimate.
     * \param dt Time step.
     * \return error
     */

    /**
     * \fn error( algebra_type &algebra , const State &x_old , const Deriv &dxdt_old , Err &x_err , time_type dt ) const
     * \brief Calculates the error level using a given algebra.
     *
     * If the returned error level is greater than 1, the estimated error was
     * larger than the permitted error bounds and the step should be repeated
     * with a smaller step size.
     *
     * \param algebra The algebra used for calculation of the error.
     * \param x_old State at the beginning of the step.
     * \param dxdt_old Derivative at the beginning of the step.
     * \param x_err Error estimate.
     * \param dt Time step.
     * \return error
     */

    /**
     * \fn time_type decrease_step(const time_type dt, const value_type error, const int error_order)
     * \brief Returns a decreased step size based on the given error and order
     *
     * Calculates a new smaller step size based on the given error and its order.
     *
     * \param dt The old step size.
     * \param error The computed error estimate.
     * \param error_order The error order of the stepper.
     * \return dt_new The new, reduced step size.
     */

    /**
     * \fn time_type increase_step(const time_type dt, const value_type error, const int error_order)
     * \brief Returns an increased step size based on the given error and order.
     *
     * Calculates a new bigger step size based on the given error and its order. If max_dt != 0, the
     * new step size is limited to max_dt.
     *
     * \param dt The old step size.
     * \param error The computed error estimate.
     * \param error_order The order of the stepper.
     * \return dt_new The new, increased step size.
     */


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED

/* controlled_runge_kutta.hpp
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
*/