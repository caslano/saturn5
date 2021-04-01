/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_LIST_10262014_0647
#define FUSION_MAKE_LIST_10262014_0647

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/generation/detail/pp_make_list.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_list
        {
            typedef list<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_list<T...>::type
    make_list(T const&... arg)
    {
        return typename result_of::make_list<T...>::type(arg...);
    }
 }}


#endif
#endif


/* make_list.hpp
hu/AbSqeIVBN5gx68Lg+sOtxVUg0DDwlzyr54Y1vXCcrWbWMOzVglnLz3TGJ5uplhw+l+F79g0QoD+L3FIWfixxJ/z1xtD9QaOOnLiPC0bBcM+E0uJGwAL6/ZTtbT/AXeFvp7yzxpVzjhji34YmHobS0nKwGonEPRUZVtUTFoTUSQL9o4EW4Km11oYI93gd3gPIe4A3Lt1KqaYkgWqN/IUTG53EBkl+Be6VJnUDJ+mGl9fwFMPyb1DY8HUgGcT+VIek+e54x7rJspPMHAfZTCwAmYgWZDvm4BTcqP9JOum1ODs8NRin82O/a+fH1rHnaolG5jkEslrnjD7d58U4Nss9yzA8c0hiPoj6qNGrpvWyTMpie2w95t5Sld8rHCKOnY/Vb15shgwyPage+Sv9R3EkIQIb47KZAK+zKS/CqIG1opIWFjCU7GW+1fqhGDm2QbUXOuoNz2P2JGE6f2PydLS9QQQHDxCh2oI1LCspUnY3r3BZNnd9vjnrUwHsR1E+GN7MdVB8M8SfSTz71ObyW7wnyUsLKpPDYVeg4Vr1TI+JJYqHuIzv+f/L9mw==
*/