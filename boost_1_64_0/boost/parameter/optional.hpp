// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_OPTIONAL_HPP
#define BOOST_PARAMETER_OPTIONAL_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.  In order for
    // a treated function to participate in overload resolution:
    //
    //   - The actual argument type matched by every keyword tag
    //     associated with a predicate must satisfy that predicate
    //
    //   - If a keyword k is specified without an optional<...> or
    //     required<...> wrapper, it is treated as though
    //     optional<k> were specified.
    template <
        typename Tag
      , typename Predicate = ::boost::parameter::aux::use_default
    >
    struct optional
    {
        typedef Tag key_type;
        typedef Predicate predicate;
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
    struct is_optional
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag, typename Predicate>
    struct is_optional< ::boost::parameter::optional<Tag,Predicate> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* optional.hpp
Rva+o8+eSi4jJunKdCwCgLKNE77wMedP+D1r27I0Zo3o1iptS7vAZqtaXty1Rt2fUqUlmV6vlrcQeYoL+WuoCQ63fT4NTfLsnwXsEEaRPv8Vgzwn7vZqJD8uPJ1whnsXBn94yqnmtcu1Q9ZYwbi8CmDOB2RQeYenI8UNH/Ik/ObZFRnz2fZDhlytOEupjev/5Efmaf8d1IUrxRd0wWPyStAysinsv9Y98YNTVVjBbezVOFNPBst98sUT5Z0Wb+3/Fuc3MwcDYLkJwFnLipeDrA1FkCfOKFfnKTjXenZJ0g1AtnF9TT8R9w5pTzMV7NOwqQVvG6H87QA5rCEaRgUU1GeE02p1sooYlpz7PAjQqOIK7vQ7mwlzgRQ8bk2CZjoj15oy15e5k0mOWQqcWLE6DyjTKMz6tItPf3O7kr3Z0OuBFZjIRlneNC6hlNEpaJZ83OZTaQuQDHoa5V1vhTdJIbjRWA0YvTR4gS0/aQcBblVxhap/6PMVGgsjrn3whGSbThmWeCM7F/cjMFheQR1xCPdE0I1O3FuFUoJsgeOBMVXOD2sTUALqkOTR2w==
*/