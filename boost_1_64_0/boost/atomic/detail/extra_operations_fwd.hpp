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
FvulInhG5d6o/e5G1hlhMfenOu4jY0/KjvjjMVfzjNhrqXLOqPVEbwVm8fcMzP8I3XVianjMKnb385Rh1GQjzHxPj2YyVtb3GakTLmzgWNW3P2PeH2ln6gooZpI+WlcY2VGYRfcv17ay5Ge7a4Eaj0q1ZVA2i5YdHl1L+NcTz9nuiH82f/Vdq1/JzjKPqj8fe+VbZ9gfSbXkl6v1XG9Umj2Wa+6UQWvPL8lSjLKq+X4yaHVMJ+7aabjD/qT6lm/um35TstR/8gj0Or6T+xmizzf+tTHtyqfHmAYeZVfzCJS6UMIR1Y9pl6Z7eTWtNqPSSauVrrRSSWG10ihV0+hqsX+KjB8m8ARNK/Un1euMCNMerNT4p2r6XCv6DTKOuETL1VgplMXznM98TexNkbEEYzZnv8aUvZvEzhp6RpPp2zZzljUpY18fRXvrJwfWeV6Cu62Z38aS382avlegWpG+5S1c6avtDbd90/hH4uYCSeMzI+M0/DJpbNwVyNIdk8bYiU7jNaJfI2lchPJKuyttO+h7kG4jrbRaaUebg6o/7ex255EWDZOpq2Ym/M68ulzl4u7StNyOamf3XxKj01Klhvmm46li/15rIn5fEklH9SfVU87zBL3vTMPZon/YmszfH6MySJ84TZ/OUofr/OO3MD418oNdaXJJO0t+iUHSRGn3ZfKTXGki1YF/Pwb7EvcsjdtZon81sJi/f0PlBjipB7UF5VPvqR9pZvwwX/RNxH4zCW3Nh6yu0tdHJ/ef4gyJPPpiCdal9JsOktMGM5K5MJBtTSY9k7U+fJt89hB8E96P4XuqR8n9V9GHr3c7rv9qXzcw/ZEjC+jDtyRcMJl8eyC5Jt9OnNw311KzGyJmx4fNpkXM+lma5z9ICpsNFv0eox8k+p8Z/QDR57Zs2Bkgfn2zbSqncLuWjy2oh/oyphB/VzpX8UpdcX4HWU9ZthjJkxXLTF5Q+6mmTxuXYuvvsn7KX7/2vbHYuY4aRb9/GX/aRMm1s/hlabvXT9xcSA5pZLXl/fellj4Z5lsxzjWOvG9UA9aipmqbSLxIHxMv0y6atHTJG1ufUVsOUUI/wp9iZLe5Px8a+UrjPeQr4c45b+aWr8T9Y5evNN5DvpJ+l+MZ0TLpqjrUjlcy8Ups5SeTTiOm9US2R9xw6xzbuePG/WOPW7ZH3HhGVNyGaNxSPOTt/YEBQU6r2jLinPLTnmpdK064OXY5XfinYY4O3wGP8P0Js3yv8Emi+8uvy3ek+RSPNM//BmleW6Ynep80f8RDDuALxL/cK04itcs3zXFTp8wu7h+7zK6nWtcvsyscp24esvhu4D2tjY7TiGkTj12m3EB91hGPZ13Ps6prP8vUL1285Oo50i7Wo36p/gb5oYtHfuAZnvLb5vrJ4mv17cri69XZW+bdoVYNl3mH3Tpk3nH/G6RZQ2Te/b/KiMsXGWt7flj0k1tbf3T/gVZnvrZj9WM9/vWy47zXZPuvBe80zTYfk/3DFW+8+Ol1va/83sj7Tyo70X/Nd6LE64X860YduKN0wNpeO599/8vLs/8/ZcSVo/gx/x6R/zY+ci3rAOYb2XGR61Z6/TrXKY7r0U6Zcg5ZcKP0egjXujZc15RpneBaG34TlYOMvWEs/CVMgLc45EslqvtWAdy75EvtxF4b+BfYE/4VjoEvwhnwJbgYvgrPh/vgNfAteBt8G94JD8D74LvwAXgQPgzfgzvg3+HT8EP4HPwHfBl+Ct+Cr8F4lTvXBGIu4Z9l6Rol2EXjHw8nSujRa/yv1fj/XOP/C5gEN8A0eB1sD6+HneEN6v9GW6n//TR9bHfr1P9+2OsEB8KhMBfOgnmwGA6HP4Kj4U8=
*/