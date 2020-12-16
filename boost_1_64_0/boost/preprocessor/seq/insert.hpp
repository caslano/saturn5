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
# ifndef BOOST_PREPROCESSOR_SEQ_INSERT_HPP
# define BOOST_PREPROCESSOR_SEQ_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_INSERT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# else
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_INSERT_I(seq, i, elem)
#    define BOOST_PP_SEQ_INSERT_I(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# endif
#
# endif

/* insert.hpp
PJxxn1fhNfgc/iPfxQ/w0/w2LyRqirqiE2Y3Q/wotol4sqKsLtvJ1/Kj/I1qriapmcDIOrVRZfUr+8381v5uP1NQOqgY1Aq6BX2COcG+4F7wa44WjhklIB5RpBSpQOqRdmQs2Uuuk3vkI8lqCKOs8b0x14g2thk/G3HMJKZlKrO+2dI8bF42X5tJreXWOuux9coSdBvdRc/T5zQ15lLabo6pjLan2rPtvfZh+6x92baAoBJOWWemM99Z7qx1MrrT3bmYwnH3s5vey+rl84p41b3aXhOvlbfU++jFYvlYcVaHdWbD2Wg2kR0Egt6zX1h8Xh5zOMY/8ZTYoPKiKvZnp3ggouVyeVQ+lRPVGZXb7+jP9X/vX/Fv+U/8REG2IG9QMigPjHQNegdjg+nB3GBpsDrYEuwMDgUnYmZRBfqIP/KSwtiMneQmfn9yY7iZyspgRVltrH7WDOuaVZU2p0PobfqEzrEX2avttU4iN8LN7S5z14ABLri33Q9uyEvsVfKivAbeROzEee8y9uK2d9975D3zXnnvvE9eiMVhCVg49iQVS8fKsIrYkubsI8vCc/FlOM8u8oq8JWdjx6sFo4IJ+K+8AEy/CUINf93f5KQsTqoxGYHtvU0ekF8IN7oah42TYD7T9MzqQPNTM5OV2zKtxlZrq4M1wZpp7bEeWKlpYVqb9qKT6Ay6hx6i5+gDGtjfODmcfE7M+TR32jg/OOOdRc4ybPg7J4fb3V3t7nYPgt3u4ZySeqm9vJ7vlQBum3rDvQXeEm+dt9s74J3zCrNSbBybwu7ilMrwSrw5/57/gE3fwveB8WqJ+uJ3YqxYIbaIn0VSmVdWkL+VHeQkOUMuxbndkQ/lTDVfzfTn+zG/OdQBZwFsziGLSEojvZHfCIwq4PjGxu+MqcZsY6Vx0HhivDLmmm/Nwha1yljHrNP4hU+tBDQJLU5b0Hk0ml6lD4HIknZbe6i9wl5nn7ev2pWcKCeGv/t6R7yTXjycw3fA1wS2CByVjmfiETwnz8sLcsIp97jkRXkkL8MrYAujeC1elzfkTXlL3oZ34F14D96H9+eD+TA+ko8Br03hM7CpC3g0X8ZX8XV8I9/Kd/DdfD8/zI9jd8/zn3lsUUAYoqL4VjQUQzCTZWKNOCnOizvivQjJePIJtjiW5npfRapvVUPVRfVS9f2mfnt/oEb1Pr9kMBEYXhT8moO/+orb0qQi6Ux6QhdHkZZGO0xqmLnZ3GEmsVZY6/RcImhuGscui93s5axw1jkJ3fRg76JuKbeB28EdAEX7PdjpinvLLe1V8Np7Xb213ibvCXD7ixeHJWdpWSGwVAlgtir7DTDbmw1gU8FZ69hmdoydYffZE5aQJ+URgkDbiooGoqPoLgaKKeIwfuNb8VkkkJGyHE6+u/xOjpZz5e/B8pvlCXkOPP9ZJlEZVIQqoaaqWepHdUc9UHX9Hf5e/6x/2X/jpw7MwMP+hsaAs4CN+CSctCYdSX8yhMwCax3CzpY1KhsNjGZGF+OSccP4ZISZmczsJjW5+Ruzs9nTnGR+MnNYha3e1mDrqnXbSgtWH0Qv06x2LrukXd5uav9WM/o8Oxqcvse+awuntFMde9HN6YOtWOscdc47V5xCbhW3tTvBneLOcOe4c6H4sVlJrXddWC82CniKZivYdrabPWW/6Jnk4gXA5ZFAyxJgYy+/xNOKzKKEKCeait+KCWIaWGyf+EXEkYZ0ZW/sQzrVWCX0s/t5ce6T/A3+Vv+g3zHoHgwJfhfMDxYHCBdCW/U/vhSPZCd5cf4dSBc4oz6YyGCgYCQZQyaQKWQGmaMZLYd5y6SWY/dzh7hT3dluC5aA4x8qEDlFflFclAEem4s=
*/