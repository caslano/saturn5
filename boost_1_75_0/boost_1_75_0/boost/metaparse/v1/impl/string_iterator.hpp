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
065CpMlOEoxjfbFcJLBdJhHxW763zjxIbxbc4CbbWWdeV8YGdoX8Kz7nFkvx77HHrEpSI56Ladlwqomw1Gl515sKZ1lB+QsQ0G5y58Ya3uD15Hp2/rwwoHjC89CnaagDYbKjXcrQdJlMig/MIaaS58gLh54XYlR89zotSTag10KqMUjjPXOIr82Y6tv8qXkPwxE8W+G2Em1P3NjL+yfImIgr50O/NCIWp0iEBfJFIdJcBVqrcNDyCadDws52KhFygE9uoH1Xqf+CUH7kEsRJHOEiHraLaK/FIoB2sXo2aH2phhui+Yn+RfWpRR7ziv74fJAYsc6CAOckHnp8+IsLIjj/xUHh0v/DEVms1yxU7g1AVKClionEohSId9CCka/N3Kf/hpRz8xgmwi/ZW5aNt7eATJvwvAMP/U240xY878THGuCC1G6tr/VrT3M8kkUko/8htBy0UqdQBEkMhs/gI/RXSrVx5/BaUGEeymBKB/X+6GY6GV07dQpxIbbVnRWVjIq9YyVmYpY5AjC0uSj23mSfUuQjqytffMdkgATzErisTWZjEG1IyPKYYzx6cf+Eo3oWmbmvKJuKcjpGD1Wm1QVvnaXj9w2RLdebOHvicUBL2WCAcRtx+ifBdRv9pRnTFZCQE3q2Ixsdi6+4aH6ay6BzFswfCNEk2XjPADFtrmUpzJom7ZsjDzZ9t6O/oU770zeIX/WqZbIQYCCD
*/