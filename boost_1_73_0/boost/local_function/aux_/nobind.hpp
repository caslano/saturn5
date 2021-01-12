
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_NOBIND_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_NOBIND_HPP_

#include <boost/local_function/config.hpp>

// NOTE: The current implementation needs no-bind placeholders only when
// local types cannot be passed as template parameters.
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS

namespace boost { namespace local_function { namespace aux {

typedef int nobind_t; // Tag no-bind type.

static nobind_t nobind; // Global variable so all no-binds can reference it.

// NOTE: Used only to get rid of unused static variable `nobind` (this function
// is never actually called so it does not need to be defined).
void no_unused_nobind_warning_(nobind_t* ptr = &nobind);

} } } // namespace

#endif // locals as tparams

#endif // #include guard


/* nobind.hpp
0bTeAmCsvqPBkkyhmMc5J+SmyS13e0utshpxiaC/X9qBE6jMCLPQbwozJeiOy9DjRcN/e4klcOj5sv1ObGQ2f4ULSdp0f92VXahvMd3V+jaCcrhPms6t3H2CS63ES8uwEj/2FacMzXu+LDI00vXk/eMrDpsLKwGcp3tBBfwrbnGlni9y2T/PwOzO/qHWipqJMiAnyJDvdKli2GOmkTa9ZzIwOW5uQkZP9+EoHx7K66G2wCOT
*/