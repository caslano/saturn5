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
y+g18fiCpaLsMoGv+hiG08THxywXZV5V6tuR7n7/vrXrb2X7bu7Hy6xUymzx6Dyra5VHx1eLut4MuTQlrK6g+XbIW59FBwRsbQXtkvFSbdc6Udd6hceMlrF9x/pAbdtGUW6TUq4na5t4T7lFef6q8nyb8nyZ8vxd5flUj+6wvKYp6TJ6P+T6KVs/PPAPBH8fOnSNuAb93HMgdyvPZyjP9yp8fKTgTFdw9ik4+z06x2xNvlN2+bHoU8HPZwIf+bA=
*/