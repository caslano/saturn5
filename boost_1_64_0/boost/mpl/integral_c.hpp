
#ifndef BOOST_MPL_INTEGRAL_C_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

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

#include <boost/mpl/integral_c_fwd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__HP_aCC, <= 53800)
// the type of non-type template arguments may not depend on template arguments
#   define AUX_WRAPPER_PARAMS(N) typename T, long N
#else
#   define AUX_WRAPPER_PARAMS(N) typename T, T N
#endif

#define AUX_WRAPPER_NAME integral_c
#define AUX_WRAPPER_VALUE_TYPE T
#define AUX_WRAPPER_INST(value) AUX_WRAPPER_NAME< T, value >
#include <boost/mpl/aux_/integral_wrapper.hpp>


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
 && !BOOST_WORKAROUND(__BORLANDC__, <= 0x551)
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
// 'bool' constant doesn't have 'next'/'prior' members
template< bool C >
struct integral_c<bool, C>
{
    BOOST_STATIC_CONSTANT(bool, value = C);
    typedef integral_c_tag tag;
    typedef integral_c type;
    typedef bool value_type;
    operator bool() const { return this->value; }
};
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
#endif

#endif // BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

/* integral_c.hpp
BmvFDHCS86JW3llzg5qBm0rMgCpA8eA6FsqPYCldcPg3qeEL5VveBPqYPKPFxaV/ccuzXPrJ/+T4301PO/4XcvK/wUPif4GS/O9Xj4X/fcHF/z7p4n8hJ/+bVcD/5j1T+N9nLP7XV5ymP3b+1zct/vd04STWacbJh30HZcNjN1hs+JbHwIZveexs+BaLDY8t+79gf+dVutnfjkUF7I8FmfmVRc8o9jdw47Ps7yn4CP9bSP53vZv/lXihsqmSC76pQlA3dU0l1/yaCkFuXZIUDTEzi+xnthBQLcxRLQRUC3Oce4y6M+g5isDA8MhtvsVWfOQlVhaVMeh0pFinrGJYVYwldi+gKuhlhNwwQAUSvdPLvYzwymDp7i+zul/jjgt6Nm4FzikaF7QctSovswI0r3HHBT0btlTn0BSzAv97V5fjDU56Id/ruF/qnL3STH/K+VJH753rPvWU7R1L/6ENS1/2AhIdRu0MW+E6ty+vKxctx1c9BQoX8w/XczwyEcsbkC5akXbtd9tSl9TwFqQuebqf9GNecrnBnGCyOcAsI3l60KKsfNkxX03XfCdl5bM7bcxsXlJOOcVSnTB1cZP5dmcqLPO1lGW+1sqgekgayBUx6608Fu3avLg5V8oMuRtkT1Yp829+5nF+wmL3cIiKm8f4ycX/+Djel3xCLwnX0Gy+zvW+pLGYe2W+NTl5DV0LJ6PKyS1uyibTdYlP5xZ4ssl85PJ9U4ceTlTgO4fvXz6W5w86dOkRsj0uDkKXxq0S9qp4rcpUNAwzD7D/tWT/u/dqSyAEmzRbQ6I4Hltp3vh8Yic3FVXG2XqMzFyjkq34wYZEGDa7dnh/KL9RoHtFrSnuv00Ve+wNLK0NKENSeqhzjzwX10ndSLHFqH7WyolRaCnWj67vEB+abKk32tfUGuiN7UBq/0rzCh+ZvDUAtI8RdO19Fc4GOBnYQS2T8VudEsStGNBtm8fKeluq0fBrURcNb4vePmVF/bq1J3r7fSPd0dtzZte3IbymBAbrw/Pj2xds1gXvz/JtwHWUa6pcLxiuozDGFEV35n3iKaM7DnzJJ50n2Wbuve+0FKmGJqD0dn/NwulrSgUf5/H9U68TH7dF03pqgz3RtExtGn6GQtajnVHabzMs95r3yv9XvpBG3KMw4sZ0pxdspjlbbVq3IYZnLeXp+x4WgzR84ZMelK4BnkoUN6MM6QZaCoEnIANIMa5SrWdGBhrHM6N1amG6PvZYF8Z+L/DoNftKxzM9xhGJLJgLEha2niGx64PF/0X7efF/j5PNq0La9o3NQEhb8Ql44ZaPqFTZsa1eejZ/z/4pWVeNm1IMC4tnBJgKvQklJFzw4LHIbHpYDXhInsMqlO/S+OSlEhGUJraBsmUNY1/XEmxw6fK6i5sVD6pvrkMgzK69jPrTVMcI7nWtV5AMkhPUoQFbRz9zLS8WLLpJnf5Z1sv+0xv4xCu4+mRMtnTKKr2NPqFVk2CWMuVngBn9kIMP2EuS3k5IJpPNYSe4Bx359D52fL4/99j4IPxyxCs+k/aIh2g6jJ6oimcRWS4qcwITpforxdZTgiHn4OyfTohmu78O9pe14tu64wEeUyIeYN3jjgf4jsKQknR6zmCnOvgfn/cxWsOkBLFVT/KSRvqBA8Q21VvpRkL8Bndw0fk6tumEhlAH/GNXBWPjk8LcxOLKfp4gQE36wkhfaP1euhvKyj5tZsyrIwoH5QjyV3coQf6+ijAcT2mQPzu+37ndTnqcHwShl85EAuDteDtHSUU8P6sd9wqI1gx9ExzGJmUkZpY3P5oiu4C3kDCM5diO+dBbefOHamXiNJrU9bjU9KmrwDuf9q8fccNbB/ZLPyE=
*/