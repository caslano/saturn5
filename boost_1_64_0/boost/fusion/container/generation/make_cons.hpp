/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_CONS_07172005_0918)
#define FUSION_MAKE_CONS_07172005_0918

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace result_of
    {
        template <typename Car, typename Cdr = nil_>
        struct make_cons
        {
            typedef cons<typename detail::as_fusion_element<Car>::type, Cdr> type;
        };
    }

    template <typename Car>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<typename detail::as_fusion_element<Car>::type>
    make_cons(Car const& car)
    {
        return cons<typename detail::as_fusion_element<Car>::type>(car);
    }

    template <typename Car, typename Cdr>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<typename detail::as_fusion_element<Car>::type, Cdr>
    make_cons(Car const& car, Cdr const& cdr)
    {
        return cons<typename detail::as_fusion_element<Car>::type, Cdr>(car, cdr);
    }
}}

#endif


/* make_cons.hpp
5JinJsvkwGZV2gkOlVPH+fk899ekaWapb6VQuEhUV7xN1cz95+/npiPoG2J+sHmrsFhyzdKfFoUuPRWf/S0Z1+9sDVvNlP2XHb14Mp+kF4yeByswVJE4ouoOH9UYW0X8pVHyWSXD+ZH7wUjrx9f5dMV8/VDrGuKCUkSV3cNcnEWkha2t40qsEgLmli1Po9BWU2uzkjIWl1P9Zb1bb6cej4GzJC+YU+IjxlCDYGMR+OhnpoK8zNxt4AoQJyY7Tx4u6iPzqibHytAzs51DPqjMunSjL7JOqZQ2s8NdIayUm0DbwRdodY7gF02YnCFg4iYg7gsRq8ZLxk5xuUN0sj0BPyATmpfoIyUpJX+EmF/sHTu8nXy8JaFsSGu7qFfrINTTgEfFE9XpUsgRV3gL7iXUqCE9XMvZBrD5T0Gv29GC388IAK80LIfJhf6tSRf6IhbiAiw84ttLRy/7ONVeISeEUGHLy/04ktwtmWME3c4hYKv6y19Q37Yq0Vd12vRS1g2klXdQCbq2yxLkNXfIc0ybGS6Z52KFUoY3RkLdTrtnEO9pigecdBA1h5ivtw==
*/