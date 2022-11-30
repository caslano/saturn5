/*
  [auto_generated]
  boost/numeric/odeint/stepper/symplectic_rkn_sb3a_m4_mclachlan.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2012-2013 Karsten Ahnert
  Copyright 2012-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_M4_MCLACHLAN_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_M4_MCLACHLAN_HPP_DEFINED

#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/resizer.hpp>


namespace boost {
namespace numeric {
namespace odeint {

#ifndef DOXYGEN_SKIP
namespace detail {
namespace symplectic_rkn_sb3a_m4_mclachlan {

    /*
      exp( a1 t A ) exp( b1 t B )
      exp( a2 t A ) exp( b2 t B )
      exp( a3 t A )
      exp( b2 t B ) exp( a2 t A )
      exp( b1 t B ) exp( a1 t A )
    */



    template< class Value >
    struct coef_a_type : public boost::array< Value , 5 >
    {
        coef_a_type( void )
        {
            using std::sqrt;

            Value z = sqrt( static_cast< Value >( 7 ) / static_cast< Value >( 8 ) ) / static_cast< Value >( 3 );
            (*this)[0] = static_cast< Value >( 1 ) / static_cast< Value >( 2 ) - z ;
            (*this)[1] = static_cast< Value >( -1 ) / static_cast< Value >( 3 ) + z ;
            (*this)[2] = static_cast< Value >( 2 ) / static_cast< Value >( 3 );
            (*this)[3] = (*this)[1];
            (*this)[4] = (*this)[0];
        }
    };

    template< class Value >
    struct coef_b_type : public boost::array< Value , 5 >
    {
        coef_b_type( void )
        {
            (*this)[0] = static_cast< Value >( 1 );
            (*this)[1] = static_cast< Value >( -1 ) / static_cast< Value >( 2 );
            (*this)[2] = (*this)[1];
            (*this)[3] = (*this)[0];
            (*this)[4] = static_cast< Value >( 0 );
        }
    };

} // namespace symplectic_rkn_sb3a_m4_mclachlan
} // namespace detail
#endif // DOXYGEN_SKIP




template<
    class Coor ,
    class Momentum = Coor ,
    class Value = double ,
    class CoorDeriv = Coor ,
    class MomentumDeriv = Coor ,
    class Time = Value ,
    class Algebra = typename algebra_dispatcher< Coor >::algebra_type ,
    class Operations = typename operations_dispatcher< Coor >::operations_type ,
    class Resizer = initially_resizer
    >
#ifndef DOXYGEN_SKIP
class symplectic_rkn_sb3a_m4_mclachlan :
        public symplectic_nystroem_stepper_base
<
    5 , 4 ,
    Coor , Momentum , Value , CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer
    >
#else
class symplectic_rkn_sb3a_m4_mclachlan : public symplectic_nystroem_stepper_base
#endif
{
public:
#ifndef DOXYGEN_SKIP
    typedef symplectic_nystroem_stepper_base
    <
    5 , 4 ,
    Coor , Momentum , Value , CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer
    > stepper_base_type;
#endif
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::value_type value_type;


    symplectic_rkn_sb3a_m4_mclachlan( const algebra_type &algebra = algebra_type() )
        : stepper_base_type(
            detail::symplectic_rkn_sb3a_m4_mclachlan::coef_a_type< value_type >() ,
            detail::symplectic_rkn_sb3a_m4_mclachlan::coef_b_type< value_type >() ,
            algebra )
    { }
};


/***************** DOXYGEN ***************/

/**
 * \class symplectic_rkn_sb3a_m4_mclachlan
 * \brief Implementation of the symmetric B3A Runge-Kutta Nystroem method of fifth order.
 *
 * The method is of fourth order and has five stages. It is described HERE. This method can be used
 * with multiprecision types since the coefficients are defined analytically.
 *
 * ToDo: add reference to paper.
 *
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
     * \fn symplectic_rkn_sb3a_m4_mclachlan::symplectic_rkn_sb3a_m4_mclachlan( const algebra_type &algebra )
     * \brief Constructs the symplectic_rkn_sb3a_m4_mclachlan. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_M4_MCLACHLAN_HPP_DEFINED

/* symplectic_rkn_sb3a_m4_mclachlan.hpp
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
*/