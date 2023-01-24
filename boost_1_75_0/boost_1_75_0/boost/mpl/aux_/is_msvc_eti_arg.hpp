
#ifndef BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED
#define BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)

template< typename T >
struct is_msvc_eti_arg
{ 
    BOOST_STATIC_CONSTANT(bool, value = false);
};

#else // BOOST_MPL_CFG_MSVC_60_ETI_BUG

struct eti_int_convertible
{
    eti_int_convertible(int);
};

template< typename T >
struct is_msvc_eti_arg
{ 
    static no_tag test(...);
    static yes_tag test(eti_int_convertible);
    static T& get();

    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(test(get())) == sizeof(yes_tag)
        );
};

#endif

template<>
struct is_msvc_eti_arg<int>
{ 
    BOOST_STATIC_CONSTANT(bool, value = true);
};

#endif // BOOST_MPL_CFG_MSVC_ETI_BUG

}}}

#endif // BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED

/* is_msvc_eti_arg.hpp
IsB7kumNV2SL4lYiLrTEZQNqkJNT57/S/fpFSscZCY4pkCQhr45Vs+GvfRnNYlQeE6FWnvZXcpNkD7ihdjHtL+UkhcrYT+ERHIOg34WFBdPc6wQH8/N6xVKZUDzEnNxABV9txucYg+pxcF4VXpxGCCtJNE+K2UVh8vrB93kyRgGeNklAvraMPGta2l/uxEQAAEA978XjuoIcZeV0RdrnagPK/Bh1luloFg3DZ+ysBXR0MwS2cgDKGp2yi/yhtM/KSRrlOuUFdMnjRkEKRCQ1EbHPbIM0CmPY1GTs6Bsr/sJejHwZy6OQH6v+KYlgXT0hkoyBqFidt3Z9nYAg4/MvXgGqfL436LBipt15R1/plnxH0Y90bCJKr2k5zqtamaxNy3smNiPshuypyBNOlPMdMT5cQGed90a7og5lnD98HuxmaHwuGVpOmqfjI6UwEvbAqoceaCwt+487jGDD36VPaqy37Hw/aQiTzyOTBsPPxovK9GTBMvZelmApLy0NsP2373QiLIyhXyIDXd7rY64MJN+0mNv7KWlZfv/+OiYmPAYvRk2GKay/lNlcuseioFBTg5CObjOxhTgpi4og8+/cslfacox9oXIfP5aGMH7k+ZSvHvEn6VUa+PW5erybwTpemvS9G6+rKidfk+YJXnBn0l86HSb4rYTwBG3wb1VoG9lQOscPytec4eq7lWSMWi8J3j2G64RVTBOg8yf+
*/