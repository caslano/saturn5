// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP
#define BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct unmatched_argument
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        static_assert(::std::is_same<T,void>::value, "T == void");
#else
        BOOST_MPL_ASSERT((
            typename ::boost::mpl::if_<
                ::boost::is_same<T,void>
              , ::boost::mpl::true_
              , ::boost::mpl::false_
            >::type
        ));
#endif
        typedef int type;
    }; 
}}} // namespace boost::parameter::aux

#endif  // include guard


/* unmatched_argument.hpp
Sa8N8ETwxI8gh+D847s3KLFLjpdJIpXxD5xd0V3R8GpP2Yl9lMSp5uzoZN3ZTSEod6f+k/2HMSta6zRvMtEFxt6dnC8uX39gU779S4Th9SfYEOPKL5wioVsxmD4atIzvqrUnmo6Y86Ond8DDRWqE5HjLK4BjDGgyc8yo+wpdMifS/JI/x86XKg8NwuzD7UiZTPirWeyP4F9JHYHm/xH8p51srflQ9A0ZGr00gpsiR00bP6ok4YAeUALUhdp9xCrOajWmcSGdlsrJUcEpxewlme+u9BsJg6D3/NqYk2EcxOezbE0XuTrsR0mDJXdynfoK9EWcP81y43O3XH8SZLddi4urBmcnef28N+jYJpkan+nFqaPZHTOdd31ziL7Kw++0LyTYsndfHfi++eto2pu9mNmMEUo44Uly8m3i9RsqK5pjkiBF6dAUSrKWtkYTEYieP3UuUkxwqhdEuf+JmaFE63JpdNbEsBUoT0ERrUBSXMPWM8PREKFUIE2e2WtYN5V+SseeQp1U3i+QGY9/r6krw1yXPDtzei+yFgHrUWwkojdPEA81ePirZL0aRdHOrARgVhlPRfxJj5K2ENHwsRmIByIUhPu86RClK7w2oiOKB2r3rRVdszzzPOMCkhBf+ibZo/+SId2XR8jBHu8GjgPtrFznXQv8IehJ4AzeofTOwFshxKUiFeKBNPmCUO2CML6XXMNl0YLg0f9r/zv2
*/