/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_20060217_2141)
#define BOOST_FUSION_CATEGORY_OF_IMPL_20060217_2141

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/mpl_iterator_category.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion {

    namespace detail
    {
        template <typename T>
        struct mpl_sequence_category_of
        {
            // assumes T is an mpl sequence
            // there should be no way this will ever be
            // called where T is an mpl iterator
        
            BOOST_STATIC_ASSERT(mpl::is_sequence<T>::value);
            typedef typename 
                mpl_iterator_category<
                    typename mpl::begin<T>::type::category
                >::type
            type;
        };
    }

    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct category_of_impl;

        template<>
        struct category_of_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply
                : detail::mpl_sequence_category_of<T>
            {};
        };
    }
}}

#endif

/* category_of_impl.hpp
e/PvZO+MgRw2USqJp9SazKGKfbYZN/cww/AhPEwiJcG5MVZWZmiQB4QRCt/XUaAV+QlXk+cYeKTTfUEXHibwaBCtsTsRiKuTpmhU5cp+HenpGebfFuW8voeieCJTW6zgcd9E6W3xun9b1ER11Bb/BZLbtYUtqn1bTMz/x23xfWSHbZEVdbq24NCVUklJmKhSWNM7YlnzNq4wuvC2AUVw3JxD1kcjRVSliBIAPfsjRU0RcBUgjKhyRbN6YMpO1A+/hNo933HtlEhT7Zo2IdFs9fCKRYdlcB5gI6wVUF4122EmacrRUGDyAQNjaQLLI9+z4EBX9zBW8mEO6U55xmQpPiFUdPd1/6GWiNYrXmewRTeDVigIcIvq6H4EEaVB8R9JuZaR0tybp0Q9/smgsatuO/q3xiFqAbJ2iCxgUodw7kLMK59tUAICa2nq7gbAfsseQvzDlpaTNZ7yKbRs+JPlUsehSKWSdeEWwkLF1OAe/Zw+NjOq2UDRGwON3nAPlL3uOggjULMHcDMJ/U5mOQJf8UIC0epjaiyoBivkwhRO7dAOqT2Gevd/sw9269QODNcZkqWWWEYLUvyolQS1kkHtAkn2LtgNYUTtAdJ+ZtTq9htYIOH1BKM2rxundt5uP2pdCnDyl/z73HAymZqxV6f3AVR8nhVtoQ8Yn9k+6A4Ee50VjOIzxOg7kydC7T1nBYK4RWNOEK7UQvajycaG
*/