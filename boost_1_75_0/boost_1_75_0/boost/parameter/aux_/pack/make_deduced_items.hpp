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
6VxVbH3V/cij7Nr22ZpBS9s9025Vcey9ZqXz1/bI2OP35/KLOP1q9TjDdxHuSlUhH0KoLRW8M7Ot1QLxmKcWU/xYqryyk7QMggTTqdRbTvucxsmSqphthQ+3Ampnj8V0rDP9KbqtPe4LcnKs0gyTaXmjl7PSutYdHRuEri/xE268hYtbRf1hNL7Yfd6jgpaWY7FoVsGEw0Tyo2c69mJ11hD36HUv5hktIxwqI54q8iF3EZLBENSz2mpSEZev0bvlPCdcwnPlzXxdLYc5hyagznP67Hv78UDefYGDJlXulx5qwhVsoDy4ZRdL9sd03cNxZaeaV+OkmoXcCSZRm9UowjrCLVK7Xl3pk2yuNVP5UT5Ji3qXa6Jueew6qe0LDtUyFXqxjUd7BcHaOHVCc27ihlhPI+UoYlOz+rjGSMYvjP2o+02rrze1VYa6/cKvWMvrmc68ezUVDhhBynrfd2o1wfrncxw5H5IRZjYFUxBgZaPiPcKrHLOZR65OorWiwgiPcFJzrVVGXOMUutMqDjQAblhvocYpVoFQOn0ylMgTsJdxaSeNmQrVlvUORdNAeY8enTN8c44eQaYgpf1XnjeXg3o4VvaVTpd9IKMZw63DcQv4yPEWnS8KztVHRdxFjs9JfB553KtJdwMHx0Ysd4tFtBvlXvqcd9SLwUKfqqwEgEAk45O1gdlDS2iNo58bIcERCdQhbDM2q06qjTMj
*/