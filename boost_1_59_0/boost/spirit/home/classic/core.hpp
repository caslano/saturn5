/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001-2003 Daniel Nuffer
    Copyright (c) 2001-2003 Hartmut Kaiser
    Copyright (c) 2002-2003 Martin Wille
    Copyright (c) 2002 Raghavendra Satish
    Copyright (c) 2001 Bruce Florman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CORE_MAIN_HPP)
#define BOOST_SPIRIT_CORE_MAIN_HPP

#include <boost/spirit/home/classic/version.hpp>
#include <boost/spirit/home/classic/debug.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit.Core includes
//
///////////////////////////////////////////////////////////////////////////////

//  Spirit.Core.Kernel
#include <boost/spirit/home/classic/core/config.hpp>
#include <boost/spirit/home/classic/core/nil.hpp>
#include <boost/spirit/home/classic/core/match.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>

//  Spirit.Core.Primitives
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/primitives/numerics.hpp>

//  Spirit.Core.Scanner
#include <boost/spirit/home/classic/core/scanner/scanner.hpp>
#include <boost/spirit/home/classic/core/scanner/skipper.hpp>

//  Spirit.Core.NonTerminal
#include <boost/spirit/home/classic/core/non_terminal/subrule.hpp>
#include <boost/spirit/home/classic/core/non_terminal/rule.hpp>
#include <boost/spirit/home/classic/core/non_terminal/grammar.hpp>

//  Spirit.Core.Composite
#include <boost/spirit/home/classic/core/composite/actions.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/core/composite/directives.hpp>
#include <boost/spirit/home/classic/core/composite/epsilon.hpp>
#include <boost/spirit/home/classic/core/composite/sequence.hpp>
#include <boost/spirit/home/classic/core/composite/sequential_and.hpp>
#include <boost/spirit/home/classic/core/composite/sequential_or.hpp>
#include <boost/spirit/home/classic/core/composite/alternative.hpp>
#include <boost/spirit/home/classic/core/composite/difference.hpp>
#include <boost/spirit/home/classic/core/composite/intersection.hpp>
#include <boost/spirit/home/classic/core/composite/exclusive_or.hpp>
#include <boost/spirit/home/classic/core/composite/kleene_star.hpp>
#include <boost/spirit/home/classic/core/composite/positive.hpp>
#include <boost/spirit/home/classic/core/composite/optional.hpp>
#include <boost/spirit/home/classic/core/composite/list.hpp>
#include <boost/spirit/home/classic/core/composite/no_actions.hpp>

//  Deprecated interface includes
#include <boost/spirit/home/classic/actor/assign_actor.hpp>
#include <boost/spirit/home/classic/actor/push_back_actor.hpp>

#if defined(BOOST_SPIRIT_DEBUG)
    //////////////////////////////////
    #include <boost/spirit/home/classic/debug/parser_names.hpp>

#endif // BOOST_SPIRIT_DEBUG

#endif // BOOST_SPIRIT_CORE_MAIN_HPP


/* core.hpp
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
*/