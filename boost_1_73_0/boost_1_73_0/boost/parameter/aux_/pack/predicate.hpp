// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_PACK_PREDICATE_HPP

namespace boost { namespace parameter { namespace aux {

    // helper for get_predicate<...>, below
    template <typename T>
    struct get_predicate_or_default
    {
        typedef T type;
    };

    // helper for predicate<...>, below
    template <typename T>
    struct get_predicate
      : ::boost::parameter::aux
        ::get_predicate_or_default<typename T::predicate>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/use_default.hpp>
#include <boost/parameter/aux_/always_true_predicate.hpp>

namespace boost { namespace parameter { namespace aux {

    template <>
    struct get_predicate_or_default< ::boost::parameter::aux::use_default>
    {
        typedef ::boost::parameter::aux::always_true_predicate type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using predicate = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required<T>
        >
      , ::boost::parameter::aux::get_predicate<T>
      , ::boost::mp11::mp_identity<
            ::boost::parameter::aux::always_true_predicate
        >
    >;
#else
    struct predicate
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::get_predicate<T>
          , ::boost::mpl::identity<
                ::boost::parameter::aux::always_true_predicate
            >
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* predicate.hpp
XXslo5+Q3pQ8MvLA2NL2cXsFbiIg5OSXCpuXRKdZQ90v0fsRKSUCuiqgA30FdHaAFlJuWqqMY7UOI7pzxDUIOkWAhFnOIAx1sJWowbAuT8Bxy2wM3QTqLSNAA9PRedVnbVg6y5t8b2y4GX1Y9uwOvBNd0U6hRzUllJYxkzCVtQl48haM8wC1t/K3kCf4qRrqWDugDOCrWNiXjKKjcVsAbF5KTlrx0t25VwNwEYANPceqaQ21nSJYsptDHpYHmEgs/Ct8jtOHOX/SPzHKm+YLxrh9vR7kL/3x5wO8TW0VmKrpIP9d+R+fE5KnfuiwMw7dMiQpZsLYh65GLCtl0U4iOjFiLvTqH6oUoBrHyZpZY2W+txk2T26qI3CFLrcnW/2+K6XhY+tl4xFFprMuU+S6iuNclYKyD+HCi6Iag8EG8RxCY0pTn3SwKTU9B0MffmQlfLN3VMRLPC1ioqVL2rF4YFCI9tqdrdIVfa5sl33FmwbczGUeUGxsrOXbCst9v1gbt7zohPwzgyqBLpdYS5uGyVaL2vo2cVklVwxtUqbBLHlubogirKq2qNigxyH/l6ZWaLNSwFZn/0I2dvphoXFcvIIVTQq5SovFXjthLG+qp5PEDHOcxCZpGqcL4yBsrff+sEuwaT8SGH8mkPcZ
*/