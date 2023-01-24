/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0946)
#define FUSION_REPLACE_IF_08182005_0946

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_if_helper;

    template <>
    struct replacer_if_helper<false>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, F&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_if_helper<true>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, F& f, T const& new_value)
        {
            return f(x) ? new_value : x;
        }
    };

    template <typename F, typename T>
    struct replacer_if
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer_if(F in_f, T const& in_new_value)
            : f(in_f), new_value(in_new_value) {}

        template<typename Params>
        struct result;

        template <typename F1, typename T1, typename U>
        struct result<replacer_if<F1, T1>(U)>
        {
            typedef typename remove_reference<U>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer_if(U)>::type
        operator()(U const& x) const
        {
            return replacer_if_helper<is_convertible<T, U>::value>::
                call(x, f, new_value);
        }

        F f;
        T new_value;
    };
}}}

#endif


/* replace_if.hpp
sl0UanMuQD0B5Dhx6BWUyz/JHeC2lAbLcjtclrF9N+X9513M0KUDqP7a8NSXcfhh7WqXi9xG4iMnMyU75i5J6WyBSqvrDvEw8QrJ32UUJL8jXyH5VglE8kjlLzeNNChmkpO3czMJlaPghEeTmi3/UxsaSyzENQtgKgw6T9O6CiAv2oq7Q03SqJsHUfLEjvx4/SCUBL6Vmw6iCR98P/LWa4Px8O9gnV+64LGR7+sWkUwR46Hy2JtvdxMJcAnBQmbA8eDzZkhzRd6h3pzrJvE4Bcpmk8w6Te9oqXhdwV9QPu1taT5Deg9HSB3D8EKlx4nxGJnzqGjVCQzO28Qy2pAxquuO6ZwHxkgLT+p9hKRjgxA7Pw7Ew8GBntYheWVjOAq5zR8clTXEUXZDHC1SMHAszzOOFis9NuT5wNGjt/qDo7q/veKoTQbhaD0t0msH0Fo9QOAoRmPL2PquupSwDR0ooxpYM47dEo2Oy2y1zjSlb4f03QlFl0G+LGxvdc61kyIKzPbloHYmNc4XDK66x4sumz11C1W6vQLd0ooug9RZ2NqtWwzvZn+2rkPR5ZbQ5Sa3LrGiyygFfzfdAviLqDAyXNRd18i69fZZWrfyFUMI7NWzEGMz6fAsHZ7O0utyY7R+AdPeUdGYIZ1JA2qjECNFqlvYldNahLSLUxvs3xlkeZbkpQYmY9s6WIquISJit4eQOL4X7szpyuXBuiYb
*/