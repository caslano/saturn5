
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct vector_chooser;

}

namespace aux {

template<>
struct vector_chooser<0>
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
struct vector_chooser<1>
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
struct vector_chooser<2>
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
struct vector_chooser<3>
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
struct vector_chooser<4>
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
struct vector_chooser<5>
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
struct vector_chooser<6>
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
struct vector_chooser<7>
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
struct vector_chooser<8>
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
struct vector_chooser<9>
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
struct vector_chooser<10>
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
struct vector_chooser<11>
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
struct vector_chooser<12>
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
struct vector_chooser<13>
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
struct vector_chooser<14>
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
struct vector_chooser<15>
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
struct vector_chooser<16>
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
struct vector_chooser<17>
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
struct vector_chooser<18>
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
struct vector_chooser<19>
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
struct vector_chooser<20>
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
struct is_vector_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_vector_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct vector_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_vector_arg<T1>::value + is_vector_arg<T2>::value 
        + is_vector_arg<T3>::value + is_vector_arg<T4>::value 
        + is_vector_arg<T5>::value + is_vector_arg<T6>::value 
        + is_vector_arg<T7>::value + is_vector_arg<T8>::value 
        + is_vector_arg<T9>::value + is_vector_arg<T10>::value 
        + is_vector_arg<T11>::value + is_vector_arg<T12>::value 
        + is_vector_arg<T13>::value + is_vector_arg<T14>::value 
        + is_vector_arg<T15>::value + is_vector_arg<T16>::value 
        + is_vector_arg<T17>::value + is_vector_arg<T18>::value 
        + is_vector_arg<T19>::value + is_vector_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct vector_impl
{
    typedef aux::vector_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::vector_chooser< arg_num_::value >
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
struct vector
    : aux::vector_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::vector_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* vector.hpp
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
*/