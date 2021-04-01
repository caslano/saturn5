/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ordering_window.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c ordering_window keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering window to sink frontends
BOOST_PARAMETER_KEYWORD(tag, ordering_window)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

/* ordering_window.hpp
LBvRFr6KILbVmkCn9910cQNAw6TRackBqZOMqBA0AjmOkXcQCe6aoV6AUW+ykfdmd8AXWn+FeGqpotF2dUZ/bDCDjUQdxd3uvwVNPQM440FA5PuMLhaMIVWOzuUdpEIp+gm+FX0nGJDOMF+Jc3fOaKgydTxldRNNW1eNWJP42uFC6V9a3PPgVk0rLCMHeRjT2aR/cWoO+K/ngFKq5mvz4Z8ovgXkMhE5B0lDDL4IF6x/BJ7AkdtrfGMXu7mygLoBCS5FSZWtMp0VujoNzh+/I+SbScJVVVx+9t+z021tkXFxMwLT1gOnEQgL+dHark2V/FtKJe5gDj3YDYAQhyU/aCh9iwRR6cOiHBxE3q5y5jwZ2SP6Leq/hI2JUigK9X5yEbpM65BVZZLNt5PZEdqbSVLg+uo+iNOXv2v7Y2lEweUYoQDSyBW5gY2X+4sgm8ZsgXUcFZHgCsqAk0pgvQKg4R9qs1WJRc4BRtInXt6UzKeZJjFN3//znAPQP24UTQXo9MXEkXkNSTMFNkiGE737bwpZrTd6/zJ6zxu5sqjB9UGI7KGb1k6waVBSyA==
*/