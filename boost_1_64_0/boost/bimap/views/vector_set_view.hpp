// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/vector_set_view.hpp
/// \brief View of a side of a bimap that is signature compatible with std::vector.

#ifndef BOOST_BIMAP_VIEWS_VECTOR_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_VECTOR_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/vector_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/bimap/detail/set_view_base.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::vector.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::vector.

See also const_set_view.
                                                                                    **/

template< class CoreIndex >
class vector_set_view
:
    public BOOST_BIMAP_SEQUENCED_SET_VIEW_CONTAINER_ADAPTOR(
        vector_adaptor,
        CoreIndex,
        reverse_iterator, const_reverse_iterator
    ),

    public ::boost::bimaps::detail::
                set_view_base< vector_set_view< CoreIndex >, CoreIndex >
{
    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(vector_set_view,CoreIndex)

    typedef BOOST_BIMAP_SEQUENCED_SET_VIEW_CONTAINER_ADAPTOR(
        vector_adaptor,
        CoreIndex,
        reverse_iterator, const_reverse_iterator

    ) base_;

    public:

    vector_set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}

    vector_set_view & operator=(const vector_set_view & v)
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

    // List operations

    void splice(BOOST_DEDUCED_TYPENAME base_::iterator position, 
                vector_set_view & x)
    {
        this->base().splice(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            x.base()
        );
    }

    void splice(BOOST_DEDUCED_TYPENAME base_::iterator position,
                vector_set_view & x,
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
                vector_set_view & x,
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

    template<typename Predicate>
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( pred, this->template functor<
                            BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void unique()
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
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
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( binary_pred,
               this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::value_from_base>() 
            )
        );
    }

    void merge(vector_set_view & x)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<
                        BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }

    template< class Compare >
    void merge(vector_set_view & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( comp, this->template functor<
                        BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void sort()
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
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
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( comp, this->template functor<
                        BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
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
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_VIEWS_VECTOR_SET_VIEW_HPP


/* vector_set_view.hpp
Vwqx3Sbnjzdz38S0wNy3pAH6W7zmBONN2yJ9of14dZ4g1w9bI+2kehAX+gJ5fjr8u71Guic8z2tL5pSWzHNkvuVsc9KOTf6PFL8VvhJfKP8lPCTs/Rkfxk9xa+4B0D+P+X9KK82DUH96dKbu56jyS4PyIxsmvw75Y6A/NVr+/VYqH9oTlrCRr9fsa3uQPAlbl8puGxAu1vp9AqYnASb/ZPJaFlJDE7OayLGwWZfqIH6OsPryPypUzzWs1Mgxm6nnJ8r55rKvZh5lvxVzbDCfspvGM5rI03FEUHenWefM36+9kANpfzcrpCswQ3ml3bbD065zgBqvZ20q38aMQW8T+wBmpDGuuu2/l/On2fppjf6UBJ0HOOcW/p9tuXLGoYmi9yn4fcfttn9Cby1uCPL7h7hdwlw7zjodeTedHq01fm+L7KXELomVilj2oYiPHIuaPV2TJQ4nkpoMdfNpvCaxOj5Ans11akuZtQvsOe9vx/pZz8SpumYdG1fPWP19iUcz0h4jZV9NGFswUvbtTNl3cit727TWa2dkBfUaFMs+rMO99Huq/NAs1WnQtCZyD1YjU4xMsowp666JupepzCJkUmQsWLfE3MsiZFZl4S8g81JQpiB1r/XX0Z96P49drLriBpPQ1rAn3Gqvs/9s6q9jcT2oncfybL8viL8LrDH8nxxqvxpeO62X9kpBQE93e/QrpIb2CNPgdR5r/OWaOeCrYm8eM5A6OhkTOQfM0vaxUeQyYuz58gmYNXyhX+z7vYRbbsLNJs2yZsdZ2XeTh/7Xs7dNVwLsozreXOqezmtaiZ+NxN8fpUczXeeib8h1msQciuwkjC33hbSR8L1mB0lYNzv1Ipq53GVyLsc3l73S36G1tRZ31zhHzVcr5dtO5Pgy120f2HlyjjIQe3i52HGtknTPmFEe6muZv5u997GzSiD2JpHt34zxTpEw5/jEbsq+ucz7tiB/dY60V9pedmJju8k2sZtsvuXaX6ufDTnaXmMXJsW1ZMZ4WlJcI6+5ovrZnqNttnndTRFt1oTbqYPROfmI6JwcX49OF/VzM376yrOAujeTOjcK3INwW4GRdw3q3mMr+F6kLMn0KW/j/ndMxLM48wzjd5JH2fSPTcy870Fx88u1ndff0MHovNyY5G8W1R91ULmkjpQdcv5zW/NoMC+xK/pGGifZPWyS57MsZ94U4P/WgB6dMsmbY/eeN+s6BvPm3EuTOidI3ozG7WEMeUNcrtrnvBnlU13fJm+0DmreOMt8C9e5LaDHp84rXzp1CubLxn3Ml733vcVR81SnPkHT3+k+xt663F/P1f2CMO2UCwm3Lsbsnx16r0fVE3uMNdRPtrmHrhD7Sutaruex3q1+Opp7+k1iv5n9XxJd92X/SM6XMJJLdhtHmPnhJpGLMTpp3hP7THz6ovsT7X++R4az0n8soex65Oq4oWNw3EABxsZF9tvmmq+L/8Zu15T6ucrWe5WrY4iODRtD2PGYnhscQ5RI88j1HkMgLxv8qF6k6qg2a3QuNuC5yt51LkpZht3387ta8vtOn69/gbnbrk/+qPqk74mJ2gXvOuUP38f6SrEXWEP4jyyHdJV5VWRutFL4X+zYIztB615wDJsca8vNYOYbHzaGvVr89w0bw24StxusZGQvxLiNnWMlvHKrkLqr15TnG3YC07WOdRSZ0VZLGVd2MPe6w2x3/LU26xm8TlRWUzui8tS58ypqy6sc9bSNyAb6vLdzaa95WqcyTJ3q6VangvKr84Lrob+S5dBB/HvUJ5HfmBdc56xbGlmfgv3YSVx/LpnQA7kjW+69btlrb0WxZl92z/GkeT7XTceTmKb6DtvzyK6LNfVKp4E=
*/