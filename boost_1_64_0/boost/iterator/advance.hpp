// Copyright (C) 2017 Michel Morin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_ADVANCE_HPP
#define BOOST_ITERATOR_ADVANCE_HPP

#include <boost/config.hpp>
#include <boost/iterator/iterator_categories.hpp>

namespace boost {
namespace iterators {

    namespace detail {
        template <typename InputIterator, typename Distance>
        inline BOOST_CXX14_CONSTEXPR void
        advance_impl(
            InputIterator& it
          , Distance n
          , incrementable_traversal_tag
        )
        {
            while (n > 0) {
                ++it;
                --n;
            }
        }

        template <typename BidirectionalIterator, typename Distance>
        inline BOOST_CXX14_CONSTEXPR void
        advance_impl(
            BidirectionalIterator& it
          , Distance n
          , bidirectional_traversal_tag
        )
        {
            if (n >= 0) {
                while (n > 0) {
                    ++it;
                    --n;
                }
            }
            else {
                while (n < 0) {
                    --it;
                    ++n;
                }
            }
        }

        template <typename RandomAccessIterator, typename Distance>
        inline BOOST_CXX14_CONSTEXPR void
        advance_impl(
            RandomAccessIterator& it
          , Distance n
          , random_access_traversal_tag
        )
        {
            it += n;
        }
    }

    namespace advance_adl_barrier {
        template <typename InputIterator, typename Distance>
        inline BOOST_CXX14_CONSTEXPR void
        advance(InputIterator& it, Distance n)
        {
            detail::advance_impl(
                it, n, typename iterator_traversal<InputIterator>::type()
            );
        }
    }

    using namespace advance_adl_barrier;

} // namespace iterators

using namespace iterators::advance_adl_barrier;

} // namespace boost

#endif

/* advance.hpp
4DnAjwLPBT4GPA/4OJX3E+DLgX9O97Xhdf6Y6/uydf0SwEkY0Avc/Rat76eE7K/xu0P6df6GIa71bwqZr/enVETX/Gto3V+75i+u9/eEhr7m/2BIXPdHucAnl9pf/983xG8AvZLvAPuxfn8wsYafuBJX4kpciStx2b7ewvk/5mvxz//V3+zfi8HoAAaWyQr7aZZvRz32JaOWyG/6P4jn82eLz3eAtY72TvpNf02xEj2vyMF/88WumYAD+RjfhtcPqteurW/raGyup5LAS6eSi3lsMugyUMIdLoCF307RvBT7X4zmb8bztC42P3zVs/bA5eurL5z761Nfy3rjlSTj+Z58Xmd/v6d8vmQ0L7I/T5PPn8Pzq5UK2YBs46a4kuWk1Mk0v5oGnAs8HXg08AzgacAzgQHIi31sKGTTKMQ0AkjnFsKcQpxPnATQHILmDbo5A49f1qOZD+wF5Av7fDDm143zMcbnY/sUGsPv1ozbabyuGavzMTrG58KYXD4ep/E36AzG23U0rt4/KjGWTlyJK3ElrsSVuBJX4kpciet/+XoL5//Njb745/9qnD8/5veH8pLVmH3t9SgR83qePmmcmt42KP1DSN83W01HIj1AOvs+H2LrCPgReT3FGUL6h0HfzOIIIpxfSzNL24u0PctYnR0KlfsRpA1cp6YhL5Wrri/UCjEDN1HMwEccmPsD7wf+UiF+i/NMlhgzkOmJ7RPg3+ORRDGuRgLvZvRVjmnKCPyWcJX8d+LPaL/Fd/A4XcfYs8WOZxQXq+NRFnOoUZWFxy/KjMYc4vGWmn+p5vs8vmdOZvkeoXxiDKpbGY2LxXyog3x+TD+vLob+pma9LWteWpIzNZnFzKlBeg9gPYvPN9WZXBiNh/NSQTiuiQqFVM4h0F7DYhDe4XSmOjnt80Q7BfcZuF+eF47pJ8J+QDdhQDgOkcX4WOoeg6/+MrLHYBa7P8rvoXNxzwHZCWlMh9Ar0qBXHlsFfiD8EHssVToGcNNI8HgySxvPjuJsmMayo3wOojWNZQda67Hs9LSdrbdQuS6B1qWh9TMemngMq3yBNj9Ky234eKH1GHmQTxsjD2kmMfKIzsXTIAPRqbz4Wd4mXRyoInKKx+lbPvZBoD/B7wr1Nmrpqlcs2SkgtVO9PBaODTvpaUlGapM/wXOkQQ6P1HYBA9sVU0y9H7HnfmUirLcOktymZEnsKuNjS1vj1k5GWyTQFgm00X5mm9q/sTIfY89uR++GElh5SAfe8KyaniPkaWMyFuKvIMvzEWU5ahP6Lt5nfpM9D0C3KdgtlSTQNHE9hRjNbGUSaCJ7sk6wtA+j/7+H5WHKQ8y5MupLH2fPH1JS8W8K8l0Pynehf7wff2erNJzvJJ2Pu4bk4/Vx+biaVsTpmH3A54KcV5gcjJbdVz/L7wfF4qzL4H0Wu0YDvot+rhf0mnbR1h6JeTHBtF0gr3BefbFp/wVa6+0CtDxuVgkyDwD8OXg2WhH6npgxtAbZBrLobHOmOHaMzoj+9mXK9RfU6w8vE2v6C9rQX9CG/oKC/jbB7vMz//36g5tK9ac8p9Nfp1X/U56zrj/lOev6Ay3X337orivr36e/yNijhOK6PQtIpj1m34f+3FH9NeELma+FdIdOBekIhi3XHeVzCLRQO707ioDnsec/U5agNh/gYYBEr5Jy0H3QmLcQeDV7/kllMqS5HiDRNy8jl495Ed9RZV0YO29nNLew98AiQHRvbseNEb7zgRdwvhE5EfAwxTE7BRvWDQeoY9rbMJ51DHOmpiriO4dizuI9xsrIHzQ+3YsHG5D3KfBXDuim/a7XFgPTPeJpsrKuSnZA6TQfEcbYj7JyndL3iXZ/7K8=
*/