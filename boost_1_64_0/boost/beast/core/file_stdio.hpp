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
URx0GzNeoIK8O+LdGn6K+BHbUWKR5/1I7KItgUu6naeGM1p3LLcn3vmE5yNdoBKc/0hmD6PiQ2fmDMU4q/EyoCBZyix9QMk9yjkO5vK+UdNu9MzcCulWGhnmo0I8sIIr6ByuVbhtJwsqEpHqbyKGxqb1V+ps/1NBxdoqumDKBdPYF6//F9xI0zremRepCqeWwqu0CyNAoSZi2GY9Idm9tMssYkdURwmR3+K5gfrVPVl+6yOWaIN94bT+xq4V5CQbqUsZWL+sWKqYLbbYAYA7xg7jRRyQWZyxgXxdI2MTAcCJ98NBiS9axPn2fInYOGLdilANxBs7bLacnHaj/BGrrRufyx6DwZd5ucgT67tdu3r/oDxDAxzxj+9Sm6ow1pf1KaEMd5WN4tJv1P/kMiELz7P9NP23KWe+j/j84eZV5HFMqJXjjcjG6jOWWznhfh/lE+gSA78ATqh5iIdmwgMyKKPV//p0Gy1c6hWKN965u2Ge29/l0xru+vaDVyOZTAMt31unXy8isvFqKcVP7RFaWcNt3aIK4Q1dntPL+fviXUlC82RCP+8/mH8Pmw==
*/