///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_VP_HPP
#define BOOST_MP_CPP_INT_VP_HPP

namespace boost {
namespace multiprecision {

namespace literals { namespace detail {

template <limb_type... VALUES>
struct value_pack
{
   constexpr value_pack() {}

   typedef value_pack<0, VALUES...> next_type;
};
template <class T>
struct is_value_pack
{
   static constexpr bool value = false;
};
template <limb_type... VALUES>
struct is_value_pack<value_pack<VALUES...> >
{
   static constexpr bool value = true;
};

struct negate_tag
{};

constexpr negate_tag make_negate_tag()
{
   return negate_tag();
}

}}}} // namespace boost::multiprecision::literals::detail

#endif // BOOST_MP_CPP_INT_CORE_HPP

/* value_pack.hpp
d5XeC8NIlWOmt06QY3DFhYnMfqc7BQTotFgs8lLHJdSJiCnEM7JRBcQmB2U3oWzQ8fnpyNaeDZjaLzPoePAbu7TRJgk7c6JSE6AFqHDozLCdg8/LrfoEkza3TdIQSQDwCItDAubJSVcYFcrBjDJt7nQc/ErS+NJQqNsnndUyU8t9V2POKdNn4RMNf9ZCSXxW0L6tOkr5RLfDeTBTm9OcvcD2rSf1YMlSA+vKkjjd/84tK6OdKDyVz0F+YsKrsgO+auTrkNXqycvrWK2SgbvT6m5CUNa2999C+xIdrnvL8DkOp/tEpvspzxt0jx1joP6IepSfqbwch84eDXCA3eCA3R+ZOECnfEHyK/lnLVH+xXM03B1azWQWFLsTRPmwSAXNgvGBJI+5FD2BLEmn+isF1fdiqp8juUp71KN6LpMrqB4hJ6he54aCEDfYdG6AyyMa4gVE1Hl5wB7igVX/mzyw7CvgAev5eODDOjxwsRXjqAQPrKzLA8tDPCDl1eEB47P+PR5Y3jQPCPzrWwHn4YFYwQOPXsY8kNg0D2x63eCBN15vggeE7J/0bD3ZX1WPA9ivyxLOAMXAAIVWYoBdlQ0wQEOi/+KSM8wA4aL/dUeDor8+H1wk+KBLiA9c/zek//xGKT//v43yH/7CLnlEfofG6P6zunTf8rS9GbLfOe5/Qfav/o9k/zOXNEv2b/2XQffv/CtE9yPr+Nn4ng5p
*/