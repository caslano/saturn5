/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PP_IS_ITERATING

#if !defined(BOOST_FUSION_NVIEW_IMPL_SEP_23_2009_1017PM)
#define BOOST_FUSION_NVIEW_IMPL_SEP_23_2009_1017PM

#include <climits>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (1, FUSION_MAX_VECTOR_SIZE,                                           \
    "boost/fusion/view/nview/detail/cpp03/nview_impl.hpp"))                   \
    /**/

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion { namespace result_of
{
    template <typename Sequence
      , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(FUSION_MAX_VECTOR_SIZE, int I, INT_MAX)>
    struct as_nview
    {
        typedef mpl::vector_c<
            int, BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, I)
        > index_type;
        typedef nview<Sequence, index_type> type;
    };
}}}

#include BOOST_PP_ITERATE()

#endif

///////////////////////////////////////////////////////////////////////////////
//  Preprocessor vertical repetition code
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

#if N < FUSION_MAX_VECTOR_SIZE
namespace boost { namespace fusion { namespace result_of
{
    template <typename Sequence, BOOST_PP_ENUM_PARAMS(N, int I)>
    struct as_nview<Sequence, BOOST_PP_ENUM_PARAMS(N, I)>
    {
        typedef mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> index_type;
        typedef nview<Sequence, index_type> type;
    };
}}}
#endif

namespace boost { namespace fusion
{
    template<BOOST_PP_ENUM_PARAMS(N, int I), typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline nview<Sequence, mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> >
    as_nview(Sequence& s)
    {
        typedef mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> index_type;
        return nview<Sequence, index_type>(s);
    }

}}

#undef N

#endif

/* nview_impl.hpp
K0lUB/Y+VHiLqN7yk7vYVV/rQFScdZY+b47WCRIVhRFYhXdDkrtrTt+7Gqdn1RlOqEIqzSjhBJPIwmYVWEeHlK0ol6HS6ST825PUOmFGEPFRKxMsslH63nG7J8veduqT6GdxUgBvSDcLIAN7Id4ng/jorAdU9uV3Qjdflt1s19Yy1CwebhCCRwBkeC4EUIPN0k0hvDBisUAJQU+xRQpHJiyZSufOfLXbNK54ZokJKmlkP8mN2UQ1HvUB1kknEBn2kzpvGKPvWkMHR12Jro8Grl/cJHFWjYe2hQnpJelI5Al97iB9L0RgO5AA04HO5R6lHqfsHBCaZ/uclDzEEAqbyhQWRGemS+z3lSNAVvI3ih0IIQGvAztNArdExzqT1IGmUPPX75e5a5eR6P65H82bWaPE9+z4xpjVCfh/RSWs343YVXEuN/dqcxzmHbN1La6MhsYA5jE0d52w/VoN9aX/bMV9Np8/h37Elt5cpAxFEfOKEbdluW1YC746IZ6uiC3Fj2bgkV3gfV1O+Mr7OAbUpdXUJxGOZGvF8erGiK5nvtnSYfJnnm1L6HHE+Q==
*/