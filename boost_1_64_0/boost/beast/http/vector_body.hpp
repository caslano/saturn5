//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_VECTOR_BODY_HPP
#define BOOST_BEAST_HTTP_VECTOR_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <cstdint>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using `std::vector`

    This body uses `std::vector` as a memory-based container
    for holding message payloads. Messages using this body type
    may be serialized and parsed.
*/
template<class T, class Allocator = std::allocator<T>>
struct vector_body
{
private:
    static_assert(sizeof(T) == 1,
        "T requirements not met");

public:
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type = std::vector<T, Allocator>;

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
            if(length)
            {
                if(*length > body_.max_size())
                {
                    ec = error::buffer_overflow;
                    return;
                }
                body_.reserve(beast::detail::clamp(*length));
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
            if (n > body_.max_size() - len)
            {
                ec = error::buffer_overflow;
                return 0;
            }

            body_.resize(len + n);
            ec = {};
            return net::buffer_copy(net::buffer(
                &body_[0] + len, n), buffers);
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
            return {{const_buffers_type{
                body_.data(), body_.size()}, false}};
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif

/* vector_body.hpp
nc1u5b7e9qQWKG1c1y5sNPwe9FXHkkcja52WXcqdYDuk1knEzzkPV7sRS6e4XaW50baK2ey/a6dED2Xm3dBaf6XTBsPdx9aQGAOZcfuFHipMv0c9T8yPediYyHMr+URbdh9blLuL7ahmk+fepYw8b542JwdUmsa2XdIuBnhcl6uOsyxsYoQTv7bo5x9ReXS0pbDz2gpa/iP0JR8zI71aD+c7rCituqy11lZd5yAeY5tWlZn923lSvqEnr8K1urfBUNGlHVV517JNoQ73UodVlH9BnVVDn7cekTrjutqptveiSnfMFm2zy7U72cDIM7FXXUeUPCOssKfyrMcdjqCP71F2Fs/zsED0JDR2+4zgktElGxYtYS9RsgGrPwQUwWGzhxUNtAfgLGovWjwokLjOa4bxvFhr1yyFHvdA+sS16rw7uPOtSI+feX1ckVObcF37R+r+gIq3mJq8Uaui/ArSlqKew6nnSaqeyzulT7fW7zmr4o6iBm801++x0jvVrfv9sdYi3KTibtZSpew9ncpenraZSAjp1VoXN1A3pZ3qpmaUo0/PIN9armvmWbZFOuHnKhbYtSQUwsYo7EFXGyPas2VjtHWjtW5eE0387inws2yH0gr8Gpl+iRs919ybsMHV7qg0fq0sv5bKXcRyN1dpZoo7+ZZkpbiV3xyX/nKSl/4yz4vd0dzL2B2tFLuLmWJ3NE1sSWKt3yNleORidxQqz0Y7FSdL2R3VRaRvlbQhpDHb8girHQ9TYd0JK+ryHBQpd+3WzsstKd9Py2/sCrmmpE3WNWEg49M+hniu9jETlPsu9E665/MpdbFYxRmjNXBdO0+1zeTgwl/Xlexk4ss4Iu/hx7ai0LCTCb7fvDZlKOPtN0/i1NBCZZ23Jsq9zFae3izXFuDLVkbSRVlr58Uq9z08loFaji3Q015G+o0GKt5KWyT/T7OJjYWVX6SHjUUlWWOqmQq/y1aG6x7BlWTaivqod1zE5RptcZTGpe+S36Fq6wind7RrHaw1hcuvV/Ugv608ZCrOGgY1Nso+VdtB6nPaamvNq5XqHCWsNfWCVfoA4pIffzVX7lStDK2tA//Xlt/s8yrdOr0R/WonSjCZsBe47m/5Dayp13Bas0gt16yMv8zfz9dV2iKqTkJwv6ncU/Ub+FXMYtRyUNtLesLwfWOdo38vqU0hfTv1vH+g4p/WPX4zpU/OUuH9bZH6E9pneppWRfmbeX2ptaV+crieh1gZ4SVyLS2/mWNUukG2grq+1bKnWaTS/qR1JBX54eczP+drH5+aKGsfSTvdbaThOkOV2/n6EtEVBqmyoDOX+n1dd18T7ouKyu6Jtd8cvxn/ClPitFYhIs9iryv0MXlufe5cL3ZQS9zsoELxW2n5mdfnun73VFm38H6d+HCZrFuorbGeY2Ug5eP9X+JVtd7rqir3NL2tbvdlIyVpIqx33gjlnqon6MV82kiFqziz9M66TZ5fM59wr2tfjiH8ZhXeWP+UGq6gF7HehTusNfzL+nyW66l0uXoL4rq8x8hzOkqF1yffii7PeiXpb+aq8POcYbq2hrHPAa61iryvZKmwKD2M0C20wVfI4QOtjuc7i7zzNlbx0/QYyi/rb3m8r9Gm5L3NlMKvNZjk1q7SvNhpZfmw0xr0f2in9WfZYz2k7Jwi4hZuC+r2cf/nAr5/8XDPGuP+evZY18ru6qKGP8KhxjQ87zxRpj2WzIfBQCTNzR7rerHHugEWc7J7mWTN//DMSLogmCHpHtaxP4LbYSO4A7aBj8LucDe8DT4B58Cn4Cb4NHwY7oc74AH4GjwI34OHrHWhZB5D5l3S3Ox57pR1oebCSDgfVofLYAO4GMaJu40=
*/