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
19yuy6BhxJnE9ZycmSvwa7HKFVvhFHZvFCg2TA2SXguONUSOLn8shYaPhkwahhD1qyJHfOUrmKX9bedUeodBFR2rIAxBgm+clxWPpFye4KEQQiESK9kDX2XCjR5Musf+c/4aoRsh5sCeO5CGB8d+rG/FMnBEY7wokoTOeIivIjYBCrZrZfcS0e2hVkBMVK2jyYF3BfnBLJyOxQzmbGDSbwrofILMXzWuH6iVBKYT9ZzO6cJOwdBgAxjq9CnVkiugV5ogd/ml1Z85AQDpTGmwcVyrlV7XMjYsPscygaFd85Ufz0kSKbDd0BEbJYUXkRG40CCAWScJ8/c49h5YR/GW8VSk7Gtu0/f0lVRimIBdBgvpH4X2/guz4quq1SxFArZSjqIU0mfZvGWLN+CtQ8w3kXCLQcJs8o1fs4BoydbkvHqJK6/6TutTphwA4W5PmJ65f1LW0bztM+nP7ozq2uW4aVQyFXCXF17IuMeNeUBh1IOkTDlZSg/+mFZdYCKrG0Mxkvjy7IusCaK/DtSuFhNB0V0tu7G0XkFKBxm9OXszKhosYAOoMfFBALOXTQ==
*/