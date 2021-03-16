// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H
#define BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H

namespace boost { namespace msm { namespace front
{

    struct none
    {
        // make every event convertible to none.
        // to support standard-conform implementation of pseudo exits.
        none(){}
        template <class Event>
        none(Event const&){}

        typedef int completion_event;
    };

}}}

#endif //BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H


/* completion_event.hpp
sxUd3ePo6GF1T0fH286jQ5hYfoaLlniMLlqwJ3TW6AnC5cK/tmJDDpgrJbTZ6mjDxyympTPy9aK0ylxdI7uwKDF9R8Bcn8mnUzN4LYhX2jtdrrSFa4groU/F6Bpch26ahJXaRpuxtBwVljCdmNAio0G4VsRc8QJbhlgpZCY1by4vsBKfBr3hiREY6GHa/3G9g8+H0WQd9sVoz/2vrbh8h6mBmmxcglOc2ZNx5P96uVCHodGocJGOfXGED+hgIjE=
*/