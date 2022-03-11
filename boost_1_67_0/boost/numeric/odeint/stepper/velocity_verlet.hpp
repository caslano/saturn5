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