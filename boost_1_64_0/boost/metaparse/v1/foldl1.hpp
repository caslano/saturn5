#ifndef BOOST_METAPARSE_V1_FOLDL1_HPP
#define BOOST_METAPARSE_V1_FOLDL1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl1
      {
        typedef foldl1 type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldl<P, State, ForwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldl1.hpp
frvIL5Lln+vU/BL8c8dt/9wCfLnx8+bER3sMn2D8ebw5f3lVqNv/Hm/yeN7jBY8XPR600B56PIW3Vu1Dz/Zpj2c8XufxrMfrPd6Ay/Wx8LsD5z92/A2/U8xPaGgZyvp1Dq8W3uTxvMcLHi9q53+0h3hn4bW4mv+WxmX71XP8rMfrPd7g8UZP+Zo8XsDl9fd40Erfnym8n/A6XI7fRF6pfwSX4zceb/QcP+c5fpNn+7zn+AWPF7XzIdPHDz2e8ngtLsfvPJ7xeB2urm/Ws329xxvw4SK/6dX4fq7b+hvew6mf2vk94TZhsIF/HlkV+7ZMiKmO8sPgHxkfiUdHm4n/3viNePQ2uhyfZrxqjlM/3TYMzmv5/++vIaXynYsfgV/o+OTz4vlBc/FRxm/DO5TKNw8faXwj3r7011X4nsaPn+W0/6o9zwcunw+8KOrfq/EvRf1767Zh8Jzx0ZPjo22DP2v89WlO/EDC8/zgXdT9j/cR/S/1Hs95vIDL+fPJkPZL5fkfA/G9TXzbLt2c+gHu9g/Y/HBX448Gtv6NRfmx8Icdt/nhrscfEOODjaHn+4b3UfVPfHvhYbtQ9k+mcVk/xGX/Li7XP/V4Dg/V84Or/v8CfrEYX16N/06ML3+I/1aMLze019c3h8vy47J94dk+6ED9TXiI3y/eH+3wnGq/4+r3DTt62icer/V42uMZXPave7ZvwDsJz+FJ4XnP/gseL+JpFV+P7y++zy22D4Pd1PgwrvY/HFf7H+fZfwMu5zd4PI/3ER7soLdP4aPF+dXgh4rzq8f3UP0DuMovvhLfQ6yf8izeV1y/cMdQrv+f9ngWH6DWv8P7iec7h3/ruI3PWop/7bjNX7sM/8Jx27+0HP9UrI/4GP6xWB+x2CkMPijVPzuViW/YhOdxLHLyl8X5iYPOYbDS+BK8Ouo/xJ80vhmP4lOq8Ycct/nLMl3CoLtqn+ED1P2Fy/4n/FA3vszm7+jK/aHG33HZP4NvI7wePzOonJ/yUnyKs76gjX8Lu+nvVy3+uZg/sB/+jpM/zu6/rrun/YzL9pPHGzz7b/R4zrP/Jo/nPV7A2wkPevB+V/n18KFifDCDf9NC1C92DoPxYn5NO/wYMT8gjfdx3cZ340sdt/W3ufh9jtv37zx8sdh/XS+un7r/8bbCG/Bq4Y14L/X74vL7t0so5xdU4YNU/DZ+m1j/diy+UKx/Ow5fINa/PQK/Wbzfj8SvF+/3VG/ej+r7jav49DrP9hM92zfiqv6Yx1V8+6u4im9fg6v49o9wFd/+Ma7i29N9wmCiKN9w/KQyv29UviPwMWV+36h8R+Kjyvy+0V/H4cPF79uEt1f1Y1z2/+Eyfn9XXOVvi718fghc9v/hsv8P79zS9k9w3JKPxqvxrWJnflIc35nBtzb+Eh5Ez9duYfB01ZbebXx8tjfgs4xfgDc/X/3C4AzR/q3Bs6L92xM/XbR/c3gv8X1ZivdU+Stw2T7yeNBfe+jxlMdrPZ72eMbjdfj2wus92zd4vNHjOY83eTzv8YLHix4PBmgPcTX+mfJsX+vxtMczHq/zeNbj9R5v8HgjfioPe6X5Z7fj0xy38VGL8Cl4pflni/ETXbfzCweGwT4qv9cg2ndO/cy2P7fB33LcxsdX4y+K+l1qsB6/q8WTwjN4Z1G/GIvvKOoXWXwn1b7wlK8R767ya+FdxfHznv0XPF7EewpPDQl1/DOu9p/xeB2uxqeznuM34LJ/Cu8k4kfznu2LnvIHe2oPcdW/WIu/3CLe3vZ/jMLvwsc43ueYeH7SaPwO45ecEc/vGIPfbvzvePP61fhexoee6dTvfhYGq1X+A/wDx21+1/fxFY7b/K5r8OU=
*/