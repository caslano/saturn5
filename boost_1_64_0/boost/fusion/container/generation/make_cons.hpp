/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_CONS_07172005_0918)
#define FUSION_MAKE_CONS_07172005_0918

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace result_of
    {
        template <typename Car, typename Cdr = nil_>
        struct make_cons
        {
            typedef cons<typename detail::as_fusion_element<Car>::type, Cdr> type;
        };
    }

    template <typename Car>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<typename detail::as_fusion_element<Car>::type>
    make_cons(Car const& car)
    {
        return cons<typename detail::as_fusion_element<Car>::type>(car);
    }

    template <typename Car, typename Cdr>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<typename detail::as_fusion_element<Car>::type, Cdr>
    make_cons(Car const& car, Cdr const& cdr)
    {
        return cons<typename detail::as_fusion_element<Car>::type, Cdr>(car, cdr);
    }
}}

#endif


/* make_cons.hpp
oeRxqu6cx0sX1x0yfmQbaQ7rlmjzKOdc7hKV5lXG+8g5lJVkfpDBtaDNzw7JzzzJTyGpQLkGv9XmR3sNev5e15aJ9jxF11QXjpDrvo9JHXuU/J1mn9YUa36eZ+fJqPwXqNsyTbeXv4y12SL7ni/7vl/2XaIuX+Hm6Om1EugSP0LdZ3/ZZ0AtdeEWss9mMr7HUi77NLwhezaGyB5DY4Xs4ybZR7zso0jdh20HqZnmlOx8C/uwenxM+nL9QN2eaUaoczzQluru6lTd1UW7rwu12urG716zfN/nb4WE3PHWmIKMeU+drHqd81rbdqxX33/2jlHLbr4neOxj/mG1j7urc3ZXl+6uDr/qdfVPtVXmP7lx2esfvD3l/G0NtzTu7HduuLu6a3d14O7qqN3Vsf9+dddVbTswbuNw36YQZdt+xLmgjvE/zLxv/ZCbm52s9cAs7hHDlfnZ7TdGBtT86eyZ5IglEXPibnTXFuCuLt19W8Bp2/ge+T6DN8r4Nl8MMzFJXIQAvA87YCH2w/txFM5BdZy9fL/AUbId7Tj7eTIuZz4G4oMYhgtwCC7EWFwk2ytRkmzvK9leI1wl24uQ8T7XynavQ1secCQOxHEYhWYchDk4GKfhECzEGFyE1+MKHIqrcTg+gyNwK47Ct3AMfojxeARvwON4o7Mc+H7gvhwelvw+IuWwRMphqZTDMimH5SjnRz7D2bbB+Zkl25st27sDe+KdGIV3yXaKSCWynR2ynStxsWznZhlvNQ6b4y04HMfjKEzGmzAFJ+EEnIypOAPT8E4041yciAswQ8p1Mj6FmfgcZuGrmI3bMEfymW6Sz1+cZx9viYmSz66Sz24Yjd0xBkMxHntiMoZJ/nrjNOyDd2E4FmJfx/mSz16MMDhfj8t1VoRN8QnsjE9iL1yJfXCVbC+BVCLbmy/b88NY2V5r2V4bvArbYWtsL+XdUco5CO/BTng/Bsv2A03y2YktZPvVsLFsP1CTjyJZ7iaDfORJPqz4N8zHrjhVjmsaRmCBlO8MKd+ZuKSG6ZLtcscZy3SBFBDC+CtSImkmyT62Lj2C9jLSKpK+/S6Q9rlIklE7XmElbXlBGEEK49+J/T1v1zvRX23bCyPFk6zSzrcEfZR2PdS395VJm58pkr9jINrb/mIi3bf/FRu0AR6OZH8ko7bAcGkPTEALyV27YDHzdpFW8e9yLMXGA43bCYukrfA4yS9K02YYdel2w5goZ9thIv+eTdK2IS6JcrYjlkSxDqk4xFfaFFkvyrVdMS668rZF/0HO9sVotLcxzsUS0h6Svr3Rb7D7NsfAYvftjoXMKybtIp0gGbVDBgxxtkXGk2ba2yR17ZJ7eH0ez2PjGH0bJTIvc5uPo60ygdcFpAXSZlmCu5TXvdguZbiXVE5qHOprCiPFkiykxaQS0h7S+VDvGELv5J28k3fyTt7JO3kn7+SdvJN3+l+c/qT2f+J0X377v9IOb1Ge7zeDdnZ7M1Zukq0jAHVNjr+bbnP5O/Hd8nKy89S299eoYO5vbyuU+IFx0qYzzN5OptZVDxo9Wg07b98SmckzeRBL0N5u41fNXfuMu3YAd/XrVW8fMG4HqHoffOP2E/ftG5bhtuM6+/7ar+9dnL/4+Sand7RZz8OU1HpQKVsp83JdnNw2Ul/YHoOxA4ZjRxyMwTgMO+NcnN3D11RE0vbJP0iK0cW3jZd6MurHJOaBaz/3NKl/0sc4kFixUrej1tXEGsSBLe3hrRPxTt7JO3kn7+SdvJN38k7eyTv9909/1u//SWmX//u/ofTT32P7/Z+Wn5U13fab/pUO6nEc9/4O807eyTt5J+/knbyTd/JO3sk7eSfv5J3+ot//WWk=
*/