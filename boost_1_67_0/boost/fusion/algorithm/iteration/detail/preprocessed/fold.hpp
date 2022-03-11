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