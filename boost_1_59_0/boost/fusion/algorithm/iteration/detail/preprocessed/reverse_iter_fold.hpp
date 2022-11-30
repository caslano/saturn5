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
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
*/