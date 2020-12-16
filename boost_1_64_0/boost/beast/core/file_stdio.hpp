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
HO+573l292J8TSRN4fq9VDpmi1smzaghYo6Ucd0Uw+6Hh+U4vEB0V0wZ460wrPcuNS8mdqvUfuaoR7Rbo+xQV2i3HkR9gB3qA+02q732IPO026L0ZSjLnI9DecJO8kPG/ynKTitjzhW0FnvmHcf5r3Xhu2cWx+kZvub3/MxDMn3NG+rNjTpX2H7s5jzmukfGbrUjkmeGpkyMLXw0tenbj972lZO+zrHXdzlSfSAZa3nbM7bf+aA+1ornflIpYC73icvjvnAncj+4M7kP3FQwnfuDZXB/rWzul9YTXEs99fVgf/A57nv3CjgQfJ37373Nfe7e51jvY4714pGmcWBLcDyYps4P5r5RPCc4l2OxPOq7/w6cwv21ijiGKwarwWng2eBs8DyT5/uCVeA14CXg0+Cl4N859vsAvBz8GrwC/JZjwe9531CXx18saJlbgFeDWeD14FDwJnAYeDP3R8sfG670bLYODgk4Rzaid+hhz5J9FuHq3gxp9JmyU4JjgeAv+Av+gr/gL/j7r/5CcFUc6/H/wrlFVRiDHw09gCTsu7egPSKRs46mlUwvml9eXSjjCXGb1AHv2j5uRZajzB28i3DefczzuHDgRp6lcwmuvbFYo52qzx1YEwfzK6zkw9l79h7cZ5WcXT9vwDDDDYd5ArpnqnH952KebTvul30N0+Befz4gw+fp8av9zkf53b+9Ie6yIX79PAD9cGxfw2dpInFNLa8snqXWg38i/lqosNl+YZcxbHv9fBPOP8RIuk/16BjI3v0zKlk23nG6OgvrPUSQlQRd8njP2og8yqPT2DJXG1tOwd8oB5ilHMSu1GZsWWUzjlykjTe9/mrU2NKbb3HynE3En+SP2hsezwU773PJ+E7NR0Xztdb6RtOJtGRqRZq9TBVWFU1rQK4YbpjSx3hDzP3MNDNMl4XiBZo+y2viZ6D5V4N6HSqeE+nHRN575p2S8b8ug/p5kn+VMAVmX9NNOfTGk+Mvhzwfh+546mqjiSmyiXt9IPdqHSiblPU/S5gx5kDTpckr46LMrbGR13juu/Cc+Ms3s8wITWZ9w6+X8F6ZZHtAeQyQZdaDsZLuJupcuEIxb0Se1WjndFSI/9Ph/wW5X4iRqNxQuNPQdBWqOTrZT+Kp9pw3EnN9WYQarVXYCAlbMo1BVdiR4neBXViZc0pkpUkT+wQjSexkQM3032OUwHap3GtCXIhWD/W6mH8EdbHGpi4uU3WMssn5IP+6uMqmLq6xqYvr/epivE9dRHlyP1bLnC77sZ5Tgm5E5mJ+knKBDkRrQ8wJkg8Sn5iz2it3H10snKkivxLTk55TWZdrOvjXZasmO9Zh+u+jyvARMWeaDn0F/XdT9fAeMSfjFMaNtMMMY0eZl8RzbrDpQ4bIfNefJVxn05uOuyRMCs8L4n3wVIuN55U+1IviJ5T13Wtu6VTfVRyXGk+xL1Jh/Ou72iflLglzvKnVdcbjWNfVfPzD4q+rCpvNsFo91+pmteqXvhQ/r4vbhlhR3xP/uLd25tto1T93kGdYZ5ffUj/GHb36scA4BvUDawnl2TaI3RCRc7Ojbz04g2aE8znfZXc0p+Lh2BGMpdzndQqQe/ZgjrLPMP1U+Z0r5s9s+64RXv+482zjNsdvIlXi5wBl1BsmO0BGEymj3jjvQJ163+geKJeUkdni7we9D0LYw8ulJdOLxN/nev+DsI3vf/zPiosDm3WW7wbSJxS2ce5Plst93vPzx75De6e8SPztVmtSC2J/u229Jb/vd/KV5/DOvu16K5j1dn0gdeG2NQts11tm4R1X/Nd4hi36O9rcooUNvKMx3BAl4650aWfNevlFkrV2+Wfx38n0vmd8Jv4=
*/