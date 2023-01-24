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
4mQ49JZiIjrtDvJpN30VnXYms3aTnhmiV5LCeiX8vDSV49Tys4rTz+6CJPEZXdBXWxdKTEklQ7l4LhzD6ce6YuFDXSP4CvZA/MfJ2iFJUdcPu5Wvw8MF9v4vkcvGcIF63FJb5ZlMPBbp67mTEY8d4f07lpaShIw23Sd/yE133EyfG335zFI0FemuGjPRk0vpXowKqGJIVhphC7zRqkh66h9W8i5ATtbEFvHgDRDvGZAwoytbQGqoz6xnjNPdl9wiUj8G5JxVmlbovbFiVto4m/da7hcWLsBalnMtAL9auNAC9ey0RBMwQqtAZ7+y3pb9mS+PJMsFGiFbQMCjvvFDBywr0keCEsnloERySbFoMjPeewEwGOK8FXzhYasp1xerzvkBtavPAqfY6DLg0y/JiWKBenRHkilgVceJEgJcj6rXiBd1lPijHewXHbZqwuqsw9ZQNwy62HqWUWxdCvMSRgRsJK0tsP+so1sTPLUq1nso9Axoraurkwk2xwFFoN7QiX6NsiOkjqCHk6mFTLvu+80It3l3aXBb1Crc3n6obbgtZMBzMuA5dbhFe00D3Do1uO1wSMLtufx5Jn+eKeB2fXUo3GZqcJtphNtMDW4zCW4BJ2lw60a5Bx6AQfuqgzrckvNSD9nuQrg8tfpABxOAhDvaa4UYsy4BCaUiLdABoVQtEe/qhAOGpb7yIC+1qHvUwRZL7dSW2mlc6hB6
*/