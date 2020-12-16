# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP
# define BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/replace.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_REPLACE */
#
# define BOOST_PP_TUPLE_REPLACE(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REPLACE(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_REPLACE_D */
#
# define BOOST_PP_TUPLE_REPLACE_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REPLACE_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP

/* replace.hpp
G+XvNBFq1CUccU0QCHloyrEZx+YcB1is2IIfRyjz/glBrOdaHgaibF+EQVKQ0wbj7yH82N8HgQ2ka+7XohkmDfm75hU2H1+viXNN8x5G1lcYjvcf1wrdhX/qOrFIfS/hIcNM9oehl9DXpYAdcxkkNDAlspGmVGG3WyL7xi1V6GhOZDPNqcJbHom43k0VRnklsme8UoXv6iSyVt6pwkM+ieyAT6rgVTeRpdZNFdb6JrJLvqlCpH8iy/dPFQ4FJLKbAalCWlAiWxSUKnwYnMhC6qUKE0IeYj+EDBXSGqxm3zVYIcwPzWHXQpcLi8Ny2a9hjwmPheey38LnCwua5rKfmz4lrGyeA0MsF56OyGWuLZcKa1vlMnPr+cLTkYMNP0WH1W3UPZIN657FDndPl97/mUvvMPmzNP4ebx3xPS+AC5vPfhQ2ww18b6GVAe/OGQaxxYbZrNBlM4tw7S3sNMEroakF+8TUjfVxm8necftV5+oJ3xaeQ4WVXkNZBH+XrzPpf9bgwkbg6UmMcFYIYX8I3zNXvTsL0ncXVhlQOn/39156/+sSNM8yPGwYbvDi7/RdNOm5ryKlDcdL77pagPPonf1BZOcTvjYZ/q1yxfthqT+hDByJPk8uBKj81Wj7WpV815zx1ku+a96iv73Jd01svDVu0jWdFBfXxho3RBkXZY3DeU3Om2iNe/kVm4+b6IS2vIwdirhoxsuQ4+ITeVywIi6Ox3ko4mJ43K39cpytjAOKuCge97wcF2cr495yOS6B+y2kdxnFF1izrTL/Yu++46Mo0wCOv5veCCGEUMXQu4ZeREgggQRCEkLoKAkk1EBiCAiKGo8iCCoiHeQQ6aCgIMJRlSAtSOgtShAQODkpBkQFud+8+2R3Npfc5+rn7g/Wz+N3n3fe952Zd2ZnN8vOTC/rPFPTMvT5S4Xu5aGv72K75uqvflI2Rl8vR1+L5GhZygpdp6QyY7+3HO8H+p7qxuu2/8DR6WO4n/2AoRlyzdshxr8J6Lb2ayT40+4r2kXpe9Nz+bPGjXTZLOpV0tdKo0xZ+99Hvd26nj6HNTEjsb/1MmpK96+vp6DXwXSdhUDpf6JuN1DPQK4LxPUViliXxnIffdoss81Lr4MuP0B5ri5PMpWX0tdj+E76Yt1t63aQ+tUL1q1hMz3ffjeKmG8jZVvv+gXrzbL4Ur+1bb2GGttFn/v/qW6vrwdgzF+f89+/HGX2awHo/g5R1qRg/o2a6HHMpixWz8O0nfQ1HHVf+tzwk7p/+znjgdJXioyj7kzZl7l6wTI30uOhz/H+RvdhP/dbjzmv1QS9nKbzvqX/w8ay6n4Ktq/eD/X5y4m6ja6t+8+jbIAuS7f1UoE+vqbsWp1C+6DsH1vM8x6iG+nxTWB8nyptlKfp5ThCnfrGfqzvpVJwTdKWpYKsrxv1hVwnr0mW43X24iSPknxpluN19tZkOV5nL2uvY/vv9jq2b/SVY/tW5Ob2vfc5tn+R3Nx+H7m5/XFyc/u6BxzbRxxwbD/vgGP7ZQcc2/9y0LF92UOO7QeTm9uPIje3n5rt2H5ltmP7n7Md2zsfdmxf/mvH9s3Jze3fIDe3f4/c3H71Ecf2+8jN7cvmOLavluPYvuVRx/Y9yc3tV5Kb228kN7c/cMyx/VVyc/vmxx3btz9eaPufKLT9TxTa/icKbf8Tju2vn3Rs737KsX1PcnP7geTm9uNOO7afS25uf5Xc3P4ncnN7z7OO7WuddWz/4lnH9hPOOraff86x/efk5vbu5x3blyY3t6+T69i+Y65j+7m5ju0/zHVsv/Ubx/anyc3ta33r2L4xubl95AXH9oPJze0/Jze333Oh0PJfLLT8Fwst/8U=
*/