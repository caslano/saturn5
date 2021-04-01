
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

/// workaround for ETI bug
template<>
struct apply0<int>
{
    typedef int type;
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

/// workaround for ETI bug
template<>
struct apply1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

/// workaround for ETI bug
template<>
struct apply2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

/// workaround for ETI bug
template<>
struct apply3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

/// workaround for ETI bug
template<>
struct apply4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// workaround for ETI bug
template<>
struct apply5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply.hpp
KejpO2dWYRRfFpmklyy7oAliK2qHAuVpD1gl2auWf8AKD8ZgzaWYupFEU92h5a41bi/Qro2RLCH+f0BrYj9BPtlSGTwfT+6nf+zdS6M0EALOeqZ7oalRCa0/R2fB4UdO3XhDe3y2Uv4qRaNxHcGKoj88Rh6DGgltArIwSF7bvWF0O1JOmZXnEoSlf4BoKl/8hTYHI+DPurqSfzx3UQWl5mhQGUDGynrB3zwLqMuwjfYpiu8nf+zYE5bO1ja0wTw9ijTO8U5H7WukvESBo98kgGhDApj+sTKF7bjIDAGjwv0kMGu2GM/ZhQss4zasPlIOJET+hdHG5gWE1NisFUGKZjtwgsGqqMcXqdXJKexcAD2oU7A2chpZotpq+lJgqipvQaSOIIDZTqMcs5dL6xZqNivZJmtkVmb3/1iFGINy+0qbVMIRvNVGhUSu4kkMCoQlNTIV+Hnw/+gsw8bnj2ntfOCcMYFDxqMaAP4+AycKl/tiwY0lsqU98Zge4c1KM6i+x9j3uOlKbFLgy5ccZbl6sZTSkac9a07wpVNvronw1RbpjB7lV28r8SewLA==
*/