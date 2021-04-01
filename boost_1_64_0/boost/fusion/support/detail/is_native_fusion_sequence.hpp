/*=============================================================================
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_IS_NATIVE_FUSION_SEQUENCE
#define BOOST_FUSION_IS_NATIVE_FUSION_SEQUENCE

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_complete.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Sequence>
    struct is_native_fusion_sequence
      : mpl::and_<
          is_complete<Sequence>
        , is_convertible<Sequence, detail::from_sequence_convertible_type>
      >
    {};
}}}

#endif

/* is_native_fusion_sequence.hpp
+uivkYaMz7Swlqrkdk8MkMjoJAK/lPfCOjKNVxhgeKahsyXv7Vvl2FBM/daK7KvzIGaiZy1AzvWY+T3KFxLEiBKa01ellb0DOtCw3QNWaeUB5Q/EEeyb2l/Lh3eaUw61QTtCSA6mYUfIf1qNwZYXJ6jVIY3QBtZduTl1svCX3cdZPH38/5fNd4EK1ygc6RBvd0VZYEE5As0XExhx7u9Vpsu2x5oHRHS17N2wiVCTvXvzusJf5orQlXo93p21rgLZ+xSHclk4y1OELw+mzoYNx7ulK70oG0UpJdwyMu+e+uJgm6kqiMMQ4GPFxsrY4IS26lz/9BddrEuvTCr2B58jdPw8rTArikWAZ/uzsnJI+0HNdtDUFf7GUJb7Qq9p9DPP+6FZuraU4ZNmWuMWqawwXT1naB0Pjk7HFOcsdi+3Z9WMgY6JdQVVs8OGg7DhRo/HA8ZUZrifpBcDzZK7HxCdvmrSD2X7YpHWURE76o1dmzNxDU2yDJi9+DgNVbmfYBycKjb3bX2lkU3CblL7uxOXg2hoezW9rw0T6zgVdt/OuBcw8Ss6hg4xJzT6qw==
*/