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

#ifndef BOOST_BEAST_ZLIB_ZLIB_HPP
#define BOOST_BEAST_ZLIB_ZLIB_HPP

#include <boost/beast/core/detail/config.hpp>
#include <cstdint>
#include <cstdlib>

namespace boost {
namespace beast {
namespace zlib {

#if !defined(__MACTYPES__)
using Byte = unsigned char; // 8 bits
#endif
using uInt = unsigned int;  // 16 bits or more

/* Possible values of the data_type field (though see inflate()) */
enum kind
{
    binary    = 0,
    text      = 1,
    unknown   = 2
};

/** Deflate codec parameters.

    Objects of this type are filled in by callers and provided to the
    deflate codec to define the input and output areas for the next
    compress or decompress operation.

    The application must update next_in and avail_in when avail_in has dropped
    to zero.  It must update next_out and avail_out when avail_out has dropped
    to zero.  The application must initialize zalloc, zfree and opaque before
    calling the init function.  All other fields are set by the compression
    library and must not be updated by the application.

    The fields total_in and total_out can be used for statistics or progress
    reports.  After compression, total_in holds the total size of the
    uncompressed data and may be saved for use in the decompressor (particularly
    if the decompressor wants to decompress everything in a single step).
*/
struct z_params
{
    /** A pointer to the next input byte.

        If there is no more input, this may be set to `nullptr`.
    */
    void const* next_in;

    /** The number of bytes of input available at `next_in`.

        If there is no more input, this should be set to zero.
    */
    std::size_t avail_in;

    /** The total number of input bytes read so far.
    */
    std::size_t total_in = 0;

    /** A pointer to the next output byte.
    */
    void* next_out;

    /** The remaining bytes of space at `next_out`.
    */
    std::size_t avail_out;

    /** The total number of bytes output so far.
    */
    std::size_t total_out = 0;

    int data_type = unknown;  // best guess about the data type: binary or text
};

/** Flush option.
*/
enum class Flush
{
    // order matters

    none,
    block,
    partial,
    sync,
    full,
    finish,
    trees
};

/* compression levels */
enum compression
{
    none        =  0,
    best_speed            =  1,
    best_size      =  9,
    default_size   = -1
};

/** Compression strategy.

    These are used when compressing streams.
*/
enum class Strategy
{
    /** Default strategy.

        This is suitable for general purpose compression, and works
        well in the majority of cases.
    */
    normal,

    /** Filtered strategy.

        This strategy should be used when the data be compressed
        is produced by a filter or predictor.
    */
    filtered,

    /** Huffman-only strategy.

        This strategy only performs Huffman encoding, without doing
        any string matching.
    */
    huffman,

    /** Run Length Encoding strategy.

        This strategy limits match distances to one, making it
        equivalent to run length encoding. This can give better
        performance for things like PNG image data.
    */
    rle,

    /** Fixed table strategy.

        This strategy prevents the use of dynamic Huffman codes,
        allowing for a simpler decoder for special applications.
    */
    fixed
};

} // zlib
} // beast
} // boost

#endif


/* zlib.hpp
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
*/