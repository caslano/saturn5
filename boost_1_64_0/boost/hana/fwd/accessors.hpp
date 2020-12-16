/*!
@file
Forward declares `boost::hana::accessors`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ACCESSORS_HPP
#define BOOST_HANA_FWD_ACCESSORS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Sequence` of pairs representing the accessors of the
    //! data structure.
    //! @ingroup group-Struct
    //!
    //! Given a `Struct` `S`, `accessors<S>()` is a `Sequence` of `Product`s
    //! where the first element of each pair is the "name" of a member of
    //! the `Struct`, and the second element of each pair is a function that
    //! can be used to access that member when given an object of the proper
    //! data type. As described in the global documentation for `Struct`, the
    //! accessor functions in this sequence must be move-independent.
    //!
    //!
    //! Example
    //! -------
    //! @include example/accessors.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    constexpr auto accessors = []() {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct accessors_impl : accessors_impl<S, when<true>> { };

    template <typename S>
    struct accessors_t;

    template <typename S>
    constexpr accessors_t<S> accessors{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ACCESSORS_HPP

/* accessors.hpp
20qqGp5Kue8SGIZ3/9IfRDwAH8DUGSJeOw59t724XENJHcz4dSH1OJ753SqQ1Jz1zOk4tCz20VOD+NGt/Ug6aDbx/SRxWcKKPV5STFdh3WXURP8rLcQclO1lq/C3E+r+/Jb3TVj+D/Yodaw+75Gq4D/9g1IpGKidWAJtfxlp/MoomwuvboPt+A+u2YgfxMsY4vUdVMOcr00qnxGiNbP1pbewMysI1DsssKso76Vooz5hY3+kqvoN/y6p2jinXqBbHEQhKIedXD03+hA9sq2lsnGJwh7eZMJ7Rzvx64e+hsu78Hz0U2znVRwUyd3oL0dfl53qZcIY9PEw4jNf1NqUDk6a39zCdisrrDt9K7RCJHc4gc/z6qXXKQ1JD+zLEuUE2k1G35ihVHQ9/FeosF43tAN23OS+3C9sXfi5tuX7itJ877JFnA90UUONzYStv0nZHrW5f+egDzkIDEaqI+VVrVIeS8k3D/2llIg7MCRBnwSaTeX7ivX46+aptdJoaYkXeG/2Bn82YtyMxH/lx/gx7LfGE0/Bno7cYMorfknQ10B8YSD95TTryNcShV6prHlHVUvcz/mXIvYTorOft6rGJmRZSAfn8GK1fTm1Vm433xvgFW/4lfjMYg1EMN4yp9sCD71s/2JP+yZgv22103zwGUUJmkwuzvvnXKKrxuJvD+KKkTq9A+mvc4zYwjTYm/sI+/xh9mtcpO/kKVkKs2IXFMcfRjC2QQrxlAvoa2yr9jzy9HKiBkNS9IRAeQJzeckG9mE9t87B+IlBThzYbS8r1QJZbiJfRk78iYdEXLiemvTASN/7TF2NmSYwMvv7BT6ptCgsxAecjxtpvLSNODceJjB1OfJhiYzmoJh2Ef1+N99zYlttLs/+3Yw+/h1/WFPe/60RcK3Ae5/VqjsFhX4Q6uDITuJyqiDfTTRWKtxZTTrg19tDpHD1FsaPMQhsJOzRi8QvWxI/P8D3nHPFxT1Q2auZ2Ofo951Y8m6lJVAtnt6XMBfo3Yz1jE1SraLAZs61vZwMXW2Ip5xW429OCdx+LFBsp4grFFOqeQXe17FE/4ipfzcf5zNHvUNHle3xYD3XFjhD3VaApALibJSb+7cR5+kec8kXh38DwS3R3Kqwdk91F9hNjaqAIpgP1ss0Gi9IHeRZ3n1Cqy9zod87qe7kDGFvl5ZATpzPPk8lfb6W6Bu18HdO4P0krPrfxn/loGxPN/TJZqpxhg1m80eNZJ6ztvAjvh9l9Zf17F5DdIs5jEpbs16uKNUWVschGT0V/25ec+w30ZUMl0AuYPdy4FWvwQymq9O2t4g3UuMwCB/MTUtSz2K5fx/zfRTVwrnK200S4gTEA3CIt58l9uubcx7UELjuLhDkK9BtCd/jdCDeXUzAcj76fQOB0GJ8LxRgKflYL5v4HCmtOvY+YERvEddB5iS+DHtSGX18hui+fOB+y8X4vSYeX1+gMX6QX1w2a/MKdIb90ueqOxFWt/bij+VkXTRHiKb5BK4bayU+MAhYvBHJig9icBW6lBDuX8JdUy3YbxjVzy8KVJxNfOsp/mLM5s2XVJbFhFZfy3sLDkvvR/hfLijVryjrDzsvBVttVmmVtWWvWrGucgUodfqZiNfV4vuPM/g7mdqsSKXmnlLdvmH4n4uIQX9ck8Zs3YczJWQMm33UTuJlI0TyrTjvlWep2jXU6TQeQc9ZIFYJdUQ35D3vqZHlbBsBb9fs78FUdqOysFFNzCSfqcqe1WX/OqAPuYjB6ELEuzvhn6zHecqXttO51YbwqfgfyvFema4+OMB68VcHA98rdfUF9mAtZbflUhvDearsz7iEvzGg7yp7gm2aeVipzcvVULkk4jMcUBk=
*/