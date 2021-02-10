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
C+mdu9hjOKS7913/f4FM9F9QSwMECgAAAAgALWdKUoJIy7TvDgAA0icAABkACQBjdXJsLW1hc3Rlci9saWIvaG9zdGlwNC5jVVQFAAG2SCRg3Vptc9s2Ev6uX7Fx5xJJJ0uxnebapumdYsuNpqntkZy2uesNByIhEQ1FsARpWdf0v9+zAEhRspyXaz+dWsc2COz7PrtYetD98z4t6tIHP4H9CvDBd3viKte/yLDYvzsI3pH7D6d+xvcPMRnQ5si7oEMfPvKO2vZI4Ll8zT8HwYcY/cyy8T8DPvlzwD9iBcf45KnO1rlaxAW1Tzt09OWXX9AhHT8+PurRmUiVTGhayHQm80WPvo7syj9icXvbN/KbHsmCRNL3pK5jZcjoebESuST8nKhQpkZGJAxF0oS5muEXlVIRS5qrRNLp5dWb8cW3PVrFKoyZyFqXZGJdJhHF4kZSLkOpbhyNTOQF6TmOg3ikTAGCZaF02gdvSYXMl4ZpMHuRGE3iRqhEzMBIFBQXRWa+GgzCMk8g/SDSoRmElfr9uFjWmryBEEuxJp0VVGgqjewR7+zRUkdqzt9hECxm5SxRJu5tpAGrNBronIxMEqaFc0oaJ7akqTdPj7dRBolVwd+MTg2zWsV6ubURdmQq8zJPwQh2wKZIw8w9
*/