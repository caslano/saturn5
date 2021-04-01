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
NUFKUR88LKLyWxc337WDLur6aU8tyGpngDVXCv4ldHF5lFYr2hf9s9vQ160TPq7xk7ale3sq/Ic4erRVKLTfw8su5O1+ef85DhjOK1z1B+V7kKgi5SqQplRBuGDnbVFPYN3JT4TMqAvDimE2t9CGpxSqE5PjF8wG+rQgyjO2lYen8TCKukIFRev34SHD2rCm1wCyYhH4/FbMiBFmQS8iCoU4aqrl9uYE31+jMcEINn9I+h5bTLMm54L6qS0G1B9wneYpK3PnSdHaDW1xGIfo/8rRSuVOClvj5VPWqkwQBAR8XWy6YhhO99hHb8BRF2BCtjQzCy3dNmsycra2J+VyiynCUVr2QFdIBfWuQS8Bs/2UTA13RGTu+5dZyrza4fExwBNRdOmLEwcI1G3S4Lfl1ki8bVcYFeywd6c+y6In5+jQccZYOieLQppg1E2YKx6ZNbDf9DhMQdyOOLIvXz0XoL0kyVR2i9GBvhjFAG4wA6g9yEQ4P+iXwOnjQmH99eEncw190/UNTxovOMBWW+oWrZNmQEmvjxDVXzqG4F1Z2gcipZ77VZotBDkR4g==
*/