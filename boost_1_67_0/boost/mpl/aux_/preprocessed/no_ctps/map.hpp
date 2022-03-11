
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/map.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct map_chooser;

}

namespace aux {

template<>
struct map_chooser<0>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef map0<
             
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<1>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map1<
              T0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<2>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map2<
              T0, T1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<3>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map3<
              T0, T1, T2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<4>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map4<
              T0, T1, T2, T3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<5>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map5<
              T0, T1, T2, T3, T4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<6>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map6<
              T0, T1, T2, T3, T4, T5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<7>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map7<
              T0, T1, T2, T3, T4, T5, T6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<8>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map8<
              T0, T1, T2, T3, T4, T5, T6, T7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<9>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map9<
              T0, T1, T2, T3, T4, T5, T6, T7, T8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<10>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map10<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<11>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map11<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<12>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map12<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<13>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map13<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<14>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map14<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<15>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map15<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<16>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map16<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<17>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map17<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<18>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map18<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<19>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map19<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<20>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map20<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_map_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_map_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct map_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_map_arg<T1>::value + is_map_arg<T2>::value 
        + is_map_arg<T3>::value + is_map_arg<T4>::value 
        + is_map_arg<T5>::value + is_map_arg<T6>::value 
        + is_map_arg<T7>::value + is_map_arg<T8>::value 
        + is_map_arg<T9>::value + is_map_arg<T10>::value 
        + is_map_arg<T11>::value + is_map_arg<T12>::value 
        + is_map_arg<T13>::value + is_map_arg<T14>::value 
        + is_map_arg<T15>::value + is_map_arg<T16>::value 
        + is_map_arg<T17>::value + is_map_arg<T18>::value 
        + is_map_arg<T19>::value + is_map_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct map_impl
{
    typedef aux::map_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::map_chooser< arg_num_::value >
        ::template result_< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

} // namespace aux

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na, typename T10 = na, typename T11 = na
    , typename T12 = na, typename T13 = na, typename T14 = na
    , typename T15 = na, typename T16 = na, typename T17 = na
    , typename T18 = na, typename T19 = na
    >
struct map
    : aux::map_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::map_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* map.hpp
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
*/