//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_EMPTY_BODY_HPP
#define BOOST_BEAST_HTTP_EMPTY_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace http {

/** An empty <em>Body</em>

    This body is used to represent messages which do not have a
    message body. If this body is used with a parser, and the
    parser encounters octets corresponding to a message body,
    the parser will fail with the error @ref http::unexpected_body.

    The Content-Length of this body is always 0.
*/
struct empty_body
{
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    struct value_type
    {
    };

    /** Returns the payload size of the body

        When this body is used with @ref message::prepare_payload,
        the Content-Length will be set to the payload size, and
        any chunked Transfer-Encoding will be removed.
    */
    static
    std::uint64_t
    size(value_type)
    {
        return 0;
    }

    /** The algorithm for parsing the body

        Meets the requirements of <em>BodyReader</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using reader = __implementation_defined__;
#else
    struct reader
    {
        template<bool isRequest, class Fields>
        explicit
        reader(header<isRequest, Fields>&, value_type&)
        {
        }

        void
        init(boost::optional<std::uint64_t> const&, error_code& ec)
        {
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const&,
            error_code& ec)
        {
            ec = error::unexpected_body;
            return 0;
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
    struct writer
    {
        using const_buffers_type =
            net::const_buffer;

        template<bool isRequest, class Fields>
        explicit
        writer(header<isRequest, Fields> const&, value_type const&)
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
            return boost::none;
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif

/* empty_body.hpp
fFX18B3h4Fvsk6/GJ98Kn3wrffKt9cm3wSefkarnO9LBl+STL8MnX7ZPvkKffCU++Up98JUYnG8DriOfM4bhO+Zu+55rQP0InAX8mTmTfgEuAf7GnGwm9VYZnP/hXFcVc3WfRr2DwNcPuBMwlznGRgOHAvdgrrEpzC02DTgSuJg5xJYwh9gPwN2ALaB/LLA1sBi4PXAcsBy4BzAA3JvnVQRK4nnV8DzjuaYkNsmh1hfYD9gfmA0cCswBngrMBZ4PzHfoy07W68ukvs7U15X6ulFfD+rrqdqD30XALzzaYz/erwnAAuD+QKtuIvBC4CTgA8AK4FPAyUov36+BZ3rojQNfD2A8sA8wEbgTcBvgzsDtgPIOCJRvFCDXWOL7Ht5pqVetscRcfd2Zo683c/ONYm6+McB3gVOZoy/AtZvO5VpU1Vxz6kauOXUn8CvgY1ybivef7x54z/K4/+1wnjsC2wPzgKm8nu2BxwDT2Q47ADNiYKdGvMAiUC1oDWgzqENMojEENBE0Lwb1oNoY1MegHtShGepBE0HzQItAtaA1oM3NEn3HvDjjXdaDOsQmMs5FxbVoY1rGM5ZlE9AZs7IENHtigopVebMuRkViU/JwjNCYlEKQMw7lBetvxpusfCNW4kxUfIk7tiQ0rkTFkpSAVOyId8yIihEpjhAXMvuABIkBKca5B0ALQbWgtaDYuEQjC1QMCoAWgmpBa0Gx8agDFYMCoIWgWtBaUGwC6kDFoABoIWg5aA3ISEw0uoJGJkZjSf5k70zgqyjOAL6bBJJAgBBDCOFKuMGACSCgIIRDoFwiRUVFkkgCCSYkknCoVGM90aCxYuuJ8UDRooWKivVorFQRKaIioqLGq6IiRkVFpdL/zvt22X3vTfIC2PbX31t+H//Mzjffzuwcb3dmdiZ8hI/wET7CR/gIH+EjfISPKGTOLz3//9w51sz/I5r3b6/Xl9Xdmnd97hxZb885Xy3nZa0857zRQ87TUe/Wz5Hzsv6dmred7toXMM/UzJtr6cwJ80UixLlytt2nNHazXHYlEY2ymxihmSPnsUtiGxnfIo3dHLddbm6odu21hwzNOn9Vscqu796GsK8P+p51/p7BrV3nT/Td86iexK1d50/03fOoNii3fp2/R5W/rPMn4XXr/K1L9HeHNuZ1dOa7Ba4LFqNZ529bM5UndrlscLwLfc8afz82a3iNP8J41vj7vlnDa/wRxrPG375mDa/xt7dZwBp/Yke/xt/PzYKv8fd5s/rX+GvdvP41/lYn/m+u8bdFs8afESflwGpHQqib6HvW+OuFW7vGn+i756p2j/Ou8XeNcuvX+OsS51njT+zJGn9OeP0af53jPPOVJLx+jb/MOP0af2sS/5NzFw7V5f6Sh0Nig6/tluq0r/XsRyXlfnise103Catf1w1/77puQ3Fr13VT+qGt6yZ62nXdHg/xXh/tdd3s+pLVPPh6ituc+lIyJ5T6gr5nbvd+5d6rbzP96su3oq9tL+O8c7u/Vm79eopfij2pDxJev55i2xYNr6d4bQv9eorrpT30nvvfX08xvL7f/8b6fqvUXIrXfvzyXuPZx7c8OmJPQnL8zG/+/9f3y2ipXzevo6yb1x5Gi9sOl3WY4aYeZricwwxXFSvr+2nCDZZw74lbxkx5rtOs7yd6SRKuvbhHinuLuN8U97t+8THiNOv7id4gCXeNX7jUWP06fWmyTl8XeKI674Sj3dWsCyj2M+V6P1tuWd+vICZGre9XAW9G1sbEhNf3O8z1/cJr+3nHcDfFxIS0vt9O9PZZurExRjoyHslDLkeqkadiw2Oy4SN8hI/wET7CR/gIH+EjfISP8PGfOqKQC3/p8f8=
*/