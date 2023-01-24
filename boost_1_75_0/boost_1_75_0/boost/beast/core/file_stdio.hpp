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
XYKV7RMEqxxVLIgJK7LjPfdEYF7VAylyxL2IQGPMYYO/QfDF2FDOdWUJWBYIUwfuiaBxWJEtIerIJ+oo5alWJCpuW4jgNsQBPx/0Q9ggtJqzPWVexHGIZ88aVorAcktCuUI2yToaYRFgXzLYRzmDbiS+I2iOpLJAWYUROYJYuVwBAo1CvAVOFyB9vF02PB1ZJgT2TPUNinBh6rFD44oiGacFOSmLjgglJt6esagBj6MadQosqhNyFQ6AhZJGPXfFqe8YCP/T7LVtZ1HQlakYniESqRnyljUQUf/AYiHXbzYi4+Wlv1YZN8xWAUyBqegRZ7ty6AlumNN0r446f3ncUpEfeBM36Ay/QccjTwSKHVuRQbz4JKT9k4ULK6glgguc7W0FieUaIUg6CQlRAjFnIOKV2z/FCCrfYweZUKmhnqRobMhaI4pabExQXAwMzfpb4F2pgAUFGv9BHgzHhebOZUrDY1EOVI8/GFlW+razZjxQJMVLFeUIW86iGdLPbTTnpYjLGL/Y39USar/biYQ7sT5+YCB0Bn4xw07ilIdST0MhrEWcqWefbUSXaLYNFDNcDLklO9FNyQSBFfveMV9G8PlhZEcnoltzMex1NjH3np3EnYDPUtb+LGJbNN4drSaUvhO+ksBODPfvU5uUWb12cCcwqP0tq8MK/hxvgT1oa9NoLfOkyirGthkS+eq0m/ro/e99R0/nN/MXL5Tm
*/