/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_fehlberg78.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Runge-Kutta-Fehlberg 78 method.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_fehlberg78.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_fehlberg78< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_fehlberg78< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};





} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED

/* generation_runge_kutta_fehlberg78.hpp
plysB3NCvdobPK5ypf/6ZmVIUTVUpRtizbZcTgpFmqKunTgIMpGrnlJSKA0sf1IEn//RxPVFbYWPF6MxTYQeBnLsEfr76xsaDB+A7KPrY+sT4tAdd1s953wwGjuj7r86av+sm4QY+I7nhuHE9W6sZ+ah8iHCzDaxDQQY9Fmdisido7+xY4oSY6QeJ+DHOM7d0IwkjETY0lFu9siSe3maOFFrcWCZiNQBo+vBU0IvZwzxQh9k8nhTTH50TXEGWreGVyJYYnw6XjHvj3LxsFqsDAIiaF4lToObDhbXBwLjJfeWirHxjnvJmnO2FqDq6UHNoLGodyulZp4fl9tdKnNRJVenbUNyfxzDx5nnhrPMOid24RRf8ziTFotFBSixyhMDxrXtvR1GX81VoTAMqx89ETDj5aq4NWdZqYyxYUnGXh5W/q63PzbUm/tl9Xo4SUW5aWFapVk60uM6aLm1K3QZnH5sO8POaNwajofAubLXlx61zs973dPWuDvoH64cqJ9mBsF/ChySMJGbpvOkmJ0dGnYucRLEUfMXPFXkT6EIr5tAaaUdZ/DhyIwLa/116xHhRf9Df3DZh5k6rmqI4GOcyQzIdJh0QDneR+bJi33+gpCRDlSpdLX3a5xcOS7po5PJXTUN4DQdfv7CcM2q
*/