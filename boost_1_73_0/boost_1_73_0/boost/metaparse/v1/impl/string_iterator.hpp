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
Tnl4/zC2vKShVltOtaWosYvOICCiEwNxkRDjVpSwBtsaepv1dLZY81q8W7u5VOSX0EbfNbXrZttQh6s6ancyx9n2hq0oj+DWn5UGWzAVut1BlWl4R5Tg60oZn8UfDmtltMqoXNUJs+Z1E5wvi8fmRBbBP4N67BfZHzxuiZyWfWhr3nt7Wm8Wy1ePPeY5NhS+5bd20aT4QsFi5wdYuyf+XxaRsedL4UJn+PAK3i3shP7v7nQnfGiF84vB/Ovf/gNQSwMECgAAAAgALWdKUsr+0INfAQAANQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzdVVAUAAbZIJGBNkl9LwzAUxd8D/Q6XyR5nEB+EEYqyVdyLq2vd0LesvbXBNBlJtlk/vbd/2KQtTXLzO+fkEhHQh0J6jJlQprL0+8b2bF3pY/acp2yT5Bs2m5UyyNleGelaJvh1i+ADdQMZuhO6mVclMuHwoFuqdljMQq080FspjVBYE9AET+hQFb4ni6aMe7fXdbb6TKj8b13wUZGMFloRPxoV/eQiErMqHC5ozEAY2WB/Eijt2WgrSzirUNtjAK9+EZSBzhR8cMp8EcAHAkRhm0aaspeccz59WWf5Kp1PSStdb3K+11LTx/Wxf/jd/QM5
*/