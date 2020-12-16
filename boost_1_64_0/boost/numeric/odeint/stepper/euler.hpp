/*
 [auto_generated]
 boost/numeric/odeint/stepper/euler.hpp

 [begin_description]
 Implementation of the classical explicit Euler stepper. This method is really simple and should only
 be used for demonstration purposes.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_EULER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_EULER_HPP_INCLUDED


#include <boost/numeric/odeint/stepper/base/explicit_stepper_base.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template<
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
#ifndef DOXYGEN_SKIP
class euler
: public explicit_stepper_base<
  euler< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
  1 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
class euler : public explicit_stepper_base
#endif
{
public :

    #ifndef DOXYGEN_SKIP
    typedef explicit_stepper_base< euler< State , Value , Deriv , Time , Algebra , Operations , Resizer > , 1 , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_base_type;
    #else
    typedef explicit_stepper_base< euler< ... > , ... > stepper_base_type;
    #endif
    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;

    #ifndef DOXYGEN_SKIP
    typedef typename stepper_base_type::stepper_type stepper_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    #endif 


    euler( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }

    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System /* system */ , const StateIn &in , const DerivIn &dxdt , time_type /* t */ , StateOut &out , time_type dt )
    {
        stepper_base_type::m_algebra.for_each3( out , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt ) );

    }

    template< class StateOut , class StateIn1 , class StateIn2 >
    void calc_state( StateOut &x , time_type t ,  const StateIn1 &old_state , time_type t_old , const StateIn2 & /*current_state*/ , time_type /* t_new */ ) const
    {
        const time_type delta = t - t_old;
        stepper_base_type::m_algebra.for_each3( x , old_state , stepper_base_type::m_dxdt.m_v ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , delta ) );
    }

    template< class StateType >
    void adjust_size( const StateType &x )
    {
        stepper_base_type::adjust_size( x );
    }
};



/********** DOXYGEN ***********/

/**
 * \class euler
 * \brief An implementation of the Euler method.
 *
 * The Euler method is a very simply solver for ordinary differential equations. This method should not be used
 * for real applications. It is only useful for demonstration purposes. Step size control is not provided but
 * trivial continuous output is available.
 * 
 * This class derives from explicit_stepper_base and inherits its interface via CRTP (current recurring template pattern),
 * see explicit_stepper_base
 *
 * \tparam State The state type.
 * \tparam Value The value type.
 * \tparam Deriv The type representing the time derivative of the state.
 * \tparam Time The time representing the independent variable - the time.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 */

    /**
     * \fn euler::euler( const algebra_type &algebra )
     * \brief Constructs the euler class. This constructor can be used as a default
     * constructor of the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */
    
    /**
     * \fn euler::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out of place, hence the input is in `in` and the output in `out`.
     * Access to this step functionality is provided by explicit_stepper_base and 
     * `do_step_impl` should not be called directly.
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
     * \fn euler::calc_state( StateOut &x , time_type t ,  const StateIn1 &old_state , time_type t_old , const StateIn2 &current_state , time_type t_new ) const
     * \brief This method is used for continuous output and it calculates the state `x` at a time `t` from the 
     * knowledge of two states `old_state` and `current_state` at time points `t_old` and `t_new`.
     */

    /**
     * \fn euler::adjust_size( const StateType &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_EULER_HPP_INCLUDED

/* euler.hpp
88CdcnHfdfoxHE4zDL/8bP1v0NNyKZ9a65tIzP6w5saRsogcfowro9X7P3qqgvzC76x3dz0u7TJtnX5L7c2SqxXU62uf4bDD6hvOFdAfPhoGM3DK0IHwISW+qWmPVO+QcSPNNdM6HxSbTPaJgu96K0XTnrZveYf/eVFfEIaN++2N/KR3pV/r0/l9NlunbvbZU8EHWJX/gXpq5vrWdveTkOfPzedTMXjVWryCP81tIh9zK+346gZxykYv0hObZsOl9XhXfGvJwV1ydEF/davem6i/1OlgG8xqPha2y5nOh2g/OvLnSvLL5/7zu/7VeFeqtyLWJY9+vNfH8KON/N/tOt77NcwcbLwxau70VjVamW6oSt9do8/pzTT6hIwfq2/7WreK8zp34bAYHAyTRsHEbNthFC16cLk6K4TbjsKdCPOwVi/XjeAPOAPn77zbrGs/ntUGmqStM/zBWRHacQEMuLhEvHPgr+f0tbw+XgaWZVbfeo7l+Ka5nm1xyH6y136HQ63t61/NQwtMsrctfvfX02dq8g218V20sauHJafkltz4QC2cF8ffT6mXgnDvgfGo3TRJ1W57+RaDhzvDnTri8Yhm3+N8Oe2VqoP+E5bWfVevvZP+gtGT1qpz9b6jJrzuHXgktBn99eJ/7J0HeFRVFscnCSAKYuhIkyIKSEsIoYhgGiGQZgrNrONkZpIMKTPMJCGIoiKriIoFBcQGooCggoIiRVysCItYEBFRAVEpCiIKdvb35t1kHrw7bt6b3f3224WPEHLmvXPuPfeU/zn3vpdysCtrOsFCvATTK++l6U5fbt1UcgX10mHqUld7IDLfu+4nppFbrmJ85ywFe8whj95E7OjCWSn0e5Ic8pwVDPsguiX+78GfX6sDrrQTO8B4xzpQcyfjv/XwsRNqPdcDe3llGzmQ/kTfZ9mrjUIHjCkdHxxF7Gw9iGca8cWcrpwj5dzW3cxrBbbwGfGhJfKzl5LzDnKOohDsjvzvRrCGm9h/hrd3CP2CSPLOtfgV9t+LPtTQicRO8MORp8FQG8n/4IH7ZuD7FuYH3soFk3zoQ6/ct7ItMaoN9XgJcQ4/b1zC9fhK/RTyiY08uJX8D76qSz6bjE6/vI+6+QRxNAb8TH4b4iEnoos5j9JHYr7hO8FwO7HFluSOj+jjLQLbPcMZ+gH4YDZ5Gh+qB7Y9QpyOn4Stl4LlLdgV4x3GnkT4SGJAFv2FynB6yBH0rMBH1NCTnlD6raxhfbDxueQYehg7mW9OGvFjLPF0Mti3EhxKzHulKWMi1nX5jLmtBsvz+YDe2AT7UtOmsAboLDIeXH9BGJiPdb2FXksDrmWdF3nA2jeAce2sSV/sLAYbfIla/k1yNT7yED61knokdgH4/E7G05H8+CRjIyaX9FFx3OUfkBvGkSc7EMvKqNVbgyG47jPWcPks/Arag6uJLdjxkm6c7UaHr36Dzy5Rzi5iowuwbTDlo+yFbXqNfsqj9PITkYlOxjfmjLMHPyBnLthFXU788twB3vGSF8kxy8ibe76EB/ng8vXkJ+W9JW+h1ybk0G1gX3DKR+/T8wbXtXCEUciBAbDfH3dTz71JfGQd36QWmguuyf+BcbPu1+Kzqw+id/q5TxD3lhYih3muILYNHAcGRu8tm4DlwRtzt4DzwWgfEtf70bN/fgN5aD5Y8j3ibwG4gL3gxuSupvSKOjGGu9nH/o7vJ4l/xcXY61B6yGC9neT1DdSEn4PPuxNnvjqBX7KmcfWIEYzx+ouI09Tx3Z9CN5uJpcSqmy3UbMeIXfPAq2tJpXb67hn0J3vB/1n6upxP6deHXOYhbyA/hzW+j5w2eBo+dTU+/DPxF+wRht4OEDc=
*/