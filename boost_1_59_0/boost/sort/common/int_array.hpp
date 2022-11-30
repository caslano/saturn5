//----------------------------------------------------------------------------
/// @file int_array.hpp
/// @brief This file contains the struct int_array , which is an array of
///        uint64_t elements, being the template parameter NN the number of
///        elements in the array
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_INT_ARRAY_HPP
#define __BOOST_SORT_COMMON_INT_ARRAY_HPP

#include <cstdint>
#include <iostream>

namespace boost
{
namespace sort
{
namespace common
{

template<uint32_t NN>
struct int_array
{
    uint64_t M[NN];

    template<class generator>
    static int_array<NN> generate(generator & gen)
    {
        int_array<NN> result;
        for (uint32_t i = 0; i < NN; ++i)
        {
            result.M[i] = gen();
        };
        return result;
    };

    uint64_t counter(void) const
    {
        uint64_t Acc = M[0];
        for (uint32_t i = 1; i < NN; Acc += M[i++])
            ;
        return Acc;
    };
};

template<class IA>
struct H_comp
{
    bool operator ( )(const IA & A1, const IA & A2) const
    {
        return (A1.counter() < A2.counter());
    };
};

template<class IA>
struct L_comp
{
    bool operator ( )(const IA & A1, const IA & A2) const
    {
        return (A1.M[0] < A2.M[0]);
    };
};
//***************************************************************************
};//    End namespace benchmark
};//    End namespace sort
};//    End namespace boost
//***************************************************************************
#endif // end of int_array.hpp

/* int_array.hpp
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
*/