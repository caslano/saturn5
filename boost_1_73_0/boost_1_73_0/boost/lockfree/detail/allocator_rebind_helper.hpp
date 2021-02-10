//  boost lockfree: allocator rebind helper
//
//  Copyright (C) 2017 Minmin Gong
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED
#define BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED

#include <memory>

namespace boost    {
namespace lockfree {
namespace detail   {

template <class allocator_type, class value_type>
struct allocator_rebind_helper
{
#if !defined( BOOST_NO_CXX11_ALLOCATOR )
    typedef typename std::allocator_traits<allocator_type>::template rebind_alloc<value_type> type;
#else
    typedef typename allocator_type::template rebind<value_type>::other type;
#endif
};

} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED */

/* allocator_rebind_helper.hpp
gewL1Ascbb8v7zgMIoOzvIzcp0Ci3/6kFikOMjDPEsNZkHQMEqBLkzYZPc9fQxJTTyRz9LGMOVPq9dFkc82sSAQ3mhu9QetlXIzr6F6TgUKmTyFSjOIUQgt9i8TkkMqFavfkuaFkPuxCG9kgrSBo38VPQkMdKBZ4PLzp9c/NfG7pc44uoS3J7xzp9a8kO5ZYPWnnd1RSS9/fGClOTvdimBD936wYtHEae4cmMU6WwmAV2uplnmovUe/FRv9cpWpINs/zF5So68SSOrSwtI2h3cF6cQQRmnYL2CX7JZ2xkdGVXMOApzHij1FTy0xVsP+UJvufkPv/B0Tg/1BLAwQKAAAACAAtZ0pScybfzj4HAAArFwAAHwAJAGN1cmwtbWFzdGVyL3NyYy90b29sX2ZpbGV0aW1lLmNVVAUAAbZIJGDVV3lz4kYW/59P8cLUeCQv5vKctscVlsOm1gNTIId14lRXI7WgU5KaUrfArsx8933dkkD4iHHirUo0Y4Sad58/1fZf7irBPjx5EfNH8MK74fgai9+Yqx6mJuQbpP+Q6xrvTympwYblG7HhaZZvYBkWkmk50d8JeUrRtbZNf9Q05zXRX/EE2TRnWyxuYz6bK7DaNjQ+ffoIB9CsNxsV6NCIswDGikVTFs8qcOKZ
*/