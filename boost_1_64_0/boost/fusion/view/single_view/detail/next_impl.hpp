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
PXszI6GwsCDYo7bd/Lmfz6Ceme0wBKStWFLygDA/Wg9m6+9V+UCYFmOHeDbfhJef7hUWSmeH8cwe9Vl7Xlgkox2ugLS320ffoFwy2eEis49rNvHRfJntkI3Z8BWdaghzotmZ8etyD1oiM35dHjCICxvEaVnUcS40VZzPIC6IlsSM3/tCVvWYTjRl7QZxATTVfBGDMbVsBrWj5WXG7508BnF+AwuhqfK0ZFebCy2Z2er/OCfQOqCp+hJCU+UCFoN1QEtgJn/fBmtH+4pZ/kw/fyXMkcMOlZidq953pzAv2jGTtJhSY1KEBXPZYRyzne5Dl6ifH9rp+xZF0Qb9XXW0MMhjh0+Zdf21zWKaD20zs24t9pUX5s5rh8rM9jln1xYWQEtk9lGKP6OwCFotZhVblZDXDPns0IHZ2lNrk6g+tGzM6P0JtDBadmb8fgXyR8etS/p+pjANzcmsesaaFWiNdHHfPLqaKsyns9bxz1pR7dEmv/eJFkLjefJ79Aha9xhp6UfdNQlzWO0wgsVt+uafYTQm2kJmK3b98T3labNDA2bOGY3tNB9aZ97rDdduUu2aHeowK3CzQFWaD60Cs+6t7o2jftrt0JXZTPdm2l78aAOZ1Z2ddwnVl2CHPsxsx9bVoXVHy2mSNrd67V40XyE75GFx4d9KyueKOrudvaZfmButLrPrmRuHaT5d3L7FHRKEhdEKcvvvrU3CLIXt4GBG3wVGc6GVYPbu3pXStEa6uG03WsljHTf98+sidmjOjD7DRPOiHWEWrjBxMVlRO/xjkvZ0c/WXwiKJ0Wvb9XgnWndncTyWM+PHcjeanRk/RvrQkpjxY3LIwCxJ/BgSfWx1oaUwo/+2QvMnqXMJJalriBjEaSXUeboNzI+mqiFsEKeVVOfiMjAvmmrMoIFBKXWeTrRSzB54pt+i+XS2+/jtRjQfWhlmb9416SoMStuhBrNnGVI+pvrQmpqkjYvr9YTiysjjZzHdsyCNm+55pDPa5LtNaG60WswOtYvdTDXwON1zqXC0yc9h0aCsOhcNTZWLE60ws6tPnh0V5kErxIw+p0Tzo1VntrHBbwuFRXRWqlW/5TRfcrQ58m9eL8yH9imzHWVGvxFmKWeHL5g1fVm6JvUMbSGzJyX6/inMm6Luix9N1c8gWmZmgyq1lvs02nxmU+yOnVRDeTu0YlY+MnyqMKiA1y/Mcve/9aMwF5qdTLePGVgALZFM98wfbUmaJaKF3l77hOIq2uEas4+GvRtC9VWywzZm9pSifSmuMp6PmJWbPeaisDBaAWb88yOogtcozPg1ioYWb5L27NvxbamfVe2wgMVdLTSfthdXNTu0NEsrtKfYDWFOpx0msLg317JR7RG0L5h1P/rqA2H+mmpz1bJDaZbnq10Hx1PPauN5k8X136IlCbN8jNsEs2ZHm6WntUVrzox/XhVB286seMk7L2m+OnboyOxBUr95lGddO5xn9nDzzXfC3PX4fNHn8BBaIjO+LVnq4/mPTPd5FZqdTHcuRlONGUJrmGbF0TJt6DdRmKNBtM19mWU/jYlWh9nMFjs+o56h2dLWKAntWsfM31CejfBczCy0095TWLAxHpdA2tWU21Wp9iZ2qM/swqeTLgjzoDVnxvsZRhP3RyXQPH2+X/LefogJNrPTZ8IlzT/ErCvcvIswlwvvSZgNqrn1OsWhNWZWYM2vV4Rpze2witmUZuvuC4ugJTOj/7BAc7Sww7fMvvYueSwMWuKxldknWab2o1zQlLm0UpsXbRSzxKHO1RTXGq/LmS2/1T0sLIDWg9mCgfVPUQ1t7LCG2Y//efu7MGirrt2JNpLZgML9I8LCaJuZvbrU3kK1t7PDMmY=
*/