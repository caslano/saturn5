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
KwB14Ilo6ebrThgcdMLEdcLDjb0knn+I54voOr14k86vkzQeLUbxZXwepdM5AB78WX2fnoQ0k3XhenE/CByL7cUPRBYM50kQXV5ivh+fj9PocpGMzydRej2PQ5pMJ4t5PLsejSNm75DexzeLeHI2nl3E86t4kobBKEqjwyW3KTqfx/Hu9Syep05xSGdzbyIM9o60Y0hsuBxDzi3jZTqK3XZ3IYivovHlYjafpvGZcygYz5L4DPZHi+QGMbkKya+k15NJfNm9XcNUSOn4CrrS6GrmlGH7bHE9W0QzKPwQjxCJmOHYRsljrYXXYaS+if+++5Npumg3hHSF5wKHHP924xe3wp01GvwRLJnFgY1n+qNRKM9e6caTOz8o+9IUrh+3dG2DDlFVIZggMBU5GLqeujqATlthhj6K4g4sYtcbLq3/hXqj7kphG3dN6rb7gcq3KCB1jenlGCPTnawdnwbfUJjjZe/3I49mdcMtZd9ZNBT5f4F2z5vDZACjQOrV6NV+EpKL6MT9PX312j1/+PlH93x1crqLfBM0JWbCe+rVcoMm0/9q7l3hwtSNlTiuF3rgdMHbJbOqu6C5nsJUvptAzyLjpp743+MUQEM5JcFcIqxoVS/5DoV5ibcOqVs94d6NWdH1PX97aznU+eO0
*/