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
t+u+BTDMpx/0DNbNHZnr5MVdzXf1Fp1X7zbvtY77a2WhdvLKlPBST5oHigS9WyuvpeRPa1GEHWAMhrkFxhSesKcwqriOHKm9jVwEhbeKkyrcxuOy7Ap6cmKadK8cZL5pwKjwdBGThrhB3fqFiAEKUooVDbpVChy4dmnIcJ3VwaJmHUviRm0dhhB13VBFYqEZXz//swLGKm346RsFERBMPXx8h+ug5rugPB59ofLWaE51i0wGrduVVjKaFlvMyYJgXi4VFGcd2T5YuNkZmaeHo5PjM603ctlB0QhYy5fpVB+iDGKrtUofs9IJfabqKVWv3K3dppc/l/XSTjj5KDaFjHy2LECuULLeV1My7FOu0jMni6VgpKxX3E8qwWnns1pvvyjaFW2ONXUEiTCYlUKkj9OKmizEquVqUNH474u964hqE11wzG3o8hAtFW+9F6I1+wLCGpOkmprV8sClCvlgEbykkd+PicgtdBMNHu2rcm+ZxS5lwXJjeVYKJivMV0/f9ijgdruUK26WavimiVED28QMBi42zYzUbuA5r3RT3KZ3Xi4O2BYOyJ0xzuumM2N0I44FDJdZByYgm2ZV5PFoozKzadv8wr16WhEQSsxUjwa28sGbbxG+G1hJUbehz/utHmyV+3TUFszkXQr3
*/