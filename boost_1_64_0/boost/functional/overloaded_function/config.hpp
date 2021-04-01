
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_HPP_
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_HPP_

/** @file
@brief Change the compile-time configuration of this library.
*/

/**
@brief Specify the maximum number of arguments of the functions being
overloaded.

If this macro is left undefined by the user, it has a default value of 5
(increasing this number might increase compilation time).
When specified by the user, this macro must be a non-negative integer number.

@See @RefSect{getting_started, Getting Started},
@RefClass{boost::overloaded_function}.
*/
#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX 
#   define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX 5
#endif

/**
@brief Specify the maximum number of functions that can be overloaded.

If this macro is left undefined by the user, it has a default value of 5
(increasing this number might increase compilation time).
When defined by the user, this macro must be an integer number greater or
equal than 2 (because at least two distinct functions need to be specified in
order to define an overload).

@See @RefSect{getting_started, Getting Started},
@RefClass{boost::overloaded_function}.
*/
#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX
#   define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX 5
#endif
#if BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX < 2
#   error "maximum overload macro cannot be less than 2"
#endif

#endif // #include guard


/* config.hpp
JSxV4X4+Ux4609rykSArlx0xv5lp0G3kD6LIBnTxG+9DHhdMHeuYEXQN5alsY0HbMqhbZats2bL0pYwKbOQn8UB8Hjl+3Kele1h7r3bQC9LTjzocXRewPudZvljhRLtjDkB2GomQRhWv2a1h4dxHzcOEpDvVdf97bXA6nIxPXPu5EnZTDIL+c/9xDJnJE0/lWg3/kSvuNBDfZzzdEdJzPfBFp+dlHzmdWJQimpOxD5/JUBXFk2WCyOjx6EksqxqmGlNa6qqPm4kv04neZYVpV/4skO02Z4WME+mEi1pFpMzFzttZZJbUuiYd+K4rZwrDYjDVgnlHZ2ili4NbWZAwYgDm/B6c22h5r1WTnVDW9shHc/N8NmegbGsFQFZX6sboaTCQGyX0rs87EgaZs3h0V3ZbWD2XyAAv1hkeL/djcO4hMuNFllrUL9+F5R16GLBVtSNRn38v7kOhwo4m783QFg54eOnXT8wBYTzc5J6VUToIjXdO/JYpQ6eP+sIyL+bIfcK0ul/fCzf8tedtPiEDa6ftuRKmYxyVXuy/TsoUmt+asn5Wl9ov4y6+yw==
*/