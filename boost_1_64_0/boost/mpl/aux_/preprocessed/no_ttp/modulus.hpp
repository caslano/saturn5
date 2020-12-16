
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct modulus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 % n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::modulus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* modulus.hpp
14BAYbs/J85DfuLd8iPfHV7Mx+tNXhx1JcanZF5actzXuvIin0XlL5PmPcufD0eZFProl8keVT7kvPDq2X3elEk3OT+5b8a+TJC8jCOcUyZTvcU5n8n0xHLkwU/1WZFpVfpXUjMzVJ8XZ9mmdXYCt3a78vO9kj+bfE5IP4YlV+nGcD+nq8sz8ZpJHpsQWimfccXllRqSVPFz+o727mV2jjwxdYnb8VroIf3AFY70K3YOe07bdc5e1Em7DWlHO9P2/pxt0LPsfbb56u/zQme6FTtHS9vnC7yeXJV6Wk/pb6h7yHfZjDafDTz/UuhzjdJHpfz75wAx5vqo3Lk+dmcq71dr/+KZ93/Ysu+RFe8FDgn5brv3/WqV+Qy/QJNcJ2Ht4jlA5HlELPIsLFmPaxvP61lkvWhCfVlvgM6cIq1krHJr9ME2eCUGYRNsix2wHfbH9ihjoOX6g//JdtVjoDvJdjvLdrtgQ+wq2+2GQdhdtT9rPe8PutLNk/WG6qTbRPrzmmIrbIbtMQDDsTkOwhayvXiT/M6HSNmeD8bI9kJkP3piPQyV/eilmislGPtgGIbhYOyLI7CfpJNCiJd0Zkk6tTFW0rFKvrOwOWZjKNqwH+bgUJyNIzEXY3EupuCNmI7zJL1thLOS3jFJrwFukfRulfSWyf4sx6a4QvZrpRz322X/VmNvXIMDcS1ei3fgZFyHM3E9rsS78HbcgNtwI76O9+B7uAkP42bnM6Xk9y00lvyqnyl1gxyHmdgI05znDWG55/MmVrVesKzXUme9a1XrxZeyXrL6fC1lPT/VentKWe96WS+XsFDq/QRZzxfTZL1Bsv8R6IOD5bgNwWY4FFvjMDluw7EbjsBwHInDMRKj8Goch6PR+bkj+WxWavkQVsh6ZZRPtGO9Mspnoaf1pHyOVuV792aeOUTYSNhNOE5Q+ssvov/Csp8BdpyJdYoIevdLb9z7n+1jr+x7pgv2Xp77po/vLb3fvYj/Byiv91Vu//ufuYe6cFXF++HDOc9iCfMJGwk7CYcIRYRai3g+FiGcMJlgI6wn7CQcIhQRqi/mmW2EYYT4xUafvrEYi7EYi7EYi7EYS3mXy9P/z8j7FGUAwJ/r/1f6xukHcva3MGebfVmEdXABtlPa+JcUt2dnximJW7lxv7i/pX4Z/WG1byk5x3Y6kRKt0oYpbZq5WNyuLW3gM2YUt2vLa6t0oGn7tvykr+re1iWfz3dB3nc8n6+B9HspicyU7anb8pmfjAUJ1QgNCJ2Vdvd5rrnJU21lz1fQQPbTrMSV/Kifc7he0rFKOhmEJqwbvcDVZ5BuVd9eUf72YdJ0tQ/L60RN+h2kn/wCoQ7hLCGU9erPd6WfaZ2rykD5+q9r4ThSsGVSBqr0Z2RlpptkHcezFBMkTwMlT/mSp2GSpwgp+3xX2aenZmdz7qqzVXa+tMdCnQ/pb3QbpzFZNhYn+ZhG6EbciJuc+bCnz/030zOTLOVOn3KR9HlP1b9kpYNV09ctfa6l5/OEJOov55AfoQf53KPNpyWDfJY9vsNVTiXzec6VT7c8LKwh8z5LHgIILYhfqMmD/eOiHGNaNJ8Pkr4rT9pySs1IsrBd55iAANZjani3PMZK//Fu5fNMHMB68YtceWTTcdNtWWmOfpigUvPoa9/upcUy9zqfcV8U/x0UNbZHH5O894Hrvd6O93q53gs2yefj2kWO9/7F3t3ARVHmARxf01IMC3VFVFR8f0NDQUVDQ0XFREVFRcUWZEFIXlZYfH8XFRSVU+s8NSVPzcw67rLSzsrSLivqrOyy8i7upDuuuIsuKu/O6+43y393Z5dZXNCje9n5+PjdGeaZ55lnXnZnnmeeCdE=
*/