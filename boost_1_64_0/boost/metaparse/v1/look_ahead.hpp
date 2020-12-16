#ifndef BOOST_METAPARSE_V1_LOOK_AHEAD_HPP
#define BOOST_METAPARSE_V1_LOOK_AHEAD_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)   2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct look_ahead
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename get_result<typename P::template apply<S, Pos> >::type,
            S,
            Pos
          >
        {};
      public:
        typedef look_ahead type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            no_error<S, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* look_ahead.hpp
VX0xzzUol07MczjLM5eNDysUfyvr4Kf460IaqxiN32O599YEr43ZvAOZjInOovUyufYNcLKT1h472zmuCUVcn5TrbUm4byGZ64d+LHEHUgUkK+GZRCFZSmHwLADcJXZM4nkKi/ZHKOOlf6EPtj6ZBlZGfPCB0awPVkynjEkDbH95xYINfQKYpG3PIPrSNqXyKeKc0xlaHCQDcxBAfp9QBDuSxHsM6krtssk9cLfdxt2DcZzcU1fdmuJMsb5Fa4G9bn5L1hvr+rjNrnKPcSfVN9agjl6Oen4U6uhahfec6q9HI94xTJcHWX/4sOoPx9XBT/WHONI4XpX1BVXWAOIlEO9oIaO0ez6b1l3hbDbGztEZNzh8YGF0hgNg+Y0OnUfFtcNlOI9OMtlGdmCfKXBNapzzcXf/i2QDf5NvklIy24CyHUbfZCPKbATx7NxW5kljni9g22cwT1bRHlb2M4d4ecQ7vIq1rtY+iCtvW91nbyEpk4Z1LiLdW97RGgrOhPtHSn14U51p9/5iYdhdPC3hhhAXl1yoz9P8zE3ndGJgh4iSha9z93XtPvEy3NM9kenRjB2Kb7FtkND7fNgGJ7H2TbHx8hTV/06tg5/qf6chjY8wHfsw83/PUHpwJuY/DvXlo5j/LMSzeYiHsxUP59TBT/FwLtL4OKMRUnr6CcxzG5Z7Pub5pOLvNiWjrYh3YV2FdeJxnqc18dcXAz1jM651HPH9KnyXKaPrMBPY3b5yaXxpx7IurwwfmNbGPoN93dC/BOk/7zhl9nZgOIzDPGjYI8y+sU99FmUQnH8Q8TODbnb6LI0bl2N+w886PMcwAvzw7+PgG/dz3H2UcEjfuzTRuRLb5At1Va3dm9B4u1xHdkPCsX5flLoG5VPZV9VZXfsSln11AC7wJ+JCv4y4XwnABXoC9zrEvR5xB9Bubauz/of2p64xY7mFg6dGNu1ad15j4kSkX/dVY7cQjhlKsVZfY/Yl5M5Z1hxgpbOyo2/5qqU0efGngG6MtY7W2e1d05Dr6U+vT7q0yqYCveB1ddjUWNfdZzdbOvuWr4x3Lu3o6oPzJXhIu0I60DyoEs22TvitWNVGdAgGeb258DddObWKNYRvuXLtdg8LHgFG2zvv820m0xiU09HTF+9e3baisz1+RMc6Wk8MTBmD31Wt3Z3Er4JB3rlyjzx/0qqBDZ24P/xdV2+6vTWPPN+Tu4GvF7xDec8Wcf6JAbprw+51w7pLCXYQlv997otWWddFopzBE1dkTgSyyT7w0uluJ4Cbc7aYYH1qLPMmWaa5KqCvc6W1FKUvKKfCfngueQLvIfhteAvMs7q3o6drVV9ne4eXiyBka3+AdmCJ8F8S2Xwxl/LkeKvLexG8lnSmkKJ78kQ8Ap7ZvW2ccwc7D8yeUOwfKfnGt7s0Bp0lKLs7hOy6V4EKrztydesKo8Je3XxQKCPYXpcMwTL3vi6PgA9M85AfqbH7x8rH/Ana1J/WjRlDZNmMd61aWmoVDae2uZPKhb/J1/mF4ueXyM/P0Z/+FfLz67qq9og3ZVJ2KBUQ5OEupOGd4fwtfEPejfYeCXuG83fUPtBu7oJbBmLHhYvigxr7Uea+pvUw2/fy2S/cm6lkW8GmmWN9a2y4rJs3MAXr9Qeslxd3eYK1YSfmTzKnwvpT4Nt2gb46Xlqtm9ady2xywXTmHvq8gfZtycp7IgGu73GB/U+D6hpFD/eeOuO359ZTAuHHgAbY+l5zocky3Ff5I5P1dF/dydz7E2gv/Za6CnGKOzAuG5r3Ic0LxHyXYlwSfA5ktp9oXxhkmC/ahXnal7rXHe8Qbkwd4pu5f4itr/7Zld/ggOsDsrsMYgCz9xhYud0=
*/