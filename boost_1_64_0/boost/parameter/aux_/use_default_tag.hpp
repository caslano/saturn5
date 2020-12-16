// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_USE_DEFAULT_TAG_HPP
#define BOOST_PARAMETER_USE_DEFAULT_TAG_HPP

#include <boost/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct use_default_tag
    {
        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(use_default_tag(), {})

        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(
            use_default_tag(use_default_tag const&), {}
        )

        inline BOOST_CONSTEXPR use_default_tag operator()() const
        {
            return *this;
        }
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* use_default_tag.hpp
7+Udg+1zCKNbmRA3XfuEVK46D1f7zXNiUq7+pt5VmU325nr+JOd6O856kDh1kziNVX5keX1oTycsFxEWs/2uULoxeh7IIqXrj3JrC/tJXcgTnYWeO9gfrY3nVnKhre8H7M/Rz/Ouzyd1xnSbuQByXne9uv6L92lCYu9zeki4H1bupvracELqdm9f9u9JYC+vrva+TsdxwvBAPvWQMG1Vdm/33eG5l/WAvZjx14d9sNqEhkWnM/1QbUNdfWmJdrNU6UTLtU4bfc53ofLDFxWmn9JtTD562Iuyzd1ZaZ8zNF/ST55f+JM2UOLyropbF10G5ir993xPeQd4XcqA3pt+SaDsKnd7Y099uqyu1X36fnW/hL1nRui5jeMzVZozPyNK7Xm+nbZ2zXDpc6Ku8sfxGXCePy7atb8R/S3Dpb9p29jk6G9Eh2t03lZ94roz7e8Jdp2jpr9t18mculC//Jlm37auOJxfmegkB/xaEs6dhehMS1Y6l1vvzNL3is61pjveddepvnf4afpesbPdCt/mcOE7gM6fDZ3kdU87x9NTROekqRO/vo0/qqPHqVfLdXeZhzKecE9PxhzSd9t+2/p34QxbHz9TzGbBHyQF5hQew7wzYjBJnhEyMc+Vfj6hhW/oEzP1N/Nw/b59jrcy85vvR9Ke2r+jHx0Z8GA90hZZh9xg9P1Zur9QPQUPAJmB7kJd2/sMXb+nKjtD3Pv+rPD9RBKcoe4PcO//syLs/7Oc/b9VN2vUvSxPT9u8wK3KLMrjaCf0t+4F3Mc1lV5G2TpM37pkJGlmlJv2y+1jCc73eJ0m92YFnwt0o7r26fKKm2qTsz+ps7aWhHyPlrqgy0pr5wa4lQnn84S9PPhHyZxRcXSQlIfm0PKQZSsPLc6raHbPf/fx0gjzW7spaTQ7mbY1qeU5T583jcxnrGZJoxrEi1QjK7tRj0cEp1Exq55q1c86/RxBvHU/NErpx7mmF27p74QJ+LcNUe1Vm4FqYmiYeXOqXalFLkloed6CpIM+u8t+5seGMQHF+6NIJ/h9+Clx3OOIIxMocUfHDSPrPb3tSEP3oqil9PHne2PcvxFJPMUNPWerm/Tlr6n710f1RvsG5GpvdNDzSoq0H32yDb2fs4fhGEwz5dmMnncU5rxPj+C/G+mFH0DMZ7G7Vfie8S0i7Qy/+srcpoPCS5BPk1SZUjyCmGe4jeikfmuZkxyQc0SqJf3jWmjPF2Y750BJfkha2uezbhkbsHxKyt0nUu4KxwTniXyjcy1zpUr3QxkDEru42M9z0J4vYu4NfjYUO9eoey95JpBuHbj+WVKgzC3opNLMLvRtAZmbrESZ/SoJtqItk/SQaz3WF1Rec86UPfAkbe5C7uhmpFlw2vDxw1nW9HzunUr3ejVP96tIN+IXE1IuIgu7vU3dMC5wY7WEbRXyalfcOjM4bHUskyym2eDQSCYnBOWfnku8Ttkp9czCx3yP+zsZ7jrbT12fGtS9OjUH6wKkzH0uFm6E5L8ep9qg7uWTToP0M/Q9ymwM8/GSdNs0rxVjF/Y8jgvT7h7MkX3KkVjkPuTGNNwc50zHenlWCR4bTZE06Kz0v+fpw78bECnX4k5ve1pi5tpv6fzoZtyntJ1BSL+CuKSldkM/IzjeQSca94nrYnx06eewH/65pljdm0urNsB1Xvkkdf8yZiyf4fqckwgzxunnHPWOci3lNT1Hns2jB/vbxvq9g3g0d30uF/2pOeZzea5z3rfWKc8xn8srrP4rwuecSMe8Qp995RuIpLm9PBVOCDg4TxyeK+WpObQ8ybNOy/NHm8e14jnHvVzofDmh7iejG+NaLsS+7Z27REJpPcO2Oytwzu5QQ48=
*/