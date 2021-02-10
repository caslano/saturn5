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
TKSIF6v04rso69L5OErTo2qMdoLG/wVjcfMz5JtyqF+ue+DDj5tlWlBxiw1A7A+MFNET7uypmrq6HGCXieuyA5tqYDx9EHC1FmptwRZfp/IFB/Zmajc6gROS0PKP8LY5Jzu2WL597OKc0XRcHRAsYjP/DExskwk8XPBsPAPNX3hYT14KDQPja7o8A83ouJ49WYyd7pTHVcbcQiqaZaDr28zTv0/wpNRL3UbnTjUG53Q+80Ncal+SZqF9O3aCEImrkR6atusFIc6fmtGaRFg5bkou1D709VzZdix9dLf6xfaR0KwYNPxp+t5aVOMEc8t2/tlojJ7xN1BLAwQKAAAACAAtZ0pS7MHWed4IAAC6FQAAGwAJAGN1cmwtbWFzdGVyL3NyYy9NYWtlZmlsZS5hbVVUBQABtkgkYK1YbXObSBL+HH5Fn+LaSDm9JLkvt9n1lglSbMqypBIoL3u5ohCMBBsELAO2tZf77/f0AJKQnHMut0rFDDM93T1Pvw5Pn/95P+0pPfpz1H8HPzx5wyxLfhNe/jCx43yh8h82fcLzERED2u/44nTo0R1fqK12OJWMn3nsOI+I+cSK8Z8Bb/zk8BAz2lPsM5J0m4XrIKe20aGXP/74d+rRqxevXnRp6MahiMjKRbwU2bpLP/tq
*/