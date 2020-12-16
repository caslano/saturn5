/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_TIE_07222005_1247)
#define FUSION_MAP_TIE_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_map_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct map_tie
        {
            template <typename ...T>
            struct apply
            {
                typedef map<fusion::pair<Key, T&>...> type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair<Key, T&>...>
    map_tie(T&... arg)
    {
        typedef map<fusion::pair<Key, T&>...> result_type;
        return result_type(arg...);
    }
 }}

#endif
#endif

/* map_tie.hpp
Y/Ycu3bX+kv3qQkxyb1V7rkW3bMP/iZto1djHAagup7c27CnwXrdpc0lBLthKKrx0OR+hKtlPW08tFayv9bYE9tgP2yLI7A9jsWOmIqdsAi7OPIl9wO83iBfjWT7jTEam2BsDc/aAPT1/9q6/0iS6zMHjOr53dbxS72+588gkDp8fV29tp5eX0dP/by2Xl5bH+/uGQXGdfD6+veDpAsS+0Tq2qWe3d2zCyqvTz+JUoeuqz+XZxpEuXuuQdXqyrX14wk9nPXiftG/rT780nXhldeDSx24m2cheF7fvQAlvoujbvtl93FeqMN2rb+OVIxx1lknxGjrql3rqevF8vwEUgKpINZbx+ydvJN38k5/1fQn/f7PzJjw+8T+z9f8/o+U39HtSHUkJnQz5ctjoWac5uhBUdfH2cY5qcOY+bHoSZx4+/OOC22/63Id48X88aq/KfMoglTX35z+mnj7TXEtXuRLZomb/OSZrZX+plbGj46dU3GcfKH83sxw/sbWjnN3PxZcN45WeT7u3vvV78CftlSPx16+O+R4kqUfTBLp6lDOnZof7UAy1wLO87x89ePx/HFcUzV/9nnNnGXOMDuJXe2cl8c8lzHMJfLb/xEZt70IA0LJ8ANu8s2J8HQMc9lc3RhmOQbtuUhwOReejF9Om5RnNTpn6vnJn+s8P9rjTPaR+NNyvV2BLZXjnKc5TtvIU4b6ZkzMSOUpD54cp9sYBPrjkuvp6Q4y1sggboW23svPt2J+A0Mpl/n6/OZmXm4+P7Hlkw1prvvWoe7zqX0fb5Z8Zkn9XDqpDev6L9DlM9fMmN4Mc7a18vpE5drJXOB67UQa5D3GoIwDdfch7TWQJjEKnpO8PkNqR16L3OY1SRnDelllq78nhmObhp6VbabEF/hW6uW+InVQ7tkLtfmV0AI8ijzXXPl1oJTtLYs8i6HxW9+XLjEEJMZKOmWfzvEkKuWv5p/52vdwmnmiUmPpMl5czpvE/b8g74VzMv65ZJFBOZhzLyvmhtyfyLgzxsKvmjH3SZw2o/H+4brx/hH6Md66eli247iuY2zz1A9b7WfKGTnuW+V6NZM6cdwh/9Act3K/YphqTpYcve2Srfw95v49pT13rp/ZRTJu3yrjL3NIweSn1CU/1J7zzlFGs3ryDAblemz7sGfvdbU8laptea/LcnL/d4lLUcSXHJvKfROXYxfymvywNq/W3Mwq1NUbjZGX+vasNM11JbEPGMgv15UzRgLzHJ9dKHk3igsg75tVlPkKjqWXch9Q8m4wnl7Ok8u9rpmMqZ8u+7GSuirtPUtcY9Vor5qqPFvJXUyULbLfQaTm0he9u/J5sFQbE0X57mNrosixEubht+5Xysz1upCyqauWjbJ513uJjLH/Qt5Tn5FClXLR5U8iUFR6P3Ufm8U47lI4BtqWNaeaDGKHuHxHlrHxr0teXyb1JK8LlrnmVd5zHn8vG7rcs9gy9nlJSrNTJd9XFktevyE1lfLtpeR1uWteJTJFpfl0+7mki2OjzcOWBvxPxiU1sSn3pxW6PCiXipRVwSXLqh5Q7/24vO8ou4nqv9vFjggNN8m87x5zzOtln5fvnNfDJOV+5FH7vL621084XvexvQ50vA6zvf7ycdfzNNugPAr1179cYzXV65+fka73xbgr5P0pn6WR2EdpTy1ylpGnbXz2NsfOrWxtmDn5RNnJne6+nS9Ie8/SxaU4bBBboK/yXedJbSwO7U/CqsUZcH7nkjJy/i605urigmT6V8zLNcp19KSbuCCSmarEHPjVIO7Bo7q4B/0kP2X+FWM8dFAytrJizI6qxsdo11Tyodtn+pUVy+A9JdaD0T6Vg6/CPo3i4cS4OfY=
*/