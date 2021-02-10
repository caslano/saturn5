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
// has_reverse.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_reverse
        : is_std_list<T>
    {
    };
}

#endif

/* has_reverse.hpp
3JKm0yrwzwRWN/nj4fq1CqeySa+hL9jwXBReZSc2nC6KI/FCh35ThX6NRoS1PXaCgXlLKv510uvpNyXwzDove9QWPFQmuFJJLPKbe7xC3/VgpRW7SfttSnWVzZHY9jpN3Lms4POQ0325mCP0LhX+pFmCDw6yefWp8/G7Vkf9DJLgTjb2qpeHnrHK/ZpFcTr58kVpHLpJkO6IlaUbJrsHnX5/kWoflba/6H0LRFRTyq4n+Gdr4iUfYkmOcdkA9nmV8GrMde1biQk27tBv0MGrHPErT/Ig41LiYhlr2J1x1ltvMRp7bKEbHQ6uHXvStcP0VkXffsPqf8cPOK+Dexb0dM2cKio/TePn++gSbcst6aX7BVRaK/VA9CHdMO96lC+LsGOGLbn4VQZr3bQhPblpdcvzsGbHw73jk91Ht5UtY3JrNPrlG5CK+4/SKrNiQ9946EUoFqt26gss1XNtlf32n7y9ep65ojcdS1bkeRYr8pM48Itm5NmG5Fmm5NnG5HnmZF2kv2JSSkZlxaysy31Wjcta86JAKO6SaM/cJMIW8C9h8Zdx+BEukUg/yh37jP9/OFSkROkt27b8lTrUx6gJKHzHE9dDOl9EU7V/dnqwy7alXcHWuHjCXpRvnSizLDZsqd/oYX6jC7WIqd/X
*/