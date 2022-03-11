// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file set_of.hpp
/// \brief Include support for set constrains for the bimap container

#ifndef BOOST_BIMAP_SET_OF_HPP
#define BOOST_BIMAP_SET_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <functional>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/multi_index/ordered_index.hpp>

#include <boost/bimap/views/map_view.hpp>
#include <boost/bimap/views/set_view.hpp>

namespace boost {
namespace bimaps {

/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::set instantiation, except
that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the set
type specification, rather it is a container configuration
parameter.
The first parameter is the type of the objects in the set, and
the second one is a Functor that compares them.
Bimap binding metafunctions can be used with this class in
the following way:

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< set_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        set_of<Type,KeyCompare>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        ordered_unique< tag<Tag>, KeyExtractor, KeyCompare >

    >::value
)

typedef bimap
<
    set_of<Type>, RightKeyType

> bimap_with_left_type_as_set;

BOOST_STATIC_ASSERT
(
    is_same
    <
        set_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_set

        >::type,

        map_view< member_at::left, bimap_with_left_type_as_set >

    >::value
)

\endcode

See also set_of_relation.
                                                                        **/

template
<
    class KeyType,
    class KeyCompare = std::less< BOOST_DEDUCED_TYPENAME 
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >
>
struct set_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef KeyType user_type;

    /// Type of the object that will be stored in the set
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;

    /// Functor that compare two keys
    typedef KeyCompare key_compare;

    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        BOOST_CLASS_REQUIRE4( key_compare, bool, value_type, value_type,
                              boost, BinaryFunctionConcept );

        typedef set_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_1CP(

        // binds to
        multi_index::ordered_unique,

        // with
        key_compare
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::set_view
    )

    typedef mpl::bool_<false> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to set_of but it is bind logically to a
relation. It is used in the bimap instantiation to specify the
desired type of the main view. This struct implements internally
a metafunction named bind_to that manages the quite complicated
task of finding the right type of the set for the relation.

\code
template<class Relation>
struct bind_to
{
    typedef -unspecified- type;
};
\endcode

See also set_of, is_set_type_of_relation.
                                                                **/

template< class KeyCompare = std::less< _relation > >
struct set_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    /// Functor that compare two keys
    typedef KeyCompare key_compare;

    BOOST_BIMAP_GENERATE_RELATION_BINDER_1CP(

        // binds to
        set_of,

        // with
        key_compare
    )

    typedef mpl::bool_<false>  left_mutable_key;
    typedef mpl::bool_<false> right_mutable_key;
};

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SET_OF_HPP


/* set_of.hpp
RV5HBzD1S98IQMe80MaRdFodXDDGW1tk46evkNSLz+MZk3d1UTHKgBUl4wf50dB5kx19Z3s6/pAgr4mBjFSMwPdGEI4c1NzkmXDl56R04iRjRS/T+Gp8p8xi7dGNUyCtkF1Or77XK1EWj5wAYukNjShoE/QfwKCLV6xY0Xj66aePJEHWmGygTKqwqkqmXfdtWX/xhWgwMET5ViB7/v6QTJw8Ee891KQlTfGmeLxPEg0O5b4X38ADlzdkR4f1yoep2XCqetLQi8xmWAns7AmLIVClQA6uekEPjV2g+++SLffdJamqGqnA59BqTzhZqo9dlPHQHIuwBqRJntE0vjE8rFyhZ5jFpWl8NrNtzWppeX6lNDx4ryTwxh9fGuPZsxICA3ZeKo0nBvrHvIqwHuQrvXwnpfnxR2TDpz4s077+bUmNHLwAwUUAACAASURBVKXlsAyCxKWT9LI8jlYcpXQt1tggG676qMQASj5b4sHQEjQCZqoea5GP8h2Gd5IXhESBBLE5iuETmni/DqM2JlgEBqdYXNcUzZkj4z7yca9dWIEIZXwlzZRXmsuXL2+kP461c/TgfD1nlTNAWAAVhyu+HwDm/DeYc/aaNWvkyCOPrBo1alQpwxmP2hqWfmE1DK/ljrjwX6Xplj9JJXsp9GIxDM+7cb5n7KX/ol91sjRx7GApc+nh0+BxnUz2Yzn+yMnzVCMijubj/1h6pgnsCCP9Xi5apIkU1ynsFVlRHp/n7S18Uae7vUW6H1squ6C3I6xw0hQpmzlbynGhd7lv8qSpKeOl8cncFm4meWhxaHdVx6bXpBO6Y+tmacO7Lu0vrpJYW4t3RzHoLMH6iQDhS0286YXrAbLJ65C8vHjxNzpq8Jvl4HTu2ldk3ccuk+nf/K7EDpkdjEqcNVDYSAvB4Y4cXbgTa+OnP6YX3REclTryAnQsi1xkUcyc9MPoGUE0gu/vhTMq24+bONy5ioM2Tq3w0Q59r3/ud38ohZCXTIr0URMUBhDe7caT6JDZNwD2azOlzeSfM0AsAzKKvQoK3AGQ/B49yRWPPPJIA3YFxlocmtaruX6ufSp2IV58/FG8NLRTCoqBdPQ4bZu3SsOyJ2T4GYuDqInmFs9OJlOp4TNX3T3+Cg7fqRHNHk4b5MP8LJJnZyOpUm8/DAZtBAqfHHEKRsbxyAMPQNrDT+6wEDTx7Xj3BV+7anzkIamDm/E4ny6ZPlNixaUKHJZRNnWavhlIeyaVaGqSLrxYlcSI1bHpdQg4tmw3rIPAe9MXCj7t1aCjGF+PIhg42pE+ahUYmtCBkHouBUuhjoqsGYQK6GnZu0s2XvkhmYKRpProY5lKlY0ktt5QEycPNn7qo1KE+tq0iiMH82F5vFAheNuQfO4FEkTy/YNFOXc54a3gIC+Rph2j1YSPXymVuC0xmwqDg+6lS5fWU2YB8tswevAt5rxUXgBhgVR+gSz0eoDk5B07dhxJlOK13Aq3p8s2ihQPHyEzv/dDeeXiCzAPZu8EKcJ/PbZ9y6ezB56mZenBRr9cr11Bg0eGx1zEQjtA9fYP4vvBaXFC8VG0pyyvII1vsTLhJDkqUrBQOLle0ds1YCdY0PEpUGh6bm+akMTOEf26NqxRWeHlDSyXc29TPTYPiCxWNX441eMoVg4g4HGNrt8ICBSvoGCvTXr4Rh7tVMFYyIyNjyxP3QwnNJA3ErIJABMp6GiXzZ/7pIz/9NUyAre0UFm72kZAx5ZNsvGqj0nx7h094EC88JqDfGHGzNvAoBXy/ZUU0JVCL8Lplfcg0OMfr5JuxwnwkqOOksmf+RyS+5UiQSHFMGobPWhidtOCEaQLnfkzl19++fWhJDk58wKI5WijCHYEONz+EfpIjiLTpk0rR5jWgsTaKGLMtfRmDl+8RCbgLM2u/70BlSuGoCMpmLTjr3+XyR+6FDsV+Lx0cDkcU5HZfmrGhfJ2qWBRZ+/wwJ+Re8WhnHj5BGFBPN/iB9OlDawW2j0LBUytkDIKJxlKWUgBNZxLExB06yhCEy7aqTiqsFMNMqPVUawi89b8kY6CzNGLJsPU9P2CuMxPpRGmKkRUPzr8glU4vVAS4OWFEQh5xwrxxVzmjTn/juu/Jp0AwvgPXpHWlu0YwV77zMelpGGvHvrkjpiCF1kqrawUMzVaUJ6HB/OnSXLoj+4BTGI4zg/2jMbw465Vd1mJHP7D/5VCnPPKpAw4LjgA5CR2rhopq1h7/CpT2r78yeO8lCHVL1gmfvJDv8Xwu4xfxsViqMHmfkasxc9kTvvCl6XsyKOlDcNoHAyi7saifOctf5MUGimOKRaZpwxX07fDyBkcbjraqdCACg7Lmy1m8dTuuFX6GMh01H5E9ff9/DSsJ3t5dGC6AOZ2MZ+tlGLFWgZdgQar9DXn7DwHxvNgqjEcVLka/pVIyxe9KvFchmnLEZ95lcKPW9BF0PhXskheD69Iv9Hp0xi4GcbYUPSDpoGiNM8yZFiNNUw1aGn4w69l09e/LAlM8djhta5dLa9hMV/aWKcnD3gCgfVjnZmHKrOoGz++f097+X5+uLcoR9sjsckAzU7IxIxv/pdUYD2USX7M3+TNzCeeeKIBa+QEZjn3XXbZZX0eSvQp72X0awQhUQQINRWGsG9hq3HJs88+2zJ79uyKMWPGYFcUPR4YTaYyfqZRJFZSKnNu+o08d+Zi6WxqRFxv0d6Kc1q777wP+6q8ds1THt895gbCrUE+w2nP0Diuf69RQxtKEweN6TWqH+CG+9FoqPLLMxpdPz9G4JWeDV2Bjxs13f7/27sSMKmqK326q6r3tXqVVUCwcUGjjqhhMcSd6IDEoONoUIEkbomOSSYmMRPn07ijjHGJ4ooZUYlxgZBo/GQyLuCWmKgxIqCydQNNb3RXV1dXzf/f907xqqh6VdXd0M3Qt/vVve/u7777v3POXc5NGCWmNAsVjngm1CJNpgibxiEeQjQekWTcdl6456Pws2F07JqoeMegee2v/kE+275NKs45T7bccJ0UgAXj+jUu9jQqR5GvaQaTJxIyS3poeeoPb7Y9yyCSyVqSopINteQOS+YgODpCQak873ypPe9fY9sj7k4BQlvBgQW1Aaz04LBuF/rmLxjWU5MxBdGCWChHtGiGXDHvQ5CxJ1DByEsvvbQDYKCWOrQRG92qnNqa3mnnDhsmB9+3SAIAUxD6s8xMOxqpGfq02qHiB07TmAoKtU0ezJ9FmEvdtgctBth1oB1Na/zs+BrHxGcSOuww40f37vf8IrIv8P1b4XY83Fr1cfirh8nHkZdJ64yfjlvLsRPH54ksnPVh/ax6OtLZSRM9K6mB0eiI3lEIagV9T1K6dYPkvvyMlEZChrqQypCCsQNZ75Z5m4LtsrUOtG23Hcx3wPqQ/eS7JUB0rqPLgCME9T2Hy0E338EUSY2zT9HNCx9q0wfx8Y6gT/5yzpw5a5NmkEZArwCiFITljLjqO9cCMG9iKXHw7bff5orJKKKdYNEHibf9J06TUT/5uXRCvYwhs/j6UEjr6oJOXTQnz32wvjj6IlAoOwaNsdXfthlEf9ow2pl3vUR4xsWx4ttpTDq67XtmYtyoB7z4gvXeZMT40ct2aNqoPxPRwMPOq0e29RCO8qwsTV7RvNUvtjzWOwbQdvCutFY6AxK8Q47SVY8eLmNPnSxDDhopB506VQqhoDyqyZ3P4cxDn9XUww6IxrHisg6kGASHBQx8FHHDkasA2KoI1nEd+vgSyc7FoXpI63bF97PVq1c3c8YcbP//zJs3L6NJQdY23vQYIPEZ8R5C+x0EzRtvvNFCMqeV1wdMBZThV3xPqi+cIx1Q+a8gMQ2IhjMLHG2QkHJbL9RpswbseLRhHC/F8L7mxZkfOw7j2pGjYUxnElthdrCJh7gpO5cpH4lMfswHhmXsdllB0V+N72ZHIzNPXgnyZZxoHlGHHZeBMHa63UHOMDucDutf/BMOlmFTJ0oehuKpNb+kxi/DT5siORig4XtlPKt94aChn7HtH/tW/Uk9OFrFi/Mb+n5pExzd+X0seoEPfgCAQ0ul/WV0JDGvIAx3h5mZJ5kJMzMzJxNmnDAzMzMz00yYJszMzMzMzHkz9+7dZ8/un++cr09Xl8vlkmVZkiWX7Hazf/o5KUkgezjvnTC00FHoFcnq3OoMINKKFW/4ZC0jbn89R+eXBuUYCenqkFSv+DffgQz7kus1twPPUrkSbcQwEWDdov3GNJHsPDYTzB4OfJGqjj1nRBWvHh+NAkLXdWWEemB7UkT+el7djjTsVINQp5Ptldaz5HUmmK6qTC547lvLgDt/SyMjWRbdzag9p3fKgEmHCs3sW2hqXdYAJHDeyGjQtUKhZofiaGyrY6H95vyQUrQTxsfBK3NgmCtUtVavgeNwineNaIKLMSaG0Zo+NOYZa383DBHrBtrAYrlWEf0oJMjCmijq2BEifLehCD5AYyvwCm3Qwfp+otNgqV4wrrEeqL/e2bQfZ62W/NM1+C3WusW0rbJONqzly4U6aL0YfBsyIxGNHMrhcPiFPppbLatJF5UxFA3Au5zMhubRqJLqSOsH74TNiyVh1bnqI4hO32L0gdhZkJpJMb4AGyzk0xHePYdAgOjr5N41+Vy6VN7tK3QZiGg5zp2+qeC6Z/xAqMqMJ7ZE7K82NKu5Hqeg7aumJOSHdRZuyNKn/rv9m0Dszr9iKs2P9cyy4bBVGnx3totpY3ONi7tAln1nrVyC9UQN3hYNTx49x23My9QkxNL92SmS2X6/KSnFDWVuGsvwOqtuxfVzBJp/ghkPZF9mJItfAqDV+/RKEF+aVmcwIu5YkJtbkWh0PFMEL2+N1QX5EvSlpe5uhI9Rnjn6A4W3eXD6JRPjZhHLFzpBkXarObzhRBs0ojlPyPGS0VahM7sci4u4YHO3Uvbeq3J+4F8KGVO46kg64iGAzeiBfm+C/BFEBgFqwN8Dh+IHum+BXk97sLFt4+J4q8MypkT+UkeFuFuEfQMxILtLNQYJFf4dkp8I6+hhz7449xKuG8UyINtAC1gejMDMKoV1k/6tatq8xiRf+rCuutGcfTjfjil7/wFtbwQIEEM4geORqUR/OHg2OpIYHD5QVZGqxqYiYC/pPlvucObIJGc2VK5ubijNqIXYwbrwzQTyo8A5QXOESHfn8QOlNsEeSlHtBzeXH7WosvS3CPKIynsPYS+ywnlAYvR7SC0ezpaVIfFs+bMVkVeYrYn0XTGDMTa54LlmWa1juX2D/b8lgu4Ss3SLw5LDUECDSyLs3GrjeqeGJfh19RNejjNe2x2NjkX5kZwEQ64t6+TsqSZLCPzVvSkb7ZfifwyAPjNl4DdbXdL7iWvyAwpksN1ulaAhSVOH+u8gAS2B9ISxgfh+Q7kn5GpicxVk8FYuEPA0uDjuYt0FlPxt6QC1BaWHOFJdVhkH6vNkSBU1WuVtlGQ+RTrvepBm0mDgSw5iOxaoJ3ufZZahhGYUAwxk0fI49VkPHU6/VbC7DMLUUYuwO7b0F/TrYf/DP1NjXfG2Xz77PTKKvfnhCBq4AxozJuHhH0idcjxrq+m1Oh22y9V6vOaMqMpmeStpuFPrDFVdMNBiB8laiARicT1lDoowQCBejKp7twAPPxOsnaF/9VizVc1FT2WZya5aUKpVGlPKdKYslx1gPNf5gAlt2bujuDf8aE4LCodE0qvi9zdf2owfZUByK3duonlJPkbJmJLdlIq/2qPG43qnX5P9G1Te24KNz+uqS8kIGW+bLrBn5De3PVFy3pbvw2/ueGhx14bB18MvTaStOzkNnRGvdhMaJzFlurfvh3hnYtws71rfu9q+phYtG3Nlqho2YFyBbzdWkUVgXSvV31taWL2wuTvRR/2YHJYb0GBlnVjslFHjBlPWmY8YibOk+xKPzKKowGag6nFfbY/sm+s9HzKj0AlKKOAJ9c0xdZ8ELAQIYYwodbCFMPgtRVs/+OEnOiYiAnjoCP7TFW3rWe0orUySXP6VEmCZhDG0jjiXgA8C6yT3SB9tweI8ldFYstkbHO17m0vB9+be4NGU5E+FD/cLaepTb8LE74iXy0g2tx29aGsUwGBoFO8OAJY8umG8kyd4SNgBWGBvhVmcgrV6XGJMadIbzHqVv73i1dGE8xEdG2FVU4N0uIVkURL/czkBvx8ILwi4bmK4nVARmC8mXu+UZm+t+cex3h+fV0Oz9fr1zDSjGuVUGkhx8lgX8JoYMJDn3zmbREKHJRez11tbPHRw5FYuQ/h8R1brCUWbBdTJGDBue3pDJD653IxmM4UzhtEcxYGtW1Aw4NC7LX6B2/rUdk9X/g5F+/efLIl9oHqx/rH7N8LqtD+6n4ji9w0E3+2WDoRKAbZPTC0J/nvJGKE+jhV7SegaAq9PdKtNVlIJzD418L5VcT2U4J6EvFgjS3cXJTNPyyryCIqIEf6x5mDXG4PrTlVKk5xkxn7XW0T7W3/N50t/TfwVuDClICdPZXC5WGOhYJJC+YYOvkwF0F9fWHd+NLoKj4CO/ynLUfQWK4RAQcx+p2j7O2vP7bt/1SRfZZsSju5TxZ5BbfhNiH4dFFoTNI4F1hLKVhjQGs7evw8dj9W0Saw/BkEpkO4yd7gcXNCP9nln/e+M1iYauBhSjysWKPUuobfgSO4dZ5IEBIIpqZnb/bxqBkViwPrHy9vzbR5GySHEcxOpM6KTTLr61m8L2k/UwAcqoG+QVhX4nkkMHkctvwSpX96WPJc+NBYDjsskaG1lvmADd624p1p0F4JNg7mgLYRMT7+I8xDiFkAagCStsNzbPdwt8F39BwraRxx6LAOg3PoEEo/5uKFrwsrqZtnj9McUQhEy3kzQmd9Pxh9lv9UQNNvAXh9jojsOjdxq5aoRf5fneQV6REMheN6TxHLRtuz1mgCjn4drj1E/20UF6htyNmqnIi238+pMxtOVh7d1S2aAimg4qrFLaVZud9/UH2cJ9ae/O0fqZ/uRaGCw1PyGwU0l0Z4OZr39Qdl3CRIIcwsmvH8kOUzHFK5xpghRUa8B0M0OlmscOWCBF92o7gL64Wn+ccgjrkegargVjZJNS/IXsDrFdwc7NHLm/ny7XY0TwNp6um5DTKb99WujVVc2rUQz8EuZVYEGJvUPLYynmvFhIp74ec+d1NYyEvrl2UN356Ws9jKU32c17hHeHvA7yZMsQO5jxx5dVWHiZ1OnpFF9+wynQw1ymX2yE/S0VohWiu7Bg2hcgE+P1CCaw46f5FsiplldhZcyDnZkOJP64fRxbDKcuoopyQqhoogNHrSSiAiFROurXWskAfoC1X2999ZJ+5x3sN/uUsTpYYQo7nslwdt8PBEEGIaLtDcG/c7y48cPnaLvYBEg3/ElZ+aniHK0eHVXNjR+8E4kbUUK+wfOfc9gDBMKLeEGcSNYm6OtRlPdl1pGogatUS8n+Hvnnf7bjukO2weGZyDLXRhPtNRWWgQKgP2c8Bm70rwpWWaMhlYPDVOEp5X2ejcrx6anrYs1Kp6d/njYv8jOdLfxmX7Lasj2a1N79g4WfBoH+P0R5PssdDw20y8lZSWlve8g0LsloIlRsJexUbDWvdj5es0ANP+AuYC6S0nlfDRwfTBhNyu/ROWSjxazLEirMnCQ82/PBjIJ9Sw/cUlMhs/T7Mtxb/XVvM/eESUE1r9RZET45ir4ktOb/iQZdpjkaYzaAuy7en9wxZw1DIy0mjqNMK4RF4IM6aDOoCqj+L+gnz1hgWRH74PAAySMZWRkCN6X9OrvDdxb1seAKT5ykvSCtQ8jl1BkmO1GzQCEUpCj4FgEMkcBgSeS06By82BMcQnwHkhwu8ZfUdCwQkeVm1O08Bl2V7X6ERV5L5WAQPtqJWV2Z5unv3xM1OgcQLaCS7VuAc0/kCmVhiJPzp70FLF8fDb3oCmtnV6N8e4EC1VogfO81+V2N2W7nXWAcMJfeXa1E+y7cHxijYnxU6T09TU//QLdghnMa4+jNQs/ul+rxZGoU/JIH2rRarWeOOFx0+j20S/2ktzg07VppuaWfmSwXtl+O1vtgkKnEMPCVMV9LbXY69LEEL+GTnD+YWvHISDQOIKbCO36chaOToWThrflar5x+thXrTxh2R7zOe+WUYP73Fp87OIrncU7onTVPbxZBJPnAO2bIMv5p62yEsHESmOQDBUvbeTHWD1+yE555wvMsVYjBhGQJe+DxqOyD9JFJkruDT1RVWvVtBPR0gxaSkhIfEXDzbsAHA4UyTO05ZuNktAElv084gxK33KqrC15PxE/FELm5nR43hrpgMChl8FFzsVL3Crs1fvLpXU3RS8EL78sPoFXqMhs5TMpvz1PV+z9Pp1PM5i7jxRDjaloI9p3GDRSyZB0W8L+BTGCRBpYzFQJUV19PyC0bmScVG5zAQzRn9ItJLt6ygCEev6fUsI4DQIJEpAU4EG28vaVf3oi2ScjqLsyB6pzdOieQ/DSVTxqZmenVPS+qA+FZN7f7WxFECPacAKZ0ma/Gq+E/Zp9cv29Zdi9C9RoROIvg9XV1DDfCw7/jZT/XihJNHnPTKJ90fcRZwpxqFhH/h6Qlox0o1t/zcLrYbIxHRMbgWzsm3lMEfB59P0lH22ECgIPNcbdj5cJ65y4CLVGWvKJCLYzyQ3Lo4L+/d79vOipdr2pwpm5dJp7PVsiXFyOgNytnl7r8gLi15N71ZFYi6qEmdniEu0CI6XeXxXEuThR7IoF+I9K9DyPOynecQsXPJtMp7OVQvmhWNhSe/j3py4YFiOqlAVJCoO9JbouIPy1WL5XggTDXM97CVRXSX60TBH7irnswHhaeRAL3riXVuuU5BQVcQxVCKHYw7XQZc2ebb0h8o/40KeIXnnZKbYsxkigP78LAoJ3N7ieowijmB4rID4FP9C6HHBnAc4gvt5IbAFVYsja4GakydQFG9QLgRb8F1wq6JsmgWZcUgIZyxTuVo6Xt+gZ2maZIvwKGDidIkLbofUQ7iqr9RpWoC4s55mbQ/Int1V3z+MZxDkrTy0kNz+pHI3Uk16M9znfYP61Nzh9JAUt7QO/axU1Hd3kt9H+CKVAfoXY31n0dWDZfjG8ie5wsI0VniK17CtBo/mk3z8xYLtkfNH71xVVsPwZj8a6UeAOxS1cvnXFxVzApevZYZ3RQJsndmB2x+WIrCtx5fFP2DE7v6inphY=
*/