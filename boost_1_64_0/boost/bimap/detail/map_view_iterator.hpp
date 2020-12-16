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
5NbP07xl5pOmdrj20arnKh8prltwWv4v/3nfR2NtuD78PsPNWhvOgJWW/tRBsKfWdHvD0dL7eh7spz01A+AcOBDWwEFwMRwMl8KT4HI4BK6R/tbCw1wb9VgXTa6JtnBN9Fivhx7LtdDK5Lxe8kpeySt5Ja/klbz+W7//zTFMwQmAI//9fym/nz6u3/9v6Pd/PsyBXeDT/P7PXK3f/6EH+53VJH993d/Dw439g5BMdhr+Y35PDzHu7wekB0The1r6OfhdK/0cfzJuuYH+ztecvzmdXT0d7dYE73fyPP9rYoDyMeEOBTq4eu4qXR1e5deHZOG7OHm6F3AeNfcu45ShgnhZc801zDBxfi/gd17Nx4x7eoq3rDk2435b4DLmCXI8ZM2/gXlRpgizA3ML5g7MDt1/FTO1q0vj/iPjT3LnLTgbKqiPrtOaaH10hdZZUbZuEepPsunRZ9xVaz/DXzG9ML90Qm1m55qoNlOkrQx+bUf+B7pl/Htj3+X4tZ1fG/enHbUdhe/r2w7+bNx3On77A1437q96nu92SbBtrg263yg9gdF1th3z3czIeT9TMYO7Uk9uXTQ/3xOsi9Vro+tiqEddjExQF2N1nl8WkfSE/8TsIrxzQ3Rd6BQkv7qQ/8Fu3gcb+28TneenMAPdNj7Q2H/nW399jPvrxl7ohu/jW3/DjfsvPesvB/Y27m/G15/6osnGfZtX/Zn9Gi9G1Zveu1a+S7+7IeG7pLk473P3iu16/ZDOz31U9270XBq8f35xYMrjAx8ufu5P28fdeN4nL/hozM81hcddjfsN/HEKf28NqHHrnJ1zYE84FvaF4+BgOB6eAifCAu2tmAAvgFNgoXXOzXw4BS7W3oq12ltxJ5wBv6Vzbp6Hl8EfwGL4S1gCfwdnw32wFL4F50hXTDnsCitgLvwcPAXOgyPgfDgeLoDTYBWcBRfCclgD58FaeDWsgzfARXAzrJcOnSVwq/Zo3AeXwse0V+Ob2qPxLdjA/7u0V+M57dX4GVwuXTEr4B/hSu3pWAXfhtfDf8EbYFvq40aYDdfBLvBmaOrN0ZgH/6p51RPgVnVKXSXP10311RMOhL3gJ2BvaHS6wnNhH1gI+2q+tT+cpXnXMjhQ9TUI3iSdMg/Bk6S7aAh8Bn5cOoyGwZfgcNXfaUr3Tkd9vcapBkwX/t6hdG9QO7sF9oG3qZ1tgsPh7fBT8E44Ft4FJ8PNcB78knQsbYGfh3fDzfAe+CC8V+neBr8BH4Avw+1K51fgr2CT2tsjOkdpB/wnfBSWH+a8cnLPzZHPL/8/7LnZwDzzdswLyfnmD911TH7/BxVzHoX1/6CM/6xuhH2QndbI+Id+oxXVli0sqmP8M+6n41781ZD75dEejPuuYHi518e45+Jez0DU2BQVf8mi+tD+gUnW2QN36HujncoxHfNYZ/65Tr9dFJizeP3P2pWOzBye+yxhh5p0VVaxGk64aP2nGSnez2tYoecpswRs9mzf8PMaEzxvqc/zMsP5q2/R86LyV93k8TyVZ10bnaep/RidMVvyGe9DzysdXlEULlMz39KIG+dk6zeg/BHa/N4yul8rImc2xLhnO0F3pBPkXh5xd/UxVGU2v7fjOP3mJS3mHGr3967RdcrzI3rnpYOUZ8b8Bp7ZVt8/gVDeU2Aw34V2vlXWOHvlXX4HuL89Lzf2RbKjRWClfuuqbGy9uBPc8PnuXEatsb9Jmq2ymltXbs8/VBs/g1V+ikPzUt346z5jf4p2s9WST9Hvdv2mvsr4+Zlxfyw/5M6r5urn3WTcH6M9pOtedLzZ6Imup93sSeX7vAfvSNdT7PozepZ7Y0+TbMvHZIpxKzGmJfMcieo4VI4=
*/