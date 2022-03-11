
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