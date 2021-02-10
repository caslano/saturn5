/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_cash_karp54_classic.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the
 Runge-Kutta-Cash-Karp 54 method with the classical implementation.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54_classic.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>


namespace boost {
namespace numeric {
namespace odeint {


// Specializations for runge_kutta_cash_karp54
template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};




} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED

/* generation_runge_kutta_cash_karp54_classic.hpp
QOTHCLNNReSLVBErz0sVJqYqwM+mprLXpziCMVRrjag7qtHEzWRm02V3/H5wMabL1nDY6o+vaHBGrf4VC/vQ7beRegllKYlFkooMylOS8ySUwjc6/7qrsdXgnE5v9+mELoY9neLp7QEekzRe3NMdbCExR3X58AfpSncTN8vu4tQHcWNr64WMvLDwBdVykSHXtdUlxCQK4QMvV6tzMffFpJgqYgSrwM733dyl/24ReTMXkU9dTzhu5kl5RDBxn4PQZH3fj5jFzaW3dRtLn/xinlgeUpxrzp1cLHJ7q9qjZ91eh3agRbhzTmwmpxE80cRJntqUya/CydVtlVFRRPFMLOpbbJghk0fVbw/GUCVTRjni5SNgJ9Rc7DfVWxlYRoiCph0V0bjIVUFhnfA7KXLsU0EeiiVA1c5jlBJqB/taiIjdZt5K9GstOkhSqAys0rnaNqpr+2tBk3vkgqzmYvvron4d1WxSUdEuqr91LSBOLckSj0ge8zLutHuiNdWRDqX3sZrm66+LQ4JYqeUoL3/RbqokGlfZvSjOeUswVPg2488dwUPjkjbB0yZ4dKw14+fubn2ZCsiGVeq1Mn0lR0+YdrBgw5DYz4rpS/1oSS/CTKwxF3lm1fALDFqCIf5uHK9ss5bG1enlS1o3SNu7
*/