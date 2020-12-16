/*!
@file
Defines `boost::hana::detail::index_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_INDEX_IF_HPP
#define BOOST_HANA_DETAIL_INDEX_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/optional.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <std::size_t i, std::size_t N, bool Done>
    struct index_if_helper;

    template <std::size_t i, std::size_t N>
    struct index_if_helper<i, N, false> {
        template <typename Pred, typename X1, typename ...Xs>
        using f = typename index_if_helper<i + 1, N,
            static_cast<bool>(detail::decay<decltype(
                std::declval<Pred>()(std::declval<X1>()))>::type::value)
        >::template f<Pred, Xs...>;
    };

    template <std::size_t N>
    struct index_if_helper<N, N, false> {
        template <typename ...>
        using f = hana::optional<>;
    };

    template <std::size_t i, std::size_t N>
    struct index_if_helper<i, N, true> {
        template <typename ...>
        using f = hana::optional<hana::size_t<i - 1>>;
    };

    template <typename Pred, typename ...Xs>
    struct index_if {
        using type = typename index_if_helper<0, sizeof...(Xs), false>
            ::template f<Pred, Xs...>;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_INDEX_IF_HPP

/* index_if.hpp
svL8WDgidMqEqYjHkN873zswKJCX2oXIIxGlDxFIj4h5RoIxOd6w0CUKGWUIKRUhgDYW9vntCSrjxBTE0BJSkFI7bTe6MU9QTNQ/1BfDcM/vCY3Eiyl51TMaqzL6CIQGwiL11RDyL/T6I6hNIicJwy1/aDSFYARCozgd+dzxK3A/2qBbHYrZLHmfPxSO4tygtM5YNBy0Kx3/oRaJ1szD8QDIQoq0lqRX2pRao++AkDsWlJUxtEhDsYr5YuGogFg0hvM0cpBhn5BraPBoxSOeqM9GKzZ1aKqo0qV5MGmuDKGSSps7NhTGSL9aCNLvX/z+RYakvjMpqZKVRm9CWa80gLUrlcDdloQXOf0jgaBPu9TZfFSuq52+lcEWzpyxuTqG2jzqR6uX/XqKcfN6EV+/lItQXC0ZH+O9E1thG9bejfaH8VnV9Ju+QLMxwWtr0lh0gtXW7LbolLmNaXjhmf1JvLlg5x6HWFRt3YrxpOkW3l97n8xjfgZD+FLexgVRwoGajQGkdiVtZ/Q/uZeRf/V0Q/ovHlO/EJ6sKZy0Xc6mcnmX6BwvaLd6qSled7RLayHbx1/9ClQHu1ebK53u/80zT5MxChkQDaA+FyoymhSYIJrIxaDdi82UxqqJBtJCnboy2BeomRMc30/kksL2zMDEL6QnciWVeGpKqH+xP5fzD5r+SdNFbGrX3zZnPlZ9bHpGg6S+XHmDSkl65MxM6ShcVajXGVkKkU7sUrcr8XvGrur7NzeRpkyTpMMzpXEfPLmGqEo1O7rmqT8bG6Wvv8qXMh2K/gJczRwqZRVlTlP0doUX+KPzcILqivpl3P+VvsJxpDCOd4RjOvo6zjLHWFvIgzYw6peU41ljx+d4FgaGR4ZVXVmm9OqshPTVLCl32hRJyoxJ+Ac2uefNbe12u5p72nrbevZwd3W3zm3taG5VXNhtBgHh1FfXGX70dLmbXe3tTa7mXZCirbNbSTq7bafZUtyfxLyjs3uOq133K3Ga9s7ddD8S8raOXld7WwubprlzXkeP9M3XXzWZ/M5W/E6UXPU6IVJ8vhM+qz7t3Nnk7mzaubW5x93R2uPudvW0IquOnu7Odndrh6upvVX6RveNSzvHtbu7ydXRsltbS48ar2w2fcvc5i53j2sn1edcNm08OO5Z7a6d5iLOe8L/bM3/HIfESaoyaiySJlPicnKiuLR1JgxLPCZcurk9iIervbOj1d3b2T5vTqtevoyM2dVvVF+zNF/zdF91SRFXzanMnkL3Jlm6r82dc9rmuHZqVam7DSa376H6Z2X1dU1tPd2tu85r627V6mv2yvLu9ramble3qiPPyufCko6dOlxzWue27dQBNWr9cljTdbjQWlsR7p7uPbo621D71fwOl1a2uacbVbyltWneTi2uHpekp0tsP1r/rNZuOGD42O3ube2e29bZgXq8s7JXJ31FsLjMlPHH29AJ6L7ieEtre2tPa4tbcdHd3tqxE1oEfDR4b49SgXZydZlS6H2M5nTPHl2t8TbV3KS3vz8UWQR3TmvP7M4W91yleOei61HbnuL23LY9W/W+V3UaErButluV6e516f2UhbfOHmN5FtYEvc1N7Z3Nu2i6TT6o8dRjZTo+c4ZxPNt8fFZ35xz3vI45rg5k0aLHjOLu7tYeV1uH29XV1dI5B7/0WDjMMs3xGHTO7UHgu9t69XrpNPnR6urZ2d0ze17HLu54kMDRecbj2+6aOzdeDnHdxvEu1CdIq+SrbrTDtbV2mI922O2PBD24uG0OR2f7oh0jw3h0w9viH8BFvqy2QS6F2v7ypQxHREJd1s6rBdp5tUjKKIIVUlaOJK3mULdCtP4I9nFUKsS+kn51LX0=
*/