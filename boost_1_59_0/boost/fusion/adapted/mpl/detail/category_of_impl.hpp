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
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
*/