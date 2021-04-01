/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP
#define BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* converter offers means to access indices of a given multi_index_container
 * and for convertibilty between index iterators, so providing a
 * localized access point for get() and project() functions.
 */

template<typename MultiIndexContainer,typename Index>
struct converter
{
  static const Index& index(const MultiIndexContainer& x){return x;}
  static Index&       index(MultiIndexContainer& x){return x;}

  static typename Index::const_iterator const_iterator(
    const MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }

  static typename Index::iterator iterator(
    MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* converter.hpp
XSwO6GhrlgBBQdjR1WBDefoTgHc+kPQhIQ8MhD5rbfSJwP/pEG6dYaNEr98eqBUbc5CcdBxHapngmAoddYQPTJaHpEVNs/cRaqAj1GamLdCARnZ9RPtIHf2j+5mVqRJ22BgUp1Pwkjm5an3QehsXDp9+B6nHdmAk/P6+hOdQJP7yVMX4URNKlP1J25ApKqNJsDFo+hPrsGL5n5xCMDBhL7u/8d/M+K1+61K1njbzEJce6zOlzwrq3ZRZ3iyGFLM3mOZJof4R4EBPM8DwcCUwo7S/Xh6E6nUq0l4KUUA57gAQOQ/98MecA/vdVfhKhMXdov8/VjeG/eHsdR0+tSHVlKrLaUb9U54BfmHHbZkzT8AN6oZQ0REWz5drsHWTP5QinBxgKeh+ROZW+vCFkPeF5mztwAnIciZa+tddIStAPTBfgubcdhJx8Izku1ttYL5CF4YnJQesQ3ZLivtj4s8Hn8ZN2SubUK3kAaxzCXshYsbSSMaN6/BwfXROx8q2Slljo+QA5Keh/2LbtbvcHnr4lhHpwQhh6jkB4NxoQ9GVvno/euv1/v9uljE3eA==
*/