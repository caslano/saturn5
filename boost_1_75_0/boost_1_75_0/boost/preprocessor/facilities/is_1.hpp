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
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_1_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_1_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/facilities/is_empty.hpp>
#
# /* BOOST_PP_IS_1 */
#
# define BOOST_PP_IS_1(x) BOOST_PP_IS_EMPTY(BOOST_PP_CAT(BOOST_PP_IS_1_HELPER_, x))
# define BOOST_PP_IS_1_HELPER_1
#
# endif

/* is_1.hpp
a+A+CViAhuMbD62WnEWeG9fdqnqqTaTDeA7E6UaPLqXoVv3Ne4nzm+VvhJxVUBzgEYADBAvW4HoQggVNcDjcITgEd3d3OwihuBMcDoK7uxzBJbi7y+FyONy1nc60fei0j//szD87+7Az33y7C73e3NosOwc84PmE2RmjEh8iCLpxNkMueu0vheHr26RRF4QlagHg1ggzuLZqwKTPuwG+2PiCh+o6rffWiH0VdnbEHzzjntMXv7LogpAEDiHyb0AJNb9NXLv3f9lkW/KO7BbjPscpF65r5VDtt9YNKHtQt1Nvq1QuxlibrdIQ9CWsySf9Y6cj8qwnnLPTaDpfFvu2z/wUw4DoosFuciuB95ToeukeX3cc1xi9U01pv6Tflll8KDezAzk00YU7gKFYsDcxsZZ/7ueZomhiKV+pdJdawslJsvfuM57F+FWna67+0IT7yZKvExVwsmpMZLKLBvawd5B5XA7ye09GfSfSAeBERNYKUVjMiNdsDyXBrwhG8Og2FAHFSaICv79OMm7IBfBe+e2wjKBIuTL7htjEM3Yn+DBc/dVOgwCs0llplcNTFpkG9Qyigap0PoojjGPpcr92pvoErTkNm52smZW11F1IPMIShNnhxeXG20GO5HyxFx/j312/ANuVWgiwY/Q/WcXGrd6qtbN/BHVobJZCwHpp04BGsZIRhcIjdGmh+HpcenJAWbG5IfbF0HtsE44z
*/