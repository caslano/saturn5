// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif             

#include <boost/config.hpp> // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/config/gcc.hpp>

#if !defined(BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION)
# if BOOST_WORKAROUND(__MWERKS__, <= 0x3003) || \
     BOOST_WORKAROUND(__BORLANDC__, < 0x600) \
     /**/
#  define BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* overload_resolution.hpp
krexvzPMOMPYf9mk6N/aPFXcLrBaV/KN+oU/vr/mqMb4ar3nUY/xnWeV7VddrsVKVxZh+nfiuV26IocOKF3594m2X5YZRzsjKQZd2RCDrmxw56tZV/DnfS+Y029K5XvB8Ot9L5jyyzWtr1Py86dOyZ1t3A+Gf2/7wdzP4NbZ2pOj6+wDcu8Mq20lOrsoRp1FF9ApdOEodDakj0WV7glL+ZE9YY2de8K0jI37wvT8aImacPs2jvTDd+C56HzqZIPOywSpS+/VXuAS9lzmyj0H48J7ubOV/A3lgvDN5UK+80hY88R9nw7rYuz4NpYbFZb525OEtVLcd+qwisR+orFcEZa7XEk4KwmnVNzu1+Fcq57JVO4Ix7xnXOnf3eJ+TZyhHHKvsRzKc5TyHNvF/Vr9HPWzsfMUzdXe+2JxPz0ux9fbWu+baZ3j/1h/H7yF+E3Ajl/+eiPHto8zlXGew1jG9Z7qVy8KpZ9vlOtvyJbJtU2sdavpjsNUNxBH1LpB0ruB9N4rfm6Ja6zivVXs6T6+Bu/r6atlqkMI17yvfBXh7RC3q7X8ton9DGMd45RBcgv5yndhkeOcg3MlbXk6rb8V+y8krnXEtVvuvzTOtC+9CbxJ3G+NO9VfJHFMti9acraCPM/uCt/En7Zw1rI8CbuY63vk3iVxdbT7LKux2iu/UfLhO188dd5C6zLZ21/EPeV+L5bwl0d+n1+fCzBfwt9N+Mpdzeuvl++lS7nlR5dNtLNcJk+Kjl0mz7kGvwclnNw44352FX+JhDWLpld9g5TrV1kTJV9voR4uJVE3NJW6WcxtiuG97g81CblvVf6e40E+IxFrcWf/u3Zbh93++1bYHDMbcxvmdsx65dc2JzWDjm/el3jcK29/8x59V9+8j71tUO8s/mttA/eKzqGH2EN6iB/RHbWfWezLtf1isa/X39kvMO7B55rkaYmkj3xW70naiZ6KfMR+q8v+NnbTN/cTG6g15DieBgNwmN1uTdXt1tSlhXkLpWPvaLe+kXarwFZ00c8y8m2l3HOjPsNisthH+rpYLYznlxCHrhMaxkt4towlvA8J70ZxX+kL1y8lYj9Bn4exJde2NyVM7PwVEHsH9CrO2L454/suWeKby3fxdJ2bK+73+b7girFNm2psa3VfaKG41/S9byWb27Kp0dvXP5LeO8V9iU7vzWLvaOpjElb080TeJqxZ4r5Nn/kxQezJ5vZpqrmOP0g4S8TtTh3OHLHXM7dBKhxTHZ0M88T9Xt+XVn3Hu1GywFGP7xU/qb7rVL9i3w+hOvI50dPcWQUzGZyquu2THwx1rsqLZaIL14m/vXYYOr6ZKHJ5GHuivFvdz/WzqDdPwH4HddidmPVJ2si1uzA38/cGeLfTXfV1+8X4/fJvpG6TMqXrNsoF16Rc6LrN1t1GWndRRUMdmFyhDvS27w4/Iu8CsdvBS30nckb+XNPyF797K77TFb979P1Kzsrvfte7Xed4sVSdT3dArZt/A/NaCten6TpoWt70bF3Z6v2eqk4M5/l74n+l+az2aRH7ShfN0W0tcYr79aZ6Q99bR9+7RLft+8XtZmN9oePU5UraAf19/TXifiZ7DWpKeUvS91zgrDd0OOV9hYIFzNMUOs+n2yd+6uu68S2xt9LhfiL2Sy1HH0f3P/8lbhPZ03GmLoe3y7WOVi3CdPR1dHz+vFBfuaF2mzNrbrZ6b6/COCxhFFrNKUcJ2DdSRu7BPN4oxGLDmBCLcUxIfldoA2vpdlnlY4U9qUvw42zzkbtqJ1vJc/Oel8yTs7qUDhbxTHIOOcaP2Wxfs+cs8hw6ODub44bmRdW/+8TvBpP+EY677ShcWmCev8CvW1eVXJU=
*/