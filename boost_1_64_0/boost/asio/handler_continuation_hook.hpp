//
// handler_continuation_hook.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP
#define BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Default continuation function for handlers.
/**
 * Asynchronous operations may represent a continuation of the asynchronous
 * control flow associated with the current handler. The implementation can use
 * this knowledge to optimise scheduling of the handler.
 *
 * Implement asio_handler_is_continuation for your own handlers to indicate
 * when a handler represents a continuation.
 *
 * The default implementation of the continuation hook returns <tt>false</tt>.
 *
 * @par Example
 * @code
 * class my_handler;
 *
 * bool asio_handler_is_continuation(my_handler* context)
 * {
 *   return true;
 * }
 * @endcode
 */
inline bool asio_handler_is_continuation(...)
{
  return false;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP

/* handler_continuation_hook.hpp
On5WTKfzhJq114ubSXEn/Q9AAKf3LCS2cCQq1oO68LLo6qjESmBAbJXGcUFmozvz0Z0Z5XaKQ6yu5310eOaC5eihzfIwLCvPuRFw5dMRqNc2t8nzGel4vbaTds/hYDBA9kvzFlacZLfd/kYtL0CJ6IQvqq/sVS/lY4+jOkdI+Ezp1XhSHcovtlV+fp6fmtBUfZz5rb5gfq0dPr8zg1BLUNTPg/2ZFbfeMEAmip/rM0R+EPFl4tYmsMXP81Mn4uz8Vtv5sTcWKD+IlM4PM5p4U2U3zk9goW3Ekb0aV68Ic8TU+wRXJ3bJ87W121Yh0YpivoFWmWM0RnqCAOdn+7G58LTC2HAEhucK++yUoXpPJ5cT+8aeqJoTsfVIZzNim0dxHDDBnjWpjuj6i3au2wwhx85diGfy1pkAeKuRp+X6cRwX0trxR3KQiJqxZLIHXi7Rl3CCb9TUZZ2EgnmojMM9pCcFcZI/j23yEJwYhmJrXZTOPt8Ip75olHUqmpia+1wIJebpwjksSMROTfG6trj59raRnzPZAue5ypXnS9vfUnTa5pIdcj5tL218WUv6SApo0z3qZJ3Nd1bWlhN+PjUqXF5UkssbGZxryeYoCZO3K8/yh2UEeUJeHjWOpY8nB/AqgTMNeiMieiMiG8Tkybsqi2Hy1CCSbVDrz0Qyn8plsymVfwIeaN8AnDZ0ao8u6daFl4biMHUBr4wPRaO48AcR3Co93wTXT3dDY12dZ12jHFFF8XrqvV5CFLrIP1WMb+oK9+jdekPjKiu9LtLrNpFnQf6sCZe/rnHC5ZCoXQ5NHwqvIwPItVx+Skz5y5z1E9BLNSJZwmOrfJaF8rep9KJQZw+U6xr4X6Kqws6KtgWCPmeHl2kypUfHUvqmdXZ6Ugg7fX1TXeNaD0QoHSmEndYTEzqm4h7YArExP9N2oFR+BOhyLncu64Ufsd8j8sqrTrTzo+JLj3Ooe6PKj7qB6w31Y6BV5efSr1WrduB/WHjGNFOeulV1q7z9O6RR7JBvRJgijACZVslWUbqrU4Mi7Gq5LoLnPBEpS0yi48QkwN6OxwdzLr44ohjJGLsjwvs4bNMzyXh9KuOOI39X3CR+NhnHeSys5orrzZ2Z7O6MDplLal8q2edq3zT8VeFvKv6m46+a7h+PvxV078NfM923EF10wUaii7HuxV+EZBKUz3z87RIyJG+Ke6LvFm0g+UMVmlZRIe+PVEiZwwhvrkS8UtLfgPAWun8jwlvp/k0I30z3C0VDKO0ix/0jqoSMvH8k7o/Q/aOqkCfdL65CnnS/lORFnZcJebp/HO5X4O8J+Kul+5X466H7bvxtofsw/kbxp1Ebj1bJdr0f4Tsof3H/TpE/3b9L1IfubxP1oft3U9oPIHwPpRX378XfEbo/JtLS/ftEWrr/Fv6+gb+v4e/b+Psm/u7En7pqnrBY/s4hhXEKaylsprCRwudQ2E5hjsIjFA6vlOEHKdxG9IMU3kThbRR6SU6jcJTCMxTeTnKzKH4zhXdReIr4iyh+lMJ7KTxL/OUUf4DiByg+RuEGClsp7KGwl8JxCh9aufi/6ncMJ4oLwzhTLIGBXTUU0rVo/yKpH6s0K+RivbcstOg31kj+q1Q6ChMvkPxnP1byKyit9xrZr1WseJ3C0DrJ5/VJEJ3qQ3xbbJj41z3Kza8l/mgZfrMqd69s77HN7vqOUX35z35uo/AI5cuvY0R/e8zdP9MpHCP+q1e4y8t5Jb2yzPCco3Q3Mn7ihoV2/YkvwunEH6d0W2i8qvmwryf7WUv1pTosUnLE5/U9R/WtLjOetZSOj2cT0e8NUH1Zulbir1rmLm+0rnT/1FLYS+n4lSP6GZ3Gn40=
*/