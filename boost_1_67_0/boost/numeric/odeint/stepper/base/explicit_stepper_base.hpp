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