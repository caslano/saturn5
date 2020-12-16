
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_IS_ALL_SAME_H
#define BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename X, typename ... Y >
struct is_all_same;

template< typename X, typename Y0, typename ... Y >
struct is_all_same< X, Y0, Y ... > {
    static constexpr bool value =
        std::is_same< X, Y0 >::value && is_all_same< X, Y ... >::value;
};

template< typename X, typename Y0 >
struct is_all_same< X, Y0 > {
    static constexpr bool value = std::is_same< X, Y0 >::value;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

/* is_all_same.hpp
O3+JlJxxCdNSPG6RHURTiIclnIUSx23icVgMFUu86yT3ymcFNyMKQZOYklcXxGauJD4yWMsR6RfhRCmTNRyRN4WxJZGXQXODic829jhE/13AQPs0odV7sTW44yGu38/fKkY6bmtoK8jbwo4sDkY7jNEimXaCg922JrW4AKm5O9pkqo2dW4Mp/h8ZXKz+3s7UTqxcYPh7V+Acdg79jcDJaewEn/LiDJ+1AfPUi2bEU3zu1JinpWD5Z7sCFewM7FPyGP6GEflMD8Mz3vmLs6TrRPj5qhD/kNtAt+eJKFzYZOQiDEd2AeOJxWIg/+UEtl4ME9Qm6E6Vjok54MygaoMVQBipiYl5OBfokFI/sJHHwe4A4nldzstPOGMPRq4BeKtf6Xl+cn0gUM3OXTCZUPXwcnhXIHEauwtsIaTmUG0ae5gljPzckDrNYUqtSkRQKhBNqSEmNWBI9Vezcy41CFJR1wKU6pebj1GpTTCWQgZniJyuiAwmXtyQi5xORAaYSL8hsqqanXORNSASFb2U3QVdFyLdVOQBTCQsn9JkiLxMEVmT2ANFXkZE+pnIKkNksJqdc5EhEImKBlBkUG5cRUVOgQc+u/AAQ+RVUiQM9Z9vwEVeRURWQW5riKypZudcZABEoqJ3s7ug33J7IiqyvYdZgF04xRDZK0WCL7ShyF4iMshE1qBI5knsnIv0g0hUdBMUGZKbHlG/7TL9tt2QeqND9du/wiCVETPy28Ew9Vsv7Wiz4bddpt/OIH57DkqdkZnf7hSmfptPpbYYfttsiJxJ/LYcRc7MzG8/XJ/6bQEV2Wr4bYshchbx2+vZzVCBZ+a3U9anfltIRXYYfttqiLyP+O1aKPK+zPz21/Wo3/qoyJjhtx2GyD7it/3rcZF9mfntWetRvy2iIqOG08YMkf3EabdGkf2ZOe0S61GnLaYi68Fp2YVRQ2SceOyb63KR8cw8tndd6rElVGSD4bH1hsiniMfujyKfysxj10CRVYZnNhhNDxLP9GLTg5l55qs16Jn4IO2MR/hDfv7UYuPZWvKAg/2ds0h0IkbxFDF5pZDpFIJC+mu8C71Ge0EPI8AzfOIoY5s4zCa+fHI1h2J2Zr68VTX68sTpqm22MkRi6KJ1eFeHMouhpnUwhiZSV60p0uskcG9bm/fz9cwCt21tDNyJ1E9rXjaHjCJPhHg/52Q2ikwN4SgykfppTQbfIw/Vd9bi/Xwvs4fqjWvhQ3Ui9dOagc4lT/Lv1uT9nJvZk7x/TXyST5x+2qa9n5BR14Nd/SSzUfeVNSbeqGuTayfIqFu5Bu9qIrNR97OqiTfqWhP8L8moW1PF+/llZqPuX6tPvFHXWlUsIKNu/eq8nwsyG3WXXH3ijbrWUuYHMuoesBrv5w+ZjbprrjbxRl1r/fQLGXU7VuX9/CWzUXfLVSfaqJtctP1BhtzpQd7PPzIbcvcOTrwh11opOpzqeDtzFegnI2Y03h63ysQbb63lqdupjrdPrQz9ZMSMxtvzV7YtT71OdYg7hDfNiBkNcdXYdBBmXKDcgqWYq9kDkv2L8kHCKZwqH68MgBJQMJqDzjcreTgeqUYc1gJoTcedB1bCcYc12WTUQIb8FvavngevU4DdzS/GOU2oEcl4MAVVqEo1GLBGQAU6JFRjqyHW6gFQmxjyW9m/Bh5UTgFC/koShCoo3Mwg/SbAhQdTRShrAYTTOH0gIE06BQoGQ3gH+9fGPd0p8/+AhCkIpZQZOUej8JpUYcNaAOE0eDYISHu2QxZvCI9Vo225BzoFUr6ARKoGShzTo7+bzOWHmPzrht8+QvU57srsbpBNHfrRyYYtMeuE5NoQH2X/GrmLOgVE0yZLiEJQdpg=
*/