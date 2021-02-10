// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_ITEMS_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/item.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Creates a item typelist.
    template <typename Spec, typename Arg, typename Tail>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using make_items = ::boost::mp11::mp_if<
        ::std::is_same<Arg,::boost::parameter::void_>
      , ::boost::mp11::mp_identity< ::boost::parameter::void_>
      , ::boost::parameter::aux::make_item<Spec,Arg,Tail>
    >;
#else
    struct make_items
      : ::boost::mpl::eval_if<
            ::boost::is_same<Arg,::boost::parameter::void_>
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::parameter::aux::make_item<Spec,Arg,Tail>
        >
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard


/* make_items.hpp
Gs9jSaSYqkeaMgLvSRwyLllEqCQRk2EaT+BHzImaMzKNE0Y6g7uPvf67Jnmcx+EcaKxFRuRcZElE5nTFSMpCFq8MiSVNFRFTwAbaUSwV0MtULLgPrBlRLF1IIIHMaSIFoSsaJ3QCbKgic6WW8ursLMzSBCQ/i0Qoz0I3dX+uFnYWH0GCBV0TsVRECZJJ1iQI1yQL8Icp/gVVwOAymySxnDcLUYARj85ESiRLEiAFaDGTRmRGRlYzTYQiS5A2VvhHCi6R0+NcLCqAoEIgMs1SDmxABQATCVBwk2Q8YqmG1ZN2HKw2tWr3mKSQNSKCgySk3h6R3qhOJlTGsknue+P3gw9jct8eDtv98UcyuCHt/keg9WOvfw32joFTStiXZcokcE5JvFgmMYuQYb1eJ22QKeHgFpKlK4DUliWczYSKqWISYGq1aQpzDYJpprKUBQHSEGBcj06kSEC4wAygblexBBODutOYK8DgIZq8Wdvn6hmPIXBZkMSgG/CDRq1mqdN0Bi4kmfudiNkMAtz9FNK9ybW0IoJ7JU64TiIkgN+Act+DBROWAuUpAvswTxQyiPlU+Av6C2jl+xZ5faWFdERF+MCUUUqNJZJVvo7015FRGZVV6BpISlpOXn/G1C28shQyAacL0F+j9n4wGgNI
*/