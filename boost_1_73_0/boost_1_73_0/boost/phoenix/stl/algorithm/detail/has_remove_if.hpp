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
bW32pE0wQ6IbsDqGJqTWHr1ndTvC+fXRy49U0L/yZJfVNxz9uotGSpwe+C9OjK7NHEreC6+Wck0grDv+nE8ygGXvLg5Ge+cHF07V8VqFbgh5k62KCvQ+kDa5phqhWU1ipTq+DcNLLDeEW5mvxL3A+1WohuEVMlApBV8rByZkLuZTD1YWbOFeVKkq5Iu4F+avR74I9p/BfiCxZ1tSLraGKBWjEjVGIzH827vjk/3R62cShlXH4TYelaF4rdQ2jPkOZW5EBi2L1cQsqmCRkisTylRkZTJW6N56vOnklUpT0JWKSl4xTADKb6wpiJjbI2GYq6yxzvNMR9r6yVW1ihLninuug74GzipZgQMYvPZkqzPRS822rFoh6CSll28ElONOckt02bQkm5RZ1Qj8xQKl5etTRAIkqz+iOLlmrShDl1pvqQ5s4nRTMitE6ioBuhFv92n/CkHlExIAqZ1jXjNwIMdzHJNICIi2z5F7rLClzJACOyQzVtyLiv2lAy5yQh5Bve9Tvu0RVDSrWk6hVVES316N1UKdclct1mfCa2F6Kt5EKR5ozWms+dVHqT7HyjLVymf/ZgV8ya5pvb8J+zVk0gH5snmgPKzqaJAGjPb4W2zywDod/X4wdT07KqOXb4aW9wEJMUPdBhMFg1YX
*/