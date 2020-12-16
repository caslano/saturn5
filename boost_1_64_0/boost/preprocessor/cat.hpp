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
# ifndef BOOST_PREPROCESSOR_CAT_HPP
# define BOOST_PREPROCESSOR_CAT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_CAT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_CAT(a, b) BOOST_PP_CAT_I(a, b)
# else
#    define BOOST_PP_CAT(a, b) BOOST_PP_CAT_OO((a, b))
#    define BOOST_PP_CAT_OO(par) BOOST_PP_CAT_I ## par
# endif
#
# if (~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700)
#    define BOOST_PP_CAT_I(a, b) a ## b
# else
#    define BOOST_PP_CAT_I(a, b) BOOST_PP_CAT_II(~, a ## b)
#    define BOOST_PP_CAT_II(p, res) res
# endif
#
# endif

/* cat.hpp
Ni3mePX2eJh41dvjyiWGY5ffEYZZqRBn9VLBASWkzZzkHEc+O+/CcXddfpY41dvM8DLGcaRzWwB3pzPeqjnV28x5w9GgCX9Xg9kVQ/ccLgyeB0v192696qp4L070DKfS8sKIdHefdAzcFKF7+Om8rxW+L7alZ0u8O+4Mv6GDwmsb0O2B8FujV/VtGYA1LqHDd8VEJGkRy1b73kJvUTDsQH+sr/uqnh4rLBxiKKw5h8LDdscQNtXdn+qd2ztm4yjPYrkQVe9Sb4e+5vnnTPAV3ps5TK9C+RbPIpWYbn/a7zepru5t8WGhG/sWJobvamA4HAOvGy2O87c1znBcKP/tJuzwPAvL4f8d7DyJjUOHTRdwWiJTpvgnGxlH6GBIQMd/3sZUAlpfLzRZOE+Av8nUzHjYRcEbJrA+MFuHwAO2IPVyAR4X8AudjXdN8zUXAqldsMy4z9LFb97v4dwApWTGRM1xpmvK8uACwRMKtY4DqqB69VDLGW0RHCk/r8v1el/Tx3H2xm+rqcGB4Xj3cGKgX/zak0iqF6QMv3dhOF/r8B2K/9lwvnmBiqXRuWi2MLBaMP6JcL56fcrwNy8O56tDUOAr3d7no8exN9f8AxFUKcI5zfBPLWF8NeK5+KvovSzw6f2eKawwTZvo0GuWu2gOToIhlmq54PaGo8uCYXhO7DDke7owuH5MJbu6B+LJudnhx9ud9+0/xHOp9Kb/3NhAHPfShtnHCmbvpysW8+0xpP/vtzDVFJdp/CkBXNmGgOu9iibrPd2h6RKWssNYOEU7+Ts0LZxnSMP5HlSZT99k3gZNWX5QZh02SXtKgfVavrJ7MkM0ugM9bfyxx7P76ftR9h3DGNXjLqseu/v7u+KJrrnZAVCPdL4R88rEfdCP/bXLhGiYu0dFBqfKFSTj+/lmgQ9dMzQc7xtO9MXltyl8S6ZEbxLf5Pscef+bYerw+/BdMPm31rspe586GKn1jFuFbUqtB5BJlH3OvAXXCCxkXruhieHCqKWal553VjYzXDQ/FvZ6wtxzojff4Pac+BQLU8nq/X+8Z2jhyr8cDgZ7sgcwk7Qb7unZuB3MN7kFXGsu5vjyhQ58A/quDm/hrrl67SLDsefqd9qYZVuLLrZwXims7M/YPCUI6StLXPgGSueswOegExxYCp6lE3Dfi9t9vIoZnduX7kI8NcYwH59lFpb2TUYlvl94zOYIa2AGB/i4j4TixlptbgnzguKxPJ1lPPtcbNPdCLPNRcTZSxx7iDJpnDEcNfYyP6C7A2P2Yjv+HzBcGFpN/KbsksuJYx88NfZ9xsmW/DiKwrk7C/MvYBPXPYiHYSS3Lz2Vzakxzdg6DUfDxtZ5icEwB5n9W/YdNVuc9kOxvn5Pwp2HQ3mZHVdcbi5jOPzmGF4eLZaluMZGGsDzBQVTe/fuJfAJ86SgT2D+agJ36I56vky18PONsUTfQH9/LCaenguebzxP/hy0P0vYHww2YWMXg+HEaE7YPwPhgnc1NG3n4ajoCF9k8AmG05y9yuD2We7VOv0rgmkIKzKF7wliYhtC7J+MlvImD0nGEY/L5XzvOm9Ux7GTcDkoIgEVk9HVhluCa8e+3q6ebcmeuelqu7P+3nFU+Vq+GnNwmx+fXJqXBFiQ+wBHgImMYEUi5mZw5d998eHegZicrw/jG6Kkc/noJ3SPwaU+e4+I0fgxNOjv6D1quBIEUxZsXAlwQWJjV3kew3gEbIxc3ag4Ckdxmpf9WH86zXnULEx/SDUJHJjVLPQ7la3NhIvP9H2yRX3Xb1PreYm+ixHEfB9eqL/jqHvJfD9H38UOmfn+lMXquxoL76b791LxXfbpVdqvrYnprnnxlFn3cDo=
*/