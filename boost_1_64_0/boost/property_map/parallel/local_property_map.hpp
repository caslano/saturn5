// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

// The placement of this #include probably looks very odd relative to
// the #ifndef/#define pair below. However, this placement is
// extremely important to allow the various property map headers to be
// included in any order.
#include <boost/property_map/property_map.hpp>

#ifndef BOOST_PARALLEL_LOCAL_PROPERTY_MAP_HPP
#define BOOST_PARALLEL_LOCAL_PROPERTY_MAP_HPP

#include <boost/assert.hpp>

namespace boost {
  /** Property map that accesses an underlying, local property map
   * using a subset of the global keys.
   */
  template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
  class local_property_map
  {
    typedef typename property_traits<GlobalMap>::value_type owner_local_pair;

  public:
    typedef ProcessGroup                                   process_group_type;
    typedef typename property_traits<StorageMap>::value_type value_type;
    typedef typename property_traits<GlobalMap>::key_type key_type;
    typedef typename property_traits<StorageMap>::reference  reference;
    typedef typename property_traits<StorageMap>::category   category;

    local_property_map() { }

    local_property_map(const ProcessGroup& process_group,
                       const GlobalMap& global, const StorageMap& storage)
      : process_group_(process_group), global_(global), storage(storage) { }

    reference operator[](const key_type& key)
    {
      owner_local_pair p = get(global_, key);
      BOOST_ASSERT(p.first == process_id(process_group_));
      return storage[p.second];
    }

    GlobalMap& global() const { return global_; }
    StorageMap& base() const { return storage; }

    ProcessGroup&       process_group()       { return process_group_; }
    const ProcessGroup& process_group() const { return process_group_; }

  private:
    ProcessGroup process_group_;
    mutable GlobalMap global_;
    mutable StorageMap storage;
  };

  template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
  inline
  typename local_property_map<ProcessGroup, GlobalMap, StorageMap>::reference
  get(const local_property_map<ProcessGroup, GlobalMap, StorageMap>& pm,
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>::key_type
        const & key)

  {
    typename property_traits<GlobalMap>::value_type p = get(pm.global(), key);
    return get(pm.base(), p.second);
  }

  template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
  inline void
  put(const local_property_map<ProcessGroup, GlobalMap, StorageMap>& pm,
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>
                 ::key_type const & key,
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>
                 ::value_type const& v)
  {
    typename property_traits<GlobalMap>::value_type p = get(pm.global(), key);
    BOOST_ASSERT(p.first == process_id(pm.process_group()));
    put(pm.base(), p.second, v);
  }
} // end namespace boost
#endif // BOOST_PARALLEL_LOCAL_PROPERTY_MAP_HPP

/* local_property_map.hpp
8IFqUA92gkPgGOgCfamQG1wDykLMBZgMYkEasIA8UAyqQB1oAUfBGdADLoJbYOK7ID9IBXZQAAKgBjSBNtAJusEQ0L8bsgIryAdO4APVoB7sBHvBIXAMdIE+MAiuASUNsoJYkAjSgAXkgWLgAVWgBRwF7WmQGfSA4TTIDCIWQW4QA+JBKsgAdlAAXKAGNIAmsB+0gU7QDYbADaB/D+wGTAVxwAjygRNUg3qwE+wFx8BJ0AX6wCC4BpTF0AUkgjRgAcXAA6pAHWgEzaAFtIMecBEMg1sgwgh9QDxIBXbgAgHQBPaDVtAGBsAQiDJBbpAMjMAK8oET+EA1qDdBdnAIHDNBftBlguxASYfdgMkgFiSCNJAHqkAjaAYt4ChoBz3pkDsdcoMIM2QGMWbIDVJBBrCDAuACAVADGkAT2A9aQRvoBN1gAAyBG0CfAb3AVBAHjMAK8oET+EA1qAfHwEkwCK6B2EzoANKABXhAFagDjaAZtIAzoAfcAhFLID+IB6kgA9hBAXCBAKgBDaAJ7AetoA0MgCFwA+izIDOIA0ZgBfnACXygGtSDnWAvOASOgZOgC/SBQXAtSy5GjQeTQRqwgDxQDDygCjSCFnAUtIMzoAdcBMPgFojIxvyAGJAKMoAdFAAXCIAmsB+0gU7QDYbADRC1FDqBZGAEVuAEPlAN6sFecAicBF1gEFwDyjLID2JBIkgDFpAHioEHVIFG0AxawFFwBvSAi+AWiLBCBxAD4kEGKAAuEAA1oAHsB62gDXSCbjAAhoDeBl1AHDACK8gHTuAD1aAeHALHQBfoA4NAycFcgMkgFiSCNGABeaAYeEAdaAYt4Cg4Ay6CYXALRORCDxAPUkEGsAMXCIAa0ACaQCtoA51gAAwBvR06gDiQDIzACvKBE/hANagHO8FecAycBF2gD1wDynLoA2JBIrCAPFAMPKAK1IFG0AKOgnZwBlwEw+AWiFgBfUAqyAABUAMaQCtoA52gGwyBqJWwJZAMjMAK8oET+EA1qF8J2VdCdnAIHFsJ+UEfGARKHmQHk0EssIA8UAyqQB1oBM3gKOjJg8x5kDkPMoOIVZAZxINUYAcuEAA1oAE0gf2gDXSDATAEolZDfhAHjMAK8oET+EA1qF8N+VdDfnAIHFsN+UHfasgPrgHlvdABTAaxIBGkAQsoBh5QB5rBUdAOesBFMAxugYh86AFiQDxIBXbgAjWgCewHraATdIMBMARuAP0a6AOmgmRgBFbgBD5QD3aCveAQOAZOgq41yv3t/nZ/u7/d3+5v97f72/3t/vZ/ub1DeTg6DGXN+tBzQkW59syclSutRSafz+Mu26Bcncn6qZ6R+qJ1aqDIH3BUBoK+Ikfluo1F3nKnivqZyoPRuqjQs3lFJZUBqVKrfI4yp+oMfQp61bKAP7TfjGgFW4sysu8/bw7bHPZbPKyM9FvkKS9xeLCv011e5Kt0lwVKi8p9AXd5mV8JyahgO6QbabPI7fUVYXOEBHGXry0qDZaVoNr9Du7XNXq/Eo/qqFQrKxWl6DHWt46uLy3xlPtVRas7OqZOLS9VlDt1zWPrKivLK+/UtYypK/UE/a47dd1j6tapoXHSZG0aVYdKt0ctK1dGyRoYc2y5Ty1TyrW6qjF1larDebeuekydX1U33K2rGVMXUD2eu3V1Y+o2VboDqjKXdSfHyMq5Kin3esvLijaWyqSFfnLiUc3mWnShudVq/FofZ8a0M3b868fUeUYE1+oaxtSN6HtnHBvH1PnVgBiaVzt255h60Uur6xtTNzLGyhLW3TgXetRocVGu2OLKQHmlY51qXJy0ePG/s1mjcaEx9Div7mElIno6/rGpxOWoLAoooc8+vaI=
*/