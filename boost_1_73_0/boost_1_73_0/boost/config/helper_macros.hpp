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
vwMbnrNCr1giNDbtumKydO5pYcI6H3EBklZVD4ehjMruCBTivlqO9oQG2TOlF8lrqbNdl3zzyBHL2gMVragxHZYF/XKOhXegrXMqjL8pxDZLX2VT8hdads89B14jK7C9GPzYhjWRTDpw4Sen4SKBC28+94JkCeEJeMGyxzvzgwlqg2FWAfSmEVQiCwFs01SM5o+Sf9NJt9zkFMaL+cwPTsJ0HAbJNEjS2TT4lJymk/AimIXeJE3gDdgHh3CO/TzY239rg12xtZYCvHUPD909NOhvKSXyNr2kitUF151HgUnMEZ9C4J1PrVckWu0CxmO7axwitVvR+lKVuiE5v64rTnKDFi+DMIr92Pqe1VnV5hSOdf5OneUHy2TKONqf0RroLdgpUTgV6udlSo71PxeGgedFkSrY6TmnHefhe8N0Mo3Hcz9K/DCwIoJdJdBwho5C64/AqvDvMVZFpK394BoNPi8EWq1tMdxOifirfa9I1eqxJzkUoh+AcR8/M/FHqGVaYVisOGoMdveBFZb2k+xPLeT6JwVfakR3DftoHibhOJzF1mmSRIN4aKzT37zzaDa13LqwumoaKfzyoNisZmqAJWDFQBuH8JcFD7YlVagOs9W1IIySFBcH7O1FQ28Iip+6Gd/YCIThox2IqCi4
*/