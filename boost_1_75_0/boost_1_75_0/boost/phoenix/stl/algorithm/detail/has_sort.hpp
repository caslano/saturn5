// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_sort.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_SORT_EN_14_12_2004
#define BOOST_PHOENIX_HAS_SORT_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_sort
        : is_std_list<T>
    {
    };
}

#endif

/* has_sort.hpp
YD1hXDWpQcNaq0oLIRahIoQT0OGnzrILKtOuRs3rg3HIxRXCTghxlmz4qA+6NmjxlsR0Hk4whuBNECXZ4fDjZeMWhT/tHyU4du3DaY3Mxy/qriai1WR/T/DhET+pKW66PO4BTiJO8gMqHPiDnxNFHcMXkmrXkThLnRn7k20hHEQj9zvKxiZyneyXrB792ZfeOOBH4sT78ARPibZyFL1HoQR9BnoP9CnS5V5Zxq/Mooi+0bSscJ2zQBYfXb51o/3MNfdFJl0bWnFLpj5h45xo6+ZUgkP2Pbswwu4kLTRuxnYimduRsC7LvwZhmmw8L7cm9AdoevB69QCLH/XUr+ndyC8hpYRIce2NbD0VaMdDeyKQN61LR1X+ezoJhZ3E694AIUtcyVhCzhrFmGFstsFTx1p6TdDW21cyq6nrTiu39tYpz27QKoRouzALZ0fMSbqX7JWJcXZZjYrEAetzuEBpQdqwHtO/3baEhwCkUy/q82shw6K9/s1y/46ddOarw+pmLZKMPR+ym59eUEuTgVDuuEOfWqW50iNZS++BG/XzoyDL2IGb4bMjWf1CHr7mDoRDHKBgxjl17qBqZODshbRCoTTJ9Y/Ed2XPYThTJYl+xTNMlJbSwLz9evE2u3UzPoGQtFCvkNTZOB29EFh27fn4hSV9qehAiIX/moShzovi+xIPM8occMvrDu8Sko/hxI64Qve5UpvnjRGNh++B
*/