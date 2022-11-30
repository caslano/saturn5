
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