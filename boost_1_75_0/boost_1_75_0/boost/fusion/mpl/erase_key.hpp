/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1907)
#define FUSION_ERASE_KEY_10022005_1907

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase_key.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_key_impl;

    template <>
    struct erase_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply
        {
            typedef typename
                fusion::result_of::erase_key<Sequence, Key>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase_key.hpp
kimjrURMmt/+HMf2buSTwBxx4f4Gq0vBqRdtNRIrRGcCxRc0pYvIpfcOXNA2Mm/gkJ4KDhDCJUyw1hThI62fY03UZSzSdRlYvQ4KHeyNYJub3zWbyNexJQcfolzIcUzJYiWmhOw0y6hxkF6MuFIGSmylqClErqfsxWimE6RwTvUrDajIA0lvI7mON41HNAqpOoflsXKYbAjSk4p+8uUClxvKbjRxSNLvBFAy5YM3fdeqbURpJ3TRvuwhx7PZiKm2ZLHyDeWdlc9/5pWcOyk33m/ZB7/uCyv5v+K1e/5gIgBzp5HppdQPh6XDRu0zz7Hms5HjaQLJ6qInTaYwvwUXGt5gWYtb61PYtZ1keW4yu6V/jQVhImn7cFRDJp2obgUE/yqhTU1vjQEwZ/Fz28z6mCl1fmWHL7dOqslETbfJlXsQFSK1pOk+VX0oOB4Re7Cim5W+mGMYoQQtiHtYnEZXsBZvuL+QffbvBdk5NNEkAEn6ksSygMSo1+AWKd460UZkYRS0ufFsIm16qsW/wF69QFdiI7SlVePZSZDjGdjtCkNzrKQincT2u9gosNjUeVfOkIW6hy5HeyJtXofqo39G8rPf/gGhr30ByC6v3YHyyOUoJIe/QAXZPnX5V6wou/9rVLQiyIH62L9NJvF1LX5V+y+6pG1UN5d0aHz1/liBUvwK1Yz4mqvJxk916FckZPcXFyXx2QPfxa7Ds7/g
*/