/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the function boost::iostreams::detail::absolute_path, used for 
 * debug output for mapped files.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED

#include <string>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#ifdef BOOST_IOSTREAMS_WINDOWS
# include <cctype>
#endif
#include <boost/iostreams/detail/current_directory.hpp>

namespace boost { namespace iostreams { namespace detail {

// Resolves the given path relative to the current working directory
inline std::string absolute_path(const std::string& path)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    return path.size() && (path[0] == '/' || path[0] == '\\') ||
           path.size() > 1 && std::isalpha(path[0]) && path[1] == ':' ?
               path :
               current_directory() + '\\' + path;
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    return path.size() && (path[0] == '/') ?
        path :
        current_directory() + '/' + path;
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED

/* absolute_path.hpp
0Ze2VdEJ8sl0lQzJpncXZzLFHSAt3d6U+LLoayFUeVPM46i57bod9r4w6FXsf0Eg+jC832X19m7wM+JOvOf5fcf9kid3LYDs1vrEAs3lye6u8k4g3KbEDwtri65C/cODppPgm5ifW1MX8/rx1uFDCG2QjVVNJOUQGg5YpEmyS+A1PZ7w1VTfrBu+qvBuVnSrq1nrqm2soZ5g763xNuqqeglp8eZtCtnJ98OR/1bLnmP+6etBK/30g2b9xQxfncbbFKcDLOJbNZwfyfNVa6dPwjMj6Qd8HpLcrRtRD0nAqE/OXxGQGV9mudVCde3B3ofYg+9H9dIVCuETWeZTAw642Km6b/HD/8MtNztEuPqyjZFxvQP1RWQsY2sL4cNP6DHw4+VdPnct9wJOCOf2O2Nsti+0et4HttFwlt/Tm+ajaQnnNEHVPHRjhfErLTrZ8O0/kHaHvug+5v9UYGL+E2m7A7hYHU3MjA3tWUzcTSDeKO46A0lgmWTrlVhK2m/bwa900lBh/bHWfINP0PTJCeVfYxeWHT59ttZKMMbQ0Sgsj/9+vPsV0NBSkg5zvWrjYTeXlnzLvYbCxKzkb7QXzxsvCo9NvGyrZzCGUlRBZO772HaRkfqDWQB1+sJLZOtl9M7tIpXP6XA8lfMo46mltardhEeWKth8WwNb3BO+zXqfUZdBvGhSiCtJMMvDCBQ36mMEUlRjs0QEajdJtjPT
*/