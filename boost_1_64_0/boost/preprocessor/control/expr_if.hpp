# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_CONTROL_EXPR_IF_HPP
# define BOOST_PREPROCESSOR_CONTROL_EXPR_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF(cond, expr) BOOST_PP_EXPR_IIF(BOOST_PP_BOOL(cond), expr)
# else
#    define BOOST_PP_EXPR_IF(cond, expr) BOOST_PP_EXPR_IF_I(cond, expr)
#    define BOOST_PP_EXPR_IF_I(cond, expr) BOOST_PP_EXPR_IIF(BOOST_PP_BOOL(cond), expr)
# endif
#
# endif

/* expr_if.hpp
Z1yVLWZG/4RROPU2hnqLV5BQGWkDCqheJ8+pfusaVA5EzSRGXVO2e2NF6YuLYkXpD26wWgMy+7OPs4Y3YZkn2VVPKxeRerXty5OaVHLejaRutWGOb3/X1Wyrw2i+ZVNrgY5aBV32yGYgPURT/vDKnFMghlKLqjKIzmn7iM7bvT4tJZGgBC0Vx0MXbX/LURzwizXcDZod5d16T73BoPomkdRYYHX71YWm1Lifi6YCWV+/lrIJZaRwnlc5vxXt6IUad3dLJBrc8aXZLTQDHXKf1yE0rm2h0fZfnLvwEXd1Y57hC+XyWRoBMotNunFHzUJz1zpTw985ONcc6L6Y7l0QywHfX6hzADq6u9lJ+nD/lbH6jcPBG7lEPHz+yGOeNLw00sTNRUmviMcvDaGj4XB40HxoOfOghTikpvXkCtI+CGcrNGouGaw7q4V6RdpWnyVRVhPfTA8SNalev3hugdQJEhu0lZOg8HOyTzzFDU7MbQ9njjoVfoZEA1Yiu0/8Bhkq7WJ8WNOqEPGJGoZNi7R1JvrELRxxoFGRdaxoYkczD+0aZrVrt/ln6Qv9kc3ToK3I00Opu0Zpn8o2pHCZtV5Vedt7JBPwzkpjzcpWP9pJGeLlq89ZsuZXmsznWdBtyWqc6vRFhnThjefK2oT6llCK6wnsPQ/IvfCwtcW2YmiTnZGpzsgsB/ix3bFGMQwCc1uxww8di/SYMNVRM7yuJbmqvLEHt2/70TivtsIpJlfqqk1oBepam5B3WciZNzzkyN7f2espQrGmyOMqBmbgbxy7RpvqaNgfSiOsSWuRk5MQSihGLHyyLUEpjpaDuxBz1fvw4hqmuJ5IMFoaji/OSQi/y7njkMvwmXipmAfemqvvx91EsifCGCmSwe1YQ+Qq6qo/gadcLl31x/AOSZcOVH/mTXfQKy5n3oB8akRG4zJPprikwmD7b3+XDBXDChR/UKQg1Qv+zBCXoQSMOj5EMsUnlXKrmkr8l0frpS00LQIxF/CJt5AX8EFdehMvQXFHJZXz+0SHXiYdZcKvANgDpkit0sCA6T6xzRj40NApwcZlqPCe+XJ3KlzrbkPH0Ts3UVhtW10ItN9GLsl7NJnYkNY1HkN+i9G/ItOcEaU25NRsrbuDooRKdUGHi6tshc2C9FWxpgINxH+RQ1VLfWIitzIgqvugKvVbxElCXMxNSW84HnYHRdJ8fYqj2spW0KjnfIlAnWtXMGe6KiSGMRaGQ+Kv5bwsQ8Hp5QuKVzjmBAIYg6xJE5EKSh80yyE2z+FqWkk4RB9BBPmwugAmsWFneCLgxk8AScL9GHqFhIYWac9uacWAJCthN+cEjZxVbzGBWr2lrB1ex+mJsVP2/mbedYb6ecWISn3nSEn018r6ArrJS754RRLBK57FCzFf5ITqeb4Q3V9YTsMvrsdD/TnvVFm1/mQeFcgwEaw3EKzGi5oFGJI6Hll4CBXOY3QX0esvLTxbGE8WrSW8sYgR4nExQvxJBnN2F0jd4bsp+Xd/AfjYRSJ4IXgDI9S8e/Gg/PP3J9D8B2tfd4gbKtCxdQlmxw5fz6KlorV7/b5IKs3nBprDudCnamhiz3NgEvtg7Km+3hjcuZHRsK0Q8RYhDRprGiwDG8ulMtZFDJEQvgy7u3lShnclrBoYFC7EqnpEutR792NOaS9J0ZbiKxYDrjdMQ7/B9MpuAbHbaZ610qsp39NI/oz/Wqy+nVoF/SkVSm67g7Rx2lSH+2a3kGmQ9v/VvJ60klZdZZP2Cy1ljtylX+I1ybdFku/UocEtBXrRrXpRLaUDmXrig3piDH3VTZcVKGoLfmhVI0p/WK4bvcIjIsUOrTpVq07Wqt3q+n3mktJrLoM=
*/