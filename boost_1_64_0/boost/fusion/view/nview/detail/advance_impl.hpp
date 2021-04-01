/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM)
#define BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<nview_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type iterator_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::advance<iterator_type, Dist>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
UO8KSlcvm7fTvprK12KilMpmrg7ohlhwCAOLhoCFDon9VYRQJouUGcC/v3/OqCs6ilT15QBocUZth2+4IAlnLDlMSIVybeCmufwzx9C0i6249Gf+0V2Rj/KYwiIM7sKi7UpfQc4uq9tzubnfZ0m8i8SvloAgCH43j9kP/Q9UV8LZsObvzu2AvjvD453nDJZQvcUqPgIx0P4oH1yiThhBaghLxo6+N2lmGulUDQMTKzWk/uZsgcIFMC3yXOL6ybJFQjarMbzei0E11PvkjRTSUXvb2KuzuAlq6gto1SR6ZQ7SqEQzmzoSA84+3eltuSAjkjQ5Uv+xqQzLJxPDhxydXcoxBtxFwRMz3adiXf9j3DSFeMxDTCTIUZtGMjt1c+mmFYtuCSiVNPPmt2W7x5ldD6dKukxOUaEHijQeslXz/ZhUxNqqx+roNrXVXEYQVkn01Dak/l2itc/zxaQlqvXDOtSWKtQeSTy7Q9ici1jj1H+H8RN2Ma02Z1Mf9ejyWL9VuF6ZKjhQs+eOsWahxBSRtiQTge7jjNeOo4ZjrBdOqEEuVjcw/Icau4bvFQ==
*/