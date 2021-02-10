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
ewq9hsnNzhLJ2lhdIPDGv7tU3B253cSOo7s2vz7EGDLHXpojl6tBE6R2IqmGZIQhDreJdCKQ/HQX1WXvzdsJbRpLvUBC0hqVfn/RnrPUpXtM+YmpdLsOeDhotk0SwNWB34fgCerNeEW+qMoYI9Gnaizwij53h+xNkN80afu02ul+TAgIM36G/o420snJhUe0i8KLI4Qi0cB2qkruGDKwxrroBwfsHCsmJC3VL11sEIrbVm6BffntM8JptM4qKIJRraT8BgvFvfolFuZQMdUsoOwCmsSYCfrmNz2cFmWqY16Y674GvU3BxKW+V3nf04A9q9vVswdyDXJL4V4ZDQ1XpKZFNbVRp+AUycIl/JpOkOGxmAubd8jxvluGsyUxDS9cyqcOpqUpbl2cxvyeUuG4Y52EQ3vwjri2mlDc2dqZCK5uV2lZt64kfvZiluBv6yR98Wy/UD+igiwFdnCgaTKf2IWzyiyIydqrl8NUfp+KW0t9VZVonpp1BXasfZWizZSXntCCTxqDVrq5/6zqizxDNVlUZEAwnTFPOlCrtk+5rWceTbUHbnphdoJA7avI+E9tLwkdHH5gi5f6hFWGrAGuW3n9PXEnKXelMR9DeSJeFpPtakUrym7qEWPdi/7FYRrN84+MTINiPpmD7g8i
*/