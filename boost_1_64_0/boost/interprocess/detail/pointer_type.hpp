//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP
#define BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/type_traits.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct two {char _[2];};

namespace pointer_type_imp {

template <class U> static two  test(...);
template <class U> static char test(typename U::pointer* = 0);

}  //namespace pointer_type_imp {

template <class T>
struct has_pointer_type
{
    static const bool value = sizeof(pointer_type_imp::test<T>(0)) == 1;
};

namespace pointer_type_imp {

template <class T, class D, bool = has_pointer_type<D>::value>
struct pointer_type
{
    typedef typename D::pointer type;
};

template <class T, class D>
struct pointer_type<T, D, false>
{
    typedef T* type;
};

}  //namespace pointer_type_imp {

template <class T, class D>
struct pointer_type
{
    typedef typename pointer_type_imp::pointer_type<T,
        typename remove_reference<D>::type>::type type;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP


/* pointer_type.hpp
uegNm/OpPtayzblJeIbNeQVjqs35NF3n1/fTWR8cq53B+qDN+UxT74/9zjIx37+zGQvanJtZb7M5r7RiUmfOEdw6tj1XcMPmfJ6B6eO98wW32pwvENxqc75QcMPmfJFg2rj6YlPvp+2PDUzy6hLGgjbnVaxXbc6Xajrpd1ez3mZzvkwww+Z8uWBWm/MVdtzvV65kXLU5X6Xr/LK6Rtf78f8J64M256tFb9icr2EsaHNeK3rD5nytYIbN+TrBrDbn6w1c2p0bGAvanG9kvWpzvol1QZvzOlPvl8X1ghk255sZC9qcbxG9YXPewFjQ5nwr64M259tEb9icbxfMsDnfIZhhc75TMMPmfJcd88fIdzMetDnfI3qrzflewQ2b832MBW3O9wf1StwfMDCJ+4MGJnF/SDDD5vwwY0Gb8yOsD9qcH2V90Ob8U1WvtHuPefqGqGRLenHKwx8XXIKOOJ85HsBV7AnCEvA9rDbXWBee9LDyqb495SnWSbvH84WkT4XZV58OwavQ9MhzhsIx7Kc/F0zsp/zuzYJZbaHPEJ622VGfJWx5mE35OcZt397P27Bywl5wsURuzJauLzKmputLrJN0JX+2uPoU6C1p8rJgRpq8wpiZJoS/6uLLPdyM91bGbfH+hWCGzeE1G0ZboZwvQfqDnASSnbHtlQkNJ19zYfL6kzq/3WvIa+Od9l/7r/33f/zrCFLrZOS4/y44amEiGY3T1iL6Z6pu5OLGWF1k5OjDRx8+qnbk8lTuqNHjfaxpwriRKbgqPBoZ2RCti1anoh6jpmFFMp1YGKmrq6+OxQ9PLIY9l0c5k3KcQY6zj9PL6eY8Ve34z1mxmoZEKlGbHjS0bNigkiTsx4ydBrO0g6Ym6pOxOtj42tkpzjk82z2zOhvDOjSTwn88x6MCZBvgzfGeTobTXFBXNwve67bdk3MmZTugWxqLp9IF7jxdDycvpxfwb0XuGPC7IKcjtvOFOX0oTdifDHQ/2HHd10ZOLYMYJuLI76Lwuyj8vsDv0NHl1yWXl0VT0Ybl7h5QdJOluMkKuHkj241FHE6ZilZH0BRP4ewHz4eRNxj+XpDjRvsI4I7KdtvuntnBvORffg72UTkYLzf+fST+qO+CfTzolXgNAL0bLjf8fQLhz4QYfMnpfh/g2RlvnP7my3u/uuzLFZcc2O+RVSd0dpwnsY/YlV8ysHHo6lU/6z9pddcd333iON8if8AzZ6zac9C8py9sOu6hC556YCuUt06uvubA3DWfv3hL0an3/PqhfVbUgL4B9X2zIkWvz9lZP/zgay4+Y8XdXznOCejPaT2vefbZUwZUbrv55Md2DDthnOM8hfxHji3+cs9R4978yce/f6kmo+Y1KF2dXf3jl51y1YhVG2t/3++f93419EdjHee8Dq7+5rkvdtz3gm/vH/zorwcPvem4yY5TjPydqwZdP/L5+J6VX9z6xDm3HngflM4MV5/cVn/BV7sOffnNK6cOHPHBhJ87zqZMV3/soOjXZy5ccliH5Uu6n/Fx9E3HmYD631zxwcv50di6lX87bfHDg++CMF6N/t+17raCczt2+C6/Zvzd8T+Mh9K/A/U//HVN97qTZp77XtcLkkOGld4CewD3cfW3XVNb9mjHz3739IZD9l635qINjnMW6ve8+2yXa89aefn0t7+ujp1w8A7H2Yr6F7J6baoaO/a5yZ0Om3jKAYX7O85e1E+bXTPgg3lfjuiaHLjj7CN3Q/iLu7j6zA2xwUPO+nrigN0Dcvo8tvgdx1mH+lGjbqv40xvf9i/bfvrAspsGbnGczzFepxw4bNCj/dY89I8Vj1/0+sVfwODlekyfksfvnP3+3vuKPr/76rU=
*/