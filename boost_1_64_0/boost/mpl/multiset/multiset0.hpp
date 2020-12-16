
#ifndef BOOST_MPL_MULTISET_MULTISET0_HPP_INCLUDED
#define BOOST_MPL_MULTISET_MULTISET0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

//#include <boost/mpl/multiset/aux_/at.hpp>
//#include <boost/mpl/multiset/aux_/front.hpp>
//#include <boost/mpl/multiset/aux_/push_front.hpp>
//#include <boost/mpl/multiset/aux_/pop_front.hpp>
//#include <boost/mpl/multiset/aux_/back.hpp>
//#include <boost/mpl/multiset/aux_/clear.hpp>
//#include <boost/mpl/multiset/aux_/O1_size.hpp>
//#include <boost/mpl/multiset/aux_/size.hpp>
//#include <boost/mpl/multiset/aux_/empty.hpp>
//#include <boost/mpl/multiset/aux_/empty.hpp>
#include <boost/mpl/multiset/aux_/insert_impl.hpp>
#include <boost/mpl/multiset/aux_/count_impl.hpp>
//#include <boost/mpl/multiset/aux_/has_key_impl.hpp>
//#include <boost/mpl/multiset/aux_/begin_end_impl.hpp>
//#include <boost/mpl/multiset/aux_/iterator.hpp>
#include <boost/mpl/multiset/aux_/item.hpp>
#include <boost/mpl/multiset/aux_/multiset0.hpp>
#include <boost/mpl/multiset/aux_/tag.hpp>

#endif // BOOST_MPL_MULTISET_MULTISET0_HPP_INCLUDED

/* multiset0.hpp
lv0dJbER49ANJ+BEnITxGIOzcTLeibH4D4zDxzEe12MCPo1TcTem4AGcJvt9On6PaViJ/ZaOVTADc1wc6xvMTt3a365ebcdDLrqDD7nc8vo1V24CilivbT0bL5r+JXVtLVluWfVtvZa7VHidW14NlzLr3XKWu9zyureCf1Vc/dvS5S63rA4u+jZXXR5pzW1/nzq1W/H73/hWRwW8/6/8/v9B9T5/nPl9fqyNDfFN5SIfaP0dFckr6qaWhpVfJY63q37aQ9tXt7xHoHlHK5Gkfkc9NT5Y81s9p2tnzW91f3mn3r2S9EePSp/qxV3sv+tv/v0Xh5bBgfcc7fWxPhPrqN5BypDPG23ek8qXd1IM8tn8fhK/1TRtqx+UbQmUsu+I+yj7yGDrtowdMWRc+Ogx/YZZGgqQHtPL8SxG3Wd6iU1er1p+7znb3/1fbH934XpjOfT/aua2lIv++a6/JTWetP/rW9P+7m6dXEfk+nLQ5v0HN7nXrYee6IGN0AubYX30Q2/siA0wBBtiLDbCGdgYj2MrPIOt8Ty2wV+wI/6OnSTONwCrY2esg4HohV2wIQahKf9yXUF3O/kfI3HN0dgYJ2BLnIjtcRIGYQxG4WRcirH4CMbjJkzA5zARd2ASHkY9FmIyfoYpeAxT8RROwys4Hf/ANFSuh+mWOHO5lmCg5F8dZ95Nyr8n1sdesh29sQv2wR7YF/tjqJR7P3wUw3A1DsCNGI6bcSBuw0GyPYPxVRyCn2ME/oxD8TIOk/0zXPbHCGyLI7EjRmKog+1/Otv8dLb5qW7zcwf3iUdJJX+j+0Xn4Bycg3NwDv8bw634/Z+ZmKOvqN//P6r66wuqVLqfn0q9eQ6t+v0/sn9UeJT8qi5vfzTn1f3RyOcEVLfRtqVS6X6oLvAhtKw8JOWWOw95NuvsJb+9b5d1epPeYrvjylonvZuVZ52dZJ3qPuWS0KZNBYd+c1dUPVxF/eb+f2srobzPDHYZf3PXq1Hy/WnvsH2/nP5yUdbc7VvLX197M7+5A0i+gWX3deEl7xDVRw/0RvN8oTKfu5356sp8blgX3VXzxcl8t9uZr5HM54Pe2Nj5W875W+4mf8v5VXPVDSMZqjl/yzkH5+AcnINzcA7O4b873JLf/wnT9Ik5/3n//8rv//N22vMPk/j/PqQDSh+0LVW/g8MiwvtHxSZm6ePpEeDG7UqW1Ve/rzX+uXTbghI7rYzMzpD4dvmcxmdz/HK0t7FdHU275ydlG3bLb/mdpK78y/LS26B0Huzwb3h/eXahXtcweW4wXsprDOmgUmHWqtS66Cr7xu3cmuvgWZfSzrtmXS1lxknojcPxXdZVbFpXfGBSrGp9pnVF2qyk7DiHqu7u7Wxi3mUfEeutaYs8kx2k3mfu0j6k7DNLH+fKPHvN7XRn62MTmMvcLvxmfvgl0zqreTnHtHEI0ja4ts1xY5uj8vkgn9V9xO+R6ZNTs7JzZJrDjHvdk7ylSSy7tGnLao3z7JZ5+JydeofeOE2hTVuvkZVNZbCLcQY/azuj+03TsWzjrMZpD3Kw+TBtF8ZfVKaVfOyQ9yJy5NixbaffX95deF7acN2Kh3uzvvbG/ZoYmKrerzdup1/Zlyc7lN6XVb21z97OeLAOg3U/1pPttjkGJR6ndLv9Uk5Tc1LU7yVoz+kSad/fvJ+OyDmbI+8uqcshVPrB3yrn0lMkpRwKO5rasrVXDj43KIfoTo6XQz1tObBd2vdSUjOSNe3T0sasbOP1y+qMfM5LTIvPzpZz3FIu1muZrFdTJiVSJi0lvqk+vkwwxDa2i/9SA+NLl0mMw+e8/dimQapntFtszsuNcg7ZiWXS5HuV9L+wVvblY6Q=
*/