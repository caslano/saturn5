/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP
#define BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct value_of_data_impl;

        template <>
        struct value_of_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template value_of_data<It>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct value_of_data
          : extension::value_of_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }
}}

#endif

/* value_of_data.hpp
A8EDFk+PNsIC2WXi3kiwHVzMqwbewF0xjG5PMD2KTe9Q9OM7d4op0ZQ4PeE8a0VwNC31TtzQj+JkX/EVKn0gMnXHFj0a9JSZhUfzMOsEWXHk3vrgIwBwz43ZWglT3PtyiOmp8cgfWn0ePcOsubgCHcex38e0xUA5BtgOH+7TdvU1JtyD6UOyuj9LVPtZH4oCP4ExgncSBo/pTMJsCnJcb0/y9KQTVMZZOKBJOXqGs0IzdUgFh6Dov9H3o+ysPb0qlFWYceu460xTxbJWMf0YbW+eOjT7gFuDBAd/HSCRlIGPpylv1cnHsT/R+aa4hPZeB7MJVlOi+0PtTwdVn0nuNZ1RpR3MAHsErfDbp7S1kkcgoVUmRKoe+YlKWX3komLfv33G6lfxdUXobfIU4pwam19yOerBazEBlzgPKWmXVPovIzq8CulezdEd+PTfJry3XMkuc9vW1b85DbxythZOV24T3zveyoHGo5B0OOMFZynnj1t5bqDcOqpJ4nAy80Y8ucXWgD3rRCxU0nreTzG5fu5UBdCbWAtsmAcqoddTTEAQPlnQdnev8hYH64bXJ4qyP2ZqMI+sb2gg+QJ5BwJYq/o50+NaHd6AaiIcDlG4lg5ZcpcztkfJaLfy/DBWDCTtfAILUIeHsEsGavph
*/