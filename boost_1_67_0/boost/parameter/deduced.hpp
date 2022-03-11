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