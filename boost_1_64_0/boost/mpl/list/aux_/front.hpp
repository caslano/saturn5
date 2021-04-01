
#ifndef BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename List::item type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

/* front.hpp
FASZEmerNxxveSLvuJM9exU6BR17VFNuZ28ppBkM1aJjkJur+nkt8+8VRuQRqGTfmt+mO5d5BpnWaBcIHRlpiWwp3IAzpDaQ+NDCN/F0BNuk9bnm4nmJ29GKkjiRSQaJBIvUu6SLw36aV688xmMHssQ5GhJL9GU3c7BwWO9h3org00xXPOcNkdwNgvV5s0Spdhhx2YeGGTCQLFivbQXujSdRp6VvAZZiJJX9eB2Mn9JvK5jfh/o8OO+vVAHtE4mvPLFyAvOlucHZdPXdaiymfEdcK/0fS65GOCTBNE07RpOLmdje91LRg42ZuI8439Igz51JoDvmv3KlNveQeuMT7hOMIN5MUM7F2XZr8HBIyojOecKmQRUM8T5uQkk9pCkFAHjS0UwIq52Rpn4cmYCt7b1SKXpKHUIBIY/qWz6VBCEUhWj9KxTY2rA5aNuCkOuzRCwyKuPN38mJXnn/4PI7JW9o6o2WwYRAfaWPOilCXqRc8bWiqTQA1ncfUZ3RP89ZAikGtYSbVzLxdwiHt/ZRkd9xk68QxCF36ljIY6TwxhQSj1EzquqSR6c+9Q==
*/