/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_SUPPORT_AS_CONST_HPP
#define BOOST_FUSION_SUPPORT_AS_CONST_HPP

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    // A customization point that allows certain wrappers around
    // Fusion sequence elements (e.g. adt_attribute_proxy) to be
    // unwrapped in contexts where the element only needs to be
    // read. The library wraps accesses to Fusion elements in
    // such contexts with calls to this function. Users can
    // specialize this function for their own wrappers.
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline const T& as_const(const T& obj) BOOST_NOEXCEPT
    {
        return obj;
    }

}}}

#endif

/* as_const.hpp
KqUE3nuCslaWfEghyS036CbKsuPfKNWUD3rzrOezgbCItD3WZ/boYVmx4MSA3ynrIn95iMIXcm3WfWLUiANRWNhIA4wrxAzh5jATwBdjBa3zXJduN6jmd1hrnleEU3X8EzL+4lAsW7tQqQULmJUG14LYGlRm7FGgdhJDSWWLeJyfDTm9k8Mc4vPMLji03T0d6o2t3vag+XswjswrbKwde0wGhLw38yKBoOqaQVcoJd+uAwWoWnwESZ/mQLbCBj7Os/rNrXzNM2Uihb0uuvPFJVL5IX85wgF9U5hYuxFNT/I7B54nUy7cDhw2XzxhQ5ASIU83M0hmt6ThKLDQlZUfG7FtYJh5BC3MvoLC18ZOoeQTsMXhHnin9wLjSONgUngapBgTDzKhxGc6EQcsdZ7szJypzmL0UTrdQaVZrDZjwXnElv1CeNpQ7k9nlPNyIzlw99CygCtuIAJ9zw5mjTc4Nd08s//jIl36bEXu0FCe1cXSdXtkb2btlqMYEwOzPZqKsFypCwYZvvUQaXoLC9/HIOsb8X4T568AoowpVipOYVCSMhK8oUL8UPyJiA==
*/