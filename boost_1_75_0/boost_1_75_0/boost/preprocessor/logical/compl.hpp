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
bQhrQZQSoMIOwnO0jZYhYPbojb8feqDkB6Nwv7nOt7/KTKlfHEE26LEm14kuIpbnqtLqXDykfKZR/Z+L6Cw/4CvijIRYuvZFxy/PSHdbBYojR3nR/+ZBrxmKtFkpqvP6ozwTKUrIXxTy2SPBQW9ml3lNiYpbdaWn1KSMrQmOxmqqO/OQL04uUD0zKMsWthkh986Fx/H+XvsfE+EoagVeRsWJOLLsgD4V7aIXTj45XPI7POn6Gmml6NW63kfcQJPl2LhyaHCOY49PhKNMxg7NWgTyL8yjtySuEYUe425rt7I1xWf+KBMEsiyaD9ikl4g8peE6eILey83JW349+NT/mAm/nSk+U81JxszLT4Y8BR+Lkqpq/+SZIaGMjfEPmdn7Mk5KRBDGdbdSxNW0RPqXt6TRDb+YGoZi6mORYx3ehbTbXxZk+siV4PnLYsoWje694aHRzVA++8ig/Kl8Ewpba1MPIf42gGBO7BcGBgHom0dkYeGu1junjZmVFTB7e1EVeAzS1SO+3OFwcHdmIHomGvS2AifgdyuBixgFtydK+Dt5nGX99SIpDjsvIxEbigbSDBMHOTnfkdX4u7u3b7YEdlzmBv4Kj8O/ZWP55OpwqRXV61HxuJ20tPlaOQh8ery/v70nuzQPoC69lR6Jnzh7oXw5K/v+2aCFUCiZvcMfC5h6bMraiZCzCYoNJ9C84S+fijSgjsvm8LiIgOZb
*/