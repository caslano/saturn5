# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
# define BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_OVERLOAD */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_OVERLOAD(prefix, ...) BOOST_PP_CAT(prefix, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
# endif

/* overload.hpp
gT0EwXRxKmBVCRCudK5uLk15ON2/FC1orecbKJX+GOQaJegTuYpTDqhvczHziEc2r5yOwV3bd0cvo43D/QGvDQqD3KsjX9/YO7HC2TJtbBqhPgwnbklvnOqEtiyg7x8v2UqsQ4lL00tacxds9DsTFzN46wGk0urcepA+fvfWQ/wFIYDpAHjJoRcvP942+mxO1Pj8TVBweixsPAYULeKbaQDLRg18OHIYRUAOjRr8qBFYhvV7OTHXgvYmXsMcoWcocLQfSeogAJYhQqPXuh2xI/NxrEB+WzfUd5EnRwO71ffLmPErjyirtJnnyJvq5Gfcg/DGO0Eb/x/Gm8q4HZLI1hY7PVsflvcZYEC/a+qc7L0thIUKypfumc/Kl5bjw69DQ4Hju3KZkT9/7l6aMA7JlHwfcjiZqJ4RwNloBYAw0YY3VvVCt301i1cQNOT23UHCVpZ8YX3PZdtrgl8Cv4l9wyxI7y4l3eaR22jTN7exi28RNPFn+J7WNa4P8qVO29fTtQ0oIpaAjAC9rACNa53w+yvs2/d9mWp4N/yE4uznOMDvv/D67t0QpYgHvlxmZ1OcaV8uDqEi2w/qAtZ88fJtpniHvkxe0YXb3/xS4cu277j0S4SPzededsd6gRix22EOVbM3c7p2N02B6OumZ57lKbMl+rTpk22NsPkkbtgLE+rsuaDRz/M7psD0gLka7iX4pvD1w1yHMI4en/lzunr0yCKLO7tHTo8euZ7/5a/lNbBOpF0x2kk8sjoYQZv/vYhXB5YkIdxQAtxlBzgoAZ5Rv5riaJqIX9R6aPNad7Q/EKmn7XCPFmlEykOI1J9RV0Gb2ihB2P7Tn9CfXr+gC/2JMLuFJJWa9Ww2vOMfNhMVZx+Nr/XHZyPT6IXQSsLzwVJN0rTWMyox00XycEZvPqInDOcSa394blLWgaZPBt+aXfV774xP4tN9WGtBxngsnjUxQAkWSM23hawa/XGI1KgKM7fS6dD0o/jkvN8cQKD4OEJe1fpTFDs2kGM3mNKlEpN5kCJM3YrgYv+FOobuAWOCY/0pqgWEvwnnIEXnRaNIBGMk6K19R/52Yw7tWbVj0qjZhwTqooJldnHfrJdTPZBO3xFw9Gu6xTMqev4eV9EkvEWCJSf+L9R9ZIeJD3oSNdj/cnj/i7+QuMFK6bdZL8d3IRoy8I3c2dQ5eM058Z175PRiS1djsYzMJDyNqpBbJzcI6Zk3TWygekEhUj4iKLvV7h8s1Pt2HzVc80u4FsBOtVhTIQ+dLyQ7dT463Do/3bcGMWHxMOnuvlVwpcv2Zjfiy7Tx8+9iKXO6is4Z9zxter02A0IE083Se/0m8qjIa6wAsvZb8Y7XcR/viL3JYxA0D1s+egnKkXAXB/g4NFCmOkK6Lm+nbTXuLm518py9vF3Cj0d4oiyeXwZUJZx+PV4CM4+ERffCW9PW8VDcAaAtjHfSKoDCxCaAYDZ+fRp/66Ke9WnCD2O5QLIrhkaHABPISb9eWRHrj9CFrRXp1xfMby3hfFlyWUZkxWyrbesHcdtKuHE7KJDgA9nD/wc+cMKeqFmD9IzPbI8Q4VO9qMG3UuuHwnuzCe+gv3h5S/wUKLg5RMG9vL3xwlGxj/zxPa0cevuJ2V/49YfoM3XByETE9045BuprYnI6eB8hI8wxJ0JBrRMpV3odBKTVqeKKc++zhsYKole++N8pXHZ2w6wB8OJWGS7yIlC8xt06aBMAEKVBf0/30AX/MhcdKEZB8zEs6JiyeH+rNeLVmwHpg/WO27KkARcmCxFskhSwlUMm/C83ddbhGTYXo08HlzD69AQ+YdX5uMnh0dqfH/+laJJYPSXWD8Dt815FI+z9oviQd8M=
*/