#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/poly_function_traits.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/poly_function_traits.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // poly_function_traits.hpp
    // Contains specializations of poly_function_traits and as_mono_function
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/poly_function_traits.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct poly_function_traits<PolyFun, PolyFun(BOOST_PP_ENUM_PARAMS(N, A)), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<BOOST_PP_ENUM_PARAMS(N, const A)> function_type;
        typedef typename function_type::result_type result_type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct as_mono_function_impl<PolyFun(BOOST_PP_ENUM_PARAMS(N, A)), true>
    {
        typedef typename PolyFun::template impl<BOOST_PP_ENUM_PARAMS(N, const A)> type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct as_mono_function_impl<PolyFun(BOOST_PP_ENUM_PARAMS(N, A)), false>
    {
        typedef PolyFun type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct as_mono_function<PolyFun(BOOST_PP_ENUM_PARAMS(N, A))>
      : as_mono_function_impl<PolyFun(BOOST_PP_ENUM_PARAMS(N, A)), is_poly_function<PolyFun>::value>
    {};

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* poly_function_traits.hpp
ZP9ZxhcHF3nb+eGSOXXSvv+axfzp2j4KfbUk79MDVOpcHOPvWoJfhc71Q3EQ/CPe/iTcYLo9m4Yxy5bxIzvGIOwKO6EMb16aZmd44KbO3nQYzhdvOxk3xHdeBxv+m70zD3H7qQL4115ut9t2q/VARarWE4/dtdZVRDfdZLux2WzcZGvVappNsrux2STmqFst2D+K1vs+/qhaoUpRkR9YtWLxQkREpGoVEUGFH1KknvSPIhWc9315b95cyfq/xWJ/mc+8uec78+bNG7Zp8vKleqvBo4jvpjy0WbwWXWf/GVa46oNQo6AYUpM1zNq4A+e1pt226jr+ulrhq6nmrJK7wZxdr1xsuEypud96uU6VbtMR90cvB4ZZ+F2k8l62ywOaHPENOf04Jxw+iyioouebG3Y5ca2D942p7hxZSkvS1muH21ZeUKfD84qejy2ONIQgTXKP2OnROg0Lyf3poi2vVFcCYbo2F8o8J3l5uEBaNngq96N23eC6jcfKV0W43NtAs06Kha30E3MtEAe1bNAdldZfrPUePG4QH50l7npILq6/mBsPyMPrnRW9/wjJ43kjavL+LSQTx2CV7TAER3MfrD/6307wj0jrP33fKRSn1TlbRH/e3fPFdagLjnPj8f44cm6mhKhdrm4hDowJSuOmn5d7OUqC6/Ta8Dg8Bu56yi33bJSPQ0Km5GAKgkkbxMNKA9hX0nczIFuBpJzDvZ7eID3mKLX1AW9ccy2p45Wofm8/bgvxIs3/bAAPgzX2TKt4KlN0MMzTd7719orY8mmbhR+F04IDOjgC5Pp+6C2/fz/L7zk9Phin3IOPnsgVlz+QDhzPyl02tcuRUBlgnOD4kmU/S/GedjAcj+pNxmOfrt78mfvvV9N+IsQ2mnhdfAM+SlSDOjlq21eFyiaPVUoVsE8Fj/pwprpC5Us+fmhc2haraFpnkQnFg1lKZ7FK6YyE8kh+C839YJHivVDU/9Ab4+Iu6sQW44G9ANXjpccNjoNHJ2gQV6zHqvIVintYpLelm+cqLs9R/rgyjlO+mVBey8qKo1al4kGbcZzkkDjUFBCL4swH2pn6Pkz/dNLAdwq8/dndT7CvN3/5aU+BsPhOXPfniQ7MVqQ+ZTpQZrlMhijMk2wvj2NJrsXuBORP4heC6/FUQO4ETXJgL9H3GsJjzC+70+n7kdhQV+Fl3nODeFjoYN0wPz+Ix83aitTNHPS0E4iVOp/nWUzYY4PwYemrmzX//E994GfeONQH4rMyLmfhcX52AgdYn45KVM5xTxlgrSZ1kWd8MnH3oKRq3eqjPs7cs7Qp3QeeMtG+hZiKRx5ZNrFvTK8c2HNIXyB6H/lVn0xzT3GW51WPbNjJ8XzQU7W5UYxX9ZxnJ85idg7clggdzLqXocGnDk5UPjaFbm/9cWHe3jO2/Cx13jpxdT9Hjc96jXowr6hQlfPDpitzIQedDw8v10nmmCMznZtPLRmqTWYP+lmSKtMf8bO0nakS1w2kD26cpU71boCDTWK7Fq9tuB+OSzaXWuifrIHRE8Skk64q675tHr63Dq7z/KjkF3OpLGCqBaC/qDGTYl2s/B4l1cHYucn4m6K+4B3WKxiMe8hG3DXZnkn3kO2ZJE/mjTwdQrbEWcDzSBYxq0Do/ngkbrt30cFhEV5DLxbml7Mn0N6V56I345kjhLsHj5HW2YyK9DrkTZ7NUrVv/UFnmOX2+Va3uZAUZwY7dgm5cDbKHgC1/fjlvSbDnvOQO89l2ebhyGuZ4ijN014O3MpFb+A94mNthjwYYprUDqd8spR7BpJzZdwKL+RVzvM5ECPzdNHlqIT6TNCqB3DyJr0Z8p7Lw1nO1xaI/b6PNZ25LfA=
*/