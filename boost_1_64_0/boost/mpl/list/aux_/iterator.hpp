
#ifndef BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

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

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Node >
struct l_iter
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
};

template< typename Node >
struct deref< l_iter<Node> >
{
    typedef typename Node::item type;
};

template< typename Node >
struct next< l_iter<Node> >
{
    typedef l_iter< typename Node::next > type;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< typename Node >
struct l_iter
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
    typedef typename Node::item type;
    typedef l_iter< typename mpl::next<Node>::type > next;
};

#endif


template<> struct l_iter<l_end>
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef na type;
    typedef l_iter next;
#endif
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, l_iter)

}}

#endif // BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

/* iterator.hpp
Hflsn6b5u3b/PZHfdsyVe+RJn6OukxJHGuXM2Ez2rtlkIbp1G2bQH0sT5WFiz0ldqpPuU5fgdzR1MYUfOV0XZ66rjPWVedZtr933MqS+BUmusg8+oL4plvqaBv4KIkotC3Fb1udSbVn9CsrYxVJWPtJDykq1KYtP6ccsy7yf35Ky6srndS35cew+taysPmsxd5Fv3rV9PnYu9kFTZW3HOlH21WTyyGe2rl595DmFxaQNPEnKtZr/XE29Ep07z1q388FCts9Ez8G6B2vKSBg2MDTWGOWU9Xa2d61bv7D9spKsyzJGMsWHRj3mta65/VZJeeNknx0t7ZdiKS8mOiYr21XXfpmOwdbGw/ZZ766so/88S5nxsf++Y9pcN+N3Jav9/LDULVTqZiDlom7JmrolxIU/dr3sXQ9GDtTXYSr/V1655VjLgcr4Ux7zNXV4gs8UGVsnS58hI+brP0MOyXTuJqbp3Assf5d10D27sKCsgzvmJU/wAnUdlIPlsdfBNYvjVDlar08X6NfLZ6H+s7H/Qvvfe9NlvQrJ8VmA5M56pS60jB/4ONfm1usnddXHwXralp2fstM0ZT/utbq96w7y65/vbqf8gpSfoSn/ca/dtduVg1/X5uESZOEj5ZYiFaZcj0WWcp/mtbxxn5K6mJao3wcuSn3AWJ+icl/LX18f5ZZUlmJvs3pfy7wdQopZbQcpP1hT/uN+v9CWzQJAX3a6nbIbKUFcurIf7zNX+7xo4wKsvkeEeNtf7xRN2U/6PUK7/rII3bY/76AO+zR1eJLvFtryWQjoyw8pblt+kSZsF0v58aFxsvM5se/tzuK+d1bKT5TPx3jzd9v31PITYmj8MCefdWzn3o3+mqGExGnJeheWezMplnKHZ/U3ZdblasvxKSnHtnxueaCncp1rKUe58HL+vpnmHFc8C2PbOfrcqr1Y/7k1Qaa95PP44GL73+niZb2aSvv5Sfx4+RT1ubXKvfiohJhHt5/u87Ck1fWqbJeYFN2z7Dk5O/+5QOYsPf/Vfly5ozhr5+OmnY0Hd/a5qs6ORejsWIH24/Gdj7u3H4fuKM7d+TEQXzLGv99tsqRbxSHN02+euRE9a979do8Xnz7ZRfrRpH8tnX8UwjGys4XIGCvh6IkRWAqHYk2MxPY4DLtgDPbBWByH8TgRh2MKJuIKHImHcBR+iqPV50hJvxd6S3208dATJH51InrhJE3caqDkqyv5tHGrNeX5U7WwAj6HxrLQ3A7Jkv+knXZoL+3QSdqhs7RDF2mHQAzArtIOPaQdeuF47IOvY19Z/364FvvjFzgAj2OQ2g7SR4TF7bVDDmkHLIaTNPn2ZZJvsuSbIvnelHx3XKTfRvpzyGe8jrwq+XLKWF6uWBpzY0PMg50xL3ZDNxyA7jgE8+FwzI+vYQGchoVxPhbBjVgU96An7sPieBZL4kUshZexDGZgWfwdy+F9LI8PsQIWou4V0Qt9sSRWwrJYBavhs1gDq6HpeXLS7yP9QelWz5NLk+3/lWz/E1gcT2JFPIXV8DTWx2+xCZ7B5/EstsPvsCv+E3thOgbhOQzFH3Aw/ijbJcVF+nqwsGwX5QNlttSrocRj+6EnNsFS2AybYHNshf7YDlthV3weR2NrXIEBuAbb4R5sj8ewI57HTngTX8Q81CEQ82NXOf7CXaT/BwOk/fJhP6nnDWm/36X9bmNJvCPtdxer4z1shPexOT7AlvgQW+GfqP7eQsrLb2c/nynniVnojrO1v7fIJN9SybdM8i3X5EvT5nPi9yTpkq+EnXyN5bzkh97YBCUflbZTnuMxVmUsPenXwAGSTzuW3mbZDtuk/XdIu3+INXEn1sNd2Ax3y/67B9s=
*/