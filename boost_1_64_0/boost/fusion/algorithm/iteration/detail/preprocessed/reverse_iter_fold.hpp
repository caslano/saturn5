/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
# define BOOST_FUSION_FOLD_IMPL_ENABLER(T) void
# else
# define BOOST_FUSION_FOLD_IMPL_ENABLER(T) typename T::type
# endif
namespace boost { namespace fusion
{
    namespace detail
    {
        template<int SeqSize, typename It, typename State, typename F, typename = void
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          
          , bool = SeqSize == 0
# endif
        >
        struct result_of_it_reverse_iter_fold
        {};
        template<typename It, typename State, typename F>
        struct result_of_it_reverse_iter_fold<0,It,State,F
          , typename boost::enable_if_has_type<BOOST_FUSION_FOLD_IMPL_ENABLER(State)>::type
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          , true
# endif
          >
        {
            typedef typename State::type type;
        };
        template<int SeqSize, typename It, typename State, typename F>
        struct result_of_it_reverse_iter_fold<SeqSize,It,State,F
          , typename boost::enable_if_has_type<
# if BOOST_WORKAROUND (BOOST_MSVC, >= 1500)
                
                
                
                typename boost::disable_if_c<SeqSize == 0, State>::type::type
# else
                BOOST_FUSION_FOLD_IMPL_ENABLER(State)
# endif
            >::type
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          , false
# endif
          >
          : result_of_it_reverse_iter_fold<
                SeqSize-1
              , typename result_of::prior<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        It const&
                    )
                >
              , F
            >
        {};
        template<typename It, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of_it_reverse_iter_fold<
            0
          , It
          , State
          , F
        >::type
        it_reverse_iter_fold(mpl::int_<0>, It const&, typename State::type state, F&)
        {
            return state;
        }
        template<typename It, typename State, typename F, int SeqSize>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename lazy_enable_if_c<
            SeqSize != 0
          , result_of_it_reverse_iter_fold<
                SeqSize
              , It
              , State
              , F
            >
        >::type
        it_reverse_iter_fold(mpl::int_<SeqSize>, It const& it, typename State::type state, F& f)
        {
            return it_reverse_iter_fold<
                typename result_of::prior<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        It const&
                    )
                >
              , F
            >(
                mpl::int_<SeqSize-1>()
              , fusion::prior(it)
              , f(state, it)
              , f
            );
        }
        template<typename Seq, typename State, typename F
          , bool = traits::is_sequence<Seq>::value
          , bool = traits::is_segmented<Seq>::value>
        struct result_of_reverse_iter_fold
        {};
        template<typename Seq, typename State, typename F>
        struct result_of_reverse_iter_fold<Seq, State, F, true, false>
          : result_of_it_reverse_iter_fold<
                result_of::size<Seq>::value
              , typename fusion::result_of::prior< typename result_of::end<Seq>::type >::type
              , add_reference<State>
              , F
            >
        {};
        template<typename Seq, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of_reverse_iter_fold<Seq, State, F>::type
        reverse_iter_fold(Seq& seq, State& state, F& f)
        {
            return it_reverse_iter_fold<
                typename fusion::result_of::prior< typename result_of::end<Seq>::type >::type
              , add_reference<State>
              , F
            >(
                typename result_of::size<Seq>::type()
              , fusion::prior( fusion::end(seq) )
              , state
              , f
            );
        }
    }
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_iter_fold
          : detail::result_of_reverse_iter_fold<Seq, State, F>
        {};
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq
      , State const
      , F
    >::type
    reverse_iter_fold(Seq& seq, State const& state, F f)
    {
        return detail::reverse_iter_fold<Seq, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State const& state, F f)
    {
        return detail::reverse_iter_fold<Seq const, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq
      , State
      , F
    >::type
    reverse_iter_fold(Seq& seq, State& state, F f)
    {
        return detail::reverse_iter_fold<Seq, State, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State& state, F f)
    {
        return detail::reverse_iter_fold<Seq const, State, F>(seq, state, f);
    }
}}

/* reverse_iter_fold.hpp
DJyAETgVz8TpGIlZ2AdLsC+WYj+8FvvjHTgA12EUVmI0voIx+DoOxLdwEFZjHB7EeDyMQ/E42p+Ap+FwPB1H4Bk4EmMxCeNxjC1GJ9dxuc4ZP+dMrsXY0816XCP1n9MlzyPZ5ovl+WJ5x2gszxfHO7biePUVwzPl+5mCKXGUHEpZvi9W51v+f0tD/f6vHb2u3ACoh9//l/Q22cbA75Df4zsxCF/Bk2PY9kvaOQBmFmRnFmW7nx9dGf9/5sv28f/yq1wz/r+VjP9f2kf5tzVvWeZN1/xO184LIL8R1b/9vZwvwGluANvcCCXy+3uafA+cRGlBvwS/4twvMrdx7WY9fx6887Pfc9TzG+vOXyz7IXMeFzHzv3qu+0MObW4hbW5JPWXaNstPc8/Hcaj7yf7c/zaSp351Y9bFUnxEScZ8VVsnd0Lc9k87zp35r1nOnTkLC4vSZ+ZlZ+YvNJvkvJr0mu28smxVjneG03kVoawfY3nOfVG6eeb8fIPnw6v3zXZORTe3vjYzf5HDfSbOVfn7TPat0Pb8h9b2upSJLFT3vJZIH50jx2UqpQ3rR7yuO8+G22Miz3Ow7q9qTosTJW9+opy3YyntqKtCv6703Hz39VnOAQyofY7BwiL5m72flBR49XlRKu2Ilnb0pRzmH8E7Nff5eI6E+/PQus8/RaueYSH/nqHqgyM6Ywc60Afmnep7Vcp9Km/n0ggymB9+uc78/MGsW+5UZ13vjXHeae6NrTpNdW9M1Qctm2rHMXSmPdU67fF2Do0gD8YvWPulvKn+HBrBVUZzaHj33AJP5tCwtiUoUHtedOP1GYZt8e65Bb9Eq55boLp/WqHz/IBQ5dpsXLecJZ4/Q4O+0JwjgTHGc63EHqd/bKqqGm5+E2v/7DhOe7724vXNdhm1xftxNz08OG+PtXvLvvlW/hv3nOvr3vJFtfeWu6+NW/pazm2PPjdwzrSzXzh3i/v5VuT7Pr8DtPOtBMk93w4Ygh2xHwbjIOyMSdgFx2MIzsKuWIDd8DzsjqswFNdjGG7HHliFPfEtPAO/wAj8Ec/E3zES/8S+eDJt64fdsD+G4wCMxCgcidE4GmMwBc/CqRiLmTgIc9A6L0scLsd4vAOH4GocipswAV/EYfgKDreNO5HfBThNZ9xJpcxXsxU74TaMwhdwML6IQ/ElnITbHbZb5mK76+Se//3YDh+Q4/QghuFDcnwelu0+ItutaiTfz+V7O9ul72iXHO9Rst0kbI9jMATHYm8ch/1xAibiRByHKTgXJ2EhTsbzcQouxVS8AafKeTANH8Dp+CSeLefDTDyA2fgVzsIfcDYexhz81TpOijbPxVaYh30wH6NwPk7GBTgdz8Xz8AK8BC/CpXgxXoWX4E14KT6ES3EDXoHP4DJ8B6/CD/FqPIjX4Bd4LX6FZfgnXifPor8eA/EmDMFbsBeuwD54K/bD23A83o4TcSVOwlU4H+/GRXgPXoarsRTvs50v8psCz9E5X9bLcd0g5+HjGIlPYCw+iWPwKZyKm1GeuyC/HzjWOs8w3yXn9xvYEXdjN3wT++JbGIV7cCS+jWNxr+35H/K7AKNl+47P/9gh239Ntvc62uYb2mk8f9EfDuuVy3o93axXLeuFuVyPUuV6/iJZj++W0j4365V5uL0qD9drtkv2w2C9pP/A/ErNdnsej/LNseSbY8k3x5JvjiVXMa1e83m+CKWYsoKykbKXcoQSRAJULCWLUkqpoOyl+C/guSQLfLEv3+JbfItv8S2+5f+0HPX5/9KK0xUy6yH239l0YvPd/JCuDAgwNbZM3zU0cUJKevykVGKBC9KLiky1+QE5tfkBMhdeI/t9+Rbym/xANPVvUX4=
*/