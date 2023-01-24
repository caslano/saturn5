
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_STACK_ALLOCATOR_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/coroutine/segmented_stack_allocator.hpp>
#include <boost/coroutine/standard_stack_allocator.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

#if defined(BOOST_USE_SEGMENTED_STACKS)
typedef segmented_stack_allocator   stack_allocator;
#else
typedef standard_stack_allocator    stack_allocator;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STACK_ALLOCATOR_H

/* stack_allocator.hpp
u8N58v1S+AK/GCu1k3a74v02Sa9hAAZqleZ4DC9xpCOfaGhsSFrfTHZCKbHf7M3a9OHUhN/X26DbRaDAIUcktDH3tb6Me4cguZ2Rh1pXZtOP/fbZqcXpENhZ2BSu9/dvTolQNQeK/qcUJ5DZqszynaECCJJwb3i//jYj3K0PRIfDRCJyBnPJ5TkD9vust9I4uJvb55owX40Af8iGPlc6UueZ2Xfc4v8xmvSFKnpHedE0Cj1pJJpwXY2IZBp535KG5Tof2FA0zPDrWG1tK1rvJUkYr6TLeZCoZZcGIrAHMAbI14xFdq86ludPEvb59Q26vog2dUQVxNIrCCqkuKewQFh0h3XrNRskaVckHidVXpY8Oe/TR+VTskJh0tdnBNwET8oBSAE2pZTrGjDwhseASsrXBwLR4IXP3w2oARVPfXicNas0nsi5SEZtDmW08GieHd+OkFUZm1ulsJHGsOSUOGslbT35ktMa8Zo29K4U8ivc2Tz3SfnAiRTtX1Rcdl+0Hgiv18xji3DxJh2FpVyzl0uao7slLz9PSk0qxHnJ9dWxEVTirzJ86oRpb/3EDeAWT/m6Y5H88/3hSj4sf92RmlB0inPr4knVwyMvHx3APT8NMf6bLq0sIbbPUO6+Xjdz9WsL2N2TbpCPBw9I5919C+aZV3egYI9BRM5+B9u12A343TnNCuo3YbCNuwtQCGL1oYs5X5GP4Gu801l0
*/