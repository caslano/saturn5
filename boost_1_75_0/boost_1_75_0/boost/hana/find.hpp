/*!
@file
Defines `boost::hana::find`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIND_HPP
#define BOOST_HANA_FIND_HPP

#include <boost/hana/fwd/find.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Key>
    constexpr auto find_t::operator()(Xs&& xs, Key const& key) const {
        using S = typename hana::tag_of<Xs>::type;
        using Find = BOOST_HANA_DISPATCH_IF(find_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::find(xs, key) requires 'xs' to be Searchable");
    #endif

        return Find::apply(static_cast<Xs&&>(xs), key);
    }
    //! @endcond

    namespace detail {
        template <typename T>
        struct equal_to {
            T const& t;
            template <typename U>
            constexpr auto operator()(U const& u) const {
                return hana::equal(t, u);
            }
        };
    }

    template <typename S, bool condition>
    struct find_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Key>
        static constexpr auto apply(Xs&& xs, Key const& key) {
            return hana::find_if(static_cast<Xs&&>(xs),
                                 detail::equal_to<Key>{key});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIND_HPP

/* find.hpp
FdhOvg9mKrF/+SQ4zuhbftffyv2Ie0m0bYyuJLnzSZb1Mr35z5t0jvE5licrPJT483+kRfkmU+enCLkTf4HlBC4uiiXvsB/dl1/QNNjKfkNddM1WIrVa6hkVM5sB2NB/zyg2w9AM0ZhVFMuasItDz991S0iUs2pd1KHnWOJsipotkCPIGjJqWOi4jDkhuw47MSVn/TNyJ0r5pCLuyBZVEX57lNZ3mS9mvoz+lZrS2MiVctKo7bEVVDGGzyjb4aJPvTyS/SrgUHr3uKBIioLI048BWQDZD75ZswPNLwyBGOiXZIHJYjJqC0trM9Bko2Gjh9X7P3mVsC/uzu+ajb0weaU4m9c/wxkOJ1zTvFK+ckJKCtinD5HfeA4i07XeB0C+7wOHUcgKo7j0Cq9XiYz5zzLHhLAfFmSNyiMI+toie7o34ukx7FhVAtR1B1FLTDsC1Qfx5Vo9N/A/IXe7e539j9Wf5I7eHl58ncqtrPe/0RBqCmhXMV83JMcw3kOw+7/f9J6sWbgqZrZ969bRr2Nd0LGzb8G/YKg1OxbwR7j3HP78NI+U8tAg5MjsuBgxMUJQMDzvZXu5IfW9WicC79zpUvWSjmTu5vXJlnxjIqQ13E3uDLIx5w/9BgNU2PTPQ8NOYmwDlnl+wowvCt5hAJG9wKGnozio/x9LylDY4gcRQBLQ/Vd3WW+j6HkuBcxuWCPg8sZTQBvKn7SFcPsC
*/