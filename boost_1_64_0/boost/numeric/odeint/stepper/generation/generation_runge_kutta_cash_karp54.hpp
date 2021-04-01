/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_cash_karp54.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Runge-Kutta-Cash-Karp 54 method.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>


namespace boost {
namespace numeric {
namespace odeint {

// Specializations for runge_kutta_cash_karp54
template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_cash_karp54< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_cash_karp54< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};





} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED

/* generation_runge_kutta_cash_karp54.hpp
1GKr9lLKSlIEPVpUbgOrCA2/pTX9WI1ANakCD6TwuxRZPhDhtVw7sKgzmzJHBgEsmN85BuMcAbu/cHJTtxF50DnF93s5ZcA9djfOP10r4aeZyPcpu3ejF0CpqttQQ45KJ6o35KCAcoRuN1zJU4VjhwcwZtwdpskPdSFYRzNAORF0afEiuVlXPmgKkWxIEs8uD+3d9FpnI7FmsVLmiJh8yH6FMZBOUS78y4dBlc6gi9Rr/3Bltx+zLArbIg4iPqaV6wXofu4P4JTo2Eo4k6oBHnOhzKODpd4w+IUTPumGAD+5qTivPGhivOLrE1zrd7vHYNXMGEBUBSDIKS6thEDdYLSENmjXFXURpjndEIFAiR1fiYehBsZEh35Gr/sIpShXM0vx0eHjqWAOLwtJrK1xu1ZHQj8riJ4YNoQYuGCnBXzB/+wC6qTzU0sHK9CYSTv6Lc6j1frBdOzvNU6/zuLBLORJWSKJci434QaZUAD2xUd95qMOmkVZCLMoDJ47H1Mr+gYpIGeUGcVgrAgP6Cb6bX83Uda4t1yGZxQDambBq2anokcksHme10uIlw==
*/