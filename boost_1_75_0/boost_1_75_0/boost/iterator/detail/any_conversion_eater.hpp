// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef ANY_CONVERSION_EATER_DWA20031117_HPP
# define ANY_CONVERSION_EATER_DWA20031117_HPP

namespace boost {
namespace iterators {
namespace detail {

// This type can be used in traits to "eat" up the one user-defined
// implicit conversion allowed.
struct any_conversion_eater
{
    template <class T>
    any_conversion_eater(T const&);
};

}}} // namespace boost::iterators::detail

#endif // ANY_CONVERSION_EATER_DWA20031117_HPP

/* any_conversion_eater.hpp
0KLCSOIHa4hvnlR1sjGtA43t+gzQs/QMOsr13JbVS5KQBOUSUuJ9s/K1bRo1HtE3bTVyLrlbSok87mUnPczN6zS4NFOQz+gBT6EAWQRWJPv9sBSdrD6j9HiaKhUNOur6XLRiQbbsApPmNPgCVHAPtrU/PmQuzLtBquVllD9jmZ+Hn96I5BPn/ZhLUQ0EMZM1EKXE4IOPkZ02FLhzLJIZIxCZPq9gc4ZlTtiilFuvWmf/3+rec8lxNMkSfZW22fsP1kVoEGO9YwYtCEFo8WcMggRAaC2efhmZlVWZ1T19t4Yxndw0i4wIkAjiUy6OH3fX+zXWecPLlaRSSya7C4zKRitF9VARP7w/F6h6PvvHiH9GqZlERRzgJAeH0+qDt3lkQUjkgxvbIF46HoeEp1MHYnM8Tq/op2+czXdKGTPrs3Wqi8EbpgxXQanwan8VKuRmAucuJDBU5EgrQSL/Rc/xhx5WbzHyjQ7WK089mhrN5mwsI6/u45iHPHmSnyJanWeJXDXX3F8CR36sFPUGftQ+XcfJbB5YTCaZiIpCdMb5a8NtKhRUPkbcLJWiK46b29eE9Xd451vEH/0YVtK5Ki42KFX+AN9crqDHSluO4X71bn0zEjRf2HR8fdEmeafq6me3hz0Cx6viwGcCEHH+zMrQ/QiwAIhPwTqYe3Z+iOCfa5z5X6z1TwY7z3h5ttmycBI0A5AmWKjuNBtIYwFV
*/