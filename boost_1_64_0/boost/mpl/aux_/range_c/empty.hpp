
#ifndef BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : equal_to<
              typename Range::start
            , typename Range::finish
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

/* empty.hpp
HwyLe68iMgwdIiGcsJOeqHWxgc4l00T2Odmi0Uw/bSCMJlXQBcabGwFgU5deYyrGamXFwXTt3MY8Ivz4HMDmX7nVwnbtcTUyr1Pms5stLNOtAl96MZ5ncM3IJBjzPR8zOGHaOdwho/juzFbv1ydckbJh1oiCKlSceWGlTaBESUVX6B8rwMWbavpJklN4cf3Pc6pQdv9ni4SBdqh2MB9t071OL189zrPIYT6t6g9Zgy0HfEcXSzHaxZE7Vh9HU3u5GWSfYvBoLfPsMg0QuebSTZMHnNFm8BxNp9AgQwvaiYd5BBAHaNbg5StE2adBZbzq02ZNZSXbjS9HDKjh4bSlb0Ou7bDA2k+Iyu9jWF+OsQqTAzywyDDJ/MNGRBQ2zzJvLeFZcoPEw5Ziw2m5m7FsJpqQXrmQsUA4gBGSiyBz1oB1UQfThHanMZZ2Iqy2BxDfBroMI1tIo9BS9dBAeZ/q3quupTtvA6FS1Wq8UnpQRrF64JtuMlqQzdvswpxcs/nS/8neTpDHtJVzmhB2uue/fxICdqPLBO888SVXg7SUQwGmvh8jJixZnq3B5g==
*/