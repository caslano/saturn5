/*
Copyright 2007 Tobias Schwinger

Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_FUNCTIONAL_VALUE_FACTORY_HPP
#define BOOST_FUNCTIONAL_VALUE_FACTORY_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <utility>
#endif

namespace boost {

template<class  T>
class value_factory;

template<class T>
class value_factory {
public:
    typedef T result_type;

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class... Args>
    result_type operator()(Args&&... args) const {
        return result_type(std::forward<Args>(args)...);
    }
#else
    result_type operator()() const {
        return result_type();
    }

    template<class A0>
    result_type operator()(A0& a0) const {
        return result_type(a0);
    }

    template<class A0, class A1>
    result_type operator()(A0& a0, A1& a1) const {
        return result_type(a0, a1);
    }

    template<class A0, class A1, class A2>
    result_type operator()(A0& a0, A1& a1, A2& a2) const {
        return result_type(a0, a1, a2);
    }

    template<class A0, class A1, class A2, class A3>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const {
        return result_type(a0, a1, a2, a3);
    }

    template<class A0, class A1, class A2, class A3, class A4>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4) const {
        return result_type(a0, a1, a2, a3, a4);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4,
        A5& a5) const {
        return result_type(a0, a1, a2, a3, a4, a5);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6) const {
        return result_type(a0, a1, a2, a3, a4, a5, a6);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7) const {
        return result_type(a0, a1, a2, a3, a4, a5, a6, a7);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7, class A8>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7, A8& a8) const {
        return result_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7, class A8, class A9>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7, A8& a8, A9& a9) const {
        return result_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
#endif
};

template<class T>
class value_factory<T&> { };

} /* boost */

#endif

/* value_factory.hpp
ctpySaa4n7RTetQ8lx2UuO6E90e8m3B38R4lLuM8xL+GH0Hm4f92boJd4gSPWMGwNfUHF6pb9CEjFVIMrNsppzK9RE+ilnAmQgKp42TdEzdq+nQ+jfe5zahJvYgRGJ7x0s6emEMLDZPkWW9LVXA1OtOvrIW/iRTRLHCz6xIXtRQ+jWls0WHwv21LZ3rSyLUt2AG/nqTWXftsw8K6ZBh/a50+p8RCV8UpvwoOCfuoZbP3LHuZFo1+PGLJRGc/HgrXas1735++cHbnFOHNW9SMZx7hWWp5uiZtufcKCRVxxQw5tp9XiDj8Xslm6ovHzUmd+Ws2+Dgf2eulbtECmX7bR8Y7XB7MEw4uEtbm0oys05557utSUbp1Op9FpXHZ25bsF60MaRqRtPLJTZlLrFzeDGcoNhpMtwev3/4p1NBtTUHJmeFLPdDyg5Yw68kplM9FdYTVQMhswemQ0f5BlfIXUg/aBzVHorLvHBciN0+63H/scnt5z4e+0MZfycfwBLdw4U526d/n7jqsPWMW+NTWSRM0/M62luTVQLpcmw5FUkRjqDjeB4Gm4g6h2lJinnsD31++OHF28r5juc++Hppl6mrAFXA0UTxdb8o7nhDvxYi6pycDNp0Tjz0RNEWs8fyNONb0AqqgR7y+CW99h0pSCk8vtvLefvnd4MyaYPaMZF5XTL1B+PSZlN5crQnyBx2HPtPRGeMRxJC4b15IGzbSybk3ojM+XGuwwhoy7hqhQdxUstyY+aa7fGnAvZZ9kleeqmFk2Vpg13Oq8PVv7qzrz4+uuSW2fyZXmBAXCx5kFggMobN0Rh9+ysXkpvDa8sY3CCjn11rEWjtYlg1+60kSIPIZYbjDObSkYUQ/xaG5aTe+Z0PYTk1wmVXuQdeNrxXMvLc9ZPc/t3uIB0hvdvDFqTTqlgd0j6iS80562mpWXjxgYQr20RZOLFpZoHQqwfW8awqW7PZZPkRI3upT6eJwZsTiaNJxD+EsnK/Nmw29Hka559/kfKmFaHZWd0nbj29Mwxebd6Oqm84DbBWn2/zNxC5wbL7y3K+19p3OmOpgeb9CraT8G793G+1S1MFiSjlFVG20EVO44bxreIeUjPNenyDcO5nI+X25SzqqVEp1t/whxwFDVRR+Uq404SHtU223o6um1zWcOGky4/sXiN8dSsxMyKsUb7I58FAx21r7IeVXaKWTQr4YEV96PPTm/FjRFFmIzt3R/uwDXlX+SQszVP8Jn+jhq9/c3XCPOy1KRP5DJFgXv9aUrTVN5rNfBuVIt36ZS/1TVquFSdbemYu7miWLBS2tvjk8/k/jL6FtZoOnPWIHh3Gq5HMkHMTFagJ5btaVakTx7x+5ZOcU4dK1lxsykie5+cuzzGRsppjR7RELsqaj1drfRrSJh3mfOTPFuIYV0jDEvD9r9fhnmN8s3pF1bcXrrRfLCV7LtZDnraxVz55/FcLlcmGSb6AET9kl5ZQP/5L5YPFQxzHlVjy/Oqs3+2tcR6YXZeKCGjIJy0UtzajLN9THLRR/vDv/4eEQkQNlTODqgahn6G7v1vTn1vu770f2zASHwzbKB6V5F+ItJrjozHUqmpa1Niv0orrwtGKVfNuq3lFo4yaVBUnLZ7rK9G/+0h8y5mCT/9HiAlvHGl/zdjBpiuLlNisKPDtSlhnGjGHriE/uuptrm434O42DPlLqfSVtKqRxNFVH+4v67pUcIt/V+KIz2D888ZZDWufwh8eftHUpHCbHRmvLgkxTOQ7p1V/devwwlHvcVNsr1Q//ayOVuxVRv62deYnKI7kXK6UW4ear9YV9PtabArPKaqIpgjYi5Wecg/2CpX7GKOP/uuKmMiNB+oxBhoc=
*/