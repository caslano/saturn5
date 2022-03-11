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