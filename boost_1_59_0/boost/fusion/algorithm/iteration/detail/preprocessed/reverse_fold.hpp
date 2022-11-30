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
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
*/