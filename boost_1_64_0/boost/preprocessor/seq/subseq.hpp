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
S9tG15amjZ4tLRsdWxo2+rW0a3Rradbo1dKq0amlUePFyIeZjpX0niItcDXAaX+r+U3rW4p0J3p0T9xQE54WvFRo2u9oKQVcthIaSiU+F6/F5+ML6Ccr8bX4evxQ3Kc3yjqdLtzrlN4ju97JoJeMokXn9brMtFNCh644c05NLs+ys+KsOetoJD7057YEnSX1lZxESrleMr3K844lCuoj0UVSD4kOkvpHdI/UO6JzpL5RT9JQz2hAjZeMukVjyYK6RPSI1CGiP6Tu0FrSp64QLX019J3elHq4dHDVv6V7q3flpntLSuKSwlUCl/StkrfSNWon+ta2819lbsnbKmvrGCllbK83MqjFo+KvSXgL1hJnwVjiK9hKXAVTwVOG+Al2EjfBTOIlWEmctBcugonEQ7CQOAgGEv/APuIemEe8A+uIc2Ac8Q1sI66BacQzsIw4BoYRv8Au4haYRbwCqxwDpxzNHuITa8AZYgz4QmwBV4gp4AlYoiR2gBvEDPCCWAFOECPAB2IDuEBMAA+IBeAAMQD4F/rBvpAP7kG9j3uiTcmjbpBug/N+UJ4G4yMgPAe+JyIFkF0G11VQXQfTSz/DtBDNNpKSJ5oG0yNgOmfndWUWwXQZTFfBdF2ZzhU2knU2Eh+o7gDV3aDaBtX9oDoNqkdAdS6aB9NFMF0G01UwXQfTS2C6AaY3wXQzmO4A091g2gbT/UoSjIDoHIieANHFWPl33kdd3hKu8/HJLWPbcJzjju98YvJPYTyfnPxdnK8nDx0PrC+c6NvYItYLxvQf4r0r0POHmK8E5v61uDcsW4mGoS1pBg1r40/oBsfnDnH1hGO5RZYiq1vQFX52kxyDvpCFB8a3dJv8nRrDP3mj1OGA9T91mWzlKjmCwkDW/ETf1Alb1RhQC4+LzvBf0AnBPZgfBfN5MF8A8yUwXwHzNTC/AOZXwPw6mPeBeekOYB7lgVnfz6xPM+tHQHwexBeZ9WVmfVX5mT+aznj0bjXZV4bdqmZN2vcS7NaA3TZht2bYrQN24ycFoY6dEkrZwIVUtnChlU1ciGUbF2rZyI8Kt3+ueXl0+/qx7+pgWTMdPGuug2l3tgvX8/8Yrv8J7eEIKE+d5Kv9azG+FXz/Fdj+r8x03///jvHf91BLAwQUAAAACADjrrxKcnyiGw8rCQAAECUADwAAAGJpbi9vcGVuc3NsLnBkYuxdCXhU1RW+s4SshEzIRqQ0ICoCiUlIQqCghCTISDaTAAGj42TmJRmdzAwzkwiCChUUK1hEVOqKCqigFbeKVVsXWjeqSGmrVi0K7lQBEVAR+t/z7lsymQAu/bp873wc/vfOPffec8/d73svU+1xBf0hf2s4p/y08hEjcqobJuWMzsvP75uQXdHAQCmMmQFn47+qREZUa2YGGWSQQQYZZJBBBhlkkEEGGWTQ/xA9feiIQQYZZJBBBhlkkEEGGWSQQQYZ9H9OpRb2I9ERgwwyyCCDDDLIIIMMMsgggwwy6L+UEl8qMJXSe/6ctZ28ldCi3keij1lSzek83OEKhh3OYFuXw+fn2Nkh+cIh9sXePTzcpAvv9EmzA06fW3L31DPr9KJo7SlhsTw3c1jYqml3+N0SyzujbHpRd9mECTztPNVOnzPs6ZI0u1z+Dqbk3eH0OdskN+6DlE8c5WPm+Ti6XA5nOBz0tHSGpdDYsVIXDHKE/J1Bl1SmyMeODc8JSA5hh3w9IarmhIgEYeWebNXGUECCFbJ9Ic/FEttzMewxC3us38EefyDs6UAKik3i/jvZdQGLSWdsfrevPY7XAp7r1OPNCXWSAG/3QfkSFoKZKdWEnCy4z2bxKdwzPCwWnGg2sTjRTvtAj2NPHaQ=
*/