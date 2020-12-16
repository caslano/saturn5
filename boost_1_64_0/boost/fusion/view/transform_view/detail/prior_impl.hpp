/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PREV_IMPL_13122005_2110)
#define FUSION_PREV_IMPL_13122005_2110

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion 
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    template<typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template<typename Tag>
        struct prior_impl;

        // Unary Version
        template<>
        struct prior_impl<transform_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::prior<first_type>::type prior_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<prior_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first), i.f);
                }
            };
        };

        // Binary Version
        template<>
        struct prior_impl<transform_view_iterator2_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::prior<first1_type>::type prior1_type;
                typedef typename result_of::prior<first2_type>::type prior2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<prior1_type, prior2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first1), fusion::prior(i.first2), i.f);
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
U03IkpVxxTe3bEaWqVi/H0/i+SzBZO0Pejry+fSaYvz+qEaLIevIgmHy7B79sfcgWQxMnomNfWvyeUmEyRq2FjnG10o6TJ7PMq1KhpDlwOT18OjDjitk2lTj+66dTycPMh3MTthxXTtvMh+YPGet/znB13sQTK53cFvD7mRhMAthL/RZfF4MMGdho5MXzCNLgMn69huOzCZLgzkJe9W34X3uH8xF2MLpZ46S5cJk1v8tWzWVa59mfG8d5F1sBVkATNa3Q7/vLvcWZiWs3LPkNK4dJvOssl5/ivuujLsypHLh8x+s4k9br8XUbt0oO5v+Xjsd5vvTNmj4WZrn90qRvZvGnw/m2/Un0WH8+SeMPkPaiMdZ3ZYNI/OfXrheMh57XnQryr9zDEbj/tJG9A2IOkv3pZgkGO1lkzaocvMHqffpZ52zYH4/bTM+l7rj8XQKmW4GapfWteRCMi+YrbAhf6/szj/rBTP/aVu06JFxLkPP8/tbGGWdgjyz02Y8IwuF2Qg78qD/BrJwmK0w96MdCl+jKHNeSv+3C1kCzFFYrQ4XG5MlK3Zu5X17snTFXP5Z6k2WBaPMtqLvh+LeV6Xe6uILbRt6W3Zf4DGypvHc93wr8bZqXbIgmIcY5zDTpB9/Rg3Tfn5nCBeCdnJDWVeywLn8HJdvNWYf60IWAqPPMWHa0TLf35GFwfzkOK9Xfcn+gJmJcSV3H9bIEpU5m46Jfk6WBLMWcy7paLKNLBVmLqz9f/sMKrCxhnQYvdbYrvUZahj3IIQsC+YkbM2OyR5kuTAPYckjrrYg089D/4Rt3OZrQuYPcxG2v/XHQ2TBMHdhZ4rVuEcWA7MT5nLqP0PIEmDmsoZWllFkSTAvYZtdsxuQZcCshJW4XbwC1w6zEDbB/bCOLAcmaz8TMP0imW6+cWbb7gT0IvOByfrcigW859phLjLPYg1mkBlgNsK6952yjSwOZilsoM/2R5yLMq5LqyE9OReYTlh70529ydJgsvYKF375wpkpc07S3tpwZjBrYW0Soz9yZsp6GxwbPiHTEoz7MHbb3ETOEyb7fk0XsZ7zhNkKq5i+phxZAMxRWOTp+QbOGibP/MrQrs5k4TB7YUcfJlzmrJV9zneb34ezVvZ5ZXfFLWTJyj7LPw26zlnDZP+cTeo7c9Yw2Yffu6f/rMEwIAtG95AdWv/K5llV/yazXsCf8+Vb9qC/dpE5KfZ72z6RBdZvgBeMertLq1yt1u6+0WT+MD9hF9eEricLh5kL6762yVGyUQv47zDzzf1cgoEsDmYlxjVw1CWSJSjjZrX/YypZorLPvwf38SNLhtkJG3k8ejlZurLPkLwBxcgylTmrLHwxgiwbZi3sddOINWS5MFOxz+EB7vR3GloejM7gHm20tqDt/LJkuoW4TwhrOWPHMTIfmF5Y3Zl7l5MFwWyF2Xay2kQWCpPr/Tp24WQyg2Idqzh8IYtX5vz11ueOZIkwG2Huoy7VJUtW5oyKtZpAlq7YwI/69mRZSu0jyp0rTpar1P6j2Q9fzmwRrlthORUj23JmMGdhfivpd/5V0YJgtJe9WnXtwsxufcnCYC7CbAPsVpDFwZyEdehtV4ksEaYTtrF/p91kqTBPYcWCrp8jy4J5C6ttdvHn9TdQM/+j8PuYaVoPbdPdUcMLbLQWAKP7xD7NoL0ed+oMWRDMRdgCw8aGZOEwJ2HOnp4TyOJgrsKKtw37TJakzFnG49pAsnSYs7BJOR5XybJhOmGDaseMIsuD2QtLXHJuCJlusYlWQpjpIsv7ZP6KnUyb9JEsGGYu7Ms9y5NkYTAbYUPXfuZxBpiDsDVmXbzI4pU5+1jVv0aWqMz5fu+mI2TJypw=
*/