//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_BASIC_DYNAMIC_BODY_HPP
#define BOOST_BEAST_HTTP_BASIC_DYNAMIC_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/buffer.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using a <em>DynamicBuffer</em>

    This body uses a <em>DynamicBuffer</em> as a memory-based container
    for holding message payloads. Messages using this body type
    may be serialized and parsed.
*/
template<class DynamicBuffer>
struct basic_dynamic_body
{
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");

    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type = DynamicBuffer;

    /** Returns the payload size of the body

        When this body is used with @ref message::prepare_payload,
        the Content-Length will be set to the payload size, and
        any chunked Transfer-Encoding will be removed.
    */
    static
    std::uint64_t
    size(value_type const& v)
    {
        return v.size();
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
            std::uint64_t> const&, error_code& ec)
        {
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            auto const n = buffer_bytes(buffers);
            if(beast::detail::sum_exceeds(body_.size(), n, body_.max_size()))
            {
                ec = error::buffer_overflow;
                return 0;
            }
            auto const mb =
                beast::detail::dynamic_buffer_prepare(
                    body_, (std::min)(n,
                        body_.max_size() - body_.size()),
                            ec, error::buffer_overflow);
            if(ec)
                return 0;
            auto const bytes_transferred =
                net::buffer_copy(*mb, buffers);
            body_.commit(bytes_transferred);
            return bytes_transferred;
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
        DynamicBuffer const& body_;

    public:
        using const_buffers_type =
            typename DynamicBuffer::const_buffers_type;

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
            return {{body_.data(), false}};
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif

/* basic_dynamic_body.hpp
i27RLbpFt+gW3f6/2xax/yNqObcJ7P92/n1jgGWzVyHXytafxvpSdz2mv+vqVrjrKsocdRkDQ/XmqLrKsLoC8SE4GpM2E0TnMTMnBZCJz+FzsNaWyT3EqlS6Cgscupif365b7KqTS1N1xiBnHS7Lec3OOrksxzU763LlgOLnUOrwcxivse1v2CU09rxhvgjLNHqNEWGx8770qvUPNHn5k8L1+vbN2Im6p2h0Z4TqZifxu1aBrf8Zjf7scP0N8v+w9WfFeusv9NZf4Pf87Xt/mkZ/Sbh+3z4mtu61Gt2l4bp9+5nY96UwTuPLE65bBmxD78sijf7KMP3+186wz32zRndVmO6GrZ9hn/uEeI1vT5h+/2toqFwgGt01Ybr9r6Nhx2QVUGkVqA1oPihNnteiWx6+kqxf759C3u1Vzv7LpHy0kYz/+4fn7Bc5HItyOWH5+pmXX9UzF3R4Pn7a1S8RvtlGEjizVT5+yoOrM+yVCVzDc3QybFbp8rcD/fkXhMRh/eUc/bavUDFz9E82cR7AA4GtZZ0ctoHjWRlh7QzK9JHyPijPk/JAU2OHJn8XZWfeq9Aqj5d7jvXmQ+3RyofnWJEbal5m7E1ZW1dPka2hrEcsHPm6K9v30VIeLLngXxN/g3LRUWL5BihfkenKz6xK+Ls5+MvERr3c8hGSugGm3eYb3T5Cit5LC7b53AhtvtijzZd42KVrPOzSy0Ps0i1p58Y5Y1+5lJercpmrT3Rlzv+TuL7NZPaJpOFhfaIgQp+AjNuvb5iUd9P1CfL3Vr5jg6VcYrYxlqs2myr7zpJ2Qq5Bnd8CdWWp/lgg5T1NTd8gfzflg5bPY+9oXG61sdz78uD5mQPQxi0MXfvW3+4lEdq9yqPdqz3afbFHuy+pxy+wdrvggcr5vB1PXyJjoKtdI/oToV0pk67zH2J9e+WT0l7K47T+Q9QXMfe+k6+IfGuC43bSbEfMbLrwNVf+T12lnO/K1f9jmk1/7Rnc2Fz99APCLy0PFBNsux4xjE0e4W6XOdPlzUbXJuTPVfnbv5dyihksm7AFWuVvdH5BlM9WbbZBymmmlJX811qfva+EfweTbUp9ffnctuW/tZ6rWt+hL0Qmw+SYpI5erLd1bHD4Cc1U/Wg6+D8T/i6mlBX/V8Kf1ca13gb7j9pfhgrV/5Kxf32qtR/fyDn0QePvQkfkQl+BsfRxK3xvWGt0nNxi2yOxMkdMTnxai6JEIw19LI597BPHb8DnaR79lc+aN0ay7ayyOu9Zkht9DPS1NkQHjldHF6UIYb+g7Dsc1DdNfOBIUs+/g/280qjfH26KUecPV+PR55d7PItWeDyLnvHwjSoC4n67xkZh3T5pg/b8rcL9xz7ef7lXg1qPkfuE75j0YNncNVh+qVfIemDMxb8NKjOBG22/9FHuMSUjSv+cI39fNaZelPLbujFE/l5qDD0n5TXhY4b9/Wmp/0DKJUq+R/j44Bh7YlSdH+eeir+r8os9f7SMWW3/zQD2Qn9qbkhfUf1jNJH9in8H+0tRhP5SEOwvTe7bbPWDDE0/+GKU6geu37iFdHC5levMVNu+7/nh7R7h3YUyPVVbHi7lU3VtT/7uqm0Pk/K88LZnXyqT+tPY9rZ8F23bl0r9CWx7mz9DPW+2y5T1WeR5cwT+nuwzDqGpfZfttjitffBAM63ff2CFybYY7GwLf2slBmU6qziEQ6U81hymj0OgTCf1LnmIlEvMEfo4BMp0UO+AE6W8h7lLeByCWpNtf+GZYI7F/2cbk9g+tq7tVQzBx1J+Kew3IJn96wipH2UOMmIYZ+L1G+L8u954gzF/R7yBNfbOHayeua72XinPGzyj+N2wzP5uGOo=
*/