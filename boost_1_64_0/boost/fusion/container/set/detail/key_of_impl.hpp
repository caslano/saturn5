/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* key_of_impl.hpp
n8mNypCKa6dB9YV48RHHF1ZsW3rb3BPjeSt4pDKihgpRvo1uLXWlruwBLvJFtbJGezdTIc2AFZV7ODGPHydA242m4cWVlzJuGaYHvbBZ0lBJ55XsZ3Pnmv3HPhR9ujZrXIRUQC5i1D0pgdiTR9WIyjtQQs/cd40pf9X8TGYlKiRD+DRSx2s+aTJfnzwLI4hJSaPpZuVFP/ZmE6QKFDNA6VhG0TLsYD+cJaITBycZqHuuM7uRRyintyEcQ96VGDN/maLBpUTHXtbWFK+pq4hXA21NKUrHd5I/XRboPWtteOIJmxjux/N77V5EVMfZiAK5WodA9Y478oof/ZANqP53zu9feEScJLAgQcGK5WunHW/qY6dPcoAEPBHPySLhdkkSFfPRZFoNf6QwUyfW4eUz3px5oNHggd4Yf9kzcGluHnsGuMARuIUtaTb74HArBF+iacHLBQBUXWbb3hVDH6yLCaQoRk5rOcr5o42yOA2cVPTzVFV2sA1jHNppGe8yaudiktY+w3+I9EmWEdQ+9zMnXvlNbuMX6znNF0v5E4adDGblrarGG0boIgvOXw==
*/