// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/map_view.hpp
/// \brief View of a side of a bimap that is signature compatible with std::map.

#ifndef BOOST_BIMAP_VIEWS_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/map_adaptor.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a side of a bimap that is signature compatible with std::map.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::map.

See also const_map_view.
                                                                            **/

template< class Tag, class BimapType >
class map_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        map_adaptor,
        Tag,BimapType,
        reverse_map_view_iterator,const_reverse_map_view_iterator
    ),
    public ::boost::bimaps::detail::
        map_view_base< map_view<Tag,BimapType>,Tag,BimapType >,
    public ::boost::bimaps::detail::
        unique_map_view_access< map_view<Tag,BimapType>, Tag,  BimapType>::type
{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        map_adaptor,
        Tag,BimapType,
        reverse_map_view_iterator,const_reverse_map_view_iterator

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(map_view,Tag,BimapType)

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::
        unique_map_view_access<
            map_view<Tag,BimapType>, Tag,  BimapType

        >::type unique_map_view_access_;

    public:

    typedef BOOST_DEDUCED_TYPENAME base_::value_type::info_type info_type;

    map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}

    using unique_map_view_access_::at;
    using unique_map_view_access_::operator[];

    BOOST_BIMAP_MAP_VIEW_RANGE_IMPLEMENTATION(base_)

    map_view & operator=(const map_view & v) 
    {
        this->base() = v.base();
        return *this;
    }

    // It can be used enable_if here but the error message when there 
    // is no info is very clear like this

    template< class CompatibleKey >
    const info_type & info_at(const CompatibleKey& k) const
    {
        BOOST_DEDUCED_TYPENAME base_::const_iterator iter = this->find(k);
        if( iter == this->end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->info;
    }

    template< class CompatibleKey >
    info_type & info_at(const CompatibleKey& k)
    {
        BOOST_DEDUCED_TYPENAME base_::iterator iter = this->find(k);
        if( iter == this->end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->info;
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
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_reverse_iterator)  \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,range_type)              \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_range_type)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,key_compare)
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,right)
};

} // namespace detail

/*===========================================================================*/
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY
/*===========================================================================*/

} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_MAP_VIEW_HPP


/* map_view.hpp
TrpexEsxmz8BvYhFEboRIe28A/Mg5iDmKCbt1TZWPqYYsxTTiNmJeQhzCHMUk/YaOhAxJZhqTBNmN2b/azF5/9gRO2JH7IgdsSN2xI7YETtixyd7fGry/+V1K06G/L8tg39DlmVk5dkjkuMhlYG7GzPTfndwRECeXd4cLK+sVN19Xu9fqf+eRr7oFbHvsPrxP0PlMSLerzLh8rEH/chbsUY+5h3jrnJvJswgCZMt79mK+Lp5B+clcd9u5VFalQXhWGe+BZg50nZfJLK8D+JymHPbqJO0xN5pCWnONyBLO+g3INWfn7r6iu2v/enGz/asUD/5+LnJ9pN6jvGzI8v9LUl9l6KV8s8h70/oe5GUK+L9iSJzXuoxRC/CYX3eU4rpaFO/o71nZKCtW/Idbbv+Hhf/E7Xtg+Ez1c5bWqOw82fXib3vNZZ0b7brpM10Uye3OPUmfpbiZ6ftJ32U8XNrmJ+N+LlNZH/7Rsj+qh951nWH7Sepp/Fzp/o5kbp2f5OyIEG/X+T67uwK6i93VKD+WvINaH2vW8NMQOqzR9TvP+t7ScZfHi3m6stGlvSMUY7c1pmZ4sZj0oBMUS60ZU5ep072+xnbItPRJS2hTRpyGU4/3+Wqn+LjvNNZEuU70qWR35EWv7nwTPEbyBN1afSGPqgy7cXO+/HyPe06j7oMvCxf7y1HLuG6mT74LbEnad1GnXs0TJ7aTRh516uQtq5ODMhkpLZNTPalpA5DhmShLe3PTlPUtrhdwrdRezC++Gbb5hDpVCYev22O0z6TWts+7nnhY5Upf0OvAb/S73wfjGgLuQZ4tYH672Xkod8T+w+tDqR1F8brO+cyz4vfh632zPN3YLSNNM6cMFlqR8b5bXF/gvdZqG/nu9+EC//ud51pp3NHq5yBttNdane1qZHpGiRuZaQ31vj/sPl2levKQ6Q5Mlnbtc20tISOkW2arf4qg/78jdenJaSmJbSPPjaLTlLb236XhspkR45X/abpotHmm6di32nsoX3osTb6jSV9V+J01UtwdLT2If02sV5aPHVvxI8JvAud5uje0Dgy5Hpikc5mzO6w68A3T9IcPywt4LkXkfaBifBixkLJmLByaHU2I89CGJUnUxnai8T+J+85yYTpa94VXyf2Y657nfqVkqaOsSvE/TW3LLaRV3tG3NKi3gNdIm6H9b7L9GEzRjqN1XGnfX6I2H3SBvup/3QelN5rt0Fy45vBNijKCLRBpvoZmar3S77GvWltkiLumbLV37bU4Luui42Yntf7rfdJvnt5yujdO8aR0Qvm9SHi3yN5HWjy8J7e2+l3/o0s3qQW3pfZ77mOGGvec232Po1yeMq5HU6Lrk9q39iW65PCb7P6pB4Ze3L0SRGhHFdpqCsx9bZerUBe7UKrTFuFLeYXIs+meVW/aaY9P7btpJCh1+Al40QWFx+prvDL1L+G12/Dz8f+YSBtd/835c6WuOLNO/29xL6Q63s30Ykxx0o8rtxfO60TlYcTe7qxLwupn11aP6P0/ro/ps6WYRkXXj/V5fXV7vpxxuX9Wn6tLw2baeT4vp1lm5b0T/qjyee6EJm9hvaR8mIr7XYcF01ejHVpQ5WXrJiGyXSVpVLbyriZMfedE5QDs8sy0pSlMqQsxemRZTmHsqSP95J985Z7I4yRa0sXdwmg5THuzvrkBMsTlGtLl3OShpRphpZpaYfIMi2jTIWeZSqbVew6h3fPMha6yrg0QrbPuGv4CNk+3E+ubN/SSNk+9SfputsaD5H1cibhS6LUi6xjm6mHkrBy3HKC5XDn70CU/M0lf3XR8reipr5qTYNX/jRMprl2m3HluDnX0xPMezuzjxA5rnZ2jCw=
*/