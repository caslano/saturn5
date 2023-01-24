/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/enable_final_rotation.hpp
 * \author Andrey Semashev
 * \date   27.11.2016
 *
 * The header contains the \c enable_final_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for enabling/disabling final log file rotation on sink backend destruction
BOOST_PARAMETER_KEYWORD(tag, enable_final_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_

/* enable_final_rotation.hpp
H6TbZUdlJsFVfUJbWZecD4JAvE48qRBwT9V0MAIFss19KeR/167HT/LlpYKDAe4fHPkwZvFSIPwSEt2nNrYEcyEnNE512a7ixa1KvnJOiw6nI8d7tgRKsu4Ws+4e1fEaS3HvwkjTH7LvPjAdmVS8bEb9frxi6FL1OfnOSmOXnb5Cr+mWEJ5toawV13Hx9qayY7gwaq5hVMMytPaTXmG5uiBL2TJDderEAGEymlSP8Ivg0k8H2XK9ZdTVFBfnOrEaOR0fIvB18mzFfC9Xc84vdWiYYczTZi5KSlHUHUmZxJuLr84K2eXKGJtE6oHAerFg4xEvhdsh9vnEVe6iQdpnxNsboI4f+Hrj22CTSt0jYijrPQKBp4AMef0dFOs7eqgSCQ+QPZXx59GE3yMLNwWv5w69BuACPbURfgkvY6AAvN4LzEevgVdKIHVnc5c4HEc4YEXMhjadFYH8xyRnwQQiySh7Q2pqR0rxFkG5Y6CJhnj+88VL9hJcsR/Jr3BdxRKM6Hh/R94TMNCJ03nqtYkO3LgA7SPibLpK2IKlMp58whFsF2VBYDRj9psABc9MKaxnLNVt7r/pHmHQDr4EYRniAPM4JDgGHucCAm24QawBtL0KmA9V2MYY7g+iP/Z9unf0xv+WjbimrzGljCFiVBG4iACkv6v5K7pl/Pr/VTPtf1Mz/1/+fsuYuVn+TcoO57pG9sRyRJK+uV+ICtAf
*/