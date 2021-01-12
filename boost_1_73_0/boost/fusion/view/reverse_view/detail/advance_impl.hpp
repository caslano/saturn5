/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_14122005_2015)
#define FUSION_ADVANCE_IMPL_14122005_2015

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/mpl/negate.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<reverse_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename mpl::negate<Dist>::type negative_dist;
                typedef typename result_of::advance<first_type, negative_dist>::type advanced_type;
                typedef reverse_view_iterator<advanced_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<negative_dist>(i.first));
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
QtfDe39BZm2dWzE2bX8L12schDZeA8NuzBTb79qhMbo8Tg5Hql/lVm0CR7FY7NTB1SUeY0Xqw5Nq7ZpAXzxe/x/VxvxfYkxOMKrBDR2ruQwyy9fTHDflxRjZMK7V8ywACbdP4GJHxWTCBtScQeAigStweAR+shhzkA6uEjj4bN3cj2I1nkrcQYmLw9h3omZyARzbz+C4XTFChlAKVK1nsXGNY0rsu7pBDs9gPVlEJe7SAxT9
*/