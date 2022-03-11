
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/deque.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct deque_chooser;

}

namespace aux {

template<>
struct deque_chooser<0>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef vector0<
             
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<1>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector1<
              T0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<2>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector2<
              T0, T1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<3>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector3<
              T0, T1, T2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<4>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector4<
              T0, T1, T2, T3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<5>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector5<
              T0, T1, T2, T3, T4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<6>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector6<
              T0, T1, T2, T3, T4, T5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<7>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector7<
              T0, T1, T2, T3, T4, T5, T6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<8>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector8<
              T0, T1, T2, T3, T4, T5, T6, T7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<9>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector9<
              T0, T1, T2, T3, T4, T5, T6, T7, T8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<10>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector10<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<11>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector11<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<12>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector12<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<13>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector13<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<14>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector14<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<15>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector15<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<16>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector16<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<17>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector17<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<18>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector18<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<19>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector19<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct deque_chooser<20>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename vector20<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_deque_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_deque_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct deque_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_deque_arg<T1>::value + is_deque_arg<T2>::value 
        + is_deque_arg<T3>::value + is_deque_arg<T4>::value 
        + is_deque_arg<T5>::value + is_deque_arg<T6>::value 
        + is_deque_arg<T7>::value + is_deque_arg<T8>::value 
        + is_deque_arg<T9>::value + is_deque_arg<T10>::value 
        + is_deque_arg<T11>::value + is_deque_arg<T12>::value 
        + is_deque_arg<T13>::value + is_deque_arg<T14>::value 
        + is_deque_arg<T15>::value + is_deque_arg<T16>::value 
        + is_deque_arg<T17>::value + is_deque_arg<T18>::value 
        + is_deque_arg<T19>::value + is_deque_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct deque_impl
{
    typedef aux::deque_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::deque_chooser< arg_num_::value >
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
struct deque
    : aux::deque_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::deque_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* deque.hpp
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
*/