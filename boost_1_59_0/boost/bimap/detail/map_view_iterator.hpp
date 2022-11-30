// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/map_view_iterator.hpp
/// \brief Iterator adaptors from multi-index to bimap.

#ifndef BOOST_BIMAP_DETAIL_MAP_VIEW_ITERATOR_HPP
#define BOOST_BIMAP_DETAIL_MAP_VIEW_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

// Boost

#ifndef BOOST_BIMAP_DISABLE_SERIALIZATION
  #include <boost/serialization/nvp.hpp>
  #include <boost/serialization/split_member.hpp>
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

#include <boost/iterator/detail/enable_if.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/bimap/relation/support/pair_by.hpp>

// check
#include <boost/bimap/relation/detail/metadata_access_builder.hpp>
#include <boost/bimap/relation/detail/static_access_builder.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/** \brief Map View Iterator adaptors from multi index to bimap.

These classes are based on transform iterators from Boost.Iterator.
                                                                         **/

template< class Tag, class BimapCore > struct       map_view_iterator ;
template< class Tag, class BimapCore > struct const_map_view_iterator ;

template< class Tag, class BimapCore > struct       reverse_map_view_iterator ;
template< class Tag, class BimapCore > struct const_reverse_map_view_iterator ;

template< class Tag, class BimapCore > struct       local_map_view_iterator ;
template< class Tag, class BimapCore > struct const_local_map_view_iterator ;


#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#ifndef BOOST_BIMAP_DISABLE_SERIALIZATION
/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT                   \
    BOOST_SERIALIZATION_SPLIT_MEMBER()                                        \
                                                                              \
    friend class ::boost::serialization::access;                              \
                                                                              \
    template< class Archive >                                                 \
    void save(Archive & ar, const unsigned int) const                         \
    {                                                                         \
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());   \
    }                                                                         \
                                                                              \
    template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       \
BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator :
    public const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    
    public:

    const_reverse_map_view_iterator() {}
    const_reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
	const_reverse_map_view_iterator(reverse_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// local_map_view_iterator

template< class Tag, class BimapCore >
struct local_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        local_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            local_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct local_map_view_iterator :
    public local_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        local_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    local_map_view_iterator() {}
    local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_local_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_local_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            local_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_local_map_view_iterator :
    public const_local_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_local_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_local_map_view_iterator() {}
    const_local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
	const_local_map_view_iterator(local_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DETAIL_MAP_VIEW_ITERATOR_HPP



/* map_view_iterator.hpp
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
*/