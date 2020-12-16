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
ZWBlJCffDD+/T7khSbIuJJGxvaO+vXF7iyL/liXWR+sLfBw+7yWmd6mOwT/T2XGo7CwrY0xyLi9jJ5buNw9a0/oyyzshaYNjnfKsY7GpXrTfNHLV1sz0Ci+DD0xQMvh84C8sPY2+3+CLLbv/gZIPusmwwdthg1zwGQSf4bquTVrieCero4z6iUIq6wHicYVjq3LEcTXzzx+Fz6iBo0TfJ2reP+WF23gx+clelnd60jyMqR9Fvd9RWh2R7yrfZXocj/yjmM5OCrxE13XobBfidS57/uOkhViV+Rr4jdJtad3R6WPlnALdpxndZlZOWgFbO2nDf7xv/Ch7viFpQVKOUEbY5yeQbj/EaK5OWgmd+bBS+Cs8yXTMxHrSS4ob9hhDuh3BdHvIMQxWKMWpRj+Dbjc4NjBeTggyRfvATm6nSvZsJvW5DuVedt+QVKzMZ/SlQh+rttVH2PMxjtehN5aGuwBLuzQpSRmRFOk7IG97c0uTzsY/xler5egPwQZbe7wXTuiHsGWAhwEP4cFxQBP6z2bAZNDgGftmvheg/h0ABrA+slyxts6krkPC3rp1SPBKa0eac33EPojWIqmvBZ34nYvasTBeUH2zgHxT7IMHxsvXMkK/i57rY7aWATrtWgbSDNcycIHm94PXMtRr0e+tr2VMBK1mLQP5Y69lnEAjroO8LZK1jCOXYe1ovHwtow/PPOMvzlrGit8br2VU/t54LeMqPBPWMlCO8VrGvXgmrGWANvZaRiNotGsZR6kcsjXKia5lnIdOaqCTLZK1DBfSVwK2WlzLUO2ya/zQ1jIu/O6tWcs4NSFc2Hg1HTCO2onrD7ydYJzCGorYTmRjC8qD9h/dg0RrmBQThD3PVzT9PfeFSey5k35jxb+Z4DuJldggg/Ugyjhpcpjwt6S/FwH9qLBisIxgdpCMPCZKLaP7jjIBpVYCrgPcCpDoAGUajj1Y/5zOaa5APIZSnpfStfrzKoJ+8k6z+YbYjvh3tw+wvB9BOanKZYBqJVmgu4Hvtbif0d3CVpKn0FygNCXcZrKJv02M5odSO+Xw58W8Pe3CPfVRVBbrjvnY/yh7Xsd4y+bjhiYv9WPsvTEDNs8UvpftAN4GPAGg7umaCKzetwIie7pSbLQLet9o3yM8jg74RrpXbS+MH/CIe5VHzX6IqbSGjyabSvhbSGtgtulmjVgd3dNRWUzex8Jn0zRGvjfmATcz+nTs6bte+Rz84ClIJPEnKtchlrNZ9IlW9jxXNo5GXuN1xe3sWRaPh+Rn905u03F/pG9f3Bc3K1Oozncz2leV0SodvnPdCnw34Ivg+CRwHyAyxvkDo10M/uYIZTUqE4iPLva8XxmLumbgl3+3A78HEUcOoeQXlFS+L+cxRteBlcEtFmIlOYHgp6oM9I2rNvw3vnHNnKtQ2oRo2kyFvp++cjqSNo/df4Dfz+HjGNUOBbCneD4JpW3W+kvX9DBjTwCchL8B2sAfNf6yrbFzm95fuL2Wvhyei5eRDQ6z/A9Cb4thVcQ+Z33SSPQAw6R+hPq4H5VJYlOtfpnmEFT+C4y+A6U7lRq07Y2D+pNW/m5/jtEto3uMV1g5ebxfEd/FzzPaCng7jW84fQpoKlm7e5nR3KBcDio2/yN/KaMyfoDnqqcVoZx6yNoO6ILc9ympujIjZz7fUMzAwjyf/OblqN8sfJn7iDviI1N52gJ2P5rfz2f3v+B+NU/qM6J/OGfwswxwgQbwc9D2sjK7m7Cxun2nd2Z9c0djWxuNvR4xPrcO+ax9C4z0jyiLjbNFnnqJpyzKkEk8HR7E0yzLPB2+CDzVvi1MOINimk0nnoKDeLpcxhPvK3/BaCfJ10WIR/IZjDk=
*/