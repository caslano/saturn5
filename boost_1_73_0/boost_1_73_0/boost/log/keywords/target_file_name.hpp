/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/target.hpp
 * \author Andrey Semashev
 * \date   05.01.2019
 *
 * The header contains the \c target_file_name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TARGET_FILE_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TARGET_FILE_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the target file name for file sink
BOOST_PARAMETER_KEYWORD(tag, target_file_name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TARGET_FILE_NAME_HPP_INCLUDED_

/* target_file_name.hpp
V30wrtKIta6xeEDZel64MZIXxGv3AyAjRnF0QKXs8RVOWkvLmS0peK4XKtxGG58XE5tu0/tCLbh6xbVqHkEtIT72iZ1/HeJXCuOT7w+fnZZohXmEJmWCpltdvXA+GHvj7gjdV60AiQZnh254/rwaHQqPkoh4AEIOMWPCciaV0ieb2+89fz6vrRexOzy23Pd6V99b3SlYVd39aHVXt7MfC539KDurJPiPhydl4tphO026/UF3UqjewUtXauU7Krv8S239MGoPzoeXVn2TxI/m8dqzfJQqMN035+Nh551emSe4mZdCKNghVJ5Iq9vh8JitSh4zXpyooqCHPvPx0r7Tt3LWh2958T+7fYmJGW6WQeLhZD4kRbfTu3rbHXlYTUgzJTRYJSnIfK/44X3mcQm955ox+N148S+Onz8Ip0l/DC04PmObChLWbjo8sFdOCbPvB9HBgZnbDD8plbRhiodfvGCT3lplNsUrLAVbz9WcXGGhCa97NX5v13UuKQTyw06szDjwn8JqNHFUm5aWGt6BHFAW4R7eZAIaBJT8oFtSo8Nep5gAYSl2yq6sq9UJAFfpykLd3QpU7+vhuMK1LwSWfjaLPxpnzm/CKPiSYzywkLuDN72BJrcFMOdZmboHSopBsWeHf2nhbdVBpEoR
*/