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
Qh0FGipt+4YtJGJf83yLDYUa/4pUqJhZn3ijadDwlchH5SkrdkklJTi9FvlWLGuxPGfcCes1Rc+WIGqUbHQ/RrTxsOEZhSMoroBXYskIsHYtTDMqZG6yR/ssKjrceNa9ldo7Phmugo0nUKVhu5309T9emroDZ66Pu1pZYAiS8kktkSCPAPELFtzJJuqBqix3rgZqIYFzOysxI7foqQoRH4xGRlecBuRtJT5uxC8Ru0jHLPZ1w/d76yYSS4pHzVvzFf0yizOPwlXpVYNfK7B6zfv7NZpeltqY23UVcGoPCPEG03CYpYTcSBBnRVRxlUXR5ii+jEnJQeh8nrNfhvgs8FXlncBhLgGAEmR3xNijfAXgUvbPe4enR+0GBuA1g0and9R50+nTRxDMKdDa+W6Xv+OfP2sJXOC22vvYbNatqFDhpBMO0cZofqS7FbRLzfv4oNfHQEA169I6UI28EWzgWdP4j2h8QdqEgBHjAO1Mx4v84e8UosShZjhsS7moT6JEh6iATEUYnyUx7NKy21lsdQMakZSFi3EXrCCXekOtHJn78kmR5nGDwq0nDR6ffd12d5ouzlJiqA15Qjy+VYdU/k+LHGDnP9ZpX9ESNtmRaWw5hy4a3o4tYPkFGGftu2NA8h+ibmRdYyW9Jppo
*/