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
77/FsHjR5xXQNMatTuwLAeN2pSLP5tgWtKxMttiWo/CEBaC3HCEhVFVsxSad/YsOtRmHVEBDaR3AsJq3Q3NV1Zz3JOejBCmyaVEe5z8GX1QD61J8QdKDmbllpjEKMH9hyMWUVanTTSN90dzU6jjkkSWMVHcCcGKJ5bY1wwwAI+qCou1ZHb82fWn25CGncg8uq8jY4kLVw7OO+zMVhYThv3+niioCG7qlV3g/446olRweqAe4qVhf3qNZFMAIVX76lPgPqVB31xkFcP0XK8XiK/mi9X1LUx2+MMmUtCJAQtg5UbLy5hqYqNZ/CsxlbOQACrvU7bME1u+goLM2kS5c2t1sPOKTZ20nRRZWg/QouVm0+NOOE+s8WhBAkcic2hLpBn3QhET2loiRoV20szrK0SFBwtNqnAEocPpg5k7Eb+EFevGgFslcFWMAmk+h+CYaOiF/wD75Ddp4CrluAVaRswwlbve37OF/WRTCeJF7PoLxZvRoPyV16vvs0Ihc/DtoA79uiFWdNd2l4/m42VYlzbB2+xNwSEMFBXLGZr98h8UwRjaq/a66YnuM+Q==
*/