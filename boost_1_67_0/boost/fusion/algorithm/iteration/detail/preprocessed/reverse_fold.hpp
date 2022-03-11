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