/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
uoVgSd8EUxrZ6BbgWl8RXcrdjpuj6Yd8mivXgPl8NZoLW9lfL4VEwfM9mwHYUOaaB4nyXQhychPgpx3SW7t/hzkBfDq3iJw78d036+FxZZorfke7kNq22VvL7EO9gt0eeR8s7I9drY00SOlLf951NnNzKruf2vDE0WAhWymg12CUr55qCr7TF6h0b1UYq/X3B8JbPr2qWyAnYTjBNvWhGbfTZkK2qtGeYKlmrZcCShfPmdn7IgMs8Au4yf6ts5ykIakbtZ5hTJ4XnmhbZ/D4ngl78G4kJbcgPUJUc00cz2sQdJZvnbw3qICU7qErvq2Zxrh6Ho3i+JJZum62Bq08tB2yNzuiiZq/idrTcdarRc1tLlY4mdW4l9ItppdU5/m76FhrgpEclHobgmGUNaJw9BI3VGcJLizQogj/uaztAGvnU2FOESVcFnaq8S/luw7ha9RKwrpjItNnKTC1Qz4oHFd+C88B3EKBip136MxkwQ1nOTBCGn/BQGcrGnzAQOMhuSC0LvCHzrWf/gCTQIQhkw1F9g50ZpLqlOuxS79xu7Bijwd3e692PaYWog==
*/