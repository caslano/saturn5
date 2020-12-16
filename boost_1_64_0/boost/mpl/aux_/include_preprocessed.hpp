
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/compiler.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_MPL_CFG_COMPILER_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_PP_CAT(BOOST_MPL_CFG_COMPILER_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#endif

#   undef AUX778076_PREPROCESSED_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
7Czi4iJWi9hFLitxv5aXiNuI2EPEzUTcWMT1RVxbxK7y/V0iriin3xZ5RNxYxM1E7CHiNiL2ErG3iH1F3F3EvUXcT8TBIg4VcZiIo0SsE3GciIeLeLSIx4p4gogniXiqiKeLeJaI54p4vogXi3ipiFeIeLWI14l4k4i3iXiXiPeJOFnER0R8QsRnRHxBxFdEfEPEd0RsEPEjEaeK+IWI34j4g4hVd6TYWsS2IrYTsaOInUTsLOLiIlaL2EXEFUVcVcSuIq4t4voibiziZiL2EHEbEXuJ2FvEviLuLuLexGYexeXJf2P/f/mNSEpQghKUoAQlKEEJSlCCEpSgBCUoQQlKUIISlKAEJShBCUpQghKUoAQlKEEJSlCCEpSgBCUoQQlKUIISlKAEJShBCUpQghKUoAQlKEEJSlCCEpSgBCUoQQlKUIISlKAEJShBCUpQghKUoAQlKEEJSlCCEpSgBCUoQQlKUIISlKAEJShBCUpQghKUoAQlKEEJSlCCEpSgBCUoQQlKUIISlKAEJShBCUr4fwkqJShBCUpQghKUoISvCEuCgg6MHT78zezBg/+YPGzYK/tnz9K2Dxx4bk1k5DXf/funebu69rOysLBc1r//sRFVqnQt8unT/cDz59ff++tfO/wYG/vI8/DhKfPGjCnV7NChxPEjRrwr+O7dk5QePdYeat362zypqe8frVzZvP+ZM799XLjQ/+Gvv3runDu37OvFi31+iI6+02vXrjl7Nm7UF//48eaq7793H1C+vFfPunXDmjdtOtLy9euXnY4cSehdu3boiyVLOte+e/ek7dOnb78fNOhWzIULf/WpWTOwacGCle2srW27HDw4Q1O2bKu+e/fOq+js7Lrghx/qOdjY5F7/4481cuXMmbdu/vwuc0aPLuZ+69b18ikpR7UVKnQ8unbtqJ/1+ofFcuXK/1NCQgld1ardqxctWrtasWJ110ZEXPmjZ8917+fP7/WqS5fFHRo1ig04d27jsd9+GzGsUqUuTW7fvjqoRo2+M8eOLfDSx+eX0JMnN0tlWfXx49391OpmpT58uJ28Zs2Qx716bdgxYMCZVr//Pvnijh392zdoEH2tXbvpZ7y8Zhm6d1/d7vjxcQNPnNha+cmT/XeXL+9U6P37x/tbtvzmfIcOP/q5uYVMHzcu33FPz4mOb98+yGFpaR0/atSnVG/v+R6NG8dt+fnncreXLm3/vHPnhZ8WLeqzq1mz0ROnTLFZ+d13TbfNm1e6Tf36UdYvXz69vm1b0O4NGwbrL136Nah06Raujo7qomlpd/M+f/4x/NSpnV5Hj8Y72dk51ylQoHyNR4/23vT337Fw5sw6Rzw8JjQoXLh6t337vn/2l7/4jRk58kNrd/ehK4KDk+/36bOlSpEitWbExNyb36/frlnx8UVOdur006grVxaFlCnjMbJyZd+/Tp3aKGHChDyHW7WaVOmPPw6e3rRpYGMnp4pDrl37y62+fbeVyJOnUOzlyysb3bhxuWutWsEdGzbUlcyd2+ly27bf5c6Rwy7MxaXNnd69N/XZs+fniNOntz9ZsaLlL4GB+5ZOm9Zg8YwZNevduXM6aciQZ7Xu3z/bMjk5qUe9ehEbw8MvTZo82SL47Nk1pzp2nHtj2bK268LCLrzr2nVFzhcvnpd7+PD4rxrN4W+HDn3xYNWq1s62to5nt2yJnBAXlxpZrly76OrVe7sUL17/6S+/dDu4bl1M5wMHZpY1GH4ffvXqgrk6naF0qVJNrrZv/8OV7dsDvklKsh83caLD1KioGy2aNBm+b/36QctDQo5caNNmqo2VVQ6LV69e58+bt/iigIA9/nXqDHjbrduqE5s3a6d9800=
*/