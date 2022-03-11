// Copyright David Abrahams and Thomas Becker 2000-2006.
// Copyright Kohei Takahashi 2012-2014.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZIP_ITERATOR_TMB_07_13_2003_HPP_
# define BOOST_ZIP_ITERATOR_TMB_07_13_2003_HPP_

#include <stddef.h>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_adaptor.hpp> // for enable_if_convertible
#include <boost/iterator/iterator_categories.hpp>

#include <boost/iterator/minimum_category.hpp>

#include <utility> // for std::pair
#include <boost/fusion/adapted/boost_tuple.hpp> // for backward compatibility

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/convert.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>

namespace boost {
namespace iterators {

  // Zip iterator forward declaration for zip_iterator_base
  template<typename IteratorTuple>
  class zip_iterator;

  namespace detail
  {

    // Functors to be used with tuple algorithms
    //
    template<typename DiffType>
    class advance_iterator
    {
    public:
      advance_iterator(DiffType step) : m_step(step) {}

      template<typename Iterator>
      void operator()(Iterator& it) const
      { it += m_step; }

    private:
      DiffType m_step;
    };
    //
    struct increment_iterator
    {
      template<typename Iterator>
      void operator()(Iterator& it) const
      { ++it; }
    };
    //
    struct decrement_iterator
    {
      template<typename Iterator>
      void operator()(Iterator& it) const
      { --it; }
    };
    //
    struct dereference_iterator
    {
      template<typename>
      struct result;

      template<typename This, typename Iterator>
      struct result<This(Iterator)>
      {
        typedef typename
          remove_cv<typename remove_reference<Iterator>::type>::type
        iterator;

        typedef typename iterator_reference<iterator>::type type;
      };

      template<typename Iterator>
        typename result<dereference_iterator(Iterator)>::type
        operator()(Iterator const& it) const
      { return *it; }
    };

    // Metafunction to obtain the type of the tuple whose element types
    // are the reference types of an iterator tuple.
    //
    template<typename IteratorTuple>
    struct tuple_of_references
      : mpl::transform<
            IteratorTuple,
            iterator_reference<mpl::_1>
          >
    {
    };

    // Specialization for std::pair
    template<typename Iterator1, typename Iterator2>
    struct tuple_of_references<std::pair<Iterator1, Iterator2> >
    {
        typedef std::pair<
            typename iterator_reference<Iterator1>::type
          , typename iterator_reference<Iterator2>::type
        > type;
    };

    // Metafunction to obtain the minimal traversal tag in a tuple
    // of iterators.
    //
    template<typename IteratorTuple>
    struct minimum_traversal_category_in_iterator_tuple
    {
      typedef typename mpl::transform<
          IteratorTuple
        , pure_traversal_tag<iterator_traversal<> >
      >::type tuple_of_traversal_tags;

      typedef typename mpl::fold<
          tuple_of_traversal_tags
        , random_access_traversal_tag
        , minimum_category<>
      >::type type;
    };

    template<typename Iterator1, typename Iterator2>
    struct minimum_traversal_category_in_iterator_tuple<std::pair<Iterator1, Iterator2> >
    {
        typedef typename pure_traversal_tag<
            typename iterator_traversal<Iterator1>::type
        >::type iterator1_traversal;
        typedef typename pure_traversal_tag<
            typename iterator_traversal<Iterator2>::type
        >::type iterator2_traversal;

        typedef typename minimum_category<
            iterator1_traversal
          , typename minimum_category<
                iterator2_traversal
              , random_access_traversal_tag
            >::type
        >::type type;
    };

    ///////////////////////////////////////////////////////////////////
    //
    // Class zip_iterator_base
    //
    // Builds and exposes the iterator facade type from which the zip
    // iterator will be derived.
    //
    template<typename IteratorTuple>
    struct zip_iterator_base
    {
     private:
        // Reference type is the type of the tuple obtained from the
        // iterators' reference types.
        typedef typename
        detail::tuple_of_references<IteratorTuple>::type reference;

        // Value type is the same as reference type.
        typedef reference value_type;

        // Difference type is the first iterator's difference type
        typedef typename iterator_difference<
            typename mpl::at_c<IteratorTuple, 0>::type
        >::type difference_type;

        // Traversal catetgory is the minimum traversal category in the
        // iterator tuple.
        typedef typename
        detail::minimum_traversal_category_in_iterator_tuple<
            IteratorTuple
        >::type traversal_category;
     public:

        // The iterator facade type from which the zip iterator will
        // be derived.
        typedef iterator_facade<
            zip_iterator<IteratorTuple>,
            value_type,
            traversal_category,
            reference,
            difference_type
        > type;
    };

    template <>
    struct zip_iterator_base<int>
    {
        typedef int type;
    };

    template <typename reference>
    struct converter
    {
        template <typename Seq>
        static reference call(Seq seq)
        {
            typedef typename fusion::traits::tag_of<reference>::type tag;
            return fusion::convert<tag>(seq);
        }
    };

    template <typename Reference1, typename Reference2>
    struct converter<std::pair<Reference1, Reference2> >
    {
        typedef std::pair<Reference1, Reference2> reference;
        template <typename Seq>
        static reference call(Seq seq)
        {
            return reference(
                fusion::at_c<0>(seq)
              , fusion::at_c<1>(seq));
        }
    };
  }

  /////////////////////////////////////////////////////////////////////
  //
  // zip_iterator class definition
  //
  template<typename IteratorTuple>
  class zip_iterator :
    public detail::zip_iterator_base<IteratorTuple>::type
  {

   // Typedef super_t as our base class.
   typedef typename
     detail::zip_iterator_base<IteratorTuple>::type super_t;

   // iterator_core_access is the iterator's best friend.
   friend class iterator_core_access;

  public:

    // Construction
    // ============

    // Default constructor
    zip_iterator() { }

    // Constructor from iterator tuple
    zip_iterator(IteratorTuple iterator_tuple)
      : m_iterator_tuple(iterator_tuple)
    { }

    // Copy constructor
    template<typename OtherIteratorTuple>
    zip_iterator(
       const zip_iterator<OtherIteratorTuple>& other,
       typename enable_if_convertible<
         OtherIteratorTuple,
         IteratorTuple
         >::type* = 0
    ) : m_iterator_tuple(other.get_iterator_tuple())
    {}

    // Get method for the iterator tuple.
    const IteratorTuple& get_iterator_tuple() const
    { return m_iterator_tuple; }

  private:

    // Implementation of Iterator Operations
    // =====================================

    // Dereferencing returns a tuple built from the dereferenced
    // iterators in the iterator tuple.
    typename super_t::reference dereference() const
    {
        typedef typename super_t::reference reference;
        typedef detail::converter<reference> gen;
        return gen::call(fusion::transform(
          get_iterator_tuple(),
          detail::dereference_iterator()));
    }

    // Two zip iterators are equal if all iterators in the iterator
    // tuple are equal. NOTE: It should be possible to implement this
    // as
    //
    // return get_iterator_tuple() == other.get_iterator_tuple();
    //
    // but equality of tuples currently (7/2003) does not compile
    // under several compilers. No point in bringing in a bunch
    // of #ifdefs here.
    //
    template<typename OtherIteratorTuple>
    bool equal(const zip_iterator<OtherIteratorTuple>& other) const
    {
        return fusion::equal_to(
          get_iterator_tuple(),
          other.get_iterator_tuple());
    }

    // Advancing a zip iterator means to advance all iterators in the
    // iterator tuple.
    void advance(typename super_t::difference_type n)
    {
        fusion::for_each(
          m_iterator_tuple,
          detail::advance_iterator<BOOST_DEDUCED_TYPENAME super_t::difference_type>(n));
    }
    // Incrementing a zip iterator means to increment all iterators in
    // the iterator tuple.
    void increment()
    {
        fusion::for_each(
          m_iterator_tuple,
          detail::increment_iterator());
    }

    // Decrementing a zip iterator means to decrement all iterators in
    // the iterator tuple.
    void decrement()
    {
        fusion::for_each(
          m_iterator_tuple,
          detail::decrement_iterator());
    }

    // Distance is calculated using the first iterator in the tuple.
    template<typename OtherIteratorTuple>
      typename super_t::difference_type distance_to(
        const zip_iterator<OtherIteratorTuple>& other
        ) const
    {
        return fusion::at_c<0>(other.get_iterator_tuple()) -
            fusion::at_c<0>(this->get_iterator_tuple());
    }

    // Data Members
    // ============

    // The iterator tuple.
    IteratorTuple m_iterator_tuple;

  };

  // Make function for zip iterator
  //
  template<typename IteratorTuple>
  inline zip_iterator<IteratorTuple>
  make_zip_iterator(IteratorTuple t)
  { return zip_iterator<IteratorTuple>(t); }

} // namespace iterators

using iterators::zip_iterator;
using iterators::make_zip_iterator;

} // namespace boost

#endif

/* zip_iterator.hpp
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
*/