/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_operations.hpp
 *
 * This header defines extra atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/detail/extra_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_HEADER(boost/atomic/detail/extra_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_

/* extra_operations.hpp
DrTCFwbovD9qoBjU2UaHxOfoZwv0pN5tRVoI1pBtoTYC3QtCPiGP9Q/X+n7JPtUaBsCbr15uEaNXDx4O5zeLV/4OFavAOZjc8HLGU9CbNs/L4vWTm5enecj+zWKsIWQdmHN89vWxw1XBQ6GBEo+NT0dEiL9Bahfbdnl7MKHQI8fe9Sx8dNXu/nlLPKB7k1D4ptfPP/8ayb0Fb7tQ3xRWqcpTToP24hbP22LOAeyRU/bk4Ijg81147tantIL4vNqEH6/L1SH/VX48s0bDAYjqSkPS1DsZV5NQx5+6eYTo/WDarR6P/geVANErh8dY9mtLt19ul0ZlJgbXXB0hlKP+xaNbxNb2q7bCd8v7myR4kqKkXRui8+2re8KzH/MnZ49R/sR5gvmr24zwX3na4N56vau7VYBwdnlIL4IvKErW9xQ+YYGbfNtkw9P0Ba9Idiiw/IPfGNdPd9fPOb23hdHBZ44I29LszDyt0bVEGzB6C5JBI6jVJl69JlZ6EtW9fYXF/p3b60Y615or8w1LO8atjDore7YNUjZrwoMFu6MSIiccw0pdwrlCDNdpaXX68fUo57DeHV9cbGxs0mdqW1cYwk57rwFaP+6zNcoCzNpslVN7/U6HNwIBNSgPD3LZMQl9TX2Vy1cop3S1dmS7L11oxFFPadHu+Zs7bWUmejoS2Zu4p5bDmg7Vel1rG1BrzQx7Ti8os2FMkZvdK4eL
*/