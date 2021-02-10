// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <streambuf>
#else 
# include <streambuf.h>
#endif 

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::basic_streambuf< ch, tr >
# define BOOST_IOSTREAMS_PUBSYNC pubsync
# define BOOST_IOSTREAMS_PUBSEEKOFF pubseekoff
# define BOOST_IOSTREAMS_PUBSEEKPOS pubseekpos
#else
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::streambuf
# define BOOST_IOSTREAMS_PUBSYNC sync
# define BOOST_IOSTREAMS_PUBSEEKOFF seekoff
# define BOOST_IOSTREAMS_PUBSEEKPOS seekpos
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED

/* streambuf.hpp
glnyWFa8WnCTxjytmFMrtGkTiadUV+xquRJxWKYZlDvSTK6bCmfJXzeaFVoiKwQTPVauZ7LVSmkUCGrmUVSMAh4pnWWpHwrcuipLWfPDvxqA9VodVNgWgv3W564/60+7rY4/9CxU/cnYG3wtiF6OdFSvouFiUFsWwxvHNsiEr9DLAgs9qmeVafZZmozTOMxCWdSGy9qZ1iJJI+oAWvCQ5RAxKE/+YJu3SsC0FTXf2CrpySc8TJRMqC8FoHTb7XwAwqnnOD5RKbO3R5m5rK/WguCFt8SRC8iwCHfVdkKFIpChbVd5uPLatlYxWGxnWPAomvPgO/X5GNX2hAivl7D1E4/t8bvJ6e7bj8E1qD/6Pk6NzEoEL3ITL3G+E+Bb0QdOGqYU5L3YDvc5KNtOakM8VDwcyrnmmprVVDxwHdJph41l36J4GCKIj5KzUndBtznqEc528K/Xa3fDgT8XrbGOM7PY1FOM5+CqeVlD0IAypR8MvtrCrCHqGPY1mgtFT1pjABSFvy2lmgRZ6e/GbhDOmWehpJVK3QCoReZpSl1dvL2uzZESajTfBTYILDrPkZ1E5L0WWgiayQO4tY3JsFgg00b+B4mwawlNslDl/TVPBylgNMoEvfbg8jbg6KEpyUi7x7xpvG26ZyiZE+1y
*/