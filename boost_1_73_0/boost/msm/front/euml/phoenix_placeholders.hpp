// Copyright 2011 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H
#define BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

#include <boost/phoenix/core/argument.hpp>
// provide some meaningful placeholders (instead of arg1...arg4)
namespace boost { namespace msm { namespace front { namespace euml
{
    boost::phoenix::expression::argument<1>::type const _event = {};
    boost::phoenix::expression::argument<2>::type const _fsm = {};
    boost::phoenix::expression::argument<3>::type const _source = {};
    boost::phoenix::expression::argument<4>::type const _target = {};
    // this is for state actions
    boost::phoenix::expression::argument<3>::type const _state = {};
}}}}

#endif //BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

/* phoenix_placeholders.hpp
+9tDHGfx4JDY82RqZ7rX1b+AuUt0r9XcQ98P3Ptp9Ha5KBsMEt3AvglEHO83G53ExSTYk25MGH1/wjai4e50gLBHoiKX12EgjDZofAneBJh/sxdyfFzx8W06zSb8IeL4brxOjy8ZO5E3KWayjsrAbgIsBKgMjN9HcL2dJLx7uloT7H2HCUO3hgJfocbP5M0ljQxpud7qVjGMbYrFjsXhbOvimsFKvdnmuQFrE1+Ft1FdZOWC
*/