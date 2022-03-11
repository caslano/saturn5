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
    // diferent from the one used for the sides in wich case we have to add yet
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
    // This is a necesary extra level of indirection to allow unconstrained
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
        BOOST_DEDUCED_TYPENAME parameters::allocator::
            BOOST_NESTED_TEMPLATE rebind<relation>::other

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

// Two auxiliar metafunctions to compute the map view types
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