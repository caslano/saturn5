// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_IS_PLACEHOLDER_HPP
#define BOOST_PARAMETER_AUX_IS_PLACEHOLDER_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_mpl_placeholder
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/arg_fwd.hpp>

namespace boost { namespace parameter { namespace aux {

    template <int I>
    struct is_mpl_placeholder< ::boost::mpl::arg<I> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/bind.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_mp11_placeholder : ::boost::mp11::mp_false
    {
    };

    template < ::std::size_t I>
    struct is_mp11_placeholder< ::boost::mp11::mp_arg<I> >
      : ::boost::mp11::mp_true
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_placeholder.hpp
dGVzdHMvbGlidGVzdC90ZXN0dHJhY2UuY1VUBQABtkgkYK1W+0/bSBD+PX/FXE6AE3wkcNWp5XUX8SjoEFQ81EOlshx7He/heCPvOgRa/vf7Zm3HSYDCSQ0iWY/n8c23szPbaf+8T4Pa9OrHs/8ePvi1Fp8y9a8IzPPanvedij9Y3eD3tSAdqk2+ey163eQ7OdbEK6Ns89rzXgt0w9j4q8OWNx4vIYEZW+6p0X0mB7EhZ69F6x8+vKffaKO70XVp30+lSOjCiLQvsoFL26GV/BX7k8maFrsuCUN+sla6uoylJq0ic+dngrBOZCBSLULyNYVCB5ns40GmZGJBkUwE7Z19uj4+/ejSXSyDmJ3cq5x0rPIkpNgfC8pEIOS48DHyM0Mqgjmch1IbOMyNVOkaYgsyIhtq9sHh/UQr8se+TPw+AvmGYmNGerPTCfIsAfpOqALdCar012IznGZyDRBD/57UyJBRlGvhEmu6NFShjPgXhEA4yvuJ1LFbo0GoNOyojLRIEvYFOyl0AVvQRUmPy2o0AmJp+EerVHOou1gN5xTBI3uJ8ixFIPAApVCBZpfyNBSZVbaZVyFKTi3BL25NjTcklQIMNXsXdHzRpL6vpXbp8/Hl0dnVJX3unZ/3Ti+v6eyQeqfX7Ozv49N9
*/