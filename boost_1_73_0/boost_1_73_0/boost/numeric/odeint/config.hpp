/*
 [auto_generated]
 boost/numeric/odeint/config.hpp

 [begin_description]
 Sets configurations for odeint and used libraries. Should be included before any other odeint library
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED


//increase macro variable to allow rk78 scheme
#ifndef FUSION_MAX_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 15
#endif


/*
 * the following definitions are only required if fusion vectors are used as state types
 * in the rk78 scheme
 * they should be defined by the user if required, see e.g. libs/numeric/examples/harmonic_oscillator_units.cpp
 */
#ifndef BOOST_FUSION_INVOKE_MAX_ARITY
#define BOOST_FUSION_INVOKE_MAX_ARITY 15
#endif

#ifndef BOOST_RESULT_OF_NUM_ARGS
#define BOOST_RESULT_OF_NUM_ARGS 15
#endif





#include <boost/config.hpp>

#if __cplusplus >= 201103L
#define BOOST_NUMERIC_ODEINT_CXX11 1
#endif




#endif // BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED

/* config.hpp
B1R3+x+KXQTB1cWZf3o288jtNdJ4N3qwsw5zhnjUE8FoOvFe3jJrNFcaqlJ+NRd/DODUD3zPFX7fVX7VWG3RYNISpTOnTBKrsd1rarMSbYqnEX17QlSh67xbd+1V0cNC7iMfuiz+A1BLAwQKAAAACAAtZ0pSr88VlWoHAAAEEgAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU5Mi5jVVQFAAG2SCRgrVdrbxpHFP3Or7iiagMWASf90IeTqMShCSrGEZBGkSKtlt2BnXqZoTuzJqjpf++5d3YXbPnRSsUyj9mZ+zrnPmZw8v+9WnRCj74i+Y/wwqeceF/YP1Ti794dRV8p/OHUZ3w+pmRAhyNfoy49fuQrdeRIVGl5wd+j6DFFn9k2fhvwyc8Rf8UKjvHJc7vdF3qdeeqcd+nZTz/9SE/p+enz0x69iY1WOc29MktVrHv0IpWVX7L4y5e+U696pDzFeb8Stci0I2dXfhcXivA914kyTqUUO0qVSwq9xA9tyGeKVjpXdH75/tN4+rZHu0wnGQvZ25JcZss8pSy+VlSoROnrIGMbF57sCschPNXOQ2DptTV96FbkVbFxLIPVx7mzFF/HOo+XUBR7yrzfup8Hg6Qsclg/SG3iBkntfj/z
*/