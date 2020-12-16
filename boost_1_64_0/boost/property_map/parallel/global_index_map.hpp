// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_PARALLEL_GLOBAL_INDEX_MAP_HPP
#define BOOST_PARALLEL_GLOBAL_INDEX_MAP_HPP

#include <boost/property_map/property_map.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace boost { namespace parallel {

template<typename IndexMap, typename GlobalMap>
class global_index_map
{
public:
  typedef typename property_traits<IndexMap>::key_type key_type;
  typedef typename property_traits<IndexMap>::value_type value_type;
  typedef value_type reference;
  typedef readable_property_map_tag category;

  template<typename ProcessGroup>
  global_index_map(ProcessGroup pg, value_type num_local_indices, 
                   IndexMap index_map, GlobalMap global)
    : index_map(index_map), global(global)
  {
    typedef typename ProcessGroup::process_id_type process_id_type;
    starting_index.reset(new std::vector<value_type>(num_processes(pg) + 1));
    send(pg, 0, 0, num_local_indices);
    synchronize(pg);
    
    // Populate starting_index in all processes
    if (process_id(pg) == 0) {
      (*starting_index)[0] = 0;
      for (process_id_type src = 0; src < num_processes(pg); ++src) {
        value_type n;
        receive(pg, src, 0, n);
        (*starting_index)[src + 1] = (*starting_index)[src] + n;
      }
      for (process_id_type dest = 1; dest < num_processes(pg); ++dest)
        send(pg, dest, 1, &starting_index->front(), num_processes(pg));
      synchronize(pg);
    } else {
      synchronize(pg);
      receive(pg, 0, 1, &starting_index->front(), num_processes(pg));
    }
  }

  friend inline value_type 
  get(const global_index_map& gim, const key_type& x)
  {
    using boost::get;
    return (*gim.starting_index)[get(gim.global, x).first]
           + get(gim.index_map, x);
  }

private:
  shared_ptr<std::vector<value_type> > starting_index;
  IndexMap index_map;
  GlobalMap global;
};

} } // end namespace boost::parallel

#endif // BOOST_PARALLEL_GLOBAL_INDEX_MAP_HPP

/* global_index_map.hpp
COgC4oAVOIEPVIN6sBMcAsdAF+gD14ASiXkAsSARpIE8UAw8oArUgUbQAtojIX8k5I6E3CDiIcgN4kEqyAB2UABcIABqQANoAm2gEwyAIXAD6MdBbpAM8oET+EA1qB8H2cFecAgcAydBF+gD14AyHv+BySARWIAHVIE60AiaQQs4CtrBRTAMJuImcwzIAHbgAgFQAxpAE9gPWkEb6ATdYAAMgRtg6sOQHyQDI8gHTuAD9eAQOAn6wCC4BpS3QGYwGSSCNJAHioEH1IFG0AxaQDs4Ay6CYXALxEdBbmAHBcAFAqAGNIAmsB+0gjbQCbqjIDsYAvpoyA6SgRHkAyfwgXqwFxwCx6IhP+gCfWAQXAPKI9ABTAaJIA1YQB4oBh7QCJrBUdAOzoCeRyA/iHirosSAeJAKMoAdFAAXqAFNoBV0gm4wBPQTFSVqImQHcSAZGIEVOIEP7JwI+cGxiZAddIG+iZAdXAPKJMgOYkEasIBiUAcaQTNoAe2gB1wEw+AWiHgUdgNiQCqwgwLgAgFQAxpAE9gPWkEbGABD4AbQvw06gKkgDhhBPvCBalAPdoK94BA4Bk6CLtAHBoEyGTpMRgFiQSKwgDzgAXWgETSDFnAUtINhEDEF4w4ygB0UABcIgBrQAJrAftAK2kAn6AYDIOoxyP4YZAfJwAisIB84gQ9Ug3qwE+wFh8AxcBJ0gT5wDShvhx5gMogFiSANWEAx8IA60AiaQQs4CtrBGdADLoJhcAtETMX8gBgQD1JBBrCDAuACNaAB7AetoA10gm4wAIbADRA1DXqCOJAMjCAfOIEP1IOdYC84BI6Bk6APDIJrQHkH9AOTQSKwgDxQDDygDjSCZtACjoJ2cAb0gItgGES8E3qBGBAPUkEGsAMXCIAa0ACaQCtoA52gGwyAIXAD6GOgWwx0A8nACKzACXygOgY6gWOgC/SBa2D8dOgBEoEF5IFi4AFVoA40gmZwFLSDM6AHXAQRj0MHEAPiQSqwgwLgAgFQAxpAE9gP2kAn6AYDQP8EZAdTQTIwAivIB07gA9WgHuwEe8ExcBJ0gT4wCK49IcnVeDAZJII0YAF5oArUgWbQAtrBGdADhsEtEDED+oB4kAoygB0UABcIgBrQBFpBG+gEA2AI3AD6mdAHTAVxIBkYgRU4gQ9Ug3qwE+wFh8AxcBJ0gT4wCK6BybOgFkgEacACqkAdaAFHQTvoARfBMLgFIuKgC4gB8SAVZAA7KAAuEAA1oAE0gf2gFbSBTjAEbgD9bOgEpoJkYAX5wAeqQT3YCQ6BY+Ak6AJ9YBBcA+PnQBcQCxJBGrCAPOABVaARNIMWcBT0gGFwC0x8ErqAeJAKMoAdFAAXCIAa0ACawH7QCtpAJ7gB9PHQA0wFcSAZGEE1qAc7wV5wDJwEfWAQXANKAnQAiSANWEAeKAYeUAXqQDM4CtrBGdADLoJhEDEXeoAYkDoX8oMCEJgLuedC7rmQey7kBd1gaC7knguZn4LMIBkYgRP4QPVTkPkpyAwOgWNPQW7Q9xTkBteeksXGeDAZJAILyAPFwAOqQB1oBi3gKGhPhOyJkBvcAhFJkBvEgFSQAeygAARADWgCbaATdIMBMARuAP086ACmgjiQDIzACpzAB6pBPdgJ9oKToAv0gUFwDShPQxcQCxJBGrCAPFAMqkAdaATNoAUcBe3gDOgBF8EwiEiGTiAVZAAXCIAa0ACawH7QCtpAJ+gGA2AI3AD6FOgF4oARWEE+cAIfqAZ7wSFwDJwEXaAPDIJrQJmPuQGxwALyQDGoAs2gBbTPh9zzITe4BSIWQHYQA+JBKsgAdlAAXCAAakADaAL7QRvoBN1An4r5SIXsIBnkAyc=
*/