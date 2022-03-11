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