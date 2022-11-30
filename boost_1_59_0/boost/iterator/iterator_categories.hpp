// (C) Copyright Jeremy Siek 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_CATEGORIES_HPP
# define BOOST_ITERATOR_CATEGORIES_HPP

# include <boost/config.hpp>
# include <boost/iterator/detail/config_def.hpp>

# include <boost/detail/workaround.hpp>

# include <boost/mpl/eval_if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/mpl/placeholders.hpp>
# include <boost/mpl/aux_/lambda_support.hpp>

# include <boost/type_traits/is_convertible.hpp>

# include <boost/static_assert.hpp>

#include <iterator>

namespace boost {
namespace iterators {

//
// Traversal Categories
//

struct no_traversal_tag {};

struct incrementable_traversal_tag
  : no_traversal_tag
{
//     incrementable_traversal_tag() {}
//     incrementable_traversal_tag(std::output_iterator_tag const&) {};
};

struct single_pass_traversal_tag
  : incrementable_traversal_tag
{
//     single_pass_traversal_tag() {}
//     single_pass_traversal_tag(std::input_iterator_tag const&) {};
};

struct forward_traversal_tag
  : single_pass_traversal_tag
{
//     forward_traversal_tag() {}
//     forward_traversal_tag(std::forward_iterator_tag const&) {};
};

struct bidirectional_traversal_tag
  : forward_traversal_tag
{
//     bidirectional_traversal_tag() {};
//     bidirectional_traversal_tag(std::bidirectional_iterator_tag const&) {};
};

struct random_access_traversal_tag
  : bidirectional_traversal_tag
{
//     random_access_traversal_tag() {};
//     random_access_traversal_tag(std::random_access_iterator_tag const&) {};
};

namespace detail
{
  //
  // Convert a "strictly old-style" iterator category to a traversal
  // tag.  This is broken out into a separate metafunction to reduce
  // the cost of instantiating iterator_category_to_traversal, below,
  // for new-style types.
  //
  template <class Cat>
  struct old_category_to_traversal
    : mpl::eval_if<
          is_convertible<Cat,std::random_access_iterator_tag>
        , mpl::identity<random_access_traversal_tag>
        , mpl::eval_if<
              is_convertible<Cat,std::bidirectional_iterator_tag>
            , mpl::identity<bidirectional_traversal_tag>
            , mpl::eval_if<
                  is_convertible<Cat,std::forward_iterator_tag>
                , mpl::identity<forward_traversal_tag>
                , mpl::eval_if<
                      is_convertible<Cat,std::input_iterator_tag>
                    , mpl::identity<single_pass_traversal_tag>
                    , mpl::eval_if<
                          is_convertible<Cat,std::output_iterator_tag>
                        , mpl::identity<incrementable_traversal_tag>
                        , void
                      >
                  >
              >
          >
      >
  {};

} // namespace detail

//
// Convert an iterator category into a traversal tag
//
template <class Cat>
struct iterator_category_to_traversal
  : mpl::eval_if< // if already convertible to a traversal tag, we're done.
        is_convertible<Cat,incrementable_traversal_tag>
      , mpl::identity<Cat>
      , boost::iterators::detail::old_category_to_traversal<Cat>
    >
{};

// Trait to get an iterator's traversal category
template <class Iterator = mpl::_1>
struct iterator_traversal
  : iterator_category_to_traversal<
        typename std::iterator_traits<Iterator>::iterator_category
    >
{};

# ifdef BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT
// Hack because BOOST_MPL_AUX_LAMBDA_SUPPORT doesn't seem to work
// out well.  Instantiating the nested apply template also
// requires instantiating iterator_traits on the
// placeholder. Instead we just specialize it as a metafunction
// class.
template <>
struct iterator_traversal<mpl::_1>
{
    template <class T>
    struct apply : iterator_traversal<T>
    {};
};
template <>
struct iterator_traversal<mpl::_>
  : iterator_traversal<mpl::_1>
{};
# endif

//
// Convert an iterator traversal to one of the traversal tags.
//
template <class Traversal>
struct pure_traversal_tag
  : mpl::eval_if<
        is_convertible<Traversal,random_access_traversal_tag>
      , mpl::identity<random_access_traversal_tag>
      , mpl::eval_if<
            is_convertible<Traversal,bidirectional_traversal_tag>
          , mpl::identity<bidirectional_traversal_tag>
          , mpl::eval_if<
                is_convertible<Traversal,forward_traversal_tag>
              , mpl::identity<forward_traversal_tag>
              , mpl::eval_if<
                    is_convertible<Traversal,single_pass_traversal_tag>
                  , mpl::identity<single_pass_traversal_tag>
                  , mpl::eval_if<
                        is_convertible<Traversal,incrementable_traversal_tag>
                      , mpl::identity<incrementable_traversal_tag>
                      , void
                    >
                >
            >
        >
    >
{
};

//
// Trait to retrieve one of the iterator traversal tags from the iterator category or traversal.
//
template <class Iterator = mpl::_1>
struct pure_iterator_traversal
  : pure_traversal_tag<typename iterator_traversal<Iterator>::type>
{};

# ifdef BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT
template <>
struct pure_iterator_traversal<mpl::_1>
{
    template <class T>
    struct apply : pure_iterator_traversal<T>
    {};
};
template <>
struct pure_iterator_traversal<mpl::_>
  : pure_iterator_traversal<mpl::_1>
{};
# endif

} // namespace iterators

using iterators::no_traversal_tag;
using iterators::incrementable_traversal_tag;
using iterators::single_pass_traversal_tag;
using iterators::forward_traversal_tag;
using iterators::bidirectional_traversal_tag;
using iterators::random_access_traversal_tag;
using iterators::iterator_category_to_traversal;
using iterators::iterator_traversal;

// This import is needed for backward compatibility with Boost.Range:
// boost/range/detail/demote_iterator_traversal_tag.hpp
// It should be removed when that header is fixed.
namespace detail {
using iterators::pure_traversal_tag;
} // namespace detail

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_ITERATOR_CATEGORIES_HPP

/* iterator_categories.hpp
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
*/