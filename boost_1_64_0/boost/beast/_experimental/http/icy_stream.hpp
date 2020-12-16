//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_ICY_STREAM_HPP
#define BOOST_BEAST_HTTP_ICY_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/logic/tribool.hpp>
#include <type_traits>

namespace boost {
namespace beast {
namespace http {

/** Stream wrapper to process Shoutcast HTTP responses

    This wrapper replaces the word "ICY" in the first
    HTTP response received on the connection, with "HTTP/1.1".
    This allows the Beast parser to be used with Shoutcast
    servers, which send a non-standard HTTP message as the
    response.

    For asynchronous operations, the application must ensure
    that they are are all performed within the same implicit
    or explicit strand.

    @par Thread Safety
    @e Distinct @e objects: Safe.@n
    @e Shared @e objects: Unsafe.
    The application must also ensure that all asynchronous
    operations are performed within the same implicit or explicit strand.

    @par Example
    To use the @ref icy_stream template with an @ref tcp_stream
    you would write:
    @code
    http::icy_stream<tcp_stream> is(ioc);
    @endcode

    @tparam NextLayer The type representing the next layer, to which
    data will be read and written during operations. For synchronous
    operations, the type must support the <em>SyncStream</em> concept.
    For asynchronous operations, the type must support the
    <em>AsyncStream</em> concept.

    @note A stream object must not be moved or destroyed while there
    are pending asynchronous operations associated with it.

    @par Concepts
    <em>AsyncStream</em>, <em>SyncStream</em>
*/
template<class NextLayer>
class icy_stream
{
    NextLayer stream_;
    char buf_[8];
    unsigned char n_ = 0;
    bool detect_ = true;

    struct ops;

    static
    net::const_buffer
    version()
    {
        return {"HTTP/1.1", 8};
    }

public:
    /// The type of the next layer.
    using next_layer_type =
        typename std::remove_reference<NextLayer>::type;

    /// The type of the executor associated with the object.
    using executor_type = typename next_layer_type::executor_type;

    icy_stream(icy_stream&&) = default;
    icy_stream(icy_stream const&) = default;
    icy_stream& operator=(icy_stream&&) = default;
    icy_stream& operator=(icy_stream const&) = default;

    /** Destructor

        The treatment of pending operations will be the same as that
        of the next layer.
    */
    ~icy_stream() = default;

    /** Constructor

        Arguments, if any, are forwarded to the next layer's constructor.
    */
    template<class... Args>
    explicit
    icy_stream(Args&&... args);

    //--------------------------------------------------------------------------

    /** Get the executor associated with the object.
    
        This function may be used to obtain the executor object that the
        stream uses to dispatch handlers for asynchronous operations.

        @return A copy of the executor that stream will use to dispatch handlers.
    */
    executor_type
    get_executor() noexcept
    {
        return stream_.get_executor();
    }

    /** Get a reference to the next layer

        This function returns a reference to the next layer
        in a stack of stream layers.

        @return A reference to the next layer in the stack of
        stream layers.
    */
    next_layer_type&
    next_layer()
    {
        return stream_;
    }

    /** Get a reference to the next layer

        This function returns a reference to the next layer in a
        stack of stream layers.

        @return A reference to the next layer in the stack of
        stream layers.
    */
    next_layer_type const&
    next_layer() const
    {
        return stream_;
    }

    //--------------------------------------------------------------------------

    /** Read some data from the stream.

        This function is used to read data from the stream. The function call will
        block until one or more bytes of data has been read successfully, or until
        an error occurs.
        
        @param buffers The buffers into which the data will be read.
        
        @returns The number of bytes read.
        
        @throws system_error Thrown on failure.
        
        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::read` if you need to ensure
        that the requested amount of data is read before the blocking operation
        completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers);

    /** Read some data from the stream.

        This function is used to read data from the stream. The function call will
        block until one or more bytes of data has been read successfully, or until
        an error occurs.
        
        @param buffers The buffers into which the data will be read.
        
        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes read.
                
        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::read` if you need to ensure
        that the requested amount of data is read before the blocking operation
        completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(
        MutableBufferSequence const& buffers,
        error_code& ec);

    /** Start an asynchronous read.
    
        This function is used to asynchronously read one or more bytes of data from
        the stream. The function call always returns immediately.
        
        @param buffers The buffers into which the data will be read. Although the
        buffers object may be copied as necessary, ownership of the underlying
        buffers is retained by the caller, which must guarantee that they remain
        valid until the handler is called.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
          const boost::system::error_code& error, // Result of operation.
          std::size_t bytes_transferred           // Number of bytes read.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.

        @note The `async_read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::async_read` if you need
        to ensure that the requested amount of data is read before the asynchronous
        operation completes.
    */
    template<
        class MutableBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 ReadHandler =
            net::default_completion_token_t<executor_type>
    >
    BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
    async_read_some(
        MutableBufferSequence const& buffers,
        ReadHandler&& handler =
            net::default_completion_token_t<executor_type>{});

    /** Write some data to the stream.
    
        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.
        
        @param buffers The data to be written.
        
        @returns The number of bytes written.
        
        @throws system_error Thrown on failure.
        
        @note The `write_some` operation may not transmit all of the data to the
        peer. Consider using the function `net::write` if you need to
        ensure that all data is written before the blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(ConstBufferSequence const& buffers);

    /** Write some data to the stream.
    
        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.
        
        @param buffers The data to be written.
        
        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes written.
                
        @note The `write_some` operation may not transmit all of the data to the
        peer. Consider using the function `net::write` if you need to
        ensure that all data is written before the blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(
        ConstBufferSequence const& buffers,
        error_code& ec);

    /** Start an asynchronous write.
        
        This function is used to asynchronously write one or more bytes of data to
        the stream. The function call always returns immediately.
        
        @param buffers The data to be written to the stream. Although the buffers
        object may be copied as necessary, ownership of the underlying buffers is
        retained by the caller, which must guarantee that they remain valid until
        the handler is called.
        
        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
          error_code const& error,          // Result of operation.
          std::size_t bytes_transferred     // Number of bytes written.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.
        
        @note The `async_write_some` operation may not transmit all of the data to
        the peer. Consider using the function `net::async_write` if you need
        to ensure that all data is written before the asynchronous operation completes.
    */
    template<
        class ConstBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
            net::default_completion_token_t<executor_type>
    >
    BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
    async_write_some(
        ConstBufferSequence const& buffers,
        WriteHandler&& handler =
            net::default_completion_token_t<executor_type>{});
};

} // http
} // beast
} // boost

#include <boost/beast/_experimental/http/impl/icy_stream.hpp>

#endif

/* icy_stream.hpp
zOHSK6n24et4RqzSMOy32qamWpurNGyr/p782PD58AVLF6eaRqFf/ZabxmH9PQG1rxz7DjbevY6yflf1/YTGaU0zrTFUnJKRARgqQuPk/i3gFye5aepqR841+oqT7DvbOM04yjhVtvXMM0LiNC7+4HZ71+Bv1NA4uX9L+MVJbqKN/bKD++Wwr17b3qtfbllov5yts7HNw+Kh8rY7PB6HjoP0o337FncfgziU+8QhoUXAXAWI2XsdyQ2+d8LjoO4Cv/Uj3xr9frRyaytejh8JnucXjjX2oX2SXxnzSLNmWe0v0/dTtxrtWa9yGH7Oea3GauOGtRFGaUH6L5UW5yJTcJvfOCwtQrspfNNklXG3MDDbponjV6LrzNGgX8YjpYuj08qmyxnGXBYoqkoX0xc26wjOOfRKl3ili87Rd55v0ua3SpuBTr+YNYftH9IqdO1RLjIz+Ns7LiytQrpO/NOqh3E3wF1+5FeC535ASit0QstQV2Me6y5Dpu/w6R9ZhpRW4XvmmLTpG6e96MPOy9+XEDBXMg9vCpvDoehUHCJtPA7WPiit4pVWm4w/EZEj+Lsnwq7vl/9Jpo+1pc7EVjrJLtG2027DDCKH02fwXEQtudEZ2fotdbPRqR05lti9FBGpb77jV6vwMzxtHrxh7H8bUc+cN2z85Sq3/eDT0OnfxPgRUXXO55JTAopjCfY3Gj9iIsfzVn0lIso5T5pL5zs753Mbf/IjXM853XnOFOxTjX1iRJx9TjlHwprfu7b/ZJLRyaZ8tAucTJmJ17miFyLB338/g4gZxxiDvMi9l5Db+f9Z5Jn4UNnFva06//vsyvNIKYOHbRvZNYuTmoaeS5ofUibR0T5MLV1ngZdac+h43SbCYdajq/3Qz+m/buYuixw8W1ZEkyu0b1/lSrqtPPvu58hObQb67g/fZjhM/3zIe2acBj7nRfKbDU6EwT6+isrwa9MznZprhx092seqO3cZd+mRipv8SQ4vy7a/YbOxHxoZUk5lHw+va+6sy8fMfzcZ8zDqfQffMnuv8fME4yfvYC5z3C/2lXVzWbwJY8QE0jQO2+0qOxeoPDpny+9AViUae8od92QOsquhU/aObFwtWPYIvy17Hu30kLWx+/QyjcJBHPxaZauihUfehAyR+PZRyG17m/53G/OD4flj3yN/MvbPB/zyJ6el2lbKn8nGPIjw6n0R8v3V+9X4+QY6Tv7Z977Nw3uMzsMBvzz80NiXBHqRh/X0PmGs05zxOjve5J3Jy1Ua2/rC5NWR5dFJLUPzKMfUpdA8GuPsM9AuYK401f+eyqO9LQ+RR+5vtn9eyY82tu6vqkbfcFh4bX0n6821Q328d6mvK6mVR3htl9dBYbTfyhHG3SW8/+oHzkEUdvnXya/vS/bt7T6HWcZ8VSCbsP4cCft9bPtNMo3eDYFx5qkRzjcT/9RPQlpFo9+yaWWd3F7Nc/h/TL9YyN41WvhzpfrA1qqfIam1R/ra7gb/92lm65DzveVPkl9/g+y72Xo0Ru79+nOzjP0SpaPjvr1rb0X8z5Mb5cEcozPDjpVHEdE6zauXzj+mb8L93e2gjcJyNUYxQvVuX2U6L3Ht6kmt86hjSt/aCba/i/R13MfbOjesGns0hY8hD0g4eB38Ft918H7rvP3WMfutU/dbT//vP3P8WK3XX7vMrGsv/H707+J7fXXLL3blXNf9/SS/deT+68XPigrev3rq49ENz//m9uTNf07uctWYwX7r7P3Wo1d/ff+xWmfvvb6/+vsZVHe9vs/+BOaMdf30MuNkSRGV35Ad+r9LpD0nXfPhTB8hdlrTHHbO0RkwHq6EreEqmADPhG1kds6N2SD/TjX+hZ4=
*/