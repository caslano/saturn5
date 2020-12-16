
#ifndef BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
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

#if BOOST_WORKAROUND(__BORLANDC__, < 0x561)
// agurt, 12/nov/02: to suppress the bogus "Cannot have both a template class 
// and function named 'xxx'" diagnostic
#   define BOOST_MPL_AUX_COMMON_NAME_WKND(name) \
namespace name_##wknd { \
template< typename > void name(); \
} \
/**/

#else

#   define BOOST_MPL_AUX_COMMON_NAME_WKND(name) /**/

#endif // __BORLANDC__

#endif // BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED

/* common_name_wknd.hpp
fTFm3WqberE4rz8TraVrNDV1ky4apGaYHiLJx11/JhaQM+ASELI106T8//Nz+Ij7+9gq/qxDIZYO58960++q+L9GTP/pzsrpyw9FSn/J9srp90VKz/rBJb+T/H1DsEBJYDFgNcO78y/69veouP3dvVLuznJHZbxZNwAGmwY606HK/H1eHTqq1ddAM2UqnJhPt3F+TO8FMpSzxusf+p9Ddv/gFpD6RsJf/eCAPf1fvoiW/rY37el3RE2/6Q17+rnR0vN9vvn7YvwTtUh1t4NxcyVyq4dMdI9J97gj8H3ySu9H9ttPoH8dWefCQQVZaERFpFhj3yrpQbcEuTz+MZQiVEjhRFwZE52WE2wXSgnxpXyXgXduxlkS3BYDCCTQv46s2/wnWUMigTcycEdy25H+vma6zXGDgRVI4d+PUfswTj8eQK98g7DKYPp11Wb201rFJbNEh8ouW1yl7CeZPdDDRVaxA42UF6Tn4nJZ9lCUDcOxz1lkZQVboXIXB5eLiDzAAtk4QBY0FAUl+oZZBT3DBQVEao//ZRK8Bs6iPXpNP0H4NyvD24N2OBIZP2jwkej2n/NeD19+g63R8688FAH/53D0/HdEyP9kNfK3DZ1/y7aXguwTlJE92R+lvEyk8DtmVORjWKGVUQ5zG54TCZSZI9trNn+3WOMV1H3akoam+q42Ul+GseqdJPtfskOpmU+GR4H50GFdZHbbkQo+caiLDJquDPMmjlSWcM20D0tnFlUDhiBX1DERvVIYBL2tLKAhLjZx/QJEhuWlGYHevuu57T60/bPtNbDpmg8dTCqFOkrD/aZcwgQ6nzurgldBv2P2KHn9OW+Hktcff4vem98UhZP376T3lfDf3410Xs9HerUKR3wc5bxg++/fRV/Pme+HXs8exH8kh13z4CuWqWiqr5exZi0W2h00WV22BUNilKqFVoqFVoqFdsphhTpxQ5VdygstTh0V5WCxu5DoWRo/ICCmNNeZZDcxoWH6ergjRt3Y2I9VLbffqzfZV/scvFBge3YjsyH0vK0v3d787DfQfGimPnpPLpmAjwKJPEjLSRkQDfLdxJnuRaYenAl16wVablug5bYF+vULWKBoxmRdg9v/RzoBTs+HqyYfLZ/9+LdsL9WvC/Fh0rkvkYZdhXntgFFjwdCqZ5TisaFwA/LFqGG+lgVBgV3VRGOw4d8diL4ef/tecVS8tFbYVaHx0loeiJ7/9s3h85et0Pmr0t8lezB+GQVixUzYgZSwgpOlC+8a0wPjEgxNtPlI36P9DxC7s7aAhN+ZqlWwHgv3o/abutQI+P9v2dp3ZHvo9v1xQXXax/Ff37Lr93Uza5GQmCN3Brfxjh02Zz1KhrMJwKPn8unipRhpBxX7ZBQ0ifFg7xUlghBUW26v21fX3t8vtoXu79QXqtNfxj/fHWo+uoaaj8nbdakR/H+pPB1o9dfL7Vp7MKRrKVFVV1tQCyPBksvP0M691J15CTZ3Ww6XVgr6qFb300+hZfYggv0AoufMrs9T5s130jZmHFf0s76vQr4h0x3mSHCOxhRgw/pHnVn5u4V/u8s2f63fCD1/exdWZ/54/e+0r/+tocvrsLY65bmw/mV55ruPYSAs/KDN9No4QaeCMUN8m81GF202KS+hFAWxTdmZV7oLUNvVopi6Px2o/gKxa/5IqhP23C5I95Ijdx38VButBSpiZHod3Nfsi4XiDRgw41UeSUXoibVcJJ6vVy3Ly3wXoV9sDbuI+zVgI/qFq+a+9/iqyW4wLjNxOd6dzmmm5QtXvin7+6U7qL9Tagf199yQ/T1/PvfMTK/DHU+1d1z3914X3taksdQ+aGdTSPABLQxtmUQIKLwwVmg=
*/