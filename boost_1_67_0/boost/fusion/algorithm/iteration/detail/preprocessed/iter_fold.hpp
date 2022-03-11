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
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
*/