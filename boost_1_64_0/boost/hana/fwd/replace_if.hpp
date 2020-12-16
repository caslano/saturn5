/*!
@file
Forward declares `boost::hana::replace_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLACE_IF_HPP
#define BOOST_HANA_FWD_REPLACE_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Replace all the elements of a structure satisfying a `predicate`
    //! with a fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `Bool` a Logical, the signature is
    //! \f$
    //!     \mathtt{replace\_if} : F(T) \times (T \to Bool) \times T \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to replace elements of.
    //!
    //! @param predicate
    //! A function called as `predicate(x)` for element(s) `x` of the
    //! structure and returning a `Logical` representing whether `x`
    //! should be replaced by `value`.
    //!
    //! @param value
    //! A value by which every element `x` of the structure for which
    //! `predicate` returns a true-valued `Logical` is replaced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replace_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto replace_if = [](auto&& xs, auto&& predicate, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct replace_if_impl : replace_if_impl<Xs, when<true>> { };

    struct replace_if_t {
        template <typename Xs, typename Pred, typename Value>
        constexpr auto operator()(Xs&& xs, Pred&& pred, Value&& value) const;
    };

    constexpr replace_if_t replace_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLACE_IF_HPP

/* replace_if.hpp
lnHsDoU+ZBX9YpyG//JxRVXZrTk73HpNVzffAqcBaSUHoen6pgLtEjeDDNaMJEZjIusBFjaF55q191QCj7gSCbT3VZgBTpGkky96fmXSh8azXnlKuMIMAyC+qO8KqI+/b7R3hcNDMdfKE2flRBZT0Kq25NyPmZSxUoyljK/JLWdPN8Xky4yY3FJDjPb8UKxdtTr4ZXTVCqzGDlPgRgz7QhSVgjj/NfhKlgFWzvKK2a+iOyvF919Wmg0V+AiTAVBHfJQH8Ii4nre4dAMm6h+G4RkM77e71RbGgTm+9e/qeK7jnFlzJQrV461wy+mdB7TjV4kuMzT7xmEZp1UZlUWFDvjPQaMGeozP2e+pvujE9cARLp3Wgingt3a5U3FXSnWEA3BM+fNm5RZaAzg6iB+VZ1s/m94rilhpxIV3WmI7jLo+w7Z+PEKjRvj7gZXO+gldCeCzZ+J/divGlFx2X2L1jJpmt1WRxmjImxFaagk2Wpb0lPY/oUqdKlWptyKaVKmbj/kvgip1qq2qnhnS4/5zSZ3aaYZiE0ec8PcllWpoI1T9giNwZE1q1c5kW9VGKqMiq6Q8f0n35dZQhaOkPHdZui8gK+iPrBIXPCY1CPwzo4WYYaWbgBLk+/7qR5Q68jjyI09TRuJIgRTpwy5MxFiVAn34PF1CvV41e9ku/Vj8p1J7PfTsXOoA340y3RKVbuouvXvkZ01+9jU+deLfb1u81sH6f2/EyyszsVTL06V8Qg54VyhCJwdw+inN8GdCDpjHu15HPTYMgdTgWmz299FJLOYwRL398eyKZz88u+HZF89MPLPw7I5nHzx74Nkbz5549sLTgacDz154FuHZh+iiL8MFzST31gk5fU3Vl+YMEX+X+uaEo4uw5w+uKTJVBqyhGzJD0xyRvvK4yy0eiqX6DiHEDVmhadnQTrJjDq0I1QFSjzphp0qF6qAvRLWiFdyXDA7iRpXXP5XWH3KLaMSMQd0G623JMXIlIVeJkcYBPSk8hriw83aLQSo+0H1OfPft3yO7D8Ecnrv4OgvxL8n4dkzcr+nn66pl/TTTrr0G3w6i9q2TFHwbL0KN4tObtGPXSlm9+icWSglIq1sb9qfPXibkNuBbP6Pp50vC0Z+8lENSSUyZAU/xlJHKXbxSz5Pc5GngDZfwkj3i/AR4LzzZPnjQLyZgoPajyGbPB2/rNHDNcDILxP4xq9E8N5bWD3llIPLX0+sUTyKltNfzpmH3jUf41GPXuB754sPD34oPK3tmqbWLMSqYXUl4vUO+mvHqkq/JeN0pXy143StfU2pdP8u0P7Ebf2D6vfV61N5gsiu2K8a/9H9FSijYzPzkVLdt0xXJlbZNUKtIgu5Suqgjk+fjzdBsShd4QaSDXyz09TW8pKRvq9tnZ84n/XV26xK1ffd93VFbVsRCijXBqHXVeMwcFIHJP5Xz7kYY0Oz8kgyw/JJCn7bhJRWf+CWNPm0LbrVG5oYrosmHC7cXvhg8krbchRBOgHavTLUDZHRq3T6iI3hyPvlm1d/o4UHEu7Eku1US/S19t89Mt8toE1r4cuGOmsuwGQXhyBbldzMLmxX8xErEkXcSttsGgwbNResuYz3ILJxIFFZ3CT1DNKXMjCeITFlSqB7huo8c1dOTqy+3VJelIII+pNLTUV2WFqoP7ahrtA/GVtmUXhfacfO+f7J3JfBRFld8r+wuycIusNgVosS6SICgkS9KgCCJJJvIuTHJLhZIaEvtulKLkghWytFN2t18BGmrbW1rT3vbuyq2WrOkEA5RjqIcPQCrTkgRqlUTFLb/9+b7NgfhCILY1s1v8n1zfDNv3ryZefPemxm8GOIvutK24MsqIH9uWpw=
*/