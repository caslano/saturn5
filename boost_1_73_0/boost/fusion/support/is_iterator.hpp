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
POZPqto3+ndXca3f+FLX06Hlcwecxucrud7a2NzQiV7j803xWo9D0i/R5DUdlvwnGpLpli5dvpTvXYcSXpHfsMP6Odl+7Fgyw2exqS74XG8yYZRPektbuzXdIwZon3dp5dcF4rUJs04J1XCS5MmjTFXPpX1+oqHjukqxET9InTdsjscjXmdMbCBdytA+79TKfE48aNiQ4Zrq7MRI8b3mI9Fn1DFQ662rjySyny8VH1C81Ena
*/