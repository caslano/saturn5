
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C1, bool C2 >
struct inherit2_impl
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1, T2
    {
        typedef Derived type_;
    };
};

template<>
struct inherit2_impl< false,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1
    {
        typedef T1 type_;
    };
};

template<>
struct inherit2_impl< true,false >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T2
    {
        typedef T2 type_;
    };
};

template<>
struct inherit2_impl< true,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
    {
        typedef T1 type_;
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : aux::inherit2_impl<
          is_empty_base<T1>::value
        , is_empty_base<T2>::value
        >::template result_< inherit2< T1,T2 >,T1, T2 >
{
    typedef typename inherit2::type_ type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
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
DO9GWX8MsDZ7ObuEfP9fGb7/yR1i16/GZ8REguk/LKsuLW3bh+f0TvGwsO/b4TsBO1OPjAF2P21J8JWessqahPU5rc3PY3GMvl3Qlx2rL1DtS34dblPnztJ5k4PO0ejMsevUK0vtWZvc1DvM5uvvJb09kTHozY/RWzoz9E5y8vrCvtigH9g7M6reV6/uXG9/jP4y3pirKY9Uux12mL7vXimxeseity5Wr69oWvv6U1hXvXR1kq5UZBy6FsXoqvAm8+6kU99dkeLcnktidNGc7VhD3ql+3o42napfQ4xOFhBJ4lrgVL+HO8a25blcMxrtunTpCiIBnYopivpWwLXyhV+p+JemKB2VpYd62hf7Mix8zjus/7+r1W5bmnpq2nVds6+XcC5tGSzBfq1bM9aGPGxoirah3dc6ux3TuD+ESoq+/j3uYMfu2NESbccqXf/s3z/YDFsipdmui1N0UPvKnt5IPvZ0zYqyp13XRexwui7qnefQOhBF1dOi2ufTVOf2yYm2Z5Wuk07tEy7NYzvnfWvF2rMn9kyNtifp66e9vwSQYAk2/R9K//bSvx2yF/rrovUnfU21HRvF/UWfM/5OzseiKVp3u6+xUW2g4xAqKboNWmTHUNkxRG3QEm1H0tddp2/rWCXYY4bytS5Arq6To5CRPeiTWwX1e6sKI0sRsaAJNUggfs/s87ep/C6q3zqKhVoSt/zCKmvhlkSOt3k8cxTctZt0jEUKaMfGkB4pCY+XCQkLxVi2WZdwe36GJSXFK9eauGLrYPzTdI/93iY7xsuOXNmRsXU8O4i/TKBNE7dDx9VhXYHr2LfO0Y6S4uAQP4E27y47Inq1ntZ8q1zZZ16DG2THTrJjhI5/g5MdSXyXPHz+5K8b+sN3au+vdA3zDDTLtypXWBuo8CUdB2hew6wuWuq1xUSq/o2WPp3nZv0bZd9S1f8iS2i7nGzTPuv8LvKxOFutL4m1LGRj1Pk8uEtoxz3VHhOQTj25520T1EcDrzzo5aUlBycSExo+5gGkpLqUsVj0ehk3dYld52uSdR2P1Wl1mTb1JdrXx4T7etfYtbH2QX9TSH/NwYW6jO6Slztq90n5heMLcifQ12qCn9hqew26sD3Wc3fNwbqv6BzwB6p1zzeejQzblnWNHetOppyWVm1jXNpmX8A2ezvwfyv1kK40ZD90eQa1pstf5W/z+d6xHSJjjAbawSrBukmyGbXW0EsONk0hf0brNtXWlCdvj+24uDGpbkxq0jGpdwRjUj3PbOj9ZPyS0+/utP8JZ9acP+fvjUnN9mg+DqQ5fJuqWDFeJbAb9ELlY34t/jet0vWedA+4FuwJQ/mQVvJ1Ur61la+zkS+nlXw/yc6f4VrwF/O9duXr5ZDvOuVrgD3h9UY+fzx95voDsnNN8334VvJ1Ub6uytfNyLdI+To55PtSdn4FU+HXhp1L4uojBfUB6VvN0NfQSr7vpO97tecKQ19jK3ZmSF8/mAr7S1850qR81yqflX+K8vVRTNhGsABmwArYD06HG8ND4aZwEdwMXgw3h5fBLeCVcICxvgLzJHG/WfWJ6vcp7Gyu02Dkb2ol/5vK36z8byn/20b+llbyP6H8Tyr/U8rfFGlnzSXAvg7tfKXyXwV7w6sNvTlZ8fW+rHyvSO+r0vuakX9qK/nfU/73lf8D5f/QiCmsU/7tHWIKb1f+O9Sv7oSbwGUwE94Ns+E9cDvYaB6PVux61lgvozN8Xna9YNjVovxDHey6X/mXy64HZNeDsuthuA18BA6Bj6rcHI+eZ2GuyjXXN0pXv+4B+8CecFO4HhwFe6mcDGSJyumicvg3+TWXYMb6ar/dHOoxR/rmSt88uAE8FmY=
*/