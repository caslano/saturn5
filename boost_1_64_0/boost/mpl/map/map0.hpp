
#ifndef BOOST_MPL_MAP_MAP0_HPP_INCLUDED
#define BOOST_MPL_MAP_MAP0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/map/aux_/contains_impl.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
//#include <boost/mpl/map/aux_/O1_size.hpp>
#include <boost/mpl/map/aux_/insert_impl.hpp>
#include <boost/mpl/map/aux_/insert_range_impl.hpp>
#include <boost/mpl/map/aux_/erase_impl.hpp>
#include <boost/mpl/map/aux_/erase_key_impl.hpp>
#include <boost/mpl/map/aux_/has_key_impl.hpp>
#include <boost/mpl/map/aux_/key_type_impl.hpp>
#include <boost/mpl/map/aux_/value_type_impl.hpp>
#include <boost/mpl/map/aux_/clear_impl.hpp>
#include <boost/mpl/map/aux_/size_impl.hpp>
#include <boost/mpl/map/aux_/empty_impl.hpp>
#include <boost/mpl/map/aux_/begin_end_impl.hpp>
#include <boost/mpl/map/aux_/iterator.hpp>
#include <boost/mpl/map/aux_/item.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

#endif // BOOST_MPL_MAP_MAP0_HPP_INCLUDED

/* map0.hpp
R3gzTEPXW2A6XAaz4G1wMrwd+uEdcB/YDufAO2EFvAvWwLvhifAeeCq8D54N74dLYQe8Dj4AH4cPwqfhw/Bt+Ah8Hz5qfd9SnqsgVdpW/b7ldtIP28O14Q5yXjcpU85bLueNgm/IebOkP/aFw+H+cFNYAfNgJdwBHgR3gQdDP5wPy2At3AsugHPgIbACLoT1cBE8DAbgcXAxPAU2wfPh4XApXCL9dQS8Ax4Jn4dHwbfh0bAbHgM/hsfBL2BzqJ7UV55tcITUMxnmSj3zpH22kfYZL/WdYLWvPKNghkP7PiHnPwlHw6es75rKcwLMlfPU75oWSPsWwjS4B8yFJXAPOB3OhKVwFiyDs+Ge0FiP+tSf4soP3n2W3QeueXckhu/7N+T1TnLn804ro/ypKbKXcaSPeyIsJ4lfW+PTVv3Zzn7spTDaex9zSXaf9Q7oJX5rfNYhX3U5vz0Fo/mqzyIpcTW2PZCdY2j0fmnLJy3+aNUH7c3/rPM3v39Rkq8XroCTjf8P8zPr91J+h3T0nL69lBtpm7NIbaSHSW+QlpOSp7E/87SEf3kgjqGw/5lZbzdxQL77H7L/31nduA82UeyE8XgArN9XmL8jjt+DfoFjFL9AicZWrwzZH8Wl5RPGe7HV5wf0foEOjayAJWu7iV5ktQaixLlr4uqbQ7JmBSvmcR+Bk6LIW6qR12LJo3Ie5T0cRd7qmvf8W0Py9o2nfu9EkbdEI69d5MVTv9RD9fK+0MjrFHlmB7qxT633IqLUb3ayZv+JPnlU0Ju8XKf6iS1bJ/Z3lfitKsRvld8ZlCcDGc+VyEtzYccOte/qN/GP1NccHPy718EXson4PVQ/VZP8Nt7mp/piFWc/VfNjYW1SVzNvccw+8OoPqRbfwiYie4zILlNlu9znxKvsyauFTj5O/BpHkQwfWWuYbLxkHnwaA+EnE19IlD4W34jG79gh9cqVNt1SfFupar1c7qnitU3ryGwcRSJ7Cgn/FgaCKtvwcMV+3gy2f8vSeVhI6DC5J6wi94TKRyydt5uo3BNSPbbX33FPWGG7XnrUe4J9/A+zv58o4/9hpf6DNf7X0Ix/VfZgjX+Ztl8k4/88c/yHyWb897Pf4xn//enPjhTN+FfrNVjjX26SJSJ7d5/4tx9VZP9Dxn8vDCT8yUPmT/4s6NfdZuzYu276fcHctF0Kt1mldovz/z4/c/pS4/dHtg38WL1/w9SO0Rk/jX0+L2Xo/MzYepbfeIXNb/yp+NM+h2b+gDY/Okj+HiV/c5T8X0r+r5T8LVHyfyf5e5X8rVHy/yj5f1byt0fJz38E8ydBM39nlPy/Svl/KOV3Rcm/ipS/Ogz5fWXOL7bACpvf9zrxS7bBEfB6mAFvhJvAm+Gu8BY4FS6DpfA2uADeDg+Fd8ATYDu8Et4J2+Dd8BZ4D3wA3gvfgPfB92AH/AY+AHvgQ3AT8X/vAh+BU2An3A0+DveFT8AK+KTlt5V5PEwlrbD5bY+VdjwOrm3zF5fJeZvIeaq/eImcdwQcCY+EY+BRcn6A1CrnHyfnp8BqkrrOcQpMg6fBDHgmHAfPkfY9FxbB8+AseAHcH14Iq+El8Ci4VH3nVeTmilz1ndeA6H0oHAUXi94NcFPYCLeETVJevo9DrqsiKW8VOFHKe1bKe07a73m4BXwBToEvSjntPplPwmFyvQ0PXl+hY3dpjz3gCDgdZsAZMNgX0h57wWlwJqyC5XABnCXtsDe8AO4DL4H7yvW1H3wVzoVvwgPkOquU62weNJQ7EK4Cq9Tr52F5d9nh+slV1rdGwHHq9fOw/vrZTM7bHI6EOXAM3EK9fuT8ixyun/HSXhNhGtwOZsAd4Tg4GRbAneE=
*/