/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_NVIEW_ITERATOR_SEP_23_2009_0948PM)
#define BOOST_FUSION_NVIEW_ITERATOR_SEP_23_2009_0948PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

#include <boost/fusion/view/nview/detail/size_impl.hpp>
#include <boost/fusion/view/nview/detail/begin_impl.hpp>
#include <boost/fusion/view/nview/detail/end_impl.hpp>
#include <boost/fusion/view/nview/detail/deref_impl.hpp>
#include <boost/fusion/view/nview/detail/value_of_impl.hpp>
#include <boost/fusion/view/nview/detail/next_impl.hpp>
#include <boost/fusion/view/nview/detail/prior_impl.hpp>
#include <boost/fusion/view/nview/detail/at_impl.hpp>
#include <boost/fusion/view/nview/detail/value_at_impl.hpp>
#include <boost/fusion/view/nview/detail/advance_impl.hpp>
#include <boost/fusion/view/nview/detail/distance_impl.hpp>
#include <boost/fusion/view/nview/detail/equal_to_impl.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;
    struct random_access_traversal_tag;

    template<typename Sequence, typename Pos>
    struct nview_iterator
      : iterator_base<nview_iterator<Sequence, Pos> >
    {
        typedef nview_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;

        typedef Sequence sequence_type;
        typedef Pos first_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit nview_iterator(Sequence& in_seq)
          : seq(in_seq) {}

        Sequence& seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(nview_iterator& operator= (nview_iterator const&))
    };

}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Sequence, typename Pos>
    struct iterator_traits< ::boost::fusion::nview_iterator<Sequence, Pos> >
    { };
}
#endif

#endif



/* nview_iterator.hpp
8xATJu7ddHH04jSjsBUX7qMe2o5wS91LtFI5vPg+Zlgv5LMWLwFn7yaqtUinuxN6Xz/KoEavra7oP+u0XBzMunpgUm3xbipdBtIMNIMWC2DhbNZzjqlM3sVbjK107wEco/UuAx1yDvPkxwTlqy1Tv4aSbFf3w6Z3uoGAFNKpscM4hRae6VkZ2QlGctSvofruqb6nIO21Ln76HqcwdXXh+6zdN6Rmx0FAhKhMVF24wXOdflwO+xji1knfVsO++D8eUEFyNsHs+pUS3OQUw689ht+NuT/ZyfrhaOu4dkv4oQTcFTNhyccv/rgEOtYkfVFP6XTfZV+Gno6nVfce5SkEqysmMdSca3IWv2+YUUe7EOliGZatpxQy50grseTyfaHJOwBtv1t2BNLWCIBfRWi2aZCajnOxp2K+tb4/Pp5k9ILIKSC1KP/aMskoKCeRrZ05xgCm2LaxUWqIz463GI630N/GqDF7+3r/sRNwDIL9DVGUXGHSKauM7cYY6DMwoKKeNZeNPPMEhEbMfa0DHnda0fTdYRZp1rfiBzbmpVT5u4NcTsXMU13H7glDuQ==
*/