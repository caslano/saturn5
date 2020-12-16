#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of = repeated<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of.hpp
4ZtkdDAvx8YtnhFR+ww2YPathan0ZNELwvWQ+cAn2xEhO9uN7NCUznHXIkDz+oStMK29w6rG0T+pcfTPCP9Jj3/Ahdy6a8bB+AfZhnwTvsY9xvsbwXQ/oDiBh3fzOE/glc/zXwK3OO87c4TR7Oh55K3e02v2Zfd4+FCVfptrhdxP1yKtfEuv2V1b0fE1zcovVi3lJ96Xumw5+c9w5ub5NOSM5M6u3ozI8DqWSZK3wRD3uDPM2J+tlzK6M5A/2G0rmuX7s/a91azj9x8gKUOWd4LHG6qVD1bKE20BHG473W61zRjzZBsrmdDv1K6iNJoGLY9rmt250OQJri5cB913oi2f+KJ04XqET0J8k4rX4TqE1wP/jQh/uckP/1HhP0GF+1T4mXjn4LdN7r3og2f4fR1tinDJtnngz/UUomHdgmNez2AiS+tG9oHdbc0N5M3VtG2UDi6q96VObWbbc6OVn0mPx84ZL6Djkc2VjL2SjoaG7aDD8KLkcVsE9T+tWdQfYV3/rQRbf5Tl/ge0P7oReQS0rt0gaEVY03oGlVN3lOUcPa1nN0XxuV7wuV7xuT6Cz9sIVv8AlGtkn8dq/smxejvrCYHj6nhtTzeyHpL4+OuuiTUxrrYr2LYAbkszbG7OV+Xv2txtzRjvFL7uVx2KBp2npLeL81S0umNoj9KV5vcMpSv7uFwxHkfr6/5Ar1azjafeQY3UGQM8JoIO1/47l+LlGFinZAI0OXQPOnVTPAXOMOgtyjDoyJ9I6dTYHFdtQPpY/Nw22KPalfHdup8HGqgs1FXzm3ldrGZcU8YF4AuFQxvelz3U2Svzpjtk73FcFuHovVa3bROKrvlwk83+/N2UvwR25biBXebOXa5e584fp+QcA29g8PiPsrhOeFNX8mS5NxVRJ8Kj+gNX0HmA+2okrt4vzBB+ozO/TdNF2UOpAvu0MHsjqZkiv/dk9iouSdG9S8wHs8KmWoF5LOwnug9krSoNnOcdJqDO5HIZm1SEKVXkHYdFlBn4xp6xNNtCbD2fSOE1np+Y36AqFYK3hYv+G3T5PArgOVAxl0tMJ7OHxRwINmewVpgX/KkXtCoqu4Jx4muQna4q4vFCPEqki6lp5OQCw/lPCXLaENjYlp6DyeD+/MFmUxYd1j/I4b6qLF2a5jaeFXXYWVV5+XbvEXlSb0glJ7gM2gsr5fO0Tkx4gJFsFZNptEnJyhPaAOFayF4D5pOHBV1rFpAdwwtqZ2cu+CRlNz8Z8yCSD2cOfymFS8pH7FObEZZpke+lKu7pzW5eRc/Vkc8U8U/isti3cKhTcT5mLb95yvY1h29SYax1IGyyVOGlIozjWFc7b1h3izesu61dxO9Yp8Q71saNu43D3LGYRtjWeU3wPrfAWce+3K0+X+/Z/mDDz6ZwnT9Pm0iQO1PpO3aTZxflj7TgDbiXCFnYYtKMZUiZpbPhSzMCFDW323Tq3HnVS7ldEK/ORfOYDB3OYyzh++eiMXacciqv/b5SyeGrml1/wq9W5Wr/xK9hPQ/7zf1pPf86wj/HsdNJn2POXEfY+Ca+TWJd3eqq0qQYB2ZMGL6NgvWcNzDPKZexTPLiVENBzqcBqmA9p6K0hndvkn0TY/abm912eQv3RY4Db9/GbUZx0fsPbxf8eqTg1+TpZo2hGH4Pg1+3bqI+qPh1RwS/3iH49SvUeUzWGaBK+TVvWvDrXRH8erfi13uYX4hjfr2P+UVxZfZrYLc98XReD5DvGC6jcHDn28Bw18w+6boftkWdLY32EgEM/Wz5nvaTWeE7us6WynbJ7afa96hSyUkkRjtca8eULL3LnchNThZSRY/TP8SHUyZuWceTDUQOIpCRfM+7kMw=
*/