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
# ifndef BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP
# define BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/for_each_i.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FOR_EACH */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH(macro, data, list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# else
#    define BOOST_PP_LIST_FOR_EACH(macro, data, list) BOOST_PP_LIST_FOR_EACH_X(macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_X(macro, data, list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_O(r, md, i, elem) BOOST_PP_LIST_FOR_EACH_O_D(r, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md), elem)
# else
#    define BOOST_PP_LIST_FOR_EACH_O(r, md, i, elem) BOOST_PP_LIST_FOR_EACH_O_I(r, BOOST_PP_TUPLE_REM_2 md, elem)
#    define BOOST_PP_LIST_FOR_EACH_O_I(r, im, elem) BOOST_PP_LIST_FOR_EACH_O_D(r, im, elem)
# endif
#
# define BOOST_PP_LIST_FOR_EACH_O_D(r, m, d, elem) m(r, d, elem)
#
# /* BOOST_PP_LIST_FOR_EACH_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# else
#    define BOOST_PP_LIST_FOR_EACH_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_R_X(r, macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_R_X(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# endif
#
# endif

/* for_each.hpp
v+WX1RNgmFTbDfmyztRCKOS5n83PSbMFT5GH9vuMnHdjqXRBCU/iyMN64L9barEXkmyvTw1W6Dz0IA/nG+VxR0cDLEvRWbzmCw/WKHFLC+C0UYmutt0MOeGu02DqmZBOEDO6prgPjwQYbLiJTy83W21Cf/zBLdIfSzruVuuRkMffJwEN7NfdEk/ffF65X5X5MqIRlE7YaLt0re3JBL0pUS7NhBebF/gQcuZhdDCFG0R3An+8isKg7IhsOUAkQ+RDN010kbS5UJdBpEKUQBRAZEMUQ5RCpKvqbKtjTlUj6HnDvbJ+s90aH2HamVA7lnTHV9E7Z2Sh2CNXo7eozRexO71RbRLJWLRUFUMimRzdgJKfjEOIF+ol7eRorsrWZunRpep8LS2InqcWa2kxOuUFWuphpzwLCq/ak2p1ymWqxIpX/S3SLd+0QnfrynuZ7svRQqfgunPEWW7KV9JcDsYz6SQ/M5N3gumLl9xeo/ofMfN/+tgDGJukN6+IsJktVhl+qK6fpOVVp/pZCktYlGI3atfTe9lK9KKROcGrFr7DLkwGDeqNgDTn6uPxCSgN9fNTOIRrsMWuUeQA7ukKUVfuhufo2zriUQ/oqEXvYJFQfVkcZXBLPDeSMaFfQpRLMGYaniiG8Stqx2YGZ9WOOYLTMdsPubCelIa1oq/NNsrF+DRRh5Hkci8hOlI7lgWXwjyYYeyIxgJ9o5jpxchMHvXso74z8jCajebi1JyNgHfjBq969D1reDPL6D4NPVEtbDBP6sd0nuQvNeADtFxBt9+wxYdAt2s//er7Uavf54rP1fBhOR0F53rV9sM0FIOLYYDePId+zTMG49FeEot2vmEbzkcR+DAPI4z0jyfYtDjlROEYFiqjdlrJQSRMK1cjB3UV8OooBgzncMzfV4p08Uh9DDNL3Mt2FP6NiHU0MVLcdsBPM/PnbsGg68E3EVm0KieEYUF9tpiTHTRs8uTZcW+rtbdbEP6ddj1Mc8gwzSfeXYmlponb7CoES/rBv32PlJkXJlrCebojLCuKd4ShUkSmtP7wnVzfrX85mCUd49P/z30JSfnvZfbUTiSwg0j6eY/XX6QuOspeASGy21QbzW4zqekO3bqUZB7Gc80zyuKPdf9GKxdK6o9UXWDF9iFoZ+6V9kFmQgnhMaNqWMLZtQHh7B2TcDzRq2BWarvrPDhO96slXzCfPXSK32iIh5C3URfDdNQpht4eNztHh47JCULhTaC4LmaB0Re3MR02pDHXg7I0211zURcywufW7rI3QiK9kbRfJ+Ct7QS5nCepfnqCDJmRg4cRli3ebDy+QT8pGtT6l5PqnkX+4GmRb3jcJzaYcb/rEisFOkzrtprs20NzfP6iZ5HzF/LJnVYKf2ODNTDZy9A88dDWa+dSpoqMqiEptm+gMTHv43FjvksXWXEXi7QLoxqWTRe582Mu3kg0XRTHXUS81hO5M3vwTN/X7UyPtnqKpKXbZwzHE7PLq8uwz1ek9nxo1gtk+2I2s3fPZkoG7VLM2PpKocr5iI+sG64Tkurvs+lkljbRsB+O+V3qnZSeN+uApB6cg27VSlPaGZMoJ8mAJ4MDni0JCOX2I7HhDjQw3rnDVaTO+FCPd4pU4MhxJXuO10r3+yPPTWOL1ShLCD7DjQhFboNUjmnXy60VeLxzrfAHrxY7ObFIYzZ0P7TCM5C3kS/DlfTPNt2PV5i/VfKLcuvAqC18tSM6A+UvPbPHHFvmejdgCFLtJTBbOKITNVkamivhofFkgtkj+VQDgjKestRGMtoyjNW4Z3SzGPVYRn5L2w9tdD/bbNYRgiA6AD8aro3IqXJb8Er8GLZgPn4qbMEVclIahouMXss=
*/