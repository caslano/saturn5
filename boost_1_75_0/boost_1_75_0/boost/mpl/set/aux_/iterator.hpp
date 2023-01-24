
#ifndef BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

// used by 's_iter_get'
template< typename Set, typename Tail > struct s_iter;

template< typename Set, typename Tail > struct s_iter_get
    : eval_if< 
          has_key< Set,typename Tail::item_type_ >
        , identity< s_iter<Set,Tail> >
        , next< s_iter<Set,Tail> >
        >
{
};

template< typename Set, typename Tail > struct s_iter_impl
{
    typedef Tail                        tail_;
    typedef forward_iterator_tag        category;
    typedef typename Tail::item_type_   type;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef typename s_iter_get< Set,typename Tail::base >::type next;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Set, typename Tail > 
struct next< s_iter<Set,Tail> >
    : s_iter_get< Set,typename Tail::base >
{
};

template< typename Set > 
struct next< s_iter<Set,set0<> > >
{
    typedef s_iter<Set,set0<> > type;
};

template< typename Set, typename Tail > struct s_iter
    : s_iter_impl<Set,Tail>
{
};

template< typename Set > struct s_iter<Set, set0<> >
{
    typedef forward_iterator_tag category;
};

#else

template< typename Set >
struct s_end_iter
{
    typedef forward_iterator_tag    category;
    typedef s_iter<Set,set0<> >     next;
};

template< typename Set, typename Tail > struct s_iter
    : if_< 
          is_same< Tail,set0<> >
        , s_end_iter<Set>
        , s_iter_impl<Set,Tail>
        >::type
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED

/* iterator.hpp
PA6+g5Y0B/LUd/ZA5UOEvsgb3wW1JCsM4mgWFsKj83OAe7nlpn9hIRHGS3ra87n4N7tynkTZlZ9+H922XcFnyr7IbJvRjfeeL7eCnpmTpOxAKTlaLiGMxqRq19UFy0gNz6Np5Fvqv/r/JkXIpigZkCMi6EzQmcf3HLYLuI/9prP/UDKOVVhx+iMGr9wWk6jXWq769iyFvJqsV+Ymabfk6iKBqzQMNRDYk5bnpca4hkcpXVW96u5xcY10AXzof/sdLeJbJMSLd3nr4dr3RuZv0PnN0szSzKOpqiLzx21A3l+XeJrylIAjR7VsVGpJjJt8oalM2Z55vk0sZK7ZuYqto5RDkc776M3Qk+Ga2lKu7DljTDmAMoR7IkfQvMuYzxqQOgfE7/Qw5EGWku/dwJ1vQFxr8aWwPwWk+3W6b1oY+bRhWUDyOTJUgGNtSfUZK0bP6pJtHRLnWzUxgaqNs6Yp/JZUhTwpsvKP4bjMrNp4NyyHSzmdQ6le6xVzayfNxjTqveohqsPG6/JHeYx9AgJAzHbcC6uP+Q0sVXqGHrzWfxPKTbcZm9JgAeRzy/zgaSg+VhFS7pk6J5Hiy2YlkuZZncMN0A6pzCtF7rTyjRFiOakW2vqi2Iv9G21JIJ/m8TNQqEQoQEfe45nTVtvDkzQyynq30HWSyD1mUFJ1900wIUK6rqvk8jFMGtchI7tcYAo3glMiKnAjJmWUyqeq
*/