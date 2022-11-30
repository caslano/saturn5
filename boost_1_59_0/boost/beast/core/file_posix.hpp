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
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
*/