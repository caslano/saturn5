#ifndef BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class BackwardOp>
      struct foldr_start_with_parser
      {
      private:
        template <class Res, class Rem>
        struct apply_unchecked1 :
          accept<
            typename BackwardOp::template apply<
              typename get_result<Rem>::type,
              typename get_result<Res>::type
            >::type,
            typename get_remaining<Rem>::type,
            typename get_position<Rem>::type
          >
        {};

        template <class Res>
        struct apply_unchecked;
      public:
        typedef foldr_start_with_parser type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      private:
        template <class Res>
        struct apply_unchecked
        {
        private:
          typedef
            typename foldr_start_with_parser::template apply<
              typename get_remaining<Res>::type,
              typename get_position<Res>::type
            >
            parsed_remaining;
        public:
          typedef
            typename boost::mpl::eval_if<
              typename is_error<parsed_remaining>::type,
              parsed_remaining,
              apply_unchecked1<Res, parsed_remaining>
            >::type
            type;
        };
      };
    }
  }
}

#endif


/* foldr_start_with_parser.hpp
S/CtCV9EGh/HwA9h/P+zzpdMdDP3n84FnmLuP50b3GfuP50HvJW5//Sq+fn5ZRSc6/9j4Oz+I/isDE8soKh/cLb+FdxX8I0V+ndWpD8Q/Gqmfw2Cn8+8/6oCfjrz/qtDwE9l3n9VBT85wbyfccFk4m2J0/NNafDXJE7H507wVyROx+cu8JclTsfnbvAxJn87J5OJ5bnxC5wdv8BHGH47eIXxX46Cl5n7ezdeKMm/vxB8K8Z+3QV8C85/Af7OTP/sn7kD/G2JU//MneBvzsS8f2SxZGJbbv4D30TmNH/gz7WI/NP9pwfAHwSfI+Jk/+lB8PslTvefHgK/V+J0/+lh8HskTsevb5eI5n/wBvE334HvJHEaf/M9+A4Sp/E3P4FvJXN6f8KSGN8Z+yoDPsTsfw2B78fsf30LHiT+eX/pO/BDJE7l/wW+v8Sp/JGlkonVGPvxUfBLmfO/r4EfTu5XGF1CzJ9vgdcI/wY80n/W0vz8Mgq+AXP/6B3g60mcxh/cA94hc/r+i2Ww/pE4vZ9rbvBTiX+rupTof/OAn0z4L2tK/lHwHOHbrCXdbwrOxveAr8Ldr71sMnGNlH9aP4uCH5MQ7wOl9bMU+BESp/UzBt4m9X/6fv2PwRcAX0lwxE+L+IBPwOcjfAx89lD+1+CzEb78mqJ8FloumXgvMZUfB16fPzy0D258A1+PO78Lfi2T/mrwqxn7/WHwY5j1QWX5ZD0+e+kG9zcfAl6SOL2/uQpekDm53yUAP0jm9P0cKyYTDzV4v2NHqH8n8JvB5wl5dP5h5VD/7uDXET4A7oX69wC/hvD7wJcL9dfAj5U5Pf+wMvwTDca3RcP8HQ1+JuGov/r5gRPAj5U47d9ngy8hcfp+o41XQf3InPpPwEsSp/PvpuCDjP7dwfdm9O8Dvivhl6wixVeAnyxxGn/+BvjREqf7d++BVyVO57ePwIsyp+8nWpU8Hznfdgx4QeL0/eMngGcJfwA8en/qqeD7R1yyH2eN4ovB95I5jX9fDesn5vzJUuBrgs8iOMZv0X6WBl+V8FHw6H7o5cGXlzg9/7AC+HISp/FVV61O/BP0fnzw7Zjx6TbwTRj/+gJr8PIXAefkLwvOyR8BP03idP36MPi2CeRDcMQXS/s3ayYTpzDxC23gJzH2+Xvg2Qb1u0z4iT/A1wf3JN66kEi/yVpJxF9O5cOrSet38G8JfxI8ys1Va0M/837Tq8EzzPv/rwHn/Ad3gW/H3P/rtWL9wNxPsTL4Rg3qN7K/VwNfn6tf8A7mfqRTweX+Qf3XH4M/l5A49f/7/PraA2fX7z445/9WyN9ZIf9ABa8o+IhC/1mK9Fcp+KiCP6rQP6ZI/56Cf8tzdOBkIs3wncG3Ye4f3QV8K+b+0T3BN5E4PT+zH/j6EqfnZ0rgyxN+Inj02yj4ylz5gHP3uyRSycRxzPsJWsCPZd5PMAf44cz7ETYG34BZf46CryP5F2l81GPgSzeIL547Ot8Nvjjho+DR/PwM+AIN4otnjuKjwOfh3l/VkUx8GSVrsL5Kg38scVo+G4C/LXHqH9sW/AWJ0/ovg98ocVr/B6bhX+Xit8AX5/of+Nrc+qwT4zfnvwfvYvgoeE5af1H+LPg2LUz8Tzf8Gwlhr1H7cQx8ZynvlG+8LuynBvPDkiHfF3w28IUFx/pS6D8b/MWE4HR9+eh68P/M/M/25Rh4EXwWie+zguQfXx/rU8IvBK/7x8HXIfwT8Kh9VDZKJoYZ/90h4AF3P8TG8C9y7Qf8AghbWirjR2CcetA/wTeF/cDEp90Cvmvin+8n9DaD/c35T8Dfnfmf98efBH8YfHOJH72kGH+fA7+X8IfBo/F3DPxOwuc=
*/