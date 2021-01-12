/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ZIP_VIEW_ITERATOR_FWD)
#define FUSION_ZIP_VIEW_ITERATOR_FWD

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/detail/strictest_traversal.hpp>

namespace boost { namespace fusion {

    template<
        typename IteratorSequence, 
        typename Traversal = typename detail::strictest_traversal<IteratorSequence>::type>
    struct zip_view_iterator;

}}

#endif

/* zip_view_iterator_fwd.hpp
dV0kWIuOnZTvQ2ccL4J3tE7StiyaAG+0qdVVrxB8T3aG0yR5kMemDEuVXO7m2M63D7vLoNt7qjb6Gu8W3Bn60OFsLZ7LN7LVjXBjBUK5+afjkSeL1vKdtnmj9JnFpHHnwfcf3vxfNNMFh/8HO1+1cADl0QJOznp0NyedPgKYwZUvYFv6Pw5zm52uHc6f8c19oTsb+Llxbpca+bsW3zrg4WNV9Dx+dJBwSJ3Jh3GTyMMLY25t
*/