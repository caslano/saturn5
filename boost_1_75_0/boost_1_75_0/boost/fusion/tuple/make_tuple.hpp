/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_TUPLE_14122014_0048
#define FUSION_MAKE_TUPLE_14122014_0048

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/make_tuple.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/tuple/tuple.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline tuple<typename detail::as_fusion_element<
        typename remove_const<
            typename remove_reference<T>::type
        >::type
    >::type...>
    make_tuple(T&&... arg)
    {
        typedef tuple<typename detail::as_fusion_element<
            typename remove_const<
                typename remove_reference<T>::type
            >::type
        >::type...> result_type;
        return result_type(std::forward<T>(arg)...);
    }
}}

#endif
#endif


/* make_tuple.hpp
UcdrXybzzTOmyBv+QgTwYNQ12OJNuDEsF/aFHs2E40esspDnYcNJ4EE9H9Lf3utScU2wDzB3WLqeoL+qIlc+S8/qWE1v7z/Zvpq5SpvNCoOvpLZ0yZOYoqnkIwFFZlIAAspbxvKVOZ8hrS4NGadSZsIz8GSqGkI6yqSqp31ByVXLGUkJgOxD+OLu1HHk0tFSzsblQRA60FAXEUWOfNYim+JGAUXqrzz5LJgvkEAqScowigaAN54zEcAHyKRiivviXU6ANMEe6pnJvZNRZP2vYwzvGSszQJLyynGB1hn2HVYBo1qr0lhj42cap36295qtjIWfTosFE57RyKUo8hUQLmy7xNgXlwqZj4R26zHBVo7YqCapF/crSPpR8X20aTS+VM8EyoqpiHHZemDdVq6pCBj7JRxwSJeoatint0BbTLFMwx03bwzluFLGvGw74p2CIivqguonMFhlagF4xiZLcTh8qn8l3JgeevimrouYonA+Hcbv9SWESpHyK5Ntn/QMYJL6kBZBhbtrEAGwglRDRCamneKK445hsmULqVAIjHpNvoyilbasBzIW90HPjOmd6v+S9Uw+oUik2IyrgQWLIBgP2IPvTgXAnrhogFk9vdIDqRYhTVekVq4uHVVZG8seJT/AgXmZpodinG7eN/WEWpIijJJmrTn0Ph0/JaYFojDVEbd71AHggizEzS1W9FzdXDzkAvJQk90YsABQ
*/