//
// Copyright (c) 2015-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_FILE_HPP
#define BOOST_BEAST_CORE_FILE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/file_base.hpp>
#include <boost/beast/core/file_posix.hpp>
#include <boost/beast/core/file_stdio.hpp>
#include <boost/beast/core/file_win32.hpp>

namespace boost {
namespace beast {

/** An implementation of File.

    This alias is set to the best available implementation
    of <em>File</em> given the platform and build settings.
*/
#if BOOST_BEAST_DOXYGEN
struct file : file_stdio
{
};
#else
#if BOOST_BEAST_USE_WIN32_FILE
using file = file_win32;
#elif BOOST_BEAST_USE_POSIX_FILE
using file = file_posix;
#else
using file = file_stdio;
#endif
#endif

} // beast
} // boost

#endif

/* file.hpp
sZ9T1XPxE9R0O5HlvxzUS0dZBIAVeqlIQejAdjKFNVvaLSHZcu/HlD64awEHVKOG4QtSWIlyb3EdVCru/WFk5KmlWgmXobA48tVcv5EOej8F0rZR1aIiotAygOWFx5E9RNnhvVdsQafp/5gafCq3FUmw6ye7FtQX40wDaSJJK47RT5Tn63rg/AXikMLW0diqPaYeulymVw7bYPTuPg+M4hRF1LxH9nIx86as0oYX8kC9LjUctCnkH70gfWUqb/bOSn94+poUpo+GxJQvgKAsitVXVB3gEHSSXoCZDgOHsHVTOSp6uKcbxa6YPTLWkqGcQeU6hC8fA9aHsPOyhzqKbS27wzSa6qp9ObmJkXLHWeJKuCh/smD/P7QQ3FUyzFpeTI0qKEyiQETBfY8Uunsf7ncGJ8qOJl+pL1iDbIPBnz12MSHfWn9sM03yLXH/f5P+eW+VNOZhM+KceyWpTju10vzbVvSV1TicYRf+htP0og5cNh/NRxwxlPSbhVegcRYpTn332a9+6A5tnMqXcwFn+Hlqici3gRh7GrgLzIE6mJHyIhKXxbZ7J1ShZw==
*/