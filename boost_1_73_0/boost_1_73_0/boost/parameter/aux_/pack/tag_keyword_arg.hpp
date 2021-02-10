// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP

#include <boost/parameter/aux_/tag.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg.hpp
J3IavaWvqjTySwX3eFCIYYWRTYl1aP2xdGPDDhdrs7sH0tpxVcfbwGpsYkH1owrd5JrbCXeLqvKcRq+7bz+8K+BKJkMXdfzn5SsH1f7KLFxWMPJIJW4xSOiS9KUan7QjaLqINbClnCNXbK9vR2zqyaapMr8dFPEeySNLEiyUXGJbiIjtnNcxHWwLtT3rg/R6/ZtBI59JQa7UjenfQWFzhzpSKaOL/B7GWvoGtLEH9ajht8G/xv5VKkXJ7K6WVGtmiP8uzxY6E0sN4RIRnvXKPK+Y6yh5FXLT7t1+GHbz487uvzvdu3FPr/sXGyy7+Zlr/pav71LW9N02d78My+CXQbCgMQ+Cl640cvck3PWSPK1l0nmo+9Sq1hEu0EeYO/O0mEm7L6cJVPLh7iTryAwzTlA2qyrDunI3JQ3xdHbXfTPjmeZ8OlcEBgOrtlPFEXUpd2iy+eWgXNvuvpW7STXUptMn67jKpaG9eAS+yb7EysOB/wJQSwMECgAAAAgALWdKUoY4p0BwBAAA6wsAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9ucm9mZi1zY2FuLnBsVVQFAAG2SCRg5VVtT9tIEP7uXzE1OcmmJiYg3YfwcnBU9KJKgIBehQiNHHsX78nZdXfXvKjhfvvNrG0c
*/