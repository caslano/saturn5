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