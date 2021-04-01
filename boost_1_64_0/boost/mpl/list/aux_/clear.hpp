
#ifndef BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_end type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
kYd6MA1Vl4GlH3Ob5JIJfLz6wmLnV+ULXEiA09OWtx4HI8Xoh71XPcwjCqR6bwdRU+b9Ww+//wGHRx/s4OELyW+GZKk8xSCqGfFh+BSKwc/laIqRbRV28J1cNHG5zr+QsqYcxnQTB8YgXYu9/swoV5vYeOfcfiSuSzcdvl4tD+oL9vJXCl0D4B7yPrEx89PtjhNJlF+JkQ+m5w1TOlxesFIjGvO4lQhnPogSaKEkF0Q3rDMVvVr+cWxaTZI4pkuGSVtrbH6EGjs+7bIyVoCshxSVBIq+AizfkS3QLufy+Ft5/gRTdtu/5ZRmIchTfO7jb6HRCLAocKf8I90SdZkqZwTIByatURxVAKIrVpdFiIEQGQiew0wdsQ2Gg7yO9pcUNBYAGteAQCviMJDLOUvAZOWO2FtqfNmroq3SamMNeCPGQW0KFZywYCdb/qwcv2ZLje0a3IdlSIyJGDumOnF9a9Ab0HaO1beoig5Vnz2oRyGS5laawGEQ6DZRXbzGyojE857pd0hMuNiyJgUHhBgvOJglNOmtx6KUbC/8G5HpeyRbovK9vbqaRZvrQQ==
*/