/* Copyright 2003-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_IS_TRANSPARENT_HPP
#define BOOST_MULTI_INDEX_DETAIL_IS_TRANSPARENT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/intrinsics.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* Metafunction that checks if f(arg,arg2) executes without argument type
 * conversion. By default (i.e. when it cannot be determined) it evaluates to
 * true.
 */

template<typename F,typename Arg1,typename Arg2,typename=void>
struct is_transparent:mpl::true_{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#if !defined(BOOST_NO_SFINAE)&&!defined(BOOST_NO_SFINAE_EXPR)&& \
    !defined(BOOST_NO_CXX11_DECLTYPE)&& \
    (defined(BOOST_NO_CXX11_FINAL)||defined(BOOST_IS_FINAL))

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_final.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/declval.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost{

namespace multi_index{

namespace detail{

struct not_is_transparent_result_type{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent_class_helper:F
{
  using F::operator();
  template<typename T,typename Q>
  not_is_transparent_result_type operator()(const T&,const Q&)const;
};

template<typename F,typename Arg1,typename Arg2,typename=void>
struct is_transparent_class:mpl::true_{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent_class<
  F,Arg1,Arg2,
  typename enable_if<
    is_same<
      decltype(
        declval<const is_transparent_class_helper<F,Arg1,Arg2> >()(
          declval<const Arg1&>(),declval<const Arg2&>())
      ),
      not_is_transparent_result_type
    >
  >::type
>:mpl::false_{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent<
  F,Arg1,Arg2,
  typename enable_if<
    mpl::and_<
      is_class<F>,
      mpl::not_<is_final<F> > /* is_transparent_class_helper derives from F */
    >
  >::type
>:is_transparent_class<F,Arg1,Arg2>{};

template<typename F,typename Arg1,typename Arg2,typename=void>
struct is_transparent_function:mpl::true_{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent_function<
  F,Arg1,Arg2,
  typename enable_if<
    mpl::or_<
      mpl::not_<mpl::or_<
        is_same<typename function_traits<F>::arg1_type,const Arg1&>,
        is_same<typename function_traits<F>::arg1_type,Arg1>
      > >,
      mpl::not_<mpl::or_<
        is_same<typename function_traits<F>::arg2_type,const Arg2&>,
        is_same<typename function_traits<F>::arg2_type,Arg2>
      > >
    >
  >::type
>:mpl::false_{};

template<typename F,typename Arg1,typename Arg2>
struct is_transparent<
  F,Arg1,Arg2,
  typename enable_if<
    is_function<typename remove_pointer<F>::type>
  >::type
>:is_transparent_function<typename remove_pointer<F>::type,Arg1,Arg2>{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
#endif

/* is_transparent.hpp
6wqp1oYht4TmiaEkFxN8wULMZa7OZXuYeOeKo4tgBPUR3Krf7u6fHlfUCJw1ik6rr0py4Q8W4h4bR56fNg/b93NuEbSTTOyB9zgt+4POGDbDeYPIt2cwyUSlLzjEE84i3XiYeNdV+xex/Rk3Y07KO+MeRZ0Jt9PaEoNuSpnwAYvILB/6BzPxrCPmFMHG1D/2Qo/wx98gaWjh2Ltn6XO4G/mChXu5YCaefYnOInib5KIesdl7G5pPo5CfzecllFy4x8KZXsnFe/cqU2m9cm9Lr9yP9crcTHGeCPXrV551qFdhBd3plVy8d65oLIKtqP37oH/447MWKmortBXTnvVQ5efVUuJSr8QKOozf4Smf3/+u6XGxwdqXa4P5NFfOH6pisMcnO29/KNlR7rL9XD7vPUwv4j0Y1CXvnP/7a5IoZs6SXFpXDVLyv69Lm4q6xT7ZMNvVnQMeBst110QH3E7fFuA9HjgWuIyjqqsYl18c2Zg8TJYbixgs9GARdBmTXVezI9bhyA5vcrDXEtVFsB/pB01oh9/8vC/Iuw+CK3GcSLnWrup2iEEyFWpqxd+uLK4WA9sPenQR7EPjQhitjXu/HVXUWZBH5+cweCR+XbDYob0lmYjjf3fevxYDe09yhIg7TxhE8D7o1XvrFDUBi1cgPTEX5L5lz6s+YOBMO7IY2Bj8MQwOIwzwzrmHx0fIeykJbTm0llxB3UeTO8dlX2gJ4f+Nyh15a3jK5/bfOQyS1H7clH+v+wuKw5/i+TEu2p+HsvCyQ/2Q6lex0USn7dfls4/r3GHwDPl+t+C4/8Evb6oWdsIiHaeH2t/rQ/vL3e3FmRzsPYhDhsEBJANRvDP73ZXJO6UL9sUMmEd8rijjeTnUkXQNG5zNiX048DpRYLA+YYCpR9z8Ho2As6Hbs/fWG3K4F5mMRMLyV0Os2dVoaLOw7SgHD4ONCIdWjBT8+JbvkpYMtYRDPuHQ/avL8ZArGWlyjgOy8PhuCRzGEw5tOAZM//oBRZ0D8zzykOty3ZyuZJN7eWjqIw9BgcNOhEM73id90Nq0G7c/pDzyMNefftHU2OQcB2Rh78sUifFhdYUD+m8ctGGxsh6IkTNO/kvV2WqMrC5yOUZSJR2tnrh477gwdBgspnkyhlGZ9nhme0U9EMJZHPdS+jnPcOnnnEiG8H9D9yYTyme6wcBi4ZWDvGEQpv4Qx9vM7j/qDUU9CHKN89W4dgru7xMO7mGw9x1WGAaFtH6chS1vCn2mWnkwnJZJ0f0Igyv9wMCZx4LFwJaDjGGwFWGQwLhtE2fRuHgInDaI/P4HKz/v3A4/MHC2A2VysH06fw/AKoQBriGO7PpyF9IWYRT1hVqMNYApvmAQijnacDE52LaU7wPst4KXsZ/+Rha9/UNhPn5DWo7qC/kH+IBBPOkYAmTgWUN/F4AGwqATw818+95zkihW1tnahytLYdDtCwaubu6yGNj+K4sDHGehC6/cOX8dOhN2OPSSTS2eL+g4l/7iBwbtkVSLYxSYhXmePADXEA6zMcpEdJ0PFfUIOCKXxsUcZVOqvdQPHFodT4/IwOPTeFMALiVdqRvvEvj0ynpFPRKWkSycla/6wxI/+kPM+QTJHFhHuFxgQHPDHLxp5YY5ZFU9ChaSX2M12RbnX+YHBqGIoyNAJgfbv/my9NywP56XfWIS+XofDdk6PhmNi9UH+oBBR6erqEwmB9u2dGmAfbjQxvT5u9fsT9GOYWQm+bMRBgt8wcCZbcnkYOtJFwbgZMLgQNSSt6iapFp5DATz2TdFrp2W+rF2cj81MAe2I5wRgCLC4CC0qV9cF1atPBZeJP/O2ymWwE9+6IrO9hosBraedGIAtiM=
*/