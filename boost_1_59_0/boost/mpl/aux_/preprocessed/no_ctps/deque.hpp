
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
+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
*/