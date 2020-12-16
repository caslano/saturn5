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
WVRakFu6MNy/2KkznSfW6+yNlpY8Q/XO0wGwC/7O9vmJUTXxywrxS9SHZtxJZVOtdtrPmy76bnYP/p2DugPVyra1/1nzHJSnRH6XlUEdtBV1CmnQ2DWW8J7yb6K0D1jPcYPouvasPmZduymbKyQ+NBykWV+RYRzIl2abdf/TaK3Thml+O9THGz9S8nN174k/zTScb4idHhpvjhvNTJ4b+SXroKj/UzKDvxUr0y15srW84H/Zv5WZ6fG/v6iE7d9Se9mhe7XU3ITpyaMoR2v89WpA+2KBhnOtL5yjW9csWz27IucLZ4W3PxUWTrUX67o3QSyIOVU95nWWv+r6LCBsKeZcInHXHRbGymq2SS7D/mZ/WAL6DmsC2iXY8/QdevrarJibvoMxN21WNTd9B8y9bVbM69d32Jx57G3WNQFt1p7eNqvqTZsVfe1t1uc1T3X35amZ7Sx5xmo6jNB0eL+WdCizQtNB7Y0lLloEpYMxb2t1DEoHY96fdAxIB2Peh3QKTwfk/kvToX/f4HRof3Jw2c7pG5gO2ncILdvY85ftkuICqGUb8+NVtsVdT1ie08r9C1Rb1J9RqwhLXkBYzLBdLWO3l4u9n2nYHHe6W85+Q+SNK1pHq0xXc97RZaL/pc75mLa2GbddL+Yviz7H2O+k51x5xm/M3NJakXlR9NOMnfZWb/JaouXZcy3t7yPoHe6GH7eNjvfW/X0Pyo/NPXdEufdbmnxp2urNPXnThMPTXt/doWb+W0Ga7ejnS7PQ9npoXlQ3YgPvhsNLmB97Xqy+F8vbtvmkoyXPvaiWqBtR3brRTg0IlwyLhodD7XQwcyPPiv5qaxb/rkElmjsNyzQfqh1C1lzzzNOi/5Z1Jn5cjfLdR2bai78QuY3WDOZ+V6I0X6p7rbVfp/NLR9Gm8tdpWeZewjLNZ+67w7xx+RQG0SddvxXRl5cQl5v7O3E5aczZ0lsqXOnuj59JxLMvu3CVmcd17DRx1U/FBStN/eSYp5t6e2az+rex+D38z+/puyxTV/EbvjA917lmmDZE84cnTBU1wtSzac0w7ak9TGqeLuYx8fLdK6dZVJ22vjDPP4ow45/awmzSlt/lHb/rq7OXdKlZ/s/tSvvdxMOUMTPHTx0tybuwuHBJQW7lqrLCsP4S9uos09V9N29fxdN3e6erJc8yTZ8y1L3Ivtbfe09ZfkFBWD9SZdPMuTYfiH6u58xELa8qm4uZfluctokxmyNntKi5WXsyzZgvrK1dgsyxt0uCxjT1fA3TLsFv7nYJ+trbJd0HVLVLYrp6y8eD3XTvKSpNuQW31g7wxL9rHVXA3KjWad8VO/01XRw3Wpk52KdEb2uc1Ll2yeSfTP9daoTnrgHBa5U+1MJUpPlpAeqxaH7yh2dpWVh+Utm5njyi+UfNpnnyh+YfNZtMPogE9i2nGZnZxy1fuPNBji8fzA7IB60HVsXbpb41G291t+RZp/G2GrUVt8oGeuLNs2bj6uo1G3qWksrjSk9yU66uHTzbrMtATuNR5aSfMAGl3zvi4+ji5OqAtRRn+9ZSvKthvsyXV9r3sORZpGGej/oRdtsP8oa5YP6SsLyCbGhdo2bTguoazOrOK+0HHd+8ElKHhOaVufL7rEvyxdvonjXXoAxHZoc/3vhtd9g1zpDzrkH5oejNGpTAuJ5k7PW03GvtUvVsqFfFrA1unKBp4V3D8swg/xoW03ZnHUjd7StZw+KLsyxvPHvKU0ovS54RUq9CrVfbD/bEkdao4XXqEJHvYuIO+5469Vz01XVqnetJaq1TRw721qlnOHM1vb3f6BLUzdgt84ZFmg4Ty8pLzytcUFm8vNB/mag/XbXOUHdwvQdjCvM=
*/