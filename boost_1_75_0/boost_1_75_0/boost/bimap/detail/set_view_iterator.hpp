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
hQdem/BeX0fksVFPwFgnunxRFfy0TsZMyla4Ez2mgs2EEpgJI1nWBJxWEW0Z3N1ppkS0Tfd16Or0xrWjWDWu8E3Oog7Rw31dE6qjnHJEO6ccZXAWRUU75TvaWwBrPzvl4XXQv6FFEVuquzjlwXWsxxXp4CH8NosrYaPyF9uQOL2RdZoGxG87McFs8JdJ3k0Wp7csxnsx3Pr0CrQsxxOfrpK3tzoJ6QyI3sCmcnUul7CvOBFpWGZUtShbfwQyJR/yjAgy9HdD5AqlYx+9Hku1/zzb1Nz7/G5h/3kw5Nx7tc8/s/98vFlz768fguferQma34Kgu2ysP+/Uqf2JT4fou0qafFxEIHEk/ZIOlwLwdga/9+jo1yfVUwvE9qRdPuRkzNyZcI204WK491djzj2+iG4vJ2zcXSeNqYN7m7E4RyPqRExAuJXLAwLmTAItQCze20qdDKqzqSbfk/5q08w0331GvbvWn8ebDSl/zHgb3ICG24u6ASCICPB/zbs7Mfhyj76C91kFcnn1VrijdaXwP018KBNcjcinpLxTRCSmBWc4Phx15AXUcdT70AGD96EaWKDngP6+yLHL5fvsKAbg9CytsfsHR5c5ljCQHUslOUcEAxtiqTbDNQw5FRYcz59JtdUPSvKt4DWSx4zESAzLsVl8LfkyK/i9Wrgq6J1RYfAkSL5bE5Ws6+AO/QHWcqkk74Lbn8ptYzBUo/B5
*/