/*
 [auto_generated]
 boost/numeric/odeint/stepper/adams_moulton.hpp

 [begin_description]
 Implementation of the Adams-Moulton method. This is method is not a real stepper, it is more a helper class
 which computes the corrector step in the Adams-Bashforth-Moulton method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED


#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4_classic.hpp>

#include <boost/numeric/odeint/stepper/detail/adams_moulton_call_algebra.hpp>
#include <boost/numeric/odeint/stepper/detail/adams_moulton_coefficients.hpp>
#include <boost/numeric/odeint/stepper/detail/rotating_buffer.hpp>




namespace boost {
namespace numeric {
namespace odeint {


/*
 * Static implicit Adams-Moulton multistep-solver without step size control and without dense output.
 */
template<
size_t Steps ,
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
class adams_moulton
{
private:


public :

    typedef State state_type;
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef Time time_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;

    typedef adams_moulton< Steps , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;

    static const size_t steps = Steps;

    typedef unsigned short order_type;
    static const order_type order_value = steps + 1;

    typedef detail::rotating_buffer< wrapped_deriv_type , steps > step_storage_type;

    adams_moulton( )
    : m_coefficients() , m_dxdt() , m_resizer() ,
      m_algebra_instance() , m_algebra( m_algebra_instance )
    { }

    adams_moulton( algebra_type &algebra )
    : m_coefficients() , m_dxdt() , m_resizer() ,
      m_algebra_instance() , m_algebra( algebra )
    { }

    adams_moulton& operator=( const adams_moulton &stepper )
    {
        m_dxdt = stepper.m_dxdt;
        m_resizer = stepper.m_resizer;
        m_algebra = stepper.m_algebra;
        return *this;
    }

    order_type order( void ) const { return order_value; }


    /*
     * Version 1 : do_step( system , x , t , dt , buf );
     *
     * solves the forwarding problem
     */
    template< class System , class StateInOut , class StateIn , class ABBuf >
    void do_step( System system , StateInOut &x , StateIn const & pred , time_type t , time_type dt , const ABBuf &buf )
    {
        do_step( system , x , pred , t , x , dt , buf );
    }

    template< class System , class StateInOut , class StateIn , class ABBuf >
    void do_step( System system , const StateInOut &x , StateIn const & pred , time_type t , time_type dt , const ABBuf &buf )
    {
        do_step( system , x , pred , t , x , dt , buf );
    }



    /*
     * Version 2 : do_step( system , in , t , out , dt , buf );
     *
     * solves the forwarding problem
     */
    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step( System system , const StateIn &in , const PredIn &pred , time_type t , StateOut &out , time_type dt , const ABBuf &buf )
    {
        do_step_impl( system , in , pred , t , out , dt , buf );
    }

    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step( System system , const StateIn &in , const PredIn &pred , time_type t , const StateOut &out , time_type dt , const ABBuf &buf )
    {
        do_step_impl( system , in , pred , t , out , dt , buf );
    }



    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }

    algebra_type& algebra()
    {   return m_algebra; }

    const algebra_type& algebra() const
    {   return m_algebra; }


private:


    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step_impl( System system , const StateIn &in , const PredIn &pred , time_type t , StateOut &out , time_type dt , const ABBuf &buf )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
        sys( pred , m_dxdt.m_v , t );
        detail::adams_moulton_call_algebra< steps , algebra_type , operations_type >()( m_algebra , in , out , m_dxdt.m_v , buf , m_coefficients , dt );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }


    const detail::adams_moulton_coefficients< value_type , steps > m_coefficients;
    wrapped_deriv_type m_dxdt;
    resizer_type m_resizer;

protected:

    algebra_type m_algebra_instance;
    algebra_type &m_algebra;
};




} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED

/* adams_moulton.hpp
7/r4b7rhK96F+069JHd5LSmeixVdNXk5L9MZ6yXzrTN+uGVt3odtDbrhlRP6QTpgbT4acyRdwOO7NVAtDZYXG+kDGPWLsTbbB7sywYtbEd7Dr9CvHO+qlujqrw+Jz6vB86j20em3SjnD9t3Ef4l9cvnUOJm9l8O0b0o9hD22U1uD5/rgSUdz8fpO2Nl1FU97orxnKsfjxQ1JCTvU2KZ15oxTvyuuf16hB02vJ+tPi9DSo13/zmxx6kw7b5ayxflH2+Oe8Y66q4fz9yuuNx5X1aFxFn5A65/gzeglxp5yllC/n52uu7CfHv6d95zCvPLCdms11Rq9+5k8HI33evLi9Lgfn4K1eofoe/aWD+Jq/kVeunwMDP5O/XSIsDeHd3dsNcYI/lJL19yPf3FCnXeMhwbaqD/v0Bk+q7HGtMMBWienGpgwy2uBJ0XXdeGDf7cVPn6pj8IP8avj8XZ6o8D3hEc7YHi84vztAnT+PPMrpI/2vizGFs/6HFwpvuNplvFwSR50lyPTe9G9H/m7Jv8kNf3js7OMb3xRWll/lXqLnIcZbdPQu/T5U3pgYFfaC1an5X328/NxmeGq+tubEI+U0MPcli9yq/qucOxzAt31SA2MucckMa5IE7TRl25R63qqd6zD0n5qoAPtMCHuu7Veyqu2g++INa+iT8L6dbUhxw6I6aBC9NO7zqbA2AW4pVOM/KvpWq/FecYtXDvXBmfRnlmDr8UAb781T562haPdaf99/LIH1n+cHDstP/Bq9nHWrIp8XQZP9RV39uCc4PdT+nm8nOJ3Tj7ZMy5r33NwC7nEXz5YxxqZ484b1jQKZum/iqihhu/CuTOwMq/83Emj65tO3tJjdscPV2nFdPTo13BpmZjtU2f6sz3iWWow7oSnIxvDTri+/yW6Y608s8aZ8pubHvDLMmp7rl56E40UQ197T7X64rBR3n3iM7TJz8F53ww4gjZc3xd/wpKv8MwJP4v+D3zsqz+FWweWWXNjmfKN2LQU97flzfdyEc7tw+P76vhMJ5j+G4xdHmhe507UQrXHahAnR4/gcX0Btw7DDRrl9TPwFm/sTO1auLMK/E8IO3ulpcNzy78KNNVU7xe7n2jHpXhwbh33yxiWZ7zFMfJPfpVbKH4Fadl69COMr2x+bb23xzF4q+67mf/KzrRF8P02i9Xvfa+tx1+73Xuw93Wx5l3pj95w+zl/sK/1oTtbyvd04jeZJzBmmTzyDNvg7JF6Nz11J/5rJtgPI0rCqHPHnffVI86hoQ/8Yr8iufrDHUvgz4blQS+hb71i/IPgY3l9p/2ceFWso/pM+dD8G8q5SeJnXUrC7sV/41uaJ50+dqDxjiiGT2DutfYRnp8VD/+evNZYYN/FG4EO4q2vUQ8+P6UaT/1beY6TCixR77zx09ZgTXHXnkUvvcILeJnOtceTwPp+clWfKa+2n3VNnLy6HL66KT7G/80onNxdjc6kLyfS4+9H6M3p/bRiDCMWzYIPHfB6JZqQnzjDmJvCpJdjYP8Ae7ri9j6v6Gbw3GQuPQWumSh/5hWlidPQl3k881JdDzJVDOnDFHRObXmVqDj8PKFnrOTnqXgSMGFsG7poCJ/JNd60Pn2O07o55XX8wLOCT/rOvi+ptVz4SB8VcUtv4Jrb3pEro3BIYdhLB6bGA3nk0xd71YmcP58Vz+qp0maP4HnTjHhxCc7o1iUU+31F77XjvTY1Bphbip/zjbGVyYq7b/KmafDOy8K0k16WPtn5HM5toAdhxYQdNArMf3LMuhdTp+adn6d+I55a51V1rAfnrFFoLAyRL+nPyoti6lsMa1QWA3E8QnOk7047xOMH4skSr0XgYtwL72rCqFM=
*/