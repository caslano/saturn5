/*!
@file
Defines `boost::hana::detail::first_unsatisfied_index`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_FIRST_UNSATISFIED_INDEX_HPP
#define BOOST_HANA_DETAIL_FIRST_UNSATISFIED_INDEX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/value.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <bool, typename Pred, typename ...Xs>
    struct find_tail_size;

    template <typename Pred, typename X, typename ...Xs>
    struct find_tail_size<true, Pred, X, Xs...> {
        static constexpr int value = find_tail_size<
            static_cast<bool>(hana::value<decltype(std::declval<Pred>()(std::declval<X>()))>()),
            Pred, Xs...
        >::value;
    };

    template <typename Pred>
    struct find_tail_size<true, Pred> {
        static constexpr int value = -1;
    };

    template <typename Pred, typename ...Xs>
    struct find_tail_size<false, Pred, Xs...> {
        static constexpr int value = sizeof...(Xs);
    };

    //! @ingroup group-details
    //! Returns the index of the first element which does not satisfy `Pred`,
    //! or `sizeof...(Xs)` if no such element exists.
    template <typename Pred>
    struct first_unsatisfied_index {
        template <typename ...Xs>
        constexpr auto operator()(Xs&& ...) const {
            return hana::size_c<
                sizeof...(Xs) - 1 - find_tail_size<true, Pred, Xs&&...>::value
            >;
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_FIRST_UNSATISFIED_INDEX_HPP

/* first_unsatisfied_index.hpp
fhcQ/HUXNpp8n1VNEV+RvnJVW7M7M3gKefVHNzOyTdyvgw+dcnCsgkU0tKIwpahcBaOOP29NM0KHBDufu8ggbId5ZgqFqNH4UsgMY4eYLdn8f72JjUbKMgEGecWWUc+RNmDBkOc4+mXGyET+tRbAJ6Wvs13T1DmVkz0V2+RBo987e6O+d+QG8aMEZoR0Y0X54+dzqy0DM/2h1GMJLnFc0cSlPifvw3VZnADRREXxS0y5JC4rhxFCL5Kx2Iho+ZWnDSaz3nAEz2TEUJSY/S5+TAxuH+UA+q6LpObqwWaD9rXNYAk82qN/rsEZw3HdpBfVuwyb/Mq97N3b57k55JEetZak/OXP9MPqP9qsrf5DEVY3gtVULrk7LFSreS23nbxtRbXHYNqVxUplhqjj5q5lsKaXeR/VowTL4IiJHKlSs72kQ2/QyK4d8pMr3SS1KqgE36QYx15TJO5wFuAhq9MnHP7fPiGafhLlQ7yelPWqqWsVD9tTBqIrLxBtXuF8KCGA8SUWXP6eYLanLMUoNNfaVm7fmIZ3zx7DB2FjrVjz6LxSH+SxFe3vKYqy6Q==
*/