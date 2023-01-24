
#ifndef BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

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
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

// theoretically will work on any discrete numeric type
template< typename N > struct r_iter
{
    typedef aux::r_iter_tag tag;
    typedef random_access_iterator_tag category;
    typedef N type;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef r_iter< typename mpl::next<N>::type > next;
    typedef r_iter< typename mpl::prior<N>::type > prior;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename N
    >
struct next< r_iter<N> >
{
    typedef r_iter< typename mpl::next<N>::type > type;
};

template<
      typename N
    >
struct prior< r_iter<N> >
{
    typedef r_iter< typename mpl::prior<N>::type > type;
};

#endif


template<> struct advance_impl<aux::r_iter_tag>
{
    template< typename Iter, typename Dist > struct apply
    {
        typedef typename deref<Iter>::type n_;
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
        typedef typename plus_impl<integral_c_tag,integral_c_tag>
            ::template apply<n_,Dist>::type m_;
#else
        typedef typename plus<n_,Dist>::type m_;
#endif
        // agurt, 10/nov/04: to be generic, the code have to do something along
        // the lines below...
        //
        // typedef typename apply_wrap1<
        //       numeric_cast< typename m_::tag, typename n_::tag >
        //     , m_
        //     >::type result_;
        //
        // ... meanwhile:
        
        typedef integral_c< 
              typename aux::value_type_wknd<n_>::type
            , BOOST_MPL_AUX_VALUE_WKND(m_)::value 
            > result_;
        
        typedef r_iter<result_> type;
    };
};

template<> struct distance_impl<aux::r_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
        : minus<
              typename Iter2::type
            , typename Iter1::type
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

/* iterator.hpp
zLsJjVD61YPtPgNBSIERtdh5GHl/3GEK1vvj0B87Amx1KqncTdqR8lDziI2YRRBEqAJJ+gJq0fOQjQAiHCIf++GCg/4YhmGNiUaxAHdh9y5mrJuIxZW8FWP9j6ah+42XwrlllgkefrJ8GOkH3hWy+IHylYBoR8QdwWCm4IY/PuisZg10hs4EzURi/Px9dEXeaBnk1bGIPZdBEaAp5Y7UpFjY42sq5S4uUtdXq8PlHb2t+I3gAxd4bh73A1JgkhU7uWg7JgmPbzE7wQ80j3tDmFDjl08cgQJ1pfbNZ0cF0e140YTtPb//eCzBsn6FGsphUiiKMlT70JcnpYku+fZRAmSLwU5Mq7aOI2W2ISx6FS0RhQlz8i2Ui0T7jKJEgYVV+XyQ0YPwwet+Js5H4SatMrXs6Mt5AkDMuwalIbMjRrVagODjyahbtPBAFLXBulcOHkqRvp52qwb6qFExAScfcEBsjKbRESR7tqTwfrKU3Vn/jx6fZDq52sxWyWIIFtOuEV4GOg3cZ4iRrSh88h2juo+lpBwWvFzprhGYZ8TEUfVPUSUm8TflX8HDoM7l7EK8SxTICGo05ZeX6Pufs4bfJKhoKAaiMU0U9+D7uze0VRNF9xsWjBCDkya6XtajX9B5Sdx6Ri43j2pWNfYgXK3lJFB4SPkn76KGVSXfXvstHWklqSHCSAkKo3Tc+DORkA+DXgWDbi305hIUQe2z
*/