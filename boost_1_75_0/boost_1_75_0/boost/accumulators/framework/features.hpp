///////////////////////////////////////////////////////////////////////////////
// features.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005
#define BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// features
//
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
struct features
  : mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
{
};

}} // namespace boost::accumulators

#endif

/* features.hpp
WAwb+2ngja19ak3DEbQD4jGhQVG7cWHI4nCVSlNSWc97xDbKbVn1Rv6hDmTjP4ys2q5H+W80Uy9si9cLf4bfUvh1mvXCA3CXp6Qa3s9BVSc70Lgml6HNIe60OKXpAqEB2q8UImXbCSM66aPj1YZ4R7dxu9TPleyp9K1mmT5kRYHQZDfRigUe47PVeyGV3qzWOZAnclSZhc4k/SC5dTc898Iv4zI9ya0xzcXk1gPz4fu0y87nSa66uDw7Gd4j8Pjo3feeTWm0nubfMo6wRu9UHtNxOjswtzXf0GGj75EL3NnSL+SWL2Ot6lF1RI6l3ynKHDSDK08HwO2Nk4tM0lBiqUJdURLq+W9Hamn6Lqk8eUWxUijuHCdN3xXpgga0FvykCxzy3dZ1e2tBnw5oXQhJFR2RrfAuqzyFJ5NAXe+XRNAGqXgzcNubgM6NvKrTpKw5KBYE4CdVnMysAJqDqODpJphRO9PDtvdHKaOjUvERKPeJpoqfVkwX/Icw1AcQTCreDdBFqujxA675YT9A12ImVRxHuuJ+nE4P4dq2Rfnl/4V38hOIgPjXPpSmH8clWI70W7u8E1DJAGI2eRdJrDqgJShhfjwsVRxoKlbkc/JhqWKXVBfNKjhZc72/3XutXHAcOuxXcl2HA3nXIWfwvOP+nZAdNyj5wE0HUMQhtwAANXO2HQiRavfIUwTD+1Lx3qzyZP4h3KDFYjul6Seg
*/