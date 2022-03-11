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