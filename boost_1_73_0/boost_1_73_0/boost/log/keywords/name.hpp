/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/name.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue name to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_NAME_HPP_INCLUDED_

/* name.hpp
/uHotZOvHP0Ua6HcijCGr5BbzjWe4yuwi8UEusKNKlLemWEtr39Yy5vJT6/lp9fz00fD2knczHy/Y773mQ/GI/X0RLjKIWwEY5MiOsTMiA6xlp8+yE+38tPPIsG1og+EvSF1UYqccJcAvcCbM+FIrc/ENMfp6SLhD8bpk0WKFpxZKd8Thjn6ohgN4IXCvzJdLPTESAvXs3LeKaO3zvQ0lyVAhPJgxxeW04TqSEjG2VNNqNAy2BryUob5Q8sA55w=
*/