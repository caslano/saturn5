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
YgJtoaSfrGLenZZV8d5UHNnkUuw4uq6W1LnK6Bo4sYVrHKcnsgwn9tIiC8uPJ/HwZgIWWlgGI7SMwRhjWC6PGCv15IH1jDyKvFiksY/9ysG63wcUK2E/UBjHq0/8bCP2334e23/qZ/H1mTatrRHerbHMmIaxeYLVCrZcsE2CbRHsN4JtE+w1wdoE+6tgnwj2lWDfCFZvGcyxDFbituKYpzpyzAoHcvccGh055gvPRm/5Yo5QPGxXUluEztcjx7o=
*/