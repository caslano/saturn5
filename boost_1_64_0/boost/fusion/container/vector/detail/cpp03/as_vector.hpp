/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_VECTOR_09222005_0950)
#define FUSION_AS_VECTOR_09222005_0950

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size>
    struct as_vector
    {
        BOOST_STATIC_ASSERT_MSG(
            size <= FUSION_MAX_VECTOR_SIZE
          , "FUSION_MAX_VECTOR_SIZE limit is too low"
        );
    };

    template <>
    struct as_vector<0>
    {
        template <typename Iterator>
        struct apply
        {
            typedef vector0<> type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return vector0<>();
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/as_vector.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/as_vector" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
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

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

#define BOOST_FUSION_NEXT_ITERATOR(z, n, data)                                  \
    typedef typename fusion::result_of::next<BOOST_PP_CAT(I, n)>::type          \
        BOOST_PP_CAT(I, BOOST_PP_INC(n));

#define BOOST_FUSION_NEXT_CALL_ITERATOR(z, n, data)                             \
    typename gen::BOOST_PP_CAT(I, BOOST_PP_INC(n))                              \
        BOOST_PP_CAT(i, BOOST_PP_INC(n)) = fusion::next(BOOST_PP_CAT(i, n));

#define BOOST_FUSION_VALUE_OF_ITERATOR(z, n, data)                              \
    typedef typename fusion::result_of::value_of<BOOST_PP_CAT(I, n)>::type      \
        BOOST_PP_CAT(T, n);

#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/as_vector.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_NEXT_ITERATOR
#undef BOOST_FUSION_NEXT_CALL_ITERATOR
#undef BOOST_FUSION_VALUE_OF_ITERATOR

BOOST_FUSION_BARRIER_END
}}}

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

    template <>
    struct as_vector<N>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(N, BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_VALUE_OF_ITERATOR, _)
            typedef BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, T)> type;
        };

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_FUSION_NEXT_CALL_ITERATOR, _)
            return result(BOOST_PP_ENUM_PARAMS(N, *i));
        }
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* as_vector.hpp
TENf8mhBP0zHQMzAfpiJA/FGjMeZ6vFLzuW4WOf4FSXXBkdjFPbFgdgP52J/XIADcF99k9FPY/TTGP00v7N+mvj7fU2TiUKihNhHnCSabvU1hRFJhHWr0Y9jTMZkTMZkTMZkTMZkTMb0vzT9BuP/6eSqm77/Iofx/wHS9hlKSNutaUcX1l1u75eTS3Ttnf816L9sJv0luXKdrmMfJVUw23RA+ijLiYeZz/95521xdXKWbch+Da43qOo7LqjqB8zXri+4tYs2dr+TU/8RJZ2qzGvflMn9mm+XvjLb0IvZBTlWWz9RIJlVqvvXK9u15129fiFYuw7ApU+efhaSZYtqX1B41TMYpWwelPfhPiJcKZsXqsqmduMv1Hy49BOHSD96N+mHDSF2Mm+lth36m8xKhxMfTW63mF/9vRalL9bteg5/6et06NNXP3c7PeTD/0XnfGTPnsEwhkvLQxunPMiaXMoj2ls/H/Eu+VC6J6dZC/LSTZeWF+fyYG3qdfNSHpKPZkQDGRvzCMvnOuXDVhzcDSNvfqp1fu6l5sVxuyHSLz9FPncpxKPMW+y8XXX3U5UuRNluQDXbDXLfrvr+b2zgvr+PMa//foftyi0ffsl+Vr3PPtLnfxnRQLZbxrxmh+3J2IN86zTGx/yCbVaNE1ne0H0f/8y8Sc7blMOdcmtTNm0tyP8l264q37OybT/ZdlNiF/PmOm275vdvrW57lkYy/kQ+Ryvkc7RE2x4HwDROQ9np1hrcw0P6sl23px4vD8n2Fsg+FhCPM6/5QNX2ajeGzNPxMlv66C1EoPRDPsG8h7Xt5DsfL6s/R7ptU9Ji1fEarM1hHEFXk6TJeA3HcveXpsX7JX9biCeVz9hLTvmT42jNy90hby5j1GRN6jgCyZ+kSxadyrDMV78Mg152zqN6kKnB74zqy5C1uZUhaZJBx/wlNbav+H3J3zFiD+stdcpfhMN7fGnlWDUWw9vf+T1OquY9Piv56yDjldqgkr/yg075q5P32Nv/0t7jjU30y9D8qnMe1fe4Bvd8qb4Mtfc4ycN7PFjyF9rUvuJCuS9OPrFX+Z68puXP7fxai9+frr/7UrClLc1hdS552i152iF52krsY5nTDnlyPffW5jexa7mlOI4DcvmMxfnZVzBX8jKHeJblDx9yyIucjy/1vdO7D5Pr54iPtNvvsXLmz31dy8elnqdd8+I4VlBW51QmSc3sK8mQMplGvMA6Sp3zIufQX1YmzW1psiqX3xGHJB9j5dx6jZxbg/6q5kP9jDieZWtyXyX986w2XruVlGwLuT7cD/czb7G6bbW6VqOx0+MOs5xcG678vZC/XcdSu35uC/E2tS6nO0ZWPS507CLHKXWssn79q4XrmFqHcwVpcqyzj9tU6nyHeQ/8KQtlvlVvkGeHY2OZw1hhWcTtHmBL/PXvAWZ+s+7uAVY1rtCH/ytTL6lndycOMu9Up23lzs61VSlrvr1cdXvaWNQ+tjRlPRkFPBzeaZ9XN9e/F1npm7/uvcjOYtkl3N9Lf6yfpzGPtb8evrZj/X7t+3vV9j4C+mMnPY3x9DwGc8xcJf22xGvejWnWfegTH9/YruRD5b5u9jFT0vaEoUSJy5ipCBljGIldMQrt9+eXdiQ8IMs53p9/rhdjinAedsZCHIkLMR2LcBbehEtwMa7GJXgLLsPNeDNuxeX4EK7AvbgS9+FqLMc1aL9vl7ThSNtOict9u7rJ/nTH9tgDO2NPHICX4/XYC3MxDNdib7wPw1HulyZtOKyTKHG5X9pnzNcYP8cO+AWG4CltedpePC//uiz/V1n+DVn+sMPy8RdZ/itZ/rQs/y9Z/ozD2L5cWb6Zzvt+UJ5f8Ao=
*/