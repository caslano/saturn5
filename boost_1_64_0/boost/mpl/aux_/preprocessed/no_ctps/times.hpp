
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct times2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times

    : if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct times2
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
+wEQfZNJIr8/WCO3GU0l1OnhvEK5lXhNQPuu9PFDJeKee96bfv1mCNNOzoAvBA+BSMjkaAbXzJYnbuOSjDJUeeWmL/taPyb/A47p1NNXJpO3SfG8OI4RBS+truNlAHov5/GiuDF0CLh0WDaFPD8Zbocq/swc/lTeL9U7eh33paLko+sQNohPD8du443CKxPZWgNxG8cshImksqGnMFMfzI4/Dx3S2gZchsdXoDLkYJ87uXqGOE+lyNpOaT2Jlt/V6OT7fimjEwfwniaCS4Y7oYtAB6GSVKGH9EZLtL2ps4vK54oZ5l0Fq7B/WbpR60t6USfTggYGb/iTauDAzo3LKmS8EfqlzkajLPLFxFgoVxHC7a9jaKTC6HRn6Ptlh3LQ+ZVKu8YMOv8Ut1ruaBMisv30umWUw3VlaTgeeDiTLtRp3GClYHh/Za+kjyf8KmDr6MxJi7TMby8siFncgsEF9HC5Glr8boidFPZ18CGmnSjPopRDcBeExMlyt1XJj3LlB/yYoxq3V7tWc+uWlsCPo6Y9XayT66f200/k8MaLBd5AfF5LqmLVB3lQDQ==
*/