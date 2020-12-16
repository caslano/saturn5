// Copyright Cromwell D. Enage 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_CONVERT_BINARY_SEQ_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_CONVERT_BINARY_SEQ_HPP

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/push_back.hpp>

#define BOOST_PARAMETER_AUX_PP_AUGMENT_BINARY_SEQ_INDEX_FOLD_OP(s, seq, idx) \
    BOOST_PP_SEQ_PUSH_BACK(seq, (idx, BOOST_PP_SEQ_SIZE(seq)))
/**/

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PARAMETER_AUX_PP_CONVERT_BINARY_SEQ_FOLD_OP(s, seq, elem) \
    ( \
        BOOST_PP_SEQ_PUSH_BACK( \
            BOOST_PP_SEQ_ELEM(0, seq) \
          , BOOST_PP_IIF( \
                BOOST_PP_TUPLE_ELEM(2, 0, elem) \
              , BOOST_PP_SEQ_ELEM(2, seq) \
              , BOOST_PP_SEQ_ELEM(1, seq) \
            )(BOOST_PP_TUPLE_ELEM(2, 1, elem), BOOST_PP_SEQ_ELEM(3, seq)) \
        ) \
    )(BOOST_PP_SEQ_ELEM(1, seq))(BOOST_PP_SEQ_ELEM(2, seq)) \
    (BOOST_PP_SEQ_ELEM(3, seq))
/**/

#include <boost/parameter/aux_/preprocessor/seq_enum.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>

#define BOOST_PARAMETER_AUX_PP_CONVERT_BINARY_SEQ(seq, macro0, macro1, data) \
    BOOST_PARAMETER_SEQ_ENUM( \
        BOOST_PP_SEQ_ELEM( \
            0 \
          , BOOST_PP_SEQ_FOLD_LEFT( \
                BOOST_PARAMETER_AUX_PP_CONVERT_BINARY_SEQ_FOLD_OP \
              , (BOOST_PP_SEQ_NIL)(macro0)(macro1)(data) \
              , BOOST_PP_SEQ_FOLD_LEFT( \
                    BOOST_PARAMETER_AUX_PP_AUGMENT_BINARY_SEQ_INDEX_FOLD_OP \
                  , BOOST_PP_EMPTY() \
                  , seq \
                ) \
            ) \
        ) \
    )
/**/

#endif  // include guard


/* convert_binary_seq.hpp
+xGWxc1YDXdiezyCnfEodsNj2B/fxSF4HEfgezgR38c0/ADn4RlcjGdxPZ7DnfgJ7sYLeBg/w2N4EU/hJfwI0zHczvbDSPwBo/EnbId3sS/qbJfZaMcF6IPr0IHPoxNfRD/chfnwHcyPZ7Awfo5F8GsMx+/xObyFm/FnZPurmE51cRg2wBnYEOfiw7gcm+PLGI1HsDWexjZ4Htvi99gBb2NH/AU7IXnTumAB7IrFsBuWwB5YFntibeyHD+NwbI4jsDsmYB+cg3H4JCbialyAT+MGXIvbcB2+jM/g67ge38YN+B5uwjO4Bb/CrfgDvoR2jtFdmBd3Yxi+jMXxKlbB/q7thQOxJw7CvjgUU3EkTsZEnIZJuBBTcAWOwVU4EXfhJDyAk/EdnIonMA3fx2l4CqfjGZyB53Amfo6z8BrOxhv4BP6K81Hz5fyEdlyE/rgYy+ASrIIrsQ2uwh64Gvuia31HYDnX+mB5nIbRuBhb4HJ8FVfiXtyC+3A7+jP/TsyDr+Bthh/BO3gC+zP8Y1nOl9gbf8Q++DMmo92P+xJ04jiMwvH4CE7ALjgRu+Mk7IuTcSxexVmYhqtxGj6Dz+E+3IxvyXSncR9exk/wBl5A3Z/rPjrQNV0oXsTSeAnL4imsgaexFr6Nj+A7GI1LsA0+he1wHnbHJ7Avzschkv4Y3E75zMYXcS4Ox5U4DNdK/wv4latc8Qrul/lPYAfXfoKd8FM1XNpsssl7LXmvmC736gFy//e6/I45jgXwBIahq020ovg+/SXwJFbAU1gHT2MDma4xfkx/bzyPA/ACxuGfcCR+jmPwC/n9+g1uwm9xK97AvXgTD+NtfBfv4nX8GW8j1zR1PfsVg9CX5UegH1ZAf6yGnbEm5sH6mBcbYCA2xSBsicHYGkOwIxbAPjJ/fyyMiVgE52E4LpbxyzACN2AkbsZS+CKWwVewOh7AKHwba+KXWB+vYQu8gxXQxjZpiU5shX7YHvNjBwzDGKyInbEq1sZ2WAc74kPYDRvgcGyIo7ERTsSHMU3N744pqd47yXuudI+Yktfl9/t3qH5/YijewDAZXhR/kP1Nc+VR0vOxMz0+7BrPAPV7nuWWxMFYH+OwB8ZjXySvack4nP4ZmIrP4SQ8gpPxFE7Bc/g4foJpeA2n4Xc4D+/gExjCsudjGC7EYrgIS+JiVM8JpW2sYGyKIfL7JRRjsAj2wkgcgiVxBJbDcVgeJ2NV3IbVcDdG4Qf4MH6MjfECNsUvsRlewWj8Cdvgr9gW87m2PwZiDBbEzlgEu2Bx7IplZHxF7IkdsRd2wf44HBNxBI7CkZiEUzEe5+NQfA6H43YcgTuxD+7BR3Ef1sEjWBeP4Rid/ONY/BrZfmo/8NPlObm8F0iX5wJ3Zb+abGd/x6noxMfRD2dhDC7EAbgI4/BJHIJL8DF8CkfjUhyPy3ABrsJFuBq34dP4B1yLu/EZ3IPPyv30RjyPO+Q+ehN+htvxz/gifol/wK/xObyNW9HBer2AeXEHBuBsLI9zsIoMb52NGJqHzufG0cyNo5kbR/N/JY5mFI39dqNLo1tPd5xO44Rbga493WS6bXQn6e7SRdEYcAzdeLotdIfoLtK5zpLF6FrTDUvLjb+Z+5f7l/uX+5f7l/uX+5f79+/689H+hfH/4mr8Q+L/nQzVjLgrfeVW0vUsJD8WRVcMp6RYVX8tulv7rrH3BgHMXtwm0jDqxz0VpL4XMmJhTFHj8unhjMsb4hpniqA2OC6FAcb394kDMurNuafNiK7CpAOTklSYJuPb/dEyrSt/c10za9Q3HOn+XmauWu7nprTGJHos2Zh2hEorQsv8br5OiGpDTXV1Q1z92R92T529bMQ=
*/