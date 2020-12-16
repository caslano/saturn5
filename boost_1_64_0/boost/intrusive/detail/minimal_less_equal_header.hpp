/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <functional>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_function.h>
#else
#  include <functional>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP

/* minimal_less_equal_header.hpp
5zDG405Btlbqvtps1TNk2+VCRqIrPMHt0rUNo8Npe1tkbxyJ7MxH2yHHfW7tlrhN21/aKZ9RZtIkTNIMKHOlDvi0NuZvDiP+rtAy5+YxHU82CgsqsznnebfEi3WtA3Tq2I6zfsd9X66jKG+bwLUPgee3pT9yCc6Lm48bRNw6t7IWWlvrLuGTiHtZO8B3iEeYa1nR6ex9XNWCcpH2lzIv5jxp+3Z4H8LHJxPeup2595PIZOBvhf8r4v2BsK/12nmX35fi5iRFvuewWUfmnPnxun6ji9ZJutZJebZLnciwdfj6WCJxjnepD9XHf/X9QKN7Jk+IJP8+3Tyvn+a/r+a/xi3/JYtKKhvI/30Sp6dr/tFnjkvSZx193m/SvA/WvA/CDbDao1veGYLncNi++VOJkxHYl0dQv+b1UR0b2v+dSlqZ00LzI/1fUUFlgSey/g8dWn/2XMa5Tt83bFrYvo94R98XyDwx0jPLWhqnZVQlcdrvZYUpq/R7Efb16Aju55yyjpdj0a5lzToGZTX7vbO0rFu1kO1VSRJuBHGzw5VVH1nC9X1iC1fitnUtP3qdve/SfbImsrgKy07mmpRckYl3rQfim3NRdQ9H931Vs4+izlK1zsgjYZpHlZV0jH0YzbazISH0OjkDveXh6rOismxxcWRtp9xoOxM6WrL1zwhVDVwn5UdRD3bbIT3CKgL2clzXOnReSEvro+80e15I7pDM4c72iPp808h8EKN9XJrU+N6I1dOOfG9E8hKyNyJphuyNeIjwXQ3sofeX1lb4iC97npTzxfKrN46bnXag1XUM6pwt9rV+9UruRw+WHv/+tz+qGf161yc+4z7U1grf9PasLrfmPxR3VfxOb+oXDzAIvi/BCn941iW5B1quue/yDe3rdt5/w7amz7d48sdW+NWexFcr5ux8+fDsNe//4OCbo7/7Pffc52c0fZ5HktTnygduf/WdFzMzV7w4o6rk+vsPNH2eSrh5J+NEf2XHaz5fMe222Vf1nnln4uDY/cdu3k9T9+5zn/fT9PkoH8t5v3FI5yEL3654Kvuu67669teztzU8T2Uwjj95ztyBHNUj74AbYDvcl/r7eNwh/d0V59gYn6LzCLxyLMDGeLGO4y+E3eEi2AuWwYGwQucHLNH5AUthts4nyNX5BAU6j2CeziOYD8vh7fBiWKPhd8FlOo/kUp1Hchncqrawn4fVant8BXwXXgn/Aa+CLcjoD3R88RrYGV4Hmbsh+rvBtfBUeAPMknAdz7ffw7Tf3xBkm5/xb8dWXjwcbezVt0vjtdZ45h5BPTVeLxin4/oJ8GSNX4Wr0/glGt+cxzFV6z9bH99mwHYwR+cTnAt7wFydVzHLo3um6bjw+WrjPQ+eBwu0/udq+ln2szvsoum3MNpUZ00/XdPvCtvCbjAddjfqoUb19HOph+NUT0fYCR4P+8qcEWOPHY0/WOObtgoTNX47mAzb6/yVZJip8y0GwVTnfOKmhT+fg/W8DNHzOdSIl6Xx4l3i9dN4/fV8DjDKn63x2ruUf7zGOxvKvRgmwUlGuuUN5PdUjX+a5vd0c/xW47XA7TDHq/V81/kiG7/dzISMxDJsZE9mjBF3E24jLncFY5Fq87EPx8fjDuIvJXwtLnFK/ZgvSxU9aTh77HcEv4dNQQduvRUG1+HyCd8yBUfYHrgDfgUTpjIGyrF7cTtxewnvQ9hhfiewUc14fqfD4HHj8qmQ8Hzytnaqfxy5Cn8R3IK/Drce/2bcbtxXuGErkcN1yyau2q2cD1cSts6Kz++tcCN+/xg04YRtwiVfpePRMB+3i7AR+A/CKvw34exx6rRp/rHqDYSthjsgY9a0T/TDbPg+YVU=
*/