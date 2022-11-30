/*
  [auto_generated]
  boost/numeric/odeint/stepper/velocity_verlet.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_VELOCITY_VERLET_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_STEPPER_VELOCITY_VERLET_HPP_DEFINED

#include <boost/numeric/odeint/stepper/base/algebra_stepper_base.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/copy.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
// #include <boost/numeric/odeint/util/is_pair.hpp>
// #include <boost/array.hpp>



namespace boost {
namespace numeric {
namespace odeint {



template <
    class Coor ,
    class Velocity = Coor ,
    class Value = double ,
    class Acceleration = Coor ,
    class Time = Value ,
    class TimeSq = Time ,
    class Algebra = typename algebra_dispatcher< Coor >::algebra_type ,
    class Operations = typename operations_dispatcher< Coor >::operations_type ,
    class Resizer = initially_resizer
      >
class velocity_verlet : public algebra_stepper_base< Algebra , Operations >
{
public:

    typedef algebra_stepper_base< Algebra , Operations > algebra_stepper_base_type;
    typedef typename algebra_stepper_base_type::algebra_type algebra_type;
    typedef typename algebra_stepper_base_type::operations_type operations_type;

    typedef Coor coor_type;
    typedef Velocity velocity_type;
    typedef Acceleration acceleration_type;
    typedef std::pair< coor_type , velocity_type > state_type;
    typedef std::pair< velocity_type , acceleration_type > deriv_type;
    typedef state_wrapper< acceleration_type > wrapped_acceleration_type;
    typedef Value value_type;
    typedef Time time_type;
    typedef TimeSq time_square_type;
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;

    typedef unsigned short order_type;

    static const order_type order_value = 1;

    /**
     * \return Returns the order of the stepper.
     */
    order_type order( void ) const
    {
        return order_value;
    }


    velocity_verlet( const algebra_type & algebra = algebra_type() )
        : algebra_stepper_base_type( algebra ) , m_first_call( true )
        , m_a1() , m_a2() , m_current_a1( true ) { }


    template< class System , class StateInOut >
    void do_step( System system , StateInOut & x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }

    
    template< class System , class StateInOut >
    void do_step( System system , const StateInOut & x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }

    
    template< class System , class CoorIn , class VelocityIn , class AccelerationIn ,
                             class CoorOut , class VelocityOut , class AccelerationOut >
    void do_step( System system , CoorIn const & qin , VelocityIn const & pin , AccelerationIn const & ain ,
                  CoorOut & qout , VelocityOut & pout , AccelerationOut & aout , time_type t , time_type dt )
    {
        const value_type one = static_cast< value_type >( 1.0 );
        const value_type one_half = static_cast< value_type >( 0.5 );

        algebra_stepper_base_type::m_algebra.for_each4(
            qout , qin , pin , ain ,
            typename operations_type::template scale_sum3< value_type , time_type , time_square_type >( one , one * dt , one_half * dt * dt ) );

        typename odeint::unwrap_reference< System >::type & sys = system;

        sys( qout , pin , aout , t + dt );

        algebra_stepper_base_type::m_algebra.for_each4(
            pout , pin , ain , aout ,
            typename operations_type::template scale_sum3< value_type , time_type , time_type >( one , one_half * dt , one_half * dt ) );
    }


    template< class StateIn >
    void adjust_size( const StateIn & x )
    {
        if( resize_impl( x ) )
            m_first_call = true;
    }

    void reset( void )
    {
        m_first_call = true;
    }

    
    /**
     * \fn velocity_verlet::initialize( const AccelerationIn &qin )
     * \brief Initializes the internal state of the stepper.
     * \param deriv The acceleration of x. The next call of `do_step` expects that the acceleration of `x` passed to `do_step`
     *              has the value of `qin`.
     */
    template< class AccelerationIn >
    void initialize( const AccelerationIn & ain )
    {
        // alloc a
        m_resizer.adjust_size( ain ,
                               detail::bind( &velocity_verlet::template resize_impl< AccelerationIn > ,
                                             detail::ref( *this ) , detail::_1 ) );
        boost::numeric::odeint::copy( ain , get_current_acc() );
        m_first_call = false;
    }


    template< class System , class CoorIn , class VelocityIn >
    void initialize( System system , const CoorIn & qin , const VelocityIn & pin , time_type t )
    {
        m_resizer.adjust_size( qin ,
                               detail::bind( &velocity_verlet::template resize_impl< CoorIn > ,
                                             detail::ref( *this ) , detail::_1 ) );
        initialize_acc( system , qin , pin , t );
    }

    bool is_initialized( void ) const
    {
        return ! m_first_call;
    }


private:
    
    template< class System , class CoorIn , class VelocityIn >
    void initialize_acc( System system , const CoorIn & qin , const VelocityIn & pin , time_type t )
    {
        typename odeint::unwrap_reference< System >::type & sys = system;
        sys( qin , pin , get_current_acc() , t );
        m_first_call = false;
    }
    
    template< class System , class StateInOut >
    void do_step_v1( System system , StateInOut & x , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< StateInOut >::type state_in_type;
        typedef typename odeint::unwrap_reference< typename state_in_type::first_type >::type coor_in_type;
        typedef typename odeint::unwrap_reference< typename state_in_type::second_type >::type momentum_in_type;
        
        typedef typename boost::remove_reference< coor_in_type >::type xyz_type;
        state_in_type & statein = x;
        coor_in_type & qinout = statein.first;
        momentum_in_type & pinout = statein.second;

        // alloc a
        if( m_resizer.adjust_size( qinout ,
                                   detail::bind( &velocity_verlet::template resize_impl< xyz_type > ,
                                                 detail::ref( *this ) , detail::_1 ) )
         || m_first_call )
        {
            initialize_acc( system , qinout , pinout , t );
        }

        // check first
        do_step( system , qinout , pinout , get_current_acc() , qinout , pinout , get_old_acc() , t , dt );
        toggle_current_acc();
    }

    template< class StateIn >
    bool resize_impl( const StateIn & x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_a1 , x , typename is_resizeable< acceleration_type >::type() );
        resized |= adjust_size_by_resizeability( m_a2 , x , typename is_resizeable< acceleration_type >::type() );
        return resized;
    }

    acceleration_type & get_current_acc( void )
    {
        return m_current_a1 ? m_a1.m_v : m_a2.m_v ;
    }

    const acceleration_type & get_current_acc( void ) const
    {
        return m_current_a1 ? m_a1.m_v : m_a2.m_v ;
    }

    acceleration_type & get_old_acc( void )
    {
        return m_current_a1 ? m_a2.m_v : m_a1.m_v ;
    }

    const acceleration_type & get_old_acc( void ) const
    {
        return m_current_a1 ? m_a2.m_v : m_a1.m_v ;
    }

    void toggle_current_acc( void )
    {
        m_current_a1 = ! m_current_a1;
    }

    resizer_type m_resizer;
    bool m_first_call;
    wrapped_acceleration_type m_a1 , m_a2;
    bool m_current_a1;
};

/**
 * \class velocity_verlet
 * \brief The Velocity-Verlet algorithm.
 *
 * <a href="http://en.wikipedia.org/wiki/Verlet_integration" >The Velocity-Verlet algorithm</a> is a method for simulation of molecular dynamics systems. It solves the ODE
 * a=f(r,v',t)  where r are the coordinates, v are the velocities and a are the accelerations, hence v = dr/dt, a=dv/dt.
 * 
 * \tparam Coor The type representing the coordinates.
 * \tparam Velocity The type representing the velocities.
 * \tparam Value The type value type.
 * \tparam Acceleration The type representing the acceleration.
 * \tparam Time The time representing the independent variable - the time.
 * \tparam TimeSq The time representing the square of the time.
 * \tparam Algebra The algebra.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 */


    /**
     * \fn velocity_verlet::velocity_verlet( const algebra_type &algebra )
     * \brief Constructs the velocity_verlet class. This constructor can be used as a default
     * constructor if the algebra has a default constructor. 
     * \param algebra A copy of algebra is made and stored.
     */

    
    /**
     * \fn velocity_verlet::do_step( System system , StateInOut &x , time_type t , time_type dt )
     * \brief This method performs one step. It transforms the result in-place.
     * 
     * It can be used like
     * \code
     * pair< coordinates , velocities > state;
     * stepper.do_step( sys , x , t , dt );
     * \endcode
     *
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Second Order System concept.
     * \param x The state of the ODE which should be solved. The state is pair of Coor and Velocity.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    /**
     * \fn velocity_verlet::do_step( System system , const StateInOut &x , time_type t , time_type dt )
     * \brief This method performs one step. It transforms the result in-place.
     * 
     * It can be used like
     * \code
     * pair< coordinates , velocities > state;
     * stepper.do_step( sys , x , t , dt );
     * \endcode
     *
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Second Order System concept.
     * \param x The state of the ODE which should be solved. The state is pair of Coor and Velocity.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */    

    

    /**
     * \fn velocity_verlet::do_step( System system , CoorIn const & qin , VelocityIn const & pin , AccelerationIn const & ain , CoorOut & qout , VelocityOut & pout , AccelerationOut & aout , time_type t , time_type dt )
     * \brief This method performs one step. It transforms the result in-place. Additionally to the other methods
     * the coordinates, velocities and accelerations are passed directly to do_step and they are transformed out-of-place.
     * 
     * It can be used like
     * \code
     * coordinates qin , qout;
     * velocities pin , pout;
     * accelerations ain, aout;
     * stepper.do_step( sys , qin , pin , ain , qout , pout , aout , t , dt );
     * \endcode
     *
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Second Order System concept.
     * \param x The state of the ODE which should be solved. The state is pair of Coor and Velocity.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    
    /**
     * \fn void velocity_verlet::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */


    /**
     * \fn velocity_verlet::reset( void )
     * \brief Resets the internal state of this stepper. After calling this method it is safe to use all
     * `do_step` method without explicitly initializing the stepper.
     */

    

    /**
     * \fn velocity_verlet::initialize( System system , const CoorIn &qin , const VelocityIn &pin , time_type t )
     * \brief Initializes the internal state of the stepper.
     *
     * This method is equivalent to 
     * \code
     * Acceleration a;
     * system( qin , pin , a , t );
     * stepper.initialize( a );
     * \endcode
     *
     * \param system The system function for the next calls of `do_step`.
     * \param qin The current coordinates of the ODE.
     * \param pin The current velocities of the ODE.
     * \param t The current time of the ODE.
     */
    
    
    /**
     * \fn velocity_verlet::is_initialized()
     * \returns Returns if the stepper is initialized.
    */
    
    
    
    
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_VELOCITY_VERLET_HPP_DEFINED

/* velocity_verlet.hpp
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
*/