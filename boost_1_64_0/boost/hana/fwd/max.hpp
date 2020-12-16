/*!
@file
Forward declares `boost::hana::max`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MAX_HPP
#define BOOST_HANA_FWD_MAX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the greatest of its arguments according to the `less` ordering.
    //! @ingroup group-Orderable
    //!
    //!
    //! @todo Can't specify the signature here either. See `min` for details.
    //!
    //! Example
    //! -------
    //! @include example/max.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto max = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct max_impl : max_impl<T, U, when<true>> { };

    struct max_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr max_t max{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MAX_HPP

/* max.hpp
+FBxr13Nui2RqoOwUMh2SCGVnIP0wGs5wDNRCkfw/bXvcZxZRpVCJ5gawtGkjCJul1ktMv6KSJW1W7zVI8YjHme7Y6VRFtInq20kVonagMbdSy47Thdsn7M/izzO+tyo95B1/kW8FWliQ0q8ovFjGn1EqIVZ9ynEXJM8KWj5veHVQ93s86dvIqCPN4eUCRh7wPd2iFrJBoK6m2VIr1LZ6ZvH+82hFhRNeUs8lFaMQkLJiGB8J5tDIM/MjHyoMSM/tThpaYAeSZPHW8L18nIOY7HYwPEi4eIwiI9aPFgrz/CUtJOn5hPkikcu6hKtKJyTuQrkCloGe0Q7pB66M7xwgHYetMbrvUUBJT7RtPRE9YafO36OHyz9rDqrlrIFg6DlForASDjqgrRg2+9GKYYJt2aPr0S8vkgK1/WPeAkBBGAtsz+YxTmwviO0yNxGZjFL6NFrboPmfVcTAZuTQumpMb0FG0M04lwyomduCVA+j/jwcC821kYMDuzOtm+iDYirGUnHByDKJ74xE0MHc+Wl0QamygYOquQGZhDXRCzcRP0jzkEM1HfW3Y9iQbTWq40butLJDEZy+pqcbY5xrdCsmM6HYODI0ruIuKS/bibhv3d8MFlWg4Exv0zdycWPR7w4C0VSe1zco6CdDJiHZJcSCNZah5LRIbILCCC3x6EzVMOCb1FdZswRDWRqiwLmK73Bozbii4odjy4RUcQP2K4nTwi5fANyTxxiyE1DRQy5+yVZSS0xhyDaZc80y5AEqznkDPPTIXWYfyHiwexxE3inLDnVTJo5fjFamlcJe4l+szom/P6eS+sTtCITchorb8lpqbxZi5gfRpfABnUrLRubd9mHEP9woT/5MxUKCsm98fK64RNzGrTrvOxRmvfvlTkeMPp7Qzp7NeTkyr/0drC1D/k8HjGwQePGSPijowSJB83NiO2hx1b2BUeP6a7CGINiymmZZZu+rHaYxQQGsbIDwkKmOpB5/+MnFueAB+TnpqM+P+LP1/zP6f7J88GPHpP2QDJVFj3mYmb5NsBILWt2kTw8jWhR0JWtTCBHqNaqVAgiL4B48fwjqJJ7HovWJOea3EiTvVBl4V66J8IHJTn0mwf3YphcsIghjasp50Ph8NurDwKvyukwhHZTorwLCBMtS90dtGscDbD1Ex95czS3jsdiIm0cZ4hOSZ6LmTMoMrfyeadun9tTgjTZ4m9Luy06FdFFZ4NcdCyPWJz68p5L2X1ifb20mkarSjqIumYgcGI7Xc9jKTf7Rjgq14+Rq1QzAjOBQIMipmLyixpEoE3FvM5MosS6SSUJl2+coLrwC8emveJElSTX88Lifomtn3daqm4ll6XUR9hmqHuJSGbuQyC7zmCB0+PzixvvkFL9Mxz+1Y6EeEdCoZOLg5Nb+i0Vw+/Q98bM9ZHG/VoPBeCJDK2CTvbnMpLaw4gHSKumY4J8ExOkTFbVK1iQQlUlIFn4jEAeaYrO7wTVxGRD1VSNrGp39VFVpRhVpWhVra2WVfHuNuNtlN6ntKSEEhWjMlqP4AvqFqZ14bM1F+meYG4m1dmzk2cVO/CltUo74yySHr++jVxB+9sE9WlaRno0N1HbaEnFbz4+xR6RxxVkeyPSjdMgeQytCnbD7IXXIjTiib9ICirCvXzgp3vJNGZBFJPQwtzs9XtAaP+ihVcm04CZGyVJbAJJbJrV0yCIGiZgP/iNh7EXxOdH/Bv9rNV+9z/8/0sPiYrx8Lqk6wfeL0Ed7qLnouLV3SRezZXy+BSs5+ZO81azgJ7xDDbfgYNP8GcdW+s2Qqo5co/5ZYfSy0TBFj240KKF7+XkViPcqoW/xeF2I9yuhTchnASULc7w/ZA=
*/