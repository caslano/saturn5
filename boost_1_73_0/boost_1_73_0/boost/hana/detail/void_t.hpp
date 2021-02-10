/*!
@file
Defines an equivalent to the proposed `std::void_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VOID_T_HPP
#define BOOST_HANA_DETAIL_VOID_T_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename ...>
    using void_t = void;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VOID_T_HPP

/* void_t.hpp
loCLlFFuupV1K6JU3k4VFRqA2yDnrnDs3htSN0y4NWSYgQ/BlSmmNwR+yEOaIyH2voTY7wQDjsNnR0KlCao+KURJEqVW8FQXFiDBZgY0bMnWNoOqOcXPmd6o9dF1RAsJVsbv7NQ7+E/4IjQrtTulEPmygWICwA7+tGoAdJSIXDAYymoJAgRoT9RoTn/8WSxegfS7In/V0KB28znqNPRqENfn6xCFzHww4qwOLWZvFu9aG4TCjNnAMMJUFJDLTcE9Bl8XJAIi3e0yCDUKeaB01lNG0qZEHUI4iMHoLc9xTINoeqQ/7I0gdvw0AUZhSZAoTOldqgR5/PN2NBrkAbWdY3tqDCwFNa7LHTfNQCIZKOCb9H5JVUzzBAdCknaTWw2FTK2Wtql7mui0wZzou9sWJoNRV660u5yewAYi/LdXExMMrT7oqGaIK4fk6BW9kF968f0y/TWj8f1oiicpLYbTr5fm+Moevf0vs8fJvcYL38knXNNRgc42ajixTwfGGaPE5kNPMTIQI421QcjhmucbxDE7NTzw56E+TpcWz+TcRBCi7+62d1S+b6sqYAMnAD/NmqLBGYB5YkdkHWWSXfMNtqtwGtwFhmRTMupR3Ab8PEA5NamnQkFVVFSTfStZkz1VIpXBYNEtJ/TTe8IS
*/