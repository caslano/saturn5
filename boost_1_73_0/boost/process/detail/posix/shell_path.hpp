// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_SHELL_PATH_HPP
#define BOOST_PROCESS_POSIX_SHELL_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/filesystem/path.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

inline boost::filesystem::path shell_path()
{
    return "/bin/sh";
}

inline boost::filesystem::path shell_path(std::error_code &ec)
{
    ec.clear();
    return "/bin/sh";
}

}}}}

#endif

/* shell_path.hpp
QpONpRX+lxJCk8YBUgNDiZ3eU5f28ZElv+o57/beKcGqlQ9VsnCo0D41X4b2WRZtvpZgr05B8wZx7xtl89twtEieU0h+acPnaYZgb+bQAg4BHeicqFtboEIS9nRIBM6maEtk2L5wJEXO0zVhGy9Lu5UtzbZ4lVkWJ9cOjPnERlVB+BysJTMpjbgKHJBgLpdCVyJ49p8QJCzQ49HIAgg1FCAf32P4877SoqwwxVONm15M6cnI
*/