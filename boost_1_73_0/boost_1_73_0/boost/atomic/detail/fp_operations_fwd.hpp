/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_operations_fwd.hpp
 *
 * This header contains forward declaration of the \c fp_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, typename Value, std::size_t Size, bool = Base::is_always_lock_free >
struct fp_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_FP_OPERATIONS_FWD_HPP_INCLUDED_

/* fp_operations_fwd.hpp
j5HTahYsSoBgQiAyWUY+sAETAIwTgIGrbOk7PCJYUjrlIK1Jpt3hklxWhwU+SML2mgbrGHtsbMVuXGU3ndFF/3rEbprDYbM3+sz6Z6zZ+wy0Lju9NvjbBU4R43dhxGPgHDF3EXoud4jhz/t5Oi2Sh11Zc06hNgFRx0vXc1x/yigKfG/BKj2e3KBtbsEREEoQ+lMfA2DOVUS/jvkJrVhtktGq+5wMqpCYkECLBfcTdOIJO1/CLRjo0reWk59hEgVMrzsQKujh0EpmbMy9YIXREAauT0GKr8B/HAMBMihiveAWQpD12pd1xZ1AtEzw/rRp6Iq8svfMPtF8glO4D5H9Q4z+8NwxBNgysnmcsfqj2zk1B83RhZLdAbt6XRN/vwJO7ajeqL99AuN+yH3D6AK8PbemPOPdH+g9eC7YFxdFCQJAjmMPhDisN6wnSNF1x4Zx0diQAtTG50KK4qIoBZghjmcNkOJ1/fAJQgAd1/G3ydBp9zIR0vs1CQATBDhuPI1/lCzCbQIMR1eDTIJssSYCItca9VdPEGEyli7dEOLstBQR5WUmSIZfO3ySHHYNykK8zRKt5lA3MlPkq0wEREw5S7ROzxi1O0NFXgn0oNI2VHnBKlY7qCC962HX/KgPjU6/ZxqjoVobu37NX21R
*/