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
// has_unique.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_unique
        : is_std_list<T>
    {
    };
}

#endif

/* has_unique.hpp
GqVreUaVfkjOpI50k/FZA4gpRCdpKRiGwRQgJuGYYB9KlhBRYatF1xFsNqvUPrMlS60JcIZKwD0YQm/owiSSVPpw2Tv/4/Svc7g8GAwO+udXcPoZDvpX6OvPXv8I95tiJAHkthBEYmQBdFbklCRVwHWeTef345NeH747uoCLUmbefq9/6MPmcf/ie0uKOKGi9dAGmnoJSSnDFT2a6j6muoGLxgfHwV0FnYhYdasxpodRNpVdO0XEnIiM5AV8u/EqL8Y0Lmiis8uiGVk153zaMLdrRzJreCG3ZExu1QIzu4NN5E84Yvdgu1sd1g30WtVeB1LMb0Im5XSK6ip0wfEQ7MGHnZ3favTXUuIhRFwalbmqULSYs3KGuHcGhCg7Db0zwIgSj01VNqkq7CIMMTG8juWtEFegeIalilhMANETSy0ER8170NLAVldTK1PMc1OqK3xZkOhaGprJaHexuuWbzap5MbtqxpiWa5u9NI+mEjCs61oXkcpAG1pBa+EGmWgxc0ErRAvOOdh0cuLtHwxOLtq2zrCYNvX739tfgHyD1taW1deqEQ1U58uqWX/q9ehwFtJtAGRGUwVV0OXEg7P8Jrl8QoVNzOtlWMKaddgtebUMi1+zCnvCXyvCwNesAY/Yu4aC1UP3CvL7Z8jv
*/