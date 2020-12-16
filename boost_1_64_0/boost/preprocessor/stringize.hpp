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
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_STRINGIZE_HPP
# define BOOST_PREPROCESSOR_STRINGIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_STRINGIZE */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_A((text))
#    define BOOST_PP_STRINGIZE_A(arg) BOOST_PP_STRINGIZE_I arg
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_OO((text))
#    define BOOST_PP_STRINGIZE_OO(par) BOOST_PP_STRINGIZE_I ## par
# else
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_I(text)
# endif
#
#if BOOST_PP_VARIADICS
# define BOOST_PP_STRINGIZE_I(...) #__VA_ARGS__
#else
# define BOOST_PP_STRINGIZE_I(text) #text
#endif
#
# endif

/* stringize.hpp
rFviatnqrjV4OStExXG98SWllwuFCH/J50su6OOkadNBGYjPFxuYrn/F6iu3Up9aRn3lq9RXvmZ8QG5bXKvKhvX2+dfdtd4Q7U3d5tubkmdt4gjMp3hE+RNHaMxoUAtNfFf3Y8kLqbgjy7yb/vNN7XuqP07IjN50StGqgSO6t9ddm/uzMO441PD4HaL1NpLtt6KKBurhyvbbSs/LyOYItscFRXHf71A6nQPphFnrRkVOJhDefgUWwxjaPL3NpYqYX3k6WzTvyi9C6xwp9wPQlneytlyu1jWojWk87x11Mrp0nTV2f4906fvG713TLp7SM9S75fT4YPdQ9zZdSDWEsbU/YLYcv41+/9DS73uIp7tpzPgR8fRj5hsu0px8Aebk/L2Id20rm139wdwqkctkdyq53QsaYRGPA1pMpFYrWKtAW7kweezFzCF/KtvIpO0UG8lW/ozJeZdwsLaUd0ihpgVMRNPxHUUliirwDRuq+53mSeNob099Uzc2hHr7N/Vt39zj7qcTrOc0F3YC9onCtE/0iyhybO9DyAJSYGtyMzapTh+k/aIqCBSlZHufXntBtmeSbF3bMzHuhvyOJ5JkY+5Teg/4RKlQKbqwXwJ2noSNI/aY2aILJAyzE0T6qXb4FdLtljDH9R/ofd5f87EppAjHYXdQrhISB9TZu4D+kzfe9AgD8cbe3zK9/B3p29E15llmpoSfXM9/b+nzQj6HBPU/kD4/WG8OE3CsqG5zsSJBzUw+euU8PlR/bo6Fs1uQJsEgxiY+Uod/2hv2E2Egzsufrb2LMntuBa5i7dc00N7FX0iOf51zH6WmHazRtraP2qvz3639rHG8t0XAY4S3cYP4J/H2hBmD6u+/8hHSgpqy/22tT2RZT1rrE9Hslhtqtvk0MmUybBANlD5C6Q9D+gUk72vxFGXdBNWR8uJfZXkXUN79Ke8hyBsxeavliYgDKM+BlEf+ngjmk1djS3/3th429HOw0adFdl1Y3Rep35YuoS4HE1/R5nrjHtYOxUI2k9wZl2E7vM2qYIxNaWn2bEprc6A18fCmEX8tATBzw8WM3iFWO8fw/jQ8DZY+LqH6PZ3JfXHdupqiBzYNDyLQaniwd7PhyUYY2S9tDjSXk42GMWqkp19G0SmyNXCk+4cR3f5a+8DGYVvOKN9UeofpwTWxRLutiv7aelIm/V1GcjyCydGJ2vrm5ivjqeD3s+32gL4dSXSeQ3ReJurrw9DIoIzCG+nZJCNK5M8tvX2mJ9RNZNrmKCprqFpZezn3l/SPaa5rh0tF3mHMq5uf78uXhd+mtZOsnttcb7wJ5vfSbVyMyHKqt3Enlbembl9NODuxDD6zMKYLMwAuk2OJxgl1aMwkMmUumllQHW9HtK4+kO8V+vcJ71frEDWrMT7jB6LKZ4xZijDvTWLG9x4VY+a9LJSfeIav1/+oYqeYz7WST/K171KK0+OwNoFzsbrnsbX3cnFWJZNGB5yslHEgMO9fQxuogv0J5a4U7pxHp3sYsNOEXK4r16vZdx51YQgg8+pxhgvDLNODpVyYiR97FPQmhbNG038M71mRWq3f/4b3oopLS+JM+Rh6m1dm2QfHhj4re4eYND4HuZY5RxQTpYTrm3kc77vUGpR8C3i/TO8fYvqLfAZ+BYOjyjvV/qKJdcglknFvv+swpL9K+XyUf8OsT9vUXqSC4TZhWkPKvUizv4l0BLsJ+5NFtLSqP9G8RdFU/hpFVNO8VSiYIqrT/8ONZUiX2J7i7XX2lO/UOLYf+rDw682/AHtMTKThi0ygOLNxzX3lj+v9XywztN6G0WeeILhpJsLtB5wIKc+mwZi9l5C6ycG8N7rv8SRIa94bkb8=
*/