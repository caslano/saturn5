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
# ifndef BOOST_PREPROCESSOR_ARRAY_DATA_HPP
# define BOOST_PREPROCESSOR_ARRAY_DATA_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_DATA */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_DATA(array) BOOST_PP_TUPLE_ELEM(2, 1, array)
# else
#    define BOOST_PP_ARRAY_DATA(array) BOOST_PP_ARRAY_DATA_I(array)
#    define BOOST_PP_ARRAY_DATA_I(array) BOOST_PP_ARRAY_DATA_II array
#    define BOOST_PP_ARRAY_DATA_II(size, data) data
# endif
#
# endif

/* data.hpp
5fkbCpv5GMJT/STeBe4XeZhwvLzz7KwPv+/g90Q3SdudSNM6UTQXG0hiaV0Ara98hOnlUejlw7DXr2L9q4fCHH8awiMVaOsFfpMIN7Pzk5w+A/4PhZ19Sx3un8di2TMcuT5p32p8itvdNPIb3B8BGS2J0v/wcwKGfTZ/QbmfDFmzYS8++Womb2xQvQjCYbSHSC3z6fBfF9rzdjYcVu3NDmefWVt7huVxXpEybp78/H8sO75arFIG4/gd5NkCc1p/F+OHOWH/fUj/QF15b8Ca1yWVfAwjfRPtc0b9yXN6zLnJ+CrOWjH2nFHjp39wLs6vsPEj6IFn50AX+uOW1Xg4iu/xIdxBhDN6ovEb7eWTdZ/6DW788N9Yn+Rgghn/8Vcx5ggTjmD01z8mqqAwP8d9NfR9NfQ91+Ah54jQSRXLx4lz/flYIOKeLsawC7ksyDenl+e/awnfQPjZStaAL8f+5nSeZX5nO4fWeHdqHIE0BB/SE49zgFNHcVZSnANRHsFxgtI70Flag3kmNuf0VXYehfJGvyET5mGOoDi7K71zZ8trmD+HTC8D30dFOR9JcCMTt5eVBDdtBdmglZV0QPblbyuOsuVg6MRcLONF+qCz8PojvuDFzsPXQ84Ps/o6wuflEcYchb2nptTc6SbWcmaE3K8JOqkEjJ/tfCXhgn1Wd0+kS23RGEpkVH9T3XtsXFYwyrZnO9jczdoaLpMry6voIzmkTHYebh3h+dyTXJ8/WM7nsjJQONlnaIFej4MsfM+1E3L7HznxZlAEtGZ97QCG2wgc6jKl6Ze3g8uPtQWE0c+bcj+tfRJL63si2M7nbIEsvB2Q+ulG/gnuoz2B4HJfdC/zUV3C5/QzPROOzfdhzzTB+N6ARpwv2y5kPKbS/Xi6J0PG1wrakyh8CvhSmpr2dUIO8LJyRAnG8yj1ERP2cj/w9FfjB02bwu5XkOeZ44zmz8A3irHNiOBj1n05TSKARvI5g5XJc+Js0xh0Q3AZtvYs+a8R/M9kMjxXYK0nW+O//2owsO8ccvJGt6CrFPuHdzJ/mGA8zLoP9627GO3wFLSvr3HrNa0N2ns6WZ0Qeab7J4l+feE3MOjFi55OOs9rPJ4EWl+3u8bru59b46b9hhJH495dyfbFCp/xFpTTLXOxLxb2/zbQncrnszBXws6SxkaIr8GXOanh4Wzc7Fcm/6fnihLx5FDUvFVn3rEIO+rmCMfOFZ1fw/q408j7rb65HDEnomTUYwLA+V3orK8OmN6/P5bGWzOAhdX4I0e9auoZc9p5TjaeVTyJnMOrHd2Fzhi9KLXW4cytCa8w579Ao+pZvZOO87dnGxl/07bxMcQaldcEzQ7RBrR80ntvYp195yiVzSmlMzmaDS6XoLf76NH9uJIjOsrfq9jEaZgeOp109gySha7LoLtD/HF6fDgvD/1ONpOOqje67fyBnt/eDjtSZU9ylV7Ayv40ve+zj67QUhsxVZHrspdA3/0DZLs+X3QhbPhdrG99Ln6fbfata9qEmrJk9py34YuJvswhE00n6SSAZ/O0B1JtZLdlcbuyEb0f06Mh20iczeZRq/GecxPebt7D8ltb1Fs3qLfoi14i2qb31NAn+nuXQgeX1fC+Ju7nY/5wGdZF3lvID02rPErD72M6v1Kk/X4K87QJ797fyny1kke+zXMVw6s4Ev9h2yZgPTVENAHzYldDJ4TzzaV9TPEMI66YW/m4aZMYXVq0SZ9k8tE8IdH45bumRtyDjX1KK9n9UmeGsQ6z1H/fbR6fHU9T/OtEWZ8n7rUwfVqZ/8/z9rXA3pIvQEcXBdyd2YSP0+9lfYKTwv79NDcTjsvF7wfkct3K6Vg5SLovQ7Y=
*/