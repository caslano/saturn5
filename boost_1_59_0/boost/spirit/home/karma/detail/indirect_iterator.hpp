//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DETAIL_INDIRECT_ITERATOR_HPP
#define BOOST_SPIRIT_KARMA_DETAIL_INDIRECT_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator> // for std::iterator_traits

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma { namespace detail
{
    ///////////////////////////////////////////////////////////////////////
    // This is a wrapper for any iterator allowing to pass a reference of it
    // to the components of the sequence
    template <typename Iterator>
    class indirect_iterator
      : public boost::iterator_facade<
            indirect_iterator<Iterator>
          , typename std::iterator_traits<Iterator>::value_type
          , boost::forward_traversal_tag
          , typename std::iterator_traits<Iterator>::reference>
    {
        typedef typename std::iterator_traits<Iterator>::value_type
            base_value_type;
        typedef typename std::iterator_traits<Iterator>::reference
            base_reference_type;

        typedef boost::iterator_facade<
            indirect_iterator<Iterator>, base_value_type
          , boost::forward_traversal_tag, base_reference_type
        > base_type;

    public:
        indirect_iterator(Iterator& iter)
          : iter_(&iter)
        {}
        indirect_iterator(indirect_iterator const& iter)
          : iter_(iter.iter_)
        {}

    private:
        friend class boost::iterator_core_access;

        void increment()
        {
            ++*iter_;
        }

        bool equal(indirect_iterator const& other) const
        {
            return *iter_ == *other.iter_;
        }

        base_reference_type dereference() const
        {
            return **iter_;
        }

    private:
        Iterator* iter_;
    };
}}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    template <typename Iterator>
    struct make_indirect_iterator
    {
        typedef karma::detail::indirect_iterator<Iterator> type;
    };

    template <typename Iterator>
    struct make_indirect_iterator<karma::detail::indirect_iterator<Iterator> >
    {
        typedef karma::detail::indirect_iterator<Iterator> type;
    };

    template <>
    struct make_indirect_iterator<unused_type const*>
    {
        typedef unused_type const* type;
    };

    template <typename Iterator>
    struct make_indirect_iterator<Iterator const&>
      : make_indirect_iterator<Iterator const>
    {};
}}}

#endif

/* indirect_iterator.hpp
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
*/