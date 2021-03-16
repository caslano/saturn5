/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_ITERATOR_05062005_1219)
#define FUSION_IS_ITERATOR_05062005_1219

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_root;

    template <typename T>
    struct is_fusion_iterator : is_base_of<iterator_root, T> {};
}}

#endif

/* is_iterator.hpp
ndywzRrT9fPD+mzM188Pa68xXz8/PA0b8/XzfX50Ab5+Plv5+M6SrfhIjm860IBKzgtPh/pcch5TyIQ7WqagSbkMjG5xGQynA8DeAoMcpTJVkaCOpzNVkKCPpzOlR3fbTOlxOgMEd+OMNExhW33B+3S2IywsDkIn3scHkZLzArDh/X0QoLEmHBIOJ9JCqrB5DyfWQqrDOMDgGeUwDjNUBkEXLNzC5WJOvOgDTnwoiCkSTu06URpr/Djpw4jTWIM=
*/