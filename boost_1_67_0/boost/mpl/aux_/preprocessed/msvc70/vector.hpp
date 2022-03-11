
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