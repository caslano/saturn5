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
NaRLfbBbwW2z+tT+gR/q78H/UEsDBAoAAAAIAC1nSlI8kkpQPgkAAPAXAAAiAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NTIuY1VUBQABtkgkYK1Y+3PaSBL+3X9FLyknwtYa7Evd7fqRXWJwQoWAC/A5vjilEtII5iwknR42ziX/+309M0LgR8hVrVKx0Kjf3fN1jxo7f921RTu08XLUfwcX7orjPI3/Lbz8aWrH+Ub6H7iucd+kpEEVyzenTptZvpGlWByj5Zh/O84mRddsG/9pMOe1wz+xAjbmPI2T+1ROZzlZp3Xa//333+hXOmgeNG1qu5EUIY1yEU1EOrXp2Fcrf87cxWIvE29sEjm54Z4RNZ7JjLI4yO/cVBB+h9ITUSZ8cjPyRealcoIHGVE+ExTIUNDp4Pyq239n091MejMWch8XlM3iIvRp5t4KSoUn5K2WkbhpTnEAdgj3ZZZDYJHLONqDbkG5SOcZy2D1bpjF5N66MnQnUOTmNMvzJDtsNLwiDWF9w4+9rOGV7u/N8vnSkysYMXfvKU5yymMqMmETU9o0j30Z8B0BwWJSTEKZzezKGqiK/EacUibCkGWBT4pMmy1oZMJjMxklsFjmfMviKGNVd7N4vkaIOLKUoEgjKEIc
*/