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
FfLIMnZJbmlhkYuP2v27viuqP9Wf6k/1p/pT/an+/N9//FuzjzoIAA1AE9AStAOdQEMHHwwuBukgBySBBPl3NsgEN4JFYAVYA+4A88ECsAQsB6vBRrAZvAr2gLdA/ipDXP+pIQ5110TxFl2k7TbEk9/z/K+XLhrxY/N/v4Py9DfEc48aolYPXbzPPYfBx2A3eA182sMQw78wRJs2fHsIpILbwGawAKwBm9qQHrwHjoOgtkQ6oCPoCsaBTHApSD7PEPHtdbGoLeUAK8AysApsAHvAPvAuOAw+ArvAIVDnPMoLGoGOoCXoAmJBEkgGKWAFWAVWgk3gFrAP7AeHwcfgZfAOOA7qNydGBa1AV9C0OXLBODAGrAQnp+tiSVeN33DUxFfoMb4FERy4DGSAHBADRgHzWgIYB5JBCrgRzAPzwRJwM1gOloG1YAN4baIuJo7XReuW2AuoA97+URNPJmInnOcRLc64ThN5/ODImixdTIC7HGSAAUM0cfdzhuj7hS6+vlcXSwmwpyYQo3Ot6be6+PwbTezj/Kd/6KJgpyEeftYQR67SxJu3aqIdNpBI+lRwGUgHv8RqYjj5DGCe/wQLiN+vM0QTzRBfPMU+Gkc1MeWwISZkGyJwkC7apWvirlXYwAlDvMm9Dy83RL8WmjjUivaroYvPbjbEqI7oBcSCsSD1fU1c10ATmztSfxAzjTnpCiHSvtTF4lGa0B/QsBfaoRPtPMIQXfhBlbi7mDttxrbv0cRx4vMP+ZH4+Uw8pz2liVpzDPEead/vBA9a/8Ke/ts1UX6FIVaxx9zCLNoyXBNj3jHEN7frYtxayvkI72o31EViM0MUXayLKb1pg3vpl4WaGLlEE+dvMMTGzvQ5sB+8DPaCtfM18fYThqjfhbKBdmAUiAXjQKbj/ErmTc/GGWIN5xvBBjM9bbhsAnbUWxM/NUD2r4aoeE8T5zHXaQPGg8fP18W3qYa4rBb97QZNNOEHJlt8bIjejXXxDTZ4H336h1hd7Illj/k5zE+GGKJsly4y22OX4FLw0meUfbsuumRpIht9vNzREFq4Lq56E72naWLORkPMe9gQe99Gf+9oIq22IUb3MkTTv2qiX6Euhr9giNVHeKsngr7ysS62rTDEu+msZ5Dn9qsN8fbLhgj9RBOeGw3xaF3acKMm3srXRMBQXcxpDnRDvNbKED3/RrqFmnjmAUP8ttIQOcGUF4wCEWHsoMb1pGD6KfjqEl3c64dP47zfk7w3P0wT6zlf3Bj5c3QxL5i+DUzuRCk2kUibBaM36t/kJkNcQ7nql+jipaa6iFhOv/Fnb//vdBEwUBMxnCeAZHApSAU3RmPzPxhikT/5gxX+yAdrzL+LNHFijiZObtHE3O74wPoCXRmi0Xr0yfnSXpromcP9FbrY20EXDf5uiHVfCFF0CJ/7miHu6aKJeNo4fbMuHkk2xJALNbHmGU1c3IA2AongG3Q6k77QuoMhLqafbMa2QkfrIpZrCT8zjngMsaUBeYEN4CWQjz/2q0UbzdTE66N0UYeNZHrdhbxE5HDe6iT96Dv6HOcxoIw2futKQ4zjPK4RzzmT6Fuc/4xeCssYs8Zros5EfEYobc29H/6G/70df8KP5RdebogM0uaAOYMNcd4nhhjajPOX+ZXgYPwBdnLoQnzyQNI8hq6P6aL+NnxbjC7WooNQ/MBN3LsWpLDm9O1q2vVLTYyNQG5PXaxuRhl+NsQ7DxkiBB+zY5Emvr1GE9dTzgMHsc+ahnjhHtYMrqcukdR9FvYfwzrNeZoYzI+zbkLm47Npjy3UAXs/jA1E16bdwcekGUY/P/mBLp4/qYvlcD0vxU88yptkifjFrbq4A250mS4=
*/