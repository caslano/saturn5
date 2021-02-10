/*!
@file
Defines `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_HPP
#define BOOST_HANA_NONE_HPP

#include <boost/hana/fwd/none.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/none_of.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto none_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using None = BOOST_HANA_DISPATCH_IF(none_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none(xs) requires 'xs' to be a Searchable");
    #endif

        return None::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::none_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_HPP

/* none.hpp
neo01QDpFw8rkF8Az5BYgENfIa/nVvE9HxDfV2y3Av6r7G7IKOcR8/umU1OniHQ0dKv5x63vfTDx8+j3sEbNKanVFpZ/1q04vHPzT3ajIxOkGLf2d2nf42bYHkPS7O4+Gb71poc1cZsfv7/oag92w6c898757tAw5BUh4AWu9mE5BH7nfHekIBjK1SziSUZHgbppascH2j72iG5J/PWXQ19wqk3J0m6s+1Zpm3zDiTxOYr+ONWE64H2t8fnVT7vDTdXR/XZjfcDmpvqM7M0DaB9uHAAh2yAk1L4/brq3IDcq16sVijR6GYO+F8XkJEGyDatgwOBinDeQvr0pGX/QbYZugog5ws+qBgl958N0bUNlQOQnwR3gZbiKgxtgJXSYSI5xZHn14qs131vhbqwDkmDE1BFN0AuJ4V/22EsZe8iGjTXscCj/FOwbqKesAzemk6/6Zc/ZXcPOCgBYBsGfiXmQzgSphoWolZMeblNZUYmEsapx+nPZG7sXw8FbPgLQj37pDntnYtTW6HruWAugUToizZB0tcePHdWRIFytU3e+8K4S6ojzGEfV619cjt2z884rVzkxXbw7bWTbP5RBg1DsJzDzdcTFGu/9qhbyqn47200sQzv5eOXMLNizpZ9eRzPqoEa5K+QAvLSh
*/