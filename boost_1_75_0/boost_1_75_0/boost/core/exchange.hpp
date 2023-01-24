/*
Copyright 2018 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_EXCHANGE_HPP
#define BOOST_CORE_EXCHANGE_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/config/workaround.hpp>
#include <utility>
#endif

namespace boost {

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class T, class U>
inline T exchange(T& t, const U& u)
{
    T v = t;
    t = u;
    return v;
}
#else
#if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
template<class T, class U>
inline T exchange(T& t, U&& u)
{
    T v = std::move(t);
    t = std::forward<U>(u);
    return v;
}
#else
template<class T, class U = T>
BOOST_CXX14_CONSTEXPR inline T exchange(T& t, U&& u)
{
    T v = std::move(t);
    t = std::forward<U>(u);
    return v;
}
#endif
#endif

} /* boost */

#endif

/* exchange.hpp
ww0zzdNxDA7xcSzDM5Gu5AU78RiFcSOZjvhxbYxCW6Ti5S4X/Wsy/6o4X4uMHesXDaNkiQEUKWSexM/9+kmDfkNeoHXUSgXWCZ9QzsVhfZrcq5epTGIWGO5Fe5Sdw44yk8JgEsV3IL8Mlpl0euHbiRi2yiqMILFKcxxHssiQrjJWlIvGY2cyKI3nw6zb2pNu02zxJsxn+knrXrWM0yiUzeM4kiEvcngLzJm8djUdxslCqBOEYXAkN9qgZKtF8tSeLBxgK2+BZw+y5LcovV4z3WJesLRpztiHbjwpgHGeNcIJ2/7YzUSZylCpLlKBMFaqYXRA3Eo7lNG3eqarynUm1cQKlWE6H4vLD+d43Mi1pJIKtVJACDw6kOcGGdRqptdwLt+F/PKLXl8pDMOMV3ycyE+xMF7KsKcLab3Jp52hTzXhSC7H+d/FIHvu0u4ZWL8ZCuPUJLXRhPO/eMavizS7vxierqswqbUlMQquSuU4H5wG8tFemqyq5KJFmUwGdWGFCawFOcPjvEk7ye7rgDcpQJBjVRoVViDKPJ7F8pQG1eZXGk2QtgiqsERnmM5wTKYkGW1iojLyo5KSGCwCgpckeh7CojMTk2JjUpPTEpPihPjukrUrEAfg5LiUDBmjAWOlh+TTWA4eGyeLS5HheCWk8ZCEByBOlpCanhGTmSET4ZwlQ9sjLlMWl26BzdmHsOREWQzC1qMeldz2QFhC
*/