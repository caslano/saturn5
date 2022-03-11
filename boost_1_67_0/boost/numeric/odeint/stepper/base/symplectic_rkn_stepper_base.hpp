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