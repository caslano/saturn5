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
HF/T+XVAg9QIE9GX85ufL3+9oS/HV1fHFze3dHlGxxe3wPrl/OIU9RZg0sRPlWYDZk1iVJWCc0/449aL9NE3qIXJUuh0gt3UOpu2j+nRud/5GIrzqCkX6jNSegzhZOa6w0RAEnbaE6P0HhUxNdSwBdoC9raQWVmjP72GmdLanW77qKjg1OnsqTbmzYE8Zlj6ntJFSmjRoZBMgzHSEPKONpHJToO+4/LfhODjR+iHWkiflVOt5ZJ2Zcnsvn9GsSTizX6rNRpTJxeaDqlzfPXpt993/6DJBFVkCkzFGfoRLy5h7HgjQICpB14qf7y+ttzhB0bYce9dwBwl+zNjB+k5kZYMOQ/qu4XFHRdYAewslRbS0vXN6U9XVxRkBWf3bp8evNfr9WXQOKqKZXgWUXDgvwXdKSJOecnhwdnHbpOaW2IYdhI6/IficKiZJ2lZqmwCPfK66vbD+KWvW7O0t7f35/bn+ROXZgH4J221aaupAPWD2f56RT9Yi+u//g9gJ1My7bv12I2Ob4Be7ZlvsDASIBOmoTFL9qxUhsOz7v6SVbPFAKHddbyOtBGT3r1bCOBfmoxX2cvU2FWs6XXBP+2BF+ir5X4L0X8lDsF4xR2wG3PcVSy3lnvXtyXGKRu5iSmwtkM2fD+/xHj+lvI7
*/