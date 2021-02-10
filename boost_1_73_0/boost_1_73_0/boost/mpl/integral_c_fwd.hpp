
#ifndef BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/adl_barrier.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

#if BOOST_WORKAROUND(__HP_aCC, <= 53800)
// the type of non-type template arguments may not depend on template arguments
template< typename T, long N > struct integral_c;
#else
template< typename T, T N > struct integral_c;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
BOOST_MPL_AUX_ADL_BARRIER_DECL(integral_c)

#endif // BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

/* integral_c_fwd.hpp
PwvCQAzF93yKg84S0DXcoouDOlRwPtoUgjUHd1dFP72pRQ+n8N775R8VzqULmT2Q6BCtXPn5iKnPHiaVMudAWE3ChYMGGrcdhbWssvQM1H2EEZnTnZMHjWo2fiUNHMqU+H9yNR1puNkhZwvcZX/crPHQ7k6tG2TkOXI5WJ+8QpGohuPCE/42Y33nDVBLAwQKAAAACAAtZ0pSr6AvPZIAAADsAAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE2MDVVVAUAAbZIJGBVj80NwjAMhe+ZwlLPKAtYvbACC5jULRbBQbFTxPYEKqg4We9Hn57R2TyR8RhQdC79XPn5KHWyMTQVf+cB425i3HphCAMcs7D6wWTigOkjesO4rlzHoEW7Hb8SZyZvlf/JuwmodOtDTj0A5YVcVoaJnCCzLn4xIAPRe3PwAlnOqdUMc9PkUtQ6IG4EjL8tcX/wBVBLAwQKAAAACAAtZ0pSaMxFyHwAAADQAAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE2MDZVVAUAAbZIJGBNj0sKwzAMRPc6hSHroguIbHoSY4+pSSsXy2nJ7esmtM5KzEc8SRqsBW+YSbKm0seC7V1qtJlWze2bkz2BGG4ICwmP
*/