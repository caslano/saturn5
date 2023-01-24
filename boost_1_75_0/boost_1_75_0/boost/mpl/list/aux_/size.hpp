
#ifndef BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

/* size.hpp
IbrhmZqN9knL35f0mu1AVi9/y7x9/pF5H+jyu2nY3hLWT2kO44/eq7A8fJcGU8WRMj60E7kpfElrwD9h0Aq4ZP2SevR2SGHUfvBhejhjGMYFRqsJJ+sL03EBHKz7F1X5xtzn3K0erRdBK4qAHh2ANUuyL6ac1lyUvaqr+GBxcxKBJcG5S4FBv4vmLerhnY8xPyiQLxdfbbOyID/JZx3P7WP0GeN+YrEWscnrKLdS6WXUMJTyuJcBQQDzqibOFbwRrXd/Ii7sFdIR5BdlxnZ+rqxwIJcLqrX01pp7GKih8jOa68U/0ZJ8ruOF2Chav162XyscTlVy6aUZZNTkAd8Wb1N57S6XiDZKOp9cvdoAbhS7w/W84o8Fs/meCCd3VFS538kZG3LjTCbbxp9zdut5vt+YLguemb82H0tYt61f0A3SW940e0rd5n2cjmzazV6mvS+y4/beinjrZRo6sGoQ7aLuCW3N7kXK8Wd4U3ztfGyvChtwmDkjUxUxEg6b9B4gqP/S+2OfGiSgJWmoIHkT0z6SfGRNSTAqedPzilKMp7l5dTDQzHKUdehs1BPvsfs7z8de6ia3yoC3eWz6Cljmp749TbQt8VRTW1FrlRK533mTm2XAO624spsK3z6E2yZa0XlojcQ26HoQ886f2itoyWR1dl0slS+r0MWSqaZEMd9dhe4zOh86HwYx3CC9JI4GRiW8IJo1ElF8OyIb
*/