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
# ifndef BOOST_PREPROCESSOR_ARRAY_REVERSE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REVERSE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/reverse.hpp>
#
# /* BOOST_PP_ARRAY_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REVERSE(array) (BOOST_PP_ARRAY_SIZE(array), BOOST_PP_TUPLE_REVERSE(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array)))
# else
#    define BOOST_PP_ARRAY_REVERSE(array) BOOST_PP_ARRAY_REVERSE_I(array)
#    define BOOST_PP_ARRAY_REVERSE_I(array) (BOOST_PP_ARRAY_SIZE(array), BOOST_PP_TUPLE_REVERSE(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array)))
# endif
#
# endif

/* reverse.hpp
nDDGJKG1TRai8yORpQTGpPoO+oJteL8tbeZgqSuQzUZzRE7/CTvYxCaP/I39pTT8ZWveuNirS1Nk/YldNum6mDHbJXJ2DXs6/oYNDcPnMy5Dp9tkdBy4dZ0mK9do0ikNfh/Q5DPG6SVkfW0eMoMdtIWCocA1z5fr8ih9qAInDMzBdjptcj5ysv5rfIsT7DEFe3kDq1peE3hOPVciV+ts8m0FMvsifEPnZ67FdoNTfkHWXl/JO2xv4AfxxQ7GLaUluBLc3KZG5LZO8GeyTR7+BKzLc8PXgQ0n6NIZv9bvDGSdvo1Ed7+qFLMPN2zR5cuvsC12XW4awRldGzVpij/siP256kdsdgV2JYX6Xtbl679hSxLAalm6TL6cOejOzJffC355jj2XwLS2k3UpbQ1ubYptQMZagEc34UtOx08sGYN/LUTf/wRmiECum2py8jnoJrxbi178DTt464O6/HYZdr4K34Euv3EWeBrfH3MNeoRNeOlZbOtL+KpY+A1umZpsk0v+JrL0EU1q6FNJPmtriDV6gQEHIqMhh9DFd3XpAM5tix72uECk0xXU00yTztisy/Elrvc5txM+Zq4BKyMjkYzdc3xG0e42d+InloCz1+syBzvwQxj+7inw0yXY5dm6hLTD/sHrg9j2Ht9Rzy+6HGmpyYhxIjnX6DLhsEhMGTEQfLMh/89MIr6w6XKY563vocvMnfjiArAimDkB3ISplx7vajI5TZMF34sUDOcZIejg+eggujFJwOF322TG3WDqPmDq09i34ztiLrBtYrwmOTH4qS90ySXe6A5maYR9/xGZ+tNt2OOJ8JnfwzXisS0imfzudACcRl+/gIcHdHzsQTBXFzDhaubsZtLnftga4oZVDpv82gkMBK8ysOkamM+zh7GazN5an+niQddiUKDW2MiPVqGnaw0sqEs/9P1i7MNT79jkwvvAfDPxH5HEU+jClfA7diH9fw77f6EmdyNfNZv5m7hv8Wrs+HbuQ/a3gn0P8L0bGZkBjqnah29+yCY37hfZ+ZjIu9/psm8+Numv+Pu+nIuM/8r6Anv1NHsv7QDngZciNO4N0yUFff4JW1wazX4T2KiB9O/2Z8BaA8E72Mjot6l/AX0kbsx5mjFCh19GBze3Jh40sPb1/N7LeWPobfeW6A+26lFijAMH8D30L7EzY3MfMQf4pXtrsB62MIRYatoUsNw2mxw+SZNn4dvdjL0d7PD+LOLPLPqIb1pNHGTfpUvGeeDgPuD5h4kX16DvbcAK6FkeWGUttnvdS9hc4oq7kK8ynvckPjSaGHklsnL+U/C4Gv3l3hU72WMyXcD4YDYH2Gwaa03Qv7evRM7wn6mx+IPlyF6GLne8gk+7GlnIwAZjr5OWaLIzinWvJ+ny8h6bfAMO+xh7aU8AZ01E3odh09KIG2bjJzsj+zo2YBfrFQcb7bLJe5k2mfU1MniDLlsYi09eoI6NPDeXsR2DPb4AW0b9lw/A9hUiC2CWJ3/Dpwzn2cSX6S9gQ+DTkf3YUPjyNDLT0QHO6Egs0hwZeYsxwpffhAxkgoU9sfQDe5X7MzEfMvDhnzQZho25lvF9twT53KrJi4vwS+C3y/DrlV+hR5R5tkjoty4X8vn4TsYazOsiXsx/kBgQf5aLj70pEv04G2yDLd31E23rgx3ZjB+6l7hsMn4ZLDw4ER3B9g+F9uYHxALYCSdy8WgosSfPcxtxbiP87UjsEdioM9g7CR97MTHwPd9gX9C5tJbY4QzGCD7M7YePiLFJP3xQnzXYgwx06RJ2MJgBPnwFWT6AHdqA/TwI3xmPidid6L8YtliT17cRp/F5Gj06CXvuAPtdchM63R+bS47FAfZd8Qg=
*/