// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unordered_map_view.hpp
/// \brief View of a side of a bimap that is signature compatible with tr1::unordered_map.

#ifndef BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/bimap/container_adaptor/unordered_map_adaptor.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Map View of a bimap, signature compatible with tr1::unordered_map.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a tr1::unordered_map.

See also const_unordered_map_view.
                                                                             **/


template< class Tag, class BimapType >
class unordered_map_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_map_adaptor,
        Tag,BimapType,
        local_map_view_iterator,const_local_map_view_iterator
    ),

    public ::boost::bimaps::detail::map_view_base<
                unordered_map_view<Tag,BimapType>,Tag,BimapType >,
    public ::boost::bimaps::detail::
                unique_map_view_access<
                    unordered_map_view<Tag,BimapType>, Tag,  BimapType>::type

{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_map_adaptor,
        Tag,BimapType,
        local_map_view_iterator,const_local_map_view_iterator

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(unordered_map_view,Tag,BimapType)

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::
        unique_map_view_access<
            unordered_map_view<Tag,BimapType>, Tag,  BimapType

        >::type unique_map_view_access_;

    public:

    typedef std::pair<
        BOOST_DEDUCED_TYPENAME base_::iterator,
        BOOST_DEDUCED_TYPENAME base_::iterator
    > range_type;

    typedef std::pair<
        BOOST_DEDUCED_TYPENAME base_::const_iterator,
        BOOST_DEDUCED_TYPENAME base_::const_iterator
    > const_range_type;

    typedef BOOST_DEDUCED_TYPENAME base_::value_type::info_type info_type;

    unordered_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    using unique_map_view_access_::at;
    using unique_map_view_access_::operator[];

    unordered_map_view & operator=(const unordered_map_view & v) 
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
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,local_iterator)          \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_local_iterator)    \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,range_type)              \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_range_type)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,hasher)                  \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,key_equal)
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::unordered_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::unordered_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::unordered_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::unordered_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,right)
};

} // namespace detail

/*===========================================================================*/
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY
/*===========================================================================*/

} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP



/* unordered_map_view.hpp
umcwzYuGSJrz9p6X5T2DaV5U6JXetF6BdYL4Fv7flCdWJOYldk8cRVrjmsXHUP4dgu8b9UqV8aCsPzUx97OZZp49QOLdwkp37av6Ots7eRMaVx8icm3w59YP9Q1Lz0Dimm7PMVPOzw6m59jwNMt3sqkBmeYRMiYvdwbT3NS/6HU7xfGxSU38mpcmre7pvK679APmOdNisVcS/zTPNF4pMvTVYlc/MpdvK/Gax3Xb4OvJjMD69hPaf/Qjjsfr+Lw5bIFZgJnG+QJ4QstAvdsOp4fep5N1oNGpofXxkRqGlp95126a93hS5tSPdTfj+T6WjvGpn2Fj/BUuY85V0eN2GTcx/sJNxl/ittZlbLrOZWz6bMTYNF3HuqF5RGh9cTykX1ddvRH7mEsqZM9Yaip2TNsc2DNiHGtm6M7x7DwSGFpXWtLTuSd/MIyhDvm5Rn6iOd/R1IkasQ9wXXcqNPLtxD4Fe5XYO7mOYycb+dZiPxr7LLF3iZ5r6P2sWs7nOMebGoZ5h831efZlItNc7TxVF3uiaTunU9cebcAaTvh8xc5bLT/jJvnnveYcXp88311WncZ8N6xrjzo3nIC5MZu1tkDZzygvmzFbpu5lVETveYzKp0be282ax/tyvh+zmjgrNB7Y6xzucK85nDMN5f1Cz5g6whvgbtJQ0EvSgAdSUH2mSYbbfJQ0qPw4Mwe6UOxjfG7PfSca+UFmTfRMsZ/ouqZZbuRHm/cKFon9MF9kfZrDuTlybonPbY0z5RBZC5d0tKOsGXHNn6ljtXxo38MyKNfVffWePS6xc/Qte//u2XdKvFL0vsR7A2Iv8gXv2Y7nL1K2tZhrhaF+mT5Y+13tb2H0jwUgaWuDU/Kl3/NJP/vAIeH9bHVydL+4IDn6WXVdclgbMM+0yT/cyL+IOrW4vyW/Mm0XxZgMZKvzTZ2SLdzLFtQWkUFRdSpd6pTKE0orK4l1g+6R/Y7ItbCi5Dzz/1aRSzH97UNib1pPWda756lTF3ooH73fgzb63ccPsuS3GdNOmUT+bA/lz+ySeRWhF5O8+w71k23WdZN7y9yIlUqfeV/M53jPZaLx08O8V9dW/KziiyS/63vThcZPV7N+myl+bqPVxUW/O619QAuRudOq0vWYySacjq7PdoeKfC09XXvzDOI0202v8UNWYM2AiJkyPUrONzZrQNPEXkldyFE3eiFx62810e/E+rTXcGpC36d1EpkVVonO87RPMfrR0+AakUmLjJvM35ZQ55dS6FtlPD0S3fJJ/s5e79Op/FrkP5Gx9DFJ/mRvHehbkHkL8xHmHZsNfO/Ea+0uRtykTui9MPr9n2ku7/+M1Pq7bYglv4n6zC0ftrYP+pj6GxhA2asHweFPIBiv5xP4DX/voKfYW/vcxiYTVd75TVg3sbf3RY19tC520fC0PuM/NJbpLPKybmPWxDvJ+Vjfq/pd5GTjp5N5zpd3qPQfEkaW3EtUR5HWqQEi3yLqHtXKCvpNi2oHKXZZiL9CerPhyONm5BMc8rNMvfxe5LuqPRQvrzWnfBhctz8rMzQvOFuPF8JzML/C/Frd6uBb8NzMvb9nZt9riEPYvaY4fN1e1+Kjx1vVLuMyO087ixtlpO9/5ruM1WV9Weto8mGW/E7RcfkUzH1MiFZIvOpK54rGrKL5fMQbNSejPqpcpukfHhD7aGsQ/6H7lXjXOhn0k276ovvEPpIReXz0PE7r2csi08rUqSdtO7boObJp897P3cPuRTP1PhS0S1wlj8ZqHj2seZSOaapmFhfI7it5VDO7yJ6+HG2/m1PB2M98tzmx7MyiOfOrJE3l2dI2ZzvasvpPD1tf8r6PZofdRwmPuBKelufhGtc=
*/