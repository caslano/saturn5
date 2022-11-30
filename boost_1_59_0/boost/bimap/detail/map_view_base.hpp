// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/map_view_base.hpp
/// \brief Helper base for the construction of the bimap views types.

#ifndef BOOST_BIMAP_DETAIL_MAP_VIEW_BASE_HPP
#define BOOST_BIMAP_DETAIL_MAP_VIEW_BASE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <stdexcept>
#include <utility>

#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include <boost/bimap/relation/support/get_pair_functor.hpp>
#include <boost/bimap/relation/detail/to_mutable_relation_functor.hpp>
#include <boost/bimap/container_adaptor/support/iterator_facade_converters.hpp>
#include <boost/bimap/relation/support/data_extractor.hpp>
#include <boost/bimap/relation/support/opposite_tag.hpp>
#include <boost/bimap/relation/support/pair_type_by.hpp>
//#include <boost/bimap/support/iterator_type_by.hpp>
#include <boost/bimap/support/key_type_by.hpp>
#include <boost/bimap/support/data_type_by.hpp>
#include <boost/bimap/support/value_type_by.hpp>
#include <boost/bimap/detail/modifier_adaptor.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/bimap/detail/map_view_iterator.hpp>

namespace boost {
namespace bimaps {

namespace detail {


// The next macro can be converted in a metafunctor to gain code robustness.
/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(                               \
    CONTAINER_ADAPTOR, TAG, BIMAP, OTHER_ITER, CONST_OTHER_ITER               \
)                                                                             \
::boost::bimaps::container_adaptor::CONTAINER_ADAPTOR                         \
<                                                                             \
    BOOST_DEDUCED_TYPENAME BIMAP::core_type::                                 \
        BOOST_NESTED_TEMPLATE index<TAG>::type,                               \
    ::boost::bimaps::detail::      map_view_iterator<TAG,BIMAP>,              \
    ::boost::bimaps::detail::const_map_view_iterator<TAG,BIMAP>,              \
    ::boost::bimaps::detail::      OTHER_ITER<TAG,BIMAP>,                     \
    ::boost::bimaps::detail::CONST_OTHER_ITER<TAG,BIMAP>,                     \
    ::boost::bimaps::container_adaptor::support::iterator_facade_to_base      \
    <                                                                         \
        ::boost::bimaps::detail::      map_view_iterator<TAG,BIMAP>,          \
        ::boost::bimaps::detail::const_map_view_iterator<TAG,BIMAP>           \
    >,                                                                        \
    ::boost::mpl::na,                                                         \
    ::boost::mpl::na,                                                         \
    ::boost::bimaps::relation::detail::                                       \
        pair_to_relation_functor<TAG,BOOST_DEDUCED_TYPENAME BIMAP::relation>, \
    ::boost::bimaps::relation::support::                                      \
        get_pair_functor<TAG, BOOST_DEDUCED_TYPENAME BIMAP::relation >        \
>
/*===========================================================================*/


#if defined(BOOST_MSVC)
/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(TYPE,TAG,BIMAP)                      \
    typedef ::boost::bimaps::detail::map_view_base<                           \
        TYPE<TAG,BIMAP>,TAG,BIMAP > friend_map_view_base;                     \
    friend class friend_map_view_base;
/*===========================================================================*/
#else
/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(TYPE,TAG,BIMAP)                      \
    friend class ::boost::bimaps::detail::map_view_base<                      \
        TYPE<TAG,BIMAP>,TAG,BIMAP >;
/*===========================================================================*/
#endif


/// \brief Common base for map views.

template< class Derived, class Tag, class BimapType>
class map_view_base
{
    typedef ::boost::bimaps::container_adaptor::support::
        iterator_facade_to_base<
            ::boost::bimaps::detail::      map_view_iterator<Tag,BimapType>,
            ::boost::bimaps::detail::const_map_view_iterator<Tag,BimapType>
        > iterator_to_base_;

    typedef ::boost::bimaps::relation::detail::
        pair_to_relation_functor<Tag,
            BOOST_DEDUCED_TYPENAME BimapType::relation>      value_to_base_;

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
                           key_type_by<Tag,BimapType>::type       key_type_;

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
                          data_type_by<Tag,BimapType>::type      data_type_;

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
           pair_type_by<Tag,
              BOOST_DEDUCED_TYPENAME BimapType::relation>::type value_type_;

    typedef 
        ::boost::bimaps::detail::map_view_iterator<Tag,BimapType> iterator_;

    public:

    bool replace(iterator_ position, const value_type_ & x)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            derived().template functor<value_to_base_>()(x)
        );
    }

    template< class CompatibleKey >
    bool replace_key(iterator_ position, const CompatibleKey & k)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            derived().template functor<value_to_base_>()(
                ::boost::bimaps::relation::detail::
                    copy_with_first_replaced(*position,k)
            )
        );
    }

    template< class CompatibleData >
    bool replace_data(iterator_ position, const CompatibleData & d)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            derived().template functor<value_to_base_>()(
                ::boost::bimaps::relation::detail::
                    copy_with_second_replaced(*position,d)
            )
        );
    }

    /* This function may be provided in the future

    template< class Modifier >
    bool modify(iterator_ position, Modifier mod)
    {
        return derived().base().modify(

            derived().template functor<iterator_to_base_>()(position),

            ::boost::bimaps::detail::relation_modifier_adaptor
            <
                Modifier,
                BOOST_DEDUCED_TYPENAME BimapType::relation,
                BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                data_extractor
                <
                    Tag, BOOST_DEDUCED_TYPENAME BimapType::relation

                >::type,
                BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                data_extractor
                <
                    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                        opossite_tag<Tag,BimapType>::type,
                    BOOST_DEDUCED_TYPENAME BimapType::relation

                >::type

            >(mod)
        );
    }
    */

    template< class Modifier >
    bool modify_key(iterator_ position, Modifier mod)
    {
        return derived().base().modify_key(
            derived().template functor<iterator_to_base_>()(position), mod
        );
    }

    template< class Modifier >
    bool modify_data(iterator_ position, Modifier mod)
    {
        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        data_extractor
        <
            BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                        opossite_tag<Tag,BimapType>::type,
            BOOST_DEDUCED_TYPENAME BimapType::relation

        >::type data_extractor_;

        return derived().base().modify(

            derived().template functor<iterator_to_base_>()(position),

            // this may be replaced later by
            // ::boost::bind( mod, ::boost::bind(data_extractor_(),_1) )

            ::boost::bimaps::detail::unary_modifier_adaptor
            <
                Modifier,
                BOOST_DEDUCED_TYPENAME BimapType::relation,
                data_extractor_

            >(mod)
        );
    }

    protected:

    typedef map_view_base map_view_base_;

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




template< class Derived, class Tag, class BimapType>
class mutable_data_unique_map_view_access
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
                          data_type_by<Tag,BimapType>::type      data_type_;

    public:

    template< class CompatibleKey >
    data_type_ & at(const CompatibleKey& k)
    {
        typedef ::boost::bimaps::detail::
            map_view_iterator<Tag,BimapType> iterator;

        iterator iter = derived().find(k);
        if( iter == derived().end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->second;
    }

    template< class CompatibleKey >
    const data_type_ & at(const CompatibleKey& k) const
    {
        typedef ::boost::bimaps::detail::
                const_map_view_iterator<Tag,BimapType> const_iterator;

        const_iterator iter = derived().find(k);
        if( iter == derived().end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->second;
    }

    template< class CompatibleKey >
    data_type_ & operator[](const CompatibleKey& k)
    {
        typedef ::boost::bimaps::detail::
                      map_view_iterator<Tag,BimapType>          iterator;

        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
                         value_type_by<Tag,BimapType>::type     value_type;

        iterator iter = derived().find(k);
        if( iter == derived().end() )
        {
            iter = derived().insert( value_type(k,data_type_()) ).first;
        }
        return iter->second;
    }

    protected:

    typedef mutable_data_unique_map_view_access
                mutable_data_unique_map_view_access_;

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


template< class Derived, class Tag, class BimapType>
class non_mutable_data_unique_map_view_access
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
                          data_type_by<Tag,BimapType>::type      data_type_;

    public:

    template< class CompatibleKey >
    const data_type_ & at(const CompatibleKey& k) const
    {
        typedef ::boost::bimaps::detail::
                const_map_view_iterator<Tag,BimapType> const_iterator;

        const_iterator iter = derived().find(k);
        if( iter == derived().end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->second;
    }

    template< class CompatibleKey >
    data_type_ & operator[](const CompatibleKey&)
    {
        BOOST_BIMAP_STATIC_ERROR( OPERATOR_BRACKET_IS_NOT_SUPPORTED, (Derived));
    }

    protected:

    typedef non_mutable_data_unique_map_view_access
                non_mutable_data_unique_map_view_access_;

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


template< class Derived, class Tag, class BimapType>
struct unique_map_view_access
{
    private:
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
        value_type_by<Tag,BimapType>::type value_type;

    public:
    typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_
    <
        typename ::boost::is_const<
            BOOST_DEDUCED_TYPENAME value_type::second_type >::type,

        non_mutable_data_unique_map_view_access<Derived,Tag,BimapType>,
        mutable_data_unique_map_view_access<Derived,Tag,BimapType>

    >::type type;
};

// Map views specialize the following structs to provide to the bimap class
// the extra side typedefs (i.e. left_local_iterator for unordered_maps, 
// right_range_type for maps)

template< class MapView >
struct  left_map_view_extra_typedefs {};

template< class MapView >
struct right_map_view_extra_typedefs {};

} // namespace detail

// This function is already part of Boost.Lambda.
// They may be moved to Boost.Utility.

template <class T> inline const T&  make_const(const T& t) { return t; }

} // namespace bimaps
} // namespace boost


// The following macros avoids code duplication in map views
// Maybe this can be changed in the future using a scheme similar to
// the one used with map_view_base.

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_RANGE_IMPLEMENTATION(BASE)                       \
                                                                              \
typedef std::pair<                                                            \
    BOOST_DEDUCED_TYPENAME base_::iterator,                                   \
    BOOST_DEDUCED_TYPENAME base_::iterator> range_type;                       \
                                                                              \
typedef std::pair<                                                            \
    BOOST_DEDUCED_TYPENAME base_::const_iterator,                             \
    BOOST_DEDUCED_TYPENAME base_::const_iterator> const_range_type;           \
                                                                              \
                                                                              \
template< class LowerBounder, class UpperBounder>                             \
range_type range(LowerBounder lower,UpperBounder upper)                       \
{                                                                             \
    std::pair<                                                                \
                                                                              \
        BOOST_DEDUCED_TYPENAME BASE::base_type::iterator,                     \
        BOOST_DEDUCED_TYPENAME BASE::base_type::iterator                      \
                                                                              \
    > r( this->base().range(lower,upper) );                                   \
                                                                              \
    return range_type(                                                        \
        this->template functor<                                               \
            BOOST_DEDUCED_TYPENAME BASE::iterator_from_base                   \
        >()                                         ( r.first ),              \
        this->template functor<                                               \
            BOOST_DEDUCED_TYPENAME BASE::iterator_from_base                   \
        >()                                         ( r.second )              \
    );                                                                        \
}                                                                             \
                                                                              \
template< class LowerBounder, class UpperBounder>                             \
const_range_type range(LowerBounder lower,UpperBounder upper) const           \
{                                                                             \
    std::pair<                                                                \
                                                                              \
        BOOST_DEDUCED_TYPENAME BASE::base_type::const_iterator,               \
        BOOST_DEDUCED_TYPENAME BASE::base_type::const_iterator                \
                                                                              \
    > r( this->base().range(lower,upper) );                                   \
                                                                              \
    return const_range_type(                                                  \
        this->template functor<                                               \
            BOOST_DEDUCED_TYPENAME BASE::iterator_from_base                   \
        >()                                         ( r.first ),              \
        this->template functor<                                               \
            BOOST_DEDUCED_TYPENAME BASE::iterator_from_base                   \
        >()                                         ( r.second )              \
    );                                                                        \
}
/*===========================================================================*/


/*===========================================================================*/
#define BOOST_BIMAP_VIEW_ASSIGN_IMPLEMENTATION(BASE)                          \
                                                                              \
template< class InputIterator >                                               \
void assign(InputIterator first,InputIterator last)                           \
{                                                                             \
    this->clear();                                                            \
    this->insert(this->end(),first,last);                                     \
}                                                                             \
                                                                              \
void assign(BOOST_DEDUCED_TYPENAME BASE::size_type n,                         \
            const BOOST_DEDUCED_TYPENAME BASE::value_type& v)                 \
{                                                                             \
    this->clear();                                                            \
    for(BOOST_DEDUCED_TYPENAME BASE::size_type i = 0 ; i < n ; ++i)           \
    {                                                                         \
        this->push_back(v);                                                   \
    }                                                                         \
}
/*===========================================================================*/


/*===========================================================================*/
#define BOOST_BIMAP_VIEW_FRONT_BACK_IMPLEMENTATION(BASE)                      \
                                                                              \
BOOST_DEDUCED_TYPENAME BASE::reference front()                                \
{                                                                             \
    return this->template functor<                                            \
        BOOST_DEDUCED_TYPENAME base_::value_from_base>()                      \
    (                                                                         \
        const_cast                                                            \
        <                                                                     \
            BOOST_DEDUCED_TYPENAME BASE::base_type::value_type &              \
                                                                              \
        > ( this->base().front() )                                            \
    );                                                                        \
}                                                                             \
                                                                              \
BOOST_DEDUCED_TYPENAME BASE::reference back()                                 \
{                                                                             \
    return this->template functor<                                            \
        BOOST_DEDUCED_TYPENAME base_::value_from_base>()                      \
    (                                                                         \
        const_cast                                                            \
        <                                                                     \
            BOOST_DEDUCED_TYPENAME BASE::base_type::value_type &              \
                                                                              \
        >( this->base().back() )                                              \
    );                                                                        \
}                                                                             \
                                                                              \
BOOST_DEDUCED_TYPENAME BASE::const_reference front() const                    \
{                                                                             \
    return this->template functor<                                            \
        BOOST_DEDUCED_TYPENAME BASE::value_from_base>()                       \
    (                                                                         \
        this->base().front()                                                  \
    );                                                                        \
}                                                                             \
                                                                              \
BOOST_DEDUCED_TYPENAME BASE::const_reference back() const                     \
{                                                                             \
    return this->template functor<                                            \
        BOOST_DEDUCED_TYPENAME BASE::value_from_base>()                       \
    (                                                                         \
        this->base().back()                                                   \
    );                                                                        \
}
/*===========================================================================*/


#endif // BOOST_BIMAP_DETAIL_MAP_VIEW_BASE_HPP

/* map_view_base.hpp
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
*/