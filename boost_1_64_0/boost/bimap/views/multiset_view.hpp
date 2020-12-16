// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/multiset_view.hpp
/// \brief View of a bimap that is signature compatible with std::multiset.

#ifndef BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/multiset_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/bimap/detail/non_unique_views_helper.hpp>
#include <boost/bimap/detail/set_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::multiset.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::multiset.

See also const_multiset_view.
                                                                                    **/

template< class CoreIndex >
class multiset_view
:
    public BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        multiset_adaptor,
        CoreIndex,
        reverse_iterator,
        const_reverse_iterator
    ),

    public ::boost::bimaps::detail::
                set_view_base< multiset_view< CoreIndex >, CoreIndex >
{
    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(multiset_view, CoreIndex)

    typedef BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        multiset_adaptor,
        CoreIndex,
        reverse_iterator,
        const_reverse_iterator

    ) base_;

    public:

    multiset_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}

    /*
    template< class LowerBounder, class UpperBounder >
    std::pair<BOOST_DEDUCED_TYPENAME base_::const_iterator,
              BOOST_DEDUCED_TYPENAME base_::const_iterator>
        range(LowerBounder lower,UpperBounder upper) const
    {
        return this->base().range(

            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                LowerBounder,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( lower, this->template functor<
                            BOOST_DEDUCED_TYPENAME base_::value_from_base>() ),

            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                UpperBounder,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( upper, this->template functor<
                            BOOST_DEDUCED_TYPENAME base_::value_from_base>() )

        );
    }
    */

    multiset_view & operator=(const multiset_view & v) 
    {
        this->base() = v.base(); return *this;
    }

    BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP


/* multiset_view.hpp
19tYuZhiTDVmE2YXZh/mMMb6LfJ6mGLMeswOzD7MYUzyG3wfFnMuphGzC7MfcwST/iayW2/G5LRiR+yIHbEjdvz3H5/4+/+r6+Rf2aoVy07W+/+bXe//N8Y57zR3VBba+nJPk73kyXNnl5RNXlCqj6L0OUDgGW7Detfe7p/Ff56jQ1fsWWrnTbLh2Pk7ke9iFcjzXNLTdxLjJS70gfQKfXevU7xpEzl8mIn4KRweWpbzqswXC6U8E1zl0fxrGP9x3w8KvjM1weQxNE+7NE9pGijVDojfosg8yYcWcXbniWYzedIwaa3NE3HoO2eap80qB1CvbV6NmYLfkrA88XhP8jKyV8R34PAb+h245WI/l3V0nPaRyO/AXSJ+JtEHnO/AvdvCPfdgXyAvId+B26594TNhfaEkwdG/3h4zzTZ2v3aV0a6ZNVX19WXLVtVWrIzo2ybfH0iY4VYH551UjaezhMlNjNDJru4jXM/FauWlPNVXa9yd8CvMezjzooZfYcJ3xZ4+Ilj/UzvMjZP9Pg0TJ+8hMz1E/d5TB9hFwnZu8fecnPHnfM+JPKs+eH332Dybk3LKuVL15/4+wFLjT8tDG3bSfeNh4eM5KXobFo1w2rBqfV15TWWwBb3bcOGIyDYkHu82VHfvNlR37zbEvfk2rItsQ8K0rA0v/A9rw4bQNjTXlzu0DRNc18ti/Ox02lDmPnkLXcs7LnK+Uf8JLZ77xpl5IjQ/w5LNtUGOeMx0/O5x8uPMxd75Uf++E87PMdk78nr+5/Vcyuu5oNdzKa/nWF7PEb2eV3k/R0zx2+e/cdbFpUcSv3jnZbs6Hj5w1/WPsR8vzxEXf+6UtvtGHGj42o1V9ZXX3PhDr+eFXs/tvJ//6R4b9xnOs5fnwvbYPqN7zYWwIxwKe8Nh8BQ4XJ/tjDB7w3rdh36Nz703nKvx9YI+2NsVrkjDpUUJd5aGOxumwHNczyJKNFy9hnM/i8jQvejOsBD2gGNgFzgedoUlMAtWwGxYBbvDavWv6ei1gbk0SjpjdO9wHMzRZ2u94DRYAIv0mdxETX+Spj8ZypzspMP85Z3ODE1ntqYzR9NZpOmUaDrzNJ35ms4Zms4i9x6+ppMQpb4HaH0PhH5Y4ITTcYv/KOHyNFxfGA/7qV7KXWx47sO8hAnuae7HzBrHfiVmN+YA5gjm3PGB/cyN8A7MQX4fg8H9ywWY3RMC+5NTigL7k5VwF2ZPUG+UbWefbP3E0H3IrpPYr8RUYu7AHBscuq94ZDL7e1P4jWnA7MA8RDwPwZcw6VPZp8XY+4qHYHBPsdM09j8xxZiuw4gHdj+dtDHh+4fnFlMm4jyCSX+L/TzMLEwdpgmz+63Y/l7s+P85PrX1P0JGJ2P9b3+/fwcXirqB9twntzv2t1WWr62psIXoxX00k/O+UPc15K22pj7wDf+rsywjx7sqTj8spu/djceMti9Ygf2DqfPnB77VGoyJzIisflAW/hFieVRN8+/JOfdNyXGtf2/H477DUy/89XL/El9w9g+e3LGy80ef/8e0z+R19nvdp3i9T+V1/3Ly3vsK3AdpfWs7LA27D+qnzxoHwB56XcRYBXr/8xm9zhbCzXDW79tYqzDu53fPYYr1eZz7WvYRhmuYXrtCr1eVoq8w8jqlz7WcZ1ry3CryWrP597FrSeyIHbEjdvyTvTMBj6LIAnBPJgmBBEhCCAlHSDhCOA3IDUK4QVCDoKKiSSTBBBKIJCgq7kYXlVVcccWLXRWPFVbRxRtvVLxWVETWe9cLFRUVEQUVdf9+86amZ6Y7BHDPj/m+mr+r+lV13V1V3V3v4O/g7+Dv4O/g7+Dv4O+/5xeLmfWvnv8XnaVP/w8=
*/