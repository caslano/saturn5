
#ifndef BOOST_MPL_TAG_HPP_INCLUDED
#define BOOST_MPL_TAG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

namespace aux {
template< typename T > struct tag_impl
{
    typedef typename T::tag type;
};
}

template< typename T, typename Default = void_ > struct tag
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : if_< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type
{
#else
{
    typedef typename eval_if< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type type;

#endif
};

}}

#endif // BOOST_MPL_TAG_HPP_INCLUDED

/* tag.hpp
v2a4J+r8xc2hwv+P25GHuVeOBB0vZY1qBRWNQYC2wJClWucEfzdPQKeyhAIJV4LKyESI8WX9CglyvS4QtqkUKfDlUm1BKyhRNyAtV5R/D6KRhuGUNYFMFFWuFRU5XrIg4ytsdYLDSsBW6pSKIuSF2hDfAngWA1+TVxQYw0ZyoD2iVG14oJVaDtlSvtSjIHdrU5tqtaLQtj3fNHe7nV9V1efTySyMbuf+aV14PruPmhmateQ8l81JWQ7R9LrXi4R5xEImFTSryBNN5Jq2KQRSXsILYgbdMlW6y4JNg61l1oXMh+zpgQQ2Rq+Uyz//xJ7+GWntGAmBeXNHs2hjAhJBK1E3dPM1go9M4X3LOmyiSu3Dh+46bETaqUL+3q/sYrHwjMndaGyEk5Fz0YMxyUpEJF8OSCOqcWnRYtqmZdrOZS2b91zgrzVVO4NQvmYYT5DTYMqB2LegqYXrlOpf7wzCG6QPtthm2IPYEU6cJN6VuOij8PqxcG1M+l5ikycWNhcucnT4pRVf2D3X5Z7rOTGPhdW7cns9r8MWxoLytp/QO8HIap6fHdYhxY5KBeZBevP4T/oDUEsDBAoAAAAIAC1nSlKb3PH3gwIAAIIEAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0
*/