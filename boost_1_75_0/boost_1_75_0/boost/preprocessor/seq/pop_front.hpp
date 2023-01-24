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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/seq.hpp>
#
# /* BOOST_PP_SEQ_POP_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_TAIL(seq)
# else
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_POP_FRONT_I(seq)
#    define BOOST_PP_SEQ_POP_FRONT_I(seq) BOOST_PP_SEQ_TAIL(seq)
# endif
#
# endif

/* pop_front.hpp
GyDareRssJRa6jdMxrox25AX/s50P7QNQ74TjjZY63nsFed8SZ/SPQ4JkU9+F2N54jZ3fFOgcq6YdaxkseOxgK4y/+5KUtiasujw7KKn/aV8xFYxbu7P3McLRI6o5f3ZKhjrDF4G3Pg9mwcJ2ILoqgkOsa5YPgprnzOjYFBnkrpEPFs++m2yTiG5/GoHoPgc2W32LtRVH0qF6sQX6E/wbiPQpBhMCXaohyy2/7TDMq2yW4++6uGGj14+vmLS/fPnN0ysRsERtCy2TUyFsPPqcePrPXSdLHLvRxUp97GfTz13oFsE9+O0qnxGuJQeUVQ9YZbMDxcwykpU1ApDSFq60qhb93cE/4F+62F12XRSRL1i8dNA3Y3yDfT6HLfOd2xCgsH1jxpsfazTRSBGQ5QezNdX7MoT3QFdoBp0doVLK1Y/ClkXoYhGzQXcwPt6sVfyrVFg93RTWiTH0A6CjRYu+CdfkscFn1uN9tkvx0CBepHm6ftWqEf+/P0XJPBhffxk2GNBxdfcjAxWFL16WFkCLEM+9uVs7X/xXiOz3QyEcwrfzD9+rv1kKbTqVPSE5N8kaUA6ym6ErwS101y92MGKyIlAz9CF4TIQDjFEEA8VKVVHjuLVRICjl/jNziNG8VVoc6XOxM/Md6KP+1ZiVPGpv5PMRq7EHUm4MeDQ9kYciX8MFRw7Aoc1GEvRFNJsSz7g//GSXXKtOVfme0nu
*/