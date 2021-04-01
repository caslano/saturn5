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
kcTlHqsSnRLLbAxrzlTNYlmlXCAbhInV+2Worh6meVG/FEcLWUQ5TDWQTyNBVXFwGDW33p7Bw6Et5IYjJr7/t4qYA39qixDYMh4ljRXgpTBt92rma15Yx2LjF6HVi4Ii+itV3MvCNMKzaXTrjTEzYWK9db4llQn9N7krRbWDUayOKTK85ZQPa1k9/hHfvYT048U6UfOaTleSgk/ZIwSR7Y1ldZLsPd+TV+VTcgtN+aAjWn8OhZC18Ib3+D378Z6lVTw7vCHdxDN4+hbbUMg5IBBG2F7X+glzewhgSLZvVJMEgFludIzgql8mk14wLWHAg8dCEdhjz9ib7fN7PaZmu+cn6Z7vGPartDMffQjGPpvXvCpsGKoK2bym4ejTLAooPqhVxir6uPritHS8AeENuJETq6s02mH+i3kaa4nI1+5URaPaY18VOONQjhJbFxm1kIQPdlqKBES7JjtiWcl2he1pPoYGv8GB1EBUN36hpt4Xy9aDzXZb2AMHRb82yitdQ+/siLe4CdcXWwQYrRCJQWlc9aV1CDeSDadLq60jngDzj9cYt+RbRp7vuA==
*/