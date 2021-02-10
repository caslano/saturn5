// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_DEDUCED_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_DEDUCED_ITEMS_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/deduced_item.hpp>
#include <boost/parameter/deduced.hpp>
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

    template <typename Spec, typename Tail>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using make_deduced_items = ::boost::mp11::mp_if<
        ::std::is_same<Spec,::boost::parameter::void_>
      , ::boost::mp11::mp_identity< ::boost::parameter::void_>
      , ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_deduced<Spec>
          , ::boost::parameter::aux::make_deduced_item<Spec,Tail>
          , Tail
        >
    >;
#else
    struct make_deduced_items
      : ::boost::mpl::eval_if<
            ::boost::is_same<Spec,::boost::parameter::void_>
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::mpl::eval_if<
                ::boost::parameter::aux::is_deduced<Spec>
              , ::boost::parameter::aux::make_deduced_item<Spec,Tail>
              , Tail
            >
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* make_deduced_items.hpp
LHkqf1skexyNOfHP3z3u1oJwigaiTQzjIPCcR7QWOs88TdKInVcogYb5OmW354xm2Q1hkXLyPbmcapei5tuOr88yhR2lw+L+qDycHXAc9xtl3TeirtdOSnzZ/o+iotNOijvZ/jO6IW/Lm/IcaUqm2jKpykuNiU9bJkC5WaLY0I7LDtnuIxGc/BUyNLEaWQU2YgXpMbIFPUu96FGqoPGFSFFF9/e/lyhvJVXFUFSMtwglNLn02ZWd2EO60E6hqHg7jw99XvkPUEsDBAoAAAAIAC1nSlLMgQPM1g0AAIksAAAkAAkAY3VybC1tYXN0ZXIvdGVzdHMvbmVndGVsbmV0c2VydmVyLnB5VVQFAAG2SCRg5Rprc9s28rt+BU6eTKg7mXacuHf1VJ0qspzo6pF8klJfLs1wIBKSWFOASoByNG3/++3iwYeednrfjpmJKXBf2Bd2AZz85SyT6dkk5meMr8hyreaC107I6V9PSSiimM+uSKamp//AkdoJfCF3qfiFhYrseoIg+J2YfyQgP8NfxDjwnJEC4/egQY5i/E48jRFYHt/hexAcYfMzCob/nSHizwG+woieUEcs12k8myvidRrk4vzV38kp/Lk4b5JrymOWkJFifMLSWZN8F+mRH+b0yxdfsu+bhClCE18T
*/