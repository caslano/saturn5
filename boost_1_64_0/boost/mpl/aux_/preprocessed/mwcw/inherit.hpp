
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
qgxKkPbcW+ETf8YiV53538Ibt2nvMB3P09yGROIrR6ZzHP41cdRen967ZnKs/v/QOE8apnuPrWtIL28kP5LycLzSUPp1rTR49obLKsoqKKw7L3eYHuXrs35sildGVcqmb5DEdhz72pTvOs5kVAA2NWm15RsfP5LqfFE+5W+yMbsgf1F1+b/uuSdsps+a5rfJzrtV/ncgw7g35lurndkFWVn8VwB7GtbYs9iPf22w9qzr3UT+NeXRJMUdVlk77rScogDyxidu0t2j0pPuWT7pvqxJ7X1HZ3ONyydu9gCNr+9zZ9lfQ+v3j1B8+yOHEV+JTXxpY1MCjq/mXWdd532p4ktQfPHI4cRXbhvftORg0ugvzkrFOVRxDkbmEGfkdzZxjhuTxt87HWemmmYDFGc/5AjiTLeLc2po0lmlODP1zKQjacS5yi7OBey2GYDv2v69zbOs+WjMMvM+SwOwIr/QWr8W66FMkk0DVb9ivq9l00DqV8D2mPLAG/87HfSeNuXJdt/4Vd9cdvFT3wLx5+/IhvujattQ0szHBtW/jTY2qP7tlA3v2uRD4+Y+Nqg+Rv5gY8PUnc+HSlM+jJcNq21sSI9D7Gwoyi10b2SSn5mV6crPyQtkDw1/9kRovKLLVST7vHMTLfYN3dOjrL2e2XbIPOwrq20f++Fkzy3OhTnzswqL0vJyMuv3/Hq/AxtzztBi/Q5aLZuay6am+g4r97EpmPhrnmXrng/xGGJQcfVXXBU+cS3KKSzkAzqobxZ/339Nttl//10mWx5QXVmHZHBNDNf77GtcZ72oLnPyXXWy5ntoFsrdYZrSfAjSGRsjf7TG4yqgDnpSHND3bvVv/qLImj6+CGv6a/r9kJy8zKy8opp5vR3d19EBV51PyYY9vNt9vueiW9jbX2JvP71vbPL7N9h/lx/7N/uxv9Le/uJ5uTkZf0f+d/3J3v4NLT2RpquezkGy4zj+yWp/4dxjskwPTJ3fq3W1GRfxYgSefY3Iw7OxoxPHxT/5bbt4r12va68yXVtlvdaSxrGRvt+Iei/4pjEro7ggp+g4o1EYQBn5eye0/VnvBJ9v49ekbX/l9RBkAdfE/+xjx05+S0RA97cEp2zzcZjsWdCqtj0LsafE154QfFtEwPuj6rZpu2waKZuGIbnYVO5rUwi+NSLguwHkU2nr2vmUh00xVT42heDbIwJW2uaT9VsksY2+RVSnByGuOMTXJrtvkSDqdi37NC7CZV7XAXF5tpSz5NuGNj7fI3q3bKxtYxo+pID2bm8doC/K/PxPj/Io2AdpJHsKsKPCjx1phUUF9bWlOo/cGYMajmve0eSQ9X0QVdtHVYhdkb9Y7WL8SL3zxv0+2v8X+/fR4r09Nx+sej0ead6Wd781fkvZRAQQv7ccar+bvWNgulE3uMC7t9cUty/IvR2qT/u+SjYukY3HKo82+thY7GIPr+zAbazJI3tfyjD5Uta29dx8gMpoBFJM/Om/GvHjxU1zq8GXmjeQxUMKcutdTjV1ON9l/W2fWzB/IDDORcm/yrmE6vK9zLCFORo9rH6gpeSpOzTTOKsm8FhsL/PYbtitOh+QDyrQZ0913vwMaHyVub1trQNVNnVgtNIREa25IyqDNsilpDXMM16s8Ki0WUnx+6UlT58+9aDRM6aPS3Plu+RY20FZxFi+s/I4KDyK7xGlZysxu1VkF+dleNs0sqdM9oyRPcnIcXFo9NhTnFdIbZybOz+QZ3Znv/Pc/3GUO5NN48nK6zHH7MpWxjiq1KvGfXZLbmJpXPmL3/x+Tq/QrV2zq+eehWrcWLDj3kI1J83fuLFlRj5fd9cVj77y7NFVS1qvj+rb9OdJ/tYCCn7cW7o=
*/