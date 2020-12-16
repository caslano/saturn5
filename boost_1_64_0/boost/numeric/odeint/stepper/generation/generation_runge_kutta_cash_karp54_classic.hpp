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
Ye+OR+ktJSAiIrIS/pS/2Tjh6vsQBo95jIjnE0Y+40BGrZ1HMAtP5ZFQjVvkKm00TE1KwFrbjhiUHDBxZztChrq9vVEuPssxveMUUgWDGm3l1/ucWDNTBBiffIRAlCL9dKs4kJQxCGU1IWEkCcnDBiRFJiQeALJ8rAFEZNcR2xFjfj0LKBoxAXqsrUCEVUZD6ND2kkDREJyLbc0cXKkv5j4rjQPuXkjiRGfxK8KFTF4qeaXkCFxLIH1Q2UZ746A4JOg8iOSq7XWELUU/nWbII5rLOsrYdeYZ4rfE0OEH4Im+03EI0SZkrHqGt3W86trajD5X0bEv99notKIRGqj4tu2ABdldh1Mer8e9dLvFdXGDMChE1CJxTLozdR4MskQPrRSDpvfY7dnkdRMubUqhbYe36/beZEBLdsBSJ4oIKFZ7ZSw+e1SN2q3fMRZEQNliC+UAY/dcfWo3oB27gNrs3SPaRHhB7oH1zWMPirnMderZ4Sit7q26jpdym4cfwMsIb6hoybKBYlTY3EbmZv2+jv3DD663DG/OPUApbBU81SQCogUOH8qZyip4j7juwtyXZFe09uiK7OmG34MmPXLRiPUj5MLHCpfNcRXfK5Ch7Ym89SY7+krR4dHxBU0dAgoTHAhS/m3wZ7yo0j2c7xwUmpc9id2ABaL91stshqNNHDKHChwD2m4YPy71xeDwTiu61dXYD4IM/ef5ps3inVSgsF8u0BvzxfgOhZtzkMloXs9+HPoEaNJvDEDB2gV+fS60x8lwcRJoDOjfEenyEbssaIyVyOOBfDOPwRR1kZ5lwBozwHUPVUQ4a1uW22Mmu8krZzKMmtuvsQOJ3AaTOo/pLx8/a9KgnRxognZXd9DeNgNcd3MnG1jvVez4OE3HYgId6gOcroQVDil2VUwJ6F9BIoANy0TWwvzGJmrw1ctZg3/Bx3/+f/3XX/pvPVzthYeIjXjP4cWvX9XfJleyFWtyQ/3IBPceu70l6zqeK9VlW3Fkk3J2UtTmyPNjXZutUUWzcj73wW5okjXqs+Jhi/rEoQtRnx2bq0RoFt7xhb5sPHAiYg4e8HRokxwitBfec6O+XDzyor48PJxRn1Ob5BShvfHeJ+rrg4cr6nOdQw9JwUdYDMD4UAR8eLFJOOyESgKXJYGzEzgBhYMwSdB6SdAcEjQXQCNEErDeBEzA68LjvKjPjUe/qK8vHn2jvn54uKO+884B6H9r+PEYGPV58BgQ9fXHo3/UNwAPT9Q3EI8Lor58PM6P+gbhMSjqOx+P/KjvAjyGRn0FeAyJ+gbjMTjqG4JHQdQ39C/DyVnwk0P8EAl8ZEn6s0sE2SSCrBJBikAQXnIkDhwSB70kDnIlDvIk7pwSd70l7vpI3LkkDtwSB30lDvpJHJwnceeRuOsvcTdA4m6gxEG+xMEg4kDip4D4EbgrIO6IH+KO+CHuhuIxMuorxOOiqG8YHhdGfcPxKIr6RuAxIuorwmN41HchHsOivovwKIz6RuIxJuorxuN9Ud/FeFwS9Y3CY3TUV4JHSdQ3Go9RUd8leFwc9b0Pj+Kobwwel0V9pXh8IOq7FI/3R31j8SiP+srwKIv6yvEYG/W9H49Lo74P4FEa9V2Gx5VR3zg8roj6xuMxMeq7HI8JUZ8XD2/UNwGPy6O+iXiMj/quwGNc1HflX9/+f+slhsF9Lg6DO13dpHrmsd41AXFWuP6wiFTkpjgT+/GFuhFrQ6wxseG4v1j22To7uSJFWLF4KdlV4fpuKzmBIt76My6hRzm3L2nLC3lBubFyxQ2uzXUH2i3uZNHae/GAYUFTLqFr8oj/IeK/WPxfLP5Hif8S8T9a/F8i/t8n/seI/9vFf0A=
*/