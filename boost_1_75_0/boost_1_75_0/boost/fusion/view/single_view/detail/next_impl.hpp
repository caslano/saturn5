/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_NEXT_IMPL_05052005_0331)
#define BOOST_FUSION_SINGLE_VIEW_NEXT_IMPL_05052005_0331

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/next.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::next<typename Iterator::position>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    // Workaround for ICE on GCC 4.0.0.
                    // see https://svn.boost.org/trac/boost/ticket/5808
                    typedef typename type::position position;
                    BOOST_STATIC_ASSERT((position::value < 2));
                    return type(i.view);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
9pUX7e+kHAA1JtCz1KDo1KDOl+OlrvKNz5avjlIncz8sdhUn/xX5Z1BLxEfGqbjHbUj79rR807PlA1vbpN/D/i5hVAT+/ck/BL6kCLDQU4D7LpKmeVq++TPY3yLol1xlG1fl3m9x8hkNR05wT++PnAjMKvRdPSWfayfPkY/OWnhcwOpiueswvgmtskjbtumOgQHdZWnL19wPUDTPkw+rsiurjEXsw/jTNZpwf+gYZrrYA/6XMeBtK15z/sifPvd+wFKyhuvJRbLjs+5vrT1aFLPDRUdPMhxR9LY+LV/9GezvIstGHya+Yxlnv5D51/A3akU0Zp0wz8spHxEwiJWTv/Man785f6fxuHinxB+gv+yfoiPMucLbhc0JFOB68Yfo56Bbw1hd6jXY3153epH2HgKkmLmWwOVd6x9zeuut/AO40/owXu/0790tOygCqrVqfdlfMn/gW3heKqb4PiffnDnoQMoMyg8UUV306SxPnX416r/dER+VspxoR9BAVcBotit27iKvH8HrSOy5Zfv7FP7qTfb3/Ncx3L/QxokHBgUHOtWdenSsErnQHXCVr5NuKTP5nuJnfbPzB/tYnXYSW+HK2cnvM4bZC/ug/lJLMm7/9hr5ymfLB08AGENzWdRx9geMh/9CfATObT/ybLNOz9PyVc+Wr5RP2x/5pjbdM/sHjbw0Z1PoJC3SveqkZ/bXvr/uM5Cv0WdZS/Up
*/