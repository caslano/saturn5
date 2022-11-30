
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