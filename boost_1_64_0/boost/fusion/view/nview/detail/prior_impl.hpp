/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_PRIOR_IMPL_SEP_24_2009_0142PM)
#define BOOST_FUSION_NVIEW_PRIOR_IMPL_SEP_24_2009_0142PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::prior<first_type>::type> type;

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

/* prior_impl.hpp
f1D4ikFvKemV3TImd2oIdC9p3Ggu7up6VdLuVl74wZllowg1eg9nO2ilBg2wRjKnSzDafQCNFk1Y9pwT5EX5Ve3oFQiUJYQnQB3Dq1IzeG6hw757RmKzvK/HSyaGUgKLhgEccXAPL5sdbkjyX2jG0V3U4Wf5iMfQ9/NR5EIAwiC041emfmC6YZJDDnKNi+T0k6ACuRzLRkQbW2fggZM4yEues3C+e+jw9nK1NjbnGUqupnK2/XOJ9o8J1Gq72dLWVblcfmu+XkeOoMnXylHMQ/r8UrHhyFOZ9J+sHUbuiyhnFGk7pew8e32y2ekozbJdeV+PN9+N6aXTsQg032dI70FQa7EJmrAj9tdxmC3bFOAlCz7dATGIu6S22McexViozqm8eaBSvBNGTi8isAHF3j2SAcmFMFm4xo9+qwL2otsKWNZtdQrqcKHGExM8Sn6Sww4qJZmFmOL0pmXgA+WujRACEKS4O3GONslBQTlAk4ZWnZ5Jh2677LoVw+G1qqLUe7W+Q3wo0otVQQQcJIJP3VFl5LETBBd+pizHoG79I3e/d0BD6PlVcLwq4Q==
*/