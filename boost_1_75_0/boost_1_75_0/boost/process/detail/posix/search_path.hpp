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
F7fiTnF3d3eH4EECgQTI2uzszM7u7P/7ex9v7jv3zH3wu8hYHRg+8u5yXwSEBJJRiU4Hlvr8Fiy3PSkDScveElyUDsp84LJQ4pJ2jo0hhG8LxnqjYbO+ebND5Svn2oFT3kldoz1PXKN+338KReeuImiKnsinpn+0AQrxtft6Ux2yfZ9I6nYdtEKQqTjJsZkKJh6rHR72DSay+ElHhLpyCbsOidF7va8e3YVqHMPNGsGj7hOX5oakqFXbPi7w6jlgNicFJ8XzO7lZJ1XOs0JjwdSAG9JweFmXf14IfxXiD+Tah8qrkskj+97mi1WU2k8hKX/9jiKnn0KgdsUT5TrZkj/DlZJZcj/ChMLdvwtF9/MM3wyrYXvgPfz6DAUwz/sczklm2YixzbccnkpmoWoDOmrgFNWd76JOy0WM43Qjf4n+ml9g/rruLp9lcN3yrThZmcxF9KTInERsaTy4WbR/SLt1dPvWWi1nxank2X/zmO8mUrIp/qOHT4jGUSH8Ku0YpXyoNvHORQd/dTKoUvV9O4wdCHTKcWEyI7r/lAGIWO7HIMi4f2f+hkba/r1YhLfuSBkNovJ+9Kzp1Snf4bEA8OKUA9uFsyNqELh3IJST43k5ZKeMFTyl9oSd+jX1ljdVLSS1NvGH4w0p+OAxXnJGR1oqEG/xidOkIAe8e7t8Xin3CmZu0oxibPG9mYov0NKgnMbSLsMaqKZSA1Ds
*/