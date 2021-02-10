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
R27+DQVmep4kE0hqJnWBEAQyQ5LIa2skno+jSRzGzg9CZlWTczghry0Vy0+OdYDyHB4H06c38K5EklTIlRcDcaFS8hq4JLbvfbReT4N4OA0nSRiNnQnDcrBWCC0Tcw5HdF8UYau0KCZUrwNLKqHpyHMcP89Jr+b/NFwbm2emVra6yJMn2W5bXDXmWtGeQHE6bQ/ClpWa1zeopJv1WtVGty1NbYAti9NCoHUXsB0yJCE+rxW+ukVmkbJjYW5PNZmSBjuTXLHnItv/GpkpcQbciqqCJXdYY9SKGZGxqtpg83yjudzAliJK2glk6YBYPLWJUwD32EcVjRC0VNRd1w6VxBFqdqI02rZMoVwcBH5bTX84DHDZ1rL/YY+KYaHEmNkzyVDvYrdm5HPFmTQOVm3JrXU7BLaFIVRN2Wi4nMUJSeSceIZpcpTlVjhnhuHMrHHS6q6AToZNK7Fi6DoXlD8B5T4TSYmjecm5hFWTlVBR1zd28FM52wLz3EFQlwoLaIvX2m4rbg9aPmivY+2ZPxslzoHdTaZREg2jUWzrbo+CP/3LyShwPFk4bXfYYv36Te8IKUwfu0AUfTrcg38deNpadLBrKVxc6G0/EvyO4eDiHhKjh4Ze1X6mIQ9HjxRxuiPmqzakj85/jlcIm5H/
*/