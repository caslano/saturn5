
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_SCOPE_DETAIL_DYNAMIC_HPP
#define BOOST_PHOENIX_SCOPE_DETAIL_DYNAMIC_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/scope/detail/cpp03/preprocessed/dynamic.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_SCOPE_DETAIL_DYNAMIC_HPP
#define BOOST_PHOENIX_SCOPE_DETAIL_DYNAMIC_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/dynamic_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_SCOPE_DYNAMIC_MEMBER(_, N, __)                            \
        typedef                                                                 \
            typename expression::dynamic_member<                                \
                mpl::int_<N>                                                    \
              , self_type *                                                     \
            >::type const                                                       \
            BOOST_PP_CAT(member, BOOST_PP_INC(N));                              \
/**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_DYNAMIC_LIMIT,                                        \
    <boost/phoenix/scope/detail/cpp03/dynamic.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef BOOST_PHOENIX_SCOPE_DYNAMIC_MEMBER

#endif

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#else

    template <BOOST_PHOENIX_typename_A>
    struct dynamic<BOOST_PHOENIX_A> : noncopyable
    {
        typedef
            BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)<BOOST_PHOENIX_A>
            tuple_type;
        typedef
            dynamic<BOOST_PHOENIX_A>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;

        dynamic()
            : frame(0) {}

        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type const
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }

        BOOST_PP_REPEAT(
            BOOST_PHOENIX_ITERATION
          , BOOST_PHOENIX_SCOPE_DYNAMIC_MEMBER
          , _
        )

        mutable dynamic_frame_type* frame;
    };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* dynamic.hpp
mmc+s8xzFyH+PtMGhtgOQplMOC4SSYidzmAksZGrhHoFloIGzzZiz/ZA+2xifMN85IpRWVHLm7AYU8BK81IljfSohIRt5bh6SGW7H3ZDMRxyxRMjGPbe2VuBsMaONFNXKKAWmNGKRLK1yZIElzfsfDhiCZ3BBX9r0UiUVubGJFqfSrjO2149wifc4FJQKIAQUcUiwPL+k9EaCEVJwBkul9jYp3Qisu0yOaP+rLPBYgHBe5del7BW0D+FteCXR7/uzsZtAOavIp0k2bj0HtlX+y6GjZmYv2qzLc5vjcbQpDmBlIsxS/NUpo9zPS7G1lOR8qZ+1mycRl80G+uoYTtvrvnNwjj6OSuArNvYnY9a5TTaWHsMDx/a2zew0WzCM8DHHVggtpZb4i1HvIVmgr+NqohhG+m3HP2VvfJY3+iRIY+0vWCJ6VzrUa6MTvMzmWLPzYuk+Xc+bTozN+c+bd7s0wyA23ziJRsiwaEuEiw4ypNpxuyAV3jt1Uu8yiZgw9ndmipvFSZjU7m666SnDlakM9XgmBlTVCPtRrD0XSmkmUqltuvbPOOny8E85Rc84WrmCML5PChSugjSU8jCgrxp09w9OmQtiFmis9SuoLi3o8lQxoSj61913LLF2AMLRgzVLATTIQobVkrju343
*/