/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

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
        struct result_of_it_fold
        {};
        template<typename It, typename State, typename F>
        struct result_of_it_fold<0,It,State,F
          , typename boost::enable_if_has_type<BOOST_FUSION_FOLD_IMPL_ENABLER(State)>::type
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          , true
# endif
          >
        {
            typedef typename State::type type;
        };
        template<int SeqSize, typename It, typename State, typename F>
        struct result_of_it_fold<SeqSize,It,State,F
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
          : result_of_it_fold<
                SeqSize-1
              , typename result_of::next<It>::type
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
        inline typename result_of_it_fold<
            0
          , It
          , State
          , F
        >::type
        it_fold(mpl::int_<0>, It const&, typename State::type state, F&)
        {
            return state;
        }
        template<typename It, typename State, typename F, int SeqSize>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename lazy_enable_if_c<
            SeqSize != 0
          , result_of_it_fold<
                SeqSize
              , It
              , State
              , F
            >
        >::type
        it_fold(mpl::int_<SeqSize>, It const& it, typename State::type state, F& f)
        {
            return it_fold<
                typename result_of::next<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        typename fusion::result_of::deref<It const>::type
                    )
                >
              , F
            >(
                mpl::int_<SeqSize-1>()
              , fusion::next(it)
              , f(state, fusion::deref(it))
              , f
            );
        }
        template<typename Seq, typename State, typename F
          , bool = traits::is_sequence<Seq>::value
          , bool = traits::is_segmented<Seq>::value>
        struct result_of_fold
        {};
        template<typename Seq, typename State, typename F>
        struct result_of_fold<Seq, State, F, true, false>
          : result_of_it_fold<
                result_of::size<Seq>::value
              , typename result_of::begin<Seq>::type
              , add_reference<State>
              , F
            >
        {};
        template<typename Seq, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of_fold<Seq, State, F>::type
        fold(Seq& seq, State& state, F& f)
        {
            return it_fold<
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
        struct fold
          : detail::result_of_fold<Seq, State, F>
        {};
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq
      , State const
      , F
    >::type
    fold(Seq& seq, State const& state, F f)
    {
        return detail::fold<Seq, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq const
      , State const
      , F
    >::type
    fold(Seq const& seq, State const& state, F f)
    {
        return detail::fold<Seq const, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq
      , State
      , F
    >::type
    fold(Seq& seq, State& state, F f)
    {
        return detail::fold<Seq, State, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq const
      , State
      , F
    >::type
    fold(Seq const& seq, State& state, F f)
    {
        return detail::fold<Seq const, State, F>(seq, state, f);
    }
}}

/* fold.hpp
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
*/