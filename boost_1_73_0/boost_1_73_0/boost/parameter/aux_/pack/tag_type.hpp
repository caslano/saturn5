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
7v9+CkF/NVzWID2BbTZ4arhpNVG3miu+ebgQSwirY98FFERzt4DVOBbwPyjEZQl3GFrVejstlGHBYehuVKq3BL+zRAWHYI+30XFHM6+lmtCOPyFIx0mDCU89+qK1GH8bDPGi/gdQSwMECgAAAAgALWdKUliAjz3gBAAAHQwAACEACQBjdXJsLW1hc3Rlci90ZXN0cy9vcHRpb25zLXNjYW4ucGxVVAUAAbZIJGCtVm1P20gQ/p5fMSRWaxfHhn67BnogOCg6HVTAXYWa1nLsNd6r47V27UAEud9+M7vrJIYg7qQuIrZ3Z56ZeebFHmyFjZLhhJchK2dQMVn0Bu9+3uoN4NUV6f8IF15J4bMUf7Ok3iwcRY9g/lBpjNdXTISw0niMPHhV4xFcrRFZG3t0H0WvmBmTY/QTkuI4olvc6Q1Q70hUc8lv8xrcIw/e7+zuwBAv73d8OI5Lzgq4qlk5YfLWh71U7xzk8f19oNhHH1gNcRFooOucK1Aiq+9iyQDvC56wUrEUYgUpU4nkE3zgJdQ5g4wXDI4uPt+cnZ/6cJfzJEeMuWhA5aIpUsjjGQPJEsZnBqKKZQ0iQ23ETrmqEa+puSgDNM2gZnKqEIKMx4USEM9iXsQTNBPXkNd1pT6EYdLIAj0PU5GoMGlD
*/