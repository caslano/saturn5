// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef FACADE_ITERATOR_CATEGORY_DWA20031118_HPP
# define FACADE_ITERATOR_CATEGORY_DWA20031118_HPP

# include <boost/core/use_default.hpp>

# include <boost/iterator/iterator_categories.hpp>

# include <boost/mpl/or.hpp>  // used in iterator_tag inheritance logic
# include <boost/mpl/and.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/eval_if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/mpl/assert.hpp>

# include <boost/type_traits/is_same.hpp>
# include <boost/type_traits/is_const.hpp>
# include <boost/type_traits/is_reference.hpp>
# include <boost/type_traits/is_convertible.hpp>

# include <boost/type_traits/is_same.hpp>

# include <boost/iterator/detail/config_def.hpp> // try to keep this last

# ifdef BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY
#  include <boost/detail/indirect_traits.hpp>
# endif

//
// iterator_category deduction for iterator_facade
//

namespace boost {
namespace iterators {

using boost::use_default;

namespace detail {

struct input_output_iterator_tag
  : std::input_iterator_tag
{
    // Using inheritance for only input_iterator_tag helps to avoid
    // ambiguities when a stdlib implementation dispatches on a
    // function which is overloaded on both input_iterator_tag and
    // output_iterator_tag, as STLPort does, in its __valid_range
    // function.  I claim it's better to avoid the ambiguity in these
    // cases.
    operator std::output_iterator_tag() const
    {
        return std::output_iterator_tag();
    }
};

//
// True iff the user has explicitly disabled writability of this
// iterator.  Pass the iterator_facade's Value parameter and its
// nested ::reference type.
//
template <class ValueParam, class Reference>
struct iterator_writability_disabled
# ifdef BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY // Adding Thomas' logic?
  : mpl::or_<
        is_const<Reference>
      , boost::detail::indirect_traits::is_reference_to_const<Reference>
      , is_const<ValueParam>
    >
# else
  : is_const<ValueParam>
# endif
{};


//
// Convert an iterator_facade's traversal category, Value parameter,
// and ::reference type to an appropriate old-style category.
//
// Due to changeset 21683, this now never results in a category convertible
// to output_iterator_tag.
//
// Change at: https://svn.boost.org/trac/boost/changeset/21683
template <class Traversal, class ValueParam, class Reference>
struct iterator_facade_default_category
  : mpl::eval_if<
        mpl::and_<
            is_reference<Reference>
          , is_convertible<Traversal,forward_traversal_tag>
        >
      , mpl::eval_if<
            is_convertible<Traversal,random_access_traversal_tag>
          , mpl::identity<std::random_access_iterator_tag>
          , mpl::if_<
                is_convertible<Traversal,bidirectional_traversal_tag>
              , std::bidirectional_iterator_tag
              , std::forward_iterator_tag
            >
        >
      , typename mpl::eval_if<
            mpl::and_<
                is_convertible<Traversal, single_pass_traversal_tag>

                // check for readability
              , is_convertible<Reference, ValueParam>
            >
          , mpl::identity<std::input_iterator_tag>
          , mpl::identity<Traversal>
        >
    >
{
};

// True iff T is convertible to an old-style iterator category.
template <class T>
struct is_iterator_category
  : mpl::or_<
        is_convertible<T,std::input_iterator_tag>
      , is_convertible<T,std::output_iterator_tag>
    >
{
};

template <class T>
struct is_iterator_traversal
  : is_convertible<T,incrementable_traversal_tag>
{};

//
// A composite iterator_category tag convertible to Category (a pure
// old-style category) and Traversal (a pure traversal tag).
// Traversal must be a strict increase of the traversal power given by
// Category.
//
template <class Category, class Traversal>
struct iterator_category_with_traversal
  : Category, Traversal
{
    // Make sure this isn't used to build any categories where
    // convertibility to Traversal is redundant.  Should just use the
    // Category element in that case.
    BOOST_MPL_ASSERT_NOT((
        is_convertible<
              typename iterator_category_to_traversal<Category>::type
            , Traversal
          >));

    BOOST_MPL_ASSERT((is_iterator_category<Category>));
    BOOST_MPL_ASSERT_NOT((is_iterator_category<Traversal>));
    BOOST_MPL_ASSERT_NOT((is_iterator_traversal<Category>));
#  if !BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
    BOOST_MPL_ASSERT((is_iterator_traversal<Traversal>));
#  endif
};

// Computes an iterator_category tag whose traversal is Traversal and
// which is appropriate for an iterator
template <class Traversal, class ValueParam, class Reference>
struct facade_iterator_category_impl
{
    BOOST_MPL_ASSERT_NOT((is_iterator_category<Traversal>));

    typedef typename iterator_facade_default_category<
        Traversal,ValueParam,Reference
    >::type category;

    typedef typename mpl::if_<
        is_same<
            Traversal
          , typename iterator_category_to_traversal<category>::type
        >
      , category
      , iterator_category_with_traversal<category,Traversal>
    >::type type;
};

//
// Compute an iterator_category for iterator_facade
//
template <class CategoryOrTraversal, class ValueParam, class Reference>
struct facade_iterator_category
  : mpl::eval_if<
        is_iterator_category<CategoryOrTraversal>
      , mpl::identity<CategoryOrTraversal> // old-style categories are fine as-is
      , facade_iterator_category_impl<CategoryOrTraversal,ValueParam,Reference>
    >
{
};

}}} // namespace boost::iterators::detail

# include <boost/iterator/detail/config_undef.hpp>

#endif // FACADE_ITERATOR_CATEGORY_DWA20031118_HPP

/* facade_iterator_category.hpp
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
*/