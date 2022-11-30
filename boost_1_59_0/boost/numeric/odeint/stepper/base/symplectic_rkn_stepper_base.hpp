/*
 [auto_generated]
 boost/numeric/odeint/stepper/base/symplectic_rkn_stepper_base.hpp

 [begin_description]
 Base class for symplectic Runge-Kutta-Nystrom steppers.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_BASE_SYMPLECTIC_RKN_STEPPER_BASE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_BASE_SYMPLECTIC_RKN_STEPPER_BASE_HPP_INCLUDED

#include <boost/array.hpp>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>

#include <boost/numeric/odeint/util/copy.hpp>
#include <boost/numeric/odeint/util/is_pair.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/stepper/base/algebra_stepper_base.hpp>




namespace boost {
namespace numeric {
namespace odeint {


template<
size_t NumOfStages ,
unsigned short Order ,
class Coor ,
class Momentum ,
class Value ,
class CoorDeriv ,
class MomentumDeriv ,
class Time ,
class Algebra ,
class Operations ,
class Resizer
>
class symplectic_nystroem_stepper_base : public algebra_stepper_base< Algebra , Operations >
{

public:

    typedef algebra_stepper_base< Algebra , Operations > algebra_stepper_base_type;
    typedef typename algebra_stepper_base_type::algebra_type algebra_type;
    typedef typename algebra_stepper_base_type::operations_type operations_type;

    const static size_t num_of_stages = NumOfStages;
    typedef Coor coor_type;
    typedef Momentum momentum_type;
    typedef std::pair< coor_type , momentum_type > state_type;
    typedef CoorDeriv coor_deriv_type;
    typedef state_wrapper< coor_deriv_type> wrapped_coor_deriv_type;
    typedef MomentumDeriv momentum_deriv_type;
    typedef state_wrapper< momentum_deriv_type > wrapped_momentum_deriv_type;
    typedef std::pair< coor_deriv_type , momentum_deriv_type > deriv_type;
    typedef Value value_type;
    typedef Time time_type;
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;
    
    #ifndef DOXYGEN_SKIP
    typedef symplectic_nystroem_stepper_base< NumOfStages , Order , Coor , Momentum , Value ,
            CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer > internal_stepper_base_type;
    #endif 
    typedef unsigned short order_type;

    static const order_type order_value = Order;

    typedef boost::array< value_type , num_of_stages > coef_type;

    symplectic_nystroem_stepper_base( const coef_type &coef_a , const coef_type &coef_b , const algebra_type &algebra = algebra_type() )
        : algebra_stepper_base_type( algebra ) , m_coef_a( coef_a ) , m_coef_b( coef_b ) ,
          m_dqdt_resizer() , m_dpdt_resizer() , m_dqdt() , m_dpdt() 
    { }


    order_type order( void ) const
    {
        return order_value;
    }

    /*
     * Version 1 : do_step( system , x , t , dt )
     *
     * This version does not solve the forwarding problem, boost.range can not be used.
     */
    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &state , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        do_step_impl( system , state , t , state , dt , typename is_pair< system_type >::type() );
    }

    /**
     * \brief Same function as above. It differs only in a different const specifier in order
     * to solve the forwarding problem, can be used with Boost.Range.
     */
    template< class System , class StateInOut >
    void do_step( System system , StateInOut &state , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        do_step_impl( system , state , t , state , dt , typename is_pair< system_type >::type() );
    }




    /*
     * Version 2 : do_step( system , q , p , t , dt );
     *
     * For Convenience
     *
     * The two overloads are needed in order to solve the forwarding problem.
     */
    template< class System , class CoorInOut , class MomentumInOut >
    void do_step( System system , CoorInOut &q , MomentumInOut &p , time_type t , time_type dt )
    {
        do_step( system , std::make_pair( detail::ref( q ) , detail::ref( p ) ) , t , dt );
    }

    /**
     * \brief Same function as do_step( system , q , p , t , dt ). It differs only in a different const specifier in order
     * to solve the forwarding problem, can be called with Boost.Range.
     */
    template< class System , class CoorInOut , class MomentumInOut >
    void do_step( System system , const CoorInOut &q , const MomentumInOut &p , time_type t , time_type dt )
    {
        do_step( system , std::make_pair( detail::ref( q ) , detail::ref( p ) ) , t , dt );
    }





    /*
     * Version 3 : do_step( system , in , t , out , dt )
     *
     * The forwarding problem is not solved in this version
     */
    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        do_step_impl( system , in , t , out , dt , typename is_pair< system_type >::type() );
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_dqdt( x );
        resize_dpdt( x );
    }

    /** \brief Returns the coefficients a. */
    const coef_type& coef_a( void ) const { return m_coef_a; }

    /** \brief Returns the coefficients b. */
    const coef_type& coef_b( void ) const { return m_coef_b; }

private:

    // stepper for systems with function for dq/dt = f(p) and dp/dt = -f(q)
    template< class System , class StateIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , time_type /* t */ , StateOut &out , time_type dt , boost::mpl::true_ )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        typedef typename odeint::unwrap_reference< typename system_type::first_type >::type coor_deriv_func_type;
        typedef typename odeint::unwrap_reference< typename system_type::second_type >::type momentum_deriv_func_type;
        system_type &sys = system;
        coor_deriv_func_type &coor_func = sys.first;
        momentum_deriv_func_type &momentum_func = sys.second;

        typedef typename odeint::unwrap_reference< StateIn >::type state_in_type;
        typedef typename odeint::unwrap_reference< typename state_in_type::first_type >::type coor_in_type;
        typedef typename odeint::unwrap_reference< typename state_in_type::second_type >::type momentum_in_type;
        const state_in_type &state_in = in;
        const coor_in_type &coor_in = state_in.first;
        const momentum_in_type &momentum_in = state_in.second;

        typedef typename odeint::unwrap_reference< StateOut >::type state_out_type;
        typedef typename odeint::unwrap_reference< typename state_out_type::first_type >::type coor_out_type;
        typedef typename odeint::unwrap_reference< typename state_out_type::second_type >::type momentum_out_type;
        state_out_type &state_out = out;
        coor_out_type &coor_out = state_out.first;
        momentum_out_type &momentum_out = state_out.second;

        m_dqdt_resizer.adjust_size( coor_in , detail::bind( &internal_stepper_base_type::template resize_dqdt< coor_in_type > , detail::ref( *this ) , detail::_1 ) );
        m_dpdt_resizer.adjust_size( momentum_in , detail::bind( &internal_stepper_base_type::template resize_dpdt< momentum_in_type > , detail::ref( *this ) , detail::_1 ) );

        // ToDo: check sizes?

        for( size_t l=0 ; l<num_of_stages ; ++l )
        {
            if( l == 0 )
            {
                coor_func( momentum_in , m_dqdt.m_v );
                this->m_algebra.for_each3( coor_out , coor_in , m_dqdt.m_v ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_a[l] * dt ) );
                momentum_func( coor_out , m_dpdt.m_v );
                this->m_algebra.for_each3( momentum_out , momentum_in , m_dpdt.m_v ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_b[l] * dt ) );
            }
            else
            {
                coor_func( momentum_out , m_dqdt.m_v );
                this->m_algebra.for_each3( coor_out , coor_out , m_dqdt.m_v ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_a[l] * dt ) );
                momentum_func( coor_out , m_dpdt.m_v );
                this->m_algebra.for_each3( momentum_out , momentum_out , m_dpdt.m_v ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_b[l] * dt ) );
            }
        }
    }


    // stepper for systems with only function dp /dt = -f(q), dq/dt = p, time not required but still expected for compatibility reasons
    template< class System , class StateIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , time_type  /* t */ , StateOut &out , time_type dt , boost::mpl::false_ )
    {
        typedef typename odeint::unwrap_reference< System >::type momentum_deriv_func_type;
        momentum_deriv_func_type &momentum_func = system;

        typedef typename odeint::unwrap_reference< StateIn >::type state_in_type;
        typedef typename odeint::unwrap_reference< typename state_in_type::first_type >::type coor_in_type;
        typedef typename odeint::unwrap_reference< typename state_in_type::second_type >::type momentum_in_type;
        const state_in_type &state_in = in;
        const coor_in_type &coor_in = state_in.first;
        const momentum_in_type &momentum_in = state_in.second;

        typedef typename odeint::unwrap_reference< StateOut >::type state_out_type;
        typedef typename odeint::unwrap_reference< typename state_out_type::first_type >::type coor_out_type;
        typedef typename odeint::unwrap_reference< typename state_out_type::second_type >::type momentum_out_type;
        state_out_type &state_out = out;
        coor_out_type &coor_out = state_out.first;
        momentum_out_type &momentum_out = state_out.second;


        // m_dqdt not required when called with momentum_func only - don't resize
        // m_dqdt_resizer.adjust_size( coor_in , detail::bind( &internal_stepper_base_type::template resize_dqdt< coor_in_type > , detail::ref( *this ) , detail::_1 ) );
        m_dpdt_resizer.adjust_size( momentum_in , detail::bind( &internal_stepper_base_type::template resize_dpdt< momentum_in_type > , detail::ref( *this ) , detail::_1 ) );


        // ToDo: check sizes?

        // step 0
        this->m_algebra.for_each3( coor_out  , coor_in , momentum_in ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_a[0] * dt ) );
        momentum_func( coor_out , m_dpdt.m_v );
        this->m_algebra.for_each3( momentum_out , momentum_in , m_dpdt.m_v ,
                                           typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_b[0] * dt ) );

        for( size_t l=1 ; l<num_of_stages ; ++l )
        {
            this->m_algebra.for_each3( coor_out , coor_out , momentum_out ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_a[l] * dt ) );
            momentum_func( coor_out , m_dpdt.m_v );
            this->m_algebra.for_each3( momentum_out , momentum_out , m_dpdt.m_v ,
                                       typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_b[l] * dt ) );
        }
    }

    template< class StateIn >
    bool resize_dqdt( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dqdt , x , typename is_resizeable<coor_deriv_type>::type() );
    }

    template< class StateIn >
    bool resize_dpdt( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dpdt , x , typename is_resizeable<momentum_deriv_type>::type() );
    }


    const coef_type m_coef_a;
    const coef_type m_coef_b;

    resizer_type m_dqdt_resizer;
    resizer_type m_dpdt_resizer;
    wrapped_coor_deriv_type m_dqdt;
    wrapped_momentum_deriv_type m_dpdt;

};

/********* DOXYGEN *********/

/**
 * \class symplectic_nystroem_stepper_base
 * \brief Base class for all symplectic steppers of Nystroem type.
 *
 * This class is the base class for the symplectic Runge-Kutta-Nystroem steppers. Symplectic steppers are usually
 * used to solve Hamiltonian systems and they conserve the phase space volume, see
 * <a href="http://en.wikipedia.org/wiki/Symplectic_integrator">en.wikipedia.org/wiki/Symplectic_integrator</a>. 
 * Furthermore, the energy is conserved
 * in average. In detail this class of steppers can be used to solve separable Hamiltonian systems which can be written
 * in the form H(q,p) = H1(p) + H2(q). q is usually called the coordinate, while p is the momentum. The equations of motion
 * are dq/dt = dH1/dp, dp/dt = -dH2/dq.
 *
 * ToDo : add formula for solver and explanation of the coefficients
 * 
 * symplectic_nystroem_stepper_base uses odeints algebra and operation system. Step size and error estimation are not
 * provided for this class of solvers. It derives from algebra_stepper_base. Several `do_step` variants are provided:
 *
 * - `do_step( sys , x , t , dt )` - The classical `do_step` method. The sys can be either a pair of function objects
 *    for the coordinate or the momentum part or one function object for the momentum part. `x` is a pair of coordinate
 *    and momentum. The state is updated in-place.
 * - `do_step( sys , q , p , t , dt )` - This method is similar to the method above with the difference that the coordinate
 *    and the momentum are passed explicitly and not packed into a pair.
 * - `do_step( sys , x_in , t , x_out , dt )` - This method transforms the state out-of-place. `x_in` and `x_out` are here pairs
 *    of coordinate and momentum.
 *
 * \tparam NumOfStages Number of stages.
 * \tparam Order The order of the stepper.
 * \tparam Coor The type representing the coordinates q.
 * \tparam Momentum The type representing the coordinates p.
 * \tparam Value The basic value type. Should be something like float, double or a high-precision type.
 * \tparam CoorDeriv The type representing the time derivative of the coordinate dq/dt.
 * \tparam MomemtnumDeriv The type representing the time derivative of the momentum dp/dt.
 * \tparam Time The type representing the time t.
 * \tparam Algebra The algebra.
 * \tparam Operations The operations.
 * \tparam Resizer The resizer policy.
 */

    /**
     * \fn symplectic_nystroem_stepper_base::symplectic_nystroem_stepper_base( const coef_type &coef_a , const coef_type &coef_b , const algebra_type &algebra )
     * \brief Constructs a symplectic_nystroem_stepper_base class. The parameters of the specific Nystroem method and the
     * algebra have to be passed.
     * \param coef_a The coefficients a.
     * \param coef_b The coefficients b.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

    /**
     * \fn symplectic_nystroem_stepper_base::order( void ) const
     * \return Returns the order of the stepper.
     */

    /**
     * \fn symplectic_nystroem_stepper_base::do_step( System system , const StateInOut &state , time_type t , time_type dt )
     * \brief This method performs one step. The system can be either a pair of two function object
     * describing the momentum part and the coordinate part or one function object describing only
     * the momentum part. In this case the coordinate is assumed to be trivial dq/dt = p. The state
     * is updated in-place.
     *
     * \note boost::ref or std::ref can be used for the system as well as for the state. So, it is correct
     * to write `stepper.do_step( make_pair( std::ref( fq ) , std::ref( fp ) ) , make_pair( std::ref( q ) , std::ref( p ) ) , t , dt )`.
     *
     * \note This method solves the forwarding problem.
     *
     * \param system The system, can be represented as a pair of two function object or one function object. See above.
     * \param state The state of the ODE. It is a pair of Coor and Momentum. The state is updated in-place, therefore, the
     * new value of the state will be written into this variable.
     * \param t The time of the ODE. It is not advanced by this method.
     * \param dt The time step.
     */

    /**
     * \fn symplectic_nystroem_stepper_base::do_step( System system , CoorInOut &q , MomentumInOut &p , time_type t , time_type dt )
     * \brief This method performs one step. The system can be either a pair of two function object
     * describing the momentum part and the coordinate part or one function object describing only
     * the momentum part. In this case the coordinate is assumed to be trivial dq/dt = p. The state
     * is updated in-place.
     *
     * \note boost::ref or std::ref can be used for the system. So, it is correct
     * to write `stepper.do_step( make_pair( std::ref( fq ) , std::ref( fp ) ) , q , p , t , dt )`.
     *
     * \note This method solves the forwarding problem.
     *
     * \param system The system, can be represented as a pair of two function object or one function object. See above.
     * \param q The coordinate of the ODE. It is updated in-place. Therefore, the new value of the coordinate will be written
     * into this variable.
     * \param p The momentum of the ODE. It is updated in-place. Therefore, the new value of the momentum will be written info
     * this variable.
     * \param t The time of the ODE. It is not advanced by this method.
     * \param dt The time step.
     */

    /**
     * \fn symplectic_nystroem_stepper_base::do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The system can be either a pair of two function object
     * describing the momentum part and the coordinate part or one function object describing only
     * the momentum part. In this case the coordinate is assumed to be trivial dq/dt = p. The state
     * is updated out-of-place.
     *
     * \note boost::ref or std::ref can be used for the system. So, it is correct
     * to write `stepper.do_step( make_pair( std::ref( fq ) , std::ref( fp ) ) , x_in , t , x_out , dt )`.
     *
     * \note This method NOT solve the forwarding problem.
     *
     * \param system The system, can be represented as a pair of two function object or one function object. See above.
     * \param in The state of the ODE, which is a pair of coordinate and momentum. The state is updated out-of-place, therefore the 
     * new value is written into out
     * \param t The time of the ODE. It is not advanced by this method.
     * \param out The new state of the ODE.
     * \param dt The time step.
     */

    /**
     * \fn symplectic_nystroem_stepper_base::adjust_size( const StateType &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_BASE_SYMPLECTIC_RKN_STEPPER_BASE_HPP_INCLUDED

/* symplectic_rkn_stepper_base.hpp
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
*/