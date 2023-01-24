
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl
{
    typedef typename T::type type;
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
eeCqEhL36Hgj+HK4Dm98IG/A2sNt6u+OsjVUeNjQ4E9azkZC9AVAQbEz237gV4LUP1JNWcktYALX3nNnHf3DkktiuJkvcABPcmu7IEp5Cwiyw74ROoLDSVISlvSjgWNH3kzmg3PpD7iTfBI+yyrkLw5e0i2ze9EiNc2hFbzcwweTexKun8kRi64TVtatOcTqtlwdTbcVsUtv/BNFB4XNNukZSJXxIXbvM05olNtID8ZGPNbbqNTx8r7+eisVYBsxLwN6s8SiqZTmik9a70itaPO5YmT14wqZgBn1RnL2pdV8YHMRZju5Sydmad/3mdxvAKdr+osU8YVr1WhIgRIylfuNrsht43WVchhmQw1Z56+z/QjfB0FBymH6xZLXNv2URo3+RubGyawlRnGFXZQUY5eLYh4Cau2jfeA/fEsV1LT08J6r+ABRHdZDm5jU//7puMkpuLpxmI1/5C4uvkoPzS5IQHnZ46fZervLkqKRjiBZ+ZcJZKRkXLy6QJ9h2mEdQTusz9dOAnA7RKFb1Y3YQ61Z9x1CLpdQjN7PBhAQRnDVHmCOD/v260w+GjDD0ImfqGmdZGviSg24TgRjqmw6Fq7O5IaAdlTzo40GXGP3yHoP1+p1UfZGHyr9izLzBAugTbJdz0ElA2h5H9qC8VdHjuCI4i+OXPqoGxDvRM/2YXvHZeiqa8LoYtmMrNZl8q+O3C6byclprupknhuo
*/