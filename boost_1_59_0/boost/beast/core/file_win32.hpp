//
// Copyright (c) 2015-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_FILE_WIN32_HPP
#define BOOST_BEAST_CORE_FILE_WIN32_HPP

#include <boost/beast/core/detail/config.hpp>

#if ! defined(BOOST_BEAST_USE_WIN32_FILE)
# ifdef _WIN32
#  define BOOST_BEAST_USE_WIN32_FILE 1
# else
#  define BOOST_BEAST_USE_WIN32_FILE 0
# endif
#endif

#if BOOST_BEAST_USE_WIN32_FILE

#include <boost/beast/core/error.hpp>
#include <boost/beast/core/file_base.hpp>
#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/handles.hpp>
#include <cstdio>
#include <cstdint>

namespace boost {
namespace beast {

/** An implementation of File for Win32.

    This class implements a <em>File</em> using Win32 native interfaces.
*/
class file_win32
{
    boost::winapi::HANDLE_ h_ =
        boost::winapi::INVALID_HANDLE_VALUE_;

public:
    /** The type of the underlying file handle.

        This is platform-specific.
    */
#if BOOST_BEAST_DOXYGEN
    using native_handle_type = HANDLE;
#else
    using native_handle_type = boost::winapi::HANDLE_;
#endif

    /** Destructor

        If the file is open it is first closed.
    */
    BOOST_BEAST_DECL
    ~file_win32();

    /** Constructor

        There is no open file initially.
    */
    file_win32() = default;

    /** Constructor

        The moved-from object behaves as if default constructed.
    */
    BOOST_BEAST_DECL
    file_win32(file_win32&& other);

    /** Assignment

        The moved-from object behaves as if default constructed.
    */
    BOOST_BEAST_DECL
    file_win32& operator=(file_win32&& other);

    /// Returns the native handle associated with the file.
    native_handle_type
    native_handle()
    {
        return h_;
    }

    /** Set the native handle associated with the file.

        If the file is open it is first closed.

        @param h The native file handle to assign.
    */
    BOOST_BEAST_DECL
    void
    native_handle(native_handle_type h);

    /// Returns `true` if the file is open
    bool
    is_open() const
    {
        return h_ != boost::winapi::INVALID_HANDLE_VALUE_;
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
    pos(error_code& ec);

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
    read(void* buffer, std::size_t n, error_code& ec);

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
#include <boost/beast/core/impl/file_win32.ipp>
#endif

#endif

#endif

/* file_win32.hpp
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
*/