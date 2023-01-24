// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_BINARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_BINARY_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_BINARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_BINARY_C x BOOST_PP_COMMA() 0)
/**/
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_BINARY_C(x,y) \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <boost/preprocessor/detail/is_binary.hpp>
#define BOOST_PARAMETER_IS_BINARY(x) BOOST_PP_IS_BINARY(x)
#endif

#endif  // include guard


/* is_binary.hpp
qpxxjf5uutV1jqAJORL8LfFeF24xNbyGSC4RHx1X2AJOl9FdYXKxcj6sooP2owloF/DuPM5GSHAo2DHmdBgIIh//claL/RIvjlQuxiUb+rZexEIvt54uOubOfwuK9cAULHIHlwz+zUL8rg2VGKur98d1V8P8+VwsBoVIAJUujEAwKBgmMBR+l4NGpIUt4GMjzIcssdZj2VWjpFiQHe6eSXq9lIZKSCJwdWfRvddNbOaQ+mqNFicOxXc8UPSv55wA2W5+tMuX5YGpr70PeOpGAteIJlPRcz9TOksjzD5lhyEzXvC+Nm4vhB4KpdFG59ZOfNBim7Q6Cn1gAcmwKy1sVDhZgi/M0kUGXJ7K6zMjHWywrtHuQ+Wa6kpzyL/C2Vy3mB+o7vttvaX4u859HgWWg2BH4RfCBsHkT3AGB4kKVE3/GHLeh9OijcLn6+9TCFndeCe/lEwxANkBkoqsP+bqKULVzlUbc7nXPUOKQVZrE4ci5FFRLmgbb5MVC/ASXEmrterxjV/MJap1e09V6yt/YlR74U9vj853Fq9S1eZUozSkq8w6uwRyo0bKrqOX7Hn0fs8HbwgwWV4tmb7vVciTDcm+EiXCNCJQ6duvl2RRptfG7WBd+dJQt0n4S3wX+356gb8wf8LcTYeR2dht0eDEI+m8ZfY3ubnSFyrL1ZMxm5wiXq5NiunznM9PyYHqQjeZrssEFDNq8RrS+Vbq
*/