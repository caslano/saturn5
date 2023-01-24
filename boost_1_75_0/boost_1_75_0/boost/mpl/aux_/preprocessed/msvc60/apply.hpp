
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

{
    typedef typename apply_wrap0<
          typename lambda<F>::type
       
        >::type type;

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

{
    typedef typename apply_wrap1<
          typename lambda<F>::type
        , T1
        >::type type;

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

{
    typedef typename apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >::type type;

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

{
    typedef typename apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >::type type;

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

{
    typedef typename apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >::type type;

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

{
    typedef typename apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >::type type;

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
Jwqn2zcRkVPjmRTLb2mb4ifhjbVN4sKhAghYFoQnd3p0NXXy+RseRE2y6VkBeQfFUnVluv73S2dOHummadH36r5MAg2WCDhOk7STiZiFBx4SaWFVD5RtymuJIhnR+KYt7Tj1+tWEfJEayhZN2vSaaCEajfHrOG9OPxzCp/0zqHyHdRuQAY6x3cpHI5x8491/Hv3gNKIHc+Y5PEeH0hLZFGt/33xf/oFPSR/5J1ib8Ar1YVgOkF7WPU5P312RFDVSMcKIi4/9vkHpCild/4bwUNaqZv1UcJ6GZPjOFFGK76MKsXGD8tOh8ISIq+3vrasnrjXCQL8XmTehGc2F0jvQszvzRmbhFeaj6N4KvKNLSgF6qPmxSZ50ImhBQHW8gXEt2Qs3IbkztP3LGev+W8kVV+/XM8VilfKuWKzCK9YQiS2jC8Kz7d+KhVcC8WgefTf1yq9AwjPRgyJlL6oEdA+2W+rCK6wzts/lgbAMIM7Mre3PKfK9E+UL880mehLp6j84WFQfKPwePBnIlL5T5UP/dGUgAz/+bJCxz/1qnHBbLPIWOS/1FQ0IknPnQTEek3BZpC4eRkgf3BfK6NkTZyZIIFcC+HHYfS5FENqaudW5UR6OjfhdcsdVsnP/hi0A6F6JP9XlL7Xby6wNN+sksJL30j3dG/Sd1OLpAekM7NeL9WRH9+G5eJelDsTmuLDsuXBxHnSMYWDTC9ObpqME
*/