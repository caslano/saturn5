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
t8m3KcOTh3P83LEriblz92UmGr7GKcl+/CvoPsZkSHYKf/oYk+IZ32EmYPbJDiajhjWu5QUVpwTxrTXT1sg3Hp7nQDavbzzMPBeWPEdK/6/09UrePL852yXjj5pKmTRB5kfQZnQrk6wEMpmckJqanqjKxaHnRPRZLmpfz7E3WUPvTfZdJjquLpMkFqHK0GO1vlThZfQ3Lw8Vop/td5SHw8dchqo8VJ7+nH3dmx8y7YHRHwTG
*/