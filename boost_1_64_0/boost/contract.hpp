
#ifndef BOOST_CONTRACT_HPP_
#define BOOST_CONTRACT_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Include all header files required by this library at once (for convenience).

All header files <c>boost/contract/\*.hpp</c> are independent from one another
and can be included one-by-one to reduce the amount of code to compile from this
library in user code (but this was measured to not make an appreciable
difference in compile-time so <c>boost/contract.hpp</c> can be included directly
in most cases).
Instead the headers <c>boost/contract/core/\*.hpp</c> are not independent from
other library headers and they are automatically included by the
<c>boost/contract/\*.hpp</c> headers (so the <c>boost/contract/core/\*.hpp</c>
headers are usually not directly included by programmers).

All files under the <c>boost/contract/detail/</c> directory, names within the
@c boost::contract::detail namespace, names prefixed by
@c boost_contract_detail... and @c BOOST_CONTRACT_DETAIL... (in any namesapce,
including user's code) are reserved for internal use of this library and should
never be used directly by programmers.

@see @RefSect{getting_started, Getting Started}
*/

#include <boost/contract/assert.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/call_if.hpp>
#include <boost/contract/constructor.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/check.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/public_function.hpp>

#endif // #include guard


/* contract.hpp
lkm/IjWNFIUc/+NhHp8obDvTcZ63MKCd4sNpA1UI20Z/zDRRHElVhTyadttrYe7AT4nxf1MLpnA9TKbI7VWCXYNbmfCrdhl4uqkOyU1uab87DYq8NkqShjQm8JuBOPJgZmIigDQtQbFNe6VTRI40PK9uCiGj9cne3OyqAb0Tankk0AoTcuzVn2gL0sUfaA/E7eFQNroiK4LOYg/vsSh9XTjeAO95CZtnggxKbUaVxLMHnFxTq+4Mysz0yF2OSgtatVkwQZ+8Kz22mNgJl74eh1LjeoKDlpywgPrJFkaecAQ2pG63jd9E42KVvR7FFDW45NMQ1CrMcCPRMp7q577nBdZ0ZXC6TwJdUlrVUxfxv2g7dD33Q35qfHCbAgWmyihOG+tTYwv4GVm1u0eiAJElUwU+e0TtQE++BLNBtFgxHCSOeuI/pnBEp3WYp4adjvN4mUAL2zqzNsZZXOv29aMTgKrzcacNqkmLqvF3+2lRO/aZjWHUFMY6s2zaaCvQgmhds0eCESAAshwJtAbyR9OZYKFynwRAsd7sALHmWyY2K7sEuPyy69nornrgow==
*/