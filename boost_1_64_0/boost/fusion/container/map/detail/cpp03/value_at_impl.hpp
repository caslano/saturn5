/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::storage_type::types, N>::type type;
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

/* value_at_impl.hpp
j7RdDNyg7X6t8fq84jV/AyfB3yru9BVYAn8Hl8Hfw7Xwj/AmjfMtGucVGt874dtwD3wXHoLvw8PwA/gePGJpF89PEdsVY8nf3tSSv72KDfQ8xHOSf7tBlhwQG43xAm+BF8Jb4SB4GxwDN8FJcDO8HP4A5sEfwkK4BW6Et8NH4J3wOXgX/Ahug/+EFfB0dN4NY+B2OAnugLPgT+AC+ABcBh+Ed8KdcDv8GXwUVsKn4SPwfbgLfg4fh6fTtl/Cc+Ee2AX+Cg6Az8AxcC9Mhc/CJfDXcBV8GW6Gf4Db4B/hQ/ANWAUPwyPwLfglfBtG05/vwNbwXdgVvgcnww9gNjwCc+HHsAQehdfBT+Em+DncBf8Od8N/wj3wa/gc/Eb78QiiZzv62L8f25jjyF/uUDzxVh03d8KL4DY4BlbAXHg3LID3wpVwO1wP79N4vB8+A38M98OfwD/BB+BH8EH4BdwJTzH2C7wQ/hyOhL+AY+FDMBU+DGfDx2Au3A0L4VNwFXwaboK/hFtgFdT5Qs+IHGsO54uPFf9yVO3+RMflpzAeHoePwS90fP0dPgv/oXb9MxinrWdDOMohD/LX0vON9PxbetiA8xWAPeFpOm6aweHwLGveftXfx+G4XabzynKd91ZY3v0/pu0GO7z7X9zIv90SOBIugxOM7WE+XAmL4Sq4Ga6GO+FV8EVYBl+FV8OD8Br4OVwDm6FvLTwXroM94HrYF14P+8EboD8vsp7V9IzDnIktL/IPLfmTK7Veq1rWO1DH+sxnGdCzlvUS67hemdbrHmG9bo0Zv0wwHEKiNkZHxSLkJGhwDHrSxug6xaF/WzHogfjzzI3RJ5ST4Gjxt5OXoHGJc/y5D3vLkdAcBTs2Rp/0OPT8pZFj0as2Rn9n8egHN0Z/73MWHN8YXa949Jibousdk96LbZKQTGQDshM5gBxFom+mfUgy4kPKkR3IAeQrJLacvyG+cjeWzi1u+TbKd5X/z3A+n4z8fwEf/9AUfec/o6DQ+IxydtF81i4sCMT4r7PE+Pv0bLZFc5O3Icfikc6W99bNGID5xbj6c7JLfFlz83NqnfN39u/YfNI2/47tfXXZlqd36o05jVj4DjR9911sttF7/rnS9FrsyQyxJ89uj/zodh95aYiPvCyq2kfexvadxqKceXQQL+KbPrY2trYZNgb/aPrayi/U/ES8/ZukyYpXMJ53OsGvkb+yTmx8aJuNnXKiuQOoQsEf6h9b2/NC2u61t90eY5BRaI6xrPzQ/YqTIcRv5pFfu5nhQ4VN4XHa6O3q1MZAooT67+OWaoO9rX77vFqunAT1bo9yT9rGrnyT6sN8+XAtfgHt+0Y95ONuY49VwQ/uHCvT89uNlQn4eVcyqWNSz01LkS+M4w398vcFd8rcZUZn1p4rRH1g+Ta9fz9NqLZNttp8Fja7Wsv37tU5aiHyJfWl9HK0ix1UNx+r3a7qeJCS6v1cq20bZNuFSBM9a/+TOg872Da/2PTq1RqHYOiMtttm83MfkT++nWKaoHFe5BnNrjMvJ9/LZaHOcU0x/arjmvYmBOOaBkZp2fkJ4bFOz/QNLksILJvVNzz+aXDf8Pin9/rY4p++lTim5jbfXLGOZdc/5vrH/j/9Y/8y3+Nb3ezC16av7vuvDhs7Zg9p9c7hmv1j6VG6n4NbHOYdn1Cei6fgaPg0zIFVcD58Bt4An5V/4Tl4m/wU1M+9qu7J4BHNH+p7iWa5Tt8FXA+7yf+SLP/LdPldMuR3WQdvUv03w8dhOayCt8B35X/5GG6BzdF3O2wF74UJcDucBe+DWfB+uBbuhBs0b3yb5o0f07zxk/BR+A58TO3CXt13cY5Qu5rr+miUF+Q=
*/