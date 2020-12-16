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
# /* Revised by Edward Diener (2015) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IDENTITY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IDENTITY_HPP
#
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_IDENTITY */
#
# define BOOST_PP_IDENTITY(item) item BOOST_PP_EMPTY
#
# define BOOST_PP_IDENTITY_N(item,n) item BOOST_PP_TUPLE_EAT_N(n)
#
# endif

/* identity.hpp
0VrfW2rdxM51ic9pQdUsUH3pfLsfPmrQEvuOuVPLQqbcRKWMsE7jvkE1falQUvJBD2shgjw1s5fyYRkx76Y5TsEk+O4+0psvqQZaJbj9+/CuMRajnuCnT5+CfuG4aghHvHzK+cDg1YvCESebJOHjJF5nr3x+OqRlHjzXjqwxlnMyH53iZDrDzJTXh1N60E5ptFSkBAgI+ZVCq+I1Wlwk5dOI5ieLGZLVQZVwxuYTcSv+YibCW/XB2jHxlzIhCfeYps7pa8+MA6/SXfULJBMEp901mpuPxmgDr+NB9W3OIi+rIzWRYoAjcgNK752yN9Bg3MPdHltsydplrelLRUVaneY+HY2M+5jSM15y6M2jgdM0fme6w1Cc3QwIPR9DbRbJY3mQLTzQS3VH33EeKHo4KPXWgj0Oqbn5KH/KTV0pHMiU+B/szEaQ+49WZuClkq0DzSzXhnnt+PIwZQfGZ0e3+z4PPNXHN2eul27qHb1sbuI32UKGAsIVmKmO1JoCH4vqmBPp9KbO9Joe2KoMcBdGL1TTGBxLhjHIA8DPBHmFnlVZH2kT98w09o2nHj7gMGlBV0xNJuDgXFTrJKGB7JiP3N2y4F50M61GHlqNusiLvHa1ffrICO6zg9OAxcArAkfUAhefpBg1kgVyEjBoWlED4CGyrh7Wc5rFglkTdbyeNEvtXYDkKcX5tP6vNtPvft5Banmii8kXSQsv+inrnP00HzcLM+O0FTH/32otr1Oyjbm8qy3OPnERRbhMpHa0KEuRyegMe6kKTdasd7C/UMsds0z0ReMuMXdlmHizi/wONb1a2K5TU9RksfpSE0j+v5rl/0dbnNCpYjUUsLhKncnto8ovpRCDq63bt8eZV5fzin1XxepZXGb+JSwuE11KMyWzn0ZdJVvOWq4h1UH9qEaTuoLqO/ANqV/hN6xuiWgWzb7DSFqXRkXLBcLgq6oQQjQS6uFd1B4vYy3jwkyMmuz/5JRmXB7WRf/VQv0wv3Z/9SrBoJqMbL7/C6ngiVO2HN+16DIhJAaVK2Irscw1alGW1MNB9S4SjDg5Nh3ioCT+zpOcs8kxtNfhQICgquoAmJoMSgOOdFUaULDQVBpwhB7n6fPBqa78EZ0LyJ9Xbd7Tw+roUs1i8BIsAcO4wAq7H2HDahfAck9Bj3KVIUEW7IeR2jCxLKRu4GDMlHRYXzckV1gC3Xz9N53L5k4uABgAXzIEC2TWfjXYz+YAzGUwc2AWwayG+RpMWynvfyv0eG6T8VyPTVCkccWVJt2RrVhUMaZxtoOrAqYcphSmGqbGvJFWN9do2QM6pKrDfrknv8yWP8jz3jZWmEvvKfZb+jEWVbL+70q9xCR7IIiaXqnV1DnJVSOuElbjTe3FUd4r1bMAjUJLa9NJp3fDY9iKRb8lwuhjld9tcYaeJjKhoiKvgZeWtysQUM4iHsHdRTpYBzQ1VVMO6lcUNqQODErLUFl3jbqfQEHDXWn18HtXWoTqx+fzxps8z8WJNPfFN3G9M3WeJfNbzGIYau1UqpFRYc1a5dQV+gss6oc1csf7K2It/XmtOIj0C5z2iPeudirgz+EM8BoQkXkZOWbOsEDmDDtypfXikNTwG7AEDVVhVeBcDpGXXAwPHhgkiK2+Vy0P81ytWeiLOJMpmMYWrWEqRXiszY814lXDJqU/JJgyS1qE6DFEhkgDFhkldsvNsltuJazJo5qZJ8w4f+oS1XqNGS+X1bel9tCxUgRfB1GZrNnDupnCarEhR7q+JMmwVtKqtTIfbBh25q/NszL/ZB43gPDxX6hTLAij6Llq97Usl/8rfFAnTmSNnchmO5FfSiIm1Sw1yqi3w+2ZKytKQRxzpQvt41E=
*/