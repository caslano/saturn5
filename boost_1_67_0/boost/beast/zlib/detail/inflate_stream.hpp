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