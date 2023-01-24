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
TqPk1/cCXGnaGUr1CqTDct47aSYfdnfGssWqkBqpqak9SNwWDEH8mAuw0VKt0/zVgCAThu/d1k/DHIcGje9GU62lEd07WrEB6i/81Ttvbzgu+j0GBoQaUQMDxNlvq94H+x29iXAC3LJX0S7JKPyUXnrfXGpl4kUTL1kRF+VyU8j6tml1t8t0YMGqxJSjyundsMS4DbLTqoFcPur+ROGPuUTtgs5YhjMlSHKGYy6N6nUPHFOxy/kD8kRn3V1tYM6iqlEbXTh/3FS9xxbGn/pIdi9Uo2Urm2dFNhvFFf1GsJlosCiEPAWt+/Uk9kmW3WuY4j+GVbCH05Wrxl620+DSoyXXrCjqbyvr/O9hL+7gH4aGkhNdBqUEUXHRVBvHx/SKqZ81Qn7Ks30jqOB/BL+f4RBs/hP8syuPVQ8Wpd/D6ZRsS/1uyWCCxShfdfR1Hntbv7ZTd6kr9cJPIfsr1uobTA6FBk0Z8aC/G4+huKO2jv8IgywyOLjMmvM36t5dhXI4lY3yGRIrig5sc5TPs7mTUSXMFs2ixxUipftK5gVXBvg3f8Aq3xFS6IX/CIjCXJg7mYA/31euYa/50MqCsVVYmGhdmM3U4PoFpEhEjWA3Y26YWVFxVmUPAIYzRAtO25oOdur/EyQs29OcuULqYu5qHSlxWhLZaElpTeNcvao0aWMQjF3jByOW74TBTlugu60d/D5nFfSauhx6jHeG
*/