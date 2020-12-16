/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_20060124_2006)
#define FUSION_PRIOR_IMPL_20060124_2006

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;
    
    namespace detail
    {
        struct poly_prior
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_prior(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;
                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::prior<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_prior(It)>::type
            operator()(const It& it) const
            {
                return fusion::prior(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct prior_impl;

        template<>
        struct prior_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Iterator::iterators, detail::poly_prior>::type,
                    typename Iterator::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& it)

                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_prior()));
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
qVu8PM0IjGc24nRGF7QQYRvPLVajhYs1zyU5ZaLpwXjWpU7F36HZgvGsb6x44ImWIKxk1vqtaIlgNsxibpQtfI6EVduvO46WDGbLLGvB9my0NGHDVN27oZ0G4795DPnyTo+WKexXmMN7tBsil+XZB7aj5YDxZ3rhoo5paHnCBrSNNqEpHpqf83vo/INoKmEx4yuNRPMGs2RnuVv3XAqaBoy/tm5/26YqWk0w3l90SAnKrL6wr6M3FUfTgvHPrSGTHIrS3IUVjbtzi2YLpmR29UjxnjRbMD7b571TetBswdyZzV3qWxktA4zneW9NqdVo2WAuzNYdivamOYCVYPY1/IEtZf3IPLP/nHd+geYPxufe/auKZhQIxvc74ax3pszAvJit7XalA2Um6tpsr6NAM4C5MetUzWY4ZQZmx6yutgRlnQzmx8xmYod1aFmiLnjW/jJoOcKel1/wjDIDs+c9HDBWR1PkmM+9Rz2Xv9A0YE7MbnW89AMtCIzvZ3WxwgnKTNi5JOt/0fTCpm3x/kh5ClOWdbqLliDs/IhS79EShSWG1s2lrIX9OFXJgbIGUzHrPPMO5ZkOZsPMft74qTQHMFdmJTvu6YyWC8azji//cwlagbAPe/Jbodk8Njf9gRaj0NTCftol/kILEDZ+/uTSNCNhzff23EczEnamSqd+NCNhb3r+VYtmJGzw6X4vaUbCTqffu0EzEvbXOLfuNCNhj5/7GWhGwu6eOumBliasa9fzF9AyhA2Mv/8CLVvYu1e369H8hDV7F12M5ifsaYetc2l+T8wt6vza9jQ/YRGvx52m+QnLHjlKTfMDc2P2+lr0VjQdmAczl6Hnc9DiRN2shX9F0hxE3Ygal90pazAvZva1u/pQnmA+fM2Txcaj5eGaaH1vhaKpnpp/z/nRtBH1V+mp+G3tXu10tJpgVsxM3ZfXpVyEjbMIeoRWH6wYsy1RAc/RtGD8uU3SrnmPFgXmzqxd62Or0AxgzswmFGv9Cy0JjM/vpO3b45QnmIqZ6n7mEbR0MJ71joCdz9ByxJqNPJyaU9bC/HxadkZTPDN/zWra63lfmgOYLTNT831z0LzB+BwcLs0bhhYA5sQ/v1zJzkALAeP9eXYKP4ymB1Pys7zvUAQtFsyNWXfPMn6UtVgzNa3+FsoajM8o/I3GiJYG5sJszIIuS9GyRO8Lpzi5U9biLIcS/T6iFYDxe/bw1JziaD/ArJmVscl+gGbzjzjnwmGX0PzBeNarv4wciBYI5sgzy5hPa4aA8TkcyH6ZTVmD2TFr3fTmOsoajD8PP3qlxaHFgfEZndFNbog2Tpyz1K6nt9ESwfg9e+kXU5RmBObK7GFHx8doqaK/4OnnGqClg/G5f3YMphlli95b9i18DckDc2ZWYnt+TZrDc/PZbrqy/BGaBoz3XnFrlI7mAObArNSHXjdoDmB8v0vepok0BzB+zokDk/pT1mA8M+uGFiXQDGDuzP7ZMmokmgnMltk61c5KlKewaoFaLeUp+vPeUeonWhaYPbPhnfs/RcsR/b2eF/4BrUD0N3rtyRNoqhfmz1+56hNaoAWA8bn3PNDIHi0IzIPZlk5loylPMJ5LgGN2WbQEMDe+ZnWv2mhGUbertKYhZQbGZ+sW2+0sZSbqui/zjqBcRJ2T9SxHtDwwO2axjboFoClyzZ+HrWfP/4WmBuO93x1SvSLlIuyVzQx7ygWMZ51z1OIgWlyu+Px5t2IlNAMYfy243vEozT1RrHl/06lgNBMYz+Vh3TvfKTMwW2b9vEpQf1nCvl957k954n5ozmkhaAVgKmZvB3o8QFO9NP+Nc+vKkcXQAsE8mbX96uONpgNzY7bSuUrh9w4wJTM=
*/