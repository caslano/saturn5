
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag, detail::callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_callable_builtin,(T,Tag))
    };
  }
}

#endif


/* is_callable_builtin.hpp
OSdiwHZ5MQyLHwsd795mLl0uTI5cHs70P90WzBNjmAGPD5KmReswYwybob+5JKNrfIiMPtSIiyDnSbNQPzK6vo48LPsDZF8pBPqAuxARuJck/3CUWVvSF3R7w0l8z4NQb9NDptbOEVBrQXlypPkOKDpyKfN80SaiHKeGsoNMpH3mDSbkQG2ySb2JmO6VJe8FVCQJZ5aSfierkWWzCpCsgrUYw0Uj2RX2HXTXrYXfmqhhVcUGpPfK10wLyw5St+VAOGNYTYq2KgQ5t8LgWPwP3KOKI6HhzkHcQdW3MHF1aTB3PUUOt13NKIMrQYlpp7j6LY+SdsEZsLPsUkhYZoUiZdLh05MXuOxCPxPLkzDG3nY4rN7VlztVcjWEHz7CnRrTFm69LMfEtZxH7pKSZG//aDJoznhYlZ0GtxO+JPNsMTB9WRSJrbqP1GxSkiRkTCAF7u6E509HkVlbqkHAdTsx/PwLWdrrc9Kt4pfcgswIUmVBf67QqFIwq2MNpsnt11CpmR/oo/aTpXuuQ9qzZXCZOwvbjh0ky55e4Eitz0C59Tdm9Jqu4P8rR7SbH0CB1l25pG6h5LFfL+7a8Q/IvYJrSdFrq8iV8zuYUk2rwNIze7jC6UrS7EFXSBuTSsIe3ICt346GkV0bMpW++Q0Gf1mRq3y9KpScMpRZvmIz+XpvGHnVYytMGrEHupWLI43mPmfOzdBC0I7FJOP+ZRjz3UyAHSPhzuTbsGHhTIjav4Ns/LobCb2UBT0LviCbOwZD8u9HYCs7mZyt8AiCJ/fifh2TScoc+Zipt9+XFCyTBYvTC8A632nkXJ2SUD5oFhdaqTj0u9qaOTQiCxpUuAi/JOyHcj3KkNKVR8HCDmfAWPU6rPmCMC1ebYfzh9ZzaxZ1JL0W+sCus4thxUWAnKIsqbM3HpYv84fyMYWYZZuNEFd7Atx+dA1eZJaGR5yZ+DQZzBS+X5D0mjCfO/16OQkekQNPYrtDlWoNOSb1HPmuf394VTsMKuxrTMJ6mmDC7Q/Je4OrwqZut0kXvM64kViI63njI/iiSRtmtiad+Fa+xHx+eBoxfnearB23BKZNvcQUPxtOLPNrMPHJh+Abi5354nAP+GFPFNMmKBgmNzExe55mkUk5Odwi8xH4REuYCf4psC8rgow+toAs5TZx7Ur8BtV/MXNVf/4bw+bB0AMXRvFzJcooioYoRMhqkFGikMxKVmmHl1LKqEgoDVRGqcgKTUUKDRUSSaShoak0VEKFFt3n/X+Fu55zfudcHeSNPszdtV5RvWYa7zZ5Bfcx63nImA9YzVXY18OfqThCh+UZ2mD6yzR+eflU+HfqUOVFb1qsNJe/cSvB/qRoiqgbipoTrjzKPoI21/SxrsQzuBgoTXHntiDi7Cb64mJIC+S8abmVP10ZmIHMa+JoVQ/lM8VbqbNZlM4mytH6tdasqnQk/ITvMPv0Mgzpt6eZ3XqozpOF7I3RWLnZkF71S9OlcSFQ0w+CxYbLTOavDhReSCOt9C25t91hvff1cWd7NT/ha4JbI0fx6H2TsFauiTm7pZLuXQdWemEk3foay+iUKZaILeUmC0bQoMhdhkslNMJzK5v3RA7/nYngJzKLaariAVRUy1DpyHK+W9gFra996HOMA3033EZ6/ha4mf2cXRNXJ/Fnh7DJr5D6R8ixJx5tsEwYze+V3aYZHefI0nw7PTtlCQ/xD4gOvYVG8Zv04aYbKQeewu5kN3bd4TSqxObw3tgPVOo0EU5jm8h0zHT2um4/eKExiZr+ol+/EzBhxyEqOHwMz1uy8XjXSFY53YrCN13Ht3YF+pCcTCEv/iJlwA89UvtwPNuBhpSEUNzYe4CVIx0RFWE=
*/