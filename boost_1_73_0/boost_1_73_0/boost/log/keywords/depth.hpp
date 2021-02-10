/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/depth.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c depth keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_DEPTH_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_DEPTH_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing maximum scopes depth to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, depth)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_DEPTH_HPP_INCLUDED_

/* depth.hpp
iUFNfwTtCg+2KSn6MHoENk8KAgugEe6g5Ng9GCrwzTwO0uhJxpJtiDrvHggI0FCCMSGtcwSeOYfkddpepzuaeN3RaDi6HL+pNL0cxhhgt38ZgxKewwILVykDJRqcuo2TNF3NgiRLyTb5Pfo92rcA4ddsAWC4XXAbJGCckBGwCm5CkCz+7F6aBWmQwHsyO1BxBwtEYt+ARlZXFGe/R0Ga+WTZMB8aQjdIyygKOGdAV2EGNlcM3fhJBEYRGlxTWC8cIEEj5kzDbOtTG+j392gZ32HjRfgJAID1BM1BudyGKU4o4HgXTMHIuwnAvIqwFQxrn0MD6LfBIVDg0SNALQtnTPEmMM7NKvCAd6N0ESQNUG1bsNLfwIL3V504WoQwxTf0V+vRrvkRjYckywAD2X5G/+5uj1iN37Kn6RKNvJ2fT2HFs5m/8bOlt0hiWFbRbc1WT/35PJjDyrPpMQNNl30tenzJeBRmEjV6Gqbewged4gVJEieNHF34T/PRPwE0qM9stmzQA4YP0EIhDMC4a/f63XOvN+hNTs03YKR6wwvvsns5HP1mvbsevBsMPwy84dWkNxxYLy+uBx187A2GE+9ieD04tz543T7PP2qP3lxfdgfUO0MJDN4MjM1fMRoPChF8kYBpCitiMrrunj0i
*/