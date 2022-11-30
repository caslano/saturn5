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
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
*/