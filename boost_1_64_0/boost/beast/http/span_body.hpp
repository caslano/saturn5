//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_SPAN_BODY_HPP
#define BOOST_BEAST_HTTP_SPAN_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/span.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using @ref span

    This body uses @ref span as a memory-based container for
    holding message payloads. The container represents a
    non-owning reference to a contiguous area of memory.
    Messages using this body type may be serialized and
    parsed.

    Unlike @ref buffer_body, only one buffer may be provided
    during a parse or serialize operation.
*/
template<class T>
struct span_body
{
private:
    static_assert(std::is_pod<T>::value,
        "POD requirements not met");

public:
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type = span<T>;

    /** Returns the payload size of the body

        When this body is used with @ref message::prepare_payload,
        the Content-Length will be set to the payload size, and
        any chunked Transfer-Encoding will be removed.
    */
    static
    std::uint64_t
    size(value_type const& body)
    {
        return body.size();
    }

    /** The algorithm for parsing the body

        Meets the requirements of <em>BodyReader</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using reader = __implementation_defined__;
#else
    class reader
    {
        value_type& body_;

    public:
        template<bool isRequest, class Fields>
        explicit
        reader(header<isRequest, Fields>&, value_type& b)
            : body_(b)
        {
        }

        void
        init(boost::optional<
            std::uint64_t> const& length, error_code& ec)
        {
            if(length && *length > body_.size())
            {
                ec = error::buffer_overflow;
                return;
            }
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            auto const n = buffer_bytes(buffers);
            auto const len = body_.size();
            if(n > len)
            {
                ec = error::buffer_overflow;
                return 0;
            }
            ec = {};
            net::buffer_copy(net::buffer(
                body_.data(), n), buffers);
            body_ = value_type{
                body_.data() + n, body_.size() - n};
            return n;
        }

        void
        finish(error_code& ec)
        {
            ec = {};
        }
    };
#endif

    /** The algorithm for serializing the body

        Meets the requirements of <em>BodyWriter</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using writer = __implementation_defined__;
#else
    class writer
    {
        value_type const& body_;

    public:
        using const_buffers_type =
            net::const_buffer;

        template<bool isRequest, class Fields>
        explicit
        writer(header<isRequest, Fields> const&, value_type const& b)
            : body_(b)
        {
        }

        void
        init(error_code& ec)
        {
            ec = {};
        }

        boost::optional<std::pair<const_buffers_type, bool>>
        get(error_code& ec)
        {
            ec = {};
            return {{
                { body_.data(),
                  body_.size() * sizeof(typename
                    value_type::value_type)},
                false}};
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif

/* span_body.hpp
IbxXuFK4SnifcLUwX7jGLd+14r5fuE64XviAcINbuo3iflC4SbhZuEX4kFu6h8X9iHCrcJtwu0H/XNz/9FzctltV/ZQseucTh0LO3Ts8V8/a/1KMfy7OeS7udID8bsrv6U6dZ5u/TwS4zsVVgJVgKKwDK8KmMAy2heGwJ6wEh8LKMA1GwvGwCrwDVoV3wWowH1aHu2ENeBTWgm/D2vBrWAcWp0zRMBTWhTVgPdha5ur6wgYwCTaEY2SObjaMhWtgI/gwbAyfhU3gSdgUfgrj4C+wJQyycc9hOIyHtWFb2AS2gwnwRtgDtodDYAeYDTvC+bArvBd2gxthd7gL9oD7YU/4JrwJfgn7wh9hPxjI89UfVoADYHU4EF4HB8F4OBj2g0NgBhwKZ8FhMB8Oh7thMjwER8BX4Uj4DkyBZ+EoqHGvU2EYvAXGwtHwepgBu8IxcCAcC1NgJpwKs+ByOA5uhdnwMLwdvg6nw/dgHv/+CWfAS/AOWIQ2OBOGwFmwKpwNY+Ac2BLOgx3hfNgXLoBJcCGcBBfB2XAxXAPvgnvgEvgsXApfg8vgKXg3/AwuhxfhPdDOs7wCBsN7YSRcBevB1bA5zIft4Ro4DK6F6fB+OAOug6vgergJPgAfgxvgQbgRvgIfhCfhJvgp3AwvwC1QL8bvFiwNt8LKcBuMhtthHNwBe8CdcAjcBbPho3A+fAzeC3fDjXAP3AUfh/vhE/Bl+CR8Cz4FP4ZPw2/gM/AXuB8a2+QcgDXhQRgPD8Eu8Fk4AD4HR8LDMAs+D6fBF+B8+Df4ADwCn4Qvwr/Bl+AJ+DL8AB6FX8JX4I/wVRhIf/QajILHYAv4OuwAj8M+8A2YCP8BM+DbMBeegpPEneWfq79mc/X+eXr/PP2V5umjavnn6f2H//Af/sN/+A//4T/8h//wH/7Df/iPv8LxB+j/R6RnJmaOvgb6/0paUNl5FTX23rajjzPWTchMySFrslW2AXFRmrXXQrRurS2hjmLISkIO7lO2Ae263JSYmkiZ05NHZDD3fcV1EdD/oTMoo/I+IXlHSITKyFchXJMj78Sc3GxWhGjSyNwLKlrt0YOvtX6DGTdChY9XuZDEaV+P4yo8/DLlirL2tgiE0Wo/Hs4hZW0oZZ1ql2/1dfk+Hq4xQp5QZVULPWERofZmuk+Vc4SU0YzTxNrLsIlyf2quecORm6FxhMpaVwNVeC+NGTm+RS9GPPzx+Vz5x6t0Zet57jXYWoW/Y67ZwTEmRZZCserjJhUnWLkzSZOo3Ied9i+U/dpkX5o2Kvx9Ff5qmOxdo2lq38MoaO6VMYv7FsYJbuUmVpU9BefIXhnE93bcSDTqq1XZJHiT2h+nSNmv1fm0miNGZTvW6eC+LIHUKXFGGPdJnZey4KYsbm3qJ9GzHUQikUcQ4z5lPel0nxxb33i7VxIvytoLaYly3+9+r6w1xnao8ACf92SlCp9Lua39vtTnM85rkG1UcQIve9+2qjglrHUvH1fuTJ/3LV+FLy7U/bnsXibck6CnPO9JrNM9cX5OAmW9u86SSSeNOPQ1SSqPvIzMsbfkTEzOctqrJzGLh03qX+KR2tpzy+l57maFlxK3rm1Wbl3dS8d1jFRhRNUWq7Bwqw5nKndJrolwozTKHc1zVvNy/ZZz/yB796gyK79ga7+ugrXcmkld9JJ9/trL/lxxyJ1GXTj6t8zRiSOxpxqRPJI/6Oq8tUeJG+mxR5KswSPhYVqI9B2TlLsO33roKs2simpNLfUIhkibnKDi1KRvsfalk3xCcasycIwdNSm3oI1Ok3zNPYNmhKBzLET7cWsrl90ribLiR1nd+t6FJaSn5sR1hPmEJO226pHq8/Y8Sxw=
*/