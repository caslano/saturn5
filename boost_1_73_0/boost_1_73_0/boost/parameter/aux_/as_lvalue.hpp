// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_AS_LVALUE_HPP
#define BOOST_PARAMETER_AUX_AS_LVALUE_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    T const& as_lvalue(T const& value)
    {
        return value;
    }

    template <typename T>
    T& as_lvalue(T& value)
    {
        return value;
    }
}}} // namespace boost::parameter::aux

#endif  // include guard


/* as_lvalue.hpp
LnBsVVQFAAG2SCRgrVNhT9swEP2eX/Fo+dBOWVP4tFE2rWLahiYBArYJAYrc5Np4S+zMdgrVyn/f2WmBSkxs0lw1Tuy7957vnrtbSWNNMpEqITVHTaaMui/+34i6eHak4Z/y4NknnBj9nTL3dHCaLtH+OOmK52coEjxkLNM+ns1Yohcy0hXHvn9P02dorrww/0h84lXqX3kl6nLega4XRs4Kh95BHzuvX7/CS+wOd4cx3gslqcSZIzUhM4uxn4eVd4W4vR1YehuDHEQ5CEDnhbSweupuhCHweykzUpZyCIucbGbkhD+kgisIU1kSDo5PLg6PPsa4KWRWMMZCN7CFbsochZgTDGUk5y1ELYyDnnI2Y+fSOsZrnNRqwNQER6ayDOHJRWk1xFzIUkyYRjgUztV2L0myxpSsPMl1ZpNsffRB4arVKS5YQSUW0LWD02gsxfBxMSqdy6mfuRS8WDeTUtoifpDCRCpPtIGlko3q0yTZVjLhbFWZ2Ed5L1fS+clqZT3TTaGrjUAuIYNMG6OYhkvAMbnmAsdoVE4mxIZDrxlW1Qyl/UNLHrTm0IqVoDM+w+FZBxNhpY3x7fD80/GXc3wbn56Oj84vcPwB46MLxvp8ePSe+y2ZyYBua0OWmQ1kVZeS8kD4/wYTnpCZ
*/