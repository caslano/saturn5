# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
#
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/facilities/is_empty.hpp>
#
# /* BOOST_PP_IS_EMPTY_OR_1 */
#
# define BOOST_PP_IS_EMPTY_OR_1(x) \
    BOOST_PP_IIF( \
        BOOST_PP_IS_EMPTY(x BOOST_PP_EMPTY()), \
        BOOST_PP_IDENTITY(1), \
        BOOST_PP_IS_1 \
    )(x) \
    /**/
#
# endif

/* is_empty_or_1.hpp
C6GptXIJ1VsCovc7RQDtOXm3a1nyVhr1rMCGi1AezWM1SFdyEnk4XftIT/1j5CuIBlFcfPWt4iAC5G2sj+sK5BCyBBaOYp8A4b+VzuEvwI6sVrG4FjVhsgeN8LvsGbi8SmbgjccBr7fhczT8CoI/ZsNrNHwS4CaVI1mZ6SiBg0UgY4f1UMHH7eRPnnyYj/vPPWWx9QGXfEzjkoc7qUV4O9B6FMNqjV+2UMbZZRqXTs2cxvtkGt/+rjWNf4xkguorgsQS4YNX49qp9vo3QWqxhvPjYjnMCnibCf3DFD0PY7DPVJPxoxCN720mUowxz05ojCREFBa69wjrwQw+hqnWpY73jlUOExGH4LfDxrNF1eVNdtC1PdQjSLE5va7e2Gzn8mKlRce8kzPMs173H2esscPdV8mlMT2T3z+GznvU9m+qtEqLEvi4M3hN07pB14SwUOTATTSuhRS5w+75OomcrAccso8T/Q4ysy+CfOMFfscqmDtgzqnwO86HmQwThFkEsxxmNUwTzGaY78M8CPM4zK9h9sGEKv2OV/B9E+YwzDGYXMBOhymBqYS5BGYRTBSmGeZumAdhfgWzF+ZvMCdhek/wOwphRsFUwdwJM7jK71gJ0wxzN8xOmDdhOmCc1X5HX5izYepgTPqU3Jc+CbqFlkH7nlPLoDH6LaSuyyrgLUvoGsAaaMXCfZsNvQbQYANu8c62YLcHWEwB0cOY730AD9JSAQJrNuwBo6SeLpxfu4DpvqUW9aA24yfMOOHdfMChY1I/o4wjTaqQXtLX6TXaFDA98Csc3Ifg+cY0Dt4PwbHScqQ8CqdeQpiAVrsXRAmMZRzwPVjhXwru+8milkNKiHglosb/bGMNh9whIQtC6k475CMcsgAhC5wxP3Fg0VrWH7pKOLtNHPOd8XIJv4VdqySdkpC6xE5nkaTTMFm9xoHd0OKxqQ04FcjeV2L2dyF4B5nIDR52NP6kC6yLB8gGv3lJLeglWgQKs7J3ADcOi0OqJyfvoz52xqrU8bFE9fwhfhkrZCbRTkRN1UdozzkrrH4Cv4gTknD4YgPsO0E0MHRQwSlvrbu2mExIVVGOh/ilJXRYwaU2/9/5IoOu7kCtwmrcWJmn7V2FLttKWf7lssz7wRLh5y6nQUZE8nFvwFWtpWGmOeUyHqBasfpgrYdVq7n0aC7jfNb7VMMMhBCcCKI1loTVCS6Vj3Gha8LqCJxatHDdeQgHHMYTVnfI8swqDGdfYtXoKakRVDp0IFXNxxtZGlYPSqKQ9oXqPuqGX+pcJyLZyjgCglGmeCaLhFUT1QvWGlMlUQBlJT1TFeC3xuGV1YC1UIe0RtLmY1rlfutCN9oIENiN1LZy8wJ9sYjofB8A/ewKjV4nWAGXu42iatKI1sGc3J5jh87ccRa1GMKkl3vgH1TDK6wjNG9lSL1OXVpuvmh6n6R1BnNIH9hP/P5HL7Bi6ClZhleDanSbETIgPOvAkdYLlPeZnzrogI46ctMspWbBMKPm0K8f2M9oLyN9G2aCUZ9m50T7IXAgNSjiCqvURaZ3HXuzZzU+fDMAKgXtqjQhB+qifCwRAAJNhR5vPsvYT82cZ7TRJ9vYYvf0gXEcNqhOjjfVULjjm1hCVrS7gHOcLgxp8Ha7j5pD62sIvvZ922yvL9uBxO8N4IeWyIUtANKdm5uu/w14++BDgALYi7S9BPYyba+AvUbb6+mR6gW4YAc2NRtFeZVxqzntxCa0HZUM8MgMqaVj6c5X8LtbgOKIQoEQrwCoDJ06gNRq7jikE5d0utZHy06F46dIE9bGHIjDz4mPIlF44devHha70PtknTMx34mbXcEZpwBA8rEWoNz7ZFZAJYHSbTw=
*/