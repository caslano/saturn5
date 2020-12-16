/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_MAKE_DEQUE_07162005_0243)
#define FUSION_MAKE_PP_DEQUE_07162005_0243

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/deque/deque.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_deque.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_deque" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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
    struct void_;

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_DEQUE_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct make_deque;

        template <>
        struct make_deque<>
        {
            typedef deque<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<>
    make_deque()
    {
        return deque<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_deque.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
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

    namespace result_of
    {
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct make_deque< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_DEQUE_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef deque<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_deque(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return deque<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_deque.hpp
irbrROm7hDeQtNeJ3al/E4zEzhiF9ngMVfK+9fI+dTyGJvK+FvK+UOyOLbEntsJB2BqHYhhOwDZ4E7bFdGyHs7E9FmIHLMGOuBo7SX1MAdJnCHOlPvUxTuoToZw3sTt2wEiMxB6Ygj1xBkZjDv4Gbe1Dshi3TxfZzq6ynd2kPmYlyft2yfvU8SEms15TnIrd8CZpj9/iaEzFsZiGBZiJWzALt+F03I4z8HHMVpVrKjQud7iUO1LKHSXljpZyE6TcMVLuOCl3vJSbJOUmS7kTpNzg2o4+N7xmK1fJtw4qy7ZA235/BPthBQ7DJ3AM7sTZuAvn4B58EPfiC7gPj+LT+AEewGp8BpVz1rMYg8/hAHwek/EFnIovYjEexjvwCG7Go/gAnsC9+Co+ha/hYXwdX8a/YhWewg/xNH6Pb2NjtvEdbIkfYAyewQH4ISbgR5iMH2MRfoq34Of4KH6Br+CX+BZ+hafxHNbigPsG6+F32AZ/wM54HhPw75iMP+JkvIAW/Ann4b+wFGuzv7ZiIO7BOngQ6+ILWA8P4xV4Dhvg3/FKbMl+bYgdsBF2wquxO16DffBaHIDXyXGRFiD9bTBVjscrMDlAnhfJ5zIEm2Nz7IahGIftMAHbYyJ2xIkYjlOwqzPOkPSbsd2fTtHEGSqS+13zMBwXYDQuxAS8BZNwEeZjMc7DxXg33oYb8XYswzvwISzBE7gcP8I78Z94FwYp31/YGldiJ1yFXfFuHI6laMLVmIxrcCKuwxtxPabhRszC36u+T6Q/DP1k3L9Ppsl15AyMxWxMwhycizfjrZiHG9GMB3A2PosFeBotEjekEOvgPLwe52MzXIitkGNZvi+lfwuOd/u+RDlf9sYIjMHB2AfHYF/ZvnhSteRjkXzqYX/JZ5LE15mMffBGjMWpOBxvwjxMxXMYXEv6jUh/khSS8kiIbWKxxaNpg6uwC96NPfEe7IdrMQHXYTKux9/iBpyJG3E2bsIHcTO+gPfjUXwQ/4lbMJAyH8LWuA07YTmOxu1owsdwKT6Oq/CPuBMrcDfuwv34JL6He/BL3It/xz9hoHK9jA1wP7bBg9gBn0FpF3vfEe5ladvFFi8pFKdgB7wRI3Aq9sabcBCm4XichlMwA9MxC/NxOs7HGbgYc/BuvBnX4ix8HnPxU8zDLzFf7gcXYHMsxF44FwdiEU7DeZiJC6W9bsFSXITlWMz/nsDb8Cm8A5/DpXgKl+E7uFwdH+YOR1wa9o9xnJsqWS+8xvVIS7X56cfDMcl64R7WK1XlFxJgHOem0p5fzevRCI78uH/qut4kdfwaWa+ph/VMXuZXLOt19bBepZfrWZ85Q08P68XKeuEG60XX9S4Oz74891g8U82u8XjMZt5DUsflqcPJNpRkj80TO1s/Pk/mbOMYPSv4b+WkEySJ18OHhnVJRfy7PRrF7onPd8bvWZjvGsOnjL/3kU6SLpD6F1Bvkja2T0mB63yvFQXuc76GWGyxfWIxk6SO8bPQQj4kbayfHbx2Ho+hNubPWYv+nLChhe7zwmby2klciGtJF7qTN4YMJm+0xf8hzXHGAOo/h/++jbZEezygJfx7E8keF6hyjjM2UMBcz/GB+rNOMulsJHmhPUbQprnucYLe4LWGUeSDnYfyehHydzfUixmUXORb3KANrH+SVE1SxxAKmWeLI2RC+xy0mfNssYTWzru4uWgPzfM8H+0n8zzHE4qe74wpZJpPPUjlpHj+rkS9+EJn5nsfY6jhAlucoW5ojTOEyViEpSR7zKHd/Hs/nkRt7KHQhbb4Q9GK/J2CC0mN43kvquMR7ebvWDyNxCXiC8sZm6g9/07htXhUxygq4m91nKIK/u42rm4=
*/