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