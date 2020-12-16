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
# ifndef BOOST_PREPROCESSOR_ARRAY_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_ARRAY_POP_FRONT_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/repetition/enum.hpp>
# include <boost/preprocessor/repetition/deduce_z.hpp>
#
# /* BOOST_PP_ARRAY_POP_FRONT */
#
# define BOOST_PP_ARRAY_POP_FRONT(array) BOOST_PP_ARRAY_POP_FRONT_Z(BOOST_PP_DEDUCE_Z(), array)
#
# /* BOOST_PP_ARRAY_POP_FRONT_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_POP_FRONT_Z(z, array) BOOST_PP_ARRAY_POP_FRONT_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# else
#    define BOOST_PP_ARRAY_POP_FRONT_Z(z, array) BOOST_PP_ARRAY_POP_FRONT_Z_D(z, array)
#    define BOOST_PP_ARRAY_POP_FRONT_Z_D(z, array) BOOST_PP_ARRAY_POP_FRONT_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# endif
#
# define BOOST_PP_ARRAY_POP_FRONT_I(z, size, array) (BOOST_PP_DEC(size), (BOOST_PP_ENUM_ ## z(BOOST_PP_DEC(size), BOOST_PP_ARRAY_POP_FRONT_M, array)))
# define BOOST_PP_ARRAY_POP_FRONT_M(z, n, data) BOOST_PP_ARRAY_ELEM(BOOST_PP_INC(n), data)
#
# endif

/* pop_front.hpp
em3huB1/6xE/XeK3IzqeUn/zaj9A1o69GT5PV3enY6p/OZGulNFNpKI2jr3vfFYtT5WmlbGq4oe542ol9y4lN/oC8z25o/QmsPvcCOnpKuJfQnNF9YR5vbueQ9wIHU2S7UYT2ShVxXgmTnOR6wZHY5k6mmrP5upWun9prsj/TjJjjneUC+ObX7NsktSaT9ig+o/LsTb3BpKtMCt3ja2E5h3fyOdtppsbbVzFSEV3Sk5Db+7kkHJZyXg07da3bN3K/6TyeqiSBKXa3Mx0+qYpdHoBdLq7aJ0WyGkxip1U4oLnoaJZFWUnTU3pCkCxkonBXTq5AjjiRutsug/zZpsvts5GuqmgGezzCEdGMZwYyWfc+I6WoYTq4lu4PvZThq7J8jMeo/mSnYHcJFbm6W2T5OntAXnqQp7O53n6N+SYjj/ZqapgNOdWvv9wfdgQPVHbkbH9C6aw/dNh++8s2vZ9uSnS5l2prt5/nf033LCW0ejtXVPoLQO9XbS/epuOK0aZfmMa+gv0Mf8VPU7u34x+90yh34ug33cXrd/AVKel50kk1/2jw9l99Kv8Y82+TpqJjm6KtLSZoSaHqPkhjAsvrdX01Csf0v3W9fBLl4k9M3p/Q4JmqKLj6P9slUCtT35mrNqhfhTSuT2sOKW3taNPa+bNQk5WzSE7KvzeWvMGnKPm43X/6womR52zLKo2T7fFyQ8m0jRHvYz6brTJcwMd889GGxq1WFPQkJRcxtppynhlgIzvZzIum0LGNUXIuEbI6ExTxg8yGddCxqt85SmS1zIJGObWlH3I9xDmTlOejwTo7Gomz6LJdbb6uKl1tvo4obOqacr4sQAZP85kXDxFua6eWsaG1STjdGQamz9Rpk8ymWqnkKm+CJnqC8/D9tHaCp2t136Dzqn2YoJlAtjOW10DW6lEHq9la24b4Fc+zeQPTTONdt/8XYu6V1TvBVewa1habF8LzWaPsn0trek8HclehbnDz6oyL8JXrnVCAfrJ5oZo76BduaWI22yomZDueLCpcNyBGN0eTyvXOqoJIKbW5/UYI5vfF7A5wRvYnjaF+zz2tH3B2/tGcbwzvjepOV4Wf2+B+F9EfDNvfTbeo5hIW+rcAlqJ4/vnlqr9c5TgjQRXf29WMhH8Vuyj+5KZZ0daxEvLTR8aWXpzsFA6rK8NHVEeXbqv13I6o5dAnM1zJWS9DbJ+w+goxOm9MxVq75gzj+5bUPFJz4eQVX2ZftuCpfJX/f+v6r4Rtfvu3DJ/+I6afWrSY0k6i3FAydeI7hwTWfOj9xEJlkoTCdXcVzuK3wxNF3V7BdEdw3qnc3SQ8NHBZCpLQww33bkltxMddm/GB9viyTaiUbhZSlvOVmWbJN3y0jtA9y36W16Eba6d1KZ1ryAxhJgmaOJuLhw3Sr2I8Wgml0tEUwOnxwfdxCdAvbqlyua7JDN93FasPRCc6g9+i/pzF7N/hbsT9v99Vn8IbuvPD0X9ubtA/B/p+AIn6wvs7Aews3tQJ+6VPANsnODWxn9Sy+mM7MG4Hwkb/ynSvt/aOOiFjV8FG/+Oju/a8/eKsGe1D/bHmk4WKvEgW79P2foEJM79SpsnW/55sC1rezqQbPgX3Ib30542TG7Xfl/vg1ge2lYeYHb3gLC7X7EyVrgHYTcPMbsjuLW73wi7+22B+A8jvsBZX8zt7tco+9/BB/9e8gywO4Jbu3u0ltMZ2YNxDwu7ewxpP27tDvTC7i6XvpXs6Q/026d22NIj8JsMoe3ojwG+85EifeefCtjbBtjbE9ze9sNGvsXmvD/nrUXTb6/snxJl/zQrJ0W3D2X/F8gicbKNlvG+Uggn2291Jgq28gz+Pou/f6s=
*/