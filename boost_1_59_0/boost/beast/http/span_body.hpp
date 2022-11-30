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
    static_assert(
        std::is_trivial<T>::value &&
        std::is_standard_layout<T>::value,
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
HfYQ1u85Ff7vFu59jGEH+JOuTWNJIJ2reZ5CUIIoU48s8lfqCU5u4XmavUWXltCPm9tMlsqsQy0GKKspTqFKWhEGHAuE6zkKpR8WRhqRU8emcjCrwlyv3M8O1w8G5u4L46YZBGF9YDAApvXaIACDbtN27YySBt6v8fIk1ggPZVsZ6mKaDyqQyMwnT/k2TM9n1TEPjAxA+ARk3fxzutdIi63naFhHKaR78QmDBg3KBzgEMAQl3GAx4G7QOWLCP9u0xeNLeraRS9ohFl5woOvExBMv8SZ4I08yQR5ITzeggg34S7B2kbpdz8fhVzLARLrY/WFkz7vB0b+gyQEi0PvDQG+lS74HUe/gFOaQs7CdKvjofgQ+gEUPQpIJgJJQyIsfaNVgF4X4xe/L7nHWlAMQn8KAe9ar2mVeT4UD6DT5FQJsAZxJbPpDYMYo2BiAmwHuomP9ViY+JDHQemiXKN7V4CIuZY5kAVM3nzwYrgbhY2fOfw4uQyjwa6cCnzrrUVeOKLWvJUEEQcLro300Nx8bSQKBWK8VX5tJiylBZi4yMCAdSdcd7jGu+bNgbIoDK1YRZhE5UBFc5+mHFDRQDBFoKtlRms2FV3rd9WiJ+pVs7zQRLJwd5Vki3BHHtRQqChCJLfQ/MGfGKi2+wCq9PZxmYPPyE4ra2mHmUhpBM4TBxiz7tRbD8SDTaWahHxIv2DmI7CXlptkLJLJ09LF3xEtMhOJLWG0c8oMkFJegxdHn8cZYNQRrgYeX20hl8MEdfMVRkUWTBl2t2KVrCLdR2UBgcjVrYDAuWdbwQCB8F5QWzn0HvAUurFfn91PYRykGMEbe0SM+HwMGlIQKmojEJHU9QCb1MhA44LkVkArHhIy4CicR4DeZudXxigHQMaaee8poKAwjZGthGDI4VomAbb+FBcMTpf5COORPFggePZuzUwuqU1ifpu4bSlP6Csi26uWTJM53Jz+RUe2FK2ubB01GsjVeAyHDJFDIbVW2eKFmtLmCh0QwDLAe97i4sCefaBu/LWgU8DXOJxPSu2TaWh0ECIn/mBJAZDzrXoOKiGmlunWWnR57mugJvnCg2CZRZpAfeGZr7fIdr/Y0+WY41Lf5s8gDTn9KC4GL+bksC4yATXqjRp4LuIe5b7k3R2cfhVr7hkXwx/gzzN9ygYV6ovTe+JxHhLcgN5P/m1MoGBxbtpXakqU4Cuk6kqgmVg7g0fBvbXhptMjiQUc4bIMgVKLJPPHjX1/ECfNPyqlUkxP1UaweTTYwds84l+WxrdQszYW8/ueCtJfEKsix9o4rN4TwoP3OSi3M04GP0E7I7hbXwDH5a8/Ng7yI1p5+9FFGd2pzxqD0H6ASZCxLFEFQRT9iIJleOSH2AUgWMCHGtzchSDyfpARkyUmX5LCBXdgcJ6fuie7vTceWmTN951YP9yz37KB7uqkelcOx0yWadctmssmE2Y9R7pOyAIwTVcH2g46TLBjVEHlAwpLhnlvOQa1pqd8MNPGMgu0vNmKBWv0s5IsWcs9wFAoldBrwcZBToKlmo/bT4HXyuC+R8ZXL9a9Zrw3gq6dpB/hG4LuR28f3p+dW8xtiuszwu7Yub2yjRT6yMsXY9FULv2BePrBPQ/RlKVwV8Bak8cX5RoD+6+utxwc94GG7AFnOLAglTQOQqEWw98prU9PXULqFN/wT+VPnaicXz7jfwCxzmFV4MyCU4PhyS+AkV44CvT8i7oactmQkpIfTQV9Dk8nJ5KRkZRAFFVVVJVBJFtI5z1TSgACmf+PxT73/0twcnPEmHISVx0qEIiI7u3ujdAK/0BJYU+mDPzyQWS/Tg/BzwdAkJlq3+/dOFOQ4MCqwDAThthDPgnCe01l/iDinbaaDAuU/RP9YA3WZdMReutSIoIDGKY1yGo2KkSEyKSYChbyKLD4l9J/X6LT9UCeA8xCNxro6uqPO0I4OjigBNYZ5ysn8CROYkIBgU+yls8J3/+IE2cH20dQnBCOB6IvjcMEosY+EkSBYCsDLe0FUQJCIYsaMqajfXiK7QgZyDI4QPBg0R8xQbBVHRLtE0+Lt1ZjH+jgV5XuU8MRi3StjFHYPNj0BS3VZWVlVeXl4GUEzmMgcAbOeTnIA4nOQfz3Rjc3ZAMyn6EhBFssFmHMki/Y7DD3jakfGGJo/WFUL0bwja789LVjCDgCVFTU1M+devQc9nVFW+rpiBb0DhmZKmpa2H56acZquP21Hz+EoBcr/0uD4gGM3KntI0Lc4oFJYstPS2Lq7uqjQh/cJVAUAfTKmBuB/VoADzxr7Q8Wd6YqXP6be6H/99TwIwHMq8tHOBldBimCaVFpVVTcIwKiAue5CJYAgpSApo9fV5LDY1axapXuYSuesn1mmMKVuShuGZLOp16UMGgULKUaXzr+joS8vLx2xszjqhiJJve4F+xny3QEwXkN12alRgKZpUvxgz4Pd4xIcMrKhUIowUJQCKKo5WIRpG5iY+EhYiFjB8Uvg3JUT7apasT6Lpmt1w2I0saplxmmlU29i9k0TJmLGersLp0b3urg+iZsCsnjrTf1XLP0dQnkyKuuzpNnOQQIpCWIoscI6AvwQgzsyfj325X/3AmuIKgd8Sa2SDAwWgWAa2vgbUqeZNJ1WgDg0hzVLR0NDQ1lxcXEn9gBsEnEzytEGTJzW6t3McO4cqPO0FXUqhOE66MUpztV2JJg6fWgRhisQRFOsm4MCAaZehRo2o2RyMq1qT+MwEi3rrERPH6AoRmB7QGiwAWk+wAWsqODSt0RFG0gzu/r/QSUEZblW50aECTOkikX37jMjHEyEPAMzwS8+LTTmj5twTSKGGzrKgNCwEFho5E0/tJNOjuZnHzJaNKWUStEa6tEZ4vGhFiSsmnW3elEuh4PT2INXGZjjLaSxvk2Y5EAsEgfqA959+WEko9PeiAYUBzaaUzB16tRxGE2MQv3QkzOQcf9nQJH1DlKKgMqlNFMTEKwKEmtXYDHXGqi08OYk8QV9JzqfkwZC6JB/BsMXyf6EAxR20rEtovbBZ92PABLxvW/cS6EjcCZQMmXavLlveINB+0E4SriajUO7iihIT0TVjqg4BAOVQxUkpAGVxPqQfc2GJc3YCCtYqB70Oq9iP2bxrCkorjGqeXCVY/0G3GV7rxDAmIb28y86+KmoGcQ1Q27EgEmbdUKOEDSe8RNjZh0NxcRMUnFOAbGhADqySb35cW7ig/af2gWznElP5vmhVPo8Y0IXEb22YuEOFudGbEshPdQ5qUAKTrlZ7QboDyKOsRi1WxC0ho0rDxZqs6BbnG1z5s2wdThTCbjyQNBaDirVryWogBHu86zyMfiBqDpEhg+fPk7i5InD/mAhTU+AobOQUHOrmmKAH8W1znXT8ZrrFophvelem8Z0AzArRrj++QxIe+wucdUOZRSmPFUZxvaDRQ2OYwfs7I9g/Hh7Pku+Kben0LxEkBDYiUCsm7HMdZExtiGrGNEH+UkkFFTzIz86T3M77muXYqHefPlyJmZUYJS3Hc52K9rAyE4xH+J3hHx1GRiZCDzHKQ2plhg+91gz5TTP8pdHpMlDBWA6lQz6XHyQEKQERjZ6WGPyUeqJvpv2Px80bU+8ZllWvWE53ttUFPT1CU8TCdy7EpZAOTOvijLKNQ7gMecoP0MREji0M7FRglGncvBupvrepaZlX8NMdH5yIAD9Bi5VGUlba0eS33gFTqgIkDVeWUqIeJ0F/hAC3P0gKx58KVLTuLkZtK+XQabNxXvCN5DXbf9KRgMmc/xXAXd+CQ1D7VoAACz/065TyuXMmVMRzzEqw0aMgoTKAaG03Fn9uXvbWsxq4x6YWZ7nYKIYKaqgW9WISEoQOJ3+fkll1a9A6cbl7SDtoFGMqOL1H0DUnFewmfrXkQKeQWbIT1C5ICFZBgqXdHwOcuYr763EQp43HH+KFUf+ePMVw82vze++0uUtdWezq05gj6xfSbpZ4iLog+EjPIAjm9bTCdmZIhiICSI8YuNjowKjzd8Uba88YFpeHmXKYcTt4FEmpzEBeR4mUvVlBnEmMQFAykgv9rSa1d2lRS3dRpLD0X0rieK2DnOpDPpoF6r6xQ3PBjbNfPC7DvAWsDimByTrmMNud+MPeffA5iS5QGUBsldtmrijpeGvg+a3PtaStr0KhtHAUlPEDdUmsZhBInFB8WfR9En87UqAYMFkzFLoSUk9GZgb9QHWC7PmjLPZ2V6oz6/1xoGm61WSzZ0uTOAwwTJTBSRcm3Yhpqos2kMsqsoyONrumiTbIDGCRNuxUIZPem9pNUXsIFCAqm6aEd4wgl8HQLIJ4Jshk0VdjoOmayw7zP3wHpRrDtT5IJqz8b3bFt0BMAx3tVZsaEmawBky0RcIxv5Nm02rDSzDtluqsmd4DQZI3NGSDMtE1zzOYlO8e64b+TJw89PgkVkTBhQhWuV7R9vMT28EFpMtm+DM7X7NN4VuVuRw3ekc7HljJq0OYNRlG1hAgkPmmcSUwQI5RmimAwVSSGUaaw1BQ/tZig8R5bVIc1uim3WjaCNEedHs+K0VoJwCBn2ecXNlVewg9EoLiSo9VnHqZcAJ72s3LmfetV8tcn1A0p3BxIVxsn7+NK0DgjgRsVGeCF9hMMW6ASYfAOd0JVPH7mVHVHc2nfR/2wDQ2urDqb1TDS5dYvY+dqrf7V1cbqsbGsx4+51ACwv9RG2NiQ8cED1OQGGKh9Xc58ix/gmPqRWtRXcnzHCOxtMyLcGU7uivJ+YE8Q1p2AOabme0LX6vGvLab64xpbtspyYe82lTduHJpuHMhcP/Iq2Sdo47mjAg2C55/fr5Uy713bJ/X6FFH3NO3r0xAW064e6Np/mQ7BOCUTQ08UI2qopVoocDE/pVLvqCAEOv0hJJ4dPzzkJmx2V2WnJkKDMVc/hkCFLYcCJVS2PmqyaRml1TSrImb8JFHqRCjP8DygAsNduKkjgzr3XsziOtUC9/p5lG2ovu2ywi5bucmIIy7+rjUKoMbeE37HlYiHu2ehaUYvFtjN1ItxsYuq+FYz5hJklGRGgIhrPZMIF6UtuacqO8U1b5pAIEIyHigprWREzP2wuZ/QS23Jy/QqOAqsgAuhguCYfPBFCgG8s5fU3rKYY8sfuWi5oFoDxhqwCWKnQQbB4kv1xM5st+2C6fvEKVUmBApYkURa7QDsceXwMo9xFP8gufIfrhFKId4Qi7ZECocCpFHkZWHkCsn/uRYfPG7WH9+g0yVChGNlDS9WpZdJz672kLg9ab9VEeiOz0m7Np5ksVlDO/ii6+29BehaZgI4SjYJEmc+kfiHFj1Y4r9oBl/nQjw3fnpqEbJ9t0QkcHbRkEGuE1lRMDCRQF6NSoNXQT+s1DsHLZEXePgvgoEUGbV4hrAqD+A7Jbx9n+VHZaMDQUnYNEblc653ND3dLXf455hnlB5ljvr7h5mL/M6UUQTaqznyp5vNYxAw3Ajt+X8MHGQo6jt3mug6aqjoPmhPE5/DVZirt4ydDbXO2bDSOHr6WPI4eNeAkTcdvoV+mpp2aqScBlBjhjCObcw2Z9pDXw5e/uocYSSjhqBfyGwwb/+Rn4nvut+wrPf4axvs7xczoojaKQKuOtkoUEalfvnZ5VjNqASmidclrTW5cU9g5lEsaGpTUajmAiABNdMhGm6MSmrpKUp+ZRDF4ch+1xXAVtBcyjtm6ZNPAmwvZSV6+3Wg07q/h83KdZL+CBOR/nBvqSntR1aVobz7j3HPGMa9/oIE8S1IWIBfSMGA2HppLJm7s3VnyEgYRAIJvv5C8dKajZocx/ZiG2aw8BRRe72icv8v/7/k+O5nN419q0bYzvAiYid9jYrlWiG8CM4V+W4WojvQeiNSYUnt+41kfmSaquM1CMAVUfeUdCZw4CsUn2+D2NuzeeR5LtSFi5uM1Jv9/GsOCv4qFmIfMOk1y8XtdPYSJDMEcQ7bOuPrGCa/1sAMInWPDsytLa2k1G0WUSIDDlYqE3lvimjVJMTap1l29KHtzyr26a5b5a26XffCWB9fc/u8826UU6ehOB/kYDqtxqbIwsg6Oz0+oN6Cdq159ny6ysR2bc0dd37/Y0fAsFEFwQ3+TixaPnorRgD+xjyHHWCx35ssj81mq5+H2u7iwO8zkVwwhqiAhg4JhrwcGzpzUER4wJwFDrfmQEeN29hceNM8v3VW0/3Qn5ZdMJV53Bh+fc6E3jq416Sq6W8Rma0ydlmg885+mN4+gwSmplQeK6xG6zjucOWq6s2Y5XRzQamL0BJKJoseLls9gh4q0pA7d91lEPMlyCn+BRNICBdaefoCB6/KUakwixYt4321KCwUpMIY0mU8R4utiDzdiXHrNGk8rRUSmqjn3+AfJfXCcXiqO6kAy4uU+DNEN66uFIFV8LvIZA0vHry9xjx1w+iC2uPYu5baxZIWwAP+z6664ToVDP8iEKdKVP3HoLeOUcH3i9iaSjKhOpzGviDtCYxgodpcqTgRf6yhu+fFS4nDhpymwq/2NfL15d+RhT/8PPGtl40HXemamFO0xy3btcoITxffMfuUPhlmzRVyx2nfNWoplTDyPjLYaxxMalV62KgxeZra+PV1nVH5v2LknhPsHDwWl8HeB4o7nLlnlOmEKbBxzgAA4x6OiV6JF13/YtXEVOHA4hZdl/CSoE6+fBrbf3YuSRB5tiCG3X0xCFP5kDhbg0Xx3N9AE9sN0ShCgsgpHdD55kJhYi6xhdEDNaMFq7NuOTrDsqF8yLn316ZykXGxzVVYmBSSYblVAZhbBfxVAMmK//iECCr+hFALywk5F3Gi67MGltpMjljHcBQLCbvr/acvV6DjD0mzYZSI7eEuIqTdeRys17tzA2iglC8iCVnFDT3UyVOlyzG4h3Y5ZFD6t4/V9MK+MWGy71anttbF2uqElIKCJXk03FBtv3c14IdqVAA9KgB1dCCxG+dNPpI/BDvd6BkcVLspcVLDVoBkPXcFFvyndeKaZi6mRS1+uisubjoIk3abF2S3R65AaHy4LF9cjmWxRiBgBCnSuYhCr9DvPHZXDrLctSz6pTP1WlQIVD8xNkWfhmi4JZo30vL344HoTTUOAQwMSvxh7LSpxGL9RjIOE1uuYxDsFBHesD2p7OhmLmRM5eZZu/MDK56USey5SeKl2vxomtd5g/jKT+c6Lko4UJorPXwvAydS3hVEsFldBp+49x+uhjXONj+/fD1jIDjKeiSTMmjxouea8Moe1InN+zVEWFfnBAppNBHQFIMK2yEJ0rZW+r4DCQDSTVDmp9vhojjMglyc1Vjjv9DMt17WUydHM5OfKEE2u6h9JvdFo1QvIeHOfbuGcMqxZcXw3cqnx6W4d1+ogH0bJr8DW/+mpxR4GABfszn3V3oD/lN7VtgH6loAUHKKCDeIA9KC14RoDobtR52rgViqjkwFovU2P5pKHx6qD2d8TjoGXET37mfVCdbPKmrEGlEf0cGDCfc+2Usk6sCxzEDZwKPuaBkLvf+GzsO63vYqqWoNww3QljWA7NQTzhk1F6gFGUvAuBCgrQYEaMdMATpGn1osqvx4lRcSOJ9tmpoUoOr94SO/S3fSdsgwpcxc6c5ZoMazWBSbiN4IXJkSXDpJ1zTMHNh7ZvqBhQRt+bHaLdLfanu2Hn
*/