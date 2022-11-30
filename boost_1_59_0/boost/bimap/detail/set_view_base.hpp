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
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
*/