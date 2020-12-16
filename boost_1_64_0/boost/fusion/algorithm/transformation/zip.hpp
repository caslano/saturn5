/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_ZIP_HPP_20060125_2058)
#define FUSION_ZIP_HPP_20060125_2058

#include <boost/fusion/view/zip_view.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/detail/pp_round.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>

#if !defined(FUSION_MAX_ZIP_SEQUENCES)
#define FUSION_MAX_ZIP_SEQUENCES 10
#endif

#define FUSION_MAX_ZIP_SEQUENCES_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_ZIP_SEQUENCES))

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/transformation/detail/preprocessed/zip.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/zip" FUSION_MAX_ZIP_SEQUENCES_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_INC(FUSION_MAX_ZIP_SEQUENCES), typename T, fusion::void_)>
        struct zip;
    }

#define FUSION_TEXT(z, n, text) , text

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/algorithm/transformation/zip.hpp>
#define BOOST_PP_ITERATION_LIMITS (2, FUSION_MAX_ZIP_SEQUENCES)
#include BOOST_PP_ITERATE()

#undef FUSION_TEXT

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

#define ZIP_ITERATION BOOST_PP_ITERATION()

    namespace result_of
    {
        template< BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, typename T) >
        struct zip< BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, T)
                    BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(ZIP_ITERATION), FUSION_MAX_ZIP_SEQUENCES, FUSION_TEXT, void_)
        >
        {
            typedef mpl::vector< BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, T) > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }

#define FUSION_REF_PARAM(z, n, data) const T ## n&

    template<BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, typename T)>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, const T)>::type
    zip(BOOST_PP_ENUM_BINARY_PARAMS(ZIP_ITERATION, T, const& t))
    {
        fusion::vector<BOOST_PP_ENUM(ZIP_ITERATION, FUSION_REF_PARAM, _)> seqs(
            BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, t));
        return typename result_of::zip<BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, const T)>::type(
            seqs);
    }

#undef FUSION_REF_PARAM
#undef ZIP_ITERATION

#endif

/* zip.hpp
4Cpv3n1xIYSxsMrYnvLLVxWo9gQlzOG7JwN7+Odn4mhPfl415CdL1uPbJZ085Gf8i3O0MT/Bnftruhei/yHR/3CkoTw7mMekXsTGE2b9xaXFwZ91a9QfN8aj/yVD/h0dZa9f0b9ZYwrlMMaknxO/G+9DvH5MbZPda+LsrqKyQt3e89jlf18e87dL9d0nOlqXS0Ssya6KokpXYdm5wa9nNJZNZqx12eR0Mp8HXcJ/VOtskMPhtbrRaNnIeK20tXy/vqFOdA1DOiDRyKnaGN1Yoy7Pcn4tIJh1o96zKaaJTn1/m9bZrLMHOlMb0Jk7Y1F6KHolr/5nYojerqK3C9ITvU5Lve4DTYLWZ8yn/px/j/+O7HWCvmqzPgYsQ+t7vePkce76XhR0v6uvZ8+IfaVSJsVIb+yrM9tHG2x8HxCp57o+3aNvtuirlvX0mVIe85A+WpsfZ9JH5PJi+zq7rlAa7wM89VyVSdDPWfMac8P7wSn8n4w79IL9YF+tnBqwuyTfVVAUxLuP0eZw9Vy0PrNB1tHz7/57DEUb7Ne38QfE/qXSnyxC+mntLd5ovxwt4dnIIGjbT9fXfcPeAuFIB6lf/dFZq9O5OGvBolm5M7KyZacQV1l5SGvS29tUf+r/rirr4f8m9+tDaKN86wLpjs8tsJdru/AEv7eBTrfMQak6VaKfj/hXpG+OItz/PhnP55D6ary31vsfxEB5TymFPP/aRSZS5jnk/XF+j08gr6Y2WUWinrLS1w+nrKffJ+V1MxxCeaUmBi6vckdFi5ZVHPwmiLJ6q5GymuCX1+DLT19/Dssa/yVtqbMwE0Ymw+RA5SEfBUHUnygpk98MdNsj0aRc9GUlZeA01I9Uvf+2KS90P6ZycGrlYNmPxFmU3xio9mSy6lvk3eUrT1mE9Uz2/I6doH779fnHpSWP0togHAYHan3PxABlqevxQ2+P6ypUWVr0+06Lfr9K/7zSlecXg0zfNPL+5qj06kiFQzw+6Uxwm8rYUIdXG8qcKFLv5kpZHYyUbwJ5PuYhNsrqyKRAZcV985VXSHu9qfIK4XtU2pKuvPzfnYu6y3NG+pFFcIh2r08z2s9Oau4uN/j7y/3waxdFhnYRZ9EGElUY+uyFknddnTfYH3Oq2f5o7D8x2cp+usAQ6qeV/W+1kP3efvw9sf8o0gt5DhmO/TVTrex3lJWtqXSGhbC/mycP62R/N/WtpexPSPafj48xtJmGzp/aJpMq2W2ICxfDEdhee7rRdu2Tp3Gbu/vbvHK9sslsZ1wQdkoZ08GZ99qJwc68aQY7Pe80Ze6GGcS+M/IdocpYr7PKQudIdFZb63Tml+eXhPIepeqmcf8rC72jtPpkpdfdnrVG0Xy9RVFmvaO1ftBKr+xYiOIm653ubT8Wesegtz6wXs+Dv7DpeVbvrL3MumNTtNiBdTvLHMUF65uu2/uMrg+g29aA7nL7urKCfBcbKzVdv/d+Z/e21p9qrd9hzy+tdLZA/X5P9CYgUUgsMk5ry5Z67VW5hfmu/CC+zaVPsXiHCPyNltPHXAZxWluztAXRanwzysBb716z0BuvtbVAeuVVtzn9i1d3Vl+z7gStvVnplueV1s0E0582prvOQvd4rb3NaEA3RR7Meb+N1bu0fgHam6XudYz7r1zfnPL26j1ioTdRa2cN6M0tWNFkvd5n+5j+notjZPxhKPLHZNqZSS97Wa5pvH2F+7WvCj9dd4quM0m4K1wIk7R2ZNLFkFZQ7z4dIu+eSVzxrZV3YHTLu5qhjCcMkLPR5B1sFJKC/sxZRv3aaZqeZ3Uo+4Ba9SmH3O8unqT0tjwjtvRBTkZ6IxOxZYfZlmY/v6Nkn9aBye4wScs=
*/