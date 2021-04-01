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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_TO_ARRAY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_ARRAY(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# else
#    define BOOST_PP_SEQ_TO_ARRAY(seq) BOOST_PP_SEQ_TO_ARRAY_I(seq)
#    define BOOST_PP_SEQ_TO_ARRAY_I(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# endif
#
# endif

/* to_array.hpp
8PGeAwdb+z50UEbgqWHfacGGv1hARtj9m1MQFbSUbomxMY24nOkXIvM9IJq9Ll5gYeFOcUbZA3Ub4RT9DWRErZ8vAIPsJ9tejREKKaLjIDbHZN4+MGBiFzc664Etdl3Xa/BzIq363Y2nhvLmkzuV3TUIYKokUeCscxuHJ+xcwKS9Q8TJDsyUzbf+XMmJevnzCNQ+j1pSHpAEsWS4ZBcmm+kzobYcy+uj3S+/u+2u98rLQK0ybZfVbuWi4Nae+7nO8K0vhTS71XcF967dXNVw6Vc8GwnLPmFTyuMqZgt++8lvv7BbgnnwDd8SaDiy37o4ra/yhHOj71Nx0AfY8ZYEPCuBOBES5pa9eKqhbdVCIVAhO820mXib/WalNqnjt8kuw0MdZjonE0oKzWJZJ+ULCl5W2BDUSx8DaPJiMzibi2UaMSpv2/Wk462k97Deg7sYo36JUndMf+dvbzIMTrq7q3kZfDNITmpE3c5YMpCemlz+YTRi670Qg89V2WlMqvl2j1TpeEfujmNbS8WEcd+1KEAZSmaV9r1Ahime0BqhURBrGXD+ts5K1yw7iQ==
*/