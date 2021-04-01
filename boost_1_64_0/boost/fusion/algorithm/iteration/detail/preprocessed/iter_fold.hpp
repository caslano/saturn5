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
tYPbLJGytsGb/roQx5mynnGRugGDuOJMeBuMZ/yWFriAolPfkpE+7VUhUNvZohBW8+WkCVz42Hb0DRRa5Y8aC/d4VK/ok+9y5OL8mOQAI5kYUZ6eKILwdQr/UgXoZT0ne0WMDbRkROjGsDeQj28Ni0IXj7lmFdbdYmIKiY5sFciOgG83K8iJnwJY3ZExnyoNach40L5+5dgJ2v5JRzRypbhWHwaSQJmKW4JvcSBr2/RLnu9e0sN57Ssf05rfTUSlH4NONxLDpy62HPMzLxxC72CW9hER+8JcS++Emg3P7b3XFcd9vIdCrCn3jt0NfgK4Iquf6EPsddsF630gx5gBFi94jy4yP1PUujSFGPH4Z0wHkZwXqk4YVAu2wTcXjuqdO/jZByxPbtM7NX4bpoekCxuLrTw04RZA/76DINLpGKnWFaR35CZRoTVs7EB0RFR/V4m3D0l1/+btueDXg9uDPGsO2hQxSaIYs+7Hw3knxLOYd5YB9XfBJN2i8HhvYUmQcLvmnI5wjm3o2Tn4Mc2kWscBSBjqvwxdbkKeOgp3LYVmNVoJ1f0W5sJGwg==
*/