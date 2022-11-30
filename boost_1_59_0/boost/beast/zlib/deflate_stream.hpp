//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_ZLIB_DEFLATE_STREAM_HPP
#define BOOST_BEAST_ZLIB_DEFLATE_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/zlib/error.hpp>
#include <boost/beast/zlib/zlib.hpp>
#include <boost/beast/zlib/detail/deflate_stream.hpp>
#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <memory>

namespace boost {
namespace beast {
namespace zlib {

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

/** Raw deflate compressor.

    This is a port of zlib's "deflate" functionality to C++.
*/
class deflate_stream
    : private detail::deflate_stream
{
public:
    /** Construct a default deflate stream.

        Upon construction, the stream settings will be set
        to these default values:

        @li `level = 6`

        @li `windowBits = 15`

        @li `memLevel = 8`

        @li `strategy = Strategy::normal`

        Although the stream is ready to be used immediately
        after construction, any required internal buffers are
        not dynamically allocated until needed.
    */
    deflate_stream()
    {
        reset(6, 15, DEF_MEM_LEVEL, Strategy::normal);
    }

    /** Reset the stream and compression settings.

        This function initializes the stream to the specified
        compression settings.

        Although the stream is ready to be used immediately
        after a reset, any required internal buffers are not
        dynamically allocated until needed.

        @note Any unprocessed input or pending output from
        previous calls are discarded.
    */
    void
    reset(
        int level,
        int windowBits,
        int memLevel,
        Strategy strategy)
    {
        doReset(level, windowBits, memLevel, strategy);
    }

    /** Reset the stream without deallocating memory.

        This function performs the equivalent of calling `clear`
        followed by `reset` with the same compression settings,
        without deallocating the internal buffers.

        @note Any unprocessed input or pending output from
        previous calls are discarded.
    */
    void
    reset()
    {
        doReset();
    }

    /** Clear the stream.

        This function resets the stream and frees all dynamically
        allocated internal buffers. The compression settings are
        left unchanged.

        @note Any unprocessed input or pending output from
        previous calls are discarded.
    */
    void
    clear()
    {
        doClear();
    }

    /** Returns the upper limit on the size of a compressed block.

        This function makes a conservative estimate of the maximum number
        of bytes needed to store the result of compressing a block of
        data based on the current compression level and strategy.

        @param sourceLen The size of the uncompressed data.

        @return The maximum number of resulting compressed bytes.
    */
    std::size_t
    upper_bound(std::size_t sourceLen) const
    {
        return doUpperBound(sourceLen);
    }

    /** Fine tune internal compression parameters.

        Compression parameters should only be tuned by someone who
        understands the algorithm used by zlib's deflate for searching
        for the best matching string, and even then only by the most
        fanatic optimizer trying to squeeze out the last compressed bit
        for their specific input data. Read the deflate.c source code
        (ZLib) for the meaning of the max_lazy, good_length, nice_length,
        and max_chain parameters.
    */
    void
    tune(
        int good_length,
        int max_lazy,
        int nice_length,
        int max_chain)
    {
        doTune(good_length, max_lazy, nice_length, max_chain);
    }

    /** Compress input and write output.

        This function compresses as much data as possible, and stops when
        the input buffer becomes empty or the output buffer becomes full.
        It may introduce some output latency (reading input without
        producing any output) except when forced to flush.

        In each call, one or both of these actions are performed:

        @li Compress more input starting at `zs.next_in` and update
        `zs.next_in` and `zs.avail_in` accordingly. If not all
        input can be processed (because there is not enough room in
        the output buffer), `zs.next_in` and `zs.avail_in` are updated
        and processing will resume at this point for the next call.

        @li Provide more output starting at `zs.next_out` and update
        `zs.next_out` and `zs.avail_out` accordingly. This action is
        forced if the parameter flush is not `Flush::none`. Forcing
        flush frequently degrades the compression ratio, so this parameter
        should be set only when necessary (in interactive applications).
        Some output may be provided even if flush is not set.

        Before the call, the application must ensure that at least one
        of the actions is possible, by providing more input and/or
        consuming more output, and updating `zs.avail_in` or `zs.avail_out`
        accordingly; `zs.avail_out` should never be zero before the call.
        The application can consume the compressed output when it wants,
        for example when the output buffer is full (`zs.avail_out == 0`),
        or after each call of `write`. If `write` returns no error
        with zero `zs.avail_out`, it must be called again after making
        room in the output buffer because there might be more output
        pending.

        Normally the parameter flush is set to `Flush::none`, which allows
        deflate to decide how much data to accumulate before producing
        output, in order to maximize compression.

        If the parameter flush is set to `Flush::sync`, all pending output
        is flushed to the output buffer and the output is aligned on a
        byte boundary, so that the decompressor can get all input data
        available so far. In particular `zs.avail_in` is zero after the
        call if enough output space has been provided before the call.
        Flushing may degrade compression for some compression algorithms
        and so it should be used only when necessary. This completes the
        current deflate block and follows it with an empty stored block
        that is three bits plus filler bits to the next byte, followed
        by the four bytes `{ 0x00, 0x00 0xff 0xff }`.

        If flush is set to `Flush::partial`, all pending output is flushed
        to the output buffer, but the output is not aligned to a byte
        boundary. All of the input data so far will be available to the
        decompressor, as for Z_SYNC_FLUSH. This completes the current
        deflate block and follows it with an empty fixed codes block that
        is 10 bits long. This assures that enough bytes are output in order
        for the decompressor to finish the block before the empty fixed
        code block.

        If flush is set to `Flush::block`, a deflate block is completed
        and emitted, as for `Flush::sync`, but the output is not aligned
        on a byte boundary, and up to seven bits of the current block are
        held to be written as the next byte after the next deflate block
        is completed. In this case, the decompressor may not be provided
        enough bits at this point in order to complete decompression of
        the data provided so far to the compressor. It may need to wait
        for the next block to be emitted. This is for advanced applications
        that need to control the emission of deflate blocks.

        If flush is set to `Flush::full`, all output is flushed as with
        `Flush::sync`, and the compression state is reset so that
        decompression can restart from this point if previous compressed
        data has been damaged or if random access is desired. Using
        `Flush::full` too often can seriously degrade compression.

        If `write` returns with `zs.avail_out == 0`, this function must
        be called again with the same value of the flush parameter and
        more output space (updated `zs.avail_out`), until the flush is
        complete (`write` returns with non-zero `zs.avail_out`). In the
        case of a `Flush::full`or `Flush::sync`, make sure that
        `zs.avail_out` is greater than six to avoid repeated flush markers
        due to `zs.avail_out == 0` on return.

        If the parameter flush is set to `Flush::finish`, pending input
        is processed, pending output is flushed and deflate returns the
        error `error::end_of_stream` if there was enough output space;
        if deflate returns with no error, this function must be called
        again with `Flush::finish` and more output space (updated
        `zs.avail_out`) but no more input data, until it returns the
        error `error::end_of_stream` or another error. After `write` has
        returned the `error::end_of_stream` error, the only possible
        operations on the stream are to reset or destroy.

        `Flush::finish` can be used immediately after initialization
        if all the compression is to be done in a single step. In this
        case, `zs.avail_out` must be at least value returned by
        `upper_bound` (see below). Then `write` is guaranteed to return
        the `error::end_of_stream` error. If not enough output space
        is provided, deflate will not return `error::end_of_stream`,
        and it must be called again as described above.

        `write` returns no error if some progress has been made (more
        input processed or more output produced), `error::end_of_stream`
        if all input has been consumed and all output has been produced
        (only when flush is set to `Flush::finish`), `error::stream_error`
        if the stream state was inconsistent (for example if `zs.next_in`
        or `zs.next_out` was `nullptr`), `error::need_buffers` if no
        progress is possible (for example `zs.avail_in` or `zs.avail_out`
        was zero). Note that `error::need_buffers` is not fatal, and
        `write` can be called again with more input and more output space
        to continue compressing.
    */
    void
    write(
        z_params& zs,
        Flush flush,
        error_code& ec)
    {
        doWrite(zs, flush, ec);
    }

    /** Update the compression level and strategy.

        This function dynamically updates the compression level and
        compression strategy. The interpretation of level and strategy
        is as in @ref reset. This can be used to switch between compression
        and straight copy of the input data, or to switch to a different kind
        of input data requiring a different strategy. If the compression level
        is changed, the input available so far is compressed with the old level
        (and may be flushed); the new level will take effect only at the next
        call of @ref write.

        Before the call of `params`, the stream state must be set as for a
        call of @ref write, since the currently available input may have to be
        compressed and flushed. In particular, `zs.avail_out` must be non-zero.

        @return `Z_OK` if success, `Z_STREAM_ERROR` if the source stream state
        was inconsistent or if a parameter was invalid, `error::need_buffers`
        if `zs.avail_out` was zero.
    */
    void
    params(
        z_params& zs,
        int level,
        Strategy strategy,
        error_code& ec)
    {
        doParams(zs, level, strategy, ec);
    }

    /** Return bits pending in the output.

        This function returns the number of bytes and bits of output
        that have been generated, but not yet provided in the available
        output. The bytes not provided would be due to the available
        output space having being consumed. The number of bits of output
        not provided are between 0 and 7, where they await more bits to
        join them in order to fill out a full byte. If pending or bits
        are `nullptr`, then those values are not set.

        @return `Z_OK` if success, or `Z_STREAM_ERROR` if the source
        stream state was inconsistent.
    */
    void
    pending(unsigned *value, int *bits)
    {
        doPending(value, bits);
    }

    /** Insert bits into the compressed output stream.

        This function inserts bits in the deflate output stream. The
        intent is that this function is used to start off the deflate
        output with the bits leftover from a previous deflate stream when
        appending to it. As such, this function can only be used for raw
        deflate, and must be used before the first `write` call after an
        initialization. `bits` must be less than or equal to 16, and that
        many of the least significant bits of `value` will be inserted in
        the output.

        @return `error::need_buffers` if there was not enough room in
        the internal buffer to insert the bits.
    */
    void
    prime(int bits, int value, error_code& ec)
    {
        return doPrime(bits, value, ec);
    }
};

/** Returns the upper limit on the size of a compressed block.

    This function makes a conservative estimate of the maximum number
    of bytes needed to store the result of compressing a block of
    data.

    @param bytes The size of the uncompressed data.

    @return The maximum number of resulting compressed bytes.
*/
std::size_t
deflate_upper_bound(std::size_t bytes);

/*  For the default windowBits of 15 and memLevel of 8, this function returns
    a close to exact, as well as small, upper bound on the compressed size.
    They are coded as constants here for a reason--if the #define's are
    changed, then this function needs to be changed as well.  The return
    value for 15 and 8 only works for those exact settings.

    For any setting other than those defaults for windowBits and memLevel,
    the value returned is a conservative worst case for the maximum expansion
    resulting from using fixed blocks instead of stored blocks, which deflate
    can emit on compressed data for some combinations of the parameters.

    This function could be more sophisticated to provide closer upper bounds for
    every combination of windowBits and memLevel.  But even the conservative
    upper bound of about 14% expansion does not seem onerous for output buffer
    allocation.
*/
inline
std::size_t
deflate_upper_bound(std::size_t bytes)
{
    return bytes +
        ((bytes + 7) >> 3) +
        ((bytes + 63) >> 6) + 5 +
        6;
}

} // zlib
} // beast
} // boost

#endif

/* deflate_stream.hpp
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
*/