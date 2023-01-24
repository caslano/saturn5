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
gOs4VB1/MwRH8Hhgh05QGG3z7A+U61BU2i/XZM8Vn4+Yf/iaPBRiXFu9/Fz7y4bfTGfaKnODeO80HULV/bPAabb5qPtitZS9gnKW/pwrdq9z1JAJ0kk/p3cDr97L55cJWY+HafYk/0amDWig4d+m9i89Byo/niCt41kcsKX3u5X4LLUNxvsuGFF1dR9nHpNtXYALB386IrsxywITbiTkh7Lc+wp8DLEI+K3Orxbujx/BV2DarIvCP2BnX8dizEZY5o75aj4zYR4NHrV6fi31EtTLxfjW6glVFiSc8fecVNfb7tyeVl/JvbHt3MqdPMLsh9q1xO9skuXn31VIZmo8/27BVQSbncr7WuuomNy1OLJ/8rH2dxabtqrEH/oibzAb+aFuhyosvsmNOUoD4wqp0rvzD7bXAnEqDb4806RKw4o3rNqhL+O3LTBITR6QpgnjR3BKppimqHwCNeQ8G9/Xvtbp4Di6mLCVGSmgJ4m1KdFkI1IaGTu2AitgvG3Ue4Gso++O5khzxgMW4QhaiZxFLWAPB34z1GD1m3YmaMdsAlrx3AcixSNRjth2SoakwNciSY0ftDBQjBk6IHYcQROR/S+evPF7eDF+7oPukldDATkvrNRO8Bi0Y7jnOSAxtHM6A4CuayDH01yknslDChbxoFPgxdLxusa+vE/nGubc8JqWwPOyld4rNArwO1S3CHuC2gGXEpVNprYhQPcI
*/