/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ACCESS_04182005_0737)
#define FUSION_ACCESS_04182005_0737

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct ref_result
    {
        typedef typename add_reference<T>::type type;
    };

    template <typename T>
    struct cref_result
    {
        typedef typename
            add_reference<
                typename add_const<T>::type
            >::type
        type;
    };

    template <typename T>
    struct call_param
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T&>
    {
        typedef T& type;
    };

    template <typename T>
    struct call_param<T const>
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T volatile>
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T const volatile>
    {
        typedef T const& type;
    };

}}}

#endif


/* access.hpp
j+A9CMsQSx0z3vMz7ySKHk2/yb796cl3RmC+mvYvIgWuYGQ2zOUJbgqSM6rcmXcTDS74D30afQuEGHO9Jb5+VJWpGKcO37Ns0COMWRdAERVj8/uJuaxqOKPewvtfFEI7GnLrw1LtYt+8u3Wz2k23ek3aXLe3cFuUFFSmbGf3FXP5b8B6fgvdcYmOBkVTL3+xeJ3Kfw1jLuyCVfbuzFuLBhPsTyfyd04VLVN0lL83tj3c3P138n970hZGswlScbjL+C/k/wWSfxEWUmRX5b/qK+IgP/hO3JraMEVmcyg3qMevLqeqZY7cTTBA2gGfeMQX6/sJ1zGZVuarNa9Dn3wcL2OjHfl9PoPfBYLVyZVWE361LAelAchwl1/tG/J6iN/Z8q8IwUL9vCzyrnd8aue1WmiR7bimzhvOWlkP9nchiC/4zyO+RBQTgns3ijru1V1NHTQ4kE79KE5QPZYkS7XyzJ4qax4bUlgp2HogeWOXTOaxiCvV+sxP5NsTeXlXQwJT28rb5xBBdpc/a/k4JcYmwXhgrcD9ZUkVVu3u1bF5a7G+vw73P7C+TGTOhinpBTt9fKEx6C3k3Gdbmb0yxkTXkRvtGMP9Tktb1NKwyMpiVEWe6vIVOEsWHpSbRkSvPRt9A/79+BLY3z47tUFjWiUuF7LymSLje/OWd1XySF22dmlhV57YZnbEOy19qqGIdRYmkjfcPNw92tpd7KE9Fwf9Q+3zRPvoM9OjPa2oaP2T3sSRAe7PUR22+rvJzFLGwNVhcfd4jPE92nv8rOVfC1zQznhJCiSEz8b3lC19Jqror5RaILj1q7iNfyo8OJ+ZMFK5Dr9Z9niL1RjP93Ofm+i/Nz4LLzHocRnJdFhOLG/evYEctQi80XwO37E62fEUUnn4HpKFiFLHJKZ7y5OIEyqnLDmC5pO41LnwoDsVwWRIURIDQGVsAerNcHeO+AwxTEstrcRgNUHIYRuufRveQFv+5woXYvJBk/VrZd4YMbF1aWkD0bGzmRrVHKnScCv1VvAjRO0TJEfBi8Y4sn58uF+2kvo9fLhxozoyD3AUfCIwnmMd7xxtbQH3h9spAzGxER4r454o89Fj3+HLC/6pTcdfMF5MWRnNLByjGvlWwZZz0v+eGcV9ZhPf4YLGdo8L8DTWwvnP4/fSnFi0o/lbLyK25X1y4UH7PVeBWxdbGZGxUiMjwXhBemesgZPSKGLjH50RXk3RV71TjJ/IePkCEnGU8QBjRiqp4Ky19wIhj+HOufAg2y2WAouhFfHZQo5v7uDrgNrKSI0qESmPhNMiqzfllntqp0rYoKstL2dE8cilyBMxS2iKcnNzdRGWq7RgcbYkY0z2Cb6uT0upjOhgGzKxYi0sEmzYscw66ZRMh2S+1MhMwC9igpmKEkmtHZIZ27VKiGf0BSxz5CE72emJ0JdOERq1YfULuA05OGttiFO5N0e5xcCbJ7wqeptN6Gb+/jBnR96dCa/wkefA2Ez2qy8CXPhGRLyBiOTL9hvkqXMXe/8TWN8m+NxYx7nrZnIfjy65A+8vEC8lIbIQA0XzuLfVm/H+AfFyYrhLyWc5k3s0QGeD3H9DvJ5wF50pm81sPs/EHuW+zxcxvuQiOOb0TO7RKJ0/dVi/Wt7nMNXFZKip/lZso/+4uAg+OAiHkSBYdtqj8Z3YIfOBVyNeSaS3zlQH+4M3bh6tru8c7t9cXggD7Mj7mglupEprS9G4IuvkRr6Tlve5SvjAzTJNxly+j0xwZNBR0NRh+WDuIpyvo360VDET/CKXwRznhxMclYVKSTEsD5qfHL5HW941UY/+2chyvVoC940ijXGrfjvBskYm403EMqE5yWENLLz4jcR5x4o=
*/