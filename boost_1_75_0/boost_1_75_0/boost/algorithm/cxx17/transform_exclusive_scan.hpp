/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_exclusive_scan.hpp
/// \brief ????
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP
#define BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T,
         class BinaryOperation, class UnaryOperation>
OutputIterator transform_exclusive_scan(InputIterator first, InputIterator last,
                                        OutputIterator result, T init,
                                        BinaryOperation bOp, UnaryOperation uOp)
{
    if (first != last)
    {
        T saved = init;
        do
        {
            init = bOp(init, uOp(*first));
            *result = saved;
            saved = init;
            ++result;
        } while (++first != last);
    }
    return result;
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP

/* transform_exclusive_scan.hpp
ymQ20N/PKUIU+Ny3gm3dTjpsJbhiZq/SOVPZLlgS2QcPtlBziVHTFr8J0Wbfuz0lYnI1A6TYXnvSoKvEkltS+RFIus7+EmbY26lKZo0PlNW56kWsrogHLE3gqyrK59hf/AkgxI/uB53fSbopTx2gW8fvdfW3Aibxb3yprwzsR1St8NeWb1FlQFYwg2xp403ikG58XlogPRdJbnOPKEj84JG7Ft7yzxewDVFx3wTnR/wbP+tTLaa62B6fi6VLAlN1VL2ExuY9omHFTBex1zq0wDEDf7fHL7QXaV1i9AMBe0C3mT+4cR7ldeYtlF7w8jJbA4CjqU3uHEzqZKncpnyFPODBAb/hG80hMPjbuTsO9+93DmPZ9PsU5B4KEDzP4S4fTjOlk0Tq1+jLEsoaG7CXNCgBCPY6e87B4v000zOUMN/VzSKAnpbn7ZS8wZDBzN9JIimdpvKF6rTgmVYNGNxg4py+ZZFoV1RvSx4I6Hqv8vDOI90rzE1d9pHt25etQyQmQciaPX+CZ9vQEz279oAH1AbmhdMko9++TtJ7K0mHiyz74GyUqhfMp3eUzoKlJ5l1+ZdadVvVQYWDgI2fReIkamE8fkJkSwdXz4hxRj5r6VZibcfPCBygqetBMTKVOdnK1MmxzF/ZNR2aZOgv90hlGCcU7j+nSjUFOCmJrPXbvnhYeQokcR15VGFK8//oivtcWNGHj6oXpu/4wk1k
*/