/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EMPTY_IMPL_31122005_1554)
#define BOOST_FUSION_EMPTY_IMPL_31122005_1554

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/empty.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Sequence>
        struct empty_impl;

        template <>
        struct empty_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::empty<Sequence> {};
        };
    }
}}

#endif

/* empty_impl.hpp
BMb+fqfT2Dmv0MtzfkTxImd6WROEokUxAXWO9p6IlXgbQX40okQ6E3DlpyByBzAOkKoq8YJ9HlANlEc0zKV59Ds/15hd+vYJ1EprtVx84pRYMzLATrM9CMxHIM/t5N3AgrnoRzKIDmr8hRsg0DbHnD2VvOEKkmJF4A7hJ7FINNZoW3G9HPM/kIdJkDVThHsiEylkT7ZkViVHEAtLOKXmowk3xQui08HefrfHXAehIjxVa7R03E5NcUTXttBmmoSu7I/SyRQJKyY3OnQ1nyhovmozmJaxhP+FGkkHTNCdgn2TrcY9QYEumjsBUfW/57cewNAvtosxpQZAUKM2H1A4dPCGPpP/76E295phESepgRnxl4ww/lgg+uIIUz+JicFLhPZc2A+K6BMnHtgzyaiJtZ/7OUvHSeXx1M+kbqyRLKpNsp1YsXqauhozqRGFmIcP6hOdAdIfuoR4u6F9s53YTU1+/AlM5TQ0bpO0p19exe+yznKRtZGZLCfqZE2cB9IAE6YxllbkFq+b8nTAVGh4UqvvKyN9iA/UPYGBNovZYWoTDY/Kx2pLQGylJw==
*/