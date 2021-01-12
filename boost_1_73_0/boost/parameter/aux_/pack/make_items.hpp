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
VG+bJaf62SY51cPVklN9WyM51auI5FR/1ktO9WSD5FQfjpGcyr1DcirfbsmpHDdLTuV1nORULl4940PF/A4c/2x2Oa59ibgccqz1dHn3Zs3vaGQ86fdv35a80/LvSB63/E7Juyz/ruRUT74nOfm335e8x/IfSE7+7Q8lp/r2I8nJv/2x5NSv/sTh9E1dh9N3dR1O39Z1OH1f1+H0jV2H03d2HU7f2nU4fW/X4fTNXcmpHf3G
*/