// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/set_view_iterator.hpp
/// \brief Iterator adaptors from multi-index to bimap.

#ifndef BOOST_BIMAP_DETAIL_SET_VIEW_ITERATOR_HPP
#define BOOST_BIMAP_DETAIL_SET_VIEW_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

// Boost

#ifndef BOOST_BIMAP_DISABLE_SERIALIZATION 
  #include <boost/serialization/nvp.hpp>
  #include <boost/serialization/split_member.hpp>
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

#include <boost/iterator/detail/enable_if.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/bimap/relation/support/get_pair_functor.hpp>

namespace boost {
namespace bimaps {
namespace detail {


/** \brief Set View Iterator adaptor from multi index to bimap.

This is class is based on transform iterator from Boost.Iterator that is
modified to allow serialization. It has been specialized for this
library, and EBO optimization was applied to the functor.

                                                                      **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class CoreIterator > struct set_view_iterator;

template< class CoreIterator >
struct set_view_iterator_base
{
    typedef iterator_adaptor
    <
        set_view_iterator< CoreIterator >,
        CoreIterator,
        BOOST_DEDUCED_TYPENAME CoreIterator::value_type::above_view

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class CoreIterator >
struct set_view_iterator : public set_view_iterator_base<CoreIterator>::type
{
    typedef BOOST_DEDUCED_TYPENAME set_view_iterator_base<CoreIterator>::type base_;

    public:

    set_view_iterator() {}

    set_view_iterator(CoreIterator const& iter)
      : base_(iter) {}

    set_view_iterator(set_view_iterator const & iter)
      : base_(iter.base()) {}

    typename base_::reference dereference() const
    {
        return const_cast<
            BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )->get_view();
    }

    private:

    friend class iterator_core_access;

    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION

    // Serialization support

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    friend class ::boost::serialization::access;

    template< class Archive >
    void save(Archive & ar, const unsigned int) const
    {
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());
    }

    template< class Archive >
    void load(Archive & ar, const unsigned int)
    {
        CoreIterator iter;
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);
        this->base_reference() = iter;
    }

    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class CoreIterator > struct const_set_view_iterator;

template< class CoreIterator >
struct const_set_view_iterator_base
{
    typedef iterator_adaptor
    <
        const_set_view_iterator< CoreIterator >,
        CoreIterator,
        const BOOST_DEDUCED_TYPENAME CoreIterator::value_type::above_view

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/** \brief Const Set View Iterator adaptor from multi index to bimap.

See also set_view_iterator.
                                                                      **/

template< class CoreIterator >
struct const_set_view_iterator : public const_set_view_iterator_base<CoreIterator>::type
{
    typedef BOOST_DEDUCED_TYPENAME const_set_view_iterator_base<CoreIterator>::type base_;

    public:

    const_set_view_iterator() {}

    const_set_view_iterator(CoreIterator const& iter)
      : base_(iter) {}

    const_set_view_iterator(const_set_view_iterator const & iter)
      : base_(iter.base()) {}

    const_set_view_iterator(set_view_iterator<CoreIterator> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return this->base()->get_view();
    }

    private:

    friend class iterator_core_access;

    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION

    // Serialization support

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    friend class ::boost::serialization::access;

    template< class Archive >
    void save(Archive & ar, const unsigned int) const
    {
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());
    }

    template< class Archive >
    void load(Archive & ar, const unsigned int)
    {
        CoreIterator iter;
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);
        this->base_reference() = iter;
    }

    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};


} // namespace detail
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DETAIL_MAP_VIEW_ITERATOR_HPP



/* set_view_iterator.hpp
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
*/