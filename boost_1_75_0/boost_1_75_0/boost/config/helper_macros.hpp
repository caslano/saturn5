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
1jA+xO1xnoLMqSEiFyDjnDSpZXlMGM8YdgP95xbikCpxsfiK1CN24HWoVgxLKMctorkpuUAlswlQHuAyooWQ8T1Azl7r385K6c/VVbhJWInzUFigkjfEzx4tQPP3ZNpX+QCX590BmaYHUr7XeZu0Ud4mksqwL2VPpqTtyYYf4PFBH4bMNvp+hg+vVOpQTEhgnRxJTtXvsNQ/mar/Ncj8/oGUjqfSJEEdNslUeb95OtAyuUsZleNSL0BPCFEsKZrgRJocUv6obrh4LdcN3wqZ/ZB83FSefDkzWRxuYGI/codvJewQR3ID21aoLTz7I8l0Esc4pWE27yXajKUp9TJ5ary9HVUBdV/MU62wDkiPUqlRdivFkJarLfJ6aZVQg4e1jXrc4Xau0lsdRc6ko0HrdzW6Wz1hb6Mx6FtvlHh1V1AukJqEItyIin2we8gBNzsdqjkVauPtNEK+9B7rhf7QZ+yP6n/m8WnvhMy6fyayV/pd9CPZRjFuOrGUsmomKqN+vqXQ3oq1oUr4pjhPlcJG3I/apAa5RQmrSa3P0aIlVK8UBH6gH7U7iDIsQOQc2p/Qxs9TbbQN//9pI9FTWdr4x+ZGcpjPjbsgc3KY2A1Q2Ca5a3tDZp4k+Twh137zbOGT4vJ50r6CInFGSsCkoY+1r0cFuE58RxiXYjCn3XIxpHKpXSlUGzW3oxhSi9Yl9ehbXXGn2zXi7HL3OFv0
*/