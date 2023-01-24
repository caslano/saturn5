
#ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
// Copyright Alexander Nasonov 2004
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
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>

namespace boost { namespace mpl {

struct empty_sequence
{
    struct tag;
    typedef empty_sequence type;
    struct begin { typedef random_access_iterator_tag category; };    
    typedef begin end;
};

template<>
struct size_impl<empty_sequence::tag>
{
    template< typename Sequence > struct apply
        : int_<0>
    {
    };
};

}}

#endif // #ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

/* empty_sequence.hpp
l6s9aNLWI6I7HtMEaUzBSmIQMAR9ZQPqIdIDdTC6JYFkdzAwW647/rLbZYia2rIaxQfzSQ+ldGX7VXOLJ5kudl7KnVM1/ixrxp0VvpqdyTpW/mm5vZFsVqifHHnXg3A/z9fURyEcLWU5mm9E8xJPVYU5SnRjHg14KV09VpXDdRDWT4Bdwgq9Ud4Rc4qXKx+Wd1xAob166as1ONAe9siM3emm+tnH49e7vDu4ieVp4Nkn2nyoxpCuYByPXYmDIH+B3ucj/KadaLeCeBSLgedUH7gbdH5sncZkm9HWfQ9f2d54980QqhbZnTdyPd7lRBg99dY2U5988deDKTkLhcP9+bQ/jnxxN8UeUE18xjwZQ6+Rj/5gT+YLVXXsC8ro3leAKUsGLDYMVQfaBZrrWKHpDKrXG+G5CdCcinZ/pK80G8fN4/NjUxpIbbBWn8bGnMAsqVpRUR9NrfcOH8iKNNQF1sHwamGffVgApnkIBeJc6jttQ0g9hIEU2Jti0YG5PXHk+5HbaJ3nQXevWzmwxOhKJN1EEkV0jG8FAXGdV47YkI9XP9DecD1XJxwG6OtDa8zOVrwOTfBXJFojNgbtzWNs2bocsZ5Y3+3QfMzwPLRkOyly8AyEYn25wEaYzN3DvdLoEE88Ob9XIYxtMzzQqFs4j3csZDwE6rgjyfi2EpLXrlTpTreNBYQBkgD1lzg/Pdb7BgjAPjtzvlrNmGKe
*/