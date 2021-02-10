
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
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
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
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
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
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
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
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
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
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
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
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
Xe2XEOCWjM03uzTbJst5mm6S3T4L+zF5f2GNrlinHRXUQypJAwVttV//sgb5w/3dwn06T6Q6ix7HPxL7pudDt6Gpx+iHI4pJ5mcDUjhBSm3A2hrCtLw/yMIUptce5vCGRpXXQQ+idGjA1Tg4oBYWcsQOIltrFxF+HrS+hO+rMiqgSGVF3gS6W45bJ3Xv/iCZBN41lWS3L/UFUEsDBAoAAAAIAC1nSlLtGYHnUQEAAFkCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjIxVVQFAAG2SCRgjZLBagIxEIbveYpB8RhDe+hB0oViLQoFxdX2KNnNrIZmN5Jktb59JytboZTSXMJM/n/yTSYyYoilCpgxaZrK0faBl7PzOmQsn67Yy9PidbueMSlueSmuUjZkQ5hag03kwWhksuwCUgT0J/QZC+WR5H0EslE1doXBY/QGT8qCq6A2IZhmD5WxCJWz1p1RQ3GBvXO6y5JXXM0gS1fXqtEZ45ygoGy93V1v3qWY82Nb/HIwpjTwFkbbfLaeAKFNhBjNl/lmsZqM8ny+Wq43ad+t3p+FdXvRuMgVJ0ajeYLgtaP1H2dSP9zfjeNnJB7TBCQYeiDxzS67XlNLj4MfjkHGNjQW0CoqVjkPIRwgDYr8
*/