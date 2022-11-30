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

#ifndef BOOST_BEAST_ZLIB_INFLATE_STREAM_HPP
#define BOOST_BEAST_ZLIB_INFLATE_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/zlib/detail/inflate_stream.hpp>

namespace boost {
namespace beast {
namespace zlib {

/** Raw deflate stream decompressor.

    This implements a raw deflate stream decompressor. The deflate
    protocol is a compression protocol described in
    "DEFLATE Compressed Data Format Specification version 1.3"
    located here: https://tools.ietf.org/html/rfc1951

    The implementation is a refactored port to C++ of ZLib's "inflate".
    A more detailed description of ZLib is at http://zlib.net/.

    Compression can be done in a single step if the buffers are large
    enough (for example if an input file is memory mapped), or can be done
    by repeated calls of the compression function. In the latter case, the
    application must provide more input and/or consume the output (providing
    more output space) before each call.
*/
class inflate_stream
    : private detail::inflate_stream
{
public:
    /** Construct a raw deflate decompression stream.

        The window size is set to the default of 15 bits.
    */
    inflate_stream() = default;

    /** Reset the stream.

        This puts the stream in a newly constructed state with
        the previously specified window size, but without de-allocating
        any dynamically created structures.
    */
    void
    reset()
    {
        doReset();
    }

    /** Reset the stream.

        This puts the stream in a newly constructed state with the
        specified window size, but without de-allocating any dynamically
        created structures.
    */
    void
    reset(int windowBits)
    {
        doReset(windowBits);
    }

    /** Put the stream in a newly constructed state.

        All dynamically allocated memory is de-allocated.
    */
    void
    clear()
    {
        doClear();
    }

    /** Decompress input and produce output.

        This function decompresses as much data as possible, and stops when
        the input buffer becomes empty or the output buffer becomes full. It
        may introduce some output latency (reading input without producing any
        output) except when forced to flush.

        One or both of the following actions are performed:

        @li Decompress more input starting at `zs.next_in` and update `zs.next_in`
        and `zs.avail_in` accordingly. If not all input can be processed (because
        there is not enough room in the output buffer), `zs.next_in` is updated
        and processing will resume at this point for the next call.

        @li Provide more output starting at `zs.next_out` and update `zs.next_out`
        and `zs.avail_out` accordingly. `write` provides as much output as
        possible, until there is no more input data or no more space in the output
        buffer (see below about the flush parameter).

        Before the call, the application should ensure that at least one of the
        actions is possible, by providing more input and/or consuming more output,
        and updating the values in `zs` accordingly. The application can consume
        the uncompressed output when it wants, for example when the output buffer
        is full (`zs.avail_out == 0`), or after each call. If `write` returns no
        error and with zero `zs.avail_out`, it must be called again after making
        room in the output buffer because there might be more output pending.

        The flush parameter may be `Flush::none`, `Flush::sync`, `Flush::finish`,
        `Flush::block`, or `Flush::trees`. `Flush::sync` requests to flush as much
        output as possible to the output buffer. `Flush::block` requests to stop if
        and when it gets to the next deflate block boundary. When decoding the
        zlib or gzip format, this will cause `write` to return immediately after
        the header and before the first block. When doing a raw inflate, `write` will
        go ahead and process the first block, and will return when it gets to the
        end of that block, or when it runs out of data.

        The `Flush::block` option assists in appending to or combining deflate
        streams. Also to assist in this, on return `write` will set `zs.data_type`
        to the number of unused bits in the last byte taken from `zs.next_in`, plus
        64 if `write` is currently decoding the last block in the deflate stream,
        plus 128 if `write` returned immediately after decoding an end-of-block code
        or decoding the complete header up to just before the first byte of the
        deflate stream. The end-of-block will not be indicated until all of the
        uncompressed data from that block has been written to `zs.next_out`. The
        number of unused bits may in general be greater than seven, except when
        bit 7 of `zs.data_type` is set, in which case the number of unused bits
        will be less than eight. `zs.data_type` is set as noted here every time
        `write` returns for all flush options, and so can be used to determine the
        amount of currently consumed input in bits.

        The `Flush::trees` option behaves as `Flush::block` does, but it also returns
        when the end of each deflate block header is reached, before any actual data
        in that block is decoded. This allows the caller to determine the length of
        the deflate block header for later use in random access within a deflate block.
        256 is added to the value of `zs.data_type` when `write` returns immediately
        after reaching the end of the deflate block header.

        `write` should normally be called until it returns `error::end_of_stream` or
        another error. However if all decompression is to be performed in a single
        step (a single call of `write`), the parameter flush should be set to
        `Flush::finish`. In this case all pending input is processed and all pending
        output is flushed; `zs.avail_out` must be large enough to hold all of the
        uncompressed data for the operation to complete. (The size of the uncompressed
        data may have been saved by the compressor for this purpose.) The use of
        `Flush::finish` is not required to perform an inflation in one step. However
        it may be used to inform inflate that a faster approach can be used for the
        single call. `Flush::finish` also informs inflate to not maintain a sliding
        window if the stream completes, which reduces inflate's memory footprint.
        If the stream does not complete, either because not all of the stream is
        provided or not enough output space is provided, then a sliding window will be
        allocated and `write` can be called again to continue the operation as if
        `Flush::none` had been used.

        In this implementation, `write` always flushes as much output as possible to
        the output buffer, and always uses the faster approach on the first call. So
        the effects of the flush parameter in this implementation are on the return value
        of `write` as noted below, when `write` returns early when `Flush::block` or
        `Flush::trees` is used, and when `write` avoids the allocation of memory for a
        sliding window when `Flush::finish` is used.

        If a preset dictionary is needed after this call,
        `write` sets `zs.adler` to the Adler-32 checksum of the dictionary chosen by
        the compressor and returns `error::need_dictionary`; otherwise it sets
        `zs.adler` to the Adler-32 checksum of all output produced so far (that is,
        `zs.total_out bytes`) and returns no error, `error::end_of_stream`, or an
        error code as described below. At the end of the stream, `write` checks that
        its computed adler32 checksum is equal to that saved by the compressor and
        returns `error::end_of_stream` only if the checksum is correct.

        This function returns no error if some progress has been made (more input
        processed or more output produced), `error::end_of_stream` if the end of the
        compressed data has been reached and all uncompressed output has been produced,
        `error::need_dictionary` if a preset dictionary is needed at this point,
        `error::invalid_data` if the input data was corrupted (input stream not
        conforming to the zlib format or incorrect check value), `error::stream_error`
        if the stream structure was inconsistent (for example if `zs.next_in` or
        `zs.next_out` was null), `error::need_buffers` if no progress is possible or
        if there was not enough room in the output buffer when `Flush::finish` is
        used. Note that `error::need_buffers` is not fatal, and `write` can be called
        again with more input and more output space to continue decompressing.
    */
    void
    write(z_params& zs, Flush flush, error_code& ec)
    {
        doWrite(zs, flush, ec);
    }
};

} // zlib
} // beast
} // boost

#endif

/* inflate_stream.hpp
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
*/