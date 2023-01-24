
#ifndef BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

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

#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct v_iter
{
    typedef aux::v_iter_tag tag;
    typedef random_access_iterator_tag category;
    typedef typename v_at<Vector,n_>::type type;

    typedef Vector vector_;
    typedef mpl::long_<n_> pos;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    enum { 
          next_ = n_ + 1
        , prior_ = n_ - 1
        , pos_ = n_
    };
    
    typedef v_iter<Vector,next_> next;
    typedef v_iter<Vector,prior_> prior;
#endif

};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct next< v_iter<Vector,n_> >
{
    typedef v_iter<Vector,(n_ + 1)> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct prior< v_iter<Vector,n_> >
{
    typedef v_iter<Vector,(n_ - 1)> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , typename Distance
    >
struct advance< v_iter<Vector,n_>,Distance>
{
    typedef v_iter<
          Vector
        , (n_ + BOOST_MPL_AUX_NESTED_VALUE_WKND(long, Distance))
        > type;
};

template< 
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , BOOST_MPL_AUX_NTTP_DECL(long, m_)
    > 
struct distance< v_iter<Vector,n_>, v_iter<Vector,m_> >
    : mpl::long_<(m_ - n_)>
{
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template<> struct advance_impl<aux::v_iter_tag>
{
    template< typename Iterator, typename N > struct apply
    {
        enum { pos_ = Iterator::pos_, n_ = N::value };
        typedef v_iter<
              typename Iterator::vector_
            , (pos_ + n_)
            > type;
    };
};

template<> struct distance_impl<aux::v_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
    {
        enum { pos1_ = Iter1::pos_, pos2_ = Iter2::pos_ };
        typedef long_<( pos2_ - pos1_ )> type;
        BOOST_STATIC_CONSTANT(long, value = ( pos2_ - pos1_ ));
    };
};

#endif

}}

#endif // BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

/* iterator.hpp
cXNgC/h0xwYIon7CWZkV2f44r59x9LQ2MjNT4GPCzS1iKxNVtAXEfktqPsGcc9G4z27+SPb9aaqQ8sm1iqfqk/qiwXZdPe+sT+iR3vUoM/x78l6HK7RKOL8OCqA/SpqmpJU7nctgr1QDx4nRiv/nr4VnVKpGIqNUBpMcJeo7Tvdmf8Hf75lmdV+d7NlxBWK89flX1OvZohcDHCGZHZjhF7TQcm92SjnG6fI8fhZW4hnzdLB9Hjppv3hTlB/6uBr1z8ZWvre+IVk/9eVQ0fjFvaYsYCTI4PQx31Hu0DOlpVqDBn6Q0MN4Q0Gof+BDYnwZTauDzKTdq1UYPDKDNY/lcmMv0Xlt2MKFQgvljScPnEQg/TqQO/8qV0Ae5DfSbXE+2CUswWxWb0sfyY36fdR0+8B02eFOo910hkbk41YQTL4XG/0haek222WYZUhN1cLVljAEPQwIHTa2nw8f6EmjnMQIJSt7cpSGa76u18ETVC8uCFYOR/Zmnv0CQ03JeUrZvfVj5jjVUatK3AkwkvCCflHjLW37FzEyk1ZjeZ0HJJFVjw8HrC2RKZ8IJLb1Xmd/ZTJehJwrh/l2KxKBd/5zj8xkqdwpTCt+8G9n8LNQjifitbv/NJiE8tP7SuSp/tXI1Wd/V9W30vyqiN3KhTBpQx5oIP5b5ZNcdR+eALHfPmLldD3LVI7hTI4Ba74oQ1VnYSBR7LsD4ysqUZIf
*/