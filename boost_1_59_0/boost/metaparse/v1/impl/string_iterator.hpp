#ifndef BOOST_METAPARSE_V1_IMPL_STRING_ITERATOR_HPP
#define BOOST_METAPARSE_V1_IMPL_STRING_ITERATOR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/string_iterator_tag.hpp>
#include <boost/metaparse/v1/impl/at_c.hpp>


#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        // string_iterator
        template <class S, int N>
        struct string_iterator
        {
          typedef string_iterator type;
          typedef string_iterator_tag tag;
          typedef boost::mpl::random_access_iterator_tag category;
        };

        // advance_c

        template <class S, int N>
        struct advance_c;

        template <class S, int N, int P>
        struct advance_c<string_iterator<S, N>, P> :
          string_iterator<S, N + P>
        {};

        // distance

        template <class A, class B>
        struct distance;

        template <class S, int A, int B>
        struct distance<string_iterator<S, A>, string_iterator<S, B> > :
          boost::mpl::int_<B - A>
        {};
      }
    }
  }
}

namespace boost
{
  namespace mpl
  {
    // advance
    template <class S>
    struct advance_impl;

    template <>
    struct advance_impl<boost::metaparse::v1::impl::string_iterator_tag>
    {
      typedef advance_impl type;

      template <class S, class N>
      struct apply :
        boost::metaparse::v1::impl::advance_c<
          typename S::type, N::type::value
        >
      {};
    };

    // distance
    template <class S>
    struct distance_impl;

    template <>
    struct distance_impl<boost::metaparse::v1::impl::string_iterator_tag>
    {
      typedef distance_impl type;

      template <class A, class B>
      struct apply :
        boost::metaparse::v1::impl::distance<
          typename A::type,
          typename B::type
        >
      {};
    };

    // next
    template <class S>
    struct next;

    template <class S, int N>
    struct next<boost::metaparse::v1::impl::string_iterator<S, N> > :
      boost::metaparse::v1::impl::string_iterator<S, N + 1>
    {};

    // prior
    template <class S>
    struct prior;

    template <class S, int N>
    struct prior<boost::metaparse::v1::impl::string_iterator<S, N> > :
      boost::metaparse::v1::impl::string_iterator<S, N - 1>
    {};

    // deref
    template <class S>
    struct deref;

    template <class S, int N>
    struct deref<boost::metaparse::v1::impl::string_iterator<S, N> > :
      boost::metaparse::v1::impl::at_c<S, N>
    {};

    // equal_to
    template <class A, class B>
    struct equal_to_impl;

    template <>
    struct equal_to_impl<
      boost::metaparse::v1::impl::string_iterator_tag,
      boost::metaparse::v1::impl::string_iterator_tag
    >
    {
      typedef equal_to_impl type;

      template <class A, class B>
      struct apply : is_same<typename A::type, typename B::type> {};
    };

    template <class T>
    struct equal_to_impl<boost::metaparse::v1::impl::string_iterator_tag, T>
    {
      typedef equal_to_impl type;
      
      template <class, class>
      struct apply : false_ {};
    };
    
    template <class T>
    struct equal_to_impl<T, boost::metaparse::v1::impl::string_iterator_tag> :
      equal_to_impl<boost::metaparse::v1::impl::string_iterator_tag, T>
    {};
  }
}

#endif


/* string_iterator.hpp
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
*/