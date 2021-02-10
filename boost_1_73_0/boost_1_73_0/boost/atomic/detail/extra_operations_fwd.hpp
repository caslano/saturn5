/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_operations_fwd.hpp
 *
 * This header contains forward declaration of the \c extra_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, std::size_t Size, bool Signed, bool = Base::is_always_lock_free >
struct extra_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_

/* extra_operations_fwd.hpp
pqClNqtiwouQyDXQhm1lYoK9IRlnp3CtKenQR5hg56KLjsRKmE4s4EYkalPy8cfZTA6hQ+Qz5WScyc3Tp23qx1dcI4JerMn5RMnREPWE+N6EeqdMwytSgUM/LDoT28kuFDiyauYCRd11MAU1o2MJWdPlmJkJ3yKPaE3iJTob2dNd6/ovLiKFMNIMwcINUoA7yiHBExqs0iHfzY/eeBizmVP7PyXZxarIWURCL+aXdHL5ghYimjihTydXv539eUWf5hcX89Orazr7lean17D1+8npEept4CmQvvdBR3gOZHrfGa2yw2/32cvR66jHenZA04KLB9cCHjX54JZB9Dl3C85ETMh47/F4tSdbLW/r84uzDxfzj5f0E715XYlUiSqZnsu0FkNq/cAa7tbo2lhkshFSA6iLYZlTOPjOCUU3e0SN89pSk/wSeC8Lnu9ZHG/hxNjGlbXXvQvrjLnKu1jQx96ysQxF6ocumUp4P0rZr8RDF0Lebs7cwPAtm2yoiNHYJc7ZGAMINdUWWMKFamuBdyYdAIu+1QJ4ARBMTlxZsrkixtiVyKK2Ch23yiHKISbXF12SOpT3yfY2eg30lCzkM4jVnemUFEGNfMPGehz3aMFR4sQXid9QRPachdTFIqxCsy4SIGa3xkJCtvU9
*/