#ifndef BOOST_METAPARSE_V1_RANGE_C_HPP
#define BOOST_METAPARSE_V1_RANGE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/util/in_range_c.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char From, char To>
      struct range_c :
        accept_when<
          one_char,
          util::in_range_c<char, From, To>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* range_c.hpp
6EsJ/3PnO+dizDh81zv7lOszphLjy/sxAX+tOBe+b7m4ww4Y4YU87AeeiC7OxiBncQZm41/MLBfnXyfn4u9v8D8RtTuP6+A69T3yMUaXPmXaTjSUPTkIvJwDXhysBD5l0wo5bW3FDlRPh/EJnS/6Y0Xh0G9VNxg8l5/Jcz/9duZCw/uoCbq+xeD9dPDOfcj9NB+2+dByLedJOXpA67ZyHQP8MLzzsq2Y7Xezsd8txvYtEzy3CPtbAj5WlGsZ2vvHK6O+NmOf2oS+Z9mVDiO7w0V7V7FNgN7guwrkR+NOrRGOKlf4BPf4bUyT9FTjlMBvMCXGymvmW166nM8I3hrPbwcSz+bcd8dgjel7a2s6BZz4y/3GIuCONwvvhpyfkm/MAP8bMX4hfYyv+mVhjA2mvNj3MTKKxqjgbwV408Ks0Taw/BWPG0WbXJ5t0+fLh1oX9aYG+lp7e9Kt7rHj9ED24TGbz2dtx7Ke09/iHTCj/yegTceV+zadCJ36AvAWD82Pe3+wy1U90NfbM5CWPFkYn3+cJHg5uZz3AaeU63XjqeXup+VzWmQvgOv+Psm05wwzx5wZ2WrgNQzZHjDb4fzUskc5FqB8Us42dZ9j6j4XdZ8HvNlD1u0341ytzOM+PV7I60Ijr6+U08/I6yLUf7HQhQuE/C8V9C4z9L5aTj9D73LQuwK48T5mjenMQKqtj/q87+i2VNQincttuqpcx7u+OtTDEClw6Y87X+HwXUrtPzzO5fW0ZQb7+TvLNeXMRb7io5PZkJnoyz2H9VPu6FyTHvDvaeCs/euinrH+TMkxiCpEGm28wOjJtUZPvgm5Xif66WzRT9eLfrrB9NON5e5nYimD3k1inFxqeLgZZa7FuP8OytyyfV0lWyN9RlQen/Wb+m5Ffeegvu+jvh8YvOOMbG4D3u2iLSebMneizBmg/SOUuQt4k9G/3lfC+4q7/uQ+pphT7lhxDekS+vgnso8/hE5vf0wMr4uO75+Z+fzn5X5+TU3U6527Kb+acHbi+djMybbMTsG9PAeBrtad+8Xa7t6CodeAD5q1AOFRnYwr1wK/QH98z+jur1z9Jqbew7xGITj7PMh2P6rWgvGyecysP6zP+uPl7A+UKzuLPyZ4QsjlhmHk8qTAO2XC0HhPizY8URjfht9zGwgntw3PGrjty+fKtazPK9Lw5wUPqSHkuEXQSMXIcauBWx5eFPD9Ct3PxGEu12/xNUk/JoK/LOR5Ld5Xc3h/y9fr5VcEneeKcum8mkPH41k6rxl+DlN+UfT2mqnHwt+MbA/WhJLW295OEczjvsPyJx30OPbtuPdMfZbGvxQNj2NpfACe6ktyeRpVEeISzNMbXaHrs/C8iiH8iEYwD46pYBu+U0UuL2N9XQTzde1seLHwXSt0+fOLpN8cxSEx5S18d1P+COmnRvACU97Cx6vybMsuA/1iU97CJ5ryfyzjO1wOvocpb+FlqjyP7xTol5vyFl5pyls/u6oK+bahx0mas/QaU4elUWdosH4yjb0MH9Yf76OmDgvf25S/y9igfSpk2o6pXPxpBv8DYxOsjdvP1F9vbOTHxRiyvpWUp9Y7s0xbbV2zDdzWdYDhhcaKgh9oylv4HFPe+i7OM+UtfL4pb2PNNpjyFr7QlH/CzBeLTXkLX2LgKUO/UcDTBNvXyG8p5LGK/Xmhv/KsxsSHQBlaT4U0bijiMsm8+DvFKyoQQ8is9VZWmBhCOLtZVcE64/I4Xh3543KbCJZ7rnAEt8nge/nZ71lHGTj9U/D2Cl77vcr3alQ7T0NM9Q6D21QwNO5qUa/Ls3e711bwHH6aoqPXVp8zdRbkD11nV4V+32QM6xPSTKuLfWnwg+8=
*/