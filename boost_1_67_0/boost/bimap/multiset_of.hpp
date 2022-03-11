// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file multiset_of.hpp
/// \brief Include support for multiset constrains for the bimap container

#ifndef BOOST_BIMAP_MULTISET_OF_HPP
#define BOOST_BIMAP_MULTISET_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <functional>
#include <boost/mpl/bool.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/multi_index/ordered_index.hpp>

#include <boost/bimap/views/multimap_view.hpp>
#include <boost/bimap/views/multiset_view.hpp>

namespace boost {
namespace bimaps {

/// \brief Set Type Specification
/**
This struct is used to specify a multiset specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::set instantiation, except
that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the set
type specification, rather it is a container configuration
parameter.
The first parameter is the type of the objects in the multiset,
and the second one is a Functor that compares them.
Bimap binding metafunctions can be used with this class in
the following way:

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< multiset_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        compute_index_type
        <
            multiset_of<Type,KeyCompare>,
            KeyExtractor,
            Tag

        >::type
        ,
        ordered_nonunique< tag<Tag>, KeyExtractor, KeyCompare >

    >::value
)

typedef bimap
<
    multiset_of<Type>, RightKeyType

> bimap_with_left_type_as_multiset;

BOOST_STATIC_ASSERT
(
    is_same
    <
        compute_map_view_type
        <
            member_at::left,
            bimap_with_left_type_as_multiset

        >::type,
        multimap_view< member_at::left, bimap_with_left_type_as_multiset >

    >::value
)

\endcode

See also multiset_of_relation.
                                                                        **/

template
<
    class KeyType,
    class KeyCompare = std::less< BOOST_DEDUCED_TYPENAME
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >
>
struct multiset_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef KeyType user_type;

    /// Type of the object that will be stored in the multiset
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

        typedef multiset_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_1CP(

        // binds to
        multi_index::ordered_non_unique,

        // with
        key_compare
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::multimap_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::multiset_view
    )

    typedef mpl::bool_<false> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to multiset_of but it is bind logically to a
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

See also multiset_of, is_set_type_of_relation.
                                                                **/

template< class KeyCompare = std::less< _relation > >
struct multiset_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    /// Functor that compare two keys
    typedef KeyCompare key_compare;


    BOOST_BIMAP_GENERATE_RELATION_BINDER_1CP(

        // binds to
        multiset_of,

        // with
        key_compare
    )

    typedef mpl::bool_<false>  left_mutable_key;
    typedef mpl::bool_<false> right_mutable_key;
};

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_MULTISET_OF_HPP

/* multiset_of.hpp
tgnrXh5+I/biRU9ago69XifKaYHmYrsEa6D5f75NikaMCMBhIHBN2sOaW9TH3nmvFGKHC2eIFHTTrvgkKQ7AYXb1zPOH8kAe2ejRcNcdej8B3+MvQhjDA0WrOn1L4GYMOJQvQWx/facJejwDp28J3F4UAssA0oWwQnQEmWSW/ibfHAiosbTo8tt8rRWaNoL4nmtoNjU1dVtCy4hmVIGF43FZcUV5MD9nQ8e36hTOyhk0k3wlQFLPvCidK1dKN+7pQkegPZpLa74EkFHUFDqqUeh5Sw45TDrQAl1Yi3AKxHqmNXrQ0AiwMNfUnKJ+vGkbd6u4VmiD5ocWyk48WY7+7Z+lEK+LhoXf6DI6zaQ/e3OjnTtcC277u4zGDtd4rKWqjjomyMvSRFGUzc/4yjhWHg8ottzzd1yThI0Tv/qaBxuI2pTxQxkEz8DNCKG48IkcTRjVTc946keTu37eCFI4fWakvLrgcGW7ublZDygiq2iA+BV/hWUBIJ3uFMuYEmkSgTj4RtSq4EBy4vzQjDFnEE198YtTus284TEhLQ8v1UZj41NlAnVkPUAn/aMUF+vTrrxKOgCODtSPD+wo0F4dkYLJwkmDcIuXyfRKJMXdaOIO0F59xtlyNHaleAGbCbKZjG10Wj28HCAgfr1dQMVwmvXwn/9WZn7tW0G4xbN0lk8+pqVlWfyIa2z3Lr1HjKMHn1Gl8cN4YYmUV/xRS2BocCgtOyIPKH7iIJmTlnEQ7Gm0D9xFhx6mfMpWJwMIZR0yr+sOZJMVIK+SjMbGRl2DuCDJJmxFR8zTOToRrA0NgbV6DKbJdUjX08+h14rhq0IxabjtVu1BOeyz4aiMQerI48cEkvnQPubt50vl8W/SuTynW3w+4pWghbCgdB1VVkZmeGsPbiXXnPsOOfzHP9Oraqxso8WyDAs4/c2PaUxzNNERBbQVjB4d9Pjh/CzffEyWwdGavG646286enAECdYflADliZMr3SoZvkGnuhm3J0gdGsZwT6WBhF5uWjgNIDyfxs66aN5RQdubDJhJWbYZksk4ZV6zjcUUA7RHTbF4inErd7KwTtftXsvA0GaFuGYRPrulIwgSk9D47j0SnOxVJoHiQTATeOaSWL9Jd054C2L3qmelk184RaPZVAPk5K1MgGiakDKTw7/zfenGEQ+eOOMzBXs2klYA/IPGDte5J8CN5CX303XgPtmGHTsEQz7nxXwupXVJKyODw0Bi9LtAod144sbLkFWkt7U5Ay0/3u/bcv89OnoUo366vWs80FzgoNuUhjkegdW3uG7lnyWEbNHtZubHtY6ZMxh90jd+gp6jM3pd0+TYTMo3ZJ1rdPZ3G9/+9rezeVX1Aoif0XMMxZDTYeCg6RYStpfMO9oDCHtVEMmRvnsTNwOsQoNjdq58QXfM+NmTUjCPeu/vfhU0HhsxTGs+buUSfkygyrBteOh/fU93mFrBzs5gPYL6aWOG6uk7vWkCGziT9qZ3fPjZhenK2ssuljp8AYoAwYaJ9tSkgbRbw2aqh9FspoHF6mD+NDPl0Zc/87LRqf62v0gxLu9gB4XNRF9+WXGz+xblj/p6P3SbsAfWcDpL25OOPFRe+17KU9gNJB2goTjL6GF1Ix8p19SUdWaHsOf9bNVIA4glhPksQxsaGhQgBhJm6MRJsxfgWLFt9xKGJDa+cbPWQ/mCSg20CcmRrpfXar7stTi8s5Gab/+rdGE+zOGfAKEyutWR448rWCYQNMdiCjT136/WhXQLegMu3NlraceA8tNAALrIC1CQlQHGG04VK/gA9LUNsvmDl0rrSy9oPTiKoJcLRpJc6hOm33XnyIK0aG6Z5KtOr3BjSMPvfy1loLmUz6W8mioPtGG03r6n5mZ88LNW1vDHcQf8gl8QxHQWifJFPvd40M2WToL5POVcjKP8Rm/YtA7GTMo3ZJ3PUZlmFU1TaQBhAipEwkfARXbv3t3J90KoDWkuWKwAM0sWHi/toBmHIZVBnes2MrdB050vvIJ7ufBsG4wirzj3LYMuwfRqz69/oeCwqRbr0x9lQkWBcO3TP3GVDMeahE+s+TCOJ2zjqDefYWjDkSDVCIDVbdxedPhxubDlsRkKWzXaogzXum79xIek8aH7dcqIaa8KJXtuKmv4XvkNggfLMmXgIB17//h7KdizW/nOdye8xbkX1xNieGpa8oN2y8V3B04nMLD6kX1DEzt0MCl5reWo3eukOPUtxQ6gyWWUafJssr1r1y4DiMq+kZUGEDKBmcF8lfb6+nruCyctM7cghod1ybELFb3sSYnmeEOzJLDDFDCGFR0oDbZ0PP+yApEMYracnrAXK4ej+bZb9OIAd7Fu9IfpzsWN7FXZiESwzPvvG2TMpe/TJ93NcPNpNfcJWXfSpIIBmvo0GReKdWCDcCSsgK6BrsKVRju//HnZ+6ff6+jBUYQ9t4FkX+qUS73dOCyLimVrx4PpX8Ovfw5weFPbIgCbdVAFP603HAFQrPF7Ivm8sTQwmc6UWvkD7Xh7/PQiMW/uJnKU1sU5bAV4/lGU4ZCi8YumyTVlHCNIF+raeMEFFwQ7WCwhDSD0IEOQmF3UMgoBVvbBNMtGD5dprr10wSLpxuXVfKWTxJLojpdYnl/JATS7X9uCTy/wWB6zJwO5OMTOBaxlsJTgZr/daDw2pitQRq+my/GHfKCiSc081Y4y53z9epn6uS/qE289ho547Ip4JCUAChNTRbLBo93qoPxHvhS2cjQiR5IaTOzrv/8d2fbd6yQBcHAkIVAopEYb0w2WMp6xLJZp/Nz98xulqLlJOyRODVWYSIdLiro9D049vTA/ThDPd1sFtC5+YDhO2I00bB4+YCW/uZAoPfEklWOjO2y64KBM7927l0fWqFZ4Rs9vL4AwiBkioUbeuXNnuw1DhjgDiotGLRT77WUnL9HpBokl0QSI8WggTY4eqpSZPVYdRdBU5ahZ0x9/J+04/qBzZTSs9bpe7Px+FRA+QGg3kHBEmfbRT8i8n/5aOvESUiPCmqA5mhAotsvVs/vCFva1MqTH6XpzusiNh3IApQq6Bh5tt/5JXv/sJ6W7pVl3tmzKZSDJr0a5xTbhYmwXIG34PHbTzb/R9RJHEO/JOSKxavyxutFJ5bcTuxoFSlBZDWWEII76MB8/jUXVOAzUMpAPLMyLebJD1lMI2DQpf9PijNMrV4Zt+bB9+3bOkCnzj9B0VS+AmPCDMUsh9KmtW7e2u5kSCGSamcZAM8tPO8MTDJ/wOI6c6EPDoJZac9DQfzOFm1O61r8WYqCXH2QJ83iuRdADAxTbv3mNXkPDHtfWEUary4hc7FEgYZ7Uo844S46/d5lUnf02aUDvQM1pF88/8ZkJF47uQt5r/Ow84MYDAV+GaWMFdCV43/X0k/LaRy7Hiek67c2tTrnQ3984rDfLYUejGwUYwbZ/5UtSloh7oweYTr4HbWrVYhtTyDWMwb4b1oyjiRtfs7TEfvaWme/N9a43pedRGgBl3Dgpxbk5a2PXNJml6co0AQK/FPRSFumqNIAwMyqayGAtEqxtaWmJ44x8r4eGbsGuvfykU6SLx05ILBmLvDpexOkVZj1AuvPV9eAwCqBSmn1uwaCNgsXtXva+SfR0e/98s/b4BhImI5OoXdpzsTMtVRgsdJfg7cqjfvQzOeYPf5Wi+cdKPUBC3QBSuZDn5jovouM0gOetuF4haKjZ+7mafgznk/W4v5XMqnJk6di4XjZ/9H1Sgu+4l+Ba//7UI5e6Go9AhoKRIxZHzp0/+h+R1zdKJQjSnSuY5HvQvp7Lc9OfbhJvSu3+4jpI6EXzojC+Raa/43DiE2Rgr44eKmfgVcVpZ2ZtU6uTAYSyjR3CBPzXXnjhhfqSlFOyN210Pcg4ywT2ldApd5pl0y2LEzZ5GXLFKZxmYRqCvAiSthdxekW/1sTa7bvuXL3Oz0a51ZOl3xDszbjdS4Cw5937kx9K51bvKLzNn1lnExK3/rnYCQYq61nZu1JwqGkfftwJsvCWOxUoVThV24wvYNVjDkDNKVgjkvOULqdiPHNF4PDkbpqGH8MILMZlGMHFNwt5/GQYThgXYqrFyzXYBoOlWEfWy8DRcO/fpfnm32Lax2ksd9089qsQmyBrE+uP0zagkOH0pgri2GjixLcIlp/G98P9tDq9AkJckHD3qvKstwTyG5ZNugkMk2HaKdvMEmFpu1f0o+LOXKTyM1sKIXr35s2b22bMmFHLDK1QMs50OIPKt54n9ffcLZVoUA5/ibZ26VyzXsrmHhqOmrc72dom3VsIdDLMDNh9p3qBsXSWoPwK9L7xjjbZ9uX/kKk/vikABcHB+lh81iUfxfjMw01HcNDP1DC8rksdx2fq9jzykNQ/9aQ0rnxamte9qlMSlq73UpL8nmSanORo7wgXR+PC2mEy/KTFMv6ct8vIxacGx1BY5lAo8qoVtG/7+n8CHFgIg17vqTlpB4HGPqsIK6B1wg/Dgjhw09/4zfiwa3IGUeIZl0rTaWTfTj/PTUN5hDiUMU6vYlOnSuncIzVp+IftQm3yy/oQKBs3bmz1/ZeG09DdCyCMzMTsNZAZ1yFbsEc8BT1IHP54/dv7ZC4FI1PjVOCigzpcutb1xnZ9cMQFVNuKVQDIYVE05OWnowc5Qz6pgiWww4MMh2Kfyqe6ZSlcC4T4ja+8JFu+8kWZeu13tDc0ZtGkoukKu3rm8eOmdfnCfIvwEHXcue+U8eedrzkm0PPXQ9h4pAQ3wUrTan/DIVReLRq7Ak/uqw6dIyV4t8HKoOnamczqEcpin5zMk7oM15OWYr3x0n9cpTfI8EYZO4yIlvCFmkXBRQ8qpFMJVjt+sgo+4zIi6gWrgoQebBr1V0/PrlHxA6HStQfCE0jUhu2Q6vMvysgH1oPgoPxSExyU6bq6ui58G33Lv/3bvy0lBWHVCyCMEMpsBdxTsFhvnT59eq3uf3vgCRopnKlgSlGNp83tP7kBdzWBINSnY9NWie/chf1p77LkXmly9Ohci/UH8tMfNf2EbBBTfjhBogt2MDEOoDQte1B2YP487mNXKkgYnXN41peKpgmeeuT446ahnflQs5OhyYahop2qAF/lHXnKaWrnj/kHHrC4edKfoDM/mi4IGW5htA+G4qcg5nz7+7LqEx+WbjzV53SGwoOa4gfPHlioSrdafGH26gviGBEKP7DqCEHTT+v5+W6Cn1lmi4uoXHOQBxw/+Uyis7hIxrztvEheas5+O7ggef3113X0AGB6be8yDZXXcp497ZeN5s/V7qJ9w4YNbYY+mizINMPDuvqd/yLYGvAqAGZwLdL6JE+wkFP909y96sao5DHWIRflq9Js/bwDA8dPQEcFaloFv8bf/kLqMY8m0Dmv5sKdwkX6qcxUR54/zMe0CTRNAiWstXHZwH64646yM70b18qhOdjKyhh1xptl0R9vkwQ2I7gmaoXWy+vAO+8EAShRNuKH/PRY6tmNyCA8FDcI9xJprdy4Gu6tOVhldBcKEoKjHa4KdDhFI0b2kkO2p8mpgcPWIOvXrzeA3GHFh82MADEQIDNOs17es2dPF3a0uixzCw8Dw9zFuH2j6sw3Y+iDgKBUIr7tpTX4sHtLP+GBxti4ye+B/GpoI3gMDRoGQeyBPAYTuF4vwN0WbpNWwWPXN/+zF0istzf6w4zKx+0KL+0U7LBpgDEwmNvMsH84fbiMfOjLJy7LobI61OCFq+PuuEdieNfCe98dl0EgDnfg2MaMTf57ChazZ2ir9HBL5iXqycvPBwYX5zp6IJBTd8oW358Z9p7LIsFh7WngsE6e7zvhpEg3/J9/17ve9Yhfci8jEiARma5Exql169a1ECBhkLDwKD383e9V4nUYZGVwbqrlkeV+78JK56e7Nr6eznBWB1loPrTg32scP1+GQ3G+zGket3750K0KvfFOrEf23vrnYCRxd7fcuhgv+mN6pXu/JmiuYDPEdfdlt/hejt5vf+jKNQ1LYFxTRl8p3iA9/q93o9c+VXfiOJrwiiHd2tf4Xk+vbaPtwvbwc7H86PbjBmEa143nJbI2RTGq3NGD4Cg66mi9M8BtN9duoKBp8vvqq6+2UKahI3ev/KIyT7EYgcxhhthKvJkFIlPuSDJTXei4REQxvRwPbIoXLFSQcKFM5Lc+/5IkGvTSOqMhNxPpdQQhU5WxJJBJe5jI3kXDPC/f7jmACz2+wYduBEk1ELPnO9fKrl/cGICEUy4Chb2lKVdAzK+/pgmYmTZKWO/clz/Dh1oZTWYarXxLcf4vfi+j3/t+b7uaIAFxfImMo4l3iNAHihINT68p0tolaEOGabgbj35eIm9WwKkcRg5oglGnV/gezfD3XK6yGiWDlFH6m8zSRB2SlGWGUbaRXUYVOYIwtmXqZ7IWGT8K4Ulu2bKlzUYQM12ghO0j3/d+9C6cZmHRykqh925++EmPGcaUHMzuHTvxJSke3vCVMs5jpvUwGRvAj+uBBM9HABLvjBPeQLzpJ7Lte9/CVjAWngAIj5UTJBSIMMOt6MEwTQBpHmjKpY12AwlBMOcr35SZX71OTw3w5ICCBA1BIbZ2UVPlnO2lFq+KZrcw+prdwtTPm7opOMAeb2qFozxso+nTpRZT+bDcuW4Dh40emzZtakMd2NE/dMkll2z0iIn+zQgQjy4Pef4ocicLfeWVVzg06cjiEkF7WKDorsaTzcIjjvBB4g3DratWSxxvAnrcIEf61t12CYRGVS5qA0SOGko8s/XztexRjk63UGseReHDrlrsBbfjjNPGT3xAOrdvU3AQJIM9mpDEoVZR7WN+fdGSESQQ0snowY/48c9xD1eZjiZt8OO7qwFIwGu2kwcYBLBdvCb024h+vj+McBi7DE2PX45OuqaFZ3sqIaM+fIXEMMuxerimySfllXYDyssvv9xMN0aP21lcNpUVIEzIAn1A/AlAeRnnVjqxYNcLHQyRRoARFDbHfurfcbwCowgqRY27HaXpocc8PpFXOej4Gzt8xjFyT++UxkxmpEQHP04aLx1DPJDwjBNAgqlWNR+Y4EjKhvdfLI1PPNprykXhIB/C9XIb40C1uzSTRip3FKDbrVu2ejAulYElGEnAn7E4MXAsdri6cA8XRxK+RKZH/1EmrEE7pI8mDIDy6eqx97SVhTEPm4XwGA7XHjEcax+GxwluHcN2AwVllXY8Oe/A6d1ugGPFRRddlHH3SmnBT1aAkFlWADLkqPEQCEi98MILTebvEpSJudWLl0jJ0cdIO+b2rBzXI604LtJFofe6jj7Nrq3+03PwThnOdF579zCYbmW2H6bhvh1BGuY3BqdbfOBVwt0tgKQWPUplS4tsw8OwLdd9VTpxGJBbwDbt0kN6mB562WjGyM7b3lbPA+zHaKNpilvbVifWi/Z811wEB1UYJPSzHa4CPNj0rjxlPAQYDUpKOmDS2jAUj2FMztFDF+ZwsAUoP5y2j7niSinIMHqw3q5sUl4JkhdffLGJMgz7MmTVp8oKEEvNgggQPFS7CWbqtddea+clv1YoTcYx0yXM7OM/9yVvmoXKWU9Qd+f9PgetpGgzUd8gPGLC3ofM8gTdjxtmKr39hsgUzxaQTEqgECQVAAnfuxgGs+uev8m6d79T9uIiNAoQhYnvhYdfe9WikEmUMPrUDbkRpoWCzHUf62Bgt7qY6YLf6pSNcBckjEc3RxMq7nAt+Asu1158GjpDbsmqdzpIwDO2ozflQgRrQ0Y1u6bzwERwqMzQRFltWIQUHTZHhmHUMvkKmyaLJqMEB28twcPBDsjwZuhfuJ2HT2Uvo0+AMBMWQg2ANKCgW+i3atUqHUVcwtzGCdurFi6S6nPOxcMlTrVYYSyytu+W5ifwEJPMyKK7t+90mOnXgYwMMTPIgxbmR+XE6wEY/TUQwVyX4Ik7TH1BCSCphUdla7Psvv6rsv5jl0vTsyuCaZcJFYXNThWE6+q6WcpgKrcstoW5KbD2MJTAJt2kuRt6zx23ytr3XCSNTz4WdAAEiQm55ZEL3TaSsCyWg45T2gFIfvrM4zdyiWgL478HEsZBJDcevCy9tzgnOHirJZ6aY+0x8T+/lnX0YB1MNk1+n3/++WbYUwDHQzi5ay9JIcfMqk+AMCkLYyFEIUDyYxayevXqVjAkTj9qI4KmERY2J3z2P6QTAsjvU+h2IIDS8OhybPvyXTxyJ1p379rthYUY6EX302gYfozR6q2emi1HDbWoF34sHn1ht2clJQBHBWiswZWmtXhjqWgNznBd9RFZf8Xl0gCBMkEwobMpi4EF2Wl+JmSu0JqfazJ+NuXGDdvDeVPAOVoYTS6YuwEABcal58vO714r8c2vyaYvfFr23PrHAEgEENNT6K2svmhjXJbHsnhNUcOePfLyJz8szXfehkNGHl89vpPnfm7aFrD7bRGAhB5+HB3lIScEh65bYXLt2gb6eG9YNQ6BhuXL3CaLrmzy1sS1a9e2MgwyfGMu9SO1hddccw1NVTjZaNZeJjOkQiPUg4lTwJQ5mH6kpk+fXk5/Cze7EeCaxfguRRKMbFrxNM5I+b0dGpX3+FbOm6O8YSlh3frUs3i91n92EmJuEJkWj0QS4+UCIw0YGo4fNZVoP64fHelAFRjP6zO9t+T0+yOwJ/bskoYH7pHGFcsFb9ZIMe5dwj5hMIqYYFFIKTSuYsNRhQWavLFGtTDXbX4uD2mnoslyWB41AUrNKSEFlpo0xcHv+nvvks1fvVraQH9pW6tOJ3lUvRDpG596Qrrw+boqXLjB40BWlnV0bnkWZjSSDpZh01CWtenqqyT+xGN4V8R73cDeNPTIDvFeK+L/MEir5k29yEI9CQ6EcN3BDrUL9WzHmatDfvorKcpwKTVpJH0GEpoEymOPPYbXzhu6y8vLf4+t3dtYKhXDs6nIw4rhBMYkZgb0cT3yP9DnY7us5ZhjjqmpqqoqYmOZYLj2cF4TcBtI/d13SvuWLei1i6QAFW95dYNUvrxGKubOCUdXtzeCwOpxECa9I5it3hqowd56hZ5UbnzfHRg9aehFkOBso34Uswj0FeNF91LUrxON1bHmZdmNUWXHD78t1YtPx23pb5GqYxYEgmJCbY1kwmTCRZP8MTfLy6Zcnlo8+hkwaFJIaRrfaW9/dY3svfsOaX7oXikAKMpRp1K0XymAUYTpLf+7wfxizOdbbr8=
*/