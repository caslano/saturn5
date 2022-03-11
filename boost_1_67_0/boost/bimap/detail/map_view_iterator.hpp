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
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

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
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
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
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

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
    const_reverse_map_view_iterator(const_reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}
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
    local_map_view_iterator(local_map_view_iterator const & iter)
      : base_(iter.base()) {}

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
    const_local_map_view_iterator(const_local_map_view_iterator const & iter)
      : base_(iter.base()) {}
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