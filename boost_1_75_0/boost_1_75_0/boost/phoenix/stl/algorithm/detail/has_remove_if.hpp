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
pPZdVejKdRpi3EjVcmEZsOp6LJJh5kYRQ9Ka0UYQ219ncEouoho+uVtgmB6PspENf6pEQ/fA1UDAk+0gLrAPm0cFt0zMzdJvxRPwTNiyoJlODgEQ2y8ZDwDlJtRBygKeuVsW9NPaIYAE+6XAAeC7v+JrAc/YLQvaae0wgIb9kvYAUOmv6CjgmbVlwThdgLrKhLSuxnvnFGUAuOyWGAeAghVWp1fGg63d8d7Rf8UauyWZAeDbCmkYsi7Z9eb5+ht5rmuveNfHz9a/Z192QYBsFQz6ADFC8yGgaAWDMUAM0mryjAfeKVHBoAdwx+MZjo/xZqtOcFUtVk6H/Uaj5vMUrC+QF4oH7fvZ8xwAVwqoFqTV/qD94jOVo/6NzBOB419byy7LHsM8lYPZgQpIT7LW5ry2/ta0eG8DTUkY0jPelZQLZPGobrtTpCJfHwAcaKXjPILmIdqyL79udRpNOJlKHLH7k528pGde0dp7taIYjLuZFMXbk0vgzbaiscdGw1gapdYr0Mu9KWwb3ai9wFykKa1h+qqW4pTEQOnZvkDQuwz5Z2O4czgchUE4ugUy+KY4eZC2B2j/B08fJOPqMnYRuDyUIHBs1esRfk/+8a0y7aBDutlgvH+7mCpN1k/djJBPb9Qu1MmHr8d0Mbfm8fUB1e54W+YPrA7nnscwMX9RWq16XDQamf6mOSfDeW+x0k/qhgSWAp8LojYFxQ77
*/