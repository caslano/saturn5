// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP


#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>

#include <boost/throw_exception.hpp>


// BSG 2012-02-06: we use this currently only for distance.
// For other scalar results area,length,perimeter it is commented on purpose.
// Reason is that for distance there is no other choice. distance of two
// empty geometries (or one empty) should NOT return any value.
// But for area it is no problem to be 0.
// Suppose: area(intersection(a,b)). We (probably) don't want a throw there...

// So decided that at least for Boost 1.49 this is commented for
// scalar results, except distance.

#if defined(BOOST_GEOMETRY_EMPTY_INPUT_NO_THROW)
#include <boost/core/ignore_unused.hpp>
#endif

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Geometry>
inline void throw_on_empty_input(Geometry const& geometry)
{
#if ! defined(BOOST_GEOMETRY_EMPTY_INPUT_NO_THROW)
    if (geometry::is_empty(geometry))
    {
        BOOST_THROW_EXCEPTION(empty_input_exception());
    }
#else
    boost::ignore_unused(geometry);
#endif
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP


/* throw_on_empty_input.hpp
F68Xh0ue1buk/Tx2xBQ73+XGm0xt+rLQXHLowG06ZYruGTxduwcuQ1ry7TdSJ7uO+cqwHkqjStLWRqmOdA76L1Ob1yjcl1UbRvA8fJrkRbbyKryb53TVla/1MfvnvODDgh/Fyb6+QPE93sD9e0RwzPZlRY+DKztddR9+bxGB3d4RNJJ1P8O0a29e9l5nL92pniV49j5SPvZWP8mP3+GeM8XLKLzBj/atc1XXjkeIb9viWElb/8Uewsemd5e0vYP/b9xHXzDFyuH1jb0zdEFyNAg+cEU3A+M2Ahd04ccxcQkMbjPRHQj3+ClqzwvvZF/eYup7aMucfW+pac91DmffON7psK8+QXjlhWTXwR46kcZ9LnonEV4uesto7Tyd1pR27cNqJ/h+3zvA/LE8oYzABiyzkuSooHXiZFoHWM7O2Dw3ODm7Y2UGJ2cvycFy9ul8YWmGP5aH54uMlnU62Lmyq6j/tND+YSvaew31i1x4p2k91Y5X+93Hvt6+jXdoK5wR0/fgyqyP5MDbnksPjev7szpmzRuh7Ccj3bh9uOW1CXuIM0k3ufA2UF9l/8/ZpDuGn6syOzjvj0KZzxccq++vjbXpIcHXzfeUFZLXj35iaXxZ+QBucPqhm68qjrNxQzi/t3OxwdmcA+cSnWc13pfwxDumNM9+XXFVdvmxHkLcbybggr//WbqXk87uKcRcbfmgXAY/61P7lqnnyejTPP9/h9ouCed7KrOlk7z+/oDWp4FwrxZcbvPX9o/z/lFkuwHHxn+7Nl4/tDfF0Sac5wu2x/lJ1L+B008+/BuIxuYEPjcJzomxc8VrxB52Z2mDbZTX16nn48NvPplUJsim0+3pjmy5PUKcjH9QPMhz5+Dzfjpl585o5+XHz2jf4srjjHZ0d/tnU6wfv/eUNonGJkdwV0RfoWI5uWK+DKKcs6V+Dlvq2IH3GQ3HzWySok21s+tm1M7x1HLAQPcXoBu9pXKrr5Owhr5DG0GumrosfPsL7Yv0SuT6vNt8uXTr8lQ6yNUGvxxkG1TnaINfmTZw6YsL/J15H63OyRbdJbvdtEthEK92pGPK9XpG3B/Ur91dUUEf0/d/zP2Tjoy7FzUDPO9I4invzvkAb8qUsgc6q7+TNHyMCLTltAHundzldSjPyyEdhDrsz6wM264E9bk7qT4QQVPm+1Rtse5T1Lb0sdp1PQ3nsvX58TVoOr7V3TclR7ySXLzRf38f1XnH42KqJxDPUt1tDunonHa/pLfQPugBM6/eBliAsw1bjV1j310v0nvIXGa34OGQnquD7psfpX3zYygjsng+f0D6NqR/XKDzrPyhfBXHv0eL/ds/C+GvcPtE0L+V9vZ/Qtrl8/nnuwj3WaRdPnC1Tbns/VT2RaQl356V9mn7XfDPksZZVMX3sSOmhPi3Ev5fCf9W4L8K/LsI/++Efxfw/wF8VxeL/xrhC9zjvy75tu/w2cp/GvitCfC3DPyuBPjbBu54Mvwd6HNyYajfGcXoF8DXfmHshPemxHGGJeAEpRYneT+8S2lWNuGv8D1ggw0rtXECZQ0rNmeaYBfYuuxWqnsgGkf6Qx6/9zgiGFEattvupdn4BbfR2N6zFPY42s/x3KsUdiLguu/S8Wzx84K9wWcL+TjyJV/4cTm13wqMrrYAD/3ayzG61L7D7H6hLJvwvZB1YMs7icZSeyXZpoWQAbrweFb/+5XGx+pWM+fwt1+XN49iEo8vjcOZfpHANWYQzQsTwHsL8wLuTwrivA4hfbK/+1DTrvX5fv3RPjUNurG+msMM/lzCFxzFPyo/xD+iFG87gD5wdSyd7HiYcq7PuhV4cqm2G2LboM/7fr1zfb60FPsHzD0HY68=
*/