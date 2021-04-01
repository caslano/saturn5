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
+b97+0JK6eVwfXkFjsS2RMLo2E6wGWmNiWfZKD1KWjP0R4dqdX+BcwTnXFvom0ibRSj/nDy81uwEkkJBvuoqO/2ECNx5hL+IMwHAvrsYLfKNuO19xi/u+DrIU8F+AZ8rtHXjIyXXHo1dzPvur0KlOOdEo2mg8uQ57WDl3ErZs8OTJz1tQbBnM1i+D8MSAdpUYcpX6tVZclUDDK+BEnUVBoSq73xlzgcaieF2jF51YOepoL8XkWh46uRCMClLv4RlsvL+E2265onL85w7BgjnVnZErp7/DI1homi179paFnxjNHY6a4kLUEFpPlpcsUIl463mwktYFrM4xrSUW30J9SKZl2u3k4+KvAUbvOSB4/NSMgmEpwZBFFKQy3EyGE0nJiSfR5NrctL0AV39m9nZwj+/5Q98+/ysSaM4P/r9t1J9z0uJjBZbHX6RNjxjXlABEbOc+K6JJ7vBtNhOFABGVRRIu8/y2Lwv+uNv+s77fBTwSi89wMZLeo03FczONeqxjeba7gNDkeBah9uQmBQnYNocOVxl8WigyqPWWXNOb6FnDMJL9vbUAc11eg==
*/