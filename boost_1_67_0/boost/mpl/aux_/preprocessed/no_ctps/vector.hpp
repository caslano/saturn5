
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
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2V8P4peuFeq33vX/cpAXoZ3ovlMWfsOdfzPo3z6QVghnPSc8VyccJupntVq10S/q+y4Ky31xjblSjbm8DrwpNH1tqm/j1olWC38eeLtM8b21FL0da1kf0Syhh6Tva6wUXLv9TG7//P7+BikGBgIFAAMAB4AAgAT4AQAFAA0AAwALAAcAD4AAgAiABIAMgAKACoAGgA6AAYAJgAWADYADgAuAB4APQABACEAEQAxAAkAKQAZADkABQAlABUANQANAC0AHQA/AAMAIwATADMACwArABsAOwAHACcAFwA3AA8ALwAfADyAAIAggBCAMIAIgCiAGIA4gASAJIAUgDSADIAsgByAPoACgCKAEoAygAqAKoAagDqABoAmgBaANoAOgC6AHoA9gAPATwBDACMAYwATAFMAMwBzAAsASwArAGsAGwBbADsAewAHAEcAJwBnABcAVwA3AHcADwBPAC8AbwAfAF8APIADgn7mXbKaT0v0UzDfbz26eVik2DvXPlswX5wg2LWuOsIpNOhOATJHWH87u3fab1XAkQDvleV1NtR53yFedFT2t6xJt1BNdEOvsetFKPj2/KmqIrixHuaxjVTqLq96vCnQSSzz7K2BAW5Y9luI1ZcSwnnOj0pmlNodFRbc/S35hfP93MHlKf6A4c1GPczY1v7IyA85JL/MEjiz8h3tKoK+od5Hu+9QgO74KzKmKeJFBsx6VbzkPrZddka+9rGHHyvP+o60RmkzElSktvTqF0U8=
*/