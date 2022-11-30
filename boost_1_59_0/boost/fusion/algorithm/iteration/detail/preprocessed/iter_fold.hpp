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
+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
*/