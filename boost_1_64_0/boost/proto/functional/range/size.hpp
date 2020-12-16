///////////////////////////////////////////////////////////////////////////////
/// \file size.hpp
/// Proto callables for boost::size()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012

#include <boost/range/size.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::size()
    struct size
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_size<Rng>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_size<Rng>
        {};

        template<typename Rng>
        typename boost::range_size<Rng>::type operator()(Rng const &rng) const
        {
            return boost::size(rng);
        }
    };

}}}

#endif

/* size.hpp
JGAJt9rzZYIV3ArfVyez+nK0zKrhXJm1Rm23wj1VFjRsGPKcBIu+za4hWWbFZUJcHlgxWDlYDVgjWBtYt8xa9yFZktXP26CfHbYFwNaUJVjntgO+t7oDvpYD5jsdxmwCuwnyfBDmG5QFrH5CDd7b7bOSejt8LYcsxbCdYMwKiDtXFrTuDxDXL0uzaoe4uDvs+VaTWXEFEFcOVi8LWOfoDjhHEDcks9bokzvg/ncnPNe4E95TlFnz5chirTN2J3y9N8y3P9hxYOfKAtYZk1lr9BT0ZUTmN2wC4r4H83faZzO9E15H6YSvpwU7sRPeN+yE7zmXxRnW0Qnv38KYL0Au78GY01Bfwl123Aoyq9cbyqx9XQRj7i+zcjkF7Mq74GupZNa6vwxjfg4Wd7dtK4NtLrP6UiKz+ll5N7zXA9YGufTK4q2+gI2DfXs3vNdzj117msza11myeKufELcTxJVBLidCXAPM1wLWAdYjs/bnG2AzkGdcF7w/DbZaF7w/LbP2565d8PmYzOr1KWBNsjTDusFGZemGee+F7527F37uwb3wte4QVwRx5TKfYVWyROu8Qw1Xwnx3Q559sqB13mXW9WXeffZ8yffB1zJC3OYQtyvEHSELWD2TWbW3yKx1aIf5emHMl2XW/X0M6pu+D947u9+OC9wPn6tB3Ob3w/UT4g4COxHsArDrZVavHwR7+X64h4PFdcPPNZKlGJYrs9Z9e5k136Ey6xzVwXzXQ573dcP7FjKf1bNueJ0PLPoBeL1AZuWS8QC8ziezat9XZvWzRmbVVw95XgPWBfYs2JjM6tkM9MX3oG2BB+FMPwhnWmb1uhTiKmG+sx6Er/mSpRrWB7m8DfNNy7yGeR6yr61xMutsBh+C79mSJVr9hDGLYcwyiDsOrF5m7esmqP16sE5ZrHVthbh+sGGo/UNZ0LDYHvjeeFnA2vMya75NwLaXJVn3MbBTeuBndoBd2QPfvwn2COQy3APfDwu1fw/z+R+2z+bKD8PP+XoYPrd/GJ7vgtWCNUMuHbI4a1/L/Na1HOJGwD6EMb8Fi33Eri/1EXiuAXHFj8DPKYW4EyGuXua31uER+DlKEPcI2AuPwGtWYN/KrH3te9SuL1nmM2wFiMsC20Rm5bmTzOpZOdgpMObFENcO9gjYENgnMuveMQ39jOq11z1BZs23ci+8ftYLz23AjuuF17ZlcdaehxraYb7HYb5hsE964WcCQZ7ex+y4BJkVlyqz6lsTbBOZ17AtZdZ+KQLbA2o46DH4fFOWZJ2Vx+CsgD0iSzFsFHKZksUbFv24vQ4JMmvMdJlVXy5YMcy3v8yqvRriznocfoYN2K1Q3yNQw7As2loHmbU/J8E8T9jml1m1p4BlPAHf+wFxm4MVyazad4W4sifg8w6o/awn4OdVyqz1uxvGfBzihqGGcajhW4jz9sHru33wNflguTLrrOwEcQf1wecWMqu+RlnAsA6wfsjzbbBpqMH3pB2XCpb9JHy/kyzO6ueT8J4N2HFg9TDfZWBtMOZ9YP3Ql7fBpiGX6KfsfibKrH22mszKMxdse5mVZxnYiU/Ba78Q1/YUvE8pSzbsDbBpsPin4WuJn4bPfZ+Gz30hruxp+PpryOUyGPNWiHtcZq3tEIw5IQsa5uu3nxOtLLPitpRZte8LdmI/PK/rh5/n0Q/fJwzzDYNNyaz96X8GXkcBywPb4xn43giZ1ZezZFbtLTDffRA3ILNqn4Axo5+Fr9WUWXFZMmu+Qog76Fm43z4L7zNDXIdsBcNehrhPwKKfs8/KCs/B19TI0gzbW5ZqWK3M6mcLjNkrS7HuY2CeAXuNkmVWfWtCXAHY/mA1MmvdLx6Aa8gAfE0=
*/