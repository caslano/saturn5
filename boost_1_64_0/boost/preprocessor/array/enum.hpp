# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ARRAY_ENUM */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_ARRAY_ENUM_I(BOOST_PP_TUPLE_REM_CTOR, array)
#    define BOOST_PP_ARRAY_ENUM_I(m, args) BOOST_PP_ARRAY_ENUM_II(m, args)
#    define BOOST_PP_ARRAY_ENUM_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_ARRAY_ENUM_I(array)
#    define BOOST_PP_ARRAY_ENUM_I(array) BOOST_PP_TUPLE_REM_CTOR ## array
# else
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_TUPLE_REM_CTOR array
# endif
#
# endif

/* enum.hpp
YyXyeTno3wv6vYFvL2M/MNvz93ZtFwO+ewguIFi5M2DvK3gXhcPOQDqfyzoGP88ZGIkjvIfCtP81l8G+00soXMvv2QGsTtyrcwXBltH+1GRygPpqUc2gCXffvI/5jxVF3ON6uf/eg2zSf+9FfixKRh0fSeUSesqfrWsxOO6xMTjSwS4D5PvJw744vvUezDkmaV1JI5wGzG+9n+WnWueHZOSZoSBf8/squ2v6g8y2rqLf3Fc8xs/AIyzPGiuYvI/p6kUF/OeUspWGP8bGeqRv+3tmBfbNlZi7QOgFc1rRO0nd0NWxMdrX2tLV2dFF99X0tkV66fkVupGlryfSqq9uMXcoTxmHXmHZ2BvRN3ggTumUcegJ9UhvZ0uruo95+nGiW3vo1hASsrOtvaO3r9/wmDEdHp3dJwbwIPW/OBWT9m59hxDxOqbB2cburPnUoik17N6JMgVRs/Lxtsyi0Y6+lmjLtpaOzpYNnXQB0ZomWzYS19cXaXCgzwBcY4Oj9SRx9Gs7eIYm4CJd7XQZzEbgZwbFRZrORFzvlq5+J1jWroi9XykQpyI30Rywex/3gdDxtaRjRtvR2dF/kqtUCXXvTwre5xSNbIvQK/50BU1LtC3S19rb0dPf3avrVzDK1rXPLPL2EzU7/ndKDhfhChGeK8J5Fjbtw3Xan4ytblgTHSbz0j7scx4sTxrRsOZqC0usga+73qNLrG5y6TYs8GCG3+cZneF3Q4WXhuF3T6UHM/xuYLIofkudWapsln+B4GEqR4XRHRn3p9bbuK9f1JPL+PYx9GH91vj43jgtYu+IY89unYb1U3vphedYmtXsXIyBNTib4eNv4v3r/SzzN/vGEh12/0Gdu/sJex082AyndTQ2Ph5PMljI6YzvIAjCVIe604Opobh/rNFv914frvVyfHzXTve+qPVYy/5iQH4KZYXn4gk+dhAy11Yq+XpSKfQVdlfotY1kPDaeT2/MpPJpF34Y0ZX74K2x8cF4shW9BZOXGSElW29sMN6WNDpYUqn3mai92fqyrlZssVC45YSrdtoT47SscLbGgiN0cTTha7F2NUPfU2HwPfZtFZO3ZbClzeiz3OLrs0T7e6KtLZ2dG1pajyentq2jl3zMtmO01grgSHeB6/TT0L1eA4fPCPRF+ymX4vsVr59PabA78wN8VBl8TlqEK0Q4J8JLRDjPwnt99XqsqVG5J5T5bYsMjNwYYN+wMHJZsJdvejByMdjn4cFs3LmOhdk09oRtupbfHTZu3vL7lgfT/A6Fz/o2wcvIZxEGLot+kW7RL7PzNDzf5VgDUHmeAX1fy9YK7sK8eIjornRsG97b3xpt3XR8X//xpu0GbFtvP3VF+tTFeu3dwJUC193bu7Wnn65io9K3fRyNo44avWehYpJ1RLf2RXAfH49HfRyyHCLQuJkurqOzM7KxpZPOO7B+yw8WQcJIJpPKdOmLMd02VULdNnWVzdd4DOctkCfa02XzMEbn3Ebiyn9l9N16ZTqtu1Va0R10QjlHJ4UGaPIku3Ytecdxc/FhC+A01lWjpGjclcT93RxI2SwYqv5TjZUxm46TFFo+7BU6m+QphTz3TEMedchwjDgYmRCellynB/iAYiXQLqHYlKhM9Pv8i/z7N36k558P1ONahbuPvtmlJc5P4Csn4tyxjaPHxLP0mPenBFd/76e/55Cew1UuX5TXPhW+l8JWPwQ7hDT+M4IFio96Sjz42FjzCBkugNXjTA9N0NNgz9XnAU5l6c+Zry//D+lzg7Wp+IZUSjWFDuw+3kEt2gjVGth+vJ1ujs15dTbelsrTaSi9R4LuAIXt/TLI9kbjyXQ84wPtWB2NJXOklykqRwBd8wQ=
*/