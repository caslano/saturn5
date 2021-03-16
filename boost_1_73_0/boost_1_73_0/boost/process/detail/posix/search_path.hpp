// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_SEARCH_PATH_HPP
#define BOOST_PROCESS_POSIX_SEARCH_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

inline boost::filesystem::path search_path(
        const boost::filesystem::path &filename,
        const std::vector<boost::filesystem::path> &path)
{
    for (const boost::filesystem::path & pp : path)
    {
        auto p = pp / filename;
        boost::system::error_code ec;
        bool file = boost::filesystem::is_regular_file(p, ec);
        if (!ec && file && ::access(p.c_str(), X_OK) == 0)
            return p;
    }
    return "";
}

}}}}

#endif

/* search_path.hpp
hx4U5aYp5R72lGN9N9Wj2zNCOp0Zgs5MUdb/fVtetLCMrSbLLS7lk3OyC/wAzpz2TMGbc85RFUarJJw7KuK8d2Z+oJp4llNov5y2dWF6P9bfpcPKh/Ozjmb0Y2evlaImOp4szjmapehGyf/I43THj/H+nKPJx6DHhXzmKnKeo3x/WfGDDynP71W+P6Pg3KE8nxKK7S+pi7K/Foj6F/rgzvfgPi9wF6m6FNL9LyvHeC4XOj3VlqFFS0TZF1V98ik=
*/