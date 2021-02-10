//
// Copyright (c) 2015-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_FILE_STDIO_HPP
#define BOOST_BEAST_CORE_FILE_STDIO_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/file_base.hpp>
#include <cstdio>
#include <cstdint>

namespace boost {
namespace beast {

/** An implementation of File which uses cstdio.

    This class implements a file using the interfaces present
    in the C++ Standard Library, in `<stdio>`.
*/
class file_stdio
{
    FILE* f_ = nullptr;

public:
    /** The type of the underlying file handle.

        This is platform-specific.
    */
    using native_handle_type = FILE*;

    /** Destructor

        If the file is open it is first closed.
    */
    BOOST_BEAST_DECL
    ~file_stdio();

    /** Constructor

        There is no open file initially.
    */
    file_stdio() = default;

    /** Constructor

        The moved-from object behaves as if default constructed.
    */
    BOOST_BEAST_DECL
    file_stdio(file_stdio&& other);

    /** Assignment

        The moved-from object behaves as if default constructed.
    */
    BOOST_BEAST_DECL
    file_stdio& operator=(file_stdio&& other);

    /// Returns the native handle associated with the file.
    FILE*
    native_handle() const
    {
        return f_;
    }

    /** Set the native handle associated with the file.

        If the file is open it is first closed.

        @param f The native file handle to assign.
    */
    BOOST_BEAST_DECL
    void
    native_handle(FILE* f);

    /// Returns `true` if the file is open
    bool
    is_open() const
    {
        return f_ != nullptr;
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
#include <boost/beast/core/impl/file_stdio.ipp>
#endif

#endif

/* file_stdio.hpp
3Sy/15+gcNtZK/u1h32Rn39Lxq2C/d5jHXj5Pe8zjr4Yn9Xno86rP3zN30DyrCX80rFnv7G9eeIJQ43KngFTVSAy923EeKx8L+bzHn6BDIDdow8d1F6sG8Z9e0CoPsdlYsB1LPb3mWfR1+XVRnGPo0/w+YUWnQ/Dn4yXk4RPEcPshT3ML/o2wyh/9/DDHDtD2Rcnoju4LLYdeZksvtOhAplJODk/KaJESFAo6MOybK27oALi8hdHWyqi8RhNxy/eNmnKci/Pjj+pfB6U5/nGG+etTQOvgjK3tIov2Nx8qXPKEktbHiPWpaE/LtpXWZMa9k7pgKOhsrbK3BkV7X0xcnuX17c8iS6H3belU3b67gKKd7v/6I1ubbs6Z0xv1FlQPe9iuYwerXWsizgK4/tGWT/99ZZVsPPHToeFHxxZuZa/nlip0kd5lc7PC5K5jA2vgTu8+DgU33HRH/R/ucI+0zEnqZBrKbaJIiY7BNmQpyQIWJg9Kqin9e2AK+p96t7YSfyJlv5yi7/7OrW7ltwk5ZMJCCs+/HAsODjCirQnzLuPHyocyo1jo6NTgt8MeWHc4AOEdOI7JkhbuFnqoC7F+aRoaWly5W7Jq8ceACAM3elc0XZ7BQfd703a/K3LCWltXi3y1y+Njj1rsjm2
*/