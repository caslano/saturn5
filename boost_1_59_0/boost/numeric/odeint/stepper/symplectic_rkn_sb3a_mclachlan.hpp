/*
 [auto_generated]
 boost/numeric/odeint/stepper/symplectic_rkn_sb3a_mclachlan.hpp
 
 [begin_description]
 Implementation of the symplectic MacLachlan stepper for separable Hamiltonian system.
 [end_description]
 
 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky
 
 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_MCLACHLAN_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_MCLACHLAN_HPP_INCLUDED


#include <boost/numeric/odeint/stepper/base/symplectic_rkn_stepper_base.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {


#ifndef DOXYGEN_SKIP
namespace detail {
namespace symplectic_rkn_sb3a_mclachlan {

    /*
      exp( a1 t A ) exp( b1 t B )
      exp( a2 t A ) exp( b2 t B )
      exp( a3 t A ) exp( b3 t B ) exp( a3 t A )
      exp( b2 t B ) exp( a2 t A )
      exp( b1 t B ) exp( a1 t A )
    */

    template< class Value >
    struct coef_a_type : public boost::array< Value , 6 >
    {
        coef_a_type( void )
        {
            (*this)[0] = static_cast< Value >( 0.40518861839525227722 );
            (*this)[1] = static_cast< Value >( -0.28714404081652408900 );
            (*this)[2] = static_cast< Value >( 1 ) / static_cast< Value >( 2 ) - ( (*this)[0] + (*this)[1] );
            (*this)[3] = (*this)[2];
            (*this)[4] = (*this)[1];
            (*this)[5] = (*this)[0];

        }
    };

    template< class Value >
    struct coef_b_type : public boost::array< Value , 6 >
    {
        coef_b_type( void )
        {
            (*this)[0] = static_cast< Value >( -3 ) / static_cast< Value >( 73 );
            (*this)[1] = static_cast< Value >( 17 ) / static_cast< Value >( 59 );
            (*this)[2] = static_cast< Value >( 1 ) - static_cast< Value >( 2 ) * ( (*this)[0] + (*this)[1] );
            (*this)[3] = (*this)[1];
            (*this)[4] = (*this)[0];
            (*this)[5] = static_cast< Value >( 0 );
        }
    };

} // namespace symplectic_rkn_sb3a_mclachlan
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
class symplectic_rkn_sb3a_mclachlan :
        public symplectic_nystroem_stepper_base
<
    6 , 4 ,
    Coor , Momentum , Value , CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer
    >
#else
class symplectic_rkn_sb3a_mclachlan : public symplectic_nystroem_stepper_base
#endif
{
public:
#ifndef DOXYGEN_SKIP
    typedef symplectic_nystroem_stepper_base
    <
    6 , 4 ,
    Coor , Momentum , Value , CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer
    > stepper_base_type;
#endif
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::value_type value_type;


    symplectic_rkn_sb3a_mclachlan( const algebra_type &algebra = algebra_type() )
        : stepper_base_type(
            detail::symplectic_rkn_sb3a_mclachlan::coef_a_type< value_type >() ,
            detail::symplectic_rkn_sb3a_mclachlan::coef_b_type< value_type >() ,
            algebra )
    { }
};


/************* DOXYGEN ***********/

/**
 * \class symplectic_rkn_sb3a_mclachlan
 * \brief Implement of the symmetric B3A method of Runge-Kutta-Nystroem method of sixth order.
 *
 * The method is of fourth order and has six stages. It is described HERE. This method cannot be used
 * with multiprecision types since the coefficients are not defined analytically.
 *
 * ToDo Add reference to the paper.
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
     * \fn symplectic_rkn_sb3a_mclachlan::symplectic_rkn_sb3a_mclachlan( const algebra_type &algebra )
     * \brief Constructs the symplectic_rkn_sb3a_mclachlan. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_MCLACHLAN_HPP_INCLUDED

/* symplectic_rkn_sb3a_mclachlan.hpp
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
*/