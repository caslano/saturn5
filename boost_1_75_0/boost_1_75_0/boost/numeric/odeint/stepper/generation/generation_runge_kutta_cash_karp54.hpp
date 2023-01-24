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
mFarpHoFWOOzGZWkoo06T3rfYNdkQRfmwoUw/7RRDLIPI6lW9hun08QJqJP1UNpcGLVwfZd5GO4xbpV/wEeBEY3qStq/Cv+FWaB48Y0wljOdVe4vXbruXmZCANVmOCHp/rbKPLEl9KI43sgUTzbyv2TCIBWeEZCdWw9uwSBfAU/Q+QI+HraIrRkTWcgX4Ohn59ajvgQiDHpSzu+Xnpp9gDHie/fCElvtNl2vDtesl1nES32ByK2dY/6dsnwwengfaTzETwLdt94rilb+vO7SqLV7MDz4z1YfSvfXKIfzfNNcXovYrJzvjKctkTFQnca2pvkqTDTQTlt031XYV+SXnucwCCuhYtvqefar9cYAQaUKtQ1PDYB9U4Y1zo10bJSRougFh3tZj8gFxI4MbSekA7zO9UayCXrV4Fx1ih3Xzw9tEuOsZ7J0m3C+YL1NIn0qoZkQiS7M4livNwYqv5UiqC7Mz7F9XtSSB/nfrZCgOjarzwsjBBYLHRSOWrDBjtes/m3Fkk7RBszgdL1G8YjtnyfpLUwYFFQLxQdoHFLzqRQHLut1yqDyBH+xHpR73Jef0QbTKtEjamTRUnsKkgNiBn+ont9HNueDTBTytDk6Xeg2YQJPup79ykbPaoh+Ps+eV9krxkSxlXjCXPzm3BxaeTwTfh/XIR3Y75dKciyJkSIqR5gkqRxLisqxhFSO5b525FEJRRILsSRRjiW5
*/