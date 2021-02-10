/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_ITERATOR_05052005_0340)
#define BOOST_FUSION_SINGLE_VIEW_ITERATOR_05052005_0340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/view/single_view/detail/deref_impl.hpp>
#include <boost/fusion/view/single_view/detail/next_impl.hpp>
#include <boost/fusion/view/single_view/detail/prior_impl.hpp>
#include <boost/fusion/view/single_view/detail/advance_impl.hpp>
#include <boost/fusion/view/single_view/detail/distance_impl.hpp>
#include <boost/fusion/view/single_view/detail/equal_to_impl.hpp>
#include <boost/fusion/view/single_view/detail/value_of_impl.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;
    struct random_access_traversal_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator
        : iterator_base<single_view_iterator<SingleView, Pos> >
    {
        typedef single_view_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;
        typedef typename SingleView::value_type value_type;
        typedef Pos position;
        typedef SingleView single_view_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit single_view_iterator(single_view_type& in_view)
            : view(in_view) {}

        SingleView& view;

    private:
        single_view_iterator& operator=(single_view_iterator const&);
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename SingleView, typename Pos>
    struct iterator_traits< ::boost::fusion::single_view_iterator<SingleView, Pos> >
    { };
}
#endif

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif



/* single_view_iterator.hpp
QEU/2EI3fNvP64YatTcDevCg9w/N0DGyjwFwqHbY6e175Ki3K57/K5Z/7vX4ULfDke9mXn3ZP2jfGiyPvDrC9lbdXvaqwWA4AqrG5abt6PLAuTe8uVQGdK+mgZVqGhfc1n4qzTVZ1wouEbEFkeD6VkyPlqvbolHDfHvQsWXrZ90qxKrBQ61gWrqd60CpaEUavXqtuI3ZXYcqdHT/jTIMWsUrEnV0Wi9FmRClgWrxc6+1VcIWe5/tYGz4CDRbz+JI4pyVz7kO2adWfvrWCDNNRfLVDrdl+2j5N1BLAwQKAAAACAAtZ0pSJ5TdOUMCAAD+BAAAGwAJAGN1cmwtbWFzdGVyL2xpYi9ob3N0Y2hlY2suaFVUBQABtkgkYK1UW0/bMBR+76/4NF6gyhrgaWwIrQpsrdha1BahSkiWm5xgb4kd2Q4XiR+/47RQTQL1BVepHZ/zXXxO6z1dmoJKjC6G5xczkV3PfonRdL7IRhfZpRj19jioDb0bT/sfN3roY+cQ3SN48Nwhrpz9Q3l4O1uIZ6w/jLrleZdIii3kWRxgN+QZ+x1EbFRO41qIXUK30Vv8SiPyVsQl7zAsIjPbPDl9pwL2swMcnZx8wWccHx4fJjiXRlOFeSCzIneX4LTodr4r+fg48HSWgAJkNdhQ
*/