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