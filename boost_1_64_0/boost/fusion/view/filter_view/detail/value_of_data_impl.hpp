/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
Y7u2gmN+W4Fgaw/TS39rBEvFYbpn4rrkGbgJo2uuiVW5Z3+o4fOCz9mxdn9hZvPojL0y1IdhjQ8UiUc/xPGaETMVCRHtzl4ZmlAWAE0rQiLKqEOYMzUCvVv8HOZtXJqbPcOhP4+nDigli1IfDtRpkqN/wYbxGFxwCE/MuyZx98hvq47juJD+C4UV3Az9wx16eVgJvyJk4iEtIR09qD0VHhrswiqNb5U48UgwYsXyoWga5joE90tvRX7NPHvTlRIrs/2FLIHzJJTCjU4BC3tit84WXZkTUyqBTCpuwrMeI66jhlZgeJNhEfkywc12a00RkKHuSXxdcPND3Xbk8HATsXLxlG5dzJAH8Diy7R3AkZIhtsfEerMm7rYJfB4Q/WEpRGjzHYqWj/22RuoyQeYugpUBVTAwb2+RJ4MRK7Y9OFE3gioCYQ+/ZjB1X4tWfoNOAgoYtdczeKrenjSZdQ9RXNyk/1//0XG1cAId49usby3WncxvgJrJoEvx8qHcI4jmtACkI6VxghwhlEQD3DVrhhsj03I9SQlyLKhtbBC63lyWZRpZDNI6BbbdiA==
*/