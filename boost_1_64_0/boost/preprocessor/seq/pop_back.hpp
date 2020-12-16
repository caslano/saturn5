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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_BACK_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_BACK_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_POP_BACK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_BACK(seq) BOOST_PP_SEQ_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
# else
#    define BOOST_PP_SEQ_POP_BACK(seq) BOOST_PP_SEQ_POP_BACK_I(seq)
#    define BOOST_PP_SEQ_POP_BACK_I(seq) BOOST_PP_SEQ_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
# endif
#
# endif

/* pop_back.hpp
XqI/TmsWMLlRHBdnwavPcGZJZHZsLJdFZWVZQ7aS7aHSh+QJvbWfZWyVVmVWpVQFYLW5uqpuq3fqF1XHb+R3hVJv8v/gn/Iv+C/9936BwAiKBf3wC0Kr4K9xhrEJBWbHkY3kHE4vrVHVSGzmM4uapcxeZn9zmrnCPGGeNd/g1GpaDa2TVgVajbake+wybiW3obsWrFuetWNj2Cb2B1aQm5hvOf4t9u0o/8BDcFk1RB3RWYzEZI+IjyIhfkNFOKxNMlK1UG3VSfVYJfB7+VP8Wf5GzHcHlHK/f9g/7p/2zwNz1/3b/n3/EXzGK/+d/8kPBXGCBEF4kCxIFaQLMsFZ5YSyFAxIQIFMGRQNIoMyQQW4kaigFvxIw6Bp0DJoE3QIugQ9oLz9g8HBsGBkMAYMNyWYASVeEEQHy4JVwbpgY7A12BHsDvYHh4PjwengfHA5uB7cjtnxHb+a66rkN6QxJrWdHCZnyWWy3HhvtDDbmn3NweYUc5a52DxjXjJ/MRNYSazsVl6rlFXBamA1s7oC7cOsUdZ1qzwdQAvZMeq7xxkPD3IVihUXepXBy+YV915DdTOwCGazcqwKawDn1on1AKPP0jg+x64Ay+/hS1LwdNzlpcCJtXkDcN0KaHEYNn6ymCmWgsPiyAQyXCaTqWQ6mUlGyJzATkFJJIW/k8BQpCwD9q8io2QtWVc2lE1lSzlEc8FheVI2UAdUpF/OH415hwXfBDooCz3DHwlIEpJes1ytv4PyMkYTY6ZRzCxtzjSbQfW+s2bDu8WjKaikxaF1J+gjusbeaO+yT9kX7Nt2K6e90wtONqvraQas6v7oHoZ+V4KLf+51ZIPYAnaJhfNkPBX/93VhNXzaTzy+yAH26y0GAHnXRBpZRDaXPeRUuUzulHflVPWNT3zHjxNwIOa3QU8gYR5O/yec9oOY33sd3R7O2yBVSDtsdF/8ziRGKiOfUcSINMppfutl9DcmGtONVcYG45BxwnhtfDSUWdxsZLYwOwELG81t5j3zkZkUKKgKFLSx+luj4WEWQwnOWrfh2ApQTltAI5fRVXQd3Ui30h10N+5Ch+lxepqeBydeh9NJaI+158APrHcSuEm013HdGpjTSTcEL+B6yjsJj5OQJWWtNVoGsSVsG7vMrrPbUINH7Bl7xd6xTyzE4/AE/K+nGfCdcLMP+I/ClkI2kM0wo++0I1gjN8qf4P4fy7fgl0wqGzShrIpSZ9VNdV+9USE/qZ/ez+UX8Zkf+GXhcmPYpoPfDUw5zB+Hff49tvien/qfb9azX3GVkCwnY4ztRjIzjZnXHGQON/9g7sEW5dBbM9XKRQuAdWphWm1pDzoG7mktLWg3srvYY+wJ9hR7hj3HXgC9WGavstcBYVvtHfZuez9873H7tH0e3ve9fdzp5ka7mbzsHoVrOgt3Gw/eLyeLZE3YNDaH7WWH2VWWBNMpz6tCIxbzlXwzzyMKiVKiCvz+c6hnITiCamDY7moYFHK52qoOYCK31HP1CTqRys/qF/SlX9qvhkn084eA00745/zwIEWQIwjg+WNIJAK4CifJSCqSjmQiESQndKMgIWBhj0hSlESSMqQCcBdFGpHepJgx3Nhi7DTOGfHNIdYa67B1Hqr5yHphxafzteM/Qx/Tl/QzTW7ntPPbtTCRSfj99+zWTkdnkDPOWejccRj2q7a70H3k5vBMuMdy3vfeeK8468imAyUvWWHelneGa1oNr3iZv+U1RV14+u3iINQnkcwMNfxWdpIj5WawQ331vfpBzVPRaofarfarw+q4Oq3Oq8vquroNbDxSz9Qr6M8nYCSOn8AP95NhMun8TH6En9PPiwkR4KWZP9Gf7l/y84O56wc=
*/