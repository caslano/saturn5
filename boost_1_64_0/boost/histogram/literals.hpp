// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_LITERALS_HPP
#define BOOST_HISTOGRAM_LITERALS_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
constexpr unsigned parse_number(unsigned n) { return n; }

template <class... Rest>
constexpr unsigned parse_number(unsigned n, char f, Rest... rest) {
  return parse_number(10u * n + static_cast<unsigned>(f - '0'), rest...);
}
} // namespace detail

namespace literals {
/// Suffix operator to generate literal compile-time numbers, 0_c, 12_c, etc.
template <char... digits>
auto operator"" _c() {
  return std::integral_constant<unsigned, detail::parse_number(0, digits...)>();
}
} // namespace literals
} // namespace histogram
} // namespace boost

#endif

/* literals.hpp
mXYeV8sWUY4zqAWG9RGZaNRShICKWuyyljYrwqOQlopjeK7msvEymstk5f+92q60fdouZY+Cwy58GoMqk5AJBTSPRngsl46XccjDL9fgKwrMFAe1Q2l92kEFlj6UA+oT7mToSLdQ08ZTnh68vAN5+OWdfjo52K5tQd60rdp2BdhXgNjFKVBubqKmTaA8b+BlIvLwy7V+oEcc0Y4hD3B1BAhKVU6oT6xIhZp1KzXuXZTnFF7SkIdf3s3XE09r55AHuDpHKFLOACfpQGEbtec9Bg6uMzrteqQl53dil7aXUQEuUvYADRmEA2rPJAPDeQg4GA+iW9sIJKSkdYIN87RusU+hmwF7lA4ggrxa+csZne8lVPakSdzeoO1jzKCGFARvVPaKOupNQlwzNSjLzwTldnIuREw2MKkZmHwfkiSLbdpWauEWbauCHMp2YCUbWGmiFr7fwMpNjBU/2fE4r51BxJSAy5VG9KZBJRuoSdYOK+fQ0JNELdTQ02knkFk7AtoCiyDijKID2CsJ8Jy8SVJ7linEX8cYOW+QSJhTIskicQC0cVA7oCC50if2ouEt1rQ9okvbR3Sm7BJbQV7WLeT5K21bWqe1RxxpaHro3vs/iPa4lNNiiwC2AVRDM0VaT6RtF91pXdYOhXyj7Qw2X5V2xHq4oZVz1KG/DgZbRoit1u2iDgVukR9EV9pGFNyFIpOVw6ixdWRatx8JrNvStlh7Ag/q9ZUppKM/OxhUxPa0HrLtYX2joY0+yjobgpwQLs8urDlDOSiABa5ddKHgbhQt63Qqp1Fn20gAsZ3r+wLnoaHoBGrcjvqsb/jLAW/PkHpSL6wnheuZzfX4QXHUBLSvm+qKIC5drzHwC4pI2+hHq4CSE1Q7DUnKAdTaogSe5rbNRinH0qi0+aJb4jkNbWcc5yingm1XpZ2wHqZhiel0frB5REPrI30770bndALerWIRYN9u7WlokfWj2zdqncqBYMtIrQuFuJQ3RKfWFWxVtO6GIOVEpJ1KHiE2YjDoMqKNTrVqW0THQCR6rTfYompbG5o4Apij8pTDg0tMuXiJqRcpERjqFZ1UZpdRKvf/4cDX6R3lBp6hF62buBmOhJpGiA4w3HytSwBNKKiFPkeKy4zUQTnQ46dQepuqbdc2RkovR+lfpncgvBY1cMpstAxd2YV0bUaFQDo6M9hk1WRpi8iRoGrShAaaLUcPuIFP8s7XwaIKb+K8H7n80yyIWORfahb0fZbS5ScBSISc7cf8BzIMgm51JnzUYN6OC2xVb0XM/v/3H/pbP5/nP5bo863ZdL4FI6PPmj8ONfbifrpEQ1PGRe5Q2g7jLHXUvLmk8oLDi3VWmmfOp93rxUhq87hDv0riQ48kHJ+s+NtRek1ZOBvnHy/w+ceqGD6ME63z5iL7TJl9mNQ1vPVIU3VkPXLUcrH1yCPVb3E98h3LoPXIjbv/99Yjn616e9cjC+P/6euR5yovtx75fuXAemRn3MXXIw9UXrge+XncpdcjFZVv43qE7X2GzbweIRfxbmwIjMJiRHwcaLrXjNj5tC4hIU0zXfI4SAuSLRZ2RFpGgz7i3JUD6xE7+VlVsRrRp4ezjJUIAnIVwi9XyTk/dnEQiDPmu/E83xUQkbQgSduodWEeZ8FEBAKwoWnFowu3K5R5BM/s5Jw8QdluTO2s0bPeojRIKHYF2dnQWvOHthBAsSk0Zx/JVQdbbXhPVA4bdatcN2YHHag7Jw2lkFdNpauhbffiVJpPYlag0mKljdYrynmu8mqj7tFG3R2oOzVtI61QtA6lE+Q1v6H5YPczQYUqGaOvWsbifayyb9C6xYDcmdbZ0DKpdW0pzQl+qa48RhMFbjc=
*/