# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP
# include <boost/preprocessor/variadic/has_opt.hpp>
# if BOOST_PP_VARIADIC_HAS_OPT()
# include <boost/preprocessor/facilities/is_empty_variadic.hpp>
# define BOOST_PP_CHECK_EMPTY(...) BOOST_PP_IS_EMPTY_OPT(__VA_ARGS__)
# endif /* BOOST_PP_VARIADIC_HAS_OPT() */
# endif /* BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP */

/* check_empty.hpp
SgA5rOYlwKUC8BLgHQIMaLTNFtsIcJoA8ljNSwA3AOaSH/sm6JfP3ssZDnnQ6SA91yy7gO0NWhIyj+bkmi6gFnAsLsp4oAPqJgB4vUT9epQZIw+ncyV9P+q92Y50PihiJDA5AC9mOFfqqWbMgoA60wY7+LhTuFn2LFE5VeLN1Svc9LVr2tNpaLarCwWTn4rBaZ+R7cormML/xJyYJfPyf2L2C6bsPzFvAnMy1FiCugMKdgu56PDgTCsBCOoPXKtn7gazwNoaMJJzcRJ+OHHZcsCUwPKCah5gABwUQGlQxQTQLgAs8u8UgKOAAVip3sTJ+AHLElgRNAGAGV4Eg+pCZBsKGUs4cJYEPP0p4JXABA50vpsqu8rYzqEfp0IYKRlA3m+nMpWfA58RfAl7PyDvl+zdJiTegRRYiwCUBQhP4fBSolPsfZq8vkLyzmOqPBYRo8PwKKK9pDNFeHt0pghvvf9N29UHNlVd8SRN24CFBChYtEDFghWKFKjY0qINlFIVIRCaoCCgID4ic6gJH4pQVjpbQpQ559zGNplO8WObbs4V5xQoAipuqOjYdJubzt0YmHWiFAWy3znnvvfS6jb9Y4Wbd++539/nnnvOucYqVFvwSwwhfhVDvRC3j+0nkFYyhzRz4biPBbw8jhYBW+nHWqPehWDKFZL8Gbh37NuNNlXAZfAx/Vt2V3USicsl/O3yuPS/rNyGGyWjrKh/aiR07iTKaa5oklbqipB6jqO4mQdxNqKkXuTqxfKAMuZKcrTVmv8AzYprqsCjGyVqmqkCHVx6t/miH7PyzV6viQGXiqVITRJLiaoUS5kqE0uFOofa+3mnbEGW4E8MZQ+qB5GVZjrH6CN1FsJ5noBvg3qkkTFPA5QUm//r9M4aB5lxMAc/hn6EY9A9gK8H3wEwZ8OUwUyEuQQmDLMYZjnMj2D2wfwR5giMRW/ovKpOuF20m24k1Lt3Z8oLbwMoCHUfT7ACSmHu3032I11Ry2L9LbGY+wMaUqNlaaphZsOssQR9BcEs1AjlPJhpnFKRhWzWamS13jz1a+b+AsKVXVpYgOC20HCFem6JQ1bx7fefV/uFN/XTzPux/NSV4LZs1U9ngIo4bftbo2u/xPvh0TNDxjujreF63lrNR5X8iZuQdaMe6CJuI36wwHyeJP8qQZiBOxDCXOi9bYW8eALRjjR2i15+hymtm5zH+p/naMGB6eSKiWtZsoZc14prcXIscwWoMNwB1WcaT0bdTMkBLqFWJ3u57DZMOsQhmPKHTnasYce7TiH+J/8k0FqGHhBHDTvaxVHmIseT4ljOPg/h12rcJOEsalcYO9CBxI3OjT0n4fX04yNfvwR84mt8jdWu62I9OXBLoQv0io8TGBgBdWeYKpG3wKK/JxAkDi+9v7bc6iSkTqhMoOEPwdMAEVh3vtWTQsDME9rTxWG5VmDak0HM7ZEbVTmnPr1AX+ZRs4M2eJ0BX1wyYiYEVXqNcBmk1vBSY5LmiLROZ5bpeNXpnM0bv06Bq3tF3dU9Y1PWn6L43qb3e0BIj3w42Lo/ho2yMmtw9OH08rqIapy8Rd+DSHcUUNTUter2kMgupOapJrFGUzPVKrGuStXRyYqKDs0OgAXU2vmmzPbW1LlaAlP7X8P1DZn+6zWHM9r7CF1qqKb5cuz4KpgCCP0/yNoJf8j4nPshByYo5LL5pDoNVUn2QzBKOXk+3Z6820B8hka+XcnSW4TjegC8efSrH11hHlBKMS++RX3hKLNIyyduxgpENq0nPSEfsCp6/XgeunWLrJbHmruKyj53M6/kOtEaJ5U5hTA45HgpN4wNpyN2WthYVkYYoTxkXUHKV+c2uXjpIM1UxODYRms=
*/