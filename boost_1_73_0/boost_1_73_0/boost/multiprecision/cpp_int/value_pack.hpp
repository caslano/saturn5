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
Y0SqUBfbAw1Jw0JdnO4ol46P3pYq9YIxWoVaDQgrz0LUahS7zYPgU8UEUdlJIRuefZIBKgmNxeX3bCmxY2PCFA9PCoIreDgudA73HtbKwpCuqsjSqkkFqbH5Zshxd3fv6IgVjCLAcDTsCQfpNThUVui0Dl8r1uTB7/45/5UShhOF0wkVqrJ1bd6gR+zh/7DG75324euGzb0qJFmZbiKcaoOl8f4vFxTydyZqjx8+lFR4WNC26O7O4D8Sdm9i2OPmVimiWL1rHubIDeBzlwfFkTmtZBTMxekYtbncXJQHbOiwsbahUKTjSP/Dosbv5fe/r9aenz6qNBqbio/wNVicq/DR6K6DoiLf8CKGPsHYP8KKdrWxdLlAqBaqrIAvFJRCEpFQfkh1Kuzbb3GHQDYDar1g7rHOBl2o2FQb1UkUm2T8RLONeC0MLsYw3+KIlX/sZXZ2h4m87m53t0/8b1affgQ5qTJuv5WLI42RTAmXTdyksUiWQcujs7ssNrsWZO6OeY9xW5qGR+xNi6htdbKVgnREoLI4I88uaDs7EkdsJyNQQbhkjQewapGLvQgAy9qfJMc8TIKszX2aaOLF/GjyiNG2EGLQd1UJNf5SRnIjF5DP/h14frkAVIUR2NTf/uhQWMHIi+l10ZFqWAxd
*/