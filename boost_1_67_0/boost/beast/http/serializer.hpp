//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_SERIALIZER_HPP
#define BOOST_BEAST_HTTP_SERIALIZER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/variant.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/chunk_encode.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace http {

/** Provides buffer oriented HTTP message serialization functionality.

    An object of this type is used to serialize a complete
    HTTP message into a sequence of octets. To use this class,
    construct an instance with the message to be serialized.
    The implementation will automatically perform chunk encoding
    if the contents of the message indicate that chunk encoding
    is required.

    Chunked output produced by the serializer never contains chunk
    extensions or trailers, and the location of chunk boundaries
    is not specified. If callers require chunk extensions, trailers,
    or control over the exact contents of each chunk they should
    use the serializer to write just the message header, and then
    assume control over serializing the chunked payload by using
    the chunk buffer sequence types @ref chunk_body, @ref chunk_crlf,
    @ref chunk_header, and @ref chunk_last.

    @tparam isRequest `true` if the message is a request.

    @tparam Body The body type of the message.

    @tparam Fields The type of fields in the message.
*/
template<
    bool isRequest,
    class Body,
    class Fields = fields>
class serializer
{
public:
    static_assert(is_body<Body>::value,
        "Body type requirements not met");

    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");

    /** The type of message this serializer uses

        This may be const or non-const depending on the
        implementation of the corresponding <em>BodyWriter</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using value_type = __implementation_defined__;
#else
    using value_type = typename std::conditional<
        std::is_constructible<typename Body::writer,
            header<isRequest, Fields>&,
            typename Body::value_type&>::value &&
        ! std::is_constructible<typename Body::writer,
            header<isRequest, Fields> const&,
            typename Body::value_type const&>::value,
        message<isRequest, Body, Fields>,
        message<isRequest, Body, Fields> const>::type;
#endif

private:
    enum
    {
        do_construct        =   0,

        do_init             =  10,
        do_header_only      =  20,
        do_header           =  30,
        do_body             =  40,
        
        do_init_c           =  50,
        do_header_only_c    =  60,
        do_header_c         =  70,
        do_body_c           =  80,
        do_final_c          =  90,
    #ifndef BOOST_BEAST_NO_BIG_VARIANTS
        do_body_final_c     = 100,
        do_all_c            = 110,
    #endif

        do_complete         = 120
    };

    void fwrinit(std::true_type);
    void fwrinit(std::false_type);

    template<std::size_t, class Visit>
    void
    do_visit(error_code& ec, Visit& visit);

    using writer = typename Body::writer;

    using cb1_t = buffers_suffix<typename
        Fields::writer::const_buffers_type>;        // header
    using pcb1_t  = buffers_prefix_view<cb1_t const&>;

    using cb2_t = buffers_suffix<buffers_cat_view<
        typename Fields::writer::const_buffers_type,// header
        typename writer::const_buffers_type>>;      // body
    using pcb2_t = buffers_prefix_view<cb2_t const&>;

    using cb3_t = buffers_suffix<
        typename writer::const_buffers_type>;       // body
    using pcb3_t = buffers_prefix_view<cb3_t const&>;

    using cb4_t = buffers_suffix<buffers_cat_view<
        typename Fields::writer::const_buffers_type,// header
        detail::chunk_size,                         // chunk-size
        net::const_buffer,                          // chunk-ext
        chunk_crlf,                                 // crlf
        typename writer::const_buffers_type,        // body
        chunk_crlf>>;                               // crlf
    using pcb4_t = buffers_prefix_view<cb4_t const&>;

    using cb5_t = buffers_suffix<buffers_cat_view<
        detail::chunk_size,                         // chunk-header
        net::const_buffer,                          // chunk-ext
        chunk_crlf,                                 // crlf
        typename writer::const_buffers_type,        // body
        chunk_crlf>>;                               // crlf
    using pcb5_t = buffers_prefix_view<cb5_t const&>;

    using cb6_t = buffers_suffix<buffers_cat_view<
        detail::chunk_size,                         // chunk-header
        net::const_buffer,                          // chunk-size
        chunk_crlf,                                 // crlf
        typename writer::const_buffers_type,        // body
        chunk_crlf,                                 // crlf
        net::const_buffer,                          // chunk-final
        net::const_buffer,                          // trailers 
        chunk_crlf>>;                               // crlf
    using pcb6_t = buffers_prefix_view<cb6_t const&>;

    using cb7_t = buffers_suffix<buffers_cat_view<
        typename Fields::writer::const_buffers_type,// header
        detail::chunk_size,                         // chunk-size
        net::const_buffer,                          // chunk-ext
        chunk_crlf,                                 // crlf
        typename writer::const_buffers_type,        // body
        chunk_crlf,                                 // crlf
        net::const_buffer,                          // chunk-final
        net::const_buffer,                          // trailers 
        chunk_crlf>>;                               // crlf
    using pcb7_t = buffers_prefix_view<cb7_t const&>;

    using cb8_t = buffers_suffix<buffers_cat_view<
        net::const_buffer,                          // chunk-final
        net::const_buffer,                          // trailers 
        chunk_crlf>>;                               // crlf
    using pcb8_t = buffers_prefix_view<cb8_t const&>;

    value_type& m_;
    writer wr_;
    boost::optional<typename Fields::writer> fwr_;
    beast::detail::variant<
        cb1_t, cb2_t, cb3_t, cb4_t,
        cb5_t ,cb6_t, cb7_t, cb8_t> v_;
    beast::detail::variant<
        pcb1_t, pcb2_t, pcb3_t, pcb4_t,
        pcb5_t ,pcb6_t, pcb7_t, pcb8_t> pv_;
    std::size_t limit_ =
        (std::numeric_limits<std::size_t>::max)();
    int s_ = do_construct;
    bool split_ = false;
    bool header_done_ = false;
    bool more_ = false;

public:
    /// Constructor
    serializer(serializer&&) = default;

    /// Constructor
    serializer(serializer const&) = default;

    /// Assignment
    serializer& operator=(serializer const&) = delete;

    /** Constructor

        The implementation guarantees that the message passed on
        construction will not be accessed until the first call to
        @ref next. This allows the message to be lazily created.
        For example, if the header is filled in before serialization.

        @param msg A reference to the message to serialize, which must
        remain valid for the lifetime of the serializer. Depending on
        the type of Body used, this may or may not be a `const` reference.

        @note This function participates in overload resolution only if
        Body::writer is constructible from a `const` message reference.
    */
    explicit
    serializer(value_type& msg);

    /// Returns the message being serialized
    value_type&
    get()
    {
        return m_;
    }

    /// Returns the serialized buffer size limit
    std::size_t
    limit()
    {
        return limit_;
    }

    /** Set the serialized buffer size limit

        This function adjusts the limit on the maximum size of the
        buffers passed to the visitor. The new size limit takes effect
        in the following call to @ref next.

        The default is no buffer size limit.

        @param limit The new buffer size limit. If this number
        is zero, the size limit is removed.
    */
    void
    limit(std::size_t limit)
    {
        limit_ = limit > 0 ? limit :
            (std::numeric_limits<std::size_t>::max)();
    }

    /** Returns `true` if we will pause after writing the complete header.
    */
    bool
    split()
    {
        return split_;
    }

    /** Set whether the header and body are written separately.

        When the split feature is enabled, the implementation will
        write only the octets corresponding to the serialized header
        first. If the header has already been written, this function
        will have no effect on output.
    */
    void
    split(bool v)
    {
        split_ = v;
    }

    /** Return `true` if serialization of the header is complete.

        This function indicates whether or not all buffers containing
        serialized header octets have been retrieved.
    */
    bool
    is_header_done()
    {
        return header_done_;
    }

    /** Return `true` if serialization is complete.

        The operation is complete when all octets corresponding
        to the serialized representation of the message have been
        successfully retrieved.
    */
    bool
    is_done()
    {
        return s_ == do_complete;
    }

    /** Returns the next set of buffers in the serialization.

        This function will attempt to call the `visit` function
        object with a <em>ConstBufferSequence</em> of unspecified type
        representing the next set of buffers in the serialization
        of the message represented by this object. 

        If there are no more buffers in the serialization, the
        visit function will not be called. In this case, no error
        will be indicated, and the function @ref is_done will
        return `true`.

        @param ec Set to the error, if any occurred.

        @param visit The function to call. The equivalent function
        signature of this object must be:
        @code
            template<class ConstBufferSequence>
            void visit(error_code&, ConstBufferSequence const&);
        @endcode
        The function is not copied, if no error occurs it will be
        invoked before the call to @ref next returns.

    */
    template<class Visit>
    void
    next(error_code& ec, Visit&& visit);

    /** Consume buffer octets in the serialization.

        This function should be called after one or more octets
        contained in the buffers provided in the prior call
        to @ref next have been used.

        After a call to @ref consume, callers should check the
        return value of @ref is_done to determine if the entire
        message has been serialized.

        @param n The number of octets to consume. This number must
        be greater than zero and no greater than the number of
        octets in the buffers provided in the prior call to @ref next.
    */
    void
    consume(std::size_t n);

    /** Provides low-level access to the associated <em>BodyWriter</em>

        This function provides access to the instance of the writer
        associated with the body and created by the serializer
        upon construction. The behavior of accessing this object
        is defined by the specification of the particular writer
        and its associated body.

        @return A reference to the writer.
    */
    writer&
    writer_impl()
    {
        return wr_;
    }
};

/// A serializer for HTTP/1 requests
template<class Body, class Fields = fields>
using request_serializer = serializer<true, Body, Fields>;

/// A serializer for HTTP/1 responses
template<class Body, class Fields = fields>
using response_serializer = serializer<false, Body, Fields>;

} // http
} // beast
} // boost

#include <boost/beast/http/impl/serializer.hpp>

#endif

/* serializer.hpp
NpvMrwAAe79uUQMPflBL6+i/txow2P59K0Bnu2nAZ3Qo4MBhb7gkwm+4X7g/I99+Yi6iCILEAvKEw7/8T2HbPHfRfcjzI1TVt4pgdkLIRZS3SZV11wlVZrMJXYoLaF/pq2gthjryHNWUD5ci9XGqSS4ieYnTB4qHWqFZt1KSJzWsfBZVNGP5VfRprBS3FIO6ojA7G5n8Xt7O2i3syde9L4vxAM7Wo0wxrta/+Xiym/C0K08M5/1Ky1ichjaelomP0qsvBAmP1Ks/4U5PaGUeNpVHfN86s5MwmxkR4nuoZyXHAkB3fI+Xv2jIkj80zoVpP58SGbrDursbAy919NNz17cf9235N3rzcId9w+G/sJxSSPVNv0rga73711qwPy1Hplpgnp5cu6PpuADymGTSlXbxePZr9Gf4MNLIMLMcW9PMG0aYdpNLWlcvTPEQ+Ex3PxxIA8RD/Bz4CDAAKRBHo349KX7Qvcl9/4yBRGdu2RdGEvZuGcqLWyJgB/gM2RBlcEnRZOEYGEgRXQnQFNBkBRgIDBAJCAxIWV1VVRnQ4NAMeIFwVVlJCQREDRAFZFlXbpvwu+ohmMhG2dybIhkhohzq7y38nAhN0UhNDU2JTdG+dw/G+2dIx/BHaKmJqcknBmnHpigGCcaoBwdnqIkJR6bwB8de46pDOhMbIHs22uKMPybFfphSv9jev2VO/+JgMIqOH6Dg9mWabezOBw9tFwr6wecIACCwFwggsAsQQND0jwUwgOArEMDgBCDAIJUv3rxfExM/CLb/L6EkuJiPl5ialxEyOZooKRq5oqKCR8Ovx8XxbQfIya8IbcC7X2KZwXfeqYX67+YTMBk0INliXwne2o+V5z4e8a84Hf1v23nIL2lV/4seoRsp6cpv2tg2ZexqZx6gqDRv2CaMLEGJ/8GjdtD4Ebx+jkLEyUBZM4ZZvYJfEi/zF+79qEXiDHnZXejWsA6lfZ1kLatpg5XXDqAZpMq4ofYuIHZ5h6gF+8xFgpYAtmLinDyVa1tuYAt5/Upe/dQlmitzEIOtk9I/to62bBji99bvjFdmu04lzzqbpIRjOjEsaeX/5kjmv3h7aEoZrTrw9Ouu3xH4YE+GNtyYcj4vOaQGwSFMYD3DNXFfA4q/UcPs2mnIvJJYWYs0MEPd6XH/cy8VnMmwS6VlzAkBvpQBol6zZT1pKBDIpviJ0vzyy/bYf/NjpMv+jeqe+C2LjfTPOM7LjUz6f9e5350yFwCEomGiod8mBaBv3y+e3vMvcBakpAOG9/824B5/m1gby6DQRLZkWExFG5matmV4TFnHjU79/8NuamrqetIlpxaRmPX6oFv8JSFRpsVpqaKyulO2otn1UvHxC1f1A4gLAQMDw43NjQYEhMbEgMvw+Hv+0AeYy8r/H0zwEd5GgH+B/1edBM7RL5biq5zGT98d4l/te2OZ+M0E+gEWRKFP9pNXB0GiAH/rk8//+a/86ZeqQW5ocPD+F/4k9MPPypY5/vd4+5fI6PXtR4+BZe8Xv/7uFzPe7KPOnr6hnp7xe7fo7NcL0IOVkKXJD7WL/Ysv7PAX1dSUVJWVFi31F/7f/W9T4S9477+n3yn69F+20IEnPzP0XybzrzhDCAYH+kaIJohGSAbHht9DMG3qK8OpqcBAbUHq33o96Sc8HP3jPUMjEyQDVNNDQzTToz2EIyRTRGRkU0PUExQDY5P/PnZLgKuzf6k4AX7i4O5+7Obg6t/d7D75fj5uH4D8/bWA+PGXfxSA6n95xsw+Vst+YR9+/6uaL/rVmYv/5a1aqmr69RlYkzRnBwCwL//Vwfd/kq7+7RivoxozQVsKjTXfqIe1zsduDoaS7u3N9/Qo54PCfMA37xURUGeJeYzvc0ip6wwMpRzaJcEBdXGWhmC3LIzySNkNPMb3KTwp9Q3Yu9fVA9Z9WtVYzYBjUvXcNqbd4bFZzdCmXs15XbzNUCZdxEpETIdZScBC0i+GMEf7eHGFT54J8XWIb+qJKhnwzDOzbHuupBOAyQVTiUUWfUd+wkkVlcIdwBODPGq0gopVdUIxWEZhwB3PRYWIhSm0QznNGmXWGxDT4SnT8q7f5Nvmkl27yaXx4s3zrm6FOFxwWNqGSzJPznKQTE+T/UERWHDjmeL72UmX2FkJHS+wHHXFliuufJDOj29buROAUZ7mA55r+U4GCVMJHRsgfO91PF/304S6nfOZy+biK19nhhjo40THdam8FwJsrTOHeIRl/uJVL+Nwm1lNnD1wJdRZ9uuwwnHWtGIuwkhZZqGSVJRRrqWT8hcvAzJr7pbM//R4nr9DIpPNB/Sh8RWPz1+2tLJ382MuAZXuRso3XYU6xhe3CDm2LniC+aCHs0Pdz4qciOynAQpM+KBdAfsSqISO6Pbr0cpDHzE14xIwUx79EXXSLFxn8nUXAA8UssQ9w34T6qcYbqwUZsKT14T5dih6V2CT1QlIERfDwfI8h3fw4y4SW29qwhIslxI2Vhmfqt005xRjkpyfHNsgeFx2OlPitxfuI7PVgaQA668V56eaY2nuJ53WSXnUCcHWJwF6ylJTZplNU1N2mnSFrXcU0r/cN/ymbdE0wMU+In/nSCYUhRKpW9pVI0Jkaq70ULu6GMIFlsJiyhg+fCCJHhqtTKsqEP1M5j4XwAYGUCqLQ567yJSneMxJyrslOexXvEzMcFt35GJFk5Kcb8X7p08rh6FlI7seCwce4AKvo7j4SGmopfqfaKeyQs5tIVD8WxKIGkXWIPxUNchGD+/NKsa7PwBOV5FGgn0E2OtmaEmaWP/hdry7nSdXAQSPTdN2g/D5AYUBmFI59+GHV3fbTZMWKbBwApJkWoYrPGQ4f9hMehMf/LO4ZzSa4fi0okZMGFEDlX49JbmHyTASAL5QAyP9AcOAblqLjGOuAzMibWZfxXURhy8h+tn9Xgok5jJQGicpwzLkj9dtgv3PUaCFRGrxmE7Yg8xHCkJmK2PezAAmN2sudk4DxwBcnPkufl+UXjX9Zj22utj0f8ErSHjSsmLBIsRc+idixVXRrQdTzgMWlfsURdG0rdKBHfCPva1ZFGiTGpCP1+/iMc3X9P9O8wFtO71jGp5s8J5oYLxZFL+obBoAZYoZAIOWBy7crMJ5JNCECbL+3ZrAGB4xi5RMBEsbhhBVpHFxhj+/KPWtAEo9QhCghVsw+LgljR/bNx8/fnvohf+1gqVihxi3VnovE/THELifp1tXZR3QL2PvBbr62edVi+6fHi5iXXY69sUG7eDY6fb3Vxh4Tx/8zjVw3HEsEQsZxwxEVV52ecj8iuhwGAFfqM7YUyaLFMPAOsOHrTa+EVDO3dflQS688FdukbFOG9VdhlM0LJtZwwFSPzaZNjKTqV3D3QoW2KDozgDp8wyynWGaX1EOerjZrgZ7JINxlgjpqJ8Qd0Ovlyvf5uUBWU5zi8CA4UNgERuitBpgmPNUce6+IgifmwRTl5gMdaTYsuszhXONj5m5dc7YHZWGY5QQ7tBWsPH5jyAm+XbChEQBvAgEP2cJwi/BCDIB+qfxVzS1YoAUIXcXes+7Eq8cRVSD8kVqOKtfHma8v9iPjGrRaqQXMmcqCzn1rXhIq42t6d5VhTDBhrLqwr7fv7+/QAwAAMB/QP6A/gH7A/4H4g/kH6g/0H9g/sD+gfsD/wfhD+IfpD/If1D+oP5B+/PfH/Q/GH8w/2D9wf6D8wf3D94f/D8Efwj/EP0h/kPyh/QP2R/yPxR/KP9Q/aH+Q/OH9g/dH/o/DH8Y/zD9Yf7D8of1D9sf9j8cfzj/cP3h/sPzh/cP3x/+PwJ/BP8I/RH+I/JH9I/YH/E/En8k/0j9kf4j80f2j9wf+T8KfxT/KP1R/qPyR/WP2h/1Pxp/NP9o/dH+o/NH94/eH/0/Bn8M/xj9Mf5j8sf0j9kf8z8Wfyz/WP2x/mPzx/aP3R/7Pw5/HP84/XH+4/LH9Y/bH/c/Hn88/3j98f7j88eX4X8zYQCA/7397g7Ue7+C+DAmHQJIrwrQftg5YmnI6/bMy6rSpBcyY3HgdYPzzJg05+Z7Do4jlKeV2xuFe/V9gnmunQ7ujJG/R51m+9ZX5XcGeq2KkWPjOsWi5Qs2+REUcTDgrbMhjeAe7OHI6+kLm5bRYWbBqi8KOFdVSQZcpeBUZKeISlJpTvfoxqDlizfXAJ6/LC26Sdf3RaR17ZS3P+TgoTsodsm/103JWdWQhv0Eq9FRJalZs53uNnz6GJFQKuPKw0x3jSNhe8RLzYJ8pRUsQMDArUoXtrXCToNMLwNI9CFwDBOMQ/ig5tZzX90QBAn+J4exPaJ3qc7gSs+uHzegQD257Wt6WlAAkFsjgtNLAvfLE49BrZGuVTr+6DlgFvVd3kCW2tMuj+1OITo2XWSnrAkeXHO5QcTGLk02rKb49bGv2mD/r/AilZU2FcRu0gv2vPhv+fahzAqKHkNXOJLZW8CVONUQaYT2vQ0PLMK7BLfP3u9pvte2geDD6UqVV3q/YZt0Eq+Z5wkCM5/UfEN2jSr2yrKqHUOgyEXXl2BlwA3DGXL4MepYFHTFZj5jXHs6zJgCeRuDoXOs/e81DkjKxsfECGT9apfgmq+xSiLf6eIPlB9o7AV85CH96YPvI+R2P7YB/Lpdz0S8gH8NDUz/LnzH1s/f+StMFo+Nm22XDV3m2/HB/31mwIxbRAmiiVfaF55hGvnxDTfIiHmiCEMx1/dKPeSGe6CCB9dQdFuzT1kDIdpu6zKMHsEKVMW0BKZMR08vezkt64aid5+azi69jlpYkkJP6oygDXb0OxgwBh8iHzpv2G4KMeUeRcLJxCUbG6fvFeUSHaiEVW3ELhiYc9Vu0ASHraoaUiGiIv0OdZC5m29lfoIbiiJ6bomeeXSiHDeuCwP75qOeY66/XWNQ9HSoTWi05KHlxd1OPSrxHGaA0/q9Mck2raQW/f50vpsNjmxC9tR5IuxhmBnbQ3IJ0QIop8lZ0fhAg22dmwS7MBhC/5iWSbTS2zXlQNkRUJw15D4nbBw2SsigO37jooQX1pOroSWy4by15YH4Xda9mHRRz1sR9G9zTi9Y7P6TETS+JHbLjp0G1HClF5VoV1r28p0uLKXifksz43K7hyKqX0oocCO7IjD6LFq7uW4OPtyvkJo4TtZvl8PoMqVQIpam4tVkQ8/pUGIh+elEuOk/vQ2+ebjoG58Mwm+3kRooWoWPRHIeE29qVYkCTIs7bMFyd7u8XmsGJCXUxlVpZ2KaUUyfubQnXgTNVfoPu1D5C7KTb9rJ5vx9q8EmxYItmidVK5aIisfwhT0Tq6qWMfVh8JSdHETT4IOQbIU5uGC481l+auDlaTZ6fpDn/TCMXyCAI6rQ6aeySyazdSlZeiFjLTIRwy+3hDDCtjpVb1ZYaUiKJIRt7c4kJsHPIZl4Mro1Gme7ZCiUnYcPT438CQP5W2YhutFp8+jmBe/80SSx5zWrmZ0fLm/FxrK5JlqYznMgnppOs7VnWlCtZqNW2EScRB1+C97Uu1c9+Px9eMO4JpcFd1xGuzn0ej/++4WiQh1xApOHq5zKl8Lmm3cQ0B9dJ6UaoL6Xz7SXKSglpujjP3wU6ZQYIOcYZmw888UAbLXtW7WYOai+oTZOTrwq6+ofr1O1wQLCvOU12RIq62lS2ZZrKNdCOfCKa9qSwTVeh7Ot5TbdqIkuP8n4Fvqc7nD/pVYlLz8P6n+NvjC+kVJK6ZwAV8ko4jYBNj3H7fhYLXjTSj5eeY/TXGswoAxQcHnNNzbB2z2rbP3l1kz4MvcbHcT2Clz+SocuFvf/GTBF+BAJHkXjk5MAOWPH3QJO8lZNvS+yqWPBs7OJlYHx72vLZsbFfu4XQpEeug4lLorGL3LWsYgDlPYR/TOqhQgquXhXLzBLOfdVRSOmE8F99Se49Umb26dpkT42IlXBP4fgvHnurhB9L85+bGX/igOz6ciVvLTofJn7qd+GBD+ha2mvOWu3NpU5f8JLc4WMH7Y1h5XbksUHGCiS0r9/UrxptEChLOAYOJzf36coc8LIehilOA773Uycuym0LX5fmNzp0elZtwwbrTDpLFAi4Hihe+/Xfz2rsBujB/21WbtTCAXO5cQrzUco5JrQte3ktjldzAyZnhi97W45NXv0+o+dMS+yZ9weJ8CcvKgYxnhf0nHGtjNP9dhFT1GSzq6ehK/F5/lYZJYfGHNbYu3t9sBQvaprd+p89X7wtDiM4BhcHn3VtwH73a7kKINi5A0LoTPvSKTDedfsnNu1UF5Q8FfQEluj2bYiHUVP++WdICCc0iBG5iNqmB6WsrmNlnq+ibehwKs9ZaT0/TbvMZIqXXVMXwB42nAj4fOAOT2NPtL6WfWkoGl8nDlVbdUBtmFEXxyAOWiqIvRbvH+e3CL6eJx/PeyiAvkg7kLr0UhBL8FqkygTHrkvSONEfSPEr9VI7DRZSl4zt09TzeMtSWKiy798uwpeWob1dMf9ne2aunPG3ZrEuAvJScg8GCM2e7Utibimvbyu2mF2Fs3RC5JA7siUwDHvqBEqm1deQ1pQYYPyznW4a4FG6lrPEtMs+Uo7MNbEf9QM/eEVnj/25w5dfVDp+4q/So4Ur4I+iBE8JNEyl58tQFzVOe7rFIT2Lltd0IRUEUPOkKtlBpfELqPDBw+wUIGsNL1z+jG+GZRCZgJEXNzrvxZ8zofQEpUzIUrzPjE+F+qwaeMRVUN2x/RNEYD3/ZUOxbcHocje7RGuEB6U6qDCCTDZJabML9Ydhi87MukH8zhGhbTpyyfd3L5IYFSePIenRcURXZWW6rUf7QD7ix8lLmxH7bAIq3+IeytwC6CniWZtVKKxHlyGbihFM4/aRY7UqVtqACLhKXqFDFLlXX6rE5e+MPJKRl74lRa5jkpluky83yzjAdp5qc0YBIulDOGMiO6/WnNo2UMwvDfRm9x+W6CHDaW9nyvQw3hdLd2GpDzoBi0b6GA/RpK6NL6Ram8cJ+jBZPXYNbhy021Lc1ilLVTpWaG/2kakv1tNfdxBxhoJW9Kxv8/6b9qvHTztXFOdQHY6Z3l+xtz8rrpweeiKB1fo4WtP8MGm8CJNWLTyEIuXQGnTS7FFc/anYNU9X1cLn2ZzTtFbpmEa4PpG5v59F+iknsLcC5Hrn+kLkkA88WjtSbx00iArerqiIG+/4jDTi9dnZt2xosv8hjKzZlOq1YHBWsptCUTNPjyf3nVT+2kazzyIj2ToTXu55EETLbh62Cj2TEbA39f9gnnKPSBJK8luio9mIBymyJFZ+kO2k+Vmx40qhLldtT2F1t47qzWsl4K+HpppadJAPxw/2iDFnK8MUbjv29rbkkMranzY/4Yv7JnGtjm5nEPgREQiSQlqF0ZTrEXfl6LJLOJlkGhLmxOjrAz2MrvRb6lWo7EIO13zuJ334s13hP2KQZFWBa4KUeELNqkU1qKX9PaFIs/lf7T8ymTJBmCULpv1c7SCCBxwyLm19rCcVUyWeqou5R8V9NgDA5zfWr9Yo9UYL/177vxmDSUO/mFynDoCJXkDOm17Zym6P1/KQIhQb3g7Sqoy2OWk23cIZA61nOpBrD8LsKErAnDVvTLMuq4XDR6RtGvQMAhOOgbOnCvtT4B0PHbMvGmU0gub317Toe528jB2/jtfVxF7Mus+KOHhvUXx4IF9CRpeUxQ9dfF6RVyEgvTm/GBekU27R/FjMlheuQkjBCvLi1CNP6Z07hRPGoPBisw3ghrnJYhvgFvUJj3eIyVVM7OycjnPPbcp21JGyCR6nURvbX0peP3uTSO+2U8Qa+e0qLpPZFwNR/Ky4Izh46Jklp6Mzj8KRqQuYDZarISHV8lGQClMY/K75b7fANMKGpR2xK7OG6SfvKFyRZ6Qmww6q6DgHN0WaUAqWCqfSbvDVcxxzTasaXYamBDHb98xWV1jpOmtqXGmI5OZAeWL35I8WFtdhveJIvLE1JIHOjH950O9nRV7J8eEEPYvDdCQk4h6iFSQaAbt8VK6DkMbbhjmIFb5sTfJw2dWTRtpXlusIqZQZJ4zWwFVCauSWXOdIdp089LUDOpVGVRfvmCg8lSxBZjc8ZZjUkzT7fkb2atuTkyJdQfuc595uVRfvqeIQhy5NsELZTj+QirfuHm5Cow5KTG700TzgJW4XTPS22irkV/OhVjpByNQXlsWf33gviCCIhgRS0eMQVEr9HcCI23oc8XJbbKm/7XHfzm21xPBQCsBN91uTx7pCd5XKu75ucbk0cxKaoxcqcOVIQwjOl4Zzw1UBltSfy80SpmqVIinbd7fFv9Wl5witn/VZsrTbpcLqPA9AWNxW5ieECC/5AoTqTkPF9x1+8SzD7UBAbPY+hBzBVPQF/FhSY7z3+CZleWGMvjNQFDvUs750lP9iKvNoU8e4vHjzoFRQr55oZ6yiymqGoIBNYgol5NusdmA4DJ3PZLCIasJg7eCUoG1fZYA0iT0v75MuXrPd1+vGXbWW3OW8vsWbZAfVck6zjizPeLN3V5QnmDAn+JWLUmU6ZMz77sRGszrHOkQ+U04gnsBvHlvZmicGB9XdolFkfIEZxwFdffOtmZFNJH1mb0uS6zmMQEmCV7xYUNGn/0bPvOamFQ9puqKOr8MiTxPK10mnv6nQe7oXXRFJodCRmv7rT2MeoiFim9qds5/6A3rm9IOjtffWwOWbjhLRVLKMp1OWT8W2nzP5w1dk1ohCAg6lDVBOSZLiL5hZEN2IaU6jblhtPD/fl21TeNr9nC3KTPVamjCIvSZo/BDeDChlj+Tu6elrUZg4+D1Go591Q5Ec53aXC+FBdccpPQipOYTVvRyp3YXa7zF5Dco7AVviJpmgJbyzGJiIE/hBcHbPrg9umIvfspKJSXxOelw+2VM2u5Uz0LZAeNxedl2vMg3WQYrcSflvLsBJjgDZ41T5+KGo62VvfEFO2utRp8OBouaWP+N4tiVHtXvftQMqGNQ4brr4T6QllUCCXMtCS1SQGcNNHwEdhsNtmaAvy6GoyeUo3bIPYBj3J+iw4kqKJ/l1dCfXOYI+2Zz7Kwa7tYA8SQF4pynYtRRgdMFlzzs1uGNAnFs8wzT6CerMxG6kklIDI1P2I5BKF71G2xhsX+oFpJcbazMtlHi7s2TkQ4PwpkEo7ZItG7moZIzhdVl1iUlZXrQQ73YrvolXywWHt84EOUogqw=
*/