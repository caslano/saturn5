/*!
@file
Defines `boost::hana::all_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ALL_OF_HPP
#define BOOST_HANA_ALL_OF_HPP

#include <boost/hana/fwd/all_of.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto all_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using AllOf = BOOST_HANA_DISPATCH_IF(all_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::all_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return AllOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct all_of_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::not_(hana::any_of(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_, static_cast<Pred&&>(pred))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ALL_OF_HPP

/* all_of.hpp
Zl7CknCa3toxZ/Dd9xweJNxldsJcnjixdwU/vIClM86mns9Zd3jxvj9402K3M8+ZYSf34YIls3Dhu2xm33AWc4d7N6KPyI5TFk6hOXTuekkKHS5SLwz2YGzOUh7PE+wDh7f9JGT2DYBoX8FAdspmaRolR/v7ziL2Yf77bugk+46a+N4snRMusIP3AMTcvmdhlLI0ZIuEtxjWbLF56HpT/AsohYfR4sr3klkrhwaGCtz9MGYJ933sC9p5PBFgczaW6GlhNRYBxF6Kf5IwSHCo21k4L1QEPGIv00UcwECAB6jkhoDmFlsELo+pMs1cDSFxSgjeqyNNDq/LwgCAYY87Y9YfP2ZXduIlLfZrf/J2eDlhv3ZGo85g8p4NT1ln8B47+7k/OAHm8WCwmPG7KOYJDB4zbx75HnflmF/us7+1tU+zGIeL2JGcM4UBbd9nc2Cpydl4N4m44009B/DtilLEBZTsj8dnzLfvebzHBiEVY18wdXaT+smeo9iN38B0HOwTGgPJsQP4d7oIHOSxRM4LoPmbFzj+AoZ5jLxkJTxdRHuzx1gwdfmUXY571vnr3gmMjqCzEz71Ai7YFsjHA2JJP0yJZi6/Wlxfe8E1QS3ng+NAy7+5oqnszTrpvb58U4ThBbaAiewD+Amuhdkr
*/