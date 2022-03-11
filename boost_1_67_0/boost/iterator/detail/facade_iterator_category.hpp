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