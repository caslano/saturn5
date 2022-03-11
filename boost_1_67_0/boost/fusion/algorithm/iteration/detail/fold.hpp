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