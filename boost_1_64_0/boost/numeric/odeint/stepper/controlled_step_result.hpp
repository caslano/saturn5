/*
 [auto_generated]
 boost/numeric/odeint/stepper/controlled_step_result.hpp

 [begin_description]
 Defines the result type for all controlled stepper.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_STEP_RESULT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_STEP_RESULT_HPP_INCLUDED


namespace boost {
namespace numeric {
namespace odeint {

/**
 * \enum controlled_step_result
 *
 * \brief Enum representing the return values of the controlled steppers.
 */
typedef enum
{
    success , /**< The trial step was successful, hence the state and the time have been advanced. */
    fail      /**< The step was not successful and might possibly be repeated with a small step size. */
} controlled_step_result;

} // namespace odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_STEP_RESULT_HPP_INCLUDED

/* controlled_step_result.hpp
rMf0RAN7Oitz+Rxq2a2MhAeDzPu40oGr+gN7bEeksXzTCkmAwh57om8OeOQ1Il3rVg0h7wBrYwwlxcZ9Gt9XDQZVFaUe986eVL2fsjtSP+2/nvA8ezg4UNaYWfCl+U4vaBAighnWL0v0elM/NE6OKt5EkAAVfn/NnYpN1pquTkAKRn1uxOMmx1gJTi1RUX/LZMwoWinLpcRP52Rq+jS8TdndtyaP7tGv8GaqjwwSpz4KZTKVz9KAuZ96UZ0F3z4O/ba5kZB5Ph8m1ZE8U4TlutYSzcdgFdYipjbTIz+2sg36tnxMch8vhIoYxqUV8hun+KdZyxWvz/5cVnfnW6o0j7bmROWCrNR488QMa5ZnsEcCeAz7uw42KP1VK8m1aBFNLd+5akXvoKvZzFRQ5tijaz9UzgJir/wmRtaaCPngMy/zAjqEENG2Wmy8xHpH8Em04aR7jq0RQBLMd6rcXzZz5JsvJgOuW4aq/FaCTl0ISiRIIX87bO3/QRXIkpNxyzi8lrsSH+2Digf8MzsmRsIZbOFznOdE7Ihx9YK8nDBFQ14MwIUzABb7pL0p4w==
*/