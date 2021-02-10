/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_14122005_2015)
#define FUSION_ADVANCE_IMPL_14122005_2015

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/mpl/negate.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<reverse_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename mpl::negate<Dist>::type negative_dist;
                typedef typename result_of::advance<first_type, negative_dist>::type advanced_type;
                typedef reverse_view_iterator<advanced_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<negative_dist>(i.first));
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
9/Y/5jgB3+dMNBuIwLcuO6BFzqXG/rJACibz6imgU9AE07H8b3MGb9hDJTdODWN5YeyNrjAT4UVjc8T8KzrXIh8pXLGG3YeRDLEhzbQTkLXELjMx5z90PEHPFsxsumlloo56A+83lhx+0UGCZ9idJXTCaOTxGiYU7KoR7NbpgPXS7N4has+WCo0qUbf9jaXEuY7rIbb4NK0WxiVNRx7GomBK4kN5wx8eEJvxylyEdNuoEsXQW4l91KxFZ31Pn/x8yM5n/MFRHKEKorq3geEEP46O4KnteeGfk1qe4bDGOZvj+zH85G1kvKoRJJoSsTkKkk4xh75eDrnm2BrSluyxT/a4Kc3Qe/qOEblQ/ZZKjAfU9KMr0aLEwU0c+EEJRjNNHYr74EV9uwpsfAihRHc7YJrtbdda2BluGAy7dGc3g3fmaICO1vBrXA+SorEDi+S1SyJmPKyKgg6eXBRPmtpry5lRM0ZuXXeD9xKy+zS5EZ21iWH2Wmrb4yGCuKVtsFmpwcQt4oVILWShPTs3Ziy2ac+d4w6xjDgnDEr2FyAR8g8fnGYj9zOHEQaL0qiRO3PHdoTl3YJtPmJctdwq4KvhsIE179QS0X6f0N3HvE07X6UZr1C0/EYhRhw2M7xTgrVCfqMd7tdcbjBInVm8
*/