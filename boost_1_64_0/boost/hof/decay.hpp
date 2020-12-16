/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    decay.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DECAY_H
#define BOOST_HOF_GUARD_DECAY_H

/// decay
/// =====
/// 
/// Description
/// -----------
/// 
/// The `decay` function is a unary function object that returns whats given to it after decaying its type.
/// 
/// Synopsis
/// --------
/// 
///     struct
///     {
///         template<class T>
///         constexpr typename decay<T>::type operator()(T&& x) const
///         {
///             return boost::hof::forward<T>(x);
///         }
///     } decay;
/// 
/// References
/// ----------
/// 
/// * [n3255](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2011/n3255.html) - Proposal for `decay_copy`
/// 

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/unwrap.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/forward.hpp>

namespace boost { namespace hof { namespace detail {

template<class T>
struct decay_mf
: unwrap_reference<typename std::decay<T>::type>
{};

struct decay_f
{
    template<
        class T, 
        class Result=typename unwrap_reference<typename std::decay<T>::type>::type, 
        class=typename std::enable_if<(BOOST_HOF_IS_CONSTRUCTIBLE(Result, T))>::type
    >
    constexpr Result operator()(T&& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, T&&)
    {
        return BOOST_HOF_FORWARD(T)(x);
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(decay, detail::decay_f);

}} // namespace boost::hof

#endif

/* decay.hpp
nei/9c6bpjsL4D1pgVcLeMfiMasL1zHH3ja7cLXBn4zb5yT4ve7em8Av2MtAjr10gd/0ZPxm7mu7i5lpH99nl/ZxCDSykNdjVMKnh1cWnDOip8RfrddX+dtM336Cv02qP5vXLzp+GWubP5tXvLX15P5sXnG93HplrBml1kz5e6Ur/+69sdb92ZDm6i8Y3WhL8R1OEv9I7xP92Si8z0exNvqzecXO107mz+aNti4f8tS36d/nYf++tvq/uVO+81P94f7yevrqWP2/cq0d4HfbEx00XyNPYtUHIrIPXHXU0gcgS/PbGV5guW3oBepp2f8so6e1A35LAV8ugb+Pkc7qgnbZvlgbXdAs8PKs8Mpft9Y3056or26s/ySBzBOazahvXsMp1TeN/6HnNPwPR7S30meSQvYuieyzh63IOsRRT1tdEFvyP/SCxxPwblXw6iW8SUnwcsSl8VgbXRAt8NxWePaPrO2hW/jvR8b+n0NWkG4R/soAeQrO9snw8y3w0aet8D0Wfrjb4P8k+PnipZ0G/PxTha/k83OvpPOHLIC5MgVfslTNd2AycaXTL450UOtlHmPbxW3S18+666llU2dDvpvsX5nW/QZ5bt5vUICfKtpwMBgvvl2kwCJ0OD4CeM/3xfE1Gl/48CpzByYeOfjLgxrRG/PE3R1ouhgMgl5YTePJwyygRe3l/2tMnW/WOxiUKW/hlPEDMuVopMQlghs8cmOAgy5O6kphwt1xr8xrdy21ISSIsMfRIeQpaHxHkvgLs6SHpqXBkCw+2PS+Ws3EfsWZnVjyKwPKa7yT4qkOiZL/womZpNW8OYGtKXwPLx9LsLIL329WwFDkhTNVPIctcKprD2/HhRpiyZfcrvpBsudpNtCJFtr8WAh9yZiJLmpCqbyT9vXjPJQgqDP3LYn495rPQbsXoMCO1ZECMf4LuYaJRuBdMd2DN8l0NzL9XtjP9JseED/ZHJOOOFXiY1SM/bgyd8Rob0iRm3Dku/vlUsD5WbQ5BNzwn99BcCYf6T9XI9742OyPoT6BGp6preCLhmNi6mdMNF6SnXmSlTU5X45DeCvnNEgrgbKN++AyrorqZTRC42gDvMQL0VYO8rj8K3Nlzsnc0Bpy+f5Dm7F/t4Dw9wb0CeguEXJi7EddB2+F6hpx/OXtj5aG+JTbJbtuywy/at8ftYcG8DIphDfGN2a3Ykzf6PZ2w4A3FU2/P5oRurBavLDDtFXna7Ptimtu1u4xzr/4SnaofpzFERoCd1yS0mN5CJM3dzSZ2Wajw2L938jzuY3yOEO9q+GvhXGeuu5ETB4NLF7laHeolPuG+q/Ij9R54lHuB7nqRi/i8Tzjb7TITBTyAy4kP+SuJkHaO1P1npuJLj4dBGP/Db94QUaxw8JiE+GbVD03GR4IxSDjBQHSPX9kybDUzDBHZbjHyOBEV8qzEzeJZ+NsBhguYo3oO/UqDy+nfkXzR3RdZJFGvNz/fVdpcqSs3/zBkfz9acr6zfKU+JdS4oMp8Q+kxF+SEv/EG8nrTaGU9FoKfh0cqeOZ2/C51+c79f60szzuw6TqN6YJeekDbEVysAlZfBBVixqupTpFjGczLg7IMCNqb6VJ6ttNbHaXNx3VfoeCftWDV0A9CNK3h//puKXrCt1eklHrxgG/4RcdCJn7r/Dxo6ELlttHZdQWho8fC529vMw+apy9dkD4+PFQ9+VlGaPGZdT2CB+Ph5zLyzJHjcusba9WIqLamAzFYtcHrwV/jZCe1qe51Jj24fNcS8n23EerNMHdELyO+D/G4Iyd6E6xiCnCzk7aZWZajdP+PBZrk4sawcMaBJfnOmqWd4K8uKSN5Un5uwjKtOkL7YYJBx0=
*/