//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//
// This is a derivative work based on Zlib, copyright below:
/*
    Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Jean-loup Gailly        Mark Adler
    jloup@gzip.org          madler@alumni.caltech.edu

    The data format used by the zlib library is described by RFCs (Request for
    Comments) 1950 to 1952 in the files http://tools.ietf.org/html/rfc1950
    (zlib format), rfc1951 (deflate format) and rfc1952 (gzip format).
*/

#ifndef BOOST_BEAST_ZLIB_DETAIL_INFLATE_STREAM_HPP
#define BOOST_BEAST_ZLIB_DETAIL_INFLATE_STREAM_HPP

#include <boost/beast/zlib/error.hpp>
#include <boost/beast/zlib/zlib.hpp>
#include <boost/beast/zlib/detail/bitstream.hpp>
#include <boost/beast/zlib/detail/ranges.hpp>
#include <boost/beast/zlib/detail/window.hpp>
#if 0
#include <boost/beast/core/detail/type_traits.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#endif

namespace boost {
namespace beast {
namespace zlib {
namespace detail {

class inflate_stream
{
protected:
    inflate_stream()
    {
        w_.reset(15);
    }

    BOOST_BEAST_DECL
    void
    doClear();

    BOOST_BEAST_DECL
    void
    doReset(int windowBits);

    BOOST_BEAST_DECL
    void
    doWrite(z_params& zs, Flush flush, error_code& ec);

    void
    doReset()
    {
        doReset(w_.bits());
    }

private:
    enum Mode
    {
        HEAD,       // i: waiting for magic header
        FLAGS,      // i: waiting for method and flags (gzip)
        TIME,       // i: waiting for modification time (gzip)
        OS,         // i: waiting for extra flags and operating system (gzip)
        EXLEN,      // i: waiting for extra length (gzip)
        EXTRA,      // i: waiting for extra bytes (gzip)
        NAME,       // i: waiting for end of file name (gzip)
        COMMENT,    // i: waiting for end of comment (gzip)
        HCRC,       // i: waiting for header crc (gzip)
        TYPE,       // i: waiting for type bits, including last-flag bit
        TYPEDO,     // i: same, but skip check to exit inflate on new block
        STORED,     // i: waiting for stored size (length and complement)
        COPY_,      // i/o: same as COPY below, but only first time in
        COPY,       // i/o: waiting for input or output to copy stored block
        TABLE,      // i: waiting for dynamic block table lengths
        LENLENS,    // i: waiting for code length code lengths
        CODELENS,   // i: waiting for length/lit and distance code lengths
            LEN_,   // i: same as LEN below, but only first time in
            LEN,    // i: waiting for length/lit/eob code
            LENEXT, // i: waiting for length extra bits
            DIST,   // i: waiting for distance code
            DISTEXT,// i: waiting for distance extra bits
            MATCH,  // o: waiting for output space to copy string
            LIT,    // o: waiting for output space to write literal
        CHECK,      // i: waiting for 32-bit check value
        LENGTH,     // i: waiting for 32-bit length (gzip)
        DONE,       // finished check, done -- remain here until reset
        BAD,        // got a data error -- remain here until reset
        SYNC        // looking for synchronization bytes to restart inflate()
    };

    /*  Structure for decoding tables.  Each entry provides either the
        information needed to do the operation requested by the code that
        indexed that table entry, or it provides a pointer to another
        table that indexes more bits of the code.  op indicates whether
        the entry is a pointer to another table, a literal, a length or
        distance, an end-of-block, or an invalid code.  For a table
        pointer, the low four bits of op is the number of index bits of
        that table.  For a length or distance, the low four bits of op
        is the number of extra bits to get after the code.  bits is
        the number of bits in this code or part of the code to drop off
        of the bit buffer.  val is the actual byte to output in the case
        of a literal, the base length or distance, or the offset from
        the current table to the next table.  Each entry is four bytes.

        op values as set by inflate_table():

        00000000 - literal
        0000tttt - table link, tttt != 0 is the number of table index bits
        0001eeee - length or distance, eeee is the number of extra bits
        01100000 - end of block
        01000000 - invalid code
    */
    struct code
    {
        std::uint8_t  op;   // operation, extra bits, table bits
        std::uint8_t  bits; // bits in this part of the code
        std::uint16_t val;  // offset in table or code value
    };

    /*  Maximum size of the dynamic table.  The maximum number of code
        structures is 1444, which is the sum of 852 for literal/length codes
        and 592 for distance codes.  These values were found by exhaustive
        searches using the program examples/enough.c found in the zlib
        distribtution.  The arguments to that program are the number of
        symbols, the initial root table size, and the maximum bit length
        of a code.  "enough 286 9 15" for literal/length codes returns
        returns 852, and "enough 30 6 15" for distance codes returns 592.
        The initial root table size (9 or 6) is found in the fifth argument
        of the inflate_table() calls in inflate.c and infback.c.  If the
        root table size is changed, then these maximum sizes would be need
        to be recalculated and updated.
    */
    static std::uint16_t constexpr kEnoughLens = 852;
    static std::uint16_t constexpr kEnoughDists = 592;
    static std::uint16_t constexpr kEnough = kEnoughLens + kEnoughDists;

    struct codes
    {
        code const* lencode;
        code const* distcode;
        unsigned lenbits; // VFALCO use std::uint8_t
        unsigned distbits;
    };

    // Type of code to build for inflate_table()
    enum class build
    {
        codes,
        lens,
        dists
    };

    BOOST_BEAST_DECL
    static
    void
    inflate_table(
        build type,
        std::uint16_t* lens,
        std::size_t codes,
        code** table,
        unsigned *bits,
        std::uint16_t* work,
        error_code& ec);

    BOOST_BEAST_DECL
    static
    codes const&
    get_fixed_tables();

    BOOST_BEAST_DECL
    void
    fixedTables();

    BOOST_BEAST_DECL
    void
    inflate_fast(ranges& r, error_code& ec);

    bitstream bi_;

    Mode mode_ = HEAD;              // current inflate mode
    int last_ = 0;                  // true if processing last block
    unsigned dmax_ = 32768U;        // zlib header max distance (INFLATE_STRICT)

    // sliding window
    window w_;

    // for string and stored block copying
    unsigned length_;               // literal or length of data to copy
    unsigned offset_;               // distance back to copy string from

    // for table and code decoding
    unsigned extra_;                // extra bits needed

    // dynamic table building
    unsigned ncode_;                // number of code length code lengths
    unsigned nlen_;                 // number of length code lengths
    unsigned ndist_;                // number of distance code lengths
    unsigned have_;                 // number of code lengths in lens[]
    unsigned short lens_[320];      // temporary storage for code lengths
    unsigned short work_[288];      // work area for code table building
    code codes_[kEnough];           // space for code tables
    code *next_ = codes_;           // next available space in codes[]
    int back_ = -1;                 // bits back of last unprocessed length/lit
    unsigned was_;                  // initial length of match

    // fixed and dynamic code tables
    code const* lencode_ = codes_   ; // starting table for length/literal codes
    code const* distcode_ = codes_; // starting table for distance codes
    unsigned lenbits_;              // index bits for lencode
    unsigned distbits_;             // index bits for distcode
};

} // detail
} // zlib
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/zlib/detail/inflate_stream.ipp>
#endif

#endif

/* inflate_stream.hpp
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
*/