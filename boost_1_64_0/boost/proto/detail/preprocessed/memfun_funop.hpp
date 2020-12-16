    ///////////////////////////////////////////////////////////////////////////////
    // memfun_funop.hpp
    // Contains overloads of memfun::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename A0>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0);
    }
    template<typename A0 , typename A1>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1);
    }
    template<typename A0 , typename A1 , typename A2>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8 , A9 const &a9) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }

/* memfun_funop.hpp
2bNgMi6uNTacZy7hy8VTmNn9mKWcqTBZR3a1V7L3BMNKC/Oa6HWc8wEm71e8U//2nAHtjevv/mG7T8wlbZ1pcONKzCWYPL9Cjyi+F2yG2ciYuY0yMJdgcj74TjmXqew2TJ77Al+/Esqew2Q/q3O0RgvGrINxXJpGHnnLXIJVF5bYvOAH9jNtXdXOY00YF5i8n8mwkiWVxcHk/h5PGslvhGmwusJSfrjHPWRp66o2ClnJfNFsSVSgubI8mI+wiwXDdioz6Wjcdwf5phZT5giTZ7todnwz5gvMIOze5fcH2XtgskcGlb7jxT6vrfuUejeMs1Fb13Gkr72yBG1dnyVzbzKXtHVd7uwYoGwNTPaspZdifZVlwmRvbdy9E3tkNqyi7AVR47uw98CKC7s2ru5L1iZMxrrczOMuyrw7GednpZDHfB8MgnkL+25fs1hlkTBZm+fXXdzIvgTzkddsP3sOc0m7n2eZqrQU7X41ZybdV7YT5i7s5YC06Zx/MJkvbccPmaYsH2Yne9bUe3cYM1hZYd+2Fjixxjobx7qO6eeazCVYeWGXXjX4xjkGk3v/0vBtL2XJsMpyFjeql8U6glUSduKJxwPOHJjsS5b1KvykzKqL8d6/n/EH55EHTO790lfzyzxbmIx14bMH/Xm22roVt9LZ56NhMmZ1A9cP5tnCvOT+bCKXM+dhHsJG+rv5cebA5NkG3au6gn1CW1fSfXwqz0+734WN7T7y/Loa19+Wx8umce8wuffN/+yawr3DKgiLH5/HXhAPcxCWOOFGPOsdJp8ls8fo3pwd2jVHJbnUUpYLCxB2PGV7RdYtzF9YA3unop+7/Wi8BwubsFLMT5jsIb+0acWY9YI5y7hU6+PH/cE8hZlWD2c802DWwiZFvSnqZ7CSwsymvmnKfgazEfaXjes2nru2h9hPR9hDbsPM5Tnc/S6b9QAzCBvT7EgrZa+1/R2tkxqszNDNOHfnvKjGXh4Ik+s6fMP/WsWzm3HPSm5Wh3ndAWYlc9DCLY9zBSb3PnhYjVD2CZilsHUeX9dwFsNkb72YXKzod1e1ZynpuZV1m6LtISz1TRPmIEzN/iDYsRdNOKtOw9yFXRv4y3X2T5iHsEEn/mG/NolCvghLSTR141yBlRVW1z3UVVkozFJY561enH/hMFthwRFP+Y7SBVZSWPEH71LYl2BOwuZu7cRv7fHaun69/PnOkKitq577O7+102E2wtKWeeUwr2EGYa6zfBuxl8NkrJt9Gb9b2VWYnbB7K485KCvU4lK8XfH1zGtYbWHuEy38mLvdUZvCNtpf4+wIhlUWtqndzZ6MGcxf2M7NTd6wn2nrXlr3e69sL0zGbHftkvwOz4F5Czu/fEVLZc9h5sIilrS8wF4Ok3FpPaN3Muu2B2pMWKrvt+HKHGE+whZk1NzDvcPkcy685XGRfR4mY5b5YAbrPUq7ZjfTNknKEmAyrxvvX1aC+QIrL3Ni7K3NrDGYjPWN/pHNGReYzPnYLqujWWM9jXO34/lRsYwLzFXY98V7MtYBMHnNrNUL9zMuMJmfh1rHD2E/g1nJ3J13YgXjoj3LgJoD+imLgcnc/Wg7hP06VjOrce2vcebADMJ2JRVnPKdp1nNxsa3KkmEyl/7cdegSZxWstLA1n3bwmzJDi8uAB3d4v73ac7br/SKEswomc8ntXufPrGkRz2qw70vU+JV1C3MXNurVL5OV2eLN0ELYudY1OFdcYIHCBq2NzOU8ggULW+JYgzNgPMxD2LA1zT8zLjAvYdvdLHnue7V1jQ+34bt3rmZ+jVsV1TRM1UNV2NiZzXi2tngDqiqsr2WbRM4AmKmw6OCc1twfLEDY0diukzg3Yf4=
*/