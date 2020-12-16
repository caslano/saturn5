
#ifndef BOOST_MPL_ZIP_VIEW_HPP_INCLUDED
#define BOOST_MPL_ZIP_VIEW_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2010
// Copyright David Abrahams 2000-2002
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/transform.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template< typename IteratorSeq >
struct zip_iterator
{
    typedef forward_iterator_tag category;
    typedef typename transform1<
          IteratorSeq
        , deref<_1>
        >::type type;

    typedef zip_iterator<
          typename transform1<
                IteratorSeq
              , mpl::next<_1>
            >::type
        > next;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequences)
    >
struct zip_view
{
 private:
    typedef typename transform1< Sequences, mpl::begin<_1> >::type first_ones_;
    typedef typename transform1< Sequences, mpl::end<_1> >::type last_ones_;
    
 public:
    typedef nested_begin_end_tag tag;
    typedef zip_view type;
    typedef zip_iterator<first_ones_> begin;
    typedef zip_iterator<last_ones_> end;
};

BOOST_MPL_AUX_NA_SPEC(1, zip_view)

}}

#endif // BOOST_MPL_ZIP_VIEW_HPP_INCLUDED

/* zip_view.hpp
Yjn6OUias5mWl59KdovA/sVOzrRiu5rkA/9x6atgv2Lh1BJz+XwafqglvO4WZAp1JwBWIIzUzOcXoyDt6VOoJE0UIg3VXhBsRj/nOeAXcIp061NQQAxoFxs3jioIs0tGzMVKViixOcHCiErLb3UTW1sU4d+kv9SwTReE3F5NhsOpJiN8k6pMUodj7ZU9sjLukhKkjh5j3jIHQwCERfRGews/MdwJxP1ZrS4bhD5dxj+NefQoRo1JdIs2T/Us/Dd8gI8X4P7Rvw9G/jYXblL3100vxrrfgiLfPP39OPeVVl4U8UycdDu3MYTXS6PLr3I5YvTLy/SNFJ/feCE944znVb2A31y4LspktU8lNK0rCrCepJQxQihMwkW4F1l+Ur4VGMKVqnqZTf9zjbRvqJdeqEOtgCLNQWwhixOfTW3Cp0tbqZxCpvUUDzVDUSadjMF6BMMN4VwzkGme9KQSqGZR04eveh1Bj7x2k1iTTS/FWq/lIo+plsZK8Fo/v7T8Frqz+kKO73tWqTn6CJHdgR+RHPhSEvEIj32+pC4qI9vvyOZoERz1UhL5NHwYpy1Vf4bAhvHskSfcHbl/V4fEXDy6KcH+JDf16eI6mUL/h4Xs8lH6hUbi2kfOZRDij88Hx0KaGwyc5GNX4dEji2dvcxZzl6P0GT4BL+pAzPO4XuSh1LvPxcp/CHXveTfOfEj/p8+DPoOfiDy744qVSqj5obw+IH74BpeYzbPmTLajK0NV1jlYThVY5yCW1z0fzkpPu1tPvMI5vX8Tm2cW9uz5NqKwSw91N28+cNRifjSejy44/6ulvONOpSJjbsrfH9sxMu7KEU0sx8iPO9kxMq7dJ/VQAg5hF2GkpUH5n0h+oDSfFBOHjocrghzsnQKbmW8BRgjflhAnF0BwvB8mlJMcofbmfW5paz1JpuH+PAFA1PBenDTGfNhtjxPtQS7N7v6KgmwJWJVDAnYBA8buLpMCJsw+oT+aC3IkfJu8YsklZQ7okK58B4czaC03DUc0AY6oT47Yo7cGArWOc+t9cR5f8nuKzYuVQ8ZdlSW7xpitFijqpC+FS6X9tlTSN+7b8WWImGi6fx5TgDtcCnBy3ji/evB/mG9LdV5rpjR+741fnei9t3994/LdEpafv7Jx+brnEpWfOMX+nmzxdpL3pDluvb38p28lK9/whL38s28dSEUeOeQZzU8AAh5X/p4TFufj4ELF7ZiWHRkudVz5ZjcOyTj4h/FQgcgIROPK3/dgd4yDExU/FdBvRdWFj7uAXVKWSnTZ+vU5KF22lqtbw+UXUmAM02CQPhcpzUxrD7cuLOq9erOjcoxHRJNBqfGqlHNaF1upN/c4KkdRKb/zzX0C6OZF40Xx4vHoY3xXPJlQH+vb5mE+GXzVmKWlqRugHeFHrO8sYrnE4peNXZPE/vX++Pa3rV5Mrt/32PPx629/IXn9y59PDN/fp8Vvv8+axPZSmS8kzu+XAnzXLU4M34u3Jhj/4uTtX746tr3Wwl9Fvh824ndk+xshW/n507HokZUiD6XaPBErfy7qfvZ6PH6YMbcx/hrwdCL8deaLjct7Epb3zLXjo45vJMNf1S9E6FO8ngx/Tbwncv66QP6xUvNPanQgBqC3mWX0KCe8Qhpm+IJIBmRm0YWCR2nNfCKZitNZdUQGHTGLzH3YALnyGp/uocu4+gEZJHugI9hCeszZnCa5GlXitf6+C78QVaEXCtf0KNzPjxtassVEXKvsFvbs/VLjg2OCDoXySjTDAhTRN16LYVGuGRYE8FDFsNgTTWSBLLg2U4ePLCACi8mCnZk2soB6wjNwFyAmivrWTItPPDGAKMpoahbSveFl1RcrRsVz3Lo=
*/