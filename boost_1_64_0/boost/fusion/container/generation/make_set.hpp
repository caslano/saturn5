/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_SET_11112014_2255
#define FUSION_MAKE_SET_11112014_2255

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/generation/detail/pp_make_set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <utility>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_set
        {
            typedef set<
                typename detail::as_fusion_element<
                    typename remove_const<
                        typename remove_reference<T>::type
                    >::type
                >::type...
            > type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_set<T...>::type
    make_set(T&&... arg)
    {
        return typename result_of::make_set<T...>::type(std::forward<T>(arg)...);
    }
 }}


#endif
#endif


/* make_set.hpp
lQF53zZG90Xe76MTVQS0CmKc1ekrZWYOtQr7vjSMJlVnWMGmuKRMfougY+e5l1uD12s5KmMTPAkQY+1wjPJfyKbqyMkVCaNQDHXs5H2QXqbyKeutIpoY2XsgnyeRc/oSm9twOKOK9R2VzjbW2algLgeBowoOqEu0H6fmBeVgok6MOPeg00XLwm6H3SVQMEB5F7twsYj08EDbTA+H0wFIcxqrCaml/X03BNpRVeT2hyOjy3D7i3yD4QpRTrUPWsXWoWyug/iolcnctUCEfH9UlNVtrWtEPvf77rjJ49VrOyKxSXt/BgIZs91qae8XCo/FpghIvMA0kMNgmzOXJTQp3djdiVn5Ds9AdZnkoj8KuzAddQNzYYpONtFuSusaNcJANGiVwgeBXDHYxMFHc40VkmD30QmNbqWFzcG5ItB+3tLo8HODCW51/PIojavlqrca9NlATnoWgya28reKyAmbPEPOERKTpv2ufuJCcUYLfYAzymgpYwbBP/lA959n9sHOIH5TlH/pUpZiIyHc3bDIBVgCeWvX6/Mn3E60a34Mq7GPfzdp72dItT+i3A==
*/