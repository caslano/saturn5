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
wIeAO4BTgb8HTgPuB24C/gP4BPAb4K+A3wJ/DYyBHJ8CxgOfBQ4CvgBMA74IPA/4KnAW8HVgNvAN4ELgeFVO4LnAZYwvCXItlysvUmxgUoAlvvOfNnOfK0FbAs13+s91yjznaOS9dZx7nrMWaGfjchAUeK6T85w2c5xDbgg8t5k0HmFQpTGvmTbef25zDsq30mdeM2Vp/XnN8vGB12lVIP36vNCcZugIHaEjdAQ6IkCX/nTjf/WpvGxORXlZ7z4D1TTAj54DuAcvMcM4Ru5LZ32TMYDoDBwMzMNL09anTR/n7otjFkCK5PEzn6PHym4b/m0Y33wq6bqGa7+fm902/c2sjg6P38g9wjMK14vWY+ypz6q4BzD6S9Z+Zr+WOFsfmyyfQ/sbxZhukbnv8B/k/Nn+/uns0xaVKB7UYQvqMFXKvCXsGLhjWA+XlCVZ+7kdKjznhr0Iv4l9HMusZxzDWG6MKJ+Rsbi256+W8MWOAdYe8nji+tv6wzPLlyS+9ooXllPGW1G+z+V8p/BElu13Em4U1sZyWWdZMx3rHHP0frGFUu41umxrpNzzed4j4ya+Mrf1E2+Wa6GPb/JY4J/k/ENhLeD74VtHc71mo0ryLMdY32m3lzLy9fVVD0VT+bJ+SVLmXY4zra+tcY7rJY8EI48Enzzmpah2Ll+clz0fPKOQB/fHl3ziJK41444zrgPiEhg3UuJexA19H95ZJ1txjl/qfCJAk9V5/IpHXEvGfSdxM1G2c4W3FePvlvhezN89kHDr1wOOwRjBJDtOs5Y52lmJkpdD0lwgurEJ+Z8F30bjgWNa9F84wtpcTzedjHdYryL+QYmfG7bKet2h5LMXcU29cxhaH7Il78utllpOZTml2eU58yjvO4BvCs+fwXO7VWP1QVrEI6bmWa4rYb3VcYdct1M9+WzabPDxntsicSM1nxP0usSlks+h+Kh/EeRzWE4d11jafTvqJfpHn8QYK2ndTpRyR2l/7phdkXPhSu/lXCvki7Dq2SQ82momcfDI6NUZ8Tds6shXwhtZr12/Z5xq13jWcaDU54CjLUaA+60z0eO9Iu3aivU9S51HiydB/nus4ZJfAs/Fu+vN/FALrSc1YVMwsopxrLXecNSJzrWiXDy60N9aENZBdOEl0QVP/HTsUKv0pIejK9cN2cpO6umkjH1lF4ZfN8u59igvwvp+PtsKR5ya90q39a2NghrzXnGWQ8/v5uj5Xfru1P7/0Yczzqnj2DdzTwb0h4iT/lDvCY761PPRnaDtvtCPME7dD/PkutLG4h90u44z74EWIqdLvby9PX5DE0Wu2HOYc1UrfMIvP1M//E/2zgTA5mqP4///nWGGGcwwM8YYjDVbDImEnixZUlGWLGGMYSZmMcZashVTiEIpiixF4k2oPPV6QkVR2kSpJJX2/b2213vf87vfe+bce89lvLze67259feZs/7P/5zf+Z3/Of+zjNjhb95XbDbOwz7zsZRsGbPaeWmta8ukDI4ZtqN2xTd33Pf5mc+HOltjTWfr/GxZW+NSl/OdJJX7vo11ufedMS/qPLA296q8h2Mw9cEh3LNyLPeszOUam8VcY7MNPA/cB7bludTtwQTcowPYCLyIYysdwZZgN67N6Q52B3uAN9F9HngxeCd4NbgSHAiuAweDO8FB6j40vwYOAY+Bw8Fw5FMaWA5MB1PAFWBdUD1XSzAX7AXOBheCc8C14FxwA3gL+Aw4HzxI8yGa3wYXgB/Q/kvwNjAqzLuX4oXgPdwDcXtGhJ4/trdPeNB5yvu7ljntmcqvItyiD8NLfLbywdIxhtJf6a/09zv9hePK+Xf3/yflp+WhD3425gEkYd+9y+oj3XI=
*/