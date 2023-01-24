/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0841)
#define FUSION_REPLACE_08182005_0841

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_helper;

    template <>
    struct replacer_helper<false>
    {
        template <typename U, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, T const&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_helper<true>
    {
        template <typename U, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, T const& old_value, T const& new_value)
        {
            return (x == old_value) ? new_value : x;
        }
    };

    template <typename T>
    struct replacer
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer(T const& in_old_value, T const& in_new_value)
            : old_value(in_old_value), new_value(in_new_value) {}

        template<typename Sig>
        struct result;

        template <typename U1, typename U2>
        struct result<replacer<U1>(U2)>
        {
            typedef typename remove_reference<U2>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer(U)>::type
        operator()(U const& x) const
        {
            return replacer_helper<is_convertible<T, U>::value>::
                call(x, old_value, new_value);
        }

        T old_value;
        T new_value;
    };
}}}

#endif


/* replace.hpp
y5P+uOZyC0k40MOfN33gsnhTL/IrBA0NUiFkAP/NHSwdI2rYx6yBZxX08LRxuWAqmclFDMZqo16qBF/5H3vSdyeX2ySXOa0HT6Qv9L8Id0jiUR3kEWIDy5XlSXx+b4DhttNsZa/z/KVIdVcjgnlwfVibjYvap9lKbhNNbGvBx6qJAW0Lh931I3O7a7/CIfwKPPVL/xirkuYeRbU6pEv0IYwTfIQky9TuwqNgN9ekiHz2DEHm+/4wCe/Blso7tuG9VP6TRAPDZfIYLFbHCsQkgiAxobrlaQWr2xIbZI5LVfyAUrVq1aQG1LJNsUXEXwT0usWqgv0PRAU5YCgxhgsPCBwrehfTKr2koDc+3JHYYAMkBZ/qSnr4OEvFcUVQrXycSlHHucyRifqgi1+7RXMrxHMtIv0QJUbWRzbQz2j9aElwCh76kQJ5AUDOPjwoL9ITL2QihxYa/ie6EYFYITVY+kHoZ810XzJx15JGNuHlAdpV8xpKrDhmfCZn8twIYD5x0iRSc7ZUloI2vJegCy530M2W9aC/t6T8YIuhjJy2UEg0mYS5n69BlwTx6MLmQJjv3hFtsKwHyrRIP9TlZPIFhWoEOc3xJc10EOQqEPBlByCYCuLPVEgRyy7DszXZQH+iwQGISnzTnxRDBgIRDkB0ZEDQs/P5s/PZsw/8bsJl+Zh4eL7y8Hz14RC/ByPiZUvRFWG/uMLtF9Lv6aW/
*/