
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
sJSHM9bE4lKPS6A3ukg5lMQhWMr2TPilPRO29nlwTp8FH+VZbyrBfjXPkQm+hFDCVMI6wkHCBcKT1bZnwrbBNtgG22AbbINtsA22wTbYBttgG2yDTvdvff4fGRH855//l+JbtnrSeKif8gxHWSo/0Qcq3etl/K1xEbO/0VUf95Xlb0ezzqd8zTrj775Z5lX+zH1n+fvxrPPLl9sz42iZdRnKTzKWcTKbZcg7nxnLaJt1GcpPDO0fzqr6P3CVZ/eV5JlWBUInb9YjLa88N2rTqnOL5obOB3LyLfHhLDAkWGf+jr7EVVDiyk/oTFyxmrgG80J6UNzgF4pLnilmfIvNj1BI7l13UW4uauKi4wGrnokpz1SHy7vq6niWy/N4T4mnDqEr8aRp4uEl++fGU0y1PoPDokOC5Zm1I65tyDoGRUYGB/FgUfWON+/cs+5KdvFbVTp5nzdQlmFWBn72WdPbnfS638mS3sCYyOc/L3xWmv0rv5w0H5cEdJU0dyL0UOpNRpqVVhwR8crr89b0YWCpn87J3NQdoXlmvk7aAvSV5zi9pI/NFFPcbH7Rqj42y1gRr9LHZrwqXr30kanuY1P9LD9B1c4hXcYjZPy+jEfK+A159k+KzN7Bj9KsVxl55u4i22JxggfrtfpexnqxWhHROdnms+v3VB9jHu8GibeyxFuR0Et5hq6JNzYo9E/HWyyznQjj5LCmXgXI8/xDUq8OSlrS1GmJDDOmJgftlnKSHm2/CdoyVT/j35cvazuJ3kp675vSGxIZFhRndb5JX61m5ePvIO9mS56MIvQhDt8HZnEoBx0r2r6o4tHUd0vrni7jQzRldVIimifpekvWPUWTLsNxKgf7AEmbeVo0+b4gv3HG4rIPKIolKrGt/JYRd1Tsn+gfWNp3PLMPDb2Hef4M1pt/Vz5Sxm+o+rNQt9MK4KBr2p8VFvt585/0jHWIiY7Xc8IUFhg/IihW3U7PcjstR8OyxzxlGah8nz8f/zd+n7+ej06mLXqSMa2BaVrtzGn1TNP2/54xzd00rVPGNM+GpmkXH2dM8zJNi8qc5mGa9vSRaRp7Npk2K3NafdO0spnTyDXKVsopgUCuhEboI2KiVeUldUa1v1b3wSH1W76mb+Hb9pllTHuZVykD+Va9YbytalxdDwOkMJZLW7tF2J/fOP2RWYaxicZyc7OyfZ3Feij9rTST8fvZbKfK9/2bS3u7ftQvfxYymfHZhvSY18cg6XPmqmlc6nOqaVz6X0kxjdczrrt6/Y/L+g+XfUAcYQDr75bL1MYpNCHWqjZ5mu1Q02ZOHac7ESlDuOxzB8l+56ApTsMex/pjZHb73A0SR2GJw5EwkDj8ckschjPiQZFBg+OtjkfK0myfqz3+uRKhMrSQeJsRCvCgO9Ys3tiguKCoeGvOA0zngnrCiPCIkHDNeiZJfJ4SnzshiPU8qY7PcBL3/Li0ZaherzJFjD8cIPWkj+Snk50pHs4VOYApJ7nW9c1jiuvPH8emStpqS9qqE4JJ2xx12uhQPUgfMTwsB8cxSZtZfqdJXM0lrtclrpPquGJCQ3NyvMwungApqaYSz2sSj7u9Op7oHB2Xs4vnpMTTRuJpIdcBSaZ4/kXXAN5Fsy+zFHW8o8LiYl4gXnU8TvxAGaLkPCNCrjXc8pjiiQwzXm38d11rbJD1WiL5t1DOKdPyZrSbDYofariPYfW2aM055QjNthis2bc7vmJccC9JV3dCCOnans+ULu4OWFmmcvzIcn9gosTRRfbv7aXuuDmY4uDWjGHVrW8XT92xcM6auZ+xd87az2Mo8c7RxmvYYqy/1jKVfzHO/bZWZn/2qRKvMf3q+GMlfg/J29qSt24=
*/