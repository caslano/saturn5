/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return ::boost::fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
kxYl5s5nQqGxgC2ko8lHHau0Wyejb3j3dbghY+ex3iUcckKes9BguDva401cOwhr7U9u5ro+UZ+U1vLuKE82c90eV7QnTa7d6Yp8so3r1kZ9sp1rX4nypMFE2RNRn/RwbVWUJ1O47rawJ9tsNPPl9KTMOgwPpnHVeS4mdwiYrEytCp5ms01dLBoyr2eBQRd8bjnVSQtFXSfjaQDAwxS0Qc7gS1CTgli/Lg94rQU8KRuY05IZa73Ws0QthWl7Is0sTR3cTQXuwQmkKmnWq5s1bJgqs9HKHdZCiXOBg00K2yqiwnz57ABXmRU7wXpC9YpNcMLaeQ9K4xnRXgu3eNvfEUcMDE3rbJ5W7WtpWlMjpzUVp3W1bVpnsGFxqj6tqfq0RsxjGjX1Vq+FWCi+K2/2qFG3vC5uWUP/jAhojhQrAWcvqADZK95q+6vU5vHBJHby2Js9hg5vXnlyKGf9b8viMaLBZzd5jNA6eYjhtg4nc8vp+0Mh6K+L3OH0rL7SsgPoHsuywwIErx0QGuQZwqT39Tch8eXs/YB1vkOTLDk9+/HRaGmVW8A45bBpJJRj5Q56n4PNbwz5nrg1nDRaPqNj0mjuDEka3YTUy7fX20mjT64H0qidI0/svdEijR6MCSONQmcBaTQsgjLadRZTRoU3MmVk7em8ScHizMUV2GR2G+vioMsnxiAtSU3LroKjfoHBvn7vGkSTltBJUXB2
*/