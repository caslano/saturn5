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
// has_remove_if.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_REMOVE_IF_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_IF_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove_if
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove_if.hpp
TWnQFr50hE/kl/Qh17Axdz5ZG5EfVM6Qt7Fns3vie8gDUKeKO9T7WmH8Gxvwh+vwfAy8w++tLkiODnfK8cWx+7t475JtZzf8/qlhnIq/smOu8fG8gxTOWgPRA8af0opTq53YQ3KnI/Gfu9CvQcGcATFm1pPQyBu71Zv8uNvwj9z+R+/T13KBL8wHPSl/EL88iNikAzltvyIn7bhHn0G7j+HhGvxiLH6Of9dcyDoiyf3ZxlzR
*/