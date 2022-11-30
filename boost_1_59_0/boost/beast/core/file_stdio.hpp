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
    std::FILE* f_ = nullptr;

public:
    /** The type of the underlying file handle.

        This is platform-specific.
    */
    using native_handle_type = std::FILE*;

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
    std::FILE*
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
    native_handle(std::FILE* f);

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