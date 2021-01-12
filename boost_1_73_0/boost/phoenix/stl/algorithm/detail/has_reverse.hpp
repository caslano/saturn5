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
ow7ELdXwzbvXmNxFks+1kbhiG7KInP92DPk9Rc5oZXL9BrBz7ks8yH1ofWSgKPHJGGxW9FfEMafIjcxMHoA/earQazl3mc1VPgT2ds5Nxr6Bz8/Befsv5HDEsg7kpRn3uNXK4asOEAeQO9x/MLKbn3v3CdT7GjtQjDrluAfLCq1KcB9Hrmdr1vftfO7GkYEBvEsx4AixLzFGWXL4zg3E15NLFNGAXDdk/Wv88Ebigp2bkaUN
*/