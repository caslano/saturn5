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