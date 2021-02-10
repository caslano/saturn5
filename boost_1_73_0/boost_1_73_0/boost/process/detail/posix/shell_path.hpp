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
Y1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL+4mtwSwMAAFEIAAAeAAkAAAAAAAEAAAAAAIJzLwBjdXJsLW1hc3Rlci9zcmMvdG9vbF9lYXN5c3JjLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pScybfzj4HAAArFwAAHwAJAAAAAAABAAAAAAASdy8AY3VybC1tYXN0ZXIvc3JjL3Rvb2xfZmlsZXRpbWUuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL+m5zOuAIAAGkGAAAfAAkAAAAAAAEAAAAAAJZ+LwBjdXJsLW1hc3Rlci9zcmMvdG9vbF9maWxldGltZS5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpw2JWFOGwAAwmUAACAACQAAAAAAAQAAAAAAlIEvAGN1cmwtbWFzdGVyL3NyYy90b29sX2Zvcm1wYXJzZS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnecH4NVBAAAMQsAACAACQAAAAAAAQAAAAAAKZ0vAGN1cmwtbWFzdGVyL3NyYy90b29sX2Zvcm1wYXJzZS5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgMASTI7RwAAqDABAB8ACQAAAAAAAQAAAAAAxaEvAGN1cmwt
*/