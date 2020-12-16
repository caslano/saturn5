//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_STRING_BODY_HPP
#define BOOST_BEAST_HTTP_STRING_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/core/buffers_range.hpp>
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

/** A <em>Body</em> using `std::basic_string`

    This body uses `std::basic_string` as a memory-based container
    for holding message payloads. Messages using this body type
    may be serialized and parsed.
*/
template<
    class CharT,
    class Traits = std::char_traits<CharT>,
    class Allocator = std::allocator<CharT>>
struct basic_string_body
{
private:
    static_assert(
        std::is_integral<CharT>::value &&
            sizeof(CharT) == 1,
        "CharT requirements not met");

public:
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type =
        std::basic_string<CharT, Traits, Allocator>;

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
            auto const extra = buffer_bytes(buffers);
            auto const size = body_.size();
            if (extra > body_.max_size() - size)
            {
                ec = error::buffer_overflow;
                return 0;
            }

            body_.resize(size + extra);
            ec = {};
            CharT* dest = &body_[size];
            for(auto b : beast::buffers_range_ref(buffers))
            {
                Traits::copy(dest, static_cast<
                    CharT const*>(b.data()), b.size());
                dest += b.size();
            }
            return extra;
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

/// A <em>Body</em> using `std::string`
using string_body = basic_string_body<char>;

} // http
} // beast
} // boost

#endif

/* string_body.hpp
ClaG70p+6zSZ+5Z58zxE9qpUB+aceU1gS9gatoJtYGt4E0yAA2F7OA52hNNgF7gEdocbYU94APaGL8BB8CM4AH4u7q/hEPhvOBRqOvcXGuUkL5n3pd6kvsrAWVLOcsSLgpVgNKwMY2AEbAojYTysCjvCKNgF1oAjYE04HtaBC2BduBjWh/mwAXwINoSPwOukXAmazHfKvclz29vxQd1xP3bBKPgorAcfg53g41DWu5X5PepS8nFe73YZ8cLgChgJV8Lq8AHYAK6BceJuo9ySrzX/pK5Z5VvHyBcax/VSnrawGewAW8OOsAvsDDNhVzgO9oSzYC84B/aG8+ECuAYuhvfDu+B+2B8ehoPhC3AYfB0Oh3+HifAfcAR8F46En8EU+AVMhT/ATFhUpw3A4jAXloYTYGU4EcbASbAZnAxbwynwBjgV3ginwwFwBkyCd8BRcBYcB++E0+AceAecC++E8+BCyHXJXpoy9wJzkDy3vTTvkb00V8pztwqGww2wJlwNY+AaGAfXwpvg/XAwXAfT4ANwjEone/8iwXLeFXLeUjBXzpvHv1A4EzaEs2ATOAe2gnNhWzgPdoXz5bwLYApcCFPhMjgOLoZT4F3wTuUv6+ia8wsyB5KHGNcVI+1qk5Rjs1zvI7Au3Arrw+9hO7gddoI7YH+4C06Eu+FsuBcugPvgIvgU3AkPwEPwWfgCPALfhi/BL+BR+BV8Rcr7GvwWnoA/SP9YQfaSDYfvwSrwA1gTfghj4WewGfwctoNfw85wN+wNL8Kb4XcwFV6Ck+D3cDb8J1wGz8EV8FEoz6WMndW43+O5/AmvCKjLHrM2WBO2gtfDANgOFoG9YFHYFwbC8bAkXAfLwG0wGD4Ky8KnYQg8DsvBkzAcvgcrwU9gVXgRRsGfYTVYxLjH8tzVgYhWD8bD+rANjIFtYQPYHl4He8BYOBjGwWTYHI6FLeAE2BJST+r68mF5uBFWgHtgKNwHK8KnYSP4ImwMX4HF5bnUzPGojGXzEKO/vCDPx0fEawLPST/3hfSXX0p//BXsA8/D4fAb6fe+lf7uO6nXS/AhcW8T915xHxT3Gfg9PAt/hNV03iNhHPwF9oGazdEP6XAEtMOxMADeAYvBeTAILocl4Epx3w9Lw62wDNwOg+E36nmRMQyMl3oor54/x/GEtKeDMAYegrHwWdgCPgdvhIdhT/gCvAW+CKfB1+Bd8HW4Hh6HO+Eb8DH4d3gO/gPadJ43aT8nYSl4CpaH70m9vA9rwNNwt42xQu3AQn+/5PrdkvdvlXx/p0SaBoX/NknW7JbvkDy/QZoLtyDyzZHP741cvzUqxJ6+sb6/K9qI+P6WiHCX74dcvx1qSj27fT8k3w45fzPkul54LuL6jdCVvw+Sb4PkuyC3b4F+xXdA3r77WYJ05nouu/444W7f+Mj3PYTJdz1LDDfxliBbkIPIW8h5JLgOe+giCcggJAuZi6yr4//+x3/4D//hP/yH//Af/sN/+I+/0vEH2f+PuRbr/5v2/8HO9v9kbdr/149iLlosSKJ82P9rOwvs/0laKLt/0y42zebdLnbdDpXnmJRC2MUS93J2sYS72sXu23Flu9jHieNmFyv5+LaLfWbHn2cX213WbYxRdrFQ7GKDt0o9+raLlThxlh1cB+X+Tr9DK+mrTiVNY5Um1LgQ5f5Bn6JV8GX3ShpXu9cE5f5JX6QV8Wnn2krFsdnmmnauVj71RDftZOcjeudeKvycPl2zu9qxSpzy8HoV5xfKW8mnveogFeeMPlnTnc6VwskK7nnWNocdeUfuOVm42Nyge8Z2Vf1t2a3Og15sWlW6iPDCtJUgA9oW47xO7rm4TZvWtG2e9qs3bPM=
*/