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
ovczSufoBonfCMe+v7W1Th2xf5bzfaRtHkuYaZbs0YU09QAzVff2KcEMzwyYlrjfmAExF+PeHns2xpYpwmTreVu2WWrDvtEnH7y/0Y/SDxaqOyqrOpmkHpjv+SlD3KQMw8ZDS5ta8jtN32GdCe36Xr3dpb6brV89277662K+tb9K7KN9Xbimm+7Duq84T66k6574F4j8UN9h/H+Pe3DvhCdELlX3zlc75yPah9lXorGcfzq6XWj/Ml3OJ0vdtcvjUrnu0b6IdmH6p4/l/DVqD8XHq64fJ+dbqj0on2ANo141032EnHUrDXMFZkQm5euoSyXwSmjLD2+A3hO7/nCtsPpT4HIPKYioJ877Qlu9K5XS93WHh8Hn7fHFDu86YTai8q4b6r+3uS+cJvb8mNC+DTPKS9jeSMtI5XuZvUfmqLxbPTpHzmXERO3prfWhRs5P9gXs7OKx07ZPkbi+mCHlzXenZu/X6Hql/WOdhJMd4+gXZyNg+pCz5HyenJ9viX+7Xpg9RE76Ol72Eu9sxZk9P6LqnMZ5vcgusSLjfDR1yL50mtaLacT/O1io/VMlrNJj22Qgdz32UZnSF0kdG637h4zAnq7fxy616t+zqs4K7Vk1e2d4HVvnUseeNXtcSLmaekd+42bnt96nzZ5Mkldh+3yPV51W7WLp75Qv2HXxG1MXS0pLgwMTy1Pf8tG7kedN7X60Qa2PGkZX01dViL2YO0SM0ZHpNWaZaPznWq1V99xMse/yj2RE/rPvaL6D6qN66dgFa5d97kgJl2+Govdz0vt1wndSj02850uYs339dfxQaK7bz+qgfdG732JHl1sP/J3ErO9VbIN9+dY8Umtfj3J11dk12YTVx9z/54n9M39ffA6Piffch/owuWa2P490OuabGp4vbB/vo9rLGMe+rsnr50RumX+bL8ZV50VrKa98oytgk1wvxne5xfVERvOUtzcni35f5IzbiMB1pQYxfXfk72cSTqrp1w8T+Tzdd1n9s8vxZNFOmU/o/SL3RjZjsDMkDR/5+1h++ki/414QUIaXqnvknSjXbEWt8uMW0us3M6BqPKwfyAzEWfYxTtW9qqV8+bqql2+oyOSkSlyqZpRUa/2ije/Wcgz40XTspnSO43uABNH3kU1bXEHHMRb/SbHnLrH3lo0dxb/lsbes+lkf9NP43C26ThUlsxWZw22ZxHNXmO/uI2SS0ggnEyad1zQoMy1CJh+ZcbZM3HkrgzJfRchMRWa8LdP8vM+i9oZVmVXITBB9SovinNdqJntoR+8pMFTaXYrag/WgXViYGwjzcInbb76MjNtF2HOwT9R+9VA4mH5uDucnZQbmL6swadhvgUdkhu79jQg3DrMbf22wf5EacNsOCUvCma1jgyMxR2EKMUMxjTB23z4ZyjhU+/LCvez3SvqcOlSkT78QN2efXudcY9Rx52KPvViXuuxVdrWLLr0VLvu75ps9FkybMOt4mRKmtgd1y5Ewpf6HjWVHy32ca2KyME9jPrDHst877xXcKqqqK8uKaqoqqsrsIAJ72Mm6miz1aR0I+ssz9/6rxX63tmGVl+iavSfUT2cz57hC7LepH12fqKk4i+7B9HWXi8x4sZeb63Y0Y99DfrDtSY55i+49qP3QUpG/16XP075WzleJrrFJRGpZK22HiXU3RLVDlVmLzBSp63XLIut6UBfVC8l8k4v5IpVrwO8w7VLsetuwffDyIflOWQbyPT1svw2Tt+JeYNxN/oWNE9YSjqUyzTFzMO8QgaU/OMveFHr0GpPeD+4Q+QlWRmi+rmFkad9r6om5p9wo5zPFPtHIp4b6evrq0rJ5YePAh0Qmz4r3mBftCpU58xcThsw=
*/