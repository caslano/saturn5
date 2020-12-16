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
vHs7NvzKrsrfO/uvnbL1pANdRl05d8TCl1MfMhobbjRW3XgOhAVRtf1/1nnmhxLvvzC+fG7E2tTcq12PMY9rJPf05V7/RvaVZpr6Sm7pxTLWYDH2wEuxDy7BwXg5jsKlOANLMReXYQFehRfhcizFq/F6vAZXYhneidfhOrwBN+CNuAVvwR14O+7GlbgX78T9uAo/x3I8hHfhH3g3BrIP92EMrsVYXIdD8X4cgw/iNHwYs/ERLMIKvBQfxWX4GJbhE3gbPokrcSN+L7+J5f499/Ut/XgyXigXsbNZrwVmYjucgR0xC3tjNg7B2XgJ5uByzMW7cA4+gnPxUZyHL2I+VuN8/BkXSHuiTHLPHkdJe/yxl7RnirQnFcNxKibiNNsYEbkPL7+z6UtVjldrx7H6sl6Ym/Uq7dujXvV6J5rs69XIej3drBfxqdTrZj2zw3qVJvV6OxzaVyHr9XSzXo2s18nlenJ/Elu7WS/uM8+2Z/7Ms/ZVeLhezWee9UvEQXv7akzGOYEZsl6Yi/WSKeWy3tWUjU5zRjwhuUdPYgxuwkH4FE7CpzENN2MpPoOWsd9yDwi3ynYdx36HSo58TwzDXrL9M3EmRuJs7IcXYn+8GgfgAxiFj2M0bsKzcAvGSv3sr9yrYf/kOtpeuYch9e+S/dqD/fEdHIL7MAPflfrfwwX4PhbiflyMH+I1+BFuwM/wFTyIO/FzfB+/kDklvsQg/BoH4zc4Gr/FVKzBLPwec/AQzsMfsQB/wovxZ7wcf8Gb8Ve8HX+T/W7WyHpfhn2V/Vaua/7y+eHXmHbgydgDT8G+2Bwn46l4PrbEq/E0vBNbyXWuNT6NbfEZbI+fYBAextPxROrqgC2xIwZhMHbArjgYu+Fw7I5jMRRnYhjmY0+8GnvjrRiOa/AMfAwj8CmMxF3YB9/CvrgP++F+7G/7PJB7M7hX5/NgsFx/47ELJuBETMRsHIbFOBwvxFF4L47GdTgON2MybsXx+DJOwNdxIu7GFGlPcWO53yL3YZT2JCnvD2Thdx39hunYFTOwN2ZiHM7APJyJKzALt+Fs3I1zcB/OxQNYIGPqCrE1nothuAij8HwcjBdgPJbiGLwSp+AyLMar8DpcjnfjtfgIluEmvAFfxZvwI7wZv8Bb8DtcgUfwVgyQsVcdcSX2xDsxAstxAN6FQ/BuHIP34GS8D8/HNbgYK/AFfBTfw/X4MW7A7/Bx/AOfwM5+XM+wO27EobgJx+BTOAGfw0J8HpfhVrwFX8T7cDtW4Mv4Kr6Ke3AHfoE78Tt8E/2UMbnYGvdgW3wbQ3AvhuM7OBz34UR8H6fhB2jGarwAP8TL8SO8Ez/G+/ETfAQ/w2fxIL6AX+JO/Ap34dcOc4/IvRv2gX5wmhsjR8aqzMUeOA8nYD7mohmX4gK8EgtwORbh03guPovn4TYsRurlPJF7LPiD1HsKLpF6Dyn9hD/Kef+TnPe/4CT8FfPwCJbi77ga/8C1+CdWYCPqW4+N8QX0w0/QHz/HAPwGm6KM8ZV7ILwnpF2OY3yby+dFSxyMp+FkbCP90RbnYTucj+2xCIPQOuatQrY/Tq7LjmPeEuTzMBHPwJE4HkdjGibhLByDV+FYvB6T8RacgGtxIm7GFHwRJ+MXOAV/x1QZSzYV2+A0HIzTcSimYSKm4yjMcPhckfsE3D/Qfq5cLv2zDLvilRiDV+HZuBzNeA0uxmvxdiyT43QdVuIN+DzeglW4Aj/AW1G5ft2GLfF27IgrMRrvwGS8E8/BcszAu/ACvBuvwnvwIVyN2/FefAvX4AFchzV4P/6MD+Av+BD+gQ+jH/v+CPZtYvIo73rjfP086w3t/BxyrSXPWnKsU3v9M7k=
*/