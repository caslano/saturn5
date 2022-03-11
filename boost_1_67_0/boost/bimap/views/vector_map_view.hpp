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