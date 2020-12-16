/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_27122005_1120)
#define BOOST_FUSION_END_IMPL_27122005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, Sequence::static_size> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
XcoF4W4yVqTCPcpuosKJEcpS36BcFG4E8/2n5Keckfqssif1eeVA+veV08KF6vnCncop4S7lrPRfVk4y35E6P+arnK6VfJWLwmlhHJJfi3KK+SqXpL9W5VDqg2q9cIdymetNRmaSr7LDfE8ip2S/ksoZya9JuSDtM8qu9O8qZ6V9a5WlfXu1vdR3VOuZn3JGuKwc1kt+X9L5cD2VfeGUckq4WTkpnFN2uH7KgXCgnNlF8lNOSz6hcpHrVx2/VvL7MtkTTioHXL9qvZzfUmUZ31UuSX2rclk4qNZz/ZRD4S5ln/lV67m/LcI7HrP08/tYP5vcRB5NbiaPIWfJa8geOSD75HPIBfLZ5E6yT+4me+TEycLna37kleQ0eTq5hTyWnCeP03zIM8gd5EvIXeQ2cg/5Gh3/K8LX6vqQc+QMeTzZJV+n45OvJ7eTryYXyRPIJfJEcmPv36/J/rJ+sq7XKcLLtL9jD6rwcs2f9Wdp/uQLdP3I52r+5Es1f/LFun7k9eSQfJ7mT16h60leSHZGCc/XfIZJvhfpfFnfSs6Q55Bz5EXkVvKF5IB8GblInqbrz59XLyCXWb9a1/NU4VWaD/lycpq8TvMhX0H2yFeRC+S1er2T55LNacLzdDzyFHIzeTHZJS/R+ZPz1fz5ebU6X9bfoNd7RtZ7Kbl42r/n64x3j3f2eGOHw6TkHaQzRl+/hBuVM8JNylnhZuWkfMWbU3al3lNOSb2v7El9oOwLdygHwqFyQbikXOQ73rHkULhBuSScUi4zX7J+hZ5Vzgq7yhlhTzkt3KbsCBeEdzrO1PctrB9NLpHHaMNxwmOJDnkcuZGcIzeTx5P17ycnkHOsn0huJS8gt5MXan7kSZofeTI5kePzn5wiT9F8yB45S3bJefJUcht5Pll/f34uscD6aeRu8nTNZzyfd7o+5Bk6Pnmmjk+epeOTZ+t45Dw5JM/R8cmLyM4E4R0PLUuyvnHCf/dz8cFTkz8d+/Abb3z0mq0fufQQblWbPDf++v3/wOSbnPzuZ8G+e/yPHekiXqKg/MGHVrwkccVTmyS27klc8VDiiifvkti6K3HFixJX3PmBxNazEle8wBiO31+R2HpG4ooHEle8LHHFj/4h28CvZVyAx+7hWPAzGbvwHzAO4Qf+iPOCn83YrYmY1yD/4kPwf2tEzAVQG+ICfL+6iAkQp+E3Qe2IQ/gZ+OzvTsT+eyLmmPdFTBGx9/6IOfjAiOmw5f0j5kuHRUzBtk9FzDmDIiZEXITPPiJiyojdT0bMaUMjpsuO9fmI2eMLERNfdYhJwZdCfREH8JehPoid5oh5ARps2xwTMY9AhyI2x0bMx6B+iDPwTw2LmP6Ii/D6EyJmqO0H/vDwiBmC2D0xYv4EjUKcHBExD0DDbD8jMXdoNOIC/MSTImYkYg8++ZSImYS4PCpiXj01YmYgTp+GdYPm23xOj5gPZpE34iz8/WdEzDKbD3zGmRGzwfY/OmIOhNbZ9vCrc1hDm+f4iHkJWm/bTMBaQUWbAzwyMWJW2zzhw1ysoZ3L1Ii5b1rEdNvy6WgLddnc4L+fgbW1uc2MmJKVXbdZEXMllFuNvYBHZkdMZjXK4Z+Csogz8MVQC2IfvgnK2/bwE/IRk0DswldCBnEAr5kTMU2Ik/DhkIM4C18JJW0b+INQCnEJvufciGmw7eHDoUbbHr4Sarbt4Q9Brm0P33NexKRte3jjfMzF5gD/zAKsA2IPvhXqQmwWRsztUDfiMvxni3AtrcEc8Yq9BSqj3FmMsaA+KC/CVyxBv4hD+LClyBlxAf6+cyOm1fYPL7Vij2x8PtbhAtwjdn3gNyyLmB67j8sjZi7k2XL4xBXYD5s=
*/