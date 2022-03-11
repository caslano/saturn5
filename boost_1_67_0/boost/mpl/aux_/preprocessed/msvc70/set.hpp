
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