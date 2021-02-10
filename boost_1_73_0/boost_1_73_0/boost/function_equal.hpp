//  Copyright Douglas Gregor 2004.
//  Copyright 2005 Peter Dimov

//  Use, modification and distribution is subject to
//  the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_EQUAL_HPP
#define BOOST_FUNCTION_EQUAL_HPP

namespace boost {

template<typename F, typename G>
  bool function_equal_impl(const F& f, const G& g, long)
  { return f == g; }

// function_equal_impl needs to be unqualified to pick
// user overloads on two-phase compilers

template<typename F, typename G>
  bool function_equal(const F& f, const G& g)
  { return function_equal_impl(f, g, 0); }

} // end namespace boost

#endif // BOOST_FUNCTION_EQUAL_HPP

/* function_equal.hpp
UI5fhA1AP9Uvui9/LSTjRfAJZDhCeYE3d+Hmu+LSp0sadzL1KkkwRpbVBdESHRyT9FeM0v/l1cvvPchfXvywQRbLkqLiowb8Fv7jJPCKPYLsMdnM5/6d3P7iXIhRCEwIiU+JdI6GZh8wfOV+rFDbJ/hYZbZlFUm58jgjUyTK1wOcu623+YnBccSbj91jqbcoqhopaVXiZIPMDgUUVIqR8aSidPShqiYBziPZzU6ZdYzG3GQdIP6D6mUiUFRfPv1QneS3CSvotZE13O5UbDEWNwqNSvsHWdvi/ZJItlmQa67u5ZqWdiSzQjR/N9dc4SPbyZ8P4uintM7lDtmUGNa61QFZnI/jVgY0Kjs404dmz7Bspwd2Z+raOp6suPyovU1X3stf2+pQVqtIr75S4d2rlzvq8tEN34z3piUO68pecPrkr8qutgUHz2yxKB+efaUGdaLryCrdSdI4H9RiV0v73H4mG/xtpn183nr9aTZrf/w80z79NIPy98l2p6+wG8YrZFIS0IqkkZ90ML3Cnoc9iJVcplz6Z0rVqwlTefrdKNOQ2Og73gO3ZLMvk0IiyPr/moNTeNA9n806mzgGRZcChLfyanFsP2mc5EkHVBlZEPCEiduc73wvJpKsVFTuc/GCDAjsx3DnfFee8fdg
*/