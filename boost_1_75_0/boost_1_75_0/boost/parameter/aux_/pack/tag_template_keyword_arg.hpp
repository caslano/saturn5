// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP

#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_template_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef ::boost::parameter::template_keyword<K,T> type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = ::boost::parameter::template_keyword<K,T>;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_template_keyword_arg.hpp
OsPov4JIa/Fi9qVBQshgT0ZOASnoPirRpIWHyqrinD3ZmCnj5ebnzdeb9q86O/4i9bITU6U/fUUmxZ7uKWYViyckhx5XVC9QOmqTAyUN6xxleciznixQbpRRX/2jJSVmbdu3F4eiYBcyf4UX1+3TqTYh4500eb50nJVWraXfYH85Eeff6P9LbqIqKs6eIQ1uXhjMDfb4GeSP5t/8F0Txizzm7rxXDFYovJul0pox1UG7IpoYk4t5yd/BqE+Kb/wPMRisdoLoBhI/4dW9rotiNccObGl4scIkh73k2rk2sN+gp4N91cBa2Ig64ZEeI9Cc6GA6Zs9VpVaXKruS2gMGFPbpG3KtZzJ2VNA/iC1rBOJUJ9Zghk8TaHfe0ryvHXT18n8uQbfNh39sftm+ECKB1hHiYNYUqBfIvNXU+bV6m2rgNho0+F5wXM20bKtB9xVij3qPmvUM/yzkJ05nmJf4KRvvXz4QH7pujCYvbsjji3IbCuf5PUtjPtiJeLrQ1RhdRdaeb9brJt95PonAoDLrh8JKl7gw2SSvoLyPPhT3ZElewR4K6+jNn3zuCE0uETDK5LuAO04fZe/socce6YxdYMbQY19Zeqeaf9iQX7/d4ErCghB/x77ahn8iQVoas05cuiYpRY3ZxnsaGA4ctGnClRJHe12eHJclK2z+mi6p9wlLNm1Dxvedy+0XhemrRymNsdrPSn3fwtgcdbD+
*/