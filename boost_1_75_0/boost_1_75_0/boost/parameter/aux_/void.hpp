// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_VOID_050329_HPP
#define BOOST_PARAMETER_VOID_050329_HPP

namespace boost { namespace parameter { 

    // A placemarker for "no argument passed."
    // MAINTAINER NOTE: Do not make this into a metafunction
    struct void_
    {
    };
}} // namespace boost::parameter

namespace boost { namespace parameter { namespace aux {

    inline ::boost::parameter::void_& void_reference()
    {
        static ::boost::parameter::void_ instance;
        return instance;
    }
}}} // namespace boost::parameter::aux

#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))

namespace boost { namespace parameter { namespace aux {

    typedef void* voidstar;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* void.hpp
jzWSudGANP8gL6JSR658oe2QU6W55X0K+Aq/Ku9+n3SeqvA2budi7nq43Hy9JSsOy7PgeS8lhyW2v/J7d08LNenWBVC5hyXI2LTo08iSigKFTJL87+63I1zy+/IJSvw/Gx0e6hn3vvPZMXG3cwGkJ4lC7uv6ZlTgG4M8q79yv4+/FlXzC5n6CkBqSLh98m3tx7fHEifN4UEYnAGR7FmP/0rP6rx+iJmjiL/SM8XxrNOo8wPIEKQBfAG/yJQSmE1E1NwdgbXDEI8RTl380MJrCdLNXbPf0OWBdQOFRjIYyHDibF8Z6sbEcl7tD59EuX/JGakaZTuWX+n6pz3f/cue71YQ/qGOA//BntnQNpE68D8R/tWe9ZH1MT4gVyPdhS6H5iK3H/etvJ51KfEONUI+Q6ZESgxNzBnFyk/bJmtDBogUUTdQN0Q8OEu3YM0VbzwwtzwjvkI+oteippRqOLn1cJK3hvswUFxJfBC1Rtud3zdns2cMoA4cb91rnDENQd9tFM/Fesx/+HLQMXTf+2zaPUv9ysgHEbpx0pUUzHtiGIu6otA+GdehMHbaOXnSTCWyctVuhW/3YM6QI3MVIX2TRewZKJwP33+DmVoZ+ntL7x26y9ip997Mp9n8lWt4jAgSvjEzjU4J5Li+INicrK1EGtb9xq7PtF8ar0gJqn4xhExU7vUSqxy1jbL19qLLmXnnUCJ8pVGe2/ABW8ay
*/