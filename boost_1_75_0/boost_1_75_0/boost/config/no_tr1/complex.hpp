//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <complex> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/complex is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_COMPLEX
#  define BOOST_CONFIG_COMPLEX

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#  include <complex>

#  ifdef BOOST_CONFIG_NO_COMPLEX_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#endif

/* complex.hpp
OZ/4RXbhIxx/eHPCAjmm9POtou/Sj/iQoEI/xrWTda5qYvOcMVfjBuPhZz6EV0qtfbm8w9HdMnl9KtMrzfhXwqBZn9rjdzP8DwinOn8q+rGbnO641NyMTD/7rCLdu69kDnl1yAnCs5HZ1QJ544vmOtmta7gjyAYTxWUkdvhcoS3Qw8t3xuZuakPhPTi/0FpN3vh0O8E9JEamxUOZvG7dIDpo9MHVEW3P+IzAKJH6ubTYJXE/qblhvxVLQKotGWFC1zikqbxPy2a+GUTnrgo2DbRMzhPlVBR3h9/pxtlMyVwKfPNp66blwym2c3Ri0j6xC2dO93cwqD13e+KaFUYjm8eu58Jr7931Hf9eKzxNOOHOzqOeTFF39F+2EcifuXtEWZvdHfaIuR+z/TBymW4d7d2A9reLuzvxMVD/t3MyU+stkPALOLuSHfn+p36YChotZx715Op+bVUavmjLIv9ZqFiyftCZtyJfrEqEvdav0D6b4EuEd2pGbGmiHD2NEjJbPRcbd0GqBnmt8H+TPPM81MiCHi7yT5fF7omlFbywwgCfEQ1W8V1u1UZ635v0Gs982RHueYssmWFcIRKS/ULKNmG80V+aBO4Ynft9OTJs6Wze4tEZke5UnGNFTg85rfX9uHlqxOsXAaq+kVugwn06BfhzzRmVte4Tw8d7fb+c1+Ro4u47xVbbz9lKCGDT1CVQ7z9GY3L91+12RFbt
*/