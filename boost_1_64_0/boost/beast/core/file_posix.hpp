//
// Copyright (c) 2015-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_FILE_POSIX_HPP
#define BOOST_BEAST_CORE_FILE_POSIX_HPP

#include <boost/beast/core/detail/config.hpp>

#if ! defined(BOOST_BEAST_NO_POSIX_FILE)
# if ! defined(__APPLE__) && ! defined(__linux__)
#  define BOOST_BEAST_NO_POSIX_FILE
# endif
#endif

#if ! defined(BOOST_BEAST_USE_POSIX_FILE)
# if ! defined(BOOST_BEAST_NO_POSIX_FILE)
#  define BOOST_BEAST_USE_POSIX_FILE 1
# else
#  define BOOST_BEAST_USE_POSIX_FILE 0
# endif
#endif

#if BOOST_BEAST_USE_POSIX_FILE

#include <boost/beast/core/error.hpp>
#include <boost/beast/core/file_base.hpp>
#include <cstdint>

namespace boost {
namespace beast {

/** An implementation of File for POSIX systems.

    This class implements a <em>File</em> using POSIX interfaces.
*/
class file_posix
{
    int fd_ = -1;

    BOOST_BEAST_DECL
    static
    int
    native_close(int& fd);

public:
    /** The type of the underlying file handle.

        This is platform-specific.
    */
    using native_handle_type = int;

    /** Destructor

        If the file is open it is first closed.
    */
    BOOST_BEAST_DECL
    ~file_posix();

    /** Constructor

        There is no open file initially.
    */
    file_posix() = default;

    /** Constructor

        The moved-from object behaves as if default constructed.
    */
    BOOST_BEAST_DECL
    file_posix(file_posix&& other);

    /** Assignment

        The moved-from object behaves as if default constructed.
    */
    BOOST_BEAST_DECL
    file_posix& operator=(file_posix&& other);

    /// Returns the native handle associated with the file.
    native_handle_type
    native_handle() const
    {
        return fd_;
    }

    /** Set the native handle associated with the file.

        If the file is open it is first closed.

        @param fd The native file handle to assign.
    */
    BOOST_BEAST_DECL
    void
    native_handle(native_handle_type fd);

    /// Returns `true` if the file is open
    bool
    is_open() const
    {
        return fd_ != -1;
    }

    /** Close the file if open

        @param ec Set to the error, if any occurred.
    */
    BOOST_BEAST_DECL
    void
    close(error_code& ec);

    /** Open a file at the given path with the specified mode

        @param path The utf-8 encoded path to the file

        @param mode The file mode to use

        @param ec Set to the error, if any occurred
    */
    BOOST_BEAST_DECL
    void
    open(char const* path, file_mode mode, error_code& ec);

    /** Return the size of the open file

        @param ec Set to the error, if any occurred

        @return The size in bytes
    */
    BOOST_BEAST_DECL
    std::uint64_t
    size(error_code& ec) const;

    /** Return the current position in the open file

        @param ec Set to the error, if any occurred

        @return The offset in bytes from the beginning of the file
    */
    BOOST_BEAST_DECL
    std::uint64_t
    pos(error_code& ec) const;

    /** Adjust the current position in the open file

        @param offset The offset in bytes from the beginning of the file

        @param ec Set to the error, if any occurred
    */
    BOOST_BEAST_DECL
    void
    seek(std::uint64_t offset, error_code& ec);

    /** Read from the open file

        @param buffer The buffer for storing the result of the read

        @param n The number of bytes to read

        @param ec Set to the error, if any occurred
    */
    BOOST_BEAST_DECL
    std::size_t
    read(void* buffer, std::size_t n, error_code& ec) const;

    /** Write to the open file

        @param buffer The buffer holding the data to write

        @param n The number of bytes to write

        @param ec Set to the error, if any occurred
    */
    BOOST_BEAST_DECL
    std::size_t
    write(void const* buffer, std::size_t n, error_code& ec);
};

} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/file_posix.ipp>
#endif

#endif

#endif

/* file_posix.hpp
/6vhOH0i9yA7A1eXLNh39dH/H3ry6MKSimme75+ds2Qvo+pF2r5yK8V/vtGrfl85xhHf6L2zOsuZRIiX63/vlPBYg5TkMd9Lc3Ksx/wMzfyOqJ5pO/UEBrnxnGQm4jayRE9Af6a5JUXTAp6J6af//mpftf5idrubueI13QIUTElxdeVcnh+jwvWRcGNh7iPmi1w/mZ3gx7KDJkF37gvE9dcRVjxc+6x/o78oi9/66Y96BBL36fBTJ+5bzRmIW+xU3BFmB2OMhOO3dtwA41Hvfjzd5CwacwbS+aqBsGIvYbmHUKF2z7KKaSWLVL5MkbCpNCNHxRxp+OkMSJyV8L8vy6MrMZRprNTS2M4Yr30zL67yhptt7bkg4e43JzPcbC1cmnGGf54oXY4Hxc/lNHvDtAzIi6Ysn63ifpF/2aj4I7zPT1mPzbbcu9NM/9SjaE7BHitpTzKSxM5TmFVi97LrTTPRuN8VKvsdLoXTTSHevYimWVoGoVHhQJNw6+/ogH0cWQZlElcX1/HGV6aT3s108dO50ToHBnUOZJ861seRrI+JsMtX+gZK5qUejszy/b5/C833pFrms2gOM9ys15v8/H+W5as/cIjmDLq36+br3qy7rzkFZr1d6AKzHv9smrtRH+EKP/e1NOfQ3cj2mHv5nYW2NMxeVyr2CHSlYg+jKxX/C3Wl9oMHzSNfF3Ss5+yOdA6uopmc+fRC/wvTvy6/+6U7Tjmt5eJnHdcjOc3hOs2lHvm6LKe54J3tLPvH37g+tVfs6ff/KWXaXVXjkpahP8227GcuKr43ufSDkPknnHTPpWP/Mdt57nit+L/7y/sm5z+x7kpz30+nJqxcs855bvdL8R/bc92A3hVhxduffOTTO+/606ZAHYjtRr0OxBSDfTL7+1K/Nb7Pwzmea+mTwRcs7+CL4PFcUz+Ya+hPAl8Bx3At/Rm0t+5To/pA6XvlPlk8u9f65XPN+8lcyz4SHMc1v9PAAvAGrjFexzXGm7jGeAs4AXyca4xf5FrnOnAmGGFCdsDO4DwwG1wGTgYvA6vA5eBi8PfgUvBKnkl1FXg3uAJ8AVwEfgueDbZ1Yd8uMAVcB3YC14NdwOHg8eAI8ATwGet+4EpwBvgH8HzwTnA5uBG8AhwDrgJPB1eDd4P3gPeD94EPgA+CD4HPgQ+Dr4GPgpFuz1lHseBfwM7gU2AO+LS2VjpW03nZbvz7Oi/LGrlObtkZ4aJ3shZ81n+e2WGOeT+udKd5ZYc55WdxbcU9WvbzzCeng3Z6JUtxOc8pcz65gbnkbYsankNe1I/zyH7r35b1C5w/3ob09tfmjp+qrJ873tqv4fVvexA2dmy4kT02OHcc/AV/v7ZfCK6Zx278b30qnzdpUfW8nB651jTAL54D2IGBzUDvXmQcL1t9VkdwGLgxw+rc9H3IPTfHLIAkyfuOuz4jYNzMcD3U+Op+MXdyNVX7Upct0PaMo/8RNJvG05mes/A1/xVVRv1+8feK/0wX9yVj+O7iPyVMzgWer+8hvkncs8T/KOW/q7aPIN/BOb7b4Em/Szvzl2FMOQ94M8z1e54jQ0Cv32w/v1voNynLGkdWLywpmiXjRDy3/LIzZF9CsSug3VdWeNgkwg7pRTjsS+4pC9j1YniP56cyOV6Q8IxA4oyBMC42bofLs0aOuI+Ce4Ryf9fsgDelXcjnYeYF6izzSDUuKVP7524Q/yHmcXjjSeRehreL3dNGOMLn4T7x6hnnFc8tqi4u5ZqBG8GPxe8TeNecalQy/flMarq4JXns+KxDxC6VdpJmPqdL0pnCPJ3PvWHnaWccz7HCcu9O7hes9o1dJ26tEC/M6hkyjFDLDv5by7oFKaM=
*/