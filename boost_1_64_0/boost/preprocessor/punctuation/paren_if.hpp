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
# ifndef BOOST_PREPROCESSOR_PUNCTUATION_PAREN_IF_HPP
# define BOOST_PREPROCESSOR_PUNCTUATION_PAREN_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/punctuation/paren.hpp>
#
# /* BOOST_PP_LPAREN_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LPAREN_IF(cond) BOOST_PP_IF(cond, BOOST_PP_LPAREN, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_LPAREN_IF(cond) BOOST_PP_LPAREN_IF_I(cond)
#    define BOOST_PP_LPAREN_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_LPAREN, BOOST_PP_EMPTY)()
# endif
#
# /* BOOST_PP_RPAREN_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_RPAREN_IF(cond) BOOST_PP_IF(cond, BOOST_PP_RPAREN, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_RPAREN_IF(cond) BOOST_PP_RPAREN_IF_I(cond)
#    define BOOST_PP_RPAREN_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_RPAREN, BOOST_PP_EMPTY)()
# endif
#
# endif

/* paren_if.hpp
LlzzkeIble5a3nrFqex33OZ45EFFXEPPX7QY5BBGstnocV6SnNOERhA2Hg1LQzngwj3Vd6XTxYstptMS6AG5Ld3JqbGH5Dpo1M33crWJyPWkmCh11yj7pmdYv0J/dvbM5Fw8L5hGamp2bmZhRlB821mDV/zABuXkbYSJK7YT5eDK3I8vfTfZ/eRdkmRtIfYjbwp720jfYc4kdmCL4Fy1sfQ00Tu3LzEal7f3Xd/Z2vSt7z3OLNx/6p73ODUz8ZDy1H3GZ6Zm5k7e7vZr+rvdPRtyftrkUdxpc+fuRcHzfHgitSUvdtaSnJTo4fWidyG2cVLLart5mGLHzHy3OrNxv7LFl4P/5s7jmk2eCCBpB2IxbxcUgyzednY2lZ92aX6OSFbueY8jmi/NpZU/bjqjqcpLN8ym47YebUGn7tqnRdAL5bqDh0q/NYJ7L//KRcUpcYtXxMF7ncn6X+pMqECrbe+pSW+vg1Ih8myvt/1bnp3ssLQagi94m6v1vdNjZ6fOzU1mY0q9+2h82kl5no/7/pBOVYqRDHKNlCZEmtl2cJmknVbG3WXOr1QDehAxApNDQ9dJslQhJEh7BMRvCpbXbttJR+PojmvuFqeNg2VKbUyy/VdvvSN9a0tbGyyq0D0ydnrx3PT8LLrMnvjEMqJFxmNsYkIlLhcN3be0cfhweac7lX3S54RoSPzIR+5DkyAO6uf/nQ6Ghf88IerJ+kwuJ/GgTKmFXu9hfzgqPT9lWZm1z3WcjHVVjRPVBRUx+n4o1IoPyodcL8QlFUn4nXLdB7AaVKKUpVPXB7GyJC/OB93Y0gVyxlDqyBhfpDTRvVTHy+aDsVCw/ZGkU4KKvJSuld4mmzi7h9hfJfroUHFaeACp+o+l8yZwYmtGVd5UL1nbv/WSFwWv26rAfUw3CpX+KJv39AzGXjM9POOWULprWhgywQk3ccV4tlGMpZJbazRAJsWruqMGR9a6d9dH6nRE+e4E0K/H0pUUgCZgbyg4CMWmR9kvmNQnpxH1dVcDiYbHSYWSC20v6fpN63XQ+CWpTrl6EIXrROC9Z7+wO909zVHVOWYYxT9cnd3Q8pO0uJVInD28tIXttQ3n9tnSa+yRx96TnztuL7Eh5GvbbE2b2WU1SQ9ccp3T0pbmJ+dFzLyxn20CHDLbD3Vv7cfclczV7EjePrV/OUfDbPcSpeVPNPjnd0f9rNUCuuvi9Mz4mbGz02W3lqOuT/YUo23M/CZPJdivC7+lLsvTqECzsot0/4rhPaBqnjquRAPT4K6H+9SShJ00Dx6eO0l9snegAWsl5Hl3PmDMZm8qjYtCPCiyg+bDLbW11NuuvY/RIniY3cOefOBscHWZt6Q2EsUrqfHpPmVV4FPnvK2O3m1Y3V1puoVo7c3aWixDyPxX52h9iPaR8MMmeW+8Yj1vLGWBcaG9aKnxc9bKDBZOxCV3X6ks3Z+jL8pYAWAHBO1rnG7R3Fxqywnn/ZEmpXR1SiAzOvroR5qz8dlzdoBoo70ehC4+urXcrdKsKEvkkkuXlm051zCyorMB527Vn8PHh8AtNbsDwyMnBtDKaO93G/F31tHH9Z3cP26NjXWh81x35wqeq92lK4ZH9Dk8NHJMniNDx04UnYDvBHwn4o8O3XVEnseG7nZcnnc9fmJI6a44qkkpmiuE0iZd1Tupqd5HCM3fSVn1fvRExF8xMuzvjxk+frR6HzmavJ+I7ySler/irpXfZfxW7/iN7yfiO36r98rvuibf30l+9U7y4zvJ93eSX72TfH/X5Ps7SYjvJ+I7SajeSYK/a/L9PfFL8uM7fqv3xO/FkSuuGMblJnzf6NgDL77qoz/8XXjcKP8Oj2P74fWB438=
*/