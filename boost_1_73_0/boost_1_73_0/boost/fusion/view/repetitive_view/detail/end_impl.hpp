/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_END_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::end<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq,end(v.seq));
                }
            };
        };

    }

}}

#endif


/* end_impl.hpp
aFVUBQABtkgkYK1UbU/bMBD+3l/xCL4AyhrGp7GhaV3b0WqoRU0RqoRkucmFeHLtyHagSPx4ziGMTWKqNOEoPce55+XOjfdVaQoqMRkPRuOFGF4tLsT5/HLC80lvn98oQ2+/TI/eb/RwhJ1DtLfgwbFFXDr7i/LwdrYQj3i+GHXDcZdIilfIozjEbsgjDlqI6FTO4lyIXUI30Vv8SSPyRsQprzAsIoe2fnDqtgo4GB7i4+npJ3zAyfHJcYKRNIo0skBmTe42wVnRrnyr5Hbb9/Q1AQVI3e+olpXy8LYM99IReK5VTsZTAelRkM+dWvODMggVoVSaMJxfrqaz8wT3lcqrSPJgG/jKNrpAJe8IjnJSd88ctXQBtmQ4kxfKByZsgrKmz9qEQG7jI0eUl9pbyDuptFyzkAyoQqj95zTNG6fZfVrY3Kf5S/n9Kmx+V7JiExv5AFsHBIvGU4KYmWBjC1XGyA3hxbpZa+Wr5NUNS5kitQ6etI5cjFPkn20Tsq49SUxDzY5ViMFb46PUfWU3fyVyHyNL2TjDQtwHTiostzlBw5+Sa5Pbyl8kup62Df7n1rz6LWANm8HeIMM028NaeuUTXE+Xk/nVEteDxWIwW64w/4HBbBXJfk5nI956xWIOtK0deRZ3UJtaKyo6
*/