// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/set_view_base.hpp
/// \brief Helper base for the construction of the bimap views types.

#ifndef BOOST_BIMAP_DETAIL_SET_VIEW_BASE_HPP
#define BOOST_BIMAP_DETAIL_SET_VIEW_BASE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/relation/support/data_extractor.hpp>
#include <boost/bimap/detail/modifier_adaptor.hpp>
#include <boost/bimap/detail/set_view_iterator.hpp>
#include <boost/bimap/relation/support/get_pair_functor.hpp>
#include <boost/bimap/relation/detail/to_mutable_relation_functor.hpp>
#include <boost/bimap/relation/mutant_relation.hpp>
#include <boost/bimap/container_adaptor/support/iterator_facade_converters.hpp>

namespace boost {
namespace bimaps {
namespace detail {

template< class Key, class Value, class KeyToBase >
class set_view_key_to_base
{
    public:
    const Key operator()( const Value & v ) const
    {
        return keyToBase( v );
    }
    private:
    KeyToBase keyToBase;
};

template< class MutantRelationStorage, class KeyToBase >
class set_view_key_to_base<MutantRelationStorage,MutantRelationStorage,KeyToBase>
{
    typedef BOOST_DEDUCED_TYPENAME MutantRelationStorage::non_mutable_storage non_mutable_storage;
    public:
    const MutantRelationStorage & operator()( const non_mutable_storage & k ) const
    {
        return ::boost::bimaps::relation::detail::mutate<MutantRelationStorage>(k);
    }
    const MutantRelationStorage & operator()( const MutantRelationStorage & k ) const
    {
        return k;
    }
};


// The next macro can be converted in a metafunctor to gain code robustness.
/*===========================================================================*/
#define BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(                               \
    CONTAINER_ADAPTOR, CORE_INDEX, OTHER_ITER, CONST_OTHER_ITER               \
)                                                                             \
::boost::bimaps::container_adaptor::CONTAINER_ADAPTOR                         \
<                                                                             \
    CORE_INDEX,                                                               \
    ::boost::bimaps::detail::                                                 \
              set_view_iterator<                                              \
                    BOOST_DEDUCED_TYPENAME CORE_INDEX::iterator         >,    \
    ::boost::bimaps::detail::                                                 \
        const_set_view_iterator<                                              \
                    BOOST_DEDUCED_TYPENAME CORE_INDEX::const_iterator   >,    \
    ::boost::bimaps::detail::                                                 \
              set_view_iterator<                                              \
                    BOOST_DEDUCED_TYPENAME CORE_INDEX::OTHER_ITER       >,    \
    ::boost::bimaps::detail::                                                 \
        const_set_view_iterator<                                              \
                    BOOST_DEDUCED_TYPENAME CORE_INDEX::CONST_OTHER_ITER >,    \
    ::boost::bimaps::container_adaptor::support::iterator_facade_to_base      \
    <                                                                         \
        ::boost::bimaps::detail::      set_view_iterator<                     \
            BOOST_DEDUCED_TYPENAME CORE_INDEX::iterator>,                     \
        ::boost::bimaps::detail::const_set_view_iterator<                     \
            BOOST_DEDUCED_TYPENAME CORE_INDEX::const_iterator>                \
                                                                              \
    >,                                                                        \
    ::boost::mpl::na,                                                         \
    ::boost::mpl::na,                                                         \
    ::boost::bimaps::relation::detail::                                       \
        get_mutable_relation_functor<                                         \
            BOOST_DEDUCED_TYPENAME CORE_INDEX::value_type >,                  \
    ::boost::bimaps::relation::support::                                      \
        get_above_view_functor<                                               \
            BOOST_DEDUCED_TYPENAME CORE_INDEX::value_type >,                  \
    ::boost::bimaps::detail::set_view_key_to_base<                            \
        BOOST_DEDUCED_TYPENAME CORE_INDEX::key_type,                          \
        BOOST_DEDUCED_TYPENAME CORE_INDEX::value_type,                        \
        BOOST_DEDUCED_TYPENAME CORE_INDEX::key_from_value                     \
    >                                                                         \
>
/*===========================================================================*/


/*===========================================================================*/
#define BOOST_BIMAP_SEQUENCED_SET_VIEW_CONTAINER_ADAPTOR(                     \
    CONTAINER_ADAPTOR, CORE_INDEX, OTHER_ITER, CONST_OTHER_ITER               \
)                                                                             \
::boost::bimaps::container_adaptor::CONTAINER_ADAPTOR                         \
<                                                                             \
    CORE_INDEX,                                                               \
    ::boost::bimaps::detail::                                                 \
              set_view_iterator<                                              \
                    BOOST_DEDUCED_TYPENAME CORE_INDEX::iterator         >,    \
    ::boost::bimaps::detail::                                                 \
        const_set_view_iterator<                                              \
                    BOOST_DEDUCED_TYPENAME CORE_INDEX::const_iterator   >,    \
    ::boost::bimaps::detail::                                                 \
              set_view_iterator<                                              \
                    BOOST_DEDUCED_TYPENAME CORE_INDEX::OTHER_ITER       >,    \
    ::boost::bimaps::detail::                                                 \
        const_set_view_iterator<                                              \
                    BOOST_DEDUCED_TYPENAME CORE_INDEX::CONST_OTHER_ITER >,    \
    ::boost::bimaps::container_adaptor::support::iterator_facade_to_base      \
    <                                                                         \
        ::boost::bimaps::detail::      set_view_iterator<                     \
            BOOST_DEDUCED_TYPENAME CORE_INDEX::iterator>,                     \
        ::boost::bimaps::detail::const_set_view_iterator<                     \
            BOOST_DEDUCED_TYPENAME CORE_INDEX::const_iterator>                \
                                                                              \
    >,                                                                        \
    ::boost::mpl::na,                                                         \
    ::boost::mpl::na,                                                         \
    ::boost::bimaps::relation::detail::                                       \
        get_mutable_relation_functor<                                         \
            BOOST_DEDUCED_TYPENAME CORE_INDEX::value_type >,                  \
    ::boost::bimaps::relation::support::                                      \
        get_above_view_functor<                                               \
            BOOST_DEDUCED_TYPENAME CORE_INDEX::value_type >                   \
>
/*===========================================================================*/


#if defined(BOOST_MSVC)
/*===========================================================================*/
#define BOOST_BIMAP_SET_VIEW_BASE_FRIEND(TYPE,INDEX_TYPE)                     \
    typedef ::boost::bimaps::detail::set_view_base<                           \
        TYPE< INDEX_TYPE >, INDEX_TYPE > template_class_friend;               \
    friend class template_class_friend;
/*===========================================================================*/
#else
/*===========================================================================*/
#define BOOST_BIMAP_SET_VIEW_BASE_FRIEND(TYPE,INDEX_TYPE)                     \
    friend class ::boost::bimaps::detail::set_view_base<                      \
        TYPE< INDEX_TYPE >, INDEX_TYPE >;
/*===========================================================================*/
#endif


/// \brief Common base for set views.

template< class Derived, class Index >
class set_view_base
{
    typedef ::boost::bimaps::container_adaptor::support::
    iterator_facade_to_base
    <
        ::boost::bimaps::detail::
                  set_view_iterator<BOOST_DEDUCED_TYPENAME Index::      iterator>,
        ::boost::bimaps::detail::
            const_set_view_iterator<BOOST_DEDUCED_TYPENAME Index::const_iterator>

    > iterator_to_base_;

    typedef BOOST_DEDUCED_TYPENAME Index::value_type::left_value_type          left_type_;

    typedef BOOST_DEDUCED_TYPENAME Index::value_type::right_value_type        right_type_;

    typedef BOOST_DEDUCED_TYPENAME Index::value_type                          value_type_;

    typedef ::boost::bimaps::detail::
                    set_view_iterator<BOOST_DEDUCED_TYPENAME Index::iterator>   iterator_;

    public:

    bool replace(iterator_ position,
                 const value_type_ & x)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),x
        );
    }

    template< class CompatibleLeftType >
    bool replace_left(iterator_ position,
                      const CompatibleLeftType & l)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            ::boost::bimaps::relation::detail::copy_with_left_replaced(*position,l)
        );
    }

    template< class CompatibleRightType >
    bool replace_right(iterator_ position,
                       const CompatibleRightType & r)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            ::boost::bimaps::relation::detail::copy_with_right_replaced(*position,r)
        );
    }

    /* This function may be provided in the future

    template< class Modifier >
    bool modify(iterator_ position,
                Modifier mod)
    {
        return derived().base().modify(

            derived().template functor<iterator_to_base_>()(position),

            ::boost::bimaps::detail::relation_modifier_adaptor
            <
                Modifier,
                BOOST_DEDUCED_TYPENAME Index::value_type,
                BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                data_extractor
                <
                    ::boost::bimaps::relation::member_at::left,
                    BOOST_DEDUCED_TYPENAME Index::value_type

                >::type,
                BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                data_extractor
                <
                    ::boost::bimaps::relation::member_at::right,
                    BOOST_DEDUCED_TYPENAME Index::value_type

                >::type

            >(mod)
        );
    }
    */
    /*
    template< class Modifier >
    bool modify_left(iterator_ position, Modifier mod)
    {
        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        data_extractor
        <
            BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::member_at::right,
            BOOST_DEDUCED_TYPENAME Index::value_type

        >::type left_data_extractor_;

        return derived().base().modify(

            derived().template functor<iterator_to_base_>()(position),

            // this may be replaced later by
            // ::boost::bind( mod, ::boost::bind(data_extractor_(),_1) )

            ::boost::bimaps::detail::unary_modifier_adaptor
            <
                Modifier,
                BOOST_DEDUCED_TYPENAME Index::value_type,
                left_data_extractor_

            >(mod)
        );
    }

    template< class Modifier >
    bool modify_right(iterator_ position, Modifier mod)
    {
        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        data_extractor
        <
            BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::member_at::right,
            BOOST_DEDUCED_TYPENAME Index::value_type

        >::type right_data_extractor_;

        return derived().base().modify(

            derived().template functor<iterator_to_base_>()(position),

            // this may be replaced later by
            // ::boost::bind( mod, ::boost::bind(data_extractor_(),_1) )

            ::boost::bimaps::detail::unary_modifier_adaptor
            <
                Modifier,
                BOOST_DEDUCED_TYPENAME Index::value_type,
                right_data_extractor_

            >(mod)
        );
    }
    */
    protected:

    typedef set_view_base set_view_base_;

    private:

    // Curiously Recurring Template interface.

    Derived& derived()
    {
        return *static_cast<Derived*>(this);
    }

    Derived const& derived() const
    {
        return *static_cast<Derived const*>(this);
    }
};



} // namespace detail
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DETAIL_SET_VIEW_BASE_HPP

/* set_view_base.hpp
JZe8aUM92IU6nfQnxsWlkjEJSckJTfxkxUroem3N80XiP1fy658ZG7LX0mr+hI6dtA4fl6zB/945Iflw1HHJgPu2EfOp2NinWnWwYkFZOUFaY3p2GIskDK9Pfr6xbxlcl/0vj3Nq3lj51VDmqcbRGv9YJG4lXiF7q7ZkOHKN0Xw8F3UTbqsqTD4Sfums2urKsOc7XfJQ3RJCd8ZGB6Psdl73UZg8J2h1n2LtD2G3QF/NTy883fOg9vman7a9Pod9yccBx5GXDZ/DAmvfQ/g+Eolbg/0NEp+Q+rg/25GrnPhlwPFwKYktmR/MR2riYvOqDMtLrY/qPtv0u+eJfoR7wEkUP0sCdbTA+p5TP10dq+9h+gdV6K4V+x5utPfj52LflPQkOFn6zr5SzDq6dZiucOIYTUyy+i6yD8Tc/9fiNsvU74bffOSlHTf5Ugy+vz8Uv62dFH1/q7/51n4F2+88/Eq66hukqyRV7OWjwoyf6HdmY8ef92SztZ/refH7R0YkXcyGp+pj4FSL+QVqhkOuRQsCe3na8S7cisOdWcF2YtWVvAN9KUkJoHFapLYiH7MklVtC/0f6OpnwKf+3XHag/UjU/g99HH4fvZ+TxjfazRInp1PZHL7S1GyRmlHJMFTZKBHqu7/wqUeYUY/Er30ubqDuaH3Xvo+Wtz4XDfs5qqfM9NvQhCXlZZ6xkkA8KKPQZ6ewne7LIvLpsAiuJH4pC+1nR5s0rQ/L9Tmw3uXqvrMZHxwg+t5uthsX7f2ufjL1eaMMRD/EPdV1rbEm3dNj1Z8zxF1Xt6Xrs+pnWRXp1b4G4/mBsOzxJxmpSNN+xiNifx/f/wPVzHVKxOxzYrTV7n8F3p/6POeLm/6u/7vlAHVmY1vTNs9I6uVvlRuZd2Mh5mehrDbajP/Nl3Dakue+hnuRzHfYIpM/PqnPvQm3qRMYh5pqjYUlat+jN79nwD2oxLRj62+0rbL6G1pnlzeon3MifB9UmTEp8qfBd9Ka9g3muPT7oLDCrlOIY9cvhCjfB+q+XbT6g/3Rvw80jGjfB2rf6j/y+6AqR59N7ZMN03m5Ku87C1lMzM1F7oeou0zz3Fwj+iGE5drzcaavcJXY9yVHEzWPg2Gkmzqdl33i5+LYUyvXDG2/R8PZuHPm2unU5jtq+63urfY7W/SFbpobmF8raxE+nlis/o7Uhp8esI/aht+GfcM2fICYtXHLMa2kDf8kUhuu8a4Tt1naXoe34UVHaMOvE78tnWZHaMPTTVtsjUNa79NfSBjfcC5p0B7nivky/Hvt8R1idgu9vvyo3wZ2fo0N/zaQfk1tDuWeG2jL/W/NusS45EanJHX3N+bNcROpPe+OWRPMCk177o1bvqBtOKRdP3o77n/3pc4z775I7bU5y556Y41NRm+zCyO02UX/Qps9NkqbndzFkWuQv44r5xHH7fPs50WbbK07Zfr+tN6v6r6zN6cn+pbuJU7UNlv95Jpn7G3Rt3Yr+Rtp3nQSuo/FTZLrtcVMHVnjRZ+KfZxbjI9oc5npcFOlfB+qHh+iHx4+9qD1+k0J90Fk8Y/WMcugn1HW94UlE1D9XSduKsP8pFNvN3XER+dAmx+36mZ/1W3doL2P2p6Pl3Da0Nr47Pqs7bm23Q3muD5DnZ199HEOf33OrgyX41em7ZCRiRmhLZ/UYH7JrmsTukZuy1O8tlzeKdqUR23LU47SlqccQ1uecpS2POU/sC0P5uMBzccszcdUHV88YMaOaspn1VVX1C6VBUBRx44ONFj/c+5xpM1Oh/2dcUf3gOPOcbxTlXdSz0suC8RtIcuzjlK+6ra3efYuFf1ffawEs9edmWd+udh/7puHidYBDaNHxDo=
*/