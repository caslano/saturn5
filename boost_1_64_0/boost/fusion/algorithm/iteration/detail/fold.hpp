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
Qn1vUT3CMTf82v7NNfcCeSxzvRdYzjLXe4EFLHOdB36mY1mIbVkWy1znhk91LAt2vvb5+Gne4bPM/Tt89TvhZO27RO37EVUZOneL/pgwsQOu3Zgw2YH6Y8LkDvhrxoTpaUt7oDbtB5V7H3s8XJvnJEwzlyL93MPpjguT01I7Zssh1jUNNNrvRG6WPN8v564mDzj/dOfXvtBSmwefEJcwo7i4/V3fKC7q/Wa20u73U/ZrNtqv29/ZrfutJ/vtaCkHE2jGyatYl32f1tn3EfadZ7hvCr4H+zY67vIekoEItMf9eBfKm+F+meb9KvLb1rZqRx3ned7VeVG9jX5Z9BtkGCeGECpbfNyVxfUSlw6ERvKce5S4RBnGhR8TSnFcJC5GdYM8s2jjd5vEL7ytNq8+J365JcWPFnccQ/K9bPGUY1hied7VVv8cLjKOV1p6Ztni47zfiHbaery4K/+JNNqvUpl7Pq7Wa13d1+W2c+ugTlyOK/WYPS6aJnAJ3OJmJpai/Mx2jIelef/uHJfut2rH/fqKuOQYxqV0Y3/Z8n/Lrdrj/rVSjxnvh4rM8/S+YXD9CgvSngcnlfJmuN/SjTtGPmuOe05d/TqjOEhbZ3yr1F+DjeLCSVmKsj+7rmd1BvHTrTOy2mvz6p9KnWYYP1WlUaZ42uqMLnWN64yz7bVl53ulLishXlQaZYqP6hoYrD1Pz7Df3Yb7tVYapbnvfMODeiPYdi8QrM2HQ035zxBbfJSfs0t33hxsKvt3eYdq7qBN+2HWDVLtq/TpPdjUfXptcQjvZN3CnqrWc2U97q+rzJ1tG6dP+x73gpt3X8Xy7kt5bm9ene04Pbfzh+47Ul8v7Xh9fl6u4/VJOxXHmJbyzK9+Pr2B57uzHPNYSz+Uu0OsP+TTRUieP5Ncno+i7NvLsHz3R75rtn63k/N3lef0TI7Z7o7cE1Rh/QqO94uROM2kfdc0rZL6eTjase/2zmP6yTJKH/GXd4EB8k7PHgPJl1kGbQV2Y4HtuVHWXa19V2Gvo6ra8la+XyTfd247mGf/PpfH5Kn2d5KkVdIVY/9t1tfHmh/N6pgsfzeTv4feav37pMvfvSqp/57q8vcjldXb2+Sr/vczjr9Vddk+KdOdpY4NJoSSVrPlvKJA6PWCKMVvJJ2c+j6E2v+OV8UhsrN+HHZLHDpdwziUj+f43zmeo/64iv++cR6v9XiO3S3jOX5fccnXwUmP133sx+qH/vnNiENlG8/Rn0C/Rf05PmTcRVlP+hrqzxnSzWk9+ggabq+t03qxsr2mJWwvipAr622X9SpjuKz3ZAW6E+BTeAvmYWd8GifhP3AePoObcTXa4+lnnJ7uznONl5CeYOc5UPwkPSVsbx/hrKxHXzPWs97D7JL1mE+e1xssw27YEMfInMYzsLHMOX0jFmATXIv++L7MafwpNpe5r2/GiuwnEG/BltgeW+EIbC1zHLfFGdgOZ+KtmIsdcCuG4MvYCfdjZ5R00w/MOB+7Oo/XWUI+Bjrnt2yvqfH2aP8hfaakLxXrWb5bXfrmNvA25QRiQwzFJtgPb8J0DMC52AL/gS3xC2yN32AQNmVbwXgzdsbeGIoR2BMXYy9cj73xAPbBj7AvfovheAX7oS9xvA1rYX9sjBHYDAcq+8Gh2AVvx6E4DONwBM7CkTgXR+FzOBo34J24Ccei5CP9iYyPSxfn87CE43KT83kt22tawvbMhEJZ7wtZrxomyHqkPacR1sYOWBcTsQEmY0Ocg41wETbG17EJ7sWm+DH64xFsJudzrEn60eAc2W8VHCH7jWQ9fxyMoTgUozEKx+LtmIbD8G4cjjk4AmfiSNlPlkn6r+Aq2U91TJH9jJc=
*/