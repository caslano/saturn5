// Copyright (C) 2017 Michel Morin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_DISTANCE_HPP
#define BOOST_ITERATOR_DISTANCE_HPP

#include <boost/config.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost {
namespace iterators {

    namespace detail {
        template <typename SinglePassIterator>
        inline BOOST_CXX14_CONSTEXPR typename iterator_difference<SinglePassIterator>::type
        distance_impl(
            SinglePassIterator first
          , SinglePassIterator last
          , single_pass_traversal_tag
        )
        {
            typename iterator_difference<SinglePassIterator>::type n = 0;
            while (first != last) {
                ++first;
                ++n;
            }
            return n;
        }

        template <typename RandomAccessIterator>
        inline BOOST_CXX14_CONSTEXPR typename iterator_difference<RandomAccessIterator>::type
        distance_impl(
            RandomAccessIterator first
          , RandomAccessIterator last
          , random_access_traversal_tag
        )
        {
            return last - first;
        }
    }

    namespace distance_adl_barrier {
        template <typename SinglePassIterator>
        inline BOOST_CXX14_CONSTEXPR typename iterator_difference<SinglePassIterator>::type
        distance(SinglePassIterator first, SinglePassIterator last)
        {
            return detail::distance_impl(
                first, last, typename iterator_traversal<SinglePassIterator>::type()
            );
        }
    }

    using namespace distance_adl_barrier;

} // namespace iterators

using namespace iterators::distance_adl_barrier;

} // namespace boost

#endif

/* distance.hpp
yWlfHtQ4wusKdmXnf1j0O59hjdBBA8+g8mT4keZNeyceYpgbysN7ulD2ZY2kLsv+ckTKtAA1Zm/1x/nTel1H4egI2CqG8S3lhTHKRhnxedgxRXWz6ufSFDcT+noQaT/x4wqKgwWruEJHvPOKJO41BnThzLGw0NFrfsFoSVyNzle8XBSpTn/A4L+i+MCjGoOYAgb/CORybXC05K0uxP/6tj16TYqlYzEgmd7+7aZCYsFZzGYLKPkmetgFLiSSB0HiIzm36sgUaXiCPXMVodbzFLxf8YPahWnuCZnT0iZRiCk2REMBHgmONfFXRdH8/7DVbptmluU3J6D/UpkkBn+L/+N1yyWyIHMTgtP8ITnqjA3EcEihUMxhLbg8yqS5EWUNwnk1jFtQ9kqk7eFhlxUO6SafXVoh6KbPK9tIkgu0B0GN/gayc6CIIIsd0dT+6ZPB5tVlpmpkYjH3h7XCXmOvDZ7WjSbh85uo4wAzpA2Qrpc2dJNcBS25YqydsWmSBOIkRtw9fJQF3dEqPT0l67VyIoqzkHupJ1sAx5MjdrDGjV4LNa6CaGkfws2QcqJuljBCZEh3bBWrbx15ZiVGUCICURGrWHWF9tT3Nn4UDpDzD71bEtdjaDlgTuaXjpWgOXVT4vIGP0PNlMmEoZPTo0/KfOaZQSg5nhqeCt8iLNBm8CT9utPq6JUlvs0YmSxmOArvOwhHhmT5i3vAVv/5
*/