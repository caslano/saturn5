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
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
*/