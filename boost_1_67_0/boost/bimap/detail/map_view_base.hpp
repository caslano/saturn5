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