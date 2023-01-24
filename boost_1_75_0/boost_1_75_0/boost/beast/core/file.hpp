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
6hbq2PopYNkxdPgHSL7AeKmsWjAxe2wuDt6yH4LXka+Ok5+vLx6/OL/6HSA+oEOgA6AF4JO/C2ga8HfQ/YIBi0AcwHlAa43Qg2gGpP0aAZFATcAqQNJ/f9C+AuWEd0DpzwWlB5vDlUBKB5IDugLSAE2AZMQx4J37AlLiKrHD6efnA12DdMDcY+0HD8gGIg84BYoDLuDvtwgQCAALoAWCF4DudwpgA/IGsgKmBzoK/Dye44A1QO83CXAE0gmYBwIF9gJeA2kOunks1DGcP1c/u8Vfs+wbMgyKe2esgPSAjdAk4XY8W8U3nkPHBlEA824dyyMcUoqVKJVJrlpGFkqUyKSTpyEkRxYijsuAm7UIkn0dUIsK0GJNI/kFFTELRA59SA5bvO7HhzyfgVSbUiI+qaz6SzWQkT+G0Gjo8NC3CFVzgTWWFc/DR0QR2TjcrJxkh3M/5I4xMZ5RcmwsYayp9BwuNoloPKxnfCzxhFIVXA4hRKIokagZrU6s0sREWiVTiRBl38RgNoGmoE0GJtXmXGNEgS0qXChVqtKopLLkV6xOYqRkDK6kHU+mgwPxX0UUAaiPJ1IqVkNVSVXOqTAtS4ERShYl1KGk2YGh+3boPVgx572OLPvIsxERGEVStE+TIsUFYqwk2uvzUMYBvRu4lULFYtOUT0jM/bhCoWKqhEoTaFmZEepE44GaLZMv8Nc1sBuqUoI+chrIuwoB
*/