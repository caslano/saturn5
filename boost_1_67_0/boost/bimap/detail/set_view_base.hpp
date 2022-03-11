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