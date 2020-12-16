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
# ifndef BOOST_PREPROCESSOR_SEQ_REST_N_HPP
# define BOOST_PREPROCESSOR_SEQ_REST_N_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
# include <boost/preprocessor/seq/detail/is_empty.hpp>
# include <boost/preprocessor/seq/detail/split.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SEQ_REST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REST_N(n, seq) BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq))
# else
#    define BOOST_PP_SEQ_REST_N(n, seq) BOOST_PP_SEQ_REST_N_I(n, seq)
#    define BOOST_PP_SEQ_REST_N_I(n, seq) BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq))
# endif
#
#    define BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, size) \
        BOOST_PP_EXPR_IIF \
            ( \
            BOOST_PP_BITAND \
                ( \
                BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size), \
                BOOST_PP_NOT_EQUAL(n,size) \
                ), \
            BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SEQ_SPLIT(BOOST_PP_INC(n), BOOST_PP_IDENTITY( (nil) seq )))() \
            ) \
/**/
#
# endif

/* rest_n.hpp
3wFA6TiykuwiB8gxcg5O4y55S+IaMapbwCCGb5RHI9IIPnawMV43ngvBk8eNsxqlz5FbhJupoRdtzO/NkciclwGXu82D5knznHkDvjZkJbLSW7mtAsBmKShJfautfnc3EchciWbsqHUaGnzdeqT7gYw0Gy1Ii9HStAq6sZH6nczqr6g8B697F243LtQ5l13AJmDNcnZ1uzGagZHgzKngzLVoB07q7wBuA5dJndRgzVwOcUo65eF9WzvjtevbCNU5A9256dxznjshNwkcUwQwabgB9DzKbYL28gd3vDvNXQrG3K2TzmvuHbhj8KVGpeGV8ip4NaBUE7yp4M1NUPoT0Pqr3i2k4Z/gHlOxTCwv3oMIVlq/tm2nv3OZxH4PTO7Qr+kvgTkfA5EpeCaeHcxZnJdB4tYSPnMi8LieH0UXehFovMef8zA0nxlEPuEgbysLNDYQ7dDzTYRHmCfWiq3isLgkboh74jGyt3RAY15ZWDJZCWisJ7sAibPkArldI/EymPNncGcclQLpsqmbsvLqN3B/7VVfNRVIXKR+BBKPq2vqjnoILH5WmfzsfkxjpPxqyMoaIR+bAxQuRXJzzb8Dh/gCOIyFpCsLOg2CHqkYeLMOuqPOwcBgZjAfursFnvG0TjOfBq+DEP4XO1QUWIwFV5hbtxzFwJp14U/6kAX6m78D5BK5ASw+IS/JZxJuZDByGgWR8yvg8Te4WbU3+mo0LoJm7wAer8EJPgQePxuZvqZoyqyGrL+R2QMseda8bz7Rd6yYpLQI8jRllYCG/8aqBzz2RJ623FprbUJ/vwf5zzl09h+szPA1eWld3dH2pYOAxVn09+DIPUDiXbRSL6DgMdlPGSCwpd3O7gqGHAgkzkRrsB4+54R9Fih8A68TjqytiOODHcs59bVyf48kZIr+Tmqrc8pJDqTNdRe5y4C2Teis9kChr7tP4Inie6m89F4ecGAAvNXzOmtXNAqom+9Fw1/u9PYCd4+8j14YS8BSgv+GspFsMpvHNuPF/B40qSfZBWR399l7KHRyHgGcmbworwjuawL/P1RjbS60egPYbx8Qd4HfhlInFz6aiilQ4mwytywoKdBUVJaUlfGeu53sgQRqAlD1e7kBd+bD8grwFKYSqCQqFVr3vPCkxbQat0H3OlANU+PVTp3+pQWOuB/4Jf2KQFJtvz4S155IqMYCT8uRBO7QL8ZuIUGNp982ZQvyBE4ggtLoyGoDT/2DsVDfK8FjdBqxQ7fha/MQkwwmE8hpaOtj8oq8JyEjhrsijMLASmkwV22jhdHN6KdvDGuNn4z9Xzuh+8Yr6Gs8MzmwIswa5kRzmjkH/e5yZF+bzF3mafOm+cj8aCawvrEyWnktw/KtyvB8Hb664LHWJGseGGwdOOwS2Cs9teCBu9OBdDhwkgWa2VpnrkPtsVDLZdDLy/ZN+7H9Dl1DGmhlQaemM9B57Xx04rkF3LJoGhq7raCGXd1e8GoT3fnIx7bCqx11L0MPX7hf3GTgHdsTUMPS0MM6Xgt45J7o0md4q73LSPK/eMlZRlYAjFMeTVxr1hepyxJ4tJ3sELuIZP+lft0PlwYUFEFiUgsuuj3vywfz0XDTC/mP/Bi/wu/yZ/wbKF8WYYJrSogyooaoL1qKqWK2iC0TyHQyu+aWKrI2lK452KUv2o318N3PZMzZc33yHdCJDlBDkd3PQud+BiySzC+Bxqcy2KMtMvWp8FyLkKRv9w/653T6Gx6kR/MRCc/VNpgURAf6A3Xdg+Ylikwnx8npv3sPTmWkN4qj88tnFjGL4UbczZwABYpCF9Lj61vXB9YzZAHVaW10zXv+brf8jn6C34ljU4ejax/gTESffNl56mQ=
*/