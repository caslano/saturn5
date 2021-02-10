/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_FUNCTION_COLLECTION_FWD_HPP
#define BOOST_POLY_COLLECTION_FUNCTION_COLLECTION_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <memory>

namespace boost{

namespace poly_collection{

namespace detail{
template<typename Signature> struct function_model;
}

template<typename Signature>
using function_collection_value_type=
  typename detail::function_model<Signature>::value_type;

template<
  typename Signature,
  typename Allocator=std::allocator<function_collection_value_type<Signature>>
>
class function_collection;

template<typename Signature,typename Allocator>
bool operator==(
  const function_collection<Signature,Allocator>& x,
  const function_collection<Signature,Allocator>& y);

template<typename Signature,typename Allocator>
bool operator!=(
  const function_collection<Signature,Allocator>& x,
  const function_collection<Signature,Allocator>& y);

template<typename Signature,typename Allocator>
void swap(
  function_collection<Signature,Allocator>& x,
  function_collection<Signature,Allocator>& y);

} /* namespace poly_collection */

using poly_collection::function_collection;

} /* namespace boost */

#endif

/* function_collection_fwd.hpp
/KK2V1jS58d5cA3nF86/UEsDBAoAAAAIAC1nSlIV8oV1VQMAAC8IAAAhAAkAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTYxMi5jVVQFAAG2SCRgzVRRb9o6FH7PrzjKXqBKSaFjLbfbNAa9K9oGCFJNaJksEzuN703iyHZoqtv99x0n0KqMq96HPlwjYvvk+75z/J0k/tHLDQeO4NlB6j/BgXPNmCv5F4/MYTQh99D8kBXi/FwSHx4p96QNz1PuoVVTyDbLW7sm5LlEoa3NXnzLDIldYgRpljmSxZ0SN4mB1qgN3cHgHI6hd9I78WBMc8FTWBqer7m68eAtqyMfElpVHc3fe8AN0LSzlQoSoUHL2NxSxQHXqYh4rjkDqoFxHSmxxo3IwSQcYpFyGM3mq8n0kwe3iYgSK3InS9CJLFMGCd1wUDziYtNoFFQZkDHSUZwJbVCwNELmHczNwXCVaath09NUS6AbKlK6xkTUQGJMof/w/ahUKVbvMxlpP9odv5OY7OEkKywio3cgCwNGQqm5BxbpQSaZiO2MhmCwKNep0In3WA2mypkvFWieplYLeYLrpmwOy609noVBgRULYyctc21T3SYyewJEH61KXKocE6EPCGISbfagzBlXNbg++S7F1tPa4H9t
*/