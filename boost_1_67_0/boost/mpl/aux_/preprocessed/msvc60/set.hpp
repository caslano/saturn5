
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct set_chooser;

}

namespace aux {

template<>
struct set_chooser<0>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef set0<
             
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<1>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set1<
              T0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<2>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set2<
              T0, T1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<3>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set3<
              T0, T1, T2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<4>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set4<
              T0, T1, T2, T3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<5>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set5<
              T0, T1, T2, T3, T4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<6>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set6<
              T0, T1, T2, T3, T4, T5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<7>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set7<
              T0, T1, T2, T3, T4, T5, T6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<8>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set8<
              T0, T1, T2, T3, T4, T5, T6, T7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<9>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set9<
              T0, T1, T2, T3, T4, T5, T6, T7, T8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<10>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set10<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<11>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set11<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<12>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set12<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<13>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set13<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<14>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set14<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<15>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set15<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<16>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set16<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<17>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set17<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<18>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set18<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<19>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set19<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<20>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set20<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_set_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_set_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct set_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_set_arg<T1>::value + is_set_arg<T2>::value 
        + is_set_arg<T3>::value + is_set_arg<T4>::value 
        + is_set_arg<T5>::value + is_set_arg<T6>::value 
        + is_set_arg<T7>::value + is_set_arg<T8>::value 
        + is_set_arg<T9>::value + is_set_arg<T10>::value 
        + is_set_arg<T11>::value + is_set_arg<T12>::value 
        + is_set_arg<T13>::value + is_set_arg<T14>::value 
        + is_set_arg<T15>::value + is_set_arg<T16>::value 
        + is_set_arg<T17>::value + is_set_arg<T18>::value 
        + is_set_arg<T19>::value + is_set_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct set_impl
{
    typedef aux::set_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::set_chooser< arg_num_::value >
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
struct set
    : aux::set_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::set_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* set.hpp
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
*/