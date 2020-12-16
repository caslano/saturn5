#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/memfun_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/memfun_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // memfun_funop.hpp
    // Contains overloads of memfun::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/memfun_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* memfun_funop.hpp
WsVElhWNqJs27XS0P+4lBXvCMF9pWsvKJCnqxhe1vb843QRME3zevTlqi0wWuua2YjsHIGjx4IB9F8We540wdbt0XMHlmGA/QLHr0hZZBZZ9U4TSMnw0wtY1z5KmzNjeMuynIqwAldHKlmy45wYsYoOvxGhcZKDIUNSctW03GD3Xw8kb3rcp3rAmUXlmE+4HEt6fe+X5RdQm8Nibp6JiG6nolgrE/ibCphBRKzGGOXFT1zNY9j9EcywXtjGlTli/H5N745ykvnIGV3bgqOg+798d76WU7s6iLuTVCtLeRWlwbD+YhPsM8zFK2+AS1p1YwCoJ+QL9eZ7OtW1Fb1cOVzo/Ap/oaM498mh/hcQ8/PmcZpx35NExyCydyjLh+9tAv3ywdhnOSV1cw8c9N/anIrae2i6cXuQIfeNxW8TPyeaW3fAOZFCG6TwcQpx4jG/YxwJXHzfOawkPZnCRS9bQD9BJeLdVHzr8eDZP58oT4h2SNIQpycWJKVwbYR6v+0/4Y3du6hKNsF3fTNLszmZuvYQbXBdj9B2ELjYqilnFtn/fc/GO6nFADf5/Opp7oGxaXRsIJUAxn+wwjXd/gIiVMK4+SzCXuOtFTx8jj2+RcronAWU2tTXzyzRi/tFhoE32B+jJmWCuf9TDoFtmEpPwpkeRvxXAkQNX57Pm7h0OMeg4ZYJtd2oRE+QGjyA08BgCNGyPtcV00DjBR8mFo2XtQd2jdGV4gse215S5bx+L+RRIQ6dZvt1DHZ/p6S3ZOU49dlY+6Fsr+H25fLQQn5dEZeziVe56nNSb8OKmzZbvv1XMa3ZEfan4OxH4p4dtEHm8sMPM/eDsugNAl8fLFuit2Uro/1ct0Mfu0DHdhjyCn32C8S+DA2NliF08Q9y7jhZkIz5RcumpUB3sqw8v4qLJAn2FPD++iCWTZuUa1uNTS3B+4qyUiPmcx1xenHcd5ssEE01eh8Hx8w2CeXLZUq8h7afzcpTCRbHxfdb5TfK0S7rdCpwXrN3JDtT1zug3Cel+HIQx98fwHWYFvKKgm6+u3H+hGAyl2/MF9reA2Z7Mn9BdH7pT3axbd/5J+fhFFATigccNp0iHEU0A7j9sg5sHzNwHv1tfsY63DTTYkVammObO4bt1O7ML6eDSYJnuGWjefT02XfDFFOg7I1etybWubQPmIQHjae1WB4eAUSf/e9QyDDybEczZZRgYcQTzmGWY7b3JlGBYH3N1sTzpAmaxPNUCZrE8GwuYxfI8lfQrjq65C7iAeVaE8ePwyt7w6pTsWzsB4xtm6g5k7vNVnPuHnq5Mpo1y9KvjqauOu+Z415/gHyvwehHF+hPM9v5O52vqA5TuF2vqBCysXx9ZxHklWO8rbA/r94kIN+280JEzyqkQcwQONBSEk845lHH7NOIf9F/xcKDs8I+I8VBYBKK9OzT3eA33xZP5b8/2JlfbDcPnMQp7ZT/NAtbNSzzzR+fm6y7vjmcwHvy9dYXQstFsc7aTt47D2dmAuSfFyNb/GVioPMVBAuYUxaROlipgbAKiwzyEYjbc+AYubG2VYh5BMa0tfAcKtne9Mjd+hQL/mlNA4l2E9XDi+MhZ1iFc77DVlSnmKykWlq85ip1eC/nm/ba6NnVPMC5bX88d5FVRXD153ry1LsDSg2VrKKZjtDUBLPzm4IjdivjB7YhfmznoU5z+k3DWpWztbMA+lWKb0eg64QbbZG+kYaY/hZ0+B/Mc72oUOxi2Nixwt8D1/NORj1BYkKC9PO0rEc2v6d5b28oxpv8mxfj9MJzhv+NpVmw2cB6FQRz54Pz5Ejqc4yFMzYPwvHDTFcC45wE/x7xtkZMBjdv3otN3xj37DS2vwZ4=
*/