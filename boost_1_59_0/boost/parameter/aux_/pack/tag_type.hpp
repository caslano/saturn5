// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_TYPE_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_TYPE_HPP

namespace boost { namespace parameter { namespace aux {

    // helper for tag_type<...>, below.
    template <typename T>
    struct get_tag_type0
    {
        typedef typename T::key_type type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/deduced.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/eval_if.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct get_tag_type
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_if<
#else
      : ::boost::mpl::eval_if<
#endif
            ::boost::parameter::aux::is_deduced0<T>
          , ::boost::parameter::aux::get_tag_type0<typename T::key_type>
          , ::boost::parameter::aux::get_tag_type0<T>
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using tag_type = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required<T>
        >
      , ::boost::parameter::aux::get_tag_type<T>
      , ::boost::mp11::mp_identity<T>
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct tag_type
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::get_tag_type<T>
          , ::boost::mpl::identity<T>
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* tag_type.hpp
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
*/