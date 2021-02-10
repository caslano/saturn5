/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0100)
#define BOOST_FUSION_CLEAR_10172012_0100

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/boost_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail {

  template <typename Tag>
  struct clear;

  template <>
  struct clear<boost_tuple_tag> : mpl::identity<boost::tuple<> > {};

}}}

#endif

/* clear.hpp
uBW20uEK6N5HXOTHNyxrNzWNne/dXpyjKKry8V6dYu7KiC7V3aXgmxOH4C8CH3wYjUfhVf3W0ajUhgmbNGP23iugU246xi+sPMhlWk9/qlPJEkhbWPB/IRLnv7MYDiEYL6b0fvhhfnDad7rPj6jo3v9QSwMECgAAAAgALWdKUpxDl1ZbBAAAMAkAADQACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RSQU5TRkVSVEVYVC4zVVQFAAG2SCRgrVRtT+NGEP7uXzFKv4STz4GjEr2WnuoLobjk4ih2jouEZG3sMd7W2XV314So9L93du3AcUWCD2dI7Kzn5ZlnnpngegBvvtvlBTYcvHhl7pPRRfe901zJPzE3zztk2T10f+R4TfdXpBrBo9d9dgCv8rqHofPK+lyn9jnLXpHu2oK0XyPrfJ3ZRzrpPHv/sWx2it9UBobjAzh6//4neAvvDo9OfDhjgmMNiUGxRnXjw2nhTn6r2N1doPGDD2iA1cGTgGnFNWhZmi1TCPRc8xyFxgKYhgJ1rviafnABpkIoeY0wjueraPa7D9uK51UfZydb0JVs6wIqdougMEd+24VpmDIgS4pA8QuuDcVsDZcioPQIBtVG92EsCFZrCeyW8Zqt
*/