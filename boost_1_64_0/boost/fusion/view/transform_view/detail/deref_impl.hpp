/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_1026)
#define FUSION_DEREF_IMPL_07162005_1026

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        // Unary Version
        template <>
        struct deref_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first);
                }
            };
        };

        // Binary Version
        template <>
        struct deref_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::deref<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first1, *i.first2);
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
Sk6P8UEbD+bObHflgAi0WWy+WvBat00Zb6o1M0hMnA165pVnSSmvmdUWI0ZUbG09RzlY82stTKY68Fp88rmRVDOrFgcmmk+c4EF1AfNi1nWG7SFaGpgfsyv2hdp+ASvHLHXsTprvulXb82CisGOsK1o2mDuz339OcqP9AlaSjenSaoT2teRhQvgyG9Cl6mE0/TBwZk3adXxOdQHzZlbix7F0xkxgfC1lx4gRaPFgbszuNk49gGaWxvR6ez4bzSKNua7DugW0l8AKM6v95q8WaFYph29/DSiPZgPzZ2ZOWOSFtkyaz9vsvZT6B4Z9/xxeL28fcCHPUpKywMyF8/ZLXZHS63zzE/vRYlMxvzyb++Pz79HiwTyZZQUda4CWCFaMWdK1gFdoyWC+zNpen/IOzSbNd9Hl40U0O5iO2bb1NaujpYP5MAsaNW0e2h5pLbXsk2qinZLM8TZhJ9UFLJDZ7/Y2b9Beg5Vg5vKsxG403diCaylp9uyMpgfjcSu+zx1MtZbirp5/mki1BuO5146JiEWzSOYzr/omtFTJ4hf/tIHqCVaSWYfsk1+jZYDxHgUW2diCaibZxq3DZqNlg/kxa2+rNoBqJuVXzT0hCM3jy4Jrcf9t6DC0MDA+5rM/a3RBM0lxWwedmkJ1AePr/KboNl+qC5gXM8Me/WmR/++VzwLDsxInqtX67bc3E9AcYL7MsqI378izqlHZYI78+0o9MWLww4MbOqKdGkfzfbLys9OmomVJVkyUjEDLASvK7MH37pPRXkuWMPPb2Wge44XwZna53eH4PKuTFARmyb8/1BdDR9Ta4H0Nbd54uo99soyEcU3Qlo2n69InOzRvwB95Fjk6HQyfNUxixNDmPTpOQ8sGs7nkzddApNb0ad80BW3LRLpmfbLDVdab0HaCFWH26+MW1dAOSHFb2tTSoR2T4g7MvtYT7YxksSvcTqJlTaT8Ptktt60v0O5KcR3fLFyKlivFbe9X9wc0MUmIcGaveq2/ixYDxnModLbXebS6kjUqNOM3tMZghZh9efFGKFq8ZHFla9fHZwYzGPa9ITwzePx1cjTasUl0P/pk4dPil6OdAXNntu/H7jXRsiZR3z9ZP8eLHDRvW8Ex9/bOPkvP0DYtrhG8junr7Y9mtmnv8RpL7/GybFofwMSzXO+BaNk27X4EJpZfqx2B5z0XTOS/V2sC532dteNENOMUGvOTuV7Y4YEWNYXO5ifTPY2ORDOB+TI7vDfmDFoHMHc25q+jZ6xCs0hjvq7kPx3NKtn7iR+i0GxgxZgtOXekfH7fU+1gWLOmon8k1QwsaCqN+clcusy9hBYG5sksodeIbLRYya6tES/zbKCIB8P+NYfXDnUf9suzXqNsYLjOFrDuGZvHX0Szg5Vg9vvky0/Q0qW4Pl02eKPtAdMx+6bsz93QMsGKM4v4cWMntBwp7lnjCw40MU0IP2b33GdlogWBBTJbvrpsClosmDez7oPc2qDFg/H8hlZ62gnPpgXss3xrCWdTF+12nZ7dwDD31vC6PPZqJbznZIDF6/J62xbuOad3jK6L13nTMiH0+We6HVznUzd5r0RLXoafg+XZpqrFh6GtWEbPtJ8svUpgfbQ0sHIsbvarSnF0HwMzMGv/4vhDtNdg9ZjNyNx6Ca3xt0IUYvM1/vzZZLR4ydY1F3XxnmMGw2tre7jnvB27qjlakhb3ycaffeeDZgErwmzwuaMr0JLB3Jg17PXfrWiDJUs50MmKZgULYmupVGNvPbR5YO4sLvFgn0fY98VsLR3g3nhj8L1GaCvA3JgNDZh/FC0NDPf1/+3y/o7r0PaAFWVmOGg8jXYKrAqzF70Pe6KJ74Sowez5N7M=
*/