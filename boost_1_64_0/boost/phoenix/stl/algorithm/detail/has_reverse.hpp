// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_reverse.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_reverse
        : is_std_list<T>
    {
    };
}

#endif

/* has_reverse.hpp
uA4/xwL8Arfjl3gUv8bj+A3+jMV4Gb/Da/g9hsi92LXwFLbA09gR/4F98Cz2xx+QctMnUa5d4WKp32o4jqR+fv3dGIDNsCU2xyhsgYNUz7FvhekYiZkYhQsxWtmecl0Kp+psz5WS32oMxxexKb6EvfBl7Iev4hh8DZNxLabi66iMqSD5BJOMNn3feJ8ch9ZhDVyPSjvY4bgdZEl80zEQZ2AozsIIfACj8EEcgrk4Ah/GyZiH83EOLsK5mI/zcCnOx3W4AAvwUdyOC/EoLsLj+Dj+jIvxMj6F1zBf2sHTWAuXYAt8DjviUuyDy7A/Lpf6Yp+Taz7EKOUO4t87pdwDpG/ZYKyHQ7ATDsUeGIujcDjm4AjMxThchPfiKzgSN+BoPIJj8Asci5dxHJbgePQhjniMwAnYFZPxXpyEWZiCM3Ay5uIULN2ObuZrP8Dnp7k89OFj/zCXJ533hWAG1sNp2BgzsQVmYRvMxs6Ygz1xOibhDJyCMzETZ+EsfBDnYy6uxtlS7jzchnNwJz6Cx3AunsD5eAkX4F3E+CgG4iJsjIuxL+bjYHwaJ+OzmIFLcBr+CafjMlyCy/ENXIHbcSV+js/jr7gKS/AV5DOBumL9+BoOx3U4DdfjDNyAz+BfcCn+FZ/HAtyCm3AXbsZPcQt+gVvxAm7DX3E7+rBdCjEQ38SauAMj8W3si3/DcViEmbgbF+IeXILv4FLcq/SZlOtHOIJktO1Lxm8/5It/xwA8hS3xNEbhP3AQnsWh+APKcYtrQI7PQ4LkuBCKAVgbo7AODsG6OBzrYxKGoxEbYBY2VD6HSJLPCJ3jz3mJ/58YiD9hKP6MEXgJo/AyDsFfcAT+hpPxKs7Ha7gIf8d8vI5L8Q98GysTz16sgh9gVTyB7vg13oG/4Z14DT3RjXirYV30wjD0wWisjt3RFwehHw5FfzSfh8h1GXxP5zwkXsqdiAGYhM3RgFE4CWMwBUdjKo7DNEzBqfgQpku5M/A5NOIKzMLNmI1/wxzcg9NRtj/XYxyfhxyW+D7DADyKLfEYDsDjOAS/xAl4AtPwK8zAr1G2P9dLHG//1yWfdRiIGzAUN2IE/hWjsEDy24QjcAtOxq04H7dJPRRiPr6JS/EtXIc7sAB34nbchSewCL/G3fgb7sFruBdN2/9drIvvYRjux2h8H7vjBzgID+JQ/BDlPESum3AM1DkPqSHlDsYADMHmWBNbYSj2x9o4FOtgCtbFNKyPj2C4sj3lughO1tmeQyW/ERiO92BTjMMYvBd742gchfdhIo7BZByLylhZHzg8D2GMM+nDjTWwAJWx2WS5vjrtoJHE1xQD8W4MxeYYgSTz+RkOxJY4DFvjJIzChzEa52FbXITt8Glsj2uwA67DjrgJO+FR7ILHsStewG54EXvgFeyJ/sTdCwOxLzbB/hiNA7A7DsSeOEiWp8By/YFtJ+VmW3JcM7+2y/ewQgzCN7EevoXNcQdG4y7shG9jD9yN/XAPDsV3MQ7fw3G4Dx/B/fg4vo9L8CCuwA9xFR7Cd/EjPISH8Rh+gt/gp3gSP8NzeBQv4TEsweNYhXJ9id54AmvgV1gLv5HtT19krifYno/RDvlckedCyPnYXVgTfTEM/bEJBmBLDMI2GIzdsBb2xlAchPVwGobhg1gfH8EG+Cw2xD9jY9yNTfAgNsVP8W78DJvjMWyBpuNAFLpjW6yO7TAYO2Id7IT1sTP2wy4Yi13xPuyOCRiDBuyJ6dgLZ2BvzMU+aB7TT64N4GyS0W5Mv5+k3VzEQPwZQ/FXjMbfcARew9FYggn4OybjH5iGlcjPCG44A6vgLHRXxgiR39qRdqv5/eOk7O+n0BNPoz+ewSD8AUM=
*/