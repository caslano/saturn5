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
# ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
# define BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
#
# /* BOOST_PP_NOT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_NOT(x) BOOST_PP_COMPL(BOOST_PP_BOOL(x))
# else
#    define BOOST_PP_NOT(x) BOOST_PP_NOT_I(x)
#    define BOOST_PP_NOT_I(x) BOOST_PP_COMPL(BOOST_PP_BOOL(x))
# endif
#
# endif

/* not.hpp
hLop8BO6CX0uPqh0YnLNCqUeRSbUlr18BCOSOxBCM2YM9/glCQRmWAk3WI9wD9/0RPOrk6zeTPM3n5TcT8uPYwZsYub6gfwl4IriQ93P70QM80VWgUSt+TPXP1YcCCfDRlp4tvXtGHMWJ/d4tpUED8b4aDj7AYsZBdWcu2NXrkYcIAAEJtcC2F5HyU25LZHMmJEMurreODqvHv87sL09uOEtSz0bOMxozGsyERn8hIRjQcLyFICx0IDTHOgduqGJtXYVCew0XD5Dskhxt4XWakCu2CrLdIdz+CtNFrDtZipM02KJJuNMq/EFgS+O5tnLC4HkyyjpFdLjW5iH9swXrlsKxhTGWH1yeohrWAgeb7k4iQZpERVReDG1WYwzA8dQ2LS+0lR74kigNyuFVBGN/yO1Jn5KPq6G7PMQ1EsbVcLMfwcPRd/WwicTRblZ/zeHVdVyWt+f6rQaC9aC+SptrK5gl1znifaqm/JAs8IX9T7y0qaFfAp6jM+B2URDmIk/kDSDAhrex2gj25krH7qLdmHXI153ofQBsoc5TA2SA32TruO9Rx7u+Q+89+6F/AOdTosRwAA/+6imIRtZBwbjqOvEEA1dGs2/Njl+c09kdjpxmk1UUy22kNYH17B+aaOatUl02SZslyA5pEEEsfXRoT5gbzXQeiHtQvoOz1SnjVRCpkj6STAvfiI9xwVictWhDxnaRlFeizVouFY9
*/