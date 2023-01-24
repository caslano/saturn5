// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ITERATORS_BASE_HPP
#define BOOST_GEOMETRY_ITERATORS_BASE_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/if.hpp>

#ifndef DOXYGEN_NO_DETAIL
namespace boost { namespace geometry { namespace detail { namespace iterators
{

template
<
    typename DerivedClass,
    typename Iterator,
    typename TraversalFlag = boost::bidirectional_traversal_tag
>
struct iterator_base
    : public boost::iterator_adaptor
    <
        DerivedClass,
        Iterator,
        boost::use_default,
        typename boost::mpl::if_
        <
            boost::is_convertible
            <
                typename boost::iterator_traversal<Iterator>::type,
                boost::random_access_traversal_tag
            >,
            TraversalFlag,
            boost::use_default
        >::type
    >
{
    // Define operator cast to Iterator to be able to write things like Iterator it = myit++
    inline operator Iterator() const
    {
        return this->base();
    }

    /*inline bool operator==(Iterator const& other) const
    {
        return this->base() == other;
    }
    inline bool operator!=(Iterator const& other) const
    {
        return ! operator==(other);
    }*/
};

}}}} // namespace boost::geometry::detail::iterators
#endif


#endif // BOOST_GEOMETRY_ITERATORS_BASE_HPP

/* base.hpp
Pdr9f2mQaL3WgutXid1VLo5+INj+LBjX5BKxW36YA1Tfehpf26kC9mqrws4izq4e80/ZNaTbjoC3kWn7As9aP8NikPzjgaiWLE/S29iMWzh6Ak/cKI1vgAgGdWnklfVNBxKTeYtYcmYfFnWUVYIkSrkitrC+AQxkZIbV9cU133Z3menc3V31zPicgZYsZvbSF2l8787NScYfsODdKB56P5XMkkLGM/XHi9y4zrdfs7bKrkR+pu5RGa1M6Hm3VRpJn+Sx8HCcf2J5DIO8eXbVTA3F9q6PdpOySxy58AbbaUiTzhZ/Hjz8SncCfiDBnab9ZMHnlcKcN++gPO4NByi3CR2v/gpfWvjcKuAyGVtdlT856p3QfkLBzfY0opcVjJQXk9wckzSsPQLqnz35LoUgzFqkHzpONdhG9dz8LeG+kWOP4vAIJ4npiPL+MzhAaRbiBQweRrz6xQfHUFOxoOUjkiXbvczAQ32YeqJFCNot7/12uxOi3r8ybm0KaSVd4ao/wq8Ah1ntBrgwcAbcDpkYnTusXqnhrV/B+q57Uiq3NDB/wFhGmKEf1ods2xM1MFAQcRxO4LT7/s5gY4LtlsPFGT1iVrkAY6sqzvHPKUxJWdkoM1qlLxdnOhFf7xuYDQaEm4TOUUAjLjqgz00Hb7/Xx+4smV/bXw6H7qxJbC9RdP0hpOWxJXw9lvWUQFbpnd8PJ9nNXxhA5EvkT+b2
*/