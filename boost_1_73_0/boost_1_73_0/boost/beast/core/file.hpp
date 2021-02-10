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
NOxen/X62OzDUAFbB3hVaTPYKtx2NxqQDocXFYfX4tIGhwDPFJP9XMdm0yIGIAejmEIMTvTKoMPFoN+1U4Q24IngiXTtamMe5z5X9in11W3cQ6B9ykoxFfCTTUw3GgB7/csBSlXvw9ltF/qRsZpPputeXnZR3D50XYyA2jiouTvIaVUcdyenorEXNG3cGUqHVsIb6RjrpLiuKqMtq0PLmKBkXdKukJ1KRn0wKqtUrMmPUDIX88Z2qmaRQKWwR/Ogdyh2W00JE+eVyde7cXRn1QOOtYhnym2NDpqo9S5nvb8QK7E3t0/F3k+ajZVTapXWWjEESynNWk2x0oGTp5ZODZ8zo2gBiaxhZe8LqD/snl00xV+YyL0ZXF0B8sVrak6+s/3Wpn8c9m671fm0ayECEp361RQy3akWXnI0tB0HjlFK9xGbeVkp/3Vr89c7+cOOqd/UXfkaIk1sC7YuSLwpNWKb0R556BgsLqK9igGt97QJN90VnLfZIj3WCf4wXdGuYEwWad7uyW9zPmZaC8Bndtq/UQz+PAhFq/mzIHxqaHBg6Vrr3vauu+yIjmPSe/fPU2LImu1Xx5BxHAGPWMzNSbTeCxknLDbbWKAdyWjkM1vjrZsQE33soF0esXE8LhWfMZCW9mtNW2oIh9bj
*/