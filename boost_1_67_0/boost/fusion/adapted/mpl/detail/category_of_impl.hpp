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