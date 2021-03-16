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
tpj8dUp+hKnKdsusWlYNHz/L4fL7G0gTuAaL5Unm+hauSMn3HDO5f6Ea682xS61Cw3RZy5YnhSk9xAzvRnZb9Cxhr1QsA0sNA6k5Vqzw+6CdMa2dDatcL1bKQu9GNguebJuUWpa11SxBmJb6cMnWpDb6DZ86uQgGg1IFxuNPBTGjER5msB9RsSHeD8unDNtRBbSGDxyxccaLtVYotFod7qVivUHdtkdoQJPBFAEgWg12t4Ps7wXr+kYSq8X0rkY=
*/