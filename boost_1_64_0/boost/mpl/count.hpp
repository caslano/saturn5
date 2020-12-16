
#ifndef BOOST_MPL_COUNT_HPP_INCLUDED
#define BOOST_MPL_COUNT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/count_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct count
    : count_impl< typename sequence_tag<Sequence>::type >
        ::template apply<Sequence,T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, count)

}}

#endif // BOOST_MPL_COUNT_HPP_INCLUDED

/* count.hpp
qS05G/y1hm4wlpZGl0V8VKrkJq5k+Nhg8TESow/BeQO0sTHVOUuRSvkj/siPD4eXiKxPe7rWpxnQ/z5S8rU6+v54aiS0wTqXp8T70N/YhygTrhKTY84WdEUPcm+OsrZzby7+g/TmZM3Q730fA6OcBKOVfxmx78xKOIketQ1TlEIjYnO/Wnb/qnn3jwRpWZow9/u3H/huN0Ga8x+0BWM/QSqzOa83Fow9Ji5qe9aqI+9FVxg//iud8VU0WgLfO0vFnu6l4oJj2TKuD3oWWjlEDR7B525QtWU1/eSMU//lzarfm6T+dx5vfv2yfuop66ek83Pc+uTz8xcfGPwvVvjXJsK/LsnR27qS46Hx1qrr11XpmsKYsjR+A4ih3K2GO/SlJrQO+DHufT51M9R4/D/dr/DPYKagnBrprsNVvBgShOuAMF/9uE3HryXMS4gF8P2gv3XFr03jZsid3tIM3AhO5UdcC1aiGNCoQPFgoob6zIqoXNBteAobhZVi6gOZasoK/aQKzvxWV5okjn9b1bg8nWw3ID9+8b6WH/f8pUnyo6vyVSCOY92peM9zzHTS32yuCJHxaas+fvpXgmAc/8yOte8dqiD+cdUuN/9I3Z2Af8z8smn84xcVevxnJ5q/2Q3yj82zaf6iBR0e/fbzN1vmb0L82jYLP28S/K5d/63w0/2T9rNE/cNpyxIPQOm/oOm/1UU0bMiDVJXaGq3iIR2tDNICMExWCktlRiPyr6RGoNDTj6ARTdrENf5vpHDao15zj5ffv55gvAR2NjZepL9iN03i8fcmxr/2583CH/RHwaUPJaQ/0trYQv8k5//e0/N7eqTJ83uumt93qfn9PM/vAXu+7fyuUTjufSHp/M6Jnd+dCV/7jp3u/uq+K0F/3f/XA02a36/v0/MnJ9H8yWlwfq/6EXUdWjB0XfPnj/Z/aFb93iT1P/ez5tcv4zWnIf0A0HuuSdQ/nLb+wwbnd8A1vzdgfteqUvufSzK/AzK/VWZWgoqokSi09+FmzQ+9/0v6rj39Ffd4+fzVBONlzQcHmji/Y3cf4/H3JsY/o3n4g/4ouG51QvojrU9lg/TPcNH/adC/TpW6cGMS+mcI/VVmHmTFhD8KTXqoWfhr/9d3iP7vb3PTv3hnAvpftrWp9M9ISn/B35sY/+Vrm4U/6I+CPVclpD/S1u9vmL9e/rbmrwVN46/ZdLvURl5/b2bmumdXc5mrC/+DCseiZ5Py19xY/voiOcPZx7/s7q/tryTorwVVB5rEXy8neBzvJxF/y22Yv86lrkML3nmw+fxNr//ebE793iT1n/st6pfxmtsQfwX0nfcnX3/1c+Efv/7K/Q7rr9zo9ddbTzV3/QXc1/+pQf6T5eI/NeA/ngcU/38qCf/JEv5T4/DPedQJKLR3VbPmr+b/exX/3xzF/19OMJ6H/PlAE/lPVkz18fh7E+Of0Tz8MT5QcN3KhPwHaX3+2CD901z0rwX9/arUhU8moX+a0L/W4Z/XEf4oNOmnzcJf8//fKf7/UhT/35qIn7zZVPrHnjWPx9+bGP/lDzQLf9AfBXv+JCH9kbZ+n9A/Sfv3aP+J1Kql9B5rqwQNgiXnLeMrQhffrJg+bTcVHW99hdjZo6gZkqY8PkJ2CNpygL/u4K8e2SylD4s26w8n7CleF1lh/U3gcICqFw40Ozhr1P4H7WuVSyRZtuWPBQuQ8H/J5UEW/J/ewP5hCFs3PgezOhVO3F66N2Y7+L3oSxVf8Qex3SjGURByQg227mqIi5EnfHr5Sh2bajONsADOkRyk62BgxlxAZkwyeF4KG03K2FrYVWuHT6hbMIF4ZOnWDDIDWe/EYIXh2XK79ka21dVgxVk=
*/