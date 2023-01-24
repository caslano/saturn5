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
L3/5hfBv5qM4/9PvoQL/unGSKJar5lLKobjBMiKSkHC4FJ6cI/Xbz43RKhPDi8MjA6hoVEgIbyxPGTg5lWIlySMSxZVGW+eGcJhKHinEp6aYIFPFuU4dKnM5Tvx2rM9lkAvW41YVVqe0nBVYVqOY02qxOvhZXIG07zPPuaeNPzj7/uJwzeNC4j7bY7MTGnRDRbL52mmj+/oX91ljtq8+mtaf47UjCP040Arx9300K5LVc+Ae8JCUYKXy6Q7utFPbQjGDG8I+DVn+bdm+D+FW4VEYafg8JCx/IWmkU0pJ7uGuejqEleXhyqXTo3K00b+/R4/e//5Vbw7zbUlQ7kpf/75V18uHmbVcFYMXuEdrnrxJr/kYsJbUi+UoVBibyLf9DJdykIJSPXxpgF76YZrrGviF783BhNWEPIYaB+PmSbBtXp1TRFBZwIXHlKpVPv0N0gGZRwqUVas3vqduP7No5aHaYeMaK/fVuC/q+AEKAZxgikIhjxiHsX5H+YG011UYr8PJb3r2Kx1unvbeRGlOlB5w5JWoNjG89k9l3tHcDZ+DRanOT1dfIA0l+erV9A9ctDwc0sFS0v4mgnt1XmuHXSeihxzKotL74rAQcSVJSE8Gez0o+9hV8iqE4sdz/49XTnQXVkOFtsj4djhlX0v4KfoSkfNftpGoMKrQAQTOLF1IAy/qSBNABHsMKNOaYltMfayr2DZun78sVkFK
*/