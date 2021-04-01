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
GovXimL5ubW84/qy+Ekf2/NbmCnJ7A+9UOD0tNAhupeUw/IeId43dt41Y4q60UaLtjPDzlXuDsX/FcXg1mpvRaaEnYN81YIIL27RxNC8OLngfgDlQR61o62/+ekaT1OWafMR2YdUe3E3eFEZB8xPAa+pppuU1BuiOMkUkRgsMocf76xo4gBINWMe9Sblo9ZsR4zFQBdLI47j4VlEYlM44h2niHw15BSZ4CnG2LWzQBletgIiZ8BoHTkv7TxrzhVUWP6+prepRjFJacLm5PROs5LRFYyDpRFUl/xfw/yqWGPPSJD35Bo4DBBDjnNuBAZ5pw+mLUdGCP9u0oWs08hZ/kU0iQwgHEzvTEw/+IWWxQ/kLZNB5mcAbcOQD5mdmsJptgbCK8nHGSaZuZuWdSONZUaEBhJyc5akD4IAeXY1h/K2iZkXzLiBkBvyapqhFKhQLY/4Nt+CQtJO3QkhFl+3NoKrvpTLQPbvtoWEomIpuLbkpj0xJvDsl0UcfRhfpDAOmmkCrfQGRaHJ6Rh1tq70mzFTPmVRQrzkMP90kSBjEbQ9vCmCmXQWHc9Atg==
*/