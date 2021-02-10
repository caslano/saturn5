/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_IS_SAME_SIZE_10082015_1156
#define FUSION_IS_SAME_SIZE_10082015_1156

#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Sequence1, typename Sequence2, bool
            = traits::is_sequence<Sequence1>::value &&
              traits::is_sequence<Sequence2>::value>
    struct is_same_size : mpl::false_ {};

    template <typename Sequence1, typename Sequence2>
    struct is_same_size<Sequence1, Sequence2, true>
        : mpl::bool_<result_of::size<Sequence1>::value == 
                     result_of::size<Sequence2>::value>
    {};
}}}

#endif

/* is_same_size.hpp
UrPAc+KrZk9uHb4YhUWIZ2e+zKH12P0qHu/FM/erqzQv/O9mWXqJ4Od+W2Rhko+jzP0WEFA4i7w+ASfAN8E23DCA4N/6/bMA+vxyExTzJAHklxfz8TgAEDRtxoU3CbxocTJOvW8LuA15ATgr92dCMAxzvIwqvv+UXTzxtqfIijQdj4vS18Mw97r4XEzybfzL6zmF1QzLHURZlnqTQ/AZJEU6q/h6VgCu9Y5uUuqXlgynHFk7i4jpOoo+BSNAq4j6pmlSXAV4H3J3e/N0+AlhTBpn0X/N4wzgDHs5pMsvLwzyIs3Cy8htPp1Pijj2oInAcOne5bMoGg2vouEn93vAmcmkBGQIOgOCFff7JE02w3wYx17nMGvqYfshEatJmBfBo0C/gECUK8p3ETGVjBGvIpJ3lkhgMsvipBhXwM80mqaZNyf4bhRdzC8dlHnSGbw9+Ptvp72+vt7mq2B3Z++JhXioBWHCg6Ojbq/fPW6f6Gbe98HuUxv5lNDzH+3uq9NeewBvA53q6W7GuKFh/nnwOcou0jxqhK2L1rA1agZ88Ek6gzOfFrpz2MrjdBhOgoOzDlDIZIi8gIATz/io/er8zavzzvHRWl6ERTwMPqfxKBjgh6gBUDAHfo46j8L8JniIuKm1VsFEwdyoTZBE
*/