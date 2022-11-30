/*
 [auto_generated]
 boost/numeric/odeint/stepper/base/explicit_stepper_base.hpp

 [begin_description]
 Base class for all explicit Runge Kutta steppers.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2012 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_STEPPER_BASE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_STEPPER_BASE_HPP_INCLUDED


#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/stepper/base/algebra_stepper_base.hpp>

namespace boost {
namespace numeric {
namespace odeint {

/*
 * base class for explicit steppers
 * models the stepper concept
 *
 * this class provides the following overloads
    * do_step( sys , x , t , dt )
    * do_step( sys , in , t , out , dt )
    * do_step( sys , x , dxdt_in , t , dt )
    * do_step( sys , in , dxdt_in , t , out , dt )
 */

template<
class Stepper ,
unsigned short Order ,
class State ,
class Value ,
class Deriv ,
class Time ,
class Algebra ,
class Operations ,
class Resizer
>
class explicit_stepper_base : public algebra_stepper_base< Algebra , Operations >
{
public:

    #ifndef DOXYGEN_SKIP
    typedef explicit_stepper_base< Stepper , Order , State , Value , Deriv , Time , Algebra , Operations , Resizer > internal_stepper_base_type;
    #endif // DOXYGEN_SKIP


    typedef State state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;
    typedef Resizer resizer_type;
    typedef Stepper stepper_type;
    typedef stepper_tag stepper_category;
    typedef algebra_stepper_base< Algebra , Operations > algebra_stepper_base_type;
    typedef typename algebra_stepper_base_type::algebra_type algebra_type;
    typedef typename algebra_stepper_base_type::operations_type operations_type;
    typedef unsigned short order_type;

    #ifndef DOXYGEN_SKIP
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    #endif // DOXYGEN_SKIP


    static const order_type order_value = Order;


    explicit_stepper_base( const algebra_type &algebra = algebra_type() )
    : algebra_stepper_base_type( algebra )
    { }

    /**
     * \return Returns the order of the stepper.
     */
    order_type order( void ) const
    {
        return order_value;
    }


    /*
     * Version 1 : do_step( sys , x , t , dt )
     *
     * the two overloads are needed in order to solve the forwarding problem
     */
    template< class System , class StateInOut >
    void do_step( System system , StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }

    /**
     * \brief Second version to solve the forwarding problem, can be called with Boost.Range as StateInOut.
     */
    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }

    /*
     * Version 2 : do_step( sys , x , dxdt , t , dt )
     *
      * this version does not solve the forwarding problem, boost.range can not be used
     *
     * the disable is needed to avoid ambiguous overloads if state_type = time_type
     */
    template< class System , class StateInOut , class DerivIn >
    typename boost::disable_if< boost::is_same< DerivIn , time_type > , void >::type
    do_step( System system , StateInOut &x , const DerivIn &dxdt , time_type t , time_type dt )
    {
        this->stepper().do_step_impl( system , x , dxdt , t , x , dt );
    }


    /*
     * named Version 2: do_step_dxdt_impl( sys , in , dxdt , t , dt )
     *
     * this version is needed when this stepper is used for initializing 
     * multistep stepper like adams-bashforth. Hence we provide an explicitely
     * named version that is not disabled. Meant for internal use only.
     */
    template < class System, class StateInOut, class DerivIn >
    void do_step_dxdt_impl( System system, StateInOut &x, const DerivIn &dxdt,
                            time_type t, time_type dt )
    {
        this->stepper().do_step_impl( system , x , dxdt , t , x , dt );
    }


    /*
     * Version 3 : do_step( sys , in , t , out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( in , detail::bind( &internal_stepper_base_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
        sys( in , m_dxdt.m_v ,t );
        this->stepper().do_step_impl( system , in , m_dxdt.m_v , t , out , dt );
    }


    /*
     * Version 4 : do_step( sys , in , dxdt , t , out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        this->stepper().do_step_impl( system , in , dxdt , t , out , dt );
    }


    /*
     * named Version 4: do_step_dxdt_impl( sys , in , dxdt , t , out, dt )
     *
     * this version is needed when this stepper is used for initializing 
     * multistep stepper like adams-bashforth. Hence we provide an explicitely
     * named version. Meant for internal use only.
     */
    template < class System, class StateIn, class DerivIn, class StateOut >
    void do_step_dxdt_impl( System system, const StateIn &in,
                            const DerivIn &dxdt, time_type t, StateOut &out,
                            time_type dt )
    {
        this->stepper().do_step_impl( system , in , dxdt , t , out , dt );
    }

    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
    }

private:

    stepper_type& stepper( void )
    {
        return *static_cast< stepper_type* >( this );
    }

    const stepper_type& stepper( void ) const
    {
        return *static_cast< const stepper_type* >( this );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }


    template< class System , class StateInOut >
    void do_step_v1( System system , StateInOut &x , time_type t , time_type dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( x , detail::bind( &internal_stepper_base_type::template resize_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) );
        sys( x , m_dxdt.m_v ,t );
        this->stepper().do_step_impl( system , x , m_dxdt.m_v , t , x , dt );
    }


    resizer_type m_resizer;

protected:

    wrapped_deriv_type m_dxdt;
};


/******* DOXYGEN *********/

/**
 * \class explicit_stepper_base
 * \brief Base class for explicit steppers without step size control and without dense output.
 *
 * This class serves as the base class for all explicit steppers with algebra and operations.
 * Step size control and error estimation as well as dense output are not provided. explicit_stepper_base 
 * is used as the interface in a CRTP (currently recurring template pattern). In order to work 
 * correctly the parent class needs to have a method `do_step_impl( system , in , dxdt_in , t , out , dt )`. 
 * This is method is used by explicit_stepper_base. explicit_stepper_base derives from
 * algebra_stepper_base. An example how this class can be used is
 *
 * \code
 * template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resizer >
 * class custom_euler : public explicit_stepper_base< 1 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
 * {
 *  public:
 *     
 *     typedef explicit_stepper_base< 1 , State , Value , Deriv , Time , Algebra , Operations , Resizer > base_type;
 *
 *     custom_euler( const Algebra &algebra = Algebra() ) { }
 * 
 *     template< class Sys , class StateIn , class DerivIn , class StateOut >
 *     void do_step_impl( Sys sys , const StateIn &in , const DerivIn &dxdt , Time t , StateOut &out , Time dt )
 *     {
 *         m_algebra.for_each3( out , in , dxdt , Operations::scale_sum2< Value , Time >( 1.0 , dt );
 *     }
 *
 *     template< class State >
 *     void adjust_size( const State &x )
 *     {
 *         base_type::adjust_size( x );
 *     }
 * };
 * \endcode
 *
 * For the Stepper concept only the `do_step( sys , x , t , dt )` needs to be implemented. But this class
 * provides additional `do_step` variants since the stepper is explicit. These methods can be used to increase
 * the performance in some situation, for example if one needs to analyze `dxdt` during each step. In this case 
 * one can use 
 *
 * \code
 * sys( x , dxdt , t );
 * stepper.do_step( sys , x , dxdt , t , dt );  // the value of dxdt is used here
 * t += dt;
 * \endcode
 *
 * In detail explicit_stepper_base provides the following `do_step` variants
 *   - `do_step( sys , x , t , dt )` - The classical `do_step` method needed to fulfill the Stepper concept. The state is updated in-place.
 *      A type modelling a Boost.Range can be used for x.
 *   - `do_step( sys , in , t , out , dt )` - This method updates the state out-of-place, hence the result of the step is stored in `out`.
 *   - `do_step( sys , x , dxdt , t , dt )` - This method updates the state in-place, but the derivative at the point `t` must be
 *      explicitly passed in `dxdt`. For an example see the code snippet above.
 *   - `do_step( sys , in , dxdt , t , out , dt )` - This method update the state out-of-place and expects that the derivative at the point 
 *     `t` is explicitly passed in `dxdt`. It is a combination of the two `do_step` methods above.
 *
 * \note The system is always passed as value, which might result in poor performance if it contains data. In this case it can be used with `boost::ref`
 * or `std::ref`, for example `stepper.do_step( boost::ref( sys ) , x , t , dt );`
 *
 * \note The time `t` is not advanced by the stepper. This has to done manually, or by the appropriate `integrate` routines or `iterator`s.
 *
 * \tparam Stepper The stepper on which this class should work. It is used via CRTP, hence explicit_stepper_base
 * provides the interface for the Stepper.
 * \tparam Order The order of the stepper.
 * \tparam State The state type for the stepper.
 * \tparam Value The value type for the stepper. This should be a floating point type, like float,
 * double, or a multiprecision type. It must not necessary be the value_type of the State. For example
 * the State can be a `vector< complex< double > >` in this case the Value must be double.
 * The default value is double.
 * \tparam Deriv The type representing time derivatives of the state type. It is usually the same type as the
 * state type, only if used with Boost.Units both types differ.
 * \tparam Time The type representing the time. Usually the same type as the value type. When Boost.Units is
 * used, this type has usually a unit.
 * \tparam Algebra The algebra type which must fulfill the Algebra Concept.
 * \tparam Operations The type for the operations which must fulfill the Operations Concept.
 * \tparam Resizer The resizer policy class.
 */


    /**
     * \fn explicit_stepper_base::explicit_stepper_base( const algebra_type &algebra )
     * \brief Constructs a explicit_stepper_base class. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

    /**
     * \fn explicit_stepper_base::order_type order( void ) const
     * \return Returns the order of the stepper.
     */

    /**
     * \fn explicit_stepper_base::do_step( System system , StateInOut &x , time_type t , time_type dt )
     * \brief This method performs one step. It transforms the result in-place.
     *
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */


    /**
     * \fn explicit_stepper_base::do_step( System system , StateInOut &x , const DerivIn &dxdt , time_type t , time_type dt )

     * \brief The method performs one step. Additionally to the other method
     * the derivative of x is also passed to this method. It is supposed to be used in the following way:
     *
     * \code
     * sys( x , dxdt , t );
     * stepper.do_step( sys , x , dxdt , t , dt );
     * \endcode
     *
     * The result is updated in place in x. This method is disabled if Time and Deriv are of the same type. In this
     * case the method could not be distinguished from other `do_step` versions.
     * 
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    /**
     * \fn void explicit_stepper_base::do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
     * \brief The method performs one step. The state of the ODE is updated out-of-place.
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     */

    /**
     * \fn void explicit_stepper_base::do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief The method performs one step. The state of the ODE is updated out-of-place.
     * Furthermore, the derivative of x at t is passed to the stepper. 
     * It is supposed to be used in the following way:
     *
     * \code
     * sys( in , dxdt , t );
     * stepper.do_step( sys , in , dxdt , t , out , dt );
     * \endcode
     *
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     */

    /**
     * \fn void explicit_stepper_base::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

} // odeint
} // numeric
} // boost

#endif // BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_STEPPER_BASE_HPP_INCLUDED

/* explicit_stepper_base.hpp
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
*/