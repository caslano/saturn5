
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
VWqToQXZw2uH4BS6E/zFS7Id1WPGWaYCEo4UXhSkXQGJcpPaVBRlWegZypYavlxMnKqGvrXnESzdok5NcEBNgo69hxoBxP0u4iYRipuA6x6pdgncOwRywzldoMS+c/bgj1nkyAJMj2cP9weMX9Li4TNPBH/8ois2Mh5yH2PmSCy9fp42qwdykceEJchR1H3xFiqh5dycvg2n6w0muZFVOCs3Bro9cZnv3tQZNCz29WvDI+ljkNvz64bWpihhXcwAG2ou3WZQKCNnBtms97xIOe9yR1fCG4nwxFB0iuiSPp9TQXCVsOi0yYnFUjuczodBkNHen8h0tuQKOUN3Kyt2Vo5+OzeN5aNGJJDJCl5BzBlJfU0zZbwtYTH8wQijQVZ6FCngxe/QY/ceXVpbmVzdWIImzDZHk1yunDGE+6PeWQLq5S6Fy0zNdVi/ZNDQXD1jvbHsHE7kzBwbGF++3gcfp92wGyVUU472yA5cKtI61pN1dTHEAFib7Nozn5R6mq88rYXYzuETL/060a8FXLh7gC5+4yUbcB5opZadCc4JUFzee0/O3QdYOWb5ynEu36Rdly3P2B+rOHzQqcu/MJhuG1K3jd4QnNgFse0GVe9sVze03/lUETKVbXpXNz104jOtVp+QfkPE6oSzqvoaTPhNxSMjZ2Zp7oG4kLScW5KsMukX3xZGCwFTo0OBG13rnKd3Ra5Qa+1M/pT27qQV
*/