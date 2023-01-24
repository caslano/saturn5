
#ifndef BOOST_MPL_RANGE_C_HPP_INCLUDED
#define BOOST_MPL_RANGE_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/range_c/front.hpp>
#include <boost/mpl/aux_/range_c/back.hpp>
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/O1_size.hpp>
#include <boost/mpl/aux_/range_c/empty.hpp>
#include <boost/mpl/aux_/range_c/iterator.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<
      typename T
    , T Start
    , T Finish
    >
struct range_c
{
    typedef aux::half_open_range_tag tag;
    typedef T value_type;
    typedef range_c type;

    typedef integral_c<T,Start> start;
    typedef integral_c<T,Finish> finish;

    typedef r_iter<start> begin;
    typedef r_iter<finish> end;
};

}}

#endif // BOOST_MPL_RANGE_C_HPP_INCLUDED

/* range_c.hpp
Q4T9fpV8j4PwZSi7YkIKJn7yUUFtX4hffF6kXywlkx0ptDppXOfIxzbusuvb4EDKKegjuUDKjTdZr2cckGruZ554wNi4AbQnOpAV4HzN7HL3uyZDYbee8fA9Q+GFs0NtLMBzysWh9rTX8yK5z/MiqOvtVN6U38ir+1C1uE3ROvuisXuyqgGjMiZ1jkM3TO6ga+Yo5cKcZVBtokVJ6GbRvAb4BQTUqKhUdVBfom+hI06eHAPc/Mb+k3wCvO29e74x62pYs1idAZ+oQLIzWkTmbAGjdErEbetc8YJpeHtelvrjrFvsdoDkiVYOw2uz/sWHl/Tbu0uRQRg5U7R+tC+Nr9/jXcOYKTTgBi4FCtutOz6rm2Y57abVx7uDpdFdm5niwSBabq5FQqZf8Ye6UZ9Ja0yWQFLPd0Z+7VY0MJG1bp63l79udDdsgIP69dwJwwanOvVOe3KftZh+iMDo7VKmAwyeaOscB7YMdmAOUeZ8T3ftlfpwsN8k5M7jQ2B1xzVhuRi58QbRQsQYTKKJXDvTdZpMP2AULma29LCmTW2zi4THy1DATvnXpwDaBHA08izsT42fbkgXG/UfG//9Hy4zE7c/1j2LjaujQ6zGtmPmF2yo9s/FNNn3YkvFBkVCdorklMx6mu1WaqPBtpguFXUJ9gUeH2CvcdgbXNbzXYEQSOvrpXE/Q3Ut3BmeMZPNIA1T5Ec8do1QiySM/qw4
*/