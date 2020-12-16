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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_TRAILING */
#
# if 0
#    define BOOST_PP_ENUM_TRAILING(count, macro, data)
# endif
#
# define BOOST_PP_ENUM_TRAILING BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_1(c, m, d) BOOST_PP_REPEAT_1(c, BOOST_PP_ENUM_TRAILING_M_1, (m, d))
#    define BOOST_PP_ENUM_TRAILING_2(c, m, d) BOOST_PP_REPEAT_2(c, BOOST_PP_ENUM_TRAILING_M_2, (m, d))
#    define BOOST_PP_ENUM_TRAILING_3(c, m, d) BOOST_PP_REPEAT_3(c, BOOST_PP_ENUM_TRAILING_M_3, (m, d))
# else
#    define BOOST_PP_ENUM_TRAILING_1(c, m, d) BOOST_PP_ENUM_TRAILING_1_I(c, m, d)
#    define BOOST_PP_ENUM_TRAILING_2(c, m, d) BOOST_PP_ENUM_TRAILING_2_I(c, m, d)
#    define BOOST_PP_ENUM_TRAILING_3(c, m, d) BOOST_PP_ENUM_TRAILING_3_I(c, m, d)
#    define BOOST_PP_ENUM_TRAILING_1_I(c, m, d) BOOST_PP_REPEAT_1(c, BOOST_PP_ENUM_TRAILING_M_1, (m, d))
#    define BOOST_PP_ENUM_TRAILING_2_I(c, m, d) BOOST_PP_REPEAT_2(c, BOOST_PP_ENUM_TRAILING_M_2, (m, d))
#    define BOOST_PP_ENUM_TRAILING_3_I(c, m, d) BOOST_PP_REPEAT_3(c, BOOST_PP_ENUM_TRAILING_M_3, (m, d))
# endif
#
# define BOOST_PP_ENUM_TRAILING_4(c, m, d) BOOST_PP_ERROR(0x0003)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_TRAILING_M_1(z, n, md) BOOST_PP_ENUM_TRAILING_M_1_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_TRAILING_M_2(z, n, md) BOOST_PP_ENUM_TRAILING_M_2_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_TRAILING_M_3(z, n, md) BOOST_PP_ENUM_TRAILING_M_3_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_TRAILING_M_1_IM(z, n, im) BOOST_PP_ENUM_TRAILING_M_1_I(z, n, im)
#    define BOOST_PP_ENUM_TRAILING_M_2_IM(z, n, im) BOOST_PP_ENUM_TRAILING_M_2_I(z, n, im)
#    define BOOST_PP_ENUM_TRAILING_M_3_IM(z, n, im) BOOST_PP_ENUM_TRAILING_M_3_I(z, n, im)
# else
#    define BOOST_PP_ENUM_TRAILING_M_1(z, n, md) BOOST_PP_ENUM_TRAILING_M_1_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_TRAILING_M_2(z, n, md) BOOST_PP_ENUM_TRAILING_M_2_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_TRAILING_M_3(z, n, md) BOOST_PP_ENUM_TRAILING_M_3_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
# endif
#
# define BOOST_PP_ENUM_TRAILING_M_1_I(z, n, m, d) , m(z, n, d)
# define BOOST_PP_ENUM_TRAILING_M_2_I(z, n, m, d) , m(z, n, d)
# define BOOST_PP_ENUM_TRAILING_M_3_I(z, n, m, d) , m(z, n, d)
#
# endif

/* enum_trailing.hpp
POMCt9J1tHJRNWUg1z5pac+km9o7J5Gak4zqTuqYOmnqJFPcY3OdXqFxbN5NXYZqnsIFriHLncqFIMlP4YpdnjqVO1rve0y9eSpb9kTUqXxa1tvewaboU9iIIxyb21wKbfzX/w1y373fqjL0JLAf+igYDF0DjkOP3VdFrcitPWAc9ASQp9+5BxOhm4C8fj8POgeGOb4Peh3Ih86BDdBbwWmO3w69/StVarhzfx/8MVAgb+5Dj/12FfPB1n4xdBMohO4BzdCNDZkkTuvgt4PTnflO6MNgpOOPRvbHPlalpoFRji+Hjv+aDlapZtALVoH1YBPYAfaAA+AIOAYGSs+N3yH9HL8Zeg/Q6dej4wt9CAx1/BHoov02/Xp0+KCP77bpM0mHD74D5Dt+BfRWcJrjd0IfAgUSX+ii75J+4h70DFDo0rMOug9Ieq2A3gQkvbZA7wajHL8X+gAogm4Fh7Rbj1epM5z5GOhpYLTjy6A7wJkuf3uhV4IxLrxroLV+neXMt8Nr/Trb6ddBePW9Kmp+ZgdBPvR4MNa5PxG6FjzDudcIvQKc6/hV0OvBMx2/CXoHGOf43dBHwHmOPwadf6BKne/4MdB14AKXXk3QfaDY8LgPvQlc6Pgt0HvBRZL/0Or7VbTvNn750NPAeMMD6F7wbMevgN4ALnbx2wR9CFwi+al/+wPSyNmfCD0fPMeZt0GvA5c6/zdC7wDPdea7oE+AiY7P/yFpASY5fgJ0Dkx2/Ero3WCK4w9CT0DPBzu+BDr+i/V/3B+8fhZDzzuKfjp+hubBCMfPh+4DeYbHf+g1YKjj10FvBMOkPEFvA1I+tkMfAFI+DkLHf3WU/0Hi3x+rUvyqiN8Gf7L6cZHWH8yPgSGOPwGNPhN+mz8T/mT1eajT52nw5UDCPwO6CQyX8ECvAPkSHuh1QNJvE/ReUCDhgT4KJP2OQxcdp0wa3v4Vw59uwmP/SuBHOvMy6DowKrA/D74o4Nvgzwj4PvjRAb8a/syAXwc/JuA3wp8V8Nvhzw74vfDnBPxB+LGOP6zj8mdXvqXOhpfyPR66ETxT0g96FZDyvQZ6B5DyvQv6MDhfyjt0/pOUbynv0NNBseMz0M3gQsd3QK8GUr7XQm8FzwrCtwt+fMDvg3+24w9AHwv4E9CFf6G8i//QE8Eljp8GndNtruPb4LeA50h8oA8CKe9Kxwn+uQFfeMKW9xrtPvQEMMnpwzToWjDZ8Y3QOUB5N+iDXg+miv5B7wUlUr6gx/+1SpVKfQQ9HzxPwgu9BUyD7pH8h39+wO+Cvyzg98G/IOAPwZdJ+wit25sXBu1N8d+q1IscPx66BLxY2h/oGWC64+ugm8BLHD8fug9c7sK/EnoTeKkrr1u1+Xcps87+bvgToMLxeU/Z9rDStYfT4OeDKqmPodeCTBCfzfDVAV+/hzI83KbXDsx0+/sNeNM/gFf8+puOz4ceD77l+BLoWrAPvlOXXegc+LXjV0BvBN+Gn6X9ht4JHnO/3wt9GHzH8cehCwdl1H7Hj4WeBr7rwpeB7gCPGx73odeA7zl+PfQOcMDxe6APg+8bHvehxw7OqB84fgJ0I/ih4+dDrwYHHb8Oeif4kbgHfQL82PGFQzJqIviJ48ugZ4BDjm+CXgF+6vg10FvAzyS9oQ+CnzueG2K4z4UwO34sdC34hbgH3Qt+aXluYCC+4FdBeuyBP+L4A9BqaEY94fgx0GWgRuoX6HngCikv0CvBDKm/oDeBmY7fCq3b3yud/uwZmnna9jfsz28ZkUn153fD6/Yrz5kfgg/aKxI4Y/R7mJhD079L+uvFmJcDaa9mQDcBaa+aoVcAaa9WQ1OfJfX9RvitQNqvHdCZw5Q=
*/