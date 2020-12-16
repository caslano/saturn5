/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAKE_TUPLE_10032005_0843)
#define FUSION_MAKE_TUPLE_10032005_0843

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/fusion/tuple/detail/tuple.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    BOOST_FUSION_GPU_ENABLED inline tuple<>
    make_tuple()
    {
        return tuple<>();
    }
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/make_tuple.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_tuple" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/tuple/detail/make_tuple.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_AS_FUSION_ELEMENT

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_tuple(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return tuple<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* make_tuple.hpp
L8HeN2z01zaXZLqwnH5RYTdkQZjpTQ833/vuad85xUWfZ2U/yLHN/0thWn4fZS8+AulK+JOr75Dh+L0t3OD/qsKNbdsgPhO/t9hz3Se/YYr0OX6QRYnjlnfa50jf/RbwnQvKx8uLsMb9tVUor7pP+POF5rt8vrQvO8ZeRX8b8DHk60tnO4YWAZfjNn2KUHRZTSQ71BXw1W+BdlWUfn76dNpPRd8rnDRVTts5FfbqPuJzILtx5k2bfCr48M9M6N5D1uPGR++fJLS60Br6FUpf2exXFfzJur1PddD740249pf4jMPTBAcO1fBtlCYbG/ppbw+hSacpL/66BCS0ke0lmK3B+ubFgVFn/qPotWnnN7BdvW+f/E5MJr5nYX+bDuxY534o6bJNNckfrMHDBGb7L+9jYSoXge3yF910+WtVyIasN9/Xxg7ks1NIv9miyzqEbQz26G36BdMFYLp+3cKhS0JdZw8gpikaoz3+oU3fWe8PtwfrY8S86v42Bt0W2vw7G0PdFtozeoDENW2qTjrq+h3SZVtV1CqnDV+/+EDAKB8kcaoqIO0mpcluCG28fFDSyEiq6t13aF/whzZO5grKOfOgNn20OdJJwbTc6MLtjFdNzOhQG3NxaW1nYLSbr8LPpye0V7mwvj1cJ2MkMdGmg/d4rYlZm+zArED8p5Hue6YkZkWOsrY3+6/dgZM7G6ZPn5uWdNSPef5V9b3CV3pRJpzpMGggVUpXdL0nZsxNYMChGkp/DHbX85PrL5Lzk9rZN4gtyZvruSDpL3yWO0UZRTy97f4C5DKZHiO/PzXBT728XCz664P1lZ0R0tYmDBqYAzQsp2dOUtoGEI0ygM4C6FgG53bOz8Jr5IAzMTcIBujyXrNZ6JsRI88HUYyUMQvi0Neq8wcmBhJR98PYX+wz6XKoB7NLpEuf2qKP7jLov7PpGzBWNOrKpftIOo4h0fZ/qe9d5Unz/5MoW3UzOJe9tK+pL9Ktbmw2tH+ZtDecl0rQnq/BzycMe3DcPQHf0Z6KJ9drHBen6LqWVwo3dLLbr1fnh2ocYqTr4xNBVJ7ur8NFqmjD9AT5Lj0nto+ZqSZNAfSofG1zrPwlnhOm9GC4Nd4OhmuDlzUYZmHywSUNadYPMO/Qj21r2j0GbR1c8eZy8ybG14w8OjYvhB8lYREwOY8/eUz9eZQn8v/WvclXTb7jruv5YZnGrM1hxIN92yyP2SDL/CJ1Iyb18KSOQ38kjK+eB+Orl0X58dl+EOVe33MWnZcpP9ZNU9+f/8xm3OZFp/p88UxPynoBfE9LWxr1zR+bMDlhxcZoJ+mETYdp7ErTTtamJR3rpbLlF0+FPmbxNMRG93mRL/pnFpu2/w3ZdrWPubQ9lqA69g7sPfCgJz8BylLlExxoXNpZ2+4PLwKLou19IpQloS1JItr6Z/j5qJYtBe9syDBm1P2fiU56f7S0gjK+NmVhlAS0H7bqLDpKwD4R1rIkpmpFpp6tpTeQfPiIlgP7AEY+YPtdJe03Zdx3nDxOb7tfkI2R1WP2P0GZbC4rNed1Xfo3fCu4S8rpsYZ9H0b7KsalpRW0f3GyRdeDehyz/7CNUSs//eXtS2af8b6pNm5loFKBmO/tIRiSX9g/7W9j4FDscLza6PpdG1N7aEw7xIG3MRuDpux+fd82HXweqYvsQBuzvXQBxxW/VnQg9M+BP3pdfw12pM9vN2OSa/en9EubW0h78wM0bWVz59waGcscfKCmrW1uvg6mxWtNW/010ja232iMP2asehbGseOkfnKn9UzOK48/Gtr3jpQH06P+HNw2U9W1P0JdC3lG6pqsl3+D78vbW/I76f9/KNdUdP5dWF6369/nJig=
*/