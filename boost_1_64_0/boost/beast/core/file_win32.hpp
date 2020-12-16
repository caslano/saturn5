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
k1kHGB9SVWJ8pL4rxnRhm+rwrvaVhEnGquG7WC+88XRTbdgUuc+TaMM2OrXn6t7XGQ+xPee97dpzyt/nEqaP3p4zHn5zbKDeHBB/GVp77ht2i0N7PkKeZUuj2/Ni8b/eLi+kDpQeQR1YYVMHVlHefb9rBdaB9TZ1YLNNHdjSiPa8IN1X/p9M98p/cG8qOz3RvrJ2vPOl3Xe3OHva6ctnrC3r+Gz1wuDa8casHR/nnQPgfEkEv3efwopyA88YuRk8lWfgjObZNNU84+ZCnnFzEc+4uQRcT32/WjVekzGzxN8Cfz/I+H+Gv06gaW3AAEaBU8CmYDXYDDwHTASteI8DLwNbgX8EW4N3gG3Bp8F24MvyjuO5fy/wOzAXzMG9B4O9wCHgCDAfHAOeDFaAfcCzwb7g+WA049nifR8FS/gczfH3Jj5HLzi3B0+g3mg/6osOAm8Dh/Bb5YngBppreRbXkzyLazu/Ub4DngR+yG+Ve/it8hA4HAwzUT5ga3AwmAqexm+SBeAIMBc8FRzFcliv3luQN0x/PP6+iel/jGv4nwAHgU9Sn/YpcDz1bKdRv3Ymz6K6A3wf3AjuAP8M7uSeYbvAl8FPwdfA3fz2+iHPMPoIjDQ97k3Bv4OxIKo/85v9hUN+z+CZVTN5NtUscBJYxbOX5vLspXngXTTX8qyrp8D51NNdwHxfCH7As66+4hlXe8Fzmd/nMb/ngB3BC8FhYA3zu5z5vRis0/ZAWDoWZ7qAa8aG/1/vhYBvyL+Z/RC2oqzewWWcGW6k4Bp6ZvCbdvAX/AV/wV/wF/wFf7+N339E/79y+tSjpf//tqb/f5O7fi4viWcCfBmLP1L0uWq5ua7/HzD/xbk8huutvun1FnOGaTcXPUL576m+RfYUcya+f86S+b5SeFkndn8O1Nnn3FS2uOeYnLdjnNniPyzWd75xlHLvKPccDXNHMbcwlxulal7tXrGDTrf4MY2xMnZvJnNkst5Bm5ssKa6fS87yPL8+l4f7BeoNVEtYORxdfcdNE3955gTjj9o8uG/4ZXbfcflcM8VfHWbtBqvwuX7hV/jo+Vfw7AH4Ez9dzY6G+7BnvFN/IGAertRmvq4qUOdc8g/l4jP/V6PCSn6qefFqsUM+0d+KgHm9PnGPpPjOW5+Q6jUfG93xCpkHWzf4D39JfMA955u6maMq5k8/7belO17rlQvW/XxDmy/i3oVJYBJ1yJN5lnkK5ytSecZ0GnXHu4CbqTu+lWeF/5XmHWBX8Fv6+5FniJvc4zwUzKEueE+wG9iLOuC9ecbyCeBYsC84DhzOM9U5pvfXuT6svvWR6FqXBselwV/wF/wFf8Ff8Bf8BX/B3398/F981Mb/r2k6/Ns5/rf2vkknr8NL+5oon/G/3LywqF7X+trAtf8M01/p1Lwj5jlmuenW5gsQCcOMUGH6qPH/W2KuRpgw2/F+gQpTYCRSx3KPmCea7Y0arEqfpekPY9xYKOPEeYY2zn5Z/F9g7jBuom4X9BNj5Bw9+FH7yhXNqy6UG8dzbP+GhFtoVsO/lbZBGaJTM7sqx9DWpmv2PQx9bT3jLVN65jskvtnmR8bF1MvxpqOdkaT8F5WXF/o9B/Wkdkv4MrPYDJF0n5Ih6a6snDW/SvxRPyoh2vLX10zG13zvOYEZcp9U3OnUuAfhtyXkYBtuGO0qCGtu7UOXiS3owtxMt8xVKL3ub6MkjfrefRXeOZ148BtxbyN7z3l15V5HJNyHrkE9oTw/Xblr1fp3f105yBHtVgTOMUhZDJKwUj5il63b9eD+cNG+cwfhMcrssy5hTYghv5NwJZA3Ia7aGJt6UoxqXIEysKsrLPudEq4j6w7j0fZVDGs=
*/