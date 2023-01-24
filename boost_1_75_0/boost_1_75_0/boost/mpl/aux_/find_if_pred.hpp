
#ifndef BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Eric Friedman 2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include <boost/mpl/aux_/iter_apply.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Predicate >
struct find_if_pred
{
    template< typename Iterator >
    struct apply
    {
        typedef not_< aux::iter_apply1<Predicate,Iterator> > type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

/* find_if_pred.hpp
n8sf9LXD2k3mhivhyhtuJaWx7wB+oQH+5gq2ep1wqcxIQbtJ9gvIkRedRvgQYtFg8W7Yvas9LzltI1CNZ2+CvDr/t/V4Y/gzhLF+p8rOdVSAwAz5+jtDj7PdHdrjRpoeHvVnZBnJ4Rwhr7cvsnuY8HcBHcsPn/+BXn48g4uPil0yhQQWoaHtUov9JmN8hTzWvAQV6sJ6GRYMjxjdcf9FHSkGyktERJaVmSqU4qPP7SV9h4sNKShX4kT1jGkHZhpLsXC1lPRGulPgS0tI70j/o2rz9bOZP5NBjSPzt1z71B4JYMSdcxoC9NQea4gzrvRYZ0BsV2fHvRp6dS0yBi+K4kII/QUkkfAvEgOdRakc4wbIFIkh4RYJA/c8isSwOBlT2RrcXeKietTnHBrFVhgd7WDUFg0DW8A+fX1n3D0CeIna+B81Ti66y06kHZNL+M7O1gR2rbdHKh2JkR57U8MlRyMZipZfJ+jgu+ZN6cyQab4bVoP1XCbHnEph+3cOW9PUJrw0+PC1aEuYhRHyCKimJqfsVhwncS4vVdR9PTSUyDTAqLEGLb4kFHEFj4Q1trq01IrA/imeMavUqMJz3eSQGZRCo2hFRYfpgbLzH9me8t5s7JSx6GKdgowtY5FBhnXYlJLDHwtLA4uKvHDETsFuwS1RQ8KoVtPNW4Mr5HG3WvbQ/YmU3Ojxtuh9givZ5qr2Ro69utRZRr4FVKlF
*/