/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : result_of::value_at<
                typename Seq::seq_type
              , mpl::minus<typename Seq::size, mpl::int_<1>, N>
            >
        {};
    };
}}}

#endif

/* value_at_impl.hpp
7tbqiu2qTSA0S8HtXIdbGJ1QtEXuGkFdcBOXN26RB3lQTzohvVxc1MjeUG7OxDGAbF/E6sQYFZ/7z4Rh+XX/AJob9SZJxBqFwPleZ0K65rB81np9cQ7UKxCI37L4M1DgxZ0nEoRJJj3s1Tk4OBCf+Zvrfo4KCwvEqxiQu4Hs5uUgQiBO5FQjim8koAIEQm69ZhURkbK8gypq62ZOEr6nUt/MRaQE81tGoXBrUBiGLjtWjwxgK0IWTfCdGKoZyxjSaDQKGapHRrCNNbeMNaupEVkmxG6jesjN1cxBkCaI5yKcVO2w/r2u89YJtTDTzf9HHg9kC5eDyMR/ppGIgGD5SJYBgx40Wc7fQl+vT2SaIOwZtKhGovgqVnyNxQU8xop/TlFRH4ni6dUc1Mcg0b8V0h++qsqQGBMZj7gm+oioQNH0nmXCSdSyPogsekTlci1r/1qAFwqwwmlTmC6AbDLaEfkVXU3l6cO+ohkY+qN/QFYOwCsQSfUTMryFjMcgce4ytRiKpEpkYsM1RSMiGGpGT5gC2mxDiWUJIoKwRbxRwdchu+H5myoMZiMo8yK9Q9VtizMs5lKkHJ8iObnrM2KA+l1pnERZozl/TagudOOvjeFiUOQCFIe58vOOg5TjzDqUHUNAbG6Mx5D/AvINRuiAkRJFJKPyiKuJgL9yTWRQjoRxGjcerCzNgJktjGNSKHyRX8LGDGqlpdTTtTJ+
*/