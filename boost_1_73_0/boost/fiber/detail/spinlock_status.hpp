
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_STATUS_H
#define BOOST_FIBERS_SPINLOCK_STATUS_H

namespace boost {
namespace fibers {
namespace detail {

enum class spinlock_status {
    locked = 0,
    unlocked
};

}}}

#endif // BOOST_FIBERS_SPINLOCK_STATUS_H

/* spinlock_status.hpp
+rORqbfa1jPIOuzevYPrXEBdZmC95U37X9JNP6m5LQOCh5EdhPUuDLTBzPVv51x/3FRiXo9sR/YhR5EcOsWByAxkGbIe2Y7sQg4hgXaEj/RHpiFVyCbkAeQZ5F3HPhV37YkvbAJDuvHz+b0FToJlSEhP/rr2pBNuhm59+fsxZ8KPYHwHb935O0nLQM5NRaowl8C6dOlv7hCpTx832PWFu+A+5BAS0q9/jN9lML8jfQIc3vHb
*/