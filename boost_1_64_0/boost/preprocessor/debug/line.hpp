# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_DEBUG_LINE_HPP
# define BOOST_PREPROCESSOR_DEBUG_LINE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/iteration/iterate.hpp>
# include <boost/preprocessor/stringize.hpp>
#
# /* BOOST_PP_LINE */
#
# if BOOST_PP_CONFIG_EXTENDED_LINE_INFO
#    define BOOST_PP_LINE(line, file) line BOOST_PP_CAT(BOOST_PP_LINE_, BOOST_PP_IS_ITERATING)(file)
#    define BOOST_PP_LINE_BOOST_PP_IS_ITERATING(file) #file
#    define BOOST_PP_LINE_1(file) BOOST_PP_STRINGIZE(file BOOST_PP_CAT(BOOST_PP_LINE_I_, BOOST_PP_ITERATION_DEPTH())())
#    define BOOST_PP_LINE_I_1() [BOOST_PP_FRAME_ITERATION(1)]
#    define BOOST_PP_LINE_I_2() BOOST_PP_LINE_I_1()[BOOST_PP_FRAME_ITERATION(2)]
#    define BOOST_PP_LINE_I_3() BOOST_PP_LINE_I_2()[BOOST_PP_FRAME_ITERATION(3)]
#    define BOOST_PP_LINE_I_4() BOOST_PP_LINE_I_3()[BOOST_PP_FRAME_ITERATION(4)]
#    define BOOST_PP_LINE_I_5() BOOST_PP_LINE_I_4()[BOOST_PP_FRAME_ITERATION(5)]
# else
#    define BOOST_PP_LINE(line, file) line __FILE__
# endif
#
# endif

/* line.hpp
964Jh4aTAiOfe9iT90B4uDi2G/2rCYrOgMohE7rMmjSjHmSBjUgx2YM+v4bxWckGkY+tKd6DZoYlVRlt/G3+kt6lkNavSx3W+hUEAcIuAZYHIVVwKFon6RI7k1SL3+CpmVYFSPjSzdEL4YUFuWtm18EevaAc5Rzs1wvStp8uKO86O5F225mxzJEbHSOksqmlphyyqrozFy8L5eFtyl4c5OXYWDGQ8cK2DmPc2GA1AN98ynSe2CbUuvkVlv/UD/dMt/mZeU18ITGxwthH4eYrnDPTh7O1xj9IT2R39Hxu8f3oK9Tbc5qHp4GLNXIvJg1aIHRknTNy2kZHUQy0PvTwbqLZ3FiOnfpEF7+aYAJcXn7y0R66kOKcmY7YkOOoV7aLfx89J695ohMvPKP8giSt3Wa6ilCiT5pRydxHNfcaC5YhMlIuvb5x0O7qb36hpwNqVQfOa4SivWtCrOb22NW8gKk8iUllVwF9FaPzbHSjRleXjQB6BKNLbPQNGj2kLAB0gNGVNnqkRvfJXoW3ImS1jRwgSMwVGE72eJqZMp68auwXJ4+nAms8DXGySvin7RsIohnp/ksMp+aKZEN7evb0xXK3xOw5PgcpimFEeDrdWMTza7Lk5QIcgAsmdwgrclc0nHDXxxOdY7mMwJbbhKAxyy72bXGuVvMLhODTZApyI49Q7DsL3yH717CxALESm1/buw+PgUSJGVK9AwrOiijWE8VTDSfSX/sSRK2H8Zc9YjdfT7HjC6aTLYNIS6yogr5bFNuSaktUASuiZMTLl5Hr8ZuKM9wfE+O+426MF0WdKIQFfFAdUixhILlTQ8bhQ3wXMUZNCMqmD/AkCT1pozYRCkLfakERU1d9+R1csQ28sdUy9EGf4z645dqdNN48/P0jqF8CYeoB1IE3Ycgl8fMjgJaiRx54WI7pyfUXJ1kheleaw9xDfxzJBKn1qHnzSTK4GxDZtd5pVmnkzoYfk5Hz1G9QVr5BvyaItT8Cgq0OBMJGM+9rH+MoVLMj0aswB0ROpVofZdzL6L0WukAuBxO033jBSejXLXTH4j3IMvuBdcN/e43xx46669ZgTv1XmoPral2CPbnqCDxhtZGCfMMyPOi/OO3On4e16gvsBvMMVBo2f8oldgJhCywqrNcczfVI+hUksaqnWOgNhFnJ5N6xt1vz8Iu9syaedui52JsNn6Qfeha0WeknULdZN2zqMNhatVShhLgImxW23aM9jHa7j9/3uayIfw9VLjCuwxYmqjGVUOEC47Exv9GY8xrac4HJtTHDNCYH52Js6ECGZsWKY5PcKPp4s/92KMurzy6bfFdn4hlGGSIkSqa13SFBHwXPKvseGVTaSe37TDLoBZqGNp/fqLJx6xmXdeXIxiN3PWn4bcRzQNAEjYgpVwb+i1VAeet+cp/a5wDzp5We1U3M1o04y5OEVoJUxcUH1CLJSWuovcZoO6+hUsD4MtqsL/SnXm/de4bXB1BsdyowcyOEpDrnIGgnI2XquTiXNLfJSStn0iL4VSNg2g6fAMYEO7N39wvfH8m6ONlQLj4i/NXidwG5tM3meZ1v/SyRgZNNtIU5y06sUSfGa6gTHaKdVlF9xDdy0B0d15jEmy6w6YP75U3f5OVZeFUm1d7lVmFPCxttNnGBTvxREOEF8zEKXU3ORK1f3auYwSR+13CiYwTF6hQNI6cexj47cuJTafTr1Bxlqn1mQDUHVvUnZebXM2wct6O0fipCYVFxG9LNfqCteYKT5GhUQVpTEc0ujW/A15+vecpxyq0z5RtiyujYyW52r1qPdKAhQi40MK3v/fBVXvyZykhX0LnJqRYpi1zcFvVY8FKpEys8Iy50rQVpNP4=
*/