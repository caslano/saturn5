#ifndef BOOST_CONFIG_HELPER_MACROS_HPP_INCLUDED
#define BOOST_CONFIG_HELPER_MACROS_HPP_INCLUDED

//  Copyright 2001 John Maddock.
//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_STRINGIZE(X)
//  BOOST_JOIN(X, Y)
//
//  Note that this header is C compatible.

//
// Helper macro BOOST_STRINGIZE:
// Converts the parameter X to a string after macro replacement
// on X has been performed.
//
#define BOOST_STRINGIZE(X) BOOST_DO_STRINGIZE(X)
#define BOOST_DO_STRINGIZE(X) #X

//
// Helper macro BOOST_JOIN:
// The following piece of macro magic joins the two
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expansion of macro arguments does not
// occur in BOOST_DO_JOIN2 but does in BOOST_DO_JOIN.
//
#define BOOST_JOIN(X, Y) BOOST_DO_JOIN(X, Y)
#define BOOST_DO_JOIN(X, Y) BOOST_DO_JOIN2(X,Y)
#define BOOST_DO_JOIN2(X, Y) X##Y

#endif // BOOST_CONFIG_HELPER_MACROS_HPP_INCLUDED

/* helper_macros.hpp
QH23uqZiBN6FR9ZIqj4LYAFHswQfOughdwJiNKM3NAcD74bYElbKEkv8odTz1eUuhTI30/Is43KNiWsbWeNcG4KrpyzhcnWyU9u2U4wVNH6l7OJcZM+WS9gwpszoByw3eD24sseKj5UVk+DLFqmi1PbZCzGJWEx9z3S2DzIvGFd0OrMRPw64zKlul5CTcCpMs/GAjobfnpNNY3JfnjsAwAC/BNySys8kMju9rTvtJVjIC+iriHeNAMUGwjUXToMB6NPzbil6UA4PkhXchSs9pSqQIcebK+s0gdeF+d4sLfrFxDOteLhqAtQRR7TTEtvR6JS7cpslu0IT+jZR/qPBtmgN6gLD3+fzxMeDBoIlbirOsu7A/4R1r5WTUhXijYZaYp5FQqgSr+Bz0jduxjnx1STlGGIq8nnY/wD4DFXH3M1BmNSN+ZnNqsdHTZgUcYIJcNKTD6uaZ5sqVo4xsBsox0EvRwajSZqrVZQXY48Fmz4qmFB0mPlD7J0ZF280VjeY6kyGNovWkrubqLFmjEOGGzpwLjNirFXOC3v25nC/y22Onp/EZxQlDso4MA==
*/