/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_VECTOR_11112014_2252
#define FUSION_MAKE_VECTOR_11112014_2252

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/generation/detail/pp_make_vector.hpp>
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
        struct make_vector
        {
            typedef vector<
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
    inline typename result_of::make_vector<T...>::type
    make_vector(T&&... arg)
    {
        return typename result_of::make_vector<T...>::type(std::forward<T>(arg)...);
    }
 }}


#endif
#endif


/* make_vector.hpp
qODNg1ROAifDQBN99ckSX8CV+Mu/wwbFLsH0rd5olfGGuMm9r+zblMdnD8L8XQf8nwc1VTOPF6U4Cc/0DXSw51wTDjR+JfwPm8ddtMBtHhB24ELg11er9/N/FFvYXRZnvykZ5KzNGi8KNBp5L7Httvz8rJ2NLsBnaqvTnYczLnBZHmTMXMxOKNqxW1742UiR4s8i3j6QJY0NwAS4kZEhbdAPrpA2i/VXyBqo859xqjfgOt5/vqtXOK1yiXrHfDZlV0gBKQYakeiIYSNKu5bS+LZdC49UYRpYzqEhB7evwOu3DnrlM2My4LatSuslA20rlZotK4z08FGRxIFW7L4n4tlIiXV6I+ftdlXCPqtLRNjVetg/9XQN46y2g6C/8l/ddW/btdx9OV0KTVGo10h9pvDwyYeVgS7fPmX1L9Y5FX2vnvGrllKfitfhhAPxefzXAyhMASD9iuG7SN42QC6qyywuEnaw0OT6lHGZv0KE7YAjevAaFTiTMriKw1jeRzyjq+kHW/67hc8PPqNXr/jZDmyO4c1XalcHZ7+DWsc54wD02Yk7u2Q0GHxWVlxWViZB0dQWcYruncjl93vHWa5S9LVzA62u386B0yj9Cuk9tn8ZJuhF/TzM3cta2A/CAwgdik5IGi0FNgpbGC5pV+BPuPzZUxT/1Njl5anrxj0VEbHQ/WD0S4I58NZm01yuloGCal9FrJDobG/Pr0Nt
*/