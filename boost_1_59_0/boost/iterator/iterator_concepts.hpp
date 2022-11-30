// (C) Copyright Jeremy Siek 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_CONCEPTS_HPP
#define BOOST_ITERATOR_CONCEPTS_HPP

#include <boost/concept_check.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>

#include <boost/static_assert.hpp>

// Use boost/limits to work around missing limits headers on some compilers
#include <boost/limits.hpp>
#include <boost/config.hpp>

#include <algorithm>
#include <iterator>

#include <boost/concept/detail/concept_def.hpp>

namespace boost_concepts
{
  // Used a different namespace here (instead of "boost") so that the
  // concept descriptions do not take for granted the names in
  // namespace boost.

  //===========================================================================
  // Iterator Access Concepts

  BOOST_concept(ReadableIterator,(Iterator))
    : boost::Assignable<Iterator>
    , boost::CopyConstructible<Iterator>

  {
      typedef BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::value_type value_type;
      typedef BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::reference reference;

      BOOST_CONCEPT_USAGE(ReadableIterator)
      {

          value_type v = *i;
          boost::ignore_unused_variable_warning(v);
      }
  private:
      Iterator i;
  };

  template <
      typename Iterator
    , typename ValueType = BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::value_type
  >
  struct WritableIterator
    : boost::CopyConstructible<Iterator>
  {
      BOOST_CONCEPT_USAGE(WritableIterator)
      {
          *i = v;
      }
  private:
      ValueType v;
      Iterator i;
  };

  template <
      typename Iterator
    , typename ValueType = BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::value_type
  >
  struct WritableIteratorConcept : WritableIterator<Iterator,ValueType> {};

  BOOST_concept(SwappableIterator,(Iterator))
  {
      BOOST_CONCEPT_USAGE(SwappableIterator)
      {
          std::iter_swap(i1, i2);
      }
  private:
      Iterator i1;
      Iterator i2;
  };

  BOOST_concept(LvalueIterator,(Iterator))
  {
      typedef typename std::iterator_traits<Iterator>::value_type value_type;

      BOOST_CONCEPT_USAGE(LvalueIterator)
      {
        value_type& r = const_cast<value_type&>(*i);
        boost::ignore_unused_variable_warning(r);
      }
  private:
      Iterator i;
  };


  //===========================================================================
  // Iterator Traversal Concepts

  BOOST_concept(IncrementableIterator,(Iterator))
    : boost::Assignable<Iterator>
    , boost::CopyConstructible<Iterator>
  {
      typedef typename boost::iterator_traversal<Iterator>::type traversal_category;

      BOOST_CONCEPT_ASSERT((
        boost::Convertible<
            traversal_category
          , boost::incrementable_traversal_tag
        >));

      BOOST_CONCEPT_USAGE(IncrementableIterator)
      {
          ++i;
          (void)i++;
      }
  private:
      Iterator i;
  };

  BOOST_concept(SinglePassIterator,(Iterator))
    : IncrementableIterator<Iterator>
    , boost::EqualityComparable<Iterator>

  {
      BOOST_CONCEPT_ASSERT((
          boost::Convertible<
             BOOST_DEDUCED_TYPENAME SinglePassIterator::traversal_category
           , boost::single_pass_traversal_tag
          > ));
  };

  BOOST_concept(ForwardTraversal,(Iterator))
    : SinglePassIterator<Iterator>
    , boost::DefaultConstructible<Iterator>
  {
      typedef typename std::iterator_traits<Iterator>::difference_type difference_type;

      BOOST_MPL_ASSERT((boost::is_integral<difference_type>));
      BOOST_MPL_ASSERT_RELATION(std::numeric_limits<difference_type>::is_signed, ==, true);

      BOOST_CONCEPT_ASSERT((
          boost::Convertible<
             BOOST_DEDUCED_TYPENAME ForwardTraversal::traversal_category
           , boost::forward_traversal_tag
          > ));
  };

  BOOST_concept(BidirectionalTraversal,(Iterator))
    : ForwardTraversal<Iterator>
  {
      BOOST_CONCEPT_ASSERT((
          boost::Convertible<
             BOOST_DEDUCED_TYPENAME BidirectionalTraversal::traversal_category
           , boost::bidirectional_traversal_tag
          > ));

      BOOST_CONCEPT_USAGE(BidirectionalTraversal)
      {
          --i;
          (void)i--;
      }
   private:
      Iterator i;
  };

  BOOST_concept(RandomAccessTraversal,(Iterator))
    : BidirectionalTraversal<Iterator>
  {
      BOOST_CONCEPT_ASSERT((
          boost::Convertible<
             BOOST_DEDUCED_TYPENAME RandomAccessTraversal::traversal_category
           , boost::random_access_traversal_tag
          > ));

      BOOST_CONCEPT_USAGE(RandomAccessTraversal)
      {
          i += n;
          i = i + n;
          i = n + i;
          i -= n;
          i = i - n;
          n = i - j;
      }

   private:
      typename BidirectionalTraversal<Iterator>::difference_type n;
      Iterator i, j;
  };

  //===========================================================================
  // Iterator Interoperability

  namespace detail
  {
    template <typename Iterator1, typename Iterator2>
    void interop_single_pass_constraints(Iterator1 const& i1, Iterator2 const& i2)
    {
        bool b;
        b = i1 == i2;
        b = i1 != i2;

        b = i2 == i1;
        b = i2 != i1;
        boost::ignore_unused_variable_warning(b);
    }

    template <typename Iterator1, typename Iterator2>
    void interop_rand_access_constraints(
        Iterator1 const& i1, Iterator2 const& i2,
        boost::random_access_traversal_tag, boost::random_access_traversal_tag)
    {
        bool b;
        typename std::iterator_traits<Iterator2>::difference_type n;
        b = i1 <  i2;
        b = i1 <= i2;
        b = i1 >  i2;
        b = i1 >= i2;
        n = i1 -  i2;

        b = i2 <  i1;
        b = i2 <= i1;
        b = i2 >  i1;
        b = i2 >= i1;
        n = i2 -  i1;
        boost::ignore_unused_variable_warning(b);
        boost::ignore_unused_variable_warning(n);
    }

    template <typename Iterator1, typename Iterator2>
    void interop_rand_access_constraints(
        Iterator1 const&, Iterator2 const&,
        boost::single_pass_traversal_tag, boost::single_pass_traversal_tag)
    { }

  } // namespace detail

  BOOST_concept(InteroperableIterator,(Iterator)(ConstIterator))
  {
   private:
      typedef typename boost::iterators::pure_iterator_traversal<Iterator>::type traversal_category;
      typedef typename boost::iterators::pure_iterator_traversal<ConstIterator>::type const_traversal_category;

   public:
      BOOST_CONCEPT_ASSERT((SinglePassIterator<Iterator>));
      BOOST_CONCEPT_ASSERT((SinglePassIterator<ConstIterator>));

      BOOST_CONCEPT_USAGE(InteroperableIterator)
      {
          detail::interop_single_pass_constraints(i, ci);
          detail::interop_rand_access_constraints(i, ci, traversal_category(), const_traversal_category());

          ci = i;
      }

   private:
      Iterator      i;
      ConstIterator ci;
  };

} // namespace boost_concepts

#include <boost/concept/detail/concept_undef.hpp>

#endif // BOOST_ITERATOR_CONCEPTS_HPP

/* iterator_concepts.hpp
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
*/