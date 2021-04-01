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
NGLBIaozaywH4BRhfN9OkdYP8zO39SnnI9gB7q4QyrXre9waYa0AOKYiSA7FV6yGJXPOV7FrAsZq7VNfdjlRbhmhddZ761LVvL+JByl7X7JKvhhzOytxaCwdu0LxHM9/okIAHSC1oAUauq+sNOfwWB7JDHSc5mcjo1Ivey29kYj3cSq59ELRPXHW4e/sfv1RFvWB8J89s5+tdU9uFDCjEB5QtHqMucNedeaIMvmgqWrzDu+DzlssrFzd+u2xzbeL2+bJGkiXDZzZH5kxPOTr+TYl2T1GtVhTQpCXHOc0/hAtXjQWu3qZc/jlTv5MRb8zopUOV7gBXK6ZhCALj5ITWt2LQb4vRVkISQJihK6be+r1AUrA6eR/TlrsJIPc9lt5XPaNR3Aepi4EsTgGqzW1uf3JE4r54/hKtXFAJVuYeM8WrCekmEg1phpeUi8yK0L3iemTPl/QlE0Cl/PNte/PF+LxcL4PUefoDogpx1r23ajowa4gHRM8MgkHr1NBsbMnkpY8g0mCXSqwIdV2gkbqMxQfQJ/fPmB5fB3x+XP50zt7j451sBaeZ0GoJg==
*/