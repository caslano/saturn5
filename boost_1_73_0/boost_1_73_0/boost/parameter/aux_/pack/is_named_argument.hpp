// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_IS_NAMED_ARGUMENT_HPP
#define BOOST_PARAMETER_AUX_PACK_IS_NAMED_ARGUMENT_HPP

#include <boost/parameter/aux_/template_keyword.hpp>
#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using is_named_argument = ::boost::mp11::mp_if<
        ::boost::parameter::aux::is_template_keyword<T>
      , ::boost::mp11::mp_true
      , ::boost::parameter::aux::is_tagged_argument_mp11<T>
    >;
#else
    struct is_named_argument
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_template_keyword<T>
          , ::boost::mpl::true_
          , ::boost::parameter::aux::is_tagged_argument<T>
        >::type
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard


/* is_named_argument.hpp
0ujbThyWlu30M3YOA8Nhc6yq24MFrR4++H41X3sJ/EOUvvkYERO6kYMXxqekJ2svOeVuUIagx3JT1R9lrT/VTrIFbo4iw0ZFbkuynH7D7hldb03qNtRP0DrcosVlvSTLOYYBAm9gtpP2zCZo54o2DVm2jBqybJkw2CBlDCcqY+ie5dSDrEnvltuRgs4whc4YpT+Op1FOF473L0tfXL6sLqA8L4PXI9fpGEHzWBeut368TiME7shsLgcVlp7DYb0=
*/