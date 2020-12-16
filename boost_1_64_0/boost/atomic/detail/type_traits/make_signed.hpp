/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/make_signed.hpp
 *
 * This header defines \c make_signed type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_SIGNED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_SIGNED_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/make_signed.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::make_signed;
#else
using boost::make_signed;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_SIGNED_HPP_INCLUDED_

/* make_signed.hpp
dNlffdRwPkz6WFe6vL5QW3TSh6vPhnb9w8xNzP6kDh77k+uKj6JP8aD2xiPT0RMtZmaoWhnLQ8jK0O+v9ZvJjxMmcq3CTX6d1U6oCtXXDMl/jtnDEn1pGUUi89VWTkGj0ZdJH2TecX1E4qej9QyROT9Hx7hrD8vjJU+tdXzbGKcc3QvT9S72YnE/1PY+dr7k6W3GxBfUb8/tBzkH0C7O0S5XH5wv56Te0geTkFsofUC9pAti7bZIfaetp2L9wMvBY5BpCeiDOsZSvLnhDyKT3ubLR3UzSN9F7pd4RWoDT7n7pmRaMwknpGa6/B7WWUNUZ1d+2c47JSWV95tn84agnt2gVkf6WLdEbrBy1Q/J5K/YeW5hNjrXKlAfhpkiNyq10DqP56pXREpTnpT61NrzsZ2fvMfINZz65Kf256p2na6nrJmRO61/RHpZuSnDrNKUAdbnqeOWlG7W4yknilxvI5eTmm2NErn1PAEujdxqfRDJs4ak5FtlyFyZkm3dxhvV76VM4x0pdTNy9akDrEJzvZMjt8v1jkzpyxvmLLlOceoQaWMtOntG6lyHBma5/UMaX45Pf5V0OG7DsK/Z1pAE2zba2zYpOy279f1zgfZfqly72UrnzcepjIx1vGHIxSyxRy0/Kn05C7u2RRvVP+BywtHc4/oW87fG5/TRNA387U4jtD8W7PfAUelfq8jeRR+uYV21vgemPm3nMdOAcWO4DGmt85S8l/2ylMc7oHGxfuT2qz+9tTo3NRJOIE/Z14LHxeKqCbXx5vSLRW6hNd3MUU5ZR4rMrVwVfTJwdY7SdPccVSfxJdY86umZ18wcdZHkqbEWOHOUKWdATB/3RKWz+esSSTvfzSW5xMxdJr2/4ZLskXi2Kz+TnSv/NZKea+a6fLWB+oO836Afzol+zFznmv+kb2e7+tZ9nylXX3hval++RDhxnF2ovy+Vk6l+32S+0/5y8h9p+uNIiT/Oe7wMlz+3FUtXq12qvySVKxA5+/oFEn/GusqKGHuxPPZytOT5OiM9U/wPHsAe38gkHX2mNt2F/8GUrD75VsA6S32c6przbeLn5WIX4OIO3G9ov61b3bPe7afJtC9mvJT1sOQ4htBb39dOpV0lt/l13FDdON7elDt8XaZyLn7UHIn38+3bbdalkp5vxk6Jxh1u7+oi+JbFB2eDnj3IjX0VyZgiX4Q5D/wb4STkm9raTpvrqpCU5Wj3Nr+C2l4nb5HhL94u8Z8T7x64pptnZEYG6qTMnW5sjOa45oqtkv4bi3uae99uvGOSR7lPX5M8bzJ7pAXOEXngpNvtPCkax7uxxEvFbsuxC6JqtzsTsNtWme0sogcik9W3LGvqmLZ9n9fSj2PJs4UyHyBPPzsPjoUzKDe9S0ZG6oCMlNQ+dsgszhwGqzA9PWgu8q8LdUy/JO292fCcWiSe6Zs74QZo2qM+veSqXn4l6YuYi1P0nFPeVrtOoXNorugv1/g4dmz4iOLE7pM9dX5Uv45iv7M963Pxu+u3abMuHJjjH8/TsaF9t/tt2r0ujIodRm0jMmPzA5HprbbulNE/cOzPM+n5Zuy/J/EBzlgWG+jXgbEclTZKncxYdo9v91ieofvBv6D3ij2EmeQtucPX7nj3Cs0/LGzskh67h/48iT/IOjfDO57NeJ0veR6Cr633dlPOoND7T62rLmH3mo9K+mbrXL3XFKKJhbnOmF3f7pjNVZkmZArs8dh7mW/eFT+3mq+ZfHmyb8CErJ49U3MZpRn8DHH/No3h8PZPgFttcwZ33WE4g0H3Me17/zgo9YyDfBkvgfc78ywiT0lIPVtBeDsno9vSO9120rgY6TZ/wwzzC7ho8D1PZYkZ3/k=
*/