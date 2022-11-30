// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_DEDUCED_HPP
#define BOOST_PARAMETER_DEDUCED_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.
    //
    // If a keyword k is specified with deduced<...>, that keyword
    // will be automatically deduced from the argument list.
    template <typename Tag>
    struct deduced
    {
        typedef Tag key_type;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_deduced_aux
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag>
    struct is_deduced_aux< ::boost::parameter::deduced<Tag> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };

    template <typename T>
    struct is_deduced0
      : ::boost::parameter::aux::is_deduced_aux<typename T::key_type>::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/if.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    //
    // tag_type, has_default, and predicate --
    //
    // These metafunctions accept a ParameterSpec and extract the
    // keyword tag, whether or not a default is supplied for the
    // parameter, and the predicate that the corresponding actual
    // argument type is required match.
    //
    // a ParameterSpec is a specialization of either keyword<...>,
    // required<...>, optional<...>
    //

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using has_default = ::boost::mp11::mp_if<
        ::boost::parameter::aux::is_required<T>
      , ::boost::mp11::mp_false
      , ::boost::mp11::mp_true
    >;
#else
    struct has_default
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_required<T>
          , ::boost::mpl::false_
          , ::boost::mpl::true_
        >::type
    {
    };
#endif

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using is_deduced = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required<T>
        >
      , ::boost::parameter::aux::is_deduced0<T>
      , ::boost::mp11::mp_false
    >;
#else
    struct is_deduced
      : ::boost::mpl::if_<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::is_deduced0<T>
          , ::boost::mpl::false_
        >::type
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* deduced.hpp
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
*/