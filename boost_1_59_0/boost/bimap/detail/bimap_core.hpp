// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/bimap_core.hpp
/// \brief Bimap base definition.

#ifndef BOOST_BIMAP_DETAIL_BIMAP_CORE_HPP
#define BOOST_BIMAP_DETAIL_BIMAP_CORE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/concept_check.hpp>

// Boost.MultiIndex
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>

// Boost.Bimap
#include <boost/bimap/relation/mutant_relation.hpp>
#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/relation/support/data_extractor.hpp>
#include <boost/bimap/tags/support/default_tagged.hpp>
#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/detail/manage_bimap_key.hpp>
#include <boost/bimap/detail/manage_additional_parameters.hpp>
#include <boost/bimap/detail/map_view_iterator.hpp>
#include <boost/bimap/detail/set_view_iterator.hpp>

#include <boost/bimap/set_of.hpp>
#include <boost/bimap/unconstrained_set_of.hpp>
#include <boost/core/allocator_access.hpp>

namespace boost {
namespace bimaps {

/// \brief Library details

namespace detail {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Type >
struct get_value_type
{
    typedef BOOST_DEDUCED_TYPENAME Type::value_type type;
};

struct independent_index_tag {};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief Base for the bimap class.
/**


See also bimap.
                                                                        **/


template< class LeftSetType, class RightSetType, class AP1, class AP2, class AP3 >
class bimap_core
{
    // Manage bimap key instantiation
    // --------------------------------------------------------------------
    public:

    typedef BOOST_DEDUCED_TYPENAME manage_bimap_key
    <
        LeftSetType

    >::type left_set_type;

    typedef BOOST_DEDUCED_TYPENAME manage_bimap_key
    <
        RightSetType

    >::type right_set_type;


    private:

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::default_tagged
    <
        BOOST_DEDUCED_TYPENAME left_set_type::user_type,
        ::boost::bimaps::relation::member_at::left

    >::type left_tagged_type;

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::default_tagged
    <
        BOOST_DEDUCED_TYPENAME right_set_type::user_type,
        ::boost::bimaps::relation::member_at::right

    >::type right_tagged_type;

    public:

    //@{

        typedef BOOST_DEDUCED_TYPENAME  left_tagged_type::tag  left_tag;
        typedef BOOST_DEDUCED_TYPENAME right_tagged_type::tag right_tag;

    //@}

    //@{

        typedef BOOST_DEDUCED_TYPENAME  left_set_type::value_type  left_key_type;
        typedef BOOST_DEDUCED_TYPENAME right_set_type::value_type right_key_type;

    //@}

    //@{

        typedef right_key_type  left_data_type;
        typedef  left_key_type right_data_type;

    //@}

    // Manage the additional parameters
    // --------------------------------------------------------------------
    private:

    typedef BOOST_DEDUCED_TYPENAME manage_additional_parameters<AP1,AP2,AP3>::type parameters;

    /// \brief Relation type stored by the bimap.
    // --------------------------------------------------------------------
    public:

    typedef ::boost::bimaps::relation::mutant_relation
    <

        ::boost::bimaps::tags::tagged<
            BOOST_DEDUCED_TYPENAME mpl::if_<
                mpl::and_
                <
                    BOOST_DEDUCED_TYPENAME left_set_type::mutable_key,
                    BOOST_DEDUCED_TYPENAME parameters::set_type_of_relation::left_mutable_key
                >,
            // {
                    left_key_type,
            // }
            // else
            // {
                    BOOST_DEDUCED_TYPENAME ::boost::add_const< left_key_type >::type
            // }

            >::type,
            left_tag
        >,

        ::boost::bimaps::tags::tagged<
            BOOST_DEDUCED_TYPENAME mpl::if_<
                mpl::and_
                <
                    BOOST_DEDUCED_TYPENAME right_set_type::mutable_key,
                    BOOST_DEDUCED_TYPENAME parameters::set_type_of_relation::right_mutable_key
                >,
            // {
                    right_key_type,
            // }
            // else
            // {
                    BOOST_DEDUCED_TYPENAME ::boost::add_const< right_key_type >::type
            // }

            >::type,
            right_tag
        >,

        // It is ::boost::mpl::na if no info_hook was included
        BOOST_DEDUCED_TYPENAME parameters::additional_info,

        // Force mutable keys
        true

    > relation;

    //@{

        typedef BOOST_DEDUCED_TYPENAME relation::left_pair  left_value_type;
        typedef BOOST_DEDUCED_TYPENAME relation::right_pair right_value_type;

    //@}

    // Bind the member of the relation, so multi_index can manage them
    // --------------------------------------------------------------------
    private:

    typedef BOOST_DEDUCED_TYPENAME relation::storage_base relation_storage_base;

    typedef BOOST_MULTI_INDEX_MEMBER(relation_storage_base, left_key_type, left)
        left_member_extractor;

    typedef BOOST_MULTI_INDEX_MEMBER(relation_storage_base,right_key_type,right)
        right_member_extractor;

    // The core indices are somewhat complicated to calculate, because they
    // can be zero, one, two or three indices, depending on the use of
    // {side}_based set type of relations and unconstrained_set_of and
    // unconstrained_set_of_relation specifications.

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::bimaps::detail::is_unconstrained_set_of< left_set_type >,
    // {
            mpl::vector<>,
    // }
    // else
    // {
            mpl::vector
            <
                BOOST_DEDUCED_TYPENAME left_set_type::
                BOOST_NESTED_TEMPLATE index_bind
                <
                    left_member_extractor,
                    left_tag

                >::type
            >
    // }
    >::type left_core_indices;

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::bimaps::detail::is_unconstrained_set_of< right_set_type >,
    // {
            left_core_indices,
    // }
    // else
    // {
            BOOST_DEDUCED_TYPENAME mpl::push_front
            <
                left_core_indices,

                BOOST_DEDUCED_TYPENAME right_set_type::
                BOOST_NESTED_TEMPLATE index_bind
                <
                    right_member_extractor,
                    right_tag

                >::type

            >::type
    // }
    >::type basic_core_indices;

    // If it is based either on the left or on the right, then only the side
    // indices are needed. But the set type of the relation can be completely
    // different from the one used for the sides in which case we have to add yet
    // another index to the core.

    // TODO
    // If all the set types are unsconstrained there must be readable compile
    // time error.

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<

        is_same< BOOST_DEDUCED_TYPENAME parameters::set_type_of_relation, left_based >,
    // {
            ::boost::bimaps::tags::tagged< left_set_type, left_tag >,
    // }
    /* else */ BOOST_DEDUCED_TYPENAME mpl::if_<
            is_same< BOOST_DEDUCED_TYPENAME parameters::set_type_of_relation, right_based >,
    // {
            ::boost::bimaps::tags::tagged< right_set_type, right_tag >,
    // }
    // else
    // {
            tags::tagged
            <
                BOOST_DEDUCED_TYPENAME parameters::
                set_type_of_relation::BOOST_NESTED_TEMPLATE bind_to
                <
                    relation

                >::type,
                independent_index_tag
            >
    // }
    >::type
    >::type tagged_set_of_relation_type;

    protected:

    typedef BOOST_DEDUCED_TYPENAME tagged_set_of_relation_type::tag
                        relation_set_tag;

    typedef BOOST_DEDUCED_TYPENAME tagged_set_of_relation_type::value_type
                        relation_set_type_of;

    // Logic tags
    // This is a necessary extra level of indirection to allow unconstrained
    // sets to be plug in the design. The bimap constructors use this logic
    // tags.

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::bimaps::detail::is_unconstrained_set_of< left_set_type >,

        BOOST_DEDUCED_TYPENAME mpl::if_<
            ::boost::bimaps::detail::is_unconstrained_set_of< right_set_type >,

            independent_index_tag,
            right_tag

        >::type,

        left_tag

    >::type logic_left_tag;

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::bimaps::detail::is_unconstrained_set_of< right_set_type >,

        BOOST_DEDUCED_TYPENAME mpl::if_< 
            ::boost::bimaps::detail::is_unconstrained_set_of< left_set_type >,

            independent_index_tag,
            left_tag

        >::type,

        right_tag

    >::type logic_right_tag;

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< 
        is_same< relation_set_tag, independent_index_tag >,

        BOOST_DEDUCED_TYPENAME mpl::if_< 
            ::boost::bimaps::detail::
                is_unconstrained_set_of< relation_set_type_of >,

            logic_left_tag,
            independent_index_tag

        >::type,

        BOOST_DEDUCED_TYPENAME mpl::if_<
            is_same< BOOST_DEDUCED_TYPENAME parameters::set_type_of_relation, left_based >,

            logic_left_tag,
            logic_right_tag

        >::type

    >::type logic_relation_set_tag;

    private:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        mpl::and_< is_same< relation_set_tag, independent_index_tag >,
                   mpl::not_<
                       ::boost::bimaps::detail::
                            is_unconstrained_set_of< relation_set_type_of > 
                   >
        >,
    // {
            BOOST_DEDUCED_TYPENAME mpl::push_front
            <
                basic_core_indices,

                BOOST_DEDUCED_TYPENAME relation_set_type_of::
                BOOST_NESTED_TEMPLATE index_bind
                <
                    ::boost::bimaps::relation::support::both_keys_extractor<relation>,
                    independent_index_tag

                >::type

            >::type,
    // }
    // else
    // {
            basic_core_indices
    // }

    >::type complete_core_indices;

    struct core_indices : public complete_core_indices {};

    // Define the core using compute_index_type to translate the
    // set type to an multi-index specification
    // --------------------------------------------------------------------
    public:

    typedef multi_index::multi_index_container
    <
        relation,
        core_indices,
        BOOST_DEDUCED_TYPENAME boost::allocator_rebind<BOOST_DEDUCED_TYPENAME
            parameters::allocator, relation>::type

    > core_type;

    // Core metadata
    // --------------------------------------------------------------------
    public:

    typedef BOOST_DEDUCED_TYPENAME ::boost::multi_index::
        index<core_type, logic_left_tag>::type  left_index;

    typedef BOOST_DEDUCED_TYPENAME ::boost::multi_index::
        index<core_type,logic_right_tag>::type right_index;

    typedef BOOST_DEDUCED_TYPENAME  left_index::iterator        left_core_iterator;
    typedef BOOST_DEDUCED_TYPENAME  left_index::const_iterator  left_core_const_iterator;

    typedef BOOST_DEDUCED_TYPENAME right_index::iterator       right_core_iterator;
    typedef BOOST_DEDUCED_TYPENAME right_index::const_iterator right_core_const_iterator;

    // Relation set view

    typedef BOOST_DEDUCED_TYPENAME ::boost::multi_index::index
    <
        core_type, logic_relation_set_tag

    >::type relation_set_core_index;

    typedef BOOST_DEDUCED_TYPENAME relation_set_type_of::
    BOOST_NESTED_TEMPLATE set_view_bind
    <
        relation_set_core_index

    >::type relation_set;

    public:

    typedef bimap_core bimap_core_;
};

// Two auxiliary metafunctions to compute the map view types
// The map view type can not be computed inside the bimap core because a 
// they need the bimap core to be parsed first.

template< class BimapBaseType >
struct left_map_view_type
{
    typedef BOOST_DEDUCED_TYPENAME BimapBaseType::left_set_type left_set_type;
    typedef BOOST_DEDUCED_TYPENAME
        left_set_type::BOOST_NESTED_TEMPLATE map_view_bind<
            BOOST_DEDUCED_TYPENAME BimapBaseType::left_tag, BimapBaseType
        >::type type;
};

template< class BimapBaseType >
struct right_map_view_type
{
    typedef BOOST_DEDUCED_TYPENAME BimapBaseType::right_set_type right_set_type;
    typedef BOOST_DEDUCED_TYPENAME
        right_set_type::BOOST_NESTED_TEMPLATE map_view_bind<
            BOOST_DEDUCED_TYPENAME BimapBaseType::right_tag, BimapBaseType
        >::type type;
};


} // namespace detail
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DETAIL_BIMAP_CORE_HPP

/* bimap_core.hpp
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
*/