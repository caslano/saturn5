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
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
*/