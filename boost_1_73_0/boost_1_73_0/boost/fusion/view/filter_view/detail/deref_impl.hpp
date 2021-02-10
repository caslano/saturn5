/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05062005_0905)
#define FUSION_DEREF_IMPL_05062005_0905

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<filter_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
njzmPaG0Oryil7gS6MSiQPAdilD+4mVqbqKuyp2Th8abV5CjrewuGbYXLdACa5uJ4g2ecOYxtZzyRgN2RPyHJcdthblnnlMdb76wsM+vwDNOoqRh4aN9HleVRrGvs+0epo5Duv2onND0CyXQkhZLjGTuYdb3VgJULyDbKbVsH586PNs9pWsBuVH3oeXwz/X7+Z/rlvurc4G+iQSIk9bGxgI/hKomNqp1hC/Bt9DuRjPSyks3upBVlJxyFmUf23v9murCk8iEJyEphwbvOieP9gbvDtvIUavAQivDV699eHpydNB9L1m+WsFek902e0dUJI7yF+lENFoPUNlYBdoO+DMy6Ra1E5pgKBxMVvSti5Pp24kFccfQsUm/oDgqK35poVXU8h48eHXadQpXlP0FSwZhRJzYHZXTgfYmrKHCvDpU0iPWMyBSoIYoAe/30AMayqcJ9uTELUJoQj0pKF8POex8UjprjFd2TqZPsAgNRlhXRkCVKurgXmFgbJ4SvUQLC9dgE8AOqRCHFX3DTsIX0ThlnYhfsY2oB1Bcy33K6JVoE2ytkjdzg6LZOTLSlcoJ76/DutaZe02Zd2VKz1V90M+iWcdgc24tkz204PS8uHQnzTpNcaD3itdUTqC85t8armdh0sM7+eFfnR69
*/