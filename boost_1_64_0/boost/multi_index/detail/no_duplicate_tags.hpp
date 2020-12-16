/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_NO_DUPLICATE_TAGS_HPP
#define BOOST_MULTI_INDEX_DETAIL_NO_DUPLICATE_TAGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/fold.hpp>
#include <boost/mpl/set/set0.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* no_duplicate_tags check at compile-time that a tag list
 * has no duplicate tags.
 * The algorithm deserves some explanation: tags
 * are sequentially inserted into a mpl::set if they were
 * not already present. Due to the magic of mpl::set
 * (mpl::has_key is contant time), this operation takes linear
 * time, and even MSVC++ 6.5 handles it gracefully (other obvious
 * solutions are quadratic.)
 */

struct duplicate_tag_mark{};

struct duplicate_tag_marker
{
  template <typename MplSet,typename Tag>
  struct apply
  {
    typedef mpl::s_item<
      typename mpl::if_<mpl::has_key<MplSet,Tag>,duplicate_tag_mark,Tag>::type,
      MplSet
    > type;
  };
};

template<typename TagList>
struct no_duplicate_tags
{
  typedef typename mpl::fold<
    TagList,
    mpl::set0<>,
    duplicate_tag_marker
  >::type aux;
 
  BOOST_STATIC_CONSTANT(
    bool,value=!(mpl::has_key<aux,duplicate_tag_mark>::value));
};

/* Variant for an index list: duplication is checked
 * across all the indices.
 */

struct duplicate_tag_list_marker
{
  template <typename MplSet,typename Index>
  struct apply:mpl::fold<
    BOOST_DEDUCED_TYPENAME Index::tag_list,
    MplSet,
    duplicate_tag_marker>
  {
  };
};

template<typename IndexList>
struct no_duplicate_tags_in_index_list
{
  typedef typename mpl::fold<
    IndexList,
    mpl::set0<>,
    duplicate_tag_list_marker
  >::type aux;
 
  BOOST_STATIC_CONSTANT(
    bool,value=!(mpl::has_key<aux,duplicate_tag_mark>::value));
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* no_duplicate_tags.hpp
DLNgOw3uFruD0kvJxUbG+RBpVBGdpTwImMFt3vcJ0jr4BzaqCh8v3fYqMvxTQTJ8hsn6rmoh513VSEO0uE7+zpXuxzW+sYlygrQT7MLflM/0mNEFDjzt8J4295D9CqtNjPew1PN1TlK+iHKLhPvMZKegOS/apE4LrjhnMnrFPOjExSlaF6x9jVkO9ENy5bKIp2DHUSYFaQBkQQVP3PbnP1dqLhPEKMRQpKVrDNpe9wSDsewYgIKJoUgIUi0w2KxuHA2e3aq5TBSUAF8ZcoCNeYHx3nbnE5Y0RGoruK7rxlOw81BTkG4HBluUjTzoT2jCJBEEBmuBwSp+DPiyurjGN/xvD1ABdIFKZHLyO22/InhGFIL/ecjlUfgiP/+RUqbbZ67xja/grxj/f1j8p4iwkwcP/Lfx888XUm2Pb/in9QE6DfxvI6LSD0ahpkuqWJSD/VE2/EOc9rF6PsZ7yWZ495nJugBVgX91YLTi5uJt0P6iEdxuSNDvP/8l9vfPViXVDO8+O/wxxr9KWHHSu7Nwnp4u6l38L+bnP8wVOWOGd7//rwN0Cmziv1U+pxNv+kb3ZogW2EJDnDzKL3Pzn9uZnnIYIwSgYPsIPg+YXKDbrVygPrEKOrAlSctAq0cYsEPQpd5bgEYCA3VINOHYXRZgMygWOffHnLzJS5gxYLxFZ4Z37w0l/04clWpYcucZT+neLOHcK2py8iVz819dMpEpd40Z3ZL/9wJ0G3wCQja8eqx/pebOL5qcONoU5KU4nHkN7My71xBhOiRzUzAY0PLY+0+w3n9ALEyDrzwFZ2RtzPuh6hL5B0w1aVzjm3Xg7Rj/iRb/QTHTJf/Bpezy31ngninbaxcKJp5QYuD4CJNkw9JpfyFneraY6sKgiR+D8RO40ni5xjf74bdiMpBsyUA3McXFP73Czr+MeGO0BDC+pQPeCJhYgRTZ0KPnmcM7O6XXbFGinSe+0Qv+c9n1gKFh6YLXY3KQaslB9y5ysMETHJghcO8JXovxn2bx36ML/+WvesA/06GhGX6Ha972FAvxWw7ulhd9yXlGgAdkVgPD3Lbg0gAdAZ9YhvzOeSw5ont7iXmp2A84OeC57SH5Yczz24WCweC5AN0PDHzye8r7dY/gzYvRzr2iNNiEI73AoIwpntQiYOedeSRAWdADmbLhppMmItdxb9G6G/LO7KRzrbS8zWwTRhqYvUOGgIUBzQ/QGuwNVG6mwxIurNe9fcSGJEgE9oUd3LpQfviK6VgE7HzPD8TsAr+IjyHsK0a78g8VccYQ6kdkzNRmEbDv2swKUAP0QUB+/zziJqyE/cTabPiJHD+pF/qA1VNoCNixFDMC1BtyEJQNJ19Z9aTu3Vk4tRDSkqATj/AAg9B4plBKi4DtL7w0QJshB9ny+43tq+7RvbuIonRzB78Tp8IPmc+Q5SuqCXMuCxg/Pp5qSoBugQx0U7ZB7pW4c7yraIQMlCMv25CPuPkvaZTxTiWM+2SLglkTGgOm9p6KJ6hesHg63rzId87PE3XerRbuOIqIPNOKsCLgjL8D9vGALvbxYm77OFJSG2LcH2F4O5/vRQG6Ge+/h2w4aMK2P3TvbmJwEuaA/Par83POOybOA44oUSFPvBtFm44dVxMN0BDg0VM2LNh2dZHmeHfh1EYphE4IrmDXCbUhxv0ihrfto3K5JoD/XrJh/jX3XqV7Bwonu28j7hdM9YJ/xv0ihrdt5PKY31DlXvvw+Qmn6949RF5cjG0nFDMHc8+HmipWdYjh43MTjYvx39vym+4pRkP+cyD/G/jfP6/fFONbMRRlAfoG/PeRDT+MHeXXHO4lGp17VogtHfMxO/8yEporrNIe38j/aQE=
*/