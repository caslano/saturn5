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