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
DFdYek4X35qWCHCgHJkSQramCahdllQdw+617wPrSJEPMQJz7zTdv/YkXBIKC0jB72wpo1pVqddcCf1iwZWSAhOpH70kh5cHlOCxSFEPD4HehobKrKTe+YBVy3d6JTLH4koOBX1d00BGyo+FCkqIa4QIa86xvI6X6GMhs74lARNjjXpBU20yjmYbO2mU/pXggstoSy1+shv6WLpTf2CBQstOjQu6z4xJ0jl+z8yyOmKDUQtxeY5uFBc/KM8gJf8a7T/5nxnR4KTdABnHLljBKYOH33UAPl0Oo9g8HPKfodK8o28Th0371RTKg0H+F2KLWXRQe90U5d3Uoc4iATO7Y9twCn5utGTCWAMJVK1ABDslvN/sv1LpN7JGl/er4lQswqJzyXyzSD6TC3hRIrOj290kA+6yXN2C8wsM4P/uYIc1Vo3rlr1egphW0xS/OpC/xtVxpJP4VH+/CaFOEBCKfxoR+zMZMNxiZ/K0Ul3jvYwzLcjycXlCR3tGAqe3x2oNyCxeyCLWw2NEJ0lc4QiKJz6X5/RZX4NXuRrLVEn4sIASXQp3aBQnB2DzXw==
*/