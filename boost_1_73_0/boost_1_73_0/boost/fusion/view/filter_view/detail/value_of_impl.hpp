/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05062005_0857)
#define FUSION_VALUE_OF_IMPL_05062005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<filter_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
icq905Yc1934HRhQjc8xLXS04tI5X0rnfG36ReZmCVct3ArhDgvXIFwiUud5gpH6YhW/XwzGkDqMRkVlVaWlIj7UmOOLL+Y4HUsyXUQyXejrwsLVCpfIF/OKuflirNXxxl9cF+Z/vi+uWkLV7JNY1Uyc/QNnkoSpSJ+YimTWfHJcCeNJ5lyRzLkkhanCzRTuceG2CJeItLz9MhoC49UPK0b9KF9aHtWqY7ZMdGM+QRdl15FYzRN72MSkKs2zg9M=
*/