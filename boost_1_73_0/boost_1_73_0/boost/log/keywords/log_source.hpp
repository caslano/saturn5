/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_source.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_source keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log source name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_source)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

/* log_source.hpp
u6SVIxcQrbHzp4XRfxYnWUV4RHkmDWSFLbjBzTyvE9Nj/lMvR69KQ4xfdRhTjQnYhEJMwB14mll7Iw1YbgJxK9KjY8/5XFGfcRLeeFGsTLUXKiM6f2h+HKZ+lt1rH/IHWuc7Fyf35AxGR/fawf+Uws9PIMqkfpnTgwWzVM6+7ALPbIiVI026/CXmGgro+dJAQ8Vccqbjdi0syhwyV9kLqleCLSmtV3Pn6oyLHidzWF8OzHNvxVz3lZ9WjkPkcixUBt4+8g0IgjXYT8l9Mdpi8pxdRYD/5BEXGdAYBxk6cQnPXWjUXGFqXFHsoWH6CmGMuv/tve22z0/lH2+6k+ZOUIrVkBKAhhX2tcalVWx6gINYOk4mUR33Lq/63avhWORimxg9qouNOglox1zKFKrQlFZ0Sp6PkSA/C+s8V1+RKmelVYMQtv9qhVYjlTNl5NkoPWG2x3IVcpklWMwxFV0qTUHmynadZ20+knVoDPlwaCHEZQVvnopdNcx4oNPYpH02mH6RRDleJISApqgvsKnQUYbO4siRVFO5sbqEUQ9l2OqVBd8lYc9cH3gqDAZfwe9i96xIN2P4SqOLv8HcW/lA/McMFgIuSJlfmrOFNg4VqwAAhvA3awZRK0M3SFz00WmTmS8P3gzzfPP2Z49c
*/