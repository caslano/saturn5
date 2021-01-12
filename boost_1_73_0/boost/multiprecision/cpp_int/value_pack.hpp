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
SUxPYqp+7gQ2xQXvS+Dlcm5C8f5e+NEJwQfiOH47Z/QP9cJpX5Tx4V74MT7vQXl3ZX8glk0eF7qm/Gzx7WOMy46Ljr+hPGd5e9Cz6IJ7hnP5T/E+gjvTqF46cRz+/urwBoXe06X7r236/Fbr4ezbzmdu5n3uMhgOjUdpjbhqbe5K7+nJc/2hdDM7n8WCp4IFX+gPcRBhF9DFyYU6jxn3v1lsbjoNw975tJmo+rVWMaKX1pVz
*/