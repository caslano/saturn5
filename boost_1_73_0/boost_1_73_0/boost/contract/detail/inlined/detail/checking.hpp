
#ifndef BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/detail/checking.hpp>
#include <boost/contract/detail/declspec.hpp>
#include <boost/thread/lock_guard.hpp>

namespace boost { namespace contract { namespace detail {

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::init_unlocked() { flag::ref() = true; }

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::init_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    init_unlocked();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::done_unlocked() { flag::ref() = false; }

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::done_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    done_unlocked();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
bool checking::already_unlocked() { return flag::ref(); }
    
BOOST_CONTRACT_DETAIL_DECLINLINE
bool checking::already_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    return already_unlocked();
}

} } } // namespace

#endif


/* checking.hpp
GDqOWrhJdXfjjWriEcidP8wyLNw0pGm7b5aDLprMx2OfnOZKft2R1NCcw7V+V0pRmVMhva3SCdrRruG0awMEjpKlzAu4Cm6HaWg7gICTyuxqQpvZeaKX1r0bX1LtUyzpFceNc22YnYs89w/Kb6N6++aDg7LOhv+57OpG5HAwHOREY8ql41TLPUZbFJxhkkaj9CqKE0dGewBY7jjV90aKBhPDecS/9zxYvPjKvfonT73w3c3p2ctvX/dclzsELXGxX3ZoEI7ojLWVgYMyWmzmyejcWlCFJLYPqqH2ClVVaq2fk0hHTcwljs7Pv3tzetZ7ymoUzVIbF6CH19NztKDTjE1UctfXRLoGFYwy1h1OwhHDqh3fWJLiSQcFgZMYSSvdnt5ow1f9TulHwXyceMRG+2A6i5LoIhrH3iiZ+hDf0Hd4E+D3NJq+smuG/w1upuOhnXdIEiMy2OnBapPaiUItljKdCZEalfJlhpLXTTsnUZ8PPO9PHFJuAWZXo1wJnCnbe9WaH/B9Z7LcGCzDj50pvcC2giaju50xvt8b4w8XlpY0Gf7cTpqUfcOPXhyEfGG943VvvX14bEMVR+TgR5iOgwQrdeO4H10fw592zna9sZVXsvkL/3mFVfrCigNBdEv/8rzBCTX1LsdTXfNM
*/