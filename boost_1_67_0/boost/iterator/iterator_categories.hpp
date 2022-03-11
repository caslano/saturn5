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