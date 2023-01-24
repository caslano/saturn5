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
HsOuc8bld2LOtHR8QCbr94mxVk5dcGFCqf+tFFPqR4u81mHQoxpT0kW1l/z0oJMsMZxVlhpMa8PSRctPf5oPrm9ivpia+CSCGw9Nm1mEVXeuUrl3WynL2Sza0Wz71pIdu/V5jeQ23lfWmwo/b49YfaGAvi+XjeuHmmSBfZKNlupTNX7jL0yFJVZpy3pQNzmy5u4aerblzXWFItfCMx8vSIm3nIISewtFYVrRzyqpuqspjg3Yj38xZ6pV8XHJGR0JzDyGXzwl/dVGUG9sv46utKHNnkNOvt6t1qRG28HfY86shvV3pV7ojVYIQcv3sdwXnQiLj6YfgM8Xn1WRa9sKBvHPsPDPV7Lh03xo4Spq0mOfY5bsfkfuTHYckApHNNRiQPflOq94Ce2i8po8jvjx7IYF1UBPAO0sYmEFWFle2etnVIN86cOPHlPspjWOYmAB3+CAV8J7RE9iDwTtCjoPGqq+SSJfwVLgOISZ+2VMnERUfIIYWBZ0reqbqRS84FTgiAvIzi2Afq3IEBGbiE7dYO3kNcveCHEEx+dsoWcLAGXYCywETwOtAjDUgS8FZYZAg6ZkplET0xQSemG6PztYHr+/XmUDRjVAfR/9Dacap41eIJO6vhi9hIIHKnr/mvzECgpeZn8Tb4OI6xIHKhuV1P6R/KKFJSldcUubwrCeFVJfjcFbnAe6Z3xv/RKnqX+Gq0+BCfsZa3voauqG
*/