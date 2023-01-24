// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP


#include <cstddef>
#include <boost/type_traits/make_signed.hpp>


namespace boost { namespace geometry
{


typedef boost::make_signed<std::size_t>::type signed_size_type;


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP

/* signed_size_type.hpp
vKs5zvdly4FnyGLY0qJKgxwhfjlO/gazs56aJyi6iON2izib1TniLDiXEpD2QxJ4y6ZDGeOoZ3BIQH6GcNrjI01/1KoWs8KYruS+zqDntyjpFPZwne5WVyoxBwg9Ayix6pcaBx8NFDLeXkAUQJo8MGziMwrkWIaN3CCOAuKsL+KAjoCboXZjBiaNg/YVWoEdXgH6Y62gF2Z4NC8LHJpW8dcKDTpHhAb1kPFmaNBuY4O2DAxbsUGPQeY1+m6ow6mBVsfRWJ/blbwLyVif27TF+gwR6zNXW2fT3ML7dNMIJxXGcTA3bGEcvzEG+F/4QboLMzDjbvSzVbk2nnI6ZH6aK+y9cp1ryJV0ebgLP4kFU5mdK0M/9YV+8qC+1zgaCON/4THmh7MfiD9B+jTXNoas81ipzfWeS2MamBdrKx9Df7HeXp2Xlo3u7pV3lhTByXiDkonVQm0IgfYp1kfLAYb0T6OpiNjd1C5Wy9ctuUxqPLIx3xJj/S4gdkE6Dskvd3Hia+/uoLWWj7EJmB9RyywZibjhVUKhZ1q+ZR00c7+Tje50j5mOSUxeoUzBs+SNyk61EibELNVNAShwTF1q7FIL5RL3DM9E7wVfjSfXPVJOwH/csCjWUddLGsdAuBIYSblzap1EfkToJIYDsRJScyT5jSYjbynFUkCKsG9s44gJHUVdpvt+9oVrI5YW5QH4wlHGmM+TH7hKWcU+sDz5
*/