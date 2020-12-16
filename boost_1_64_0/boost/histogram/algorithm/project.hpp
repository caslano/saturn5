// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ALGORITHM_PROJECT_HPP
#define BOOST_HISTOGRAM_ALGORITHM_PROJECT_HPP

#include <algorithm>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/make_default.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/histogram.hpp>
#include <boost/histogram/indexed.hpp>
#include <boost/histogram/unsafe_access.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/set.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace boost {
namespace histogram {
namespace algorithm {

/**
  Returns a lower-dimensional histogram, summing over removed axes.

  Arguments are the source histogram and compile-time numbers, the remaining indices of
  the axes. Returns a new histogram which only contains the subset of axes. The source
  histogram is summed over the removed axes.
*/
template <class A, class S, unsigned N, typename... Ns>
auto project(const histogram<A, S>& h, std::integral_constant<unsigned, N>, Ns...) {
  using LN = mp11::mp_list<std::integral_constant<unsigned, N>, Ns...>;
  static_assert(mp11::mp_is_set<LN>::value, "indices must be unique");

  const auto& old_axes = unsafe_access::axes(h);
  auto axes = detail::static_if<detail::is_tuple<A>>(
      [&](const auto& old_axes) {
        return std::make_tuple(std::get<N>(old_axes), std::get<Ns::value>(old_axes)...);
      },
      [&](const auto& old_axes) {
        return std::decay_t<decltype(old_axes)>({old_axes[N], old_axes[Ns::value]...});
      },
      old_axes);

  const auto& old_storage = unsafe_access::storage(h);
  using A2 = decltype(axes);
  auto result = histogram<A2, S>(std::move(axes), detail::make_default(old_storage));
  auto idx = detail::make_stack_buffer<int>(unsafe_access::axes(result));
  for (auto&& x : indexed(h, coverage::all)) {
    auto i = idx.begin();
    mp11::mp_for_each<LN>([&i, &x](auto J) { *i++ = x.index(J); });
    result.at(idx) += *x;
  }
  return result;
}

/**
  Returns a lower-dimensional histogram, summing over removed axes.

  This version accepts a source histogram and an iterable range containing the remaining
  indices.
*/
template <class A, class S, class Iterable, class = detail::requires_iterable<Iterable>>
auto project(const histogram<A, S>& h, const Iterable& c) {
  using namespace boost::mp11;
  const auto& old_axes = unsafe_access::axes(h);

  // axes is always std::vector<...>, even if A is tuple
  auto axes = detail::make_empty_dynamic_axes(old_axes);
  axes.reserve(c.size());
  auto seen = detail::make_stack_buffer<bool>(old_axes, false);
  for (auto d : c) {
    if (static_cast<unsigned>(d) >= h.rank())
      BOOST_THROW_EXCEPTION(std::invalid_argument("invalid axis index"));
    if (seen[d]) BOOST_THROW_EXCEPTION(std::invalid_argument("indices are not unique"));
    seen[d] = true;
    axes.emplace_back(detail::axis_get(old_axes, d));
  }

  const auto& old_storage = unsafe_access::storage(h);
  auto result =
      histogram<decltype(axes), S>(std::move(axes), detail::make_default(old_storage));
  auto idx = detail::make_stack_buffer<int>(unsafe_access::axes(result));
  for (auto&& x : indexed(h, coverage::all)) {
    auto i = idx.begin();
    for (auto d : c) *i++ = x.index(d);
    result.at(idx) += *x;
  }

  return result;
}

} // namespace algorithm
} // namespace histogram
} // namespace boost

#endif

/* project.hpp
gSszIxfWLkJCXpHNUXUpfgQuN/v704ROTkRA3kmj+ziNVtpxmjdrsxRyQL3JDLPfgRO7+ZSJSf5uU4wo/6HmrvDi5aj+Gs6MjeQ5KraTPxuqdzIQTnBsfoHugc1FyaSCIP7ZcCrbUf0bskuDBfHaKwNhq2PzL5DF8fjewFvrHVX0eFXgjOK4LYgfBY1F/JwYFQRlhf9n7UzdAVtwVorj8YSC5O0UjwD5/xYw7ckrSl1dDpMoS32zFe+m4FewKEWKqtA3vXddhzK65RWlODZnn6MB2DAxrbIgr41yfTDAEDJVJyNTRSPPOlAK23tepc2x+aOP42JHWvGT5u+2fBSAR7+qDLszanX+9FhkHT9K+BfdJ//F3CfuLaqJBec8JGqzUjTyuvxSqWXXHMK5eVxbGhDHPQwjqV6K7nB9ZhRptCY6SQYua+XoZCrUXUag0IWNVhpt0yVUzEZppgERJoZ5GBn7XlpE1nYKozJYo7eH2J2XYnhu/PubIfbPZCf63/qR/MWbWDlujXnV9ySfRzKnSWTNEpmYZ7Af010KF2LTECt+M5wFY9mwbA+aQeO7SvyARTbjVucss93eAiaw3jTRfVTEHMtRFUANsr7GolTTnWbYsB+FTEl8+3KWYaOHbLBVZMc/ROS6gCtrTmwsslER7yydhttESZbcm4uY7edL9WxARyP6ypAYct+lRxS5b3Eyue+ckV7Uh57fHs6W+TrRfm4iQvjRSrRnZRpEm4XqBtXGBR6zQbLfregszZb21oOGsr8cPheQ1BKMIsuv5W2Z4RdHyChupLPpc7lbt5cVPYnlh5D8wwyGPmb+nNnXO3Au7L/CaysTrxqqEv8rzeNbF+pqp3gYx5ZyQoYRhAwP8KDSJQ/kT2pMZFJxorkLK6Qo/5sXtkJ7tSLudRjQxsg3OXRoY+oLUcWihRWf8X5Z+/gdhi4AMzO0n9xA6dSVkBHB8zx2i2fg+avop4fGlU7j2j40FsmTKmKx/JMuILh1qzu7uHFwqxOYGyNsguQQ1N8DDBEWYWSEcKUTnydZBKBvdxzD7u6hz0crGt+aHoPGl3ePQuNLu39KNCZbrq1Yb3S1bdp2jQzjSqLv2ZfJC+BMLOjOdUr0VexEvordbN1kxbY5gF09cD+gWFsFCXHvvrqEGMchbFhGMVjG4o42SjSr+2k/foGciibK37Ue7VzUpXB/l+LcRP9h3AL3D1Sb4qr/Y6ph+Yr6y71JdGMbl8pd7uJwr3R4D6erWcQjC97N/0CbciJ2/IXRXUnahOvm1JXmIrpqPkXbGe1uFS85WhqB4hi0KVJkgIaIBukpqyQu0f/Wxo+3oyFfqaqYjd6u4N52lb2lofRxq09RQoJ4XmEKIF8fgnPfvyBaT1TEbxUusVD6lMA/X4I65xM/5L9TjJxIsoFpGW3FQcb7z4PbvP9M5GkuXedazAq6ZQQpMeHgMXlQHwb9QjG0wWViwGCD4OR4J6i7aOhrvFcDYHt76y4X3H145bJuznj1ecFF8p1Hl7jIHjm2+l4WvxXGkbWx0dQlyhsonhQm4igu7m68ZZfsLZfNLW2+g0gyZ8JTVi7xwsfH9LPtN738+nAq1ZABD94QtdhE4gSdnjuqKsL4tJZNdYk7ZVlKLEAahAi9QkWZkB3MZpaGeY1hSKDHiLUG3XHA7Rlf2quV5bxyPdCgJIpnUoki6eKPXtAp9pNbwQjus01raXbyFpZu0zWpOWEOh945BgpZ7hZpckrQ6w67ys2xI1083zBOPJVuzG4ugZaeKhJXnD2mx2UAZIgD2MZG4pwAF+IyXeKBd499srO+uPZmRtrLiLT3jzORuiPtNZzpRN30YRfgpKbU9cxsL8t4Qwc=
*/