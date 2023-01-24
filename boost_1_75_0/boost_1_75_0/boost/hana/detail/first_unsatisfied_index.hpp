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
fQi/0/BLhXrOgN+N8FsAvyL4DaHHfzB6VE+N0SPQPYQe/d0KPeCb21WLJbukg2gGbrVCDm3Av30Csf82DPg0AtuHAXch8B20BSV3wdsf4c2jkyqVjPMuynk1DYHh66KQL7toiDHcTeQ3oH6N8DsMPwl+F+B3FdTtWvjNhd8i+N09VaGB0JPnd6YVl0j9q+jIPJXUzPbJ3pmCbHg8QZBnbJ4ojXo7ttGz4i3c6CHtJBK6C6RdoQzCxhmQntuHYMgHh/MIdWPUTt0YHZP+81YYATvRAKvHzO06UBBOh2hS7RBok6vePSBdVaTuz/wlx54NA7Vo7609j6cJWw14Cjuh9nwWPwJTL6KpIQ36uXZGmN91C//vDU3qIneTEGgPT4NvZZEbvl8JXwXf+bHvtrCBBNFpj0/m8z0p68ILMevPF+IatrRwkzdjYak3HcKMHvM6mZcw8O8uEFhXUZhlHQLeorERDdLyLFqToyaBT0rGX+l1orOrwTkgursJjK7oElOKr8EfERrbtWvw8P2Kdg0evlHH3i+LRb3o/qrMdrxyDR77OGC28VLFTGLvqTbZWismwXxvNED4kdaAzd5dkVadYCvqqkoQDpjCGcUFoNCANiONAWyM9l5yGlpH+ECHiOsWsjX9gdADdNd8AIEjoXp9TWZ+nMwfg2+Zb5fExTjvRSdZkXAeqYkWlxRKIz6lloiAV6xS327VKENfk55P
*/