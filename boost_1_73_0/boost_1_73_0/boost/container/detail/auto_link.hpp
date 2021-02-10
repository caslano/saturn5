//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED
#define BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

//Define BOOST_CONTAINER_DYNAMIC_LINKING which is independent from BOOST_*_NO_LIB
//and is needed is some tests that need to disable some checks (like operator new replacements)
//that don't work across DLL boundaries
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTAINER_DYN_LINK)
#  define BOOST_CONTAINER_DYNAMIC_LINKING
#endif

//
// Automatically link to the correct build variant where possible.
//
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_CONTAINER_NO_LIB) && !defined(BOOST_CONTAINER_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_container

//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_CONTAINER_DYNAMIC_LINKING)
#  define BOOST_DYN_LINK
#endif

//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif   //#ifndef BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED

/* auto_link.hpp
agqTKF4F4V8OXFUsrwaeG96DqHhfF1CRSwodzSm7NDQt6STwEhmQv2BCImcvGW9clKcgabcVA40KgtSCA7kkrCYblCMSKilb8ft4nPddjScZFzwX43xnhVvJ7aNTrTCaLbkB3kqQHHpBHVD7HdjygpVqRItwsu03NROVcxcWCjbFmHcgaF0PdAhlVJgjUEgGtxy1E1qMnkk1CN4IpXZV8e2DjWjrQFT2XYNyaAvuKzga70DfFLTT+7URO5XBZW35d1J2F3sBvMGowPYSCBIbNkQw4cB5kJ5EyxTOvcXCC9MVRDPwwtXAdxqEU6wNhqod0Ou2owKj6IBt25rR4oH4D+10y01PYLJczINwFmVJ8I+fLeN55E2zFN6AfXgEZ5jDw4PXb22wa7ZR6Ye37tGRe4AT6l9GibjJLqhkTclVtrGoBPImJxB6Z771P+TrV4AYbXPTb7FblOl9W3NSoIWbG0mF5khWYRQnQWL9zJq87gsKx0rV1GH1wdL8Ocf5J8GM1BLsV1giNVbK84E4BsfLMpOwbwJo995r7amfTBZBnAZRaMUEM0Kg5ayRqlawPWBdBnfgdRmr2aHpTDFxSWogW943uvn0qXCFSOuKYt3sjutqtXgRpdEkmieWp6oeZ/y/vbN47ltuU1rmLNr+
*/