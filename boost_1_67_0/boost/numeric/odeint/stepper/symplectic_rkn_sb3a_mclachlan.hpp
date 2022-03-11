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