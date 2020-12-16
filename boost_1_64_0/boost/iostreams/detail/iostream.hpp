// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IOSTREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IOSTREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <istream>
# include <ostream>
#else
# include <iostream.h>
#endif

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_IOSTREAMS_BASIC_ISTREAM(ch, tr) std::basic_istream< ch, tr >
# define BOOST_IOSTREAMS_BASIC_OSTREAM(ch, tr) std::basic_ostream< ch, tr >
# define BOOST_IOSTREAMS_BASIC_IOSTREAM(ch, tr) std::basic_iostream< ch, tr >
#else
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::streambuf
# define BOOST_IOSTREAMS_BASIC_ISTREAM(ch, tr) std::istream
# define BOOST_IOSTREAMS_BASIC_OSTREAM(ch, tr) std::ostream
# define BOOST_IOSTREAMS_BASIC_IOSTREAM(ch, tr) std::iostream
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IOSTREAM_HPP_INCLUDED

/* iostream.hpp
tOEmcRZH6Tf5dsgM2vDGDlqXEQtjTCMutCLXeJl2uVnCtvCsR+I1dbAmOWj3w72P423iX8uz/ggb2R9YmlUa9gHxr+7x3OoZttAd9jHxr+r1HEvY8vUls27KVR/kVWxWmOdW078kD/rcqm6aNretlyy1S+hz5n9CG/ajLks860k7HYepI20fIfsj70m449LnXvfuc8Tt2eeMvZ/vxH+oV10R1tO+i+mvgzs6/ut4DqnMfDKfR51FXF/qbOZsFiJ61RG6J+/bK+V6HWkdPtNPHxW3+rxXnMK1o/fTAs7PSoH8fb701dj76186RvRXbR/R+2ssdk6kHKRfX9HR9Ouw9vKmJmYtYiO/QCby8Jae7movspqYpc55s/JyZhTletgGMmsou0q4DCvdu60Qr2dbMe/gNoh/S6uZ99hMeA+7Ulp3fcSvkqzdn0A/yIoP2UzrZ3nYyBGdoni1bZZQYHQORayX1PXtZgz+Qwx16rFe0rMO3e+rs6ueWBcDnHd8J9RFwbyT1cGXZdTBYVcdrJfwEqGpg2mdTl4Hh09SB9+66qAE5X1VcEv2roOQzjF0vk+OvQ42oTss+cfVwXpxk3yH3bOsqmbJ0U/roC9SizrY2imiDgpyWV+fl7ugKLb1zoT3avde5Wt09V6IoyDPXb/bxb+bdYrcPUyRa01Ppf0gM5BzUq0y98h1xpx3OsVm6yCivZqxI766Jcc8Lau5yODWzkeKaGU13VlL7WlXrC6Mk3CzpN2O8m67GrcdcV/sXY5u3Xclxbr+Sttqf/FvStg6nm25uvhXkjXbq2kXWxIoi1TaaaBHQpXKCYFk/td31rTX0jarbtpmy66LqGXvvt+OaKdN1DbhBsSn6wwmO3uKucremHObUXR+QW5s7XR159jbKbpev93e33c6e/5GmzHnJvFfY51FbtRmlIa5lPLvY+JS96h21urCteJ/vTUt7JvQzNxZ8kWIctD47xK95cZu7MxUY2tB6i2X81nIbGROatnjjdOnPuhc/j4V6+94ivubhclP+G/IIflf5njLO9t42MKxc9HFo13kFkT9DZkl+mNZX+rzaifE564DvU922dHZLP5+z3ajYd02FiQx0+meKaF95UXnCetK/v9VlN+ahaJTyXyLfEjOuxl7RO0z9JnMhJXyMnYsHxD9rVYhOboGqeH6Nihp0bZ5q+jttlaSn42Io9dN9Hi+ceX5WdGrbMrwEzlfQutNi0yTjCktagZfBuQ5Y4o9DuM+CXbTaLarVb8F+uc6+pVzTrDvkKI6o9GZG9xTfnNCfHzEb6qJS+5j5zl61ZfuidTRZ1IzhkGRPXWR2sF73K/rOPLjbbLqfS7tJ/yZ85i+MOmK2EgGMsH5Lc4obctyX8oy9IXztUXLT0z0e6MHJGxHq5337wtxe9ol8WrHRtc93g+K4be37LIoPGG8b5GsEWhZDEAmNHcKx10WzArgV9ZZ8W7FaIeF8BHfaZ1P5975VV2N1zw7mbKNF/8eVvvQfYnaUV2IFCOnppRdNmL3sWtsY6iMg5pet93G9BRLjicQW3kuH6myw8qqiHu/6Htt5Iruo3wTY6cHZBKSjzyMeI6HJ5RjznxPW0ARukmiOw8DPN6/m27d/ICkE12PZ9vIeD2ebX8n/jWZIx9nns1LxK1v5BhpbP3NF/+H+LZX2eqM6znwYqubeTau3w1/St/jPl3+HhiDvfWy65iyNO9DoLhRZq73IWonC7fwe9Rj2hZ6aVvoicxx2kK3cJvr7tHjZM9WuRKuK3kKeLcD/CPGBKTsdu9VBu58ZKaeaL9qojMWuvNR6Lxzk6kvC4vmeNrwNe/eHpFwtb3yQJyxjwlu3eFyHbm0Z1tWXfM=
*/