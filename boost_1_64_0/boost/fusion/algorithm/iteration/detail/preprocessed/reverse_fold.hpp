/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt
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
        struct result_of_it_reverse_fold
        {};
        template<typename It, typename State, typename F>
        struct result_of_it_reverse_fold<0,It,State,F
          , typename boost::enable_if_has_type<BOOST_FUSION_FOLD_IMPL_ENABLER(State)>::type
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          , true
# endif
          >
        {
            typedef typename State::type type;
        };
        template<int SeqSize, typename It, typename State, typename F>
        struct result_of_it_reverse_fold<SeqSize,It,State,F
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
          : result_of_it_reverse_fold<
                SeqSize-1
              , typename result_of::prior<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        typename fusion::result_of::deref<It const>::type
                    )
                >
              , F
            >
        {};
        template<typename It, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of_it_reverse_fold<
            0
          , It
          , State
          , F
        >::type
        it_reverse_fold(mpl::int_<0>, It const&, typename State::type state, F&)
        {
            return state;
        }
        template<typename It, typename State, typename F, int SeqSize>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename lazy_enable_if_c<
            SeqSize != 0
          , result_of_it_reverse_fold<
                SeqSize
              , It
              , State
              , F
            >
        >::type
        it_reverse_fold(mpl::int_<SeqSize>, It const& it, typename State::type state, F& f)
        {
            return it_reverse_fold<
                typename result_of::prior<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        typename fusion::result_of::deref<It const>::type
                    )
                >
              , F
            >(
                mpl::int_<SeqSize-1>()
              , fusion::prior(it)
              , f(state, fusion::deref(it))
              , f
            );
        }
        template<typename Seq, typename State, typename F
          , bool = traits::is_sequence<Seq>::value
          , bool = traits::is_segmented<Seq>::value>
        struct result_of_reverse_fold
        {};
        template<typename Seq, typename State, typename F>
        struct result_of_reverse_fold<Seq, State, F, true, false>
          : result_of_it_reverse_fold<
                result_of::size<Seq>::value
              , typename fusion::result_of::prior< typename result_of::end<Seq>::type >::type
              , add_reference<State>
              , F
            >
        {};
        template<typename Seq, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of_reverse_fold<Seq, State, F>::type
        reverse_fold(Seq& seq, State& state, F& f)
        {
            return it_reverse_fold<
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
        struct reverse_fold
          : detail::result_of_reverse_fold<Seq, State, F>
        {};
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State const
      , F
    >::type
    reverse_fold(Seq& seq, State const& state, F f)
    {
        return detail::reverse_fold<Seq, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_fold(Seq const& seq, State const& state, F f)
    {
        return detail::reverse_fold<Seq const, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State
      , F
    >::type
    reverse_fold(Seq& seq, State& state, F f)
    {
        return detail::reverse_fold<Seq, State, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State
      , F
    >::type
    reverse_fold(Seq const& seq, State& state, F f)
    {
        return detail::reverse_fold<Seq const, State, F>(seq, state, f);
    }
}}

/* reverse_fold.hpp
JV7MiNYNNrq5kCWoKE7Z+ldXu3FfPd48eg9HE/Pt0fGhvQRIh/qxKv1DRAdMrSpObgSV5g14lA8v10w/i2aVS31Q+Uc0QB+ZXeEqAsuMky+oiwDJ7IMLrFa3kD4J/fElskS5HpwI9x36HCDlqHKYqH2/5j93fzyth3291e8PskCfBpEeOm18o9/GU9mnbJ6Cm2KqUKiwkWdS0nJ7HlrMgXi/tZ9hb+9ak2JmZ7dhg49JZnDz2Y+Rv5Fk6vMrctO2ZjZICrw7kyu2K0M3fRSVRSBPS4r7x2gfBltAI5bJN/75flaJhimScYkFAjIhILrozeqhei1tS56fNZGHXy66+pRdUGOQFh15w7AwCuYrR9/PfIGt1/K3wgR8jBlCHGrdfPXTAB+vg17u9OMH7Aqx1FANSOc09YX9csYjhPW1UirjD6iHwQaC1YakZ0aDFrg4mamLn4ThjRApwHMfQoZRWnG655CIWQK+wfli6mmK0diDm80s3ufD3BslUZ+vZVN0lGH6tZJzySa5mGc3CI3I8X8u/WkiDupcbvf18RgVIXUqG3+YS5D4xOMgYw==
*/