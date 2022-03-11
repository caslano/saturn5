
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