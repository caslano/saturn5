/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
xb4pC6MheYkcHW4YfkMjTbIoCmGM1cuONUu5mqrgl40vmmo1MeJdlIaPsRPBUGZOBtYRpF6hXwfQvJ/bBlcWjYqNtZHdUbj8uFLqWsubqKVU+XG1lD3Hn5az0WkR+OxdtcCNnZdoEVN+XCk1HSvtcuSHNUH4U6uzjFUvpNvTWUM3NCLkszVCFIff0Sraqzg3ja/3DXW01amu2q3iio9rAu2uLrAb++BJxMswEQy9WfDYpeutal4Zlsot2wTvuLfgMYryZOsAdut8AwcOE9cyduIdS3bbZeiDjwMHGzi+v2NPXuKB3LcNgtSvtmrq3LqfXRnTEr8A3e68YBU+J3nPo5MUW+iThoGxAPXuNP39BS+NBD+EGTFmapDGMAGxiYNeF6oKs7PYAiAJ3W8wC+OQD5xtxWuokzG3jNEX1T6pLswAaznRPjuBnOBEIBtTmz9dHvuAsh9UXbagNr+9LHqgwEBROf3sIsH+nTm+t/ZgSgBn5MSP7J30oo8iRb28YB2+PWZOVFtXZqqmXxv8/xbKlCvm5B364CRtkzCYa9/P1ZwL5pFB5IaN5axWMUxQ3TIuBsu4kHBfBLxH/4R9kHP/5WARH6BzvD9FnwD262DyrxBLJN5jIKOzHG9FwsXuTCQ+yLbLfc9maL4yWgEZ
*/