/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
hUJl2IQz7OdUokgOeI90wh0t4dwqAWJePqy28vhWxCqtyKA5sYQHRseVAUaJSUfMqsnfjzpHnSydzjtPStTYehIcBzHQx7CBGnDT24dRNlJfvqZgQuqwFGUdWahwxrx/nVcxDuJHbgApejJS3Nt1hKblcdFw1bDbjHCAll1bocPx6VE7Kg4I8KNh5AQAPp3VMDTGIuo8cLtSNxbHhO9elPgZyG1ac2xuz7Ij++BMy5WZOeTnsEEK62lO1VIRyUf5TOC2/U5huXEtaJHx9/1JGGZ9agDm9hznLvE+w3z6ycIxvSV4OlcPYr+4pOaH19lCvEMbGhtZ42opyALZoQaEHlTWwikveuZn26XDOruRIINhpLphUb5BI6w3lqSXCqrzNzBTg5EBNLzFmmH/hEw16nCD+B+eyN201HSZUgrPPInF65AT2x2y1VTR5HsfoROpy8R5PrFEzkftLM6xp1zd4q7yN3iegVZKbgg9YlucvK4kXvIOJ0jsX/iwlJQKB04MuO5BFHUG22lBcQAsqluMn6+rnrB6MrkZfFqV6HsxN86SMtkxgZCLl0q/aA==
*/