/* Copyright 2017-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/has_equal_to.hpp>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T>
using is_equality_comparable=std::integral_constant<
  bool,
  has_equal_to<T,T,bool>::value
>;

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_equality_comparable.hpp
+YcH0i2eqY2phYPzw2MIPgwLJg+0KXI04/Mabb1oDDQirvXDq9mXCBrUggn4hSPSEKGIJETFnya8MQRswrTIck6ZLpoJNSSkJEIqJaTQ+U1bD5VhTeJnyg9cMK69Py8ziiWgyQzo17HKsOVhXj6v2tztsT714mKQbO079jKQtqHlxsBl+GmHEvf+XX0elpey2lJ6Kc1+DYmete1bif60QVUjPq0MspoZ3rqYBRkOjw6tA1e/k7CqtFUMUZDW7KGCcMpccxG5yyentnhNOOb0Wzpb9p3ghj9XLBmQCTP8nJkYxX7ByX03QJ92FFUCULdMbCSnTyMh1yB3ET0LcWiGfHdj4zzlN1Ucysia1N89kAynbXbui9XJkSWbR63Pi9ETbVCuaLMciBRmdDlsJ+Ymnx4uSTxO3W4vbs78hTth4EOXyyKpNiyif1dpePnDZv8wSE+X+MrqzZelb5BnDhnlgi7ZWfp1wI/v8PTp91QjXfSOxixjH69vh5UeFGDfYnnjL390F233KMVGrxgsv0nZNQaaZ/+xiZ7eXTLKVO69UtVOflrlQJMTMllcnChtQUnf8GuxuQVRlnQM9V830eOsqBqzyb6uxb7+jONxkWFDUdGvpBFMYi+mNoC6rLRSTYzFmmi8G/OeWRu27fbVpzRG7YNEf9/bP9HlIeroGwMI28lFur2JWiU48iDGDBQxAQp9a9uQl3BauLjfVwR2
*/