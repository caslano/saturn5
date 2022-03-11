
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