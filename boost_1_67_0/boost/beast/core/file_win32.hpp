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
# ifdef BOOST_MSVC
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