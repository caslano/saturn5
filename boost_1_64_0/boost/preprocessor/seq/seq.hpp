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
# ifndef BOOST_PREPROCESSOR_SEQ_SEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_SEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/elem.hpp>
#
# /* BOOST_PP_SEQ_HEAD */
#
# define BOOST_PP_SEQ_HEAD(seq) BOOST_PP_SEQ_ELEM(0, seq)
#
# /* BOOST_PP_SEQ_TAIL */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_SEQ_TAIL(seq) BOOST_PP_SEQ_TAIL_1((seq))
#    define BOOST_PP_SEQ_TAIL_1(par) BOOST_PP_SEQ_TAIL_2 ## par
#    define BOOST_PP_SEQ_TAIL_2(seq) BOOST_PP_SEQ_TAIL_I ## seq
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_SEQ_TAIL(seq) BOOST_PP_SEQ_TAIL_ID(BOOST_PP_SEQ_TAIL_I seq)
#    define BOOST_PP_SEQ_TAIL_ID(id) id
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TAIL(seq) BOOST_PP_SEQ_TAIL_D(seq)
#    define BOOST_PP_SEQ_TAIL_D(seq) BOOST_PP_SEQ_TAIL_I seq
# else
#    define BOOST_PP_SEQ_TAIL(seq) BOOST_PP_SEQ_TAIL_I seq
# endif
#
# define BOOST_PP_SEQ_TAIL_I(x)
#
# /* BOOST_PP_SEQ_NIL */
#
# define BOOST_PP_SEQ_NIL(x) (x)
#
# endif

/* seq.hpp
vszW1VCO4yCc6E6E0+HDc9A2LlY/xwleRhf8quBQ8Dqckp303u4I5pRTfyhYYCOb1gShD62p9xa6xwF5KKvaAr4KHkKdc5vS7Sh0tKXl79pKtF/JLLyWSXgzc/A2K+s5vpM46kX2uRnYt4LzO2e9adWVknlfTqeuAPi4KdQitaQzdG6oWxmiWCgVuhxfeAetqRvVOx4lvzbGhTChFNtToZL2wpfU/tgX2u/68toRG3L6Dipz1Bo+PUx+A92ZLI7Uv8vQ/66Sj5NRU4TZjK+K/i+9ZVp6IN1vEjs16S4HlGVZDX8KX31FZ2RbxG36tUfO0iTowSe0I8lIH97/YORadwuVU51lC81HHpAzUlQif49mxZxckneYF+9HVpgZa0oifofy3SItkQacq+LKP0rpRt5hp5UVw1+Uw+3dLyg5Jfs5pfJIo3iq43ua5w3tFAfxHt32/un4jufgOl4cNaLhqBO9LEomQfMhE90ZvVWtxPuUxClEn4Bjn42WNTdele4zHz0As34Er34Kq34Fp26DUU+BT89S4q8nZsKkSfWKB+WK3BwbkTOym02B5Kk2vGdiM7E9ymTPxd705uD7sRV25TXYc1NZmBZxZ2f83Hi3mDPmKkfizXT8RnXAR6Ug3a/8Kn1w6Z574dCqNsX98QXpnx/HG/HP4dSDei2g1Tnd4Z7XZmI4YcdxLnP6dddfx5Ql9cyczbGBjysHS7fy8Nsqr7qTUI3bJfypVedTuTyHfrzT1MS/INEjBSCpnXSQHYdcvfKh2cRueeqTiUfdnL3SZxXcqzntrO8kFuVifZJYS3yhNnhTsoWkzRnJTvXZ3X02RsLmcibwDnW1hpO7pGCNqcH5CMmPp7j5nlP+g9QaWZr90l+Xkx+Tovnc7bdoB3bbjR3oCn7ceqM3rC5cvzKT1+Hb71RyMtd7H9mGh2jIPaGmbZlpP6v81Fu4VAfwqD5S8xYNDHcKXi1s9znb3fwDjWO8KTIlUsNMwzaSRh+ewKC0iJvVRMoqdYaSi0pWlBu3x6gYLxtzJE7qypzQ2UCnWDO+UKqnSbmTMwKd8lkuDVja+y4PDAR2BNLs68OBXYFRLtKxwP1KcE6xvZdQMfZqL3ydzOJ+qWvLyhR8rmyQz0RlwzXuMM8x/ebFpmH+mOS7yhxCG86YO9Hf7jBz6oo/RPLgCZyLZ80yG80s7kVNufQD5hJq8SqO2Loaj9vYOE9h3zwr2IU+16PMXDLY9+MLOUoF3kbiY7eU5ElydMXgM8GZ4J5gRZfVm8H6YfXuE7VGN4PfBZusFqsNhZlcEvfGpZZlxayUtvkdSt4NW7usUesua4xLecJ6BMfoKaskZ+Qlq8qGu8/aby3I1/7YarDrblgHpUW3yis5Rz634aWa+kNXhYbw6DKhnWzCd6hzRItLLdVpvfHwgrcJvxWaP6wLfooy+BWOyjYS1qegW5OzV47YDNueRjPIbU62QsniLKnPfPiB8GT4Uc8x3kPv82V0mzfluizqJaBPULe/CG/iqTdFWiJumqozQgqDq8WKxNQ/H4hMkcErR16U+/KBXlz5LLJBnnabfTLceSa++wUwZ9i+jDzGIBd+Bs7cbT8kzfsnzCit52QU7zPhxfNRGEPRhF6ZuSZ6A/7ubpTvJ+HAV9gnv4ueF7sldmfsnlhv/Ar25gdRdBbjpzlX46W8CDu843zpfOfclHg48QZ70jeJ1mQH6I0mr0ZvvkdIfYoNaFvvqSAviROyQUdku68ChM427jWeBwNvGG/J1fjG+JrOaZd5Cd3qOpO8lW/qQrS1nez19/L1PM4unbUes562XmCGfmttV+/uttBr/G0+RBNpYqvuDF8UTjPVbg/fze/27fA=
*/