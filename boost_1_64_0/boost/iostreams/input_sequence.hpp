// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_INPUT_SEQUENCE_HPP_INCLUDED
#define BOOST_IOSTREAMS_INPUT_SEQUENCE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <utility>           // pair.
#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>  // is_custom 
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct input_sequence_impl;

} // End namespace detail.

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*,
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*
>
input_sequence(T& t)
{ return detail::input_sequence_impl<T>::input_sequence(t); }

namespace detail {

//------------------Definition of direct_impl-------------------------------//

template<typename T>
struct input_sequence_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          input_sequence_impl<direct_tag>
      >::type
    { };

template<>
struct input_sequence_impl<direct_tag> {
    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*,
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*
    >
    input_sequence(U& u) { return u.input_sequence(); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_INPUT_SEQUENCE_HPP_INCLUDED

/* input_sequence.hpp
o2zz/9WN4vPQ/TmpDcX8B++bmSt/dk6et44CivkttDmXiPuHsJPiu6W7iEkMFY47fyZ2kvXeMZF24k9TxF52Zlam2vP6Ni4Te5eZEKnIs2T+urfPjm9H5VPgcpFfSP47Xufv6rPwbX2+IWP1G7I7AflOvx978PudMs4Bx61ic8D1O1Dznu4vpN+Qs4uel6D5JkW+KfV7NJA/UvS7ssDTR9ifB15yPq3Eu7ih6VPbVJf4Ef8E41P83qX6AOJG2thNiu5x1FznLnTUwHZA9UYmp51fzuayvGYqn4zFy5qtXGGvbOUqp13Zy5Un66W9lJPJBVOt5SooL24fvVypvHXtUCLMF/PWmIesZUrt+/NReh7DmRs/Nv+IjMZDkfxjjp5/3PywRPzMN4qfH6pJfjioE75fRFVCPY/qgczOaH6IZqyJOTOn5EXnLB2u4Z2hYs8POwNpkR9RWc2Xtnyh8sXzmjVf7LTkNVt+2GnPa9a8EJTdWM9wEZfq1z1a/4xJlD6uSbmTZmflZ+WK2V7MXDs1xWzSrGnZUf19aqe+xG7mjGlZef774HOx49WzrGJT/VdVXwSNlmHtT8tu7/rvOL3Hn3If689DyU2M1mu9alKONR+2KkM+JB39c15SvP6xiOppekl+tOTZhGJ5NqlYnkVP4m5jPc2b+gw3zty4TA7EJbISZzVdfY1HZCWuiEP0NA7VP6969aDGH3nZn0N4sIqRa0KY/KLsS17eLXG2aMac/IkUiNLrt4b6XsnrIOsqQi1NEzOVXoZXyHENndom17G2LXC/RL7039FjOrlme0xIfBrnr93YL89oZysTuGfPvym6zuN1sTs6NNSkOkuceL/fdqI8K84fA/lM7qvru9x7ZoPQiewuYylfwedqeyZ3ttQ16v6Kjq75HKeOqUyfS7K/j+Jvxd2rTHcz2lYe1d1guycnV0JkrZ9V3l7/2+pjlbfX/7U1HULix0mhpqTYx6aTGRWKta6BVLdKXVe6V8yXm0EmxrYuEvtHbm99JOb9w9oWknog0Iby57dNF/+mh84m/z1DbZ3pdPLT0Uv/AeYzJ0XSKugOERVoU/UW2U9Db5oKpbW//Hx/ncheHmpCe+oC09zcbQaa6k5HM9q51K+/tK0bbI/5bTU3zFNqGq7ZmcE5rSmSD+vrvef/eG+dkt82uxrVp6b8po0WVavJYKtIwMtRtOP8MQBwxLbb/g4/ve2WGGy7URZKtts0H6t+ainv6bqlvKfTir2na0u9Z2nTqTsHte7zzQJjEct/xrGId6q4+t2/ad5s9NcLL94y6PTU/RUuveDnG6N4XcYoHmjV6/sHB825d87b9RIyl758culjFIPEP/m1V3y1+JSrT7+wxWnXJbSv+MGxj10kijvLbr3mtQ+fTU9f/Oyo+TMuu2V/+ZjGv2JMY7f37anf9JuC+9jpnLbKcDhM17774TBXxypOgePhadqXP1bHIsbBRSq3TPvuL9O++8u17/5WmAF3aJ/9Lu2LfwtmaZ/9NB2rmAG/hrPgYZ2jGMG/OTARng3rwVyV7+23/+UbSsIVI2Mi0esLnRP5JawKD8Ik+I2OyRxSd7Z6bU/4orpTA7VR3WmgYyMtYCsdm+moYzInwxM0nvrp2EcbnaOYDs+CJ8JZsKOO3XTW+OkC18Cu8HrYHW7TuX73wd7wMZ2b+LSOvTwvz9E5jo6+47R9tUnclP3x5LpA15wtha7+MvXfhTrm9KnOqVyhYzGXwHnwUrgUrtQ5i5fDa+Cv1Z9X6BjT1Tpn8Rr4CFyv/r0ePgs3qH9vhC/Cv8Iv4U2avhthRSdqvy78GKbDT2B/uB+OgJ/CUXATLIB/hRfA2+BqeCe8F94DH4E=
*/