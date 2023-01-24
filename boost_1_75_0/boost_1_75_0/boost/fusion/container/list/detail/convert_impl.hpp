/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1215)
#define FUSION_CONVERT_IMPL_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::build_cons<
                        typename result_of::begin<Sequence>::type
                      , typename result_of::end<Sequence>::type
                    >
                build_cons;

                typedef typename build_cons::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return build_cons::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
uvnw1BbSFg+I+0JRXs2qnzO9ABZybVqPyOxyCXU2SYo4Kv1ySy6RvIqlXmrEGo3pa5Q/LT/LOwm3lNtLP1in8sjuDHGSGtv9p4jd1yG730tN7f7GWHwzG2x8Tl9yUn+kkRwEHWurwIyQj6J8ffwpH8VTClGMgsZf9AgKmLEBRQFHtNoPDXcfhIHEDPLIEIOciUKYGeEG+axiwX+9gKRtiUC2noJi5wUGis2Q5DEgDdmRjfGxbWNhVXiifNkgW4zyz+CE0GPwL4O3anpQZeoVNhxCCv9COLHaehxLtGkHdM8o+3REPyjq1pi24dvdQK+6SKbXtKqsByS5leypR459W7mPtx7c+uZyH7UenHo/uU+gHk5ebgJhe9WPkvxaKBwOi7xqBNKmh4fpAA+Im1EnpB7ts7tI8oAQ8lWEDnDStlk3/UaAyjZMC7DMCcJfOLDp/upJDls0N30Hl9/e219FKs0Ktulie8ER9rsl5DXAia9qva2ZfNRgegqF40grfbY2Q4E4kVQ4sH1HEz8xMIVDKZ/HB1LK+sASFnvDTMCOUM3wYgT/qIOaZh6aZnotfOC0g5dk9jGPrEYa0Re+t/n6XMTs/L7wvc2pJBli0/n0xoNaB5vOqzcgtmzOHjyqFmsGlOXtmea32+fVvgh1VU1KvSTM3hIa1dvHnaEomocgXsLxZ8y0kMxucC5nHoxHckYoPem0hU3XqyceASVZ
*/