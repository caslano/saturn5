/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONCEPT_EQUIVALENT_HPP_JOFA_090830
#define BOOST_ICL_TYPE_TRAITS_IS_CONCEPT_EQUIVALENT_HPP_JOFA_090830

#include <boost/mpl/and.hpp> 

namespace boost{ namespace icl
{

    template<template<class>class IsConcept, class LeftT, class RightT>
    struct is_concept_equivalent
    {
        typedef is_concept_equivalent<IsConcept, LeftT, RightT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<IsConcept<LeftT>, IsConcept<RightT> >::value)
            );
    };

    template<template<class>class IsConcept, class LeftT, class RightT>
    struct has_same_concept
    {
        typedef has_same_concept<IsConcept, LeftT, RightT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<IsConcept<LeftT>, is_concept_equivalent<IsConcept, LeftT, RightT> >::value)
            );
    };

}} // namespace boost icl

#endif



/* is_concept_equivalent.hpp
JgsClfbsZMqBG4Sol20rYzCBai9gmShzDlCMRa2KycPeGLoDhraiM7FmHdow2WEkbbQxHe9MspUUGc580ZiRlmk497ERczI6ya0ldNTTAK/mONOEp34KAqkDDI2h7RtC6yJOPDqU6je2b1gj8RopUwiT8lLeqecCqhkNgZaHxQ019lQ9JNeFmXOmTDyXYRnhDRG2kV48osU7lHikY4PQS1zoJd5Mv3ad0Ju5vJUN7UGzh1J9UQeIHj+U5VnlYDFXr1rVsYYBqCFglD2RCoUjXaFErMepG9OiOAo02hTPjeaa6Id7m+mrY6NN+JiGzyl4FLs5PcQlPYlLekIv6Qm+qsmLaXg1PVSTmh7FJT2JS3pCz+l5+KomL6bhJb0CZr39pNgTNKGDAcg7Fd0HuKEgDMb48GBUmoGHMX7pZEulfsua4CWdX3qgMJjEVwYWQ2zAfPkVbJ5H9RqMwUSuFKgVSzRsOE/XVpGpAnAa3Jk8AOzhHNMZK2H55MI20UyE1/bRtSkwV8YV1lwWk8TxSrVu9utYXa4XT9pTOraDNMUSu5ybkNEF8/ayCkuh14vFrffGuiKREixLCStA5h1KsTln+45qLGHAyStpj0FEJV+CRbQndTbMomWhKaOQEKt5r49nK8WnsR304PFUlN53T2RLYBzIjpqlkpl3J1pbMW+ZsMix4PgSMAJU88jNCHknlDl8ma1mfSyHMtGIN1qdorxmJ6uUJTOOKt0FANcJvBejojm1AhZveFI63GjQJWd+X6axmgmlDnUnB8Ox5G3ALHvxbWgeKa3AopjoVjW+AbbtBCvApZPGOFkroG9wJnmsr5sYUKi2q5gr16WI+CHLjcFqnnKUp4mmDuthG47VWq5aR0X66nZkvVuX2z3CSsp7t4ajbiQ3FB1MKPJQa9VckRRF1EeFsX3m8iVRt9lScwPK6kTqsFwdLZb0mhBaahF/lK6bbsJVT/2QSvO88anZitng+hRdStreHUwH2CEgtKMTxRIt2kRwPhXd4qgu+8KAK5kD5qRZErjMSxp10xwsVorlibKgmnHZKR3n1Ys7eWV4vj89YmKiKd2MnHxVRafs4dsquBUzhfnu1koR605de1Femh6UC3Z9DPYPJozBvpQKDxXMLJWZK8yDj0LBTPFXgmoqVIMdKWZLoTJ7eVRceaLUKBKBi+UfFpRm3W4ZKruXNbj4JvLVyt6yLQO+gwbPc00jgZkkPJaVInyC4m4Q7wD3FyzgaPZJugrvJspsyGSUcGVrPDHFFoqzY5iql4HpaCor78480MOR40aE4J19KP5yRpHLvPNOy8boEFs4Ny6uLRU2XCntdePDsvoUfL/6Tjg9vrVCvk0zD7Ait2843l+pTTRUGFklrPh6suPj3C46bhI+D0b74azpuFi2Zpcpxa4tL2+VYgMcnGMFHkr3pJQ400zPy27Q6TBrBth2wBjOcDtTTK3nldPT4EyuysntjmXreZrzDFrjM9UXc+lwKZUvjnm89FmOD2y7BmO5KszLhj98uw+cxXhwuLhZig5jCTqcJehwSdQfzqJ0nH99JWOOz5QxOpxr0YP3ZBu5QjRfLlaYyRfnU3ZqZNZXXeagGd09E27EHO/Foo8xHlzLtg5nYg+m1yXDsabcPa0uE/V6tc4gxQ5MOGMHZgY9Ca0fsn1gjNbHANRh1gywGftYwr8vAewP3z5zHwPWv4/5w61Z4D0E1/sT4H6waX0MMP++BLA/fLsPnMXo/YmhOsy3jwGuwfT60OH+/YtF+fYHFuePYzZd55lJ12MG6jC9bIDrZYPzEhuIsj8hpnhGvNfn1HzH+uNwdtBkd7oMDNfk046RZ8mbj2BmkSNIdRx7Y0205SI=
*/