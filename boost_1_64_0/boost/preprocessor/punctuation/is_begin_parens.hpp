# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP
# define BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP

# include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/preprocessor/punctuation/detail/is_begin_parens.hpp>

#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BOOST_PP_IS_BEGIN_PARENS(param) \
    BOOST_PP_DETAIL_IBP_SPLIT \
      ( \
      0, \
      BOOST_PP_DETAIL_IBP_CAT \
        ( \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_, \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_C param \
        ) \
      ) \
/**/

#else

#define BOOST_PP_IS_BEGIN_PARENS(...) \
    BOOST_PP_DETAIL_IBP_SPLIT \
      ( \
      0, \
      BOOST_PP_DETAIL_IBP_CAT \
        ( \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_, \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_C __VA_ARGS__ \
        ) \
      ) \
/**/

#endif /* BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP */

/* is_begin_parens.hpp
pR9vfK42m7T/wcZe/1Tko1V0DkcP38ckK8Bq/NFxz/ttXHboFT/LRTgHm8QePuYAT8+Up2fmyskHL6BTVMzic9DBgGnSaOFeZ2X7ExmtcK7UDVcJNuzQKKPb3d7VlXjKlO5F10wV7+8lluMP5e9yuodOyiVE9puDjD9+37SV3h0l7JWwj+qG55Y9o75FrAMmw1owFNgnRyRazrqZp4cFbjsXRi/p172ofw0o+vV7RXrpDNYjA84GOcjC2EO33BK+ZJ1Kgz80wGL9HoK/J30xysbYgR69hh6YyRYn0lhhFG74HVWZFn23qr3b2tVWfS7ROcTDlrKIfUPTOXBMkzZw3O+mD9hZVMdulnZ9k+RHYZDV6Dho3VVuLHESl8w6xLi0tcyOnc2Txll5vjR12ne1Nuw8q6uJlIYFs07X/BQQ06ze7V217b4ucaKYnF0/MHf2+nH3XqnNzPXTD6TTbJVUIewx0+XKEHrQZPicGZbbrRDGbSO7l6IoxymLOuOG6Clrdv/CWlUYpBp741F2Hl+2YoLC/R/Y5nwWUB0K/U6cj75ZWpRv7xz5Rl7ewnpKyznzK2yoRtShda4SBqNw2GWRja2EG3fHXRL1mA2VY5SwIjnhlenqLtXfoIsQiaw6gssWlAzYqV1D35VHrQqVngd3auRxE2rCK4xJtrnA+9N+CYg90W8d6f2YgfwckeR5ejW8eI/etMLp5iA9/xtsXGa8YIkuO+KM0cUzcREg2m6FdQTrr+nJ8YXJib47Dp148OGG85hIE4FvA9VOYKOFKx1a+roUUS0cNh5xNTFY3p96r13B8jWB5dfLHF/Srs9MzVBJ1xUCPwfTPdPGanUpqjpp2XCObmUlpb/E7kNcX4lZmhgOgfJuT4w6LJocmCbC7nTAIZ8dO3V26uzCQ6CpxelhXG6cg2UaK3yncwtnSv/idw/ZTHBzzB4c0W1ud8PHyUOiIHr0yBEdLy8OPnppWbRXtDrnjxhB95DRnzxkTqO2yjspU4pvJk8eYoV2CHkwLyz3IiKdnO2sjdpgMwp6lKh1zQuZ7MFyP7e7hB8Ou/7zeI6QNlUXAdMjtj1Z5biJEcyDaHtXROkEVl/9drlUDvwzS5A6x+3rb1QiSO2HPC7aNooBsQCurF9Kn7uzzMWxHaUq3y3I1C3y+jzOKMuooq6p96qVEE1m8zUftqoykhXjJP5OTZ2dPzM5wZ13To5TPuGSHVvKeFAtAWQZabIzpXbShbP3n5w5t1C2VlZ2KcbVKOf4oPLU1Mz4/Rr+PZZ9z2XfD66+u+u7O3K+6WGlo8LEzPSk4LXPeZD+/aDsey77jlGkZTA+NTM/OVGeekhpC+tKtjMdjPRKDC9zk9OT95lZODu2gMUh8HLjfbyHgO8dR1ZLF7osy3LDXo2+8HrMxK38TnkiX62+tvfKZkU9JSENYyobKogem3PGI2ULEJjQTrcOotGLuFVaZc/tMim05w0ZzcGZQhBtneGoym0KiCf3Oz8Vr/XwZrb9GbYrqVcc3a5/gnb/c3BopIt6WrjpwYfJhJmcm65uoffyTGS8cTJh3UTejEZX4/Sfnb9jwh9RuvF4QqE5CnIDS9sJZjq9UzBq21yhk1VLgi8oZ0V5lBKFroomfR2QOPX7Wsnq/H6ZjIFKJARFUiW/KRFXGI17e8W5RaSNWI7NSubBaHRsCGFkcej4UrNMBoa2519Vw3CEsWXiZcbGycv6aXpPXtavoef4dpTuZ+epjA4tLMrokFZpz1GHcQ97tX1jwoicOKM8+Gk/B/Ggk7MZBK5oYFtysaM6m1pRzca6ofNDKWG8V4Rl3+T44YkztDxj3j/ucY9zu266di0PiWWvI4eC+Iqf8bY=
*/