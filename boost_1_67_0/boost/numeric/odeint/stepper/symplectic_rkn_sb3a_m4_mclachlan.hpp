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