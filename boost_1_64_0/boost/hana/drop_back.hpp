/*!
@file
Defines `boost::hana::drop_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_BACK_HPP
#define BOOST_HANA_DROP_BACK_HPP

#include <boost/hana/fwd/drop_back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_back_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using DropBack = BOOST_HANA_DISPATCH_IF(drop_back_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::drop_back(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_back(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::drop_back(xs, n) requires 'n' to be non-negative");

        return DropBack::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_back_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_c<1>);
    }
    //! @endcond

    template <typename S, bool condition>
    struct drop_back_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...n>
        static constexpr auto drop_back_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_back_helper(static_cast<Xs&&>(xs),
                                    std::make_index_sequence<(n > len ? 0 : len - n)>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_BACK_HPP

/* drop_back.hpp
fudXXe84htkllKXn2zkp33F+zXWIY3ggMXT5IIYpnA8jhHzN/H8YTfUyOU+kb34e0S/90i/90u/v8Rv/Hox/8rV7Z/xumt10BL8HU6uffun37/Yr49/Sz578Tn9qSmaO/QapVL9DhBBCSBp8ev4f/3cFXt70H1z/T9+fHi/fIPP6t+Lxe3ifMsc3vydSrZ++f61vQsgb9u4l1oUojuP4v1yPiAgWIuLRRRMiuaPXo0RIvENCIoiIVKLtnNZE22k6U8rKStiJlaWlJTuJjeVdWoqVpYWFhAUW4syco6ZFddSExfeTVGt+5/xneu/0Zv53prcAAAD4H4w5/x9dkDTV+/QBAAAAAMD/Ycz5/17oNb3wxnTvSQIAAAAAAP/eH33+Xz7Z/y+L/015XfVfqQ0AAAAAACaT+vr/FP15VnUBAAAAAEA6f3T9f4pePcvaAAAAAABgMmP6f/1hstdUN5yuR8+yNgAAAAAAmMyMvjk/79HrXlMFN4JQtaZ8n37W9QEAAAAAwO/7/9SffZ6iN8+yNgAAAAAAmMyY8/+qfc3r+u2Wak95nX7W9QEAAAAAwO/7/1/8nf4rqtKZ6u/0Z1UXAAAAAACkM+b6/26vHX1U33Tn5rOsDQAAAAAAJjPm/H+rEl6Z6jx9VnUBAAAAAEA6Y/r/IHQ9P9Gop+7Ts6oLAAAAAADSmdG31bZP35o/6bWvqm5+qz0nL8mefIXuyp9VftWTH8rtXyW1664c2Vv2O6od+L1uTZmHQXO22vOa7uycM+cU67PXgu3Fud2DrF/aORtcqXSVO9tVTVUJlB0hqq+ieq66VrZzzh8un/P9ZlA+dVY/nNvpzBWd7buipOq1y8f9ILxQ2lnu61tTPxXn6IWj0nGrf3OjypVOJ/g2zImK11qu5Le1/abf8PPbXFXtNfLbgl7VfLbh3pqv19tU+W1+J9zbVXX9oBfuHaoSPU9tnZRW5WS5yEqR+U8LRf9K5LITqn4YZ7tX3bLLRMtJnBRabZGNOlstEmd6TCIrFIt2bsnm9xN5365zQbzOGdl3ZIEcEDngdN1KWDHz7myRaNlz0RaI40VJYZfJ9GbG4/WYKCsWa/WG2PUttdkDkx0+c65w4fDB4ezhUHZwKHuUzC4Oz3ucyE6M1HyazEZqPh/KDg9l88lsZH0vEtnpkfW9TGYj814nsnMj894kMztPbPbOZI265waFGybLX8olM/sdMt/71wvMvJW3c4OscPPmTbfasOu0de+YPKwV9JdmeHs+JrKLI89D7g6yc6Pzliayb/NWbrbbY7K+3dY4O23n5R/HmUpmB3JmX+vobLCvbTfZWjHZ4yeJbMfwPjqfzHaa7K1nstOvElnJ7PcLo/3+8mJ5uCoXj3HsxqzR8168/77fL5Q4Mcs3iNzSy3UeLa8Ggak1E9W6tUTmN4l5DXW+v4a+LTM/b21iX3uLonkP9byN8YBDjv5p49cEAAAAyITtL+N+U6KG7rO+n5HvbN9oO46oR9Tj9IBj+v6LHjtgj3vNsOiYOj62lg/6P0f0/fC45/YoOD5e1sfN8Upkj74frWePh++ti4rqfL2+v/DDuEMCAF/ZO/u4Ks8yjt8PHBQUF2xauGDDDRVNHRhsuHQe4PBy8ABHRQUHgyMc5CjvnONg04UNF25Y2NCwXKHhwqaFpaWFDQsLCws3dLDhhoWlpYWFhaXV73D/nuc89vbp09+ez+e7e+e57vf7uu/rup7nkXPvc+9z73Pvc+9z73Pvc+9z73Pvc+/zHz9/x+dBv8du1H5CiPDpQsywKGKyEOKg1SAUIcQqhxAfd3/P8xn/fskuv7t2i/HvlweV8XSHtxBLhRDbd8nrV6tl/utvyu8=
*/