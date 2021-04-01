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
y/o3l6i2vGIU38TIw44I8/ONBqL8wHHPmP0/wNXJ92YKNP/hzkTmHHzQ3g6mQZO/K1xxPzfLKAw9ReURMRM0kQkrHKgkBsGN9OgJTHrjen5U3LG0lKcHkkc05/qj8+K72wCeGYkTdO0ADWPtbsqc2oyEr+3Yk9hWAtPEoAv3BAK2T+eL2lKGh89Sdvgq43AvkdRnGViBASz3OkFneUKxYNERDvyEVk+JEGjJPP2OiyoOxGK6pejIibqBRLYideLaeOjvfoDYKt840iVbQWlsFRVnVunVDbhLJltNpMw9eQXhSOIBmD11nTQgdsyhTFWbdSy/Nbat+4uxVDMfBDQt35fCdaltQjln3SY8RcaKuuNG9r2y/hyR8kPrRNVfIxWTduFXmVGzyobOduYEEaEKpDgorWVk/arcsj7DR7hTzDnsK8BKmq5bqIkoTkE9t5QzyXpMsY6rllNdYU0BlYAOqRDUamyxkyI+t2OETyRpCs2rpMcFiAoB7XhN97rO9KBEvdInwvNqVlMK8uSHzKuB7CB6sa32cxOniFQKMBcANdH0zWD912LbhbNioA==
*/