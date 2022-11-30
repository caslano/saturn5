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
JMy1HwJvLIuuSpZH/DDplkkMu/TX4Q64NET4YyvimTKwhshuE85oio4b/DbBy0HlR4pY/rq7Mf23OvbTOpV8K1zGO7t1cp3+WbuQAbattUnaxNAITgSCERSfy8AGW7t5VXVnPTDc8ORV4PFlOMQObaTD4VF8+PtTRQS2vfim3SwTW0Ksz21hcgcscDVlQV835KrmRdaYMPVo16bSloXaRy7XEf/hpOKTmfYlyZ2agJxRS3AroiUHnvzQMEMU23joLSF0aa9CYK99JXUyLeSE/rLUNXCKLtDG3r3dHUK7GZfFVfCKCGZx2C6SEmGzCc9Eu9awg5xxpv/gkKYKwfD3KglSAPdDd37F+WO3i1d1b748p3Q8HReZQ1BQvV6VaJFmKPPxaZ2ZbAwEq5afSxG0r7gStoKW2U4c1wQzZQwrq/743pZpE1FHSHbIJOKt9bs3GzLTDt/ng1Viau/k9R5Ra0h7ccrh54FTao8dK7oehnRWIwlenT23sIxpQiO4j+jMORSfE4GhDlPhMQ3H089mpFNE1HelPrB3xcoYcv2B8JRXCpAsScLNNkD8uEGx6W40KZRdBEhvrpKd7fq+8VDWhss2foJgpMD17j7qpD9DQm/2bIAHybcSxGzLqhZqvEjmfke8OcYSR+4l/oRcD0nIx6lQwbnWp+MfGL5FkMMY9h5wQjGuqHd1gZ1Ed6I9y75bTo67dE90OG9nLOhrzeWTYcQaefV+Bxbm989MkUDVmnHz9YL+KrB+7lUaaiF617iUMeLpb5v4TxST0lWoj4VCpfcTrp31A7i5Y2urYHJLrHF1s53iHaHuo0epwYlV0jpysh3lGN3lBmrt3LyT25BNZfVkFuL22atSBqEiGLCMzxjTESSplnIqL7jBRCYrLERD78UsoXXKSsR3YJKkzGOrVpvXG+QTKBJ4kQ+UUW6AvsHhuCTbm+qutycFbzoa5kl3ChQFWPnAxzw9TtSXQxSarLHuF63zOc2OPYhsCPevrWOXx0l17eJbL5ogmqyqJoBUqBHhmEXsajj6KNmk2yC72qzeEK9PYus0+VoW9f0BscMwWfZ5bMgmvRi13gOFcOwg5y6EK3czQxVD+6fYI97qEyMesXGhV5uu1z+Vuq5rHLreX13MJvZEMEz7WK1T8WrHRJD9ZgOIvkVdsem3ntaN8b4DT+qi8v1Jwhrye5QiFSFwZa7JrboAsFfSejMz67iwT912ZwIX7oqyMkvSJ9fjtp9YnukiAhuJTDZZxFherhzEj8b8HKwJbwmL5lEfieUnSL7weRstVGgO9be3dA5wv/xECur/CifhXmhZ0ZI/IaFLCV5ZfLeLdNvRa9w1UpYXrNhJvinfnc/1CTzRoFVeX/OCH+j3KZV4rSaGnQmRpvPvjRHIc31nPdJVNxJcdX+azc2xCYTd2d6QbrNicX85rYsmMm1Fhr0ZoXfIp3lbu/BJrdLZY0SuJMe5kegyDzTn6uTj2QrCQJ+kxWFmAgzISGcsOU7dtP8d19euxDQKv+sc4IPWb3cTQLzMbUXaDyI0IRFrkbsBIzlMChmMPXknuJibTlsxIfU0d+M4bJ0EcaHi7v0SMRqWepN/kPKOFND8AUHQXzUloUKJ2YurZv871YhmWgp3xbE03n89YtLE0Z+v05z7cfTaKXJszGlHIkpIMHFoEldoNKQHjDBRGPyHH2SG1ffrgst3lsEuzRDOO/vs09hJ8dtfGPZ/Zr9xdy7n02x1SZsRuInFK/FOcnVfDlCzpHGn6n7VY6CJLfXiG5WMXbXE/dubt/JviHNfEJlMQiHhBuBXWJpdbBbSegc6PhFsPAwmwppM9dXgw/WXSx2K41ro5hGbEDBuVdFDa/yUZr7+oAsVxcwtCQbWlCzj73YsVuAsRXXFBvQiMrg+GSGJPxkUSbXTB2UkPF6mHDVisqlnzvdjX5b1Q9qmI672o1leONExo3L8iRx+w/TBvEiUHhhqDAygqcls//pSJNucT8ufIvvI1DfYA0MpO7vf00BeopPl7u+LxEMyTXgqeEe8eIQSl+KTh8k+orj2Pe/PJzVKQzJU6sC0MoQOJd93Pn2s9E+DM2CL5gZL4wduT7dH5oJ9Tb9jAqk7QlJ93AORhyjXXoSFQm3s45v4q3ONBApz231gVnhWJ+VrbjKYr3/rB/0yQos5Cr9njxjViZ8OwCFT0tHzW/3em1xWwfQkf9bOBMkrHvfhd5z4Zl9CxsAdLdLGhlsmhtr3lu5Ccfj2dBkKWyUbUs0078XmQVPR4fvR7apKRNpxs+M9cLrVTPJ8kravy/gWjHPX65CYZvnp9gd0vQyIT7gRwaKFbtw92v0QQL6pkZ6Gk5DEKgbFJu7UrRfxFzH8forI1RbWTIPZQ7VG9/HHsK2WDS/8L9i+hKNN7IArFnxsiDQhh7sEd1amAthKQsJ9F2jP3XgC+BsyRijn3xHt4hP8uCdya5Db7vEe2ZEcDccetKwH05PRSEFRLIcSe5pqPui6yWpKxFvoBmmU8jGRn0Lis4u78AqHavz9jni4IwJIwLXSpobzaaOAqlsd/S061yl7rhlh2YKGY9Qhqo/y1QzRO22gg2oAGyzk0xlTKvZvqqevF76+JwdC7+4Zjm7MA84sjGY4Iprc5gJFkSEimTfjXVcWKtnG1p2OVsQUC1lmOQoe/J+ydUjX+MkmMXIjH6JBAnhwULT9O1xnFm8KEW9IrC1isgP3suktxVVfWEtjoSWFTn7rrMGLidR+DsgnFSOQGg8lEYzIM3fDYhzSrBHfG2ApZY+xf71uY9ix2eMmaoaDi5UZeoMRgO/T7XUXwd5jRAj0AbhqB5ivPBg22F8mk6YGqosUhZPQvErz0r6lSNEo5nJYqt1dxX2HwOSihBSRgnlNHWBlS/vhnOTWWdWw1b9LCt4GYeKmqLs2IpGM1I8BZAHBzU6YfP4B5wFfPfoF+6AuPHZiqzCcQsj5cfKRA+l3Omjig3VcTzj83Lnm509NlmyOpvhDaONIACu7rYPcc9i7l7SlMwnM9Y4jckR6rp6KbJsuMVDW9eCMIzfUIn4B9M6RNYce7o+30w/Vv4qn1Z5VaMp2CY8HD9Z7ogfJvRHKOZZt7TIXYpkvSmPMSrZO8GFmzVZ5uPDIz5CaGk/IYEsqa4B23zFaDOeVJJpoV8++7Qx7Iue0oIcL7S677UTzWRtooWmnVhgZVFb8Sva3I40H+Trf7yA49YiyoeLG5ME/cxBbHBmseh/H4MQPJpNZ59DsD72XK3p/H0gWEe+tj4+bsCV/EcZbK9lSbSCE/cXWWsTKrdsfQ4BMePR7I7pq1n/Mj3t3DDVDLxAyWs2i9+is47sxvsktoYJglr5DrbeAlnDt5N8BNO+GreJLwB4XLUqtIiG7DkUgrlb2QwlXh/mUkDjWdDkGJyUk3SfhoT48C92i8NXPZ17rBwi4OHvhILgjofcbodkN2macWjC0TyBuxKz2KaYAvd4f10kDA3XSRpLNj2KsL42RR0RqISOwwrPmFcZTEz0mgW3+s9jFRiSjnqTK6WcH+F85nbdGlFRL9jY5OVxWPgd2fd/3+cFrsB7tnLWrp1Y5N6abN2nXpRQqkQ2cb6N0psUsmlY6gbToN7Uod2GvtBIocpSx3O2lt9BJNBQNM7rSoRoh0UoBjw4UEaEvzRUSLaSt+NSuTXglXITIfAmVBwXAKzlSMGTK0hO13YaPuGlCr7haBKcexIVGxJ46kHqE/C1s0hXGvX7bv0POPK1PZVtKgcRmIm5Po9stQPr+eT4f4DJFQv0qY9rVPArfB56HNdZrG8rv0HcpGwvfwkzAQD95S0fBi3REMnV5bI83JH+op/pWYh89YYiFdgC0RDu0vvQi+vnWCsVyeaze5SHQYV0y5QeHCBATwZ42wEJ88l1Ip0gCG+Je8mFBwg+GJspxpEWglz1pN3G/dptJR5lg28JNeQD6zd4jOmrEecNjYu30CCv3k5cl8FwHubpUZYL5dhBFB7VzIjQ1RfcJhLBuMZDdlDty2XlqLBhYQ4/PEum6Rt5TscVAcrAq+gqvRKfsvLLdOMY8fyPFLHof5dZbWz/pf6Bc82rK9wiBx04jGOU2HZ/06h+wvhKsN9mpyVcS0fmqcsDRaPBqtQrM8vpoRR5C41pcLhDRBbK8m6QV8hBC54fWtkfOSCxTqE902xsZMne/1xwCxU03EPCnmkBuZjAxg1cpTe1Uv/jaktPHsk2RdnDMi+xhRel/9pU6Ze3erB3uXhVakLIU8pV2FmVfdZQq5nZGvOV5C3CleWLM9Ids88ByAvBsQAxfhwdBRuAY51yRwfDZh1xrBTV1De7EoxAaI8tS9IxsPjR4jmkY8E2yLu06FRXicuSx0T9xijk/RVQR/ZF8XcuODvozACKdprWiDaq3GCmtX+s+gy6JXpvgRfLBEQjTa8exOPcU4+IVv1oDFDE7xg2HYR6Kos/9X0LmsdXafwCAQ0ulvVOQLkzTBDi2zhjP2LY9c8a2bdv2Gdu2bdu2bdva99uIP2Lv974vuqu7ujKjK7PRO84MQm3VevUS65q1FXCgZ1VEB0QPhjH0tjyHqXXn0xPjdmaO762BkUP5IWE7bTnOx4IM9NOy+qLFVjFS4UwcPwrvq34rxL8GGn8Oi52WkScsBES3fCW2QzVTsT7cNDZQifNT7W8DdrshIISwfwZk7LwbFSK2dfVxIHxtxHdxTnB/VSX1//3xwTVMZ58WY1v1PjKENhPwq+OQ+Q3thBgQzrchKTpuh0mLc/zaK+X/trhg3AoawgMnZDuXoZiNjkuV4TCpM3hukmGj/D5gnGVPyf2lEr7/HhuzwNEZPdJ1aHs7YTjMtetmzd51jDUIypf+KZHNFXOmnbkGKdG5fkq/C7pqDr8Na3q7d4Rf/JlLVpcItOUd+4cJ1XV+0r3NqsoDSTw/5EWr88aAdljX6ICZukSeTXfMR/LjFjexXxBwJx0URKtuTrgF2AIS2beNmn66hsB3rDbvk/n05lxDbOvhtTj1cseBov97YvXlwvJLvAa/xWYr3Bqmyoqfwev1EmR5SFrwCnPdnfzTKtbK9O/2xRGTETQAq5sTIS4+i6wQc87bGNflu3JDoI8NweghCbgS7yu9KDo44sCaBqFV/09TCML0WaxJm6B8jgwLC6UUxmPUZ6qkP+esy8cpTUrhfedqH4f60J4xQy6ZG+hkVouT194q4Kkelq5tT7eZNjPAbklMOVVhRF5fGgsKbd4E0sJECi3X/q4fsnbygR6kKcA/gEv0Qe/3We/8C92OEm5A1PCqbkvcnQ5kwUi/6qgOgxnhmTSP0/RDlmSG1VwN4AY/58Qgdg6B+de5Ce26gHNJ22fXofaBXnXTW9yNMhe0Gm1GoCxJtUV2AeeEteLsr89sT48tswb0oEAapqhzUS1IDZLnY+ZulqolUlH0QHf4YB8bKg4UPLB/uNmtYYeqI0BX5cZ9SxF6ztabeCA1ZOqPUa2gV8O720V56X9Vgz1dZNA+c04V4L8spuRWThN1qKX5zbXRpCoOmu+IvGHBlJBqlWwFkspn7uaBDCKy10YmKnR4xuLwATIDERCwN+uFMoDEF+gWtGe2/kLZgWoLuJDyp4dJt5sLYi4CWQzlOJraJTKPkY/M2xywEc4UCEps5+pyT42yqw9V2Y136KJHLtrKByIOpcKc5xSf+Rd1BFux14MZjjBcXerwOyEiKtTDJUz3g3TK/3PInxBAuLcl/hW1F976afadSeNwKC8H0tVstyRDdbVnJctZtrp3PHKMqn0zsqvrDAoHUhewxtC3Je748366G+RQdvoWwPfoIyZbuwvBVKGZT9pRKO9d7XpVeQjiNi6+suyHI0sIF3DcLc5ObHAYjpZAHMNBZEOVwIcN8MWBVheys2CtZlWIrv8Lz42wTdpnSts6pU9yw9h382527gTuiaBaBVUJ0lofDXqVii626kL0pdu8nsB0WFbAq+1QuBHUhuz5mEsUgE+zD3fmmtSssd1gGKTgDNuZGS+QWM8weqJxTMTLK+rsXIk5+nINz/TIGDNJ2nfN1HrGAW1nDbg2HOyb1dEHcCzxqXHGI6FEg/R6uehqf31WyZ7uiDk2L7otOcFhq4IzlUNGzsp8nwmiRUGDBgjCt8qm7OkFCV32VDU3PTCi9R9+uRLN1FQoxiwul53nFnKQH7EneiFFBTPQFZqWpkNgh5mQ9vEEoVGFKnK8YttiJGV6QKzGLFgtBZgDbDGO5DbP9g4HG81mff1ZFHfsxjio6AcDS/P7HI0IlBUrtcLGxfkIgzDnXiGszipSLGyRcKAxiYGjFoXHEeE9TtLNSpJR6TofNyd4YaIDD+0q11/7+BcEcAOKC++Li52WAMdYtHtfm9lcuFPyMKR/Y+pHBV5m5+PdbSNPV364/K+A6+BBo6YsEG2H5083vnixByv8FuPeN7fP+MrhwAzGxF8S47Ni4s+48sovGlYLHK6sKW4kLjChnTkRZuoip6ke2gIchQ1YI/eFWtlhWTJBXPTfwoxS083yqhAokCdA6QFu+/rGrSqpJTzH54xwtpLB7IjFjutOnu9rRrEypVWPXyazS8N0qbwQ+bqHfDr5H2kbQbAlu0SHFL0UXKiBNGEgY80wI1NI1Ezl00M6yxynZQZkFm/MIv/BqhhUk0AcmKucoQkTwDnqe7v+O3Puu3TH6TK8ibWRIOF7n4UwJciuGBy4PJNrynOqdrhZEthOppAynXtmBW/mPlOKmAtNDkovIFEs5gk7pVlPXD9m686sNCvMiimroOYuNqs/hXmE/p3mwNFC5uuU+ouQ8opwg/C3t+PBQxEbamC+PslM3F1PVdimBL4rXNum4hCGenH6VIc32lJNrU77baqBwe/pYKQQ2ILH6JUIwK0hx/75LtXHZTInfOYZXWTNBjWBRccQ232zzcDSrvUphgk+4k8oVtgXK72f7ck8O8fOew473uGS1zO/ztCHGcYGhL+qx7I1+XoE0yk44hA8s76tmcp3Hvcon5eZHzuON4TG9/20uKoi7CsJcS9EOeRPB6uutDor3RzfJrgdp9+35lzBEDoAEDHzTmDKc2epgB+O+FeP1FMTqo8pvT6qAFtk3hVtM6SK9NjnFPwG+JY97MDkBvBoJB64z7tFUT88thwTU8k+8tH5acjt6wblo5aivk35K0G49D8DEfNz40CM5G+/hrlQfQomD+Nb6hbtH342r3/qbzNl3UjYEKAH7jyRVzIu/s8+rrqA/5+21kCOP/KG+FYZRULy+P+mJhmdby+ZBs+AE4GzmiZqag5qE0WCFZkU9t7P/4Qb3Ivj5jvxV+HqwOloVBJt8G6Uaw3RZscbJ1jr7tGbZ5FaH+nJeGm8oeH+AXAcmsv0dvRSN4gg5QR3oYWhDbnKOjE1ks+Eoef7fvxqyW+Cd04yaXce+pbTe4r5P9NK8wffuKgjTGh3n1BtTRhdLbVZ6XEvFHYmeBu11gCJUa0UfuSDgaM3NQdVd3bPITbMnaikcw5qmDSGPoOX0j7Xtu+ROaY1xOxl1qP9jWyooUFumMe6HqnTTedeAWskNohJCsMoHfKqRTdsF9c+o/U3HXqjtyEKa8wxUd5V7fEXPh+qTvX9r8Wr+4yoX4rS5aN0K/kwkK61Cn1pxHrHEVb6dQHR
*/