/*!
@file
Defines `boost::hana::transform`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TRANSFORM_HPP
#define BOOST_HANA_TRANSFORM_HPP

#include <boost/hana/fwd/transform.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/fwd/adjust_if.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr auto transform_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Transform = BOOST_HANA_DISPATCH_IF(transform_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::transform(xs, f) requires 'xs' to be a Functor");
    #endif

        return Transform::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct transform_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            return hana::adjust_if(static_cast<Xs&&>(xs),
                                   hana::always(hana::true_c),
                                   static_cast<F&&>(f));
        }
    };

    template <typename S>
    struct transform_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <typename F>
        struct transformer {
            F f;
            template <typename ...Xs>
            constexpr auto operator()(Xs&& ...xs) const {
                return hana::make<S>((*f)(static_cast<Xs&&>(xs))...);
            }
        };
        //! @endcond

        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            // We use a pointer to workaround a Clang 3.5 ICE
            return hana::unpack(static_cast<Xs&&>(xs),
                                transformer<decltype(&f)>{&f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TRANSFORM_HPP

/* transform.hpp
qR7LdN31g2xkxLeblv7E/O6fPrHrG6tk08q4d5kdoxcQGaf7eNahsqJlTa9aLWs+DVpcPxVtVOhPVugJgG2N8ZLmrN2NnjooDL9B+BrYx8pcqB+kemTNLFewxahaihOEKtKllKhW4/r+WtSnZn7w1gxdy7aWiRBeTlICRF9LWBhCECX1tTzcnPSPcr0c2p7q2Y9H83luUWpm6R/wHqpHVqy2stJ1nZzWtpJZJXhWytH3/Hw2JtCxMEGROMOvFHoEa6UR1tiwhsTtJlzBR+C6i2APXz2rzkvc3i26N6pZJ1RV906Arlir0UpOnBfiWWl3b4RLIvkit8o6daK2blB9Puee50i00RyY6zY7RidDtoE2FqrrsoJhpPvKsfF8v3u0clf3toLfNEpa6QXLwerIj2tDUVfFXKOdlUaN7yFWGN2jQueBCuy9UenSV+O7VNdFaLPtvTQsDoI8P6B/C+UVisnW2tq2fSg37vv2d8Ohf1qFV4QjT7yMIHkwb79NdNWCib43uuPdujbszw+ScQEm/VnOoBYx7dDvY5/qe5w2vKm9ZiHlYLnOn1A+NTDeetn0tl8tN7kDzUK4PZziQvedveIg7EFttk1tl1jPSjZD3Rubx0zej+NYKR1Sg+G2yHf9h6JukjlQJ2vPoW4EkzAu9zk/6PS7YHimfAatmw2xvK1Sus2JQUHlaTo27B6FCTJs/wjwLvqQUj2SM9m1Rg2tznq2ig0y9uDhblZM/JI/WOiqmQiHTNt44r9PE7GS/dZjxn34Dlti7BXtc8xxp73gJo9FGL7w3aMFCOqT0wbMYZPLln5Wzyzuhet26GrLmRrP+6UP2u1LXu5k41SdPJUmvHelvBe19d56AAFfOiIRm9h9KK+oWF+3vfe9gjmsHEJwsBu3XqFTcoqi1TMNo/q4ZENlXN92ME/Hcbjmz2NxC0jbsF20wYdto+sHdh4Su05jeF80KdMOLbS4gxy5uwtix5sfT8rieb80lXfWiK6x6U0souj66j4AfVYnOupa1INXNcuDNPus/5s6fHQi74w2Q9hz12SbvbYSBF96qqMXsm2EZ3l5jIvhGgU0NzPVoSTTXdVUJgCtwmp//VkY2Ou+/5emwIIyh/6zJngM1lfBnyz4pZ2GD37VpSyZv7BiOK50ocswIUUthe3yXBCddKFypYlqhht03GcVejqmpQourENp7wJlq+auU7qv+WChp2emrVrRtf+3nm8VejRrhK46L6r/1K5sGIXuxjPoX6ke3rBOVINoGlXu++TBWYwCwVj0U/TjfHbpY68r1dZtJ0v5Gb5znK5D886Xe+nLVM/AeG86rlTDlmH0cVWNpxbRlnYMTWW5ZZ53bVO5Ie4V866QVOcB0o9pW69/2mOOY8LWx67gyRwW7XJMGXjb0jbkbA5gg88yIT2wddtwsoRfE03BsMH9Z6FHMlFV1gz8f1SzUV+Xv9Gyfzx3WvdtxU7hTAWvmOYfsXg/SGWe0HHrBsP5KLI42d1LAniW+HXRjz0zva183zsW7Cp5QxY9KOk6h3NBjd/vc8p4BW6ldpUfML8OvJSjmHExvVc0veDM8jSb3y3VJTjTqtba1DWcsdLs9piUvvxkd3aKZnCa3qxYZ15Z6GuZaUxvdMvX5CCy4Jm3txtWny3fVQL6jMwHHy30dIzrurO8HthEigCOpO0gVJDi7lI9UrG27ipXWzE9v6G+4hhH/KmfW94RdFo2vdQ89/n5MbzwcI5GPQSPleK7UD1SsrYVlWlUzxb/7vyWB8f8mM5PJ4UezqSoWq4EZ1WallTc5GB64nJHxjbQb5HqsayumiacvHDcR/eFccwc5nH/WSrzeN9rF3Y9o8jJGeJQVbg=
*/