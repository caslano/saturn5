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
# ifndef BOOST_PREPROCESSOR_LOGICAL_HPP
# define BOOST_PREPROCESSOR_LOGICAL_HPP
#
# include <boost/preprocessor/logical/and.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
# include <boost/preprocessor/logical/bitnor.hpp>
# include <boost/preprocessor/logical/bitor.hpp>
# include <boost/preprocessor/logical/bitxor.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
# include <boost/preprocessor/logical/nor.hpp>
# include <boost/preprocessor/logical/not.hpp>
# include <boost/preprocessor/logical/or.hpp>
# include <boost/preprocessor/logical/xor.hpp>
#
# endif

/* logical.hpp
na/XHp2uzd+mM4S6qP/2L5ltPv82v6A5/N07mszntnUg83qykwfXNZm7sOe8hsXyuiXzEjZiwlweS4HSrk3EGfu/6Sme156s6+r5vPfUk40U1j/mixDey6nCc9qR6UJDncn009ef4vMoj/v8x17fudv+e1XInISd7PPzNt5fyHxvmxPZxrgA3kNqyO69nb+/bXubNvwtwbrX0Q74eW/kOttrr5e2ZE9P2f0Qr1syl9t5H67kqIzM6bbdo1gVWfDfRv+5XzEXOinib49lFNmkAZ0KOX+vU58a7dLoJpN4+3mqNZMZNcx3v32cgYr5H9C2wDe1zVqobcFv2b6Rhf4zL/PO6O2/b1ux39/sYv+3dRQrCGv9g+/6wsLI2s3rO57n+m2dbtMQMvpPGzGWdmQ6Hf8b2mV+ZMduTl1ss7+LWH/bzEo76ktX6PO3hZb1IFv8yqvzbVbXn2MvM5Fdsrx/zmb1ZEG3zYtsRpV/lc38A6hP9//22Y1sV+G+T21WcRf/+7BlXZWxmGlFJd/usyPZM9l7BtusgMxw29zIbvRyO2izMjKX2zaMzHDtpWqbVYXYYxhDduXwhTdtVi0sTImvRtgAsocXlhTbrFbYeMWa7v7vWFLJTGqORut0lX8bxe6lWDOZ7+12RsUsY+x9eihmJTO3+2+fwxVrHEvjvN3uHsWayFxujyVUMd2422YILRutmAGYmczn9vPCFAsbZx/LBMXCx9njG6BYlGgn17sTmU7H+2fZvYo5AXMBpgdmAGYEZgJmBmYB5gvMH1ggMCuwIGDBwEKAhQIL0zSdLlxnX39//2/ZLlW0u0/pMw1YOrAMYJnAsoBlA8vRNJ0uV8Q+UYm9SrTrr/RZDawGWC2wOmD1wBqANQJrAtYMrAVYKzBdG21zAuYCTA/MAMwIzATMDMwCzBeYP7BAYFZgQcCCgYUACwUWBiwcWASwSGBRwKKBxQCLBRYHLB5YArBEYEnAkoGlAEsFlgYsHVgGsExgWcCygeUAywWWBywfWAGwQmBFwIqBlQArA1YOrAJYJbAqYNXAaoDVAqsDVg+sAVgjsCZgzcBagLUC07XVNidgLsD0wAzAjMBMwMzALMB8gfkDCwRmBRYELBhYCLBQYGHAwoFFAIsEFgUsGlgMsFhgccDigSUASwSWBCwZWAqwVGBpwNKBZQDLBJYFLBtYDrBcYHnA8oEVACsEVgSsGFgJsDJg5cAqgFUCqwJWDawGWC2wOmD1wBqANQJrAtYMrAVYKzBdO21zAuYCTA/MAMwIzATMDMwCzBeYP7BAYFZgQcCCgYUACwUWBiwcWASwSGBRwKKBxQCLBRYHLB5YArBEYEnAkoGlAEsFlgYsHVgGsExgWcCygeUAywWWBywfWAGwQmBFwIqBlQArA1YOrAJYJbAqYNXAaoDVAqsDVg+sAVgjsCZgzcBagLUC0zlpmxMwF2B6YAZgRmAmYGZgFmC+wPyBBQKzAgsCFgwsBFgosDBg4cAigEUCiwIWDSwGWCywOGDxwBKAJQJLApYMLAVYKrA0YOnAMoBlAssClg0sB1gusDxg+cAKgBUCKwJWDKwEWBmwcmAVwCqBVQGrBlYDrBZYHbB6YA3AGoE1AWsG1gKsFZjOWducgLkA0wMzADMCMwEzA7MA8wXmDywQmBVYELBgYCHAQoGFAQsHFgEsElgUsGhgMcBigcUBiweWACwRWBKwZGApwFKBpQFLB5YBLBNYFrBsYDnAcoHlAcsHVgCsEFgRsGJgJcDKgJUDqwBWCawKWDWwGmC1wOqA1QNrANYIrAlYM7AWYK3AdO21zQmYCzA9MAMwIzATMDMwCzBfYP7AAoFZgQUBCwYWAiwUWBg=
*/