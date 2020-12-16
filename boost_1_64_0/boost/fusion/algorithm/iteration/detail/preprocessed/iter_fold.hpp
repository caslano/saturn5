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
        struct result_of_it_iter_fold
        {};
        template<typename It, typename State, typename F>
        struct result_of_it_iter_fold<0,It,State,F
          , typename boost::enable_if_has_type<BOOST_FUSION_FOLD_IMPL_ENABLER(State)>::type
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          , true
# endif
          >
        {
            typedef typename State::type type;
        };
        template<int SeqSize, typename It, typename State, typename F>
        struct result_of_it_iter_fold<SeqSize,It,State,F
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
          : result_of_it_iter_fold<
                SeqSize-1
              , typename result_of::next<It>::type
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
        inline typename result_of_it_iter_fold<
            0
          , It
          , State
          , F
        >::type
        it_iter_fold(mpl::int_<0>, It const&, typename State::type state, F&)
        {
            return state;
        }
        template<typename It, typename State, typename F, int SeqSize>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename lazy_enable_if_c<
            SeqSize != 0
          , result_of_it_iter_fold<
                SeqSize
              , It
              , State
              , F
            >
        >::type
        it_iter_fold(mpl::int_<SeqSize>, It const& it, typename State::type state, F& f)
        {
            return it_iter_fold<
                typename result_of::next<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        It const&
                    )
                >
              , F
            >(
                mpl::int_<SeqSize-1>()
              , fusion::next(it)
              , f(state, it)
              , f
            );
        }
        template<typename Seq, typename State, typename F
          , bool = traits::is_sequence<Seq>::value
          , bool = traits::is_segmented<Seq>::value>
        struct result_of_iter_fold
        {};
        template<typename Seq, typename State, typename F>
        struct result_of_iter_fold<Seq, State, F, true, false>
          : result_of_it_iter_fold<
                result_of::size<Seq>::value
              , typename result_of::begin<Seq>::type
              , add_reference<State>
              , F
            >
        {};
        template<typename Seq, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of_iter_fold<Seq, State, F>::type
        iter_fold(Seq& seq, State& state, F& f)
        {
            return it_iter_fold<
                typename result_of::begin<Seq>::type
              , add_reference<State>
              , F
            >(
                typename result_of::size<Seq>::type()
              , fusion::begin(seq)
              , state
              , f
            );
        }
    }
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct iter_fold
          : detail::result_of_iter_fold<Seq, State, F>
        {};
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State const
      , F
    >::type
    iter_fold(Seq& seq, State const& state, F f)
    {
        return detail::iter_fold<Seq, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State const
      , F
    >::type
    iter_fold(Seq const& seq, State const& state, F f)
    {
        return detail::iter_fold<Seq const, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State
      , F
    >::type
    iter_fold(Seq& seq, State& state, F f)
    {
        return detail::iter_fold<Seq, State, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State
      , F
    >::type
    iter_fold(Seq const& seq, State& state, F f)
    {
        return detail::iter_fold<Seq const, State, F>(seq, state, f);
    }
}}

/* iter_fold.hpp
1f90XvWhdn71kltd17xqb3OqtbnUznnUnudQe5I/LbnTmrzpoPZ+XuVOL5/pR/60c+503fKmjXKml0Tac6VTaZ/kS0uudP3kSRvlSBdRnzpP2rMc6b+TH712pl+95kjr5Udvow57jvTfz4+uZnvKBFghlDhKFqWUUkF5j+KfTa40JZVSQnmQ8iZFmSQrlJJMyaOUUh6kVFGOUEJmsz1KKqWIspKymVI9+7+fa+xbfItv+XctDZX/T/Sq3vL/7+eHT3/JUS+T79lZ2AnTMVXJudtX+528NmFBSbTyPN+rSfOh71nyNmpTyGUAgFEexAidPIpkidk5P3s8FTW5Vtr4nm3fkuWex02UIPmNmEb9Fe857BtZtJadc79v1n2YZt8H23Mgt2jaq8kh8zg+GS5x1W3S/sGU1pQYyu/KXODv17afF9TOvO02P/9k6/Pn1fNuy79nqJ8RKx+jHSgnUdpKDm6lpU5JnLJWreTfuh8f4HhMbpTth1NaUMJMMu5Au30SVt0/f9Z47IE8399f7nPLOfAS5Rz2J+ID5/osGRne5JjIeXBunsP5uUWTH4jW+Ln2HLA98+zP2vdAsW1sSUBzdZ6a8/iGan/9MRUR+4/emIqcJvpjKjL2N8yYCluecBNtnni6kqe632gcQd3yxNN0cvJDlPeCYT3e5Ubbx0+o8gJ1c/IP6o8P4ERo+PEBWTrjA2by+jjjttD/7s8/ax7lHy6e9fJeU/3cfXP10cndt9abE6jf/+XVDZ8nfzhQP0++urqh8+RlnJvk7adJ30yhZPP64A/t+T/KyUhKo9vnpUoelGZsXrHOZ2kc/h5du57tOupvuSbLdwNtmw/hikZGOS9GOT5GuSRGuR5GOTJGORre58jo5wQZ5cgY5bYY5QQZ5TQZ5UZ5n4u0Jkr5++a9e44ftevtXxqtX3wgoEsg/Wy5JyzfP+V7aUkj9T3heJkXMgEHYiIm4jBMwuE4FUfgbByJ83EULsHRWIZJeBOOwXtwLN6LyfgojsdncQK+ihOxClPwM5yEn+NU/A6n4e84HU+grWnYGs/GtngORmA6RuIMjMGZmITZOBFz8GzMxXScg5Z5iuW7K9Ju+kU9T3GExPb6YAL2xenYD+dif7wcB+ByjMZrMEb6Q+YDZTvyHRMHSz2O84a0UPYLT8UYbGl7nXxPxA46r2vNn07CNtgWKfI6+f6H4TqvmyfzmudjGHIsZd5h+R6HO+R1jvMOF0t/XCCvuxhH4CWYjiUyj+hinINL8Hq8HNfhUtyMV+BWLMUXcBm+hFc55qjst+VOsBjnxmTIemFu1iuX9VrXnsfGOS+Vsl5PN+uZqu3rJTdykaNSLfvhZj2zh+uVe1hvtawX5mK9VJN8pmCaHG/HWNrpcl52xk7YBXtiVxyE3TARu+NIDMMp2BO3+ZnqJZ6ijqVo4yiBg/TiJwaxE1WspH7iJBIjUcVH1LERdVxkRJwqFqIbB9lGUcU+NHEPbcxDG+9Qxzoqz3Uf37DHNlzHNd48TxvP6EXJktiFxC0c4hXexSm0MQqj+IQmJiHxCHUs4uAipxiEl7EHV7GGJFuM4ejMvyKxBYknqGMJ2viBY+wAL6J9Odz3pyynrKZspxykBOYynwklmXIhZTVlB+UQJYgHaiRQ8ub4YgC+xbf4Ft/iW3yLb/EtvsW3+Jajt/hT5jRA/J8ZAZTw/9+O/a/ubbLNT1ch91ObyrjdxjhWiY2+7RgbVcYnWx7kTxvMbNBtfFTJATiy1z53g7xOnldumyPAFjNtHSNzHhRKTN/lHA25OmO57XGL5qfJthziFie2sY2zVsUzoxprYzrTwrmn9o5ePFMJ53geP/mjtTZ+EtBcP54=
*/