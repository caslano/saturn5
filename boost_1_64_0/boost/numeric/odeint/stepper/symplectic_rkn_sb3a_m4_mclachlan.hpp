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
sn4zxG5s+SXsZAHcwJGa2HWtJl7+HD10M8RF2N5z+LIPs8FG7AsfG1WE/Ri0S7Au3uae/aBxBTp7iT7wli4um26IB7/XxNrRWuV1IwJdjeQXcm9kXSTNEH9/BV/3iiY+uA0bO2aIxnWwY3DsRk10wHYH301ZjujitV+4zgvAWfdzf6IuUtDT1DJNzCzXReNd9NGFvEGj62IB9948QxMNvsKvM15dHmUI4ypsMlsTu9lkPId+1pl+Whe0P6wL/QJdaDMNMcPDuEe7bLtHFzFciwcJ4Af6xufv6+Kr0YZYgq/0/KCLwxN08SXj30/8WEbHYl2EnjTED1fr4uVHNfHYDbq4uswQX1+Jrp5H7k70t0ETbQ/yPZkE7PtZXdzdWRdH8eW7XtTFR73Q5U2ssY2jHfAZGx/WRLC/Jt6/Hj/NuPRjHXw1/fnG11nPgn+qgyYe+t4Qt8zFF97C9y6OYseLdDEaGyifRv2w/3WcrwcbgWkbu8Gr4HWw17wWoIv2kYzjnH8APgQfg5fAuJ/wQ/dbf/s3gaMvXsvYWJfzI8uw2znY/Q5d3EoMEwz3DG13xYW66J3AOLESnTXmPuziPjCXBaTn79RFHgbSsiljtB82PhRbYcx9OMMQY3doYvsu2pRr2SAajAETwGUgeTf8Xl2s5Hw12ASG3m+IXixGTn9VF0mP08/4IeInxjJeFGGvA3VxgPFq4Gv0gXDGho/RZRDtCjL30bcL8A2cr2Ns+1ueITpybl7vBG65Cf1ehs6OE5sQJybDTQB9WqMfFszSTRngzveI+UIN8elaTQwgJoo7iq1it1n3YafobKEpCywBy8BSsNLME9wehHyQwFh+/9PYapCV/uY/3PNYc00UMVbcxvlts/Arj1s7XY8ZYIhlvxjidc7fAHvBHrC/H7FQoLVrZkICY9gYTTxC+a7qjk4YP0LaG+Kpb+ivd1o7YR4DuwdguxGayOlniPy/WLt7nXwDW95EOzykibgwXbSCe2ooZa2piYksRr9Jm/rD1QctUhgjiBnaXmiIrX/Hn8ON/9IQnzyqi7/m6aLhLdgRXIe7aP8s/ADnqSANfLieek9hnOZ8LDj+KXbYAHtinPg8gXGhiy4WEnvNbqWLJx8zxMSHdDGUsXkeaZOJ5fVfsSHOJy9Gp5T52HT8x7v4IbiFJhinQ3rQz4ml/LCVW+kv0+8yRI0WxGaZGunov8OZC9ymi+YniOm59yD9suNM2jYb2Regs6mMuZvJvwZtTr8e8oUmJszSxKhiQ9wcQFuBpcD/e9qnp0b/0kXJZYxTcDcGwD1Pf8aHZYylXsQQt8FFdtFoP+J2f6MyliyIo7/Npq2o+1+7GCIBP10eiF8g7UtbiH0WGuKh2bTDEvoLfnN/c9rJtIuO+IDzDTHgWuoeQNnNMeBCYmTGzosYY95GB5ldGaM3GSI7El+2lpjnPtpuAjHPs4yRjCsNEg2xgnpmcb73a2LyVYyVnA9CDz/mEPOmGGJ2mCFi4D6J1sT4XORwPm0etr9aEwmc1xhGG/RmHG5LvGSOE9zb7xHanWsZz2ui2yzarhH65PoFxNHkhR9gjGGcu4nzxeCNnobo9gb65HwFuBXMbciYt18X68x7wY/rdfEJY2svfOCn6zTx/R5DXHUHOkcP87i+AAzfQWyPjx3VHt/alLHjRSG+oG+e2Mcxg/nAUV3c3MjOZyVYBW6XeaSgn5W7NfHFXkNMu5JfJznGWJqPD/6JmPErQ+QyxkUxD/mYtP6N6Yt7WEu/nLGO8017NLFoPPMAzmf9DZ+C/bfhfPho7P9pxriZzGlY2O8Ktyyc8b42/ctMO4p2x4+lcb4FzAO3gadKaZ/l2M3VmmjJ2DE=
*/