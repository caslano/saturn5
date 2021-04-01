//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <memory> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/memory is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_MEMORY
#  define BOOST_CONFIG_MEMORY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#  include <memory>

#  ifdef BOOST_CONFIG_NO_MEMORY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#endif

/* memory.hpp
vHY0ixNWqb7FTjKMwYnMqyjuSx7++SUtP783DfapAH6Aj41icNj9ttu1VyIv23RJWP0UPimMnl3FPYARCuBrghzc0NYOfLOvU69KUyPuNUDNKNrhIarWFMIXc73LpBX71l8urlJIon1PV9enb4BNukW0h1Tf/CqB01e1YAdEwb2FMArBoaUr3EDfp4Nu1BDG9jUC1kW/haiGsy9QDjA+8U9UMkEHmk0zSVFyzpj+TCD65YPp/PITaCO2MKJOAT9kBHy2bUG87HEJZ1bA8tPaTvVpQMH1pGrJrwQgdCATfOu+/Aa49+Yg0odhmLAnfZa7ZhFjbvjp5fL5bdFNM2lTEUQlkibXAx2SpRwV21GbTvOlJjLD+Mwv34YooW2UxEti/IjqdiTnsnWPb8EVA/XiiXCugPYAcVgrqZFsMrWQT5muIlDaSHdux3wW/IV0wditT/qvraID5kwthcPP5PaoZNRaI9gDVXy7VvQ/K5Tgu1SxUAgdkjP1+jItJpAxOIFOJui4od1jiFjIE4VqVBN6mW5VPbo4f6TjmQLuHgrtwkiR9afQCJxnpr81Yw==
*/