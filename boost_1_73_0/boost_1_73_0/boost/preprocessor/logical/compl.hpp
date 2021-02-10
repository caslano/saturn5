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
# ifndef BOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
# define BOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_COMPL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_COMPL(x) BOOST_PP_COMPL_I(x)
# else
#    define BOOST_PP_COMPL(x) BOOST_PP_COMPL_OO((x))
#    define BOOST_PP_COMPL_OO(par) BOOST_PP_COMPL_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_COMPL_I(x) BOOST_PP_COMPL_ ## x
# else
#    define BOOST_PP_COMPL_I(x) BOOST_PP_COMPL_ID(BOOST_PP_COMPL_ ## x)
#    define BOOST_PP_COMPL_ID(id) id
# endif
#
# define BOOST_PP_COMPL_0 1
# define BOOST_PP_COMPL_1 0
#
# endif

/* compl.hpp
VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUk0NLjPKAwAAUQgAAEAACQAAAAAAAQAAAAAAG1QPAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfRElTQUxMT1dfVVNFUk5BTUVfSU5fVVJMLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSZQBhrksFAABFCwAAOQAJAAAAAAABAAAAAABMWA8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9ETlNfQ0FDSEVfVElNRU9VVC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtaOFxtfBAAAUQkAADUACQAAAAAAAQAAAAAA910PAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfRE5TX0lOVEVSRkFDRS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkX5T1+UBAAAoQkAADUACQAAAAAAAQAAAAAAsmIPAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfRE5TX0xPQ0FMX0lQNC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUjor5z6UBAAAnwkAADUACQAAAAAA
*/