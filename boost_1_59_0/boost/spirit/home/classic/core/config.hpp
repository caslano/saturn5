/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CONFIG_HPP)
#define BOOST_SPIRIT_CONFIG_HPP

#include <boost/config.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Compiler check:
//
//  Historically, Spirit supported a lot of compilers, including (to some
//  extent) poorly conforming compilers such as VC6. Spirit v1.6.x will be
//  the last release that will support older poorly conforming compilers.
//  Starting from Spirit v1.8.0, ill conforming compilers will not be
//  supported. If you are still using one of these older compilers, you can
//  still use Spirit v1.6.x.
//
//  The reason why Spirit v1.6.x worked on old non-conforming compilers is
//  that the authors laboriously took the trouble of searching for
//  workarounds to make these compilers happy. The process takes a lot of
//  time and energy, especially when one encounters the dreaded ICE or
//  "Internal Compiler Error". Sometimes searching for a single workaround
//  takes days or even weeks. Sometimes, there are no known workarounds. This
//  stifles progress a lot. And, as the library gets more progressive and
//  takes on more advanced C++ techniques, the difficulty is escalated to
//  even new heights.
//
//  Spirit v1.6.x will still be supported. Maintenance and bug fixes will
//  still be applied. There will still be active development for the back-
//  porting of new features introduced in Spirit v1.8.0 (and Spirit 1.9.0)
//  to lesser able compilers; hopefully, fueled by contributions from the
//  community. For instance, there is already a working AST tree back-port
//  for VC6 and VC7 by Peder Holt.
//
//  If you got here somehow, your compiler is known to be poorly conforming
//  WRT ANSI/ISO C++ standard. Library implementers get a bad reputation when
//  someone attempts to compile the code on a non-conforming compiler. She'll
//  be confronted with tons of compiler errors when she tries to compile the
//  library. Such errors will somehow make less informed users conclude that
//  the code is poorly written. It's better for the user to see a message
//  "sorry, this code has not been ported to your compiler yet", than to see
//  pages and pages of compiler error messages.
//
/////////////////////////////////////////////////////////////////////////////////
#if     (defined(BOOST_MSVC) && (BOOST_MSVC < 1310))                            \
    ||  (defined(BOOST_BORLANDC) && (BOOST_BORLANDC <= 0x570))                      \
    ||  (defined(__GNUC__) && (__GNUC__ < 3))                                   \
    ||  (defined(__GNUC__) && (__GNUC__ == 3) && (__GNUC_MINOR__ < 1))
# error "Compiler not supported. See note in <boost/spirit/core/config.hpp>"
#else
// Pass... Compiler supported.
#endif

#endif



/* config.hpp
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
*/