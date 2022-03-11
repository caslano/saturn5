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