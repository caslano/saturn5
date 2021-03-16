// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_AS_PARAMETER_REQUIREMENTS_HPP
#define BOOST_PARAMETER_AUX_PACK_AS_PARAMETER_REQUIREMENTS_HPP

#include <boost/parameter/aux_/pack/parameter_requirements.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/aux_/pack/predicate.hpp>
#include <boost/parameter/deduced.hpp>

namespace boost { namespace parameter { namespace aux {

    // Converts a ParameterSpec into a specialization of
    // parameter_requirements.  We need to do this in order to get the
    // tag_type into the type in a way that can be conveniently matched
    // by a satisfies(...) member function in arg_list.
    template <typename ParameterSpec>
    struct as_parameter_requirements
    {
        typedef ::boost::parameter::aux::parameter_requirements<
            typename ::boost::parameter::aux::tag_type<ParameterSpec>::type
          , typename ::boost::parameter::aux::predicate<ParameterSpec>::type
          , ::boost::parameter::aux::has_default<ParameterSpec>
        > type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* as_parameter_requirements.hpp
Q23IuYcyGQJ64XsnnhJ7J5L3YW3IGqtu+HTuZEiCMYLv53tG9CFrRD1t7pWI+LFm7qNZZcJjJjWen/M9G8/u5Z6N1WLPRkjs2XjOs2eD7YCdHguH7U1o/jtTm0QzZavq8HMia59Oc2MXNccaQmeEK5zyJEsOL+6lHF4ScpB7El/2yEFUvfQdvA9shHt/YDXfSVzM67Xz/YHiGf1s7Q981dPvnu1RXtbMPnq518183ky9DXMfH0OwdjNxmbFaHmk=
*/