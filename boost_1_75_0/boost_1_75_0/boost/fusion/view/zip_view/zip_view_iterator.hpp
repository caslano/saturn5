/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ZIP_VIEW_ITERATOR_23012006_0814)
#define FUSION_ZIP_VIEW_ITERATOR_23012006_0814

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/view/zip_view/detail/deref_impl.hpp>
#include <boost/fusion/view/zip_view/detail/next_impl.hpp>
#include <boost/fusion/view/zip_view/detail/prior_impl.hpp>
#include <boost/fusion/view/zip_view/detail/advance_impl.hpp>
#include <boost/fusion/view/zip_view/detail/distance_impl.hpp>
#include <boost/fusion/view/zip_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/zip_view/detail/equal_to_impl.hpp>

#include <boost/fusion/container/vector/convert.hpp>

namespace boost { namespace fusion {
    
    struct zip_view_iterator_tag;

    template<
        typename IteratorSequence, 
        typename Traversal>
    struct zip_view_iterator
        : iterator_base<zip_view_iterator<IteratorSequence, Traversal> >
    {
        typedef zip_view_iterator_tag fusion_tag;
        typedef Traversal category;

        template<typename InitSeq>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        zip_view_iterator(
            const InitSeq& iterator_seq)
            : iterators_(iterator_seq)
        {}

        typedef typename result_of::as_vector<IteratorSequence>::type iterators;
        iterators iterators_;
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename IteratorSequence, typename Traversal>
    struct iterator_traits< ::boost::fusion::zip_view_iterator<IteratorSequence, Traversal> >
    { };
}
#endif

#endif

/* zip_view_iterator.hpp
4pzTRz3KU3+Z/2E8iPkF+kPXM5t4j/GiD6hsDlFJPp5/Ps5LH+4xIZpt5fUNykTf2w/Yk3p9Gr6P+8F6eR4gP/BG6L4ga0BXfX2RzxnMMYxIJuNzk3XwPHV0WJd2FITlHJ3i3BwPR7cpnKEghIZwvceTU2fpO/A0dAe6EgJPcF7fp1a3KQvB3xi/Nuo8VwFyYNQObFHJv24v+edR3tciW49WOfmg5jjnM4GGBBdWBsxkdcA4lD/vFMxIbWV/T8vUKVKHsY7KCtPIPBeslf+Uy4cfD+P+TZ7+2U9s/IYzCa2880LStdHerYfG9WzeVZ6i851VuGrkHhMymWN66j6oo5/rVbpvu/w/8O6O9+0/G4NbBPhsKirUcXM8wxjwau86d+AnXT8aFGlOx5OP8hD6MDvWdidfrTNJnZX353k7c5jPfA/3n7uW4okw9Nrl6xkxvoSzaluY/2oNz8PlNBElF4oGa+We8ucFezJpTzxxapKmtv042Xk7naNNeg32vnw9MJ6dIirqxK7P1PIPPH8Q/iYwoEwYInbI1wMR6/NH1dL86I5hO+Xc6F3AD28VNef4g1H5RToVJskyH8+7hPH8Zk/fdPbxqGv5b+d6ZLDIfWE/zIR/8mMyg5tqH1xdRfTyTPuLfzUeumrVWQPN6Hja/T1UnoxmMS96q9M4X+TDnnuCpLtsnG8iPl+CTluq/2vAb+sZKu1lPXYfr+gW
*/