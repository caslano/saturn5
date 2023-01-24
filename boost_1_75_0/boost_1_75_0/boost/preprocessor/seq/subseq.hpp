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
# ifndef BOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_SUBSEQ */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_SUBSEQ(seq, i, len) BOOST_PP_SEQ_FIRST_N(len, BOOST_PP_SEQ_REST_N(i, seq))
# else
#    define BOOST_PP_SEQ_SUBSEQ(seq, i, len) BOOST_PP_SEQ_SUBSEQ_I(seq, i, len)
#    define BOOST_PP_SEQ_SUBSEQ_I(seq, i, len) BOOST_PP_SEQ_FIRST_N(len, BOOST_PP_SEQ_REST_N(i, seq))
# endif
#
# endif

/* subseq.hpp
WKg475/6JGuZ1mY7RnMlG/ZMdX6iqiO4wLUX0+zeGhrSyw8U3ANvyjAqKSb5U4o684qazsop//i5x7F0qIw77DZxt1LwhZdyg0DQaQHZQNkbt68KSB307Vo+HZXNgvgKckn4wY5qL/KVvAYjm61Esz+eHqIJ9doGIBgxrBj+sPcIrYuYPfwA64yfXTbXKZeOtglqSCIVOcd0xC8ayxsq46rU62x2Bkbow8pLpqlN8oC0opQCMtnK68ROMYMcmQIAsDIfhpZ8+cmrWyFJA+YpHf3suKGEfn9j2ewT0i8Fgi3NgilDCY/+9rGCdWaloTvdJcMJIg/Ccobhts+VbG06FEu7h8rZpNG3uOdR2MMjt4IX76+46hx91/HmzDgGXYwzlVMOjM5/+3ThZlj7p7WJFA5rwGpbg9nIWFA8sdr+zuvzhQKP5XgtnX/wOvbvvAbDPBMRObVkmkZ/5fXT33k9CvLHunnagMGLIdBMhsWUv/K67W+8Fg655JiBuh/fJ8J7zoP2jnjPp8o31y/Uy9+qt7ekj1inyWR59qYRMW7linPD/2BPmPlsUAlUqxBRq9SRc2+P2ussztdM3jgY/mxIuBvJVfB5vKxqiJjJJQrjtZJSwMHGnIe7oTvZx17zy/KJrSthUQq5shEU6wmFd2hK8OgEpbKD81vNCIC++v2Zg7VQr9XkTzgsWXCNuGZzcS64jJtqe/ul6HRKOtSf
*/