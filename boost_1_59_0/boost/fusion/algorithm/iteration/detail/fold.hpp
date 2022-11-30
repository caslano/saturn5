/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/preprocessor/cat.hpp>

#define FUSION_HASH #

#ifdef BOOST_FUSION_REVERSE_FOLD
#   ifdef BOOST_FUSION_ITER_FOLD
#       define BOOST_FUSION_FOLD_NAME reverse_iter_fold
#   else
#       define BOOST_FUSION_FOLD_NAME reverse_fold
#   endif

#   define BOOST_FUSION_FOLD_IMPL_FIRST_IT_FUNCTION end
#   define BOOST_FUSION_FOLD_IMPL_NEXT_IT_FUNCTION prior
#   define BOOST_FUSION_FOLD_IMPL_FIRST_IT_META_TRANSFORM(IT)                   \
        typename fusion::result_of::prior<IT>::type
#   define BOOST_FUSION_FOLD_IMPL_FIRST_IT_TRANSFORM(IT) fusion::prior(IT)
#else
#   ifdef BOOST_FUSION_ITER_FOLD
#       define BOOST_FUSION_FOLD_NAME iter_fold
#   else
#       define BOOST_FUSION_FOLD_NAME fold
#   endif

#   define BOOST_FUSION_FOLD_IMPL_FIRST_IT_FUNCTION begin
#   define BOOST_FUSION_FOLD_IMPL_NEXT_IT_FUNCTION next
#   define BOOST_FUSION_FOLD_IMPL_FIRST_IT_META_TRANSFORM(IT) IT
#   define BOOST_FUSION_FOLD_IMPL_FIRST_IT_TRANSFORM(IT) IT
#endif
#ifdef BOOST_FUSION_ITER_FOLD
#   define BOOST_FUSION_FOLD_IMPL_INVOKE_IT_META_TRANSFORM(IT) IT&
#   define BOOST_FUSION_FOLD_IMPL_INVOKE_IT_TRANSFORM(IT) IT
#else
#   define BOOST_FUSION_FOLD_IMPL_INVOKE_IT_META_TRANSFORM(IT)                  \
        typename fusion::result_of::deref<IT>::type
#   define BOOST_FUSION_FOLD_IMPL_INVOKE_IT_TRANSFORM(IT) fusion::deref(IT)
#endif

#if (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
FUSION_HASH if BOOST_WORKAROUND BOOST_PREVENT_MACRO_SUBSTITUTION (BOOST_MSVC, < 1500)
FUSION_HASH     define BOOST_FUSION_FOLD_IMPL_ENABLER(T) void
FUSION_HASH else
FUSION_HASH     define BOOST_FUSION_FOLD_IMPL_ENABLER(T) typename T::type
FUSION_HASH endif
#else
#   if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
#       define BOOST_FUSION_FOLD_IMPL_ENABLER(T) void
#   else
#       define BOOST_FUSION_FOLD_IMPL_ENABLER(T) typename T::type
#   endif
#endif

namespace boost { namespace fusion
{
    namespace detail
    {
        template<int SeqSize, typename It, typename State, typename F, typename = void
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if BOOST_WORKAROUND BOOST_PREVENT_MACRO_SUBSTITUTION (BOOST_MSVC, < 1500)
#endif
#if BOOST_WORKAROUND(BOOST_MSVC, < 1500) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
          // Dirty hack: those compilers cannot choose exactly one partial specialization.
          , bool = SeqSize == 0
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif
        >
        struct BOOST_PP_CAT(result_of_it_,BOOST_FUSION_FOLD_NAME)
        {};

        template<typename It, typename State, typename F>
        struct BOOST_PP_CAT(result_of_it_,BOOST_FUSION_FOLD_NAME)<0,It,State,F
          , typename boost::enable_if_has_type<BOOST_FUSION_FOLD_IMPL_ENABLER(State)>::type
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if BOOST_WORKAROUND BOOST_PREVENT_MACRO_SUBSTITUTION (BOOST_MSVC, < 1500)
#endif
#if BOOST_WORKAROUND(BOOST_MSVC, < 1500) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
          , true
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif
          >
        {
            typedef typename State::type type;
        };

        template<int SeqSize, typename It, typename State, typename F>
        struct BOOST_PP_CAT(result_of_it_,BOOST_FUSION_FOLD_NAME)<SeqSize,It,State,F
          , typename boost::enable_if_has_type<
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if BOOST_WORKAROUND BOOST_PREVENT_MACRO_SUBSTITUTION (BOOST_MSVC, >= 1500)
#endif
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1500) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
                // Following SFINAE enables to avoid MSVC 9's partial specialization
                // ambiguous bug but MSVC 8 don't compile, and moreover MSVC 8 style
                // workaround won't work with MSVC 9.
                typename boost::disable_if_c<SeqSize == 0, State>::type::type
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH else
                BOOST_FUSION_FOLD_IMPL_ENABLER(State)
#endif
#else
                BOOST_FUSION_FOLD_IMPL_ENABLER(State)
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif
            >::type
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if BOOST_WORKAROUND BOOST_PREVENT_MACRO_SUBSTITUTION (BOOST_MSVC, < 1500)
#endif
#if BOOST_WORKAROUND(BOOST_MSVC, < 1500) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
          , false
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif
          >
          : BOOST_PP_CAT(result_of_it_,BOOST_FUSION_FOLD_NAME)<
                SeqSize-1
              , typename result_of::BOOST_FUSION_FOLD_IMPL_NEXT_IT_FUNCTION<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        BOOST_FUSION_FOLD_IMPL_INVOKE_IT_META_TRANSFORM(It const)
                    )
                >
              , F
            >
        {};

        template<typename It, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename BOOST_PP_CAT(result_of_it_,BOOST_FUSION_FOLD_NAME)<
            0
          , It
          , State
          , F
        >::type
        BOOST_PP_CAT(it_,BOOST_FUSION_FOLD_NAME)(mpl::int_<0>, It const&, typename State::type state, F&)
        {
            return state;
        }

        template<typename It, typename State, typename F, int SeqSize>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename lazy_enable_if_c<
            SeqSize != 0
          , BOOST_PP_CAT(result_of_it_,BOOST_FUSION_FOLD_NAME)<
                SeqSize
              , It
              , State
              , F
            >
        >::type
        BOOST_PP_CAT(it_,BOOST_FUSION_FOLD_NAME)(mpl::int_<SeqSize>, It const& it, typename State::type state, F& f)
        {
            return BOOST_PP_CAT(it_,BOOST_FUSION_FOLD_NAME)<
                typename result_of::BOOST_FUSION_FOLD_IMPL_NEXT_IT_FUNCTION<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        BOOST_FUSION_FOLD_IMPL_INVOKE_IT_META_TRANSFORM(It const)
                    )
                >
              , F
            >(
                mpl::int_<SeqSize-1>()
              , fusion::BOOST_FUSION_FOLD_IMPL_NEXT_IT_FUNCTION(it)
              , f(state, BOOST_FUSION_FOLD_IMPL_INVOKE_IT_TRANSFORM(it))
              , f
            );
        }

        template<typename Seq, typename State, typename F
          , bool = traits::is_sequence<Seq>::value
          , bool = traits::is_segmented<Seq>::value>
        struct BOOST_PP_CAT(result_of_,BOOST_FUSION_FOLD_NAME)
        {};

        template<typename Seq, typename State, typename F>
        struct BOOST_PP_CAT(result_of_,BOOST_FUSION_FOLD_NAME)<Seq, State, F, true, false>
          : BOOST_PP_CAT(result_of_it_,BOOST_FUSION_FOLD_NAME)<
                result_of::size<Seq>::value
              , BOOST_FUSION_FOLD_IMPL_FIRST_IT_META_TRANSFORM(
                    typename result_of::BOOST_FUSION_FOLD_IMPL_FIRST_IT_FUNCTION<Seq>::type
                )
              , add_reference<State>
              , F
            >
        {};

        template<typename Seq, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename BOOST_PP_CAT(result_of_,BOOST_FUSION_FOLD_NAME)<Seq, State, F>::type
        BOOST_FUSION_FOLD_NAME(Seq& seq, State& state, F& f)
        {
            return BOOST_PP_CAT(it_,BOOST_FUSION_FOLD_NAME)<
                BOOST_FUSION_FOLD_IMPL_FIRST_IT_META_TRANSFORM(
                    typename result_of::BOOST_FUSION_FOLD_IMPL_FIRST_IT_FUNCTION<Seq>::type
                )
              , add_reference<State>
              , F
            >(
                typename result_of::size<Seq>::type()
              , BOOST_FUSION_FOLD_IMPL_FIRST_IT_TRANSFORM(
                    fusion::BOOST_FUSION_FOLD_IMPL_FIRST_IT_FUNCTION(seq)
                )
              , state
              , f
            );
        }
    }

    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct BOOST_FUSION_FOLD_NAME
          : detail::BOOST_PP_CAT(result_of_,BOOST_FUSION_FOLD_NAME)<Seq, State, F>
        {};
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::BOOST_FUSION_FOLD_NAME<
        Seq
      , State const
      , F
    >::type
    BOOST_FUSION_FOLD_NAME(Seq& seq, State const& state, F f)
    {
        return detail::BOOST_FUSION_FOLD_NAME<Seq, State const, F>(seq, state, f);
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::BOOST_FUSION_FOLD_NAME<
        Seq const
      , State const
      , F
    >::type
    BOOST_FUSION_FOLD_NAME(Seq const& seq, State const& state, F f)
    {
        return detail::BOOST_FUSION_FOLD_NAME<Seq const, State const, F>(seq, state, f);
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::BOOST_FUSION_FOLD_NAME<
        Seq
      , State
      , F
    >::type
    BOOST_FUSION_FOLD_NAME(Seq& seq, State& state, F f)
    {
        return detail::BOOST_FUSION_FOLD_NAME<Seq, State, F>(seq, state, f);
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::BOOST_FUSION_FOLD_NAME<
        Seq const
      , State
      , F
    >::type
    BOOST_FUSION_FOLD_NAME(Seq const& seq, State& state, F f)
    {
        return detail::BOOST_FUSION_FOLD_NAME<Seq const, State, F>(seq, state, f);
    }
}}

#undef BOOST_FUSION_FOLD_NAME
#undef BOOST_FUSION_FOLD_IMPL_ENABLER
#undef BOOST_FUSION_FOLD_IMPL_FIRST_IT_FUNCTION
#undef BOOST_FUSION_FOLD_IMPL_NEXT_IT_FUNCTION
#undef BOOST_FUSION_FOLD_IMPL_FIRST_IT_META_TRANSFORM
#undef BOOST_FUSION_FOLD_IMPL_FIRST_IT_TRANSFORM
#undef BOOST_FUSION_FOLD_IMPL_INVOKE_IT_META_TRANSFORM
#undef BOOST_FUSION_FOLD_IMPL_INVOKE_IT_TRANSFORM
#undef FUSION_HASH

/* fold.hpp
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
*/