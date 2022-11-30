
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
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
*/