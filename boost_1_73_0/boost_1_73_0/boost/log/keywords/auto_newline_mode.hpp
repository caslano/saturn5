/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/auto_newline_mode.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains the \c auto_newline_mode keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_AUTO_NEWLINE_MODE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_AUTO_NEWLINE_MODE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing automatic trailing newline insertion mode to a sink backend initialization
BOOST_PARAMETER_KEYWORD(tag, auto_newline_mode)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_AUTO_NEWLINE_MODE_HPP_INCLUDED_

/* auto_newline_mode.hpp
E648GnLUDIXGkewS3iH1d7BXLQsgygujSwiIb9zSuVJS6cqkjcxpWgBvtLfABIVBr3a2t79Vq7w+G89mZ8OjUQeD+wNF/+zCixekU7cENNDrHWwHvm/f0P0eHB5ajZo81nomMccYRLZEvsVpg2+QSy2o2WCNDRBJpCwPPhfaRYnUh7yMNNKsmpRtkNE2VYngfPaM+qUR3b1L7FC5d6O1EobTAj0r+RL2Pfq/g2il5oBvX2XtR4QomS8PK4MHtGL9ReSWcnXOAmRhKethUpZ6NwqtJpI8QW76eisEF/JDEbh622tacncqZj9SnN+uQxL43kIuJOIe0Wazg3niO5gLlTJD9J8ifbMlp23AuS4Uju449ztU35ylHiYeVlwtJIaNuSRzuMPhccgR/qBlmYZsP840dxgD+v2+I4YbojhwX8hhynRY7gEKVpxQwWMUYm6uc+7K0HFc5aTGmFZ529lolWdhx341cVk73v23wOAunKAcmSGSgk6vp7HPMuwnKvkmRg4k8vR/gtSEora5PAZFDYmYJ/n9MCzxJJaVC++7Q4WgtsZjgAUFWxIbVioypXjCjDuvBDJN6biT0H7F1LJIER9dKxvyGHWOxycj2HWWHoNAWLKu+KoJyAOQbHu83B89qLqL+thRLtFR2b6r
*/