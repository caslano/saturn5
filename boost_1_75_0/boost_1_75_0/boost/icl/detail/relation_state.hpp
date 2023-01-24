/*-----------------------------------------------------------------------------+
Author: Joachim Faulhaber
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------+
States of comparison and inclusion relations as static constants
+-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_RELATION_STATE_HPP_JOFA_090214
#define  BOOST_ICL_RELATION_STATE_HPP_JOFA_090214

namespace boost{namespace icl
{
    namespace comparison
    {
        static const int less    = -1;
        static const int equal   =  0;
        static const int greater =  1;
    }

    namespace inclusion
    {
        static const int unrelated =  0;
        static const int subset    =  1;
        static const int superset  =  2;
        static const int equal     =  3;
    }


}} // namespace icl boost

#endif // BOOST_ICL_RELATION_STATE_HPP_JOFA_090214



/* relation_state.hpp
+W1A52F7pRDQ56WJx01QR5EuD6Hvm/6L3JFHUlpvPMEghExRHxrNunVI7qotmU7odq0Z4nxKhaY/Clf4Ht2yilGUoz1OLVIlqhmvoC4w8JCe3RVnaRtfuTZO5mpm8PqeqOhr6/EomuOCuyfXJoGDEfTU+e9TIlV+pqUvYdmGfqfGv7zgCdhUPrB1aWbrShBM+MOCHebfTm9fnf2HRoKIUYFQVasq9/4sTbXL+2Vr37prvHrbiw7tqI/qdjQApEi3JP+G/xkHHvNFUUc+hG+z/2lKpMvPswbELbrAqOcXc9x9gruf5Lp961Ci4tW7GSSGXG+PkPKllCVpVwoGr/kEdZTXexfdTxcJ1LyssVT7q1A1dL9K+kiGNulaguph4ZZ84iU2IpVibCsse+Mjaf3BwmzyYtBzz5qawobrye3dU9OZ6RouIzc8JJ89hovSIofMBEN1//D+s4UK2cYdZt/GMTlyUbISNQsgusp01lziRsq5uPBmUquS2hRNKGeZWDgsuBarWlqXxfR8THkAaRgq4GT0sRm0XsT51XS8Lunja5LexADDJZbJ7tof/fwFaoMhUONfhOgoxOtj/sLSxccpGpdne28dOwVl3hvUZu67LtNRmcG7/YZbM3kM59Xkn+E9wX4IELdkOKsa799yKemtC+RYdlumbFq4lzLVLPBdQVSWUXryxIjuaXHnr4362XmlCOnTXp+/yyy70lBA
*/