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
V/gUkIeqe/HKpdyGuTg/hDfxlD8aZSAyviqb5mNVoqvn0v292gbV+sT/FvOIPbBGNj7dZKfoW1XJZt4RkXO/IUo41EpthGTI5fE5S8/2NqGlbLdptDcJkU5WfCSpXpSGWthOY099ZyVfHLDL2gQrCJmfx+kaf6qeguvxVOPGx4tUn/mQqa61Hz4ycQ3cskyGzxqMb+GvN5EdbuKkD/NMUimCza304KN27W9BiEvS/8rnveSqreHTPLomdCjTKkYo4K7mdVVIKi69tT8URM+HEynL8alIrLSK4rsSoaooG5o99jc1/MOD0s8YbBNz1CBuYmvT51p0U6Bb23e93WptVG/WjJUtTCmY7W28gx997xLUul37//36SPt1UzNvb+iHGum/vkcV1P/a7vwPUEsDBAoAAAAIAC1nSlIjanvCiAYAAM4aAAAnAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9zdHViX2dzc2FwaS5oVVQFAAG2SCRgzVl7b+JGEP+fTzG6SG2CuJBwVVs1p1MdMAkqgZRHr5FOXW3sBW9rbMe7TqB3990767XB2OYRklbd6GJnZ37zntmFO+ITz2YTuDaNljkgzfGgS66GQ+O2Q4aj8eWQXFeOkM49to2lXn29VYEq7Fwk/kdw
*/