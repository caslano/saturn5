
#ifndef BOOST_MPL_SET_SET10_C_HPP_INCLUDED
#define BOOST_MPL_SET_SET10_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/set/set0_c.hpp>
#   include <boost/mpl/set/set10.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set10_c.hpp
#   include <boost/mpl/set/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, 10, <boost/mpl/set/aux_/numbered_c.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_SET_SET10_C_HPP_INCLUDED

/* set10_c.hpp
406ch7twP76O2fgOHsN38Qvci+dwH5bisffj/XgAW2EW+uFBjMD3MBYP4VQ8jDPxfZyPH+Cz+CGuxWzcgEcxE3NwF36Mb+ExPIjH8SP8DE/jCbyFJ7EqdT2FzfAsdsdzGILf4xj8AVPwAk7DizgHL+F8vIyL8Qquwqu4Aa9hJl7HXXgD38WbeBh/wo/xZ/wGb+FN/AUd+Tv+FZvib/gg8kJNGWIPmIx2OBvtcR6WxsVYBlfhXfg8lsVNeC++guVwJ5bHd7AC5mBFPIP34a/ogFV5XzhiM3TC7lgJQ9AZk9AFU9AVp2FlnINuuAir4EqsimvRHZX3X66dHFfleKu8hoP5WWkbnVwL7oaNsBY2wQbYFJtgc4zBFpiOLfFzbIXfYmu8gm2whlzb3QA7YCvshD7ojT2xMz6MD2ISdsF1+JC8n7rhV9gdnShjD6yBvtgIe2I77IVd0A/90B/7YW8MxT44EfviNAzARTgQN+Eg3I6D8RAOwQs4FJ14XYZhfRyBvfBRHIOBmIIjcREG4WYchbsxGA9gCGZjKH6Mo/EbDMNbGIGleJ3GYGOMQS+MRR98DHtjAj6CiRiISTgdkzETx+F7OB5/wAlYnc/mFGyIE7E1TsKuOBl74xTlcXEqDsNpGIfTcRam4lycjc/hk7gV0/BtnItH8Sn8DufhfXzmzcfmuAAfwoUYhotwJi7GZ/EZ3IJL8CAuxVx8Fk/hMvwWl+MFXIGleP+uRFdcjen/8+v47vRr+Nyqcg1fVe084H89lUj/PzTYZuP/71Vd/x8l5/8nku1lDnxPDlYtTP1/nln6osWYZ66A/qdcU2/sa0rfU92vbOfYX74v1mmr09+ON96+s8cYHNZ/z+7xVttNPXSeS2ZmNQtO9DnIlwiZ20nalLaWMQbquZ0cVWMMGqEz+qEr9sfKGIZVcAJWxboFjEHgc9A4DmGRu/b5oyUtaUlLWtKSlrSkJS1pSUu2SiXS/w+OjQ+1wfh/J115xyAmSqWLqCMyF0pc27StfP62luptDvnbPNXbnPO3tVJvc9NvCzF7PPf8bWaPVzN/m9nj1c3fZni8l7ld0yN/m5dsa+XNtobKtvjg2BidPo5RXnUdQ6bE8wPos1fEvtiafRxeMcYxQkJVMQwP9etngxiGYX2zxFayjpphDnSdac76tCrcjsy/fULunyD3P23Yn8ZSr4+WILfPGn7vKXOoG34vt/MMv28h86Ubft8iP4bS+RWzGIqx3c7K3P5p0m4zpd10r5niPzH/4nbL+4N2O/sH7db8NbN2M46byZXKV8WK6IIP0G4t3jG2G+sgGN5zgVRX1g4opP2cVO03NiE03k/GYpSX+Jh6fnwH1byVTqp6sSRiHJjW1CstbWd1TQ3zefjPy+2ExKDEsQnm9U2XtQRO3s2+mItKffsdMKtvaIxFfcv/TfW9UYT6qtdNkLgh1zsVFL+zXTzR+ngE251v/1UfZ3yu9an9Q2cd9R4U5hjx2sBRo4sfx7ysI5WSz0j57NyD1clX5IXinO2UingC2+JJ9MavcBKexj34NSrn38/gQ+hZmrglemE6tsdr6IM9qW93XIm9cT32wS3YF7fjw3gvn02DcTg+ipsxBO2U84Z4N8ZhGCbhEkzG6zgRPZTzfvgkpuLrOANrUM852BfTUNpBPvPYZqUdnKUd3KUdqks71JF2qCvtUE/aob60Qzz2x0RMx/F4Daeg0g5P4Eqci+vxKdyC83A7Po1KOyzF4bgKN2M6Ku3wAt6NmZiE23E97kAX6vsmdsfduB334je4Dx+hnodwJh7Gy/pxF/IZJp9te9CZnCHtkGdHO+A3WA/PYmM8h63wO2yHP2AsXsBn8SIewEs=
*/