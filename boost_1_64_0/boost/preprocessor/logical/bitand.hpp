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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITAND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_I(x, y)
# else
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_OO((x, y))
#    define BOOST_PP_BITAND_OO(par) BOOST_PP_BITAND_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ ## x ## y
# else
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ID(BOOST_PP_BITAND_ ## x ## y)
#    define BOOST_PP_BITAND_ID(res) res
# endif
#
# define BOOST_PP_BITAND_00 0
# define BOOST_PP_BITAND_01 0
# define BOOST_PP_BITAND_10 0
# define BOOST_PP_BITAND_11 1
#
# endif

/* bitand.hpp
3oTPaLkaSs3FskmejMuycaksfdoPqZrc7dO2nSkMMxmTJVIu8DPvSAFI/Bfxwn6vmZdqntiBiNVS82QmrfGQcIoaZ3QAIZLVMtpYuqi51u1KUKwiTmifGq7wbVhXN2XdmGFWSkaHebEZaLiFlE7FJcy4rrV5ZIcpWU2BO+puU0PYafn7H9xvagg5b9chzLjAqKvZFaO/6EtT/Fz6//g6un46hLUpOgnG1v7CkxMJqhN2WsdDA+RISgPQRCuzSnoLOjbalkRc1FJT1XTpwFJ0VSn2ImlLHg6S5604rE2aI/m1KMguCUc30cd/qyI+OibsD5fsYCUlGKP19jMZBF1LtXMRu20oatME9g7SivvrxKsYtPutoytG/q6jui7zBhkwB2NKsyIaDIiQY8Xb61l7CbUnt0qdCVZLK4lTuAOWNA4XveizZn25FdcbyetcvNLvfxxv/NirPWCwBi56TEm1d6g3yxKaH1G5wNOouFkbDO8QWTtBXRYJz5pvy5G1I220873adetfQfvvITaBtfVhvqJj2wQtZ7Cqp00ItsOh8qSzabYbpHab+QcJT5+iCRKyj5m2tyx71quZ1xK7GxL0LyzQ6JZ0LFyh4t6aiDQ/1i7PgTt2uqJNG1pqIWzOim5kGcyb+06eqGtaUVldDJ0+McMMol9nEmWWdS0qrkFhJqoLiAmzRaFNgS2S6q4ZtmhB0+W0Stsee0votbVmjWWxzuKCCdySjHWfBC9KI5PR6Z9tvStNHjpSZ5sZ+da6QYhUUHItH0h3FfulCWDxh7bGC3FQbILFXFtXB+O6dm7nH0yq6fbxVEdLvamhXiYOg9KmrEp4hpLXWiW9sXbwbCcr6+njwmXV1MN2s258bu9TFp7w/EPVmsn4YfO+mhEtQ31dXqcsls09GKCjUaZFuHy37XyF+//sqnVTB3DhfYbMmmLWpQMnc1iniU5sqFSV3hrsuiR54a+mRwuejtbKNCW006djNJKZ5sGF59X9MWbUwTquN4f28mBSaMvIudB6QyXFL2P2JVGF2wY7ZFRN7cyqpTNlZehl7is3TBta7jS1dHYval3U1NC9aOkSmtQlTS3tLc317qJpS+3m5XlkKp1r9dQHPvvVTsdTEgiqh60RlXaNMdpyacTCoR1pLX8aMmbnxLHuaJI0y5pVo3ipNZpqpmOIcBGPlPERR1nqFvbs2C1SDgKbRiAoY9ix5axMTycFI5U9jc95hv66J232xgZjazwvbZnULtdoqSUTXxGWobovbPbbgiVP4mU3kL1QaInx9wTr6yXqkfWoEcoOTtoy2JRMsBMaHGtSAa/HpeXTobCdYoqFpnNdu3jHbfOApGKHXxMjmItUBnNYM9awW/betm++1rbpVk5ayHjgvgZyhFhG7GTWVP77blTaNYEuXVaSBSZWryXPiql8kgRfQpHWtT3pT6jA60jOSm3MmRkxTtFlu/LOn6qseosaZnV1dy5acpV4ovuCeOSNyIKpW7B8pbmja1gp5muraIzIbQ2w7napo3YPyC7/mh1yNSKz/eWZ8kGlWDIDGelNdHybTdOe2LjTnep0XWNBnE00rJRm+zriP0hR140iTUljV1plijTNm3UlIhv1Q7ddJD+ozyktoRrD8iFidSV6QWRS6p6NkqlsS65pb1fHI+4jTI7L3hFNGNEorOOAXmW584xe8lM0WqGqoJqVkrZeF3bxRNXsNOXGNH2yScNKqy0Ha6pdKpfWA21ldYVaM7Wf5YGkNqKy39zS2bm0s75bR5G6mSFVmv4iHOagP7HyXeEOCyMd/1m7eizRNE3VasfVPw1O2WBrmun3dF5hgpbJ5YpaWPy6ofktkdDBnvqDE1590MglCrI=
*/