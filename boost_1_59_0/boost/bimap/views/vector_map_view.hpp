// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/vector_map_view.hpp
/// \brief View of a side of a bimap.

#ifndef BOOST_BIMAP_VIEWS_VECTOR_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_VECTOR_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/vector_map_adaptor.hpp>
#include <boost/bimap/support/iterator_type_by.hpp>
#include <boost/bimap/detail/map_view_base.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a side of a bimap.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core.

See also const_map_view.
                                                                             **/
template< class Tag, class BimapType >
class vector_map_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        vector_map_adaptor,
        Tag,BimapType,
        reverse_map_view_iterator, const_reverse_map_view_iterator
    ),

    public ::boost::bimaps::detail::
                map_view_base< vector_map_view<Tag,BimapType>,Tag,BimapType >
{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        vector_map_adaptor,
        Tag,BimapType,
        reverse_map_view_iterator, const_reverse_map_view_iterator

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(vector_map_view,Tag,BimapType)

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::data_extractor
    <
        Tag,
        BOOST_DEDUCED_TYPENAME BimapType::relation

    >::type key_from_base_value;

    public:

    typedef BOOST_DEDUCED_TYPENAME base_::value_type::info_type info_type;

    vector_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}

    vector_map_view & operator=(const vector_map_view & v)
    {
        this->base() = v.base();
        return *this;
    }
    
    BOOST_DEDUCED_TYPENAME base_::const_reference
        operator[](BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().operator[](n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference
        at(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().at(n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference
        operator[](BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type &>(
                this->base().operator[](n)
        ));
    }

    BOOST_DEDUCED_TYPENAME base_::reference
        at(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type &>(
                this->base().at(n)
        ));
    }
    
    BOOST_BIMAP_VIEW_ASSIGN_IMPLEMENTATION(base_)

    BOOST_BIMAP_VIEW_FRONT_BACK_IMPLEMENTATION(base_)

    // Lists operations

    void splice(BOOST_DEDUCED_TYPENAME base_::iterator position, vector_map_view & x)
    {
        this->base().splice(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            x.base()
        );
    }

    void splice(BOOST_DEDUCED_TYPENAME base_::iterator position,
                vector_map_view & x,
                BOOST_DEDUCED_TYPENAME base_::iterator i)
    {
        this->base().splice(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            x.base(),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }

    void splice(BOOST_DEDUCED_TYPENAME base_::iterator position,
                vector_map_view & x,
                BOOST_DEDUCED_TYPENAME base_::iterator first,
                BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        this->base().splice(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            x.base(),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
    }

    void remove(BOOST_DEDUCED_TYPENAME ::boost::call_traits< 
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type value)
    {
        this->base().remove(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(value)
        );
    }

    template< class Predicate >
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                key_from_base_value

            >( pred, key_from_base_value() )
        );
    }

    void unique()
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::key_type>,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                key_from_base_value

            >(std::equal_to<BOOST_DEDUCED_TYPENAME base_::key_type>(),
                    key_from_base_value() )
        );
    }

    template< class BinaryPredicate >
    void unique(BinaryPredicate binary_pred)
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                BinaryPredicate,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                key_from_base_value

            >( binary_pred, key_from_base_value() )
        );
    }

    void merge(vector_map_view & x)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::key_type>,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                key_from_base_value

            >( std::less<BOOST_DEDUCED_TYPENAME base_::key_type>(), 
                    key_from_base_value() )
        );
    }

    template< class Compare >
    void merge(vector_map_view & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                key_from_base_value

            >( comp, key_from_base_value() )
        );
    }

    void sort()
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::key_type>,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                key_from_base_value

            >( std::less<BOOST_DEDUCED_TYPENAME base_::key_type>(),
                    key_from_base_value() )
        );
    }

    template< class Compare >
    void sort(Compare comp)
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                key_from_base_value

            >( comp, key_from_base_value() )
        );
    }

    void reverse()
    {
        this->base().reverse();
    }

    // Rearrange Operations

    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position, 
                  BOOST_DEDUCED_TYPENAME base_::iterator i)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }

    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position,
                  BOOST_DEDUCED_TYPENAME base_::iterator first, 
                  BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
    }

};


} // namespace views

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,TYPENAME)            \
typedef BOOST_DEDUCED_TYPENAME MAP_VIEW::TYPENAME                             \
    BOOST_PP_CAT(SIDE,BOOST_PP_CAT(_,TYPENAME));
/*===========================================================================*/

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(MAP_VIEW,SIDE)               \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,reverse_iterator)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_reverse_iterator)
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::vector_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::vector_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::vector_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::vector_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,right)
};

} // namespace detail

/*===========================================================================*/
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY
/*===========================================================================*/

} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_VECTOR_MAP_VIEW_HPP


/* vector_map_view.hpp
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
*/