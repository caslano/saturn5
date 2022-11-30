/*
 [auto_generated]
 boost/numeric/odeint/stepper/symplectic_euler.hpp

 [begin_description]
 Implementation of the symplectic Euler for separable Hamiltonian systems.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_EULER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_EULER_HPP_INCLUDED


#include <boost/numeric/odeint/stepper/base/symplectic_rkn_stepper_base.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {


#ifndef DOXYGEN_SKIP
namespace detail {
namespace symplectic_euler_coef {

template< class Value >
struct coef_a_type : public boost::array< Value , 1 >
{
    coef_a_type( void )
    {
        (*this)[0] = static_cast< Value >( 1 );
    }
};

template< class Value >
struct coef_b_type : public boost::array< Value , 1 >
{
    coef_b_type( void )
    {
        (*this)[0] = static_cast< Value >( 1 );
    }
};

} // namespace symplectic_euler_coef
} // namespace detail
#endif



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
class symplectic_euler :
public symplectic_nystroem_stepper_base
<
1 , 1 ,
Coor , Momentum , Value , CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer
>
#else
class symplectic_euler : public symplectic_nystroem_stepper_base
#endif
{
public:

#ifndef DOXYGEN_SKIP
    typedef symplectic_nystroem_stepper_base<
    1 , 1 , Coor , Momentum , Value , CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer > stepper_base_type;
#endif
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::value_type value_type;


    symplectic_euler( const algebra_type &algebra = algebra_type() )
    : stepper_base_type( detail::symplectic_euler_coef::coef_a_type< value_type >() ,
            detail::symplectic_euler_coef::coef_b_type< value_type >() ,
            algebra )
    { }
};


/*************** DOXYGEN ***************/

/**
 * \class symplectic_euler
 * \brief Implementation of the symplectic Euler method.
 *
 * The method is of first order and has one stage. It is described HERE.
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
     * \fn symplectic_euler::symplectic_euler( const algebra_type &algebra )
     * \brief Constructs the symplectic_euler. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_EULER_HPP_INCLUDED

/* symplectic_euler.hpp
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
*/