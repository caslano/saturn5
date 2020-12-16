#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>
#include <boost/metaparse/v1/cpp11/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp11/impl/size.hpp>

#include <boost/mpl/clear.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_back;

        template <char C>
        struct pop_back<string<C>> : boost::mpl::clear<string<C>> {};

        template <char C, char... Cs>
        struct pop_back<string<C, Cs...>> :
          push_front_c<typename pop_back<string<Cs...>>::type, C>
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
Tfvci+06tZsFbylS07Vzj4TYuLFAyHh/+Qj8+8F5Gkwdd+coNZ3aekU1fZIy9sbor5Q6jSJ7RcMN+hFD8M9djl2sTr7qJzpoccBdsM6YjpWNhEsH6W8MVn9s08PIr/ajrd5ii9vz6qNUV0PcynaOeZ2uS+fzraP0fG6MhN/jhevK0cHXqdOvojdh2W/M47q5bNtLXdqTXfH/+W247oQa/nb+ziOezK2gfsqDvezs5Zs/3khDro8/M4NWV+MfmaxG2ICnYHd3GqYBjVYli5yfgOtai5cG7N5KLwHG/fCycbop8O378EEj32fPQ4VdqzTsx/efZTY3vi0uLjaN5YvK/FwYnmWOho/8bY/jX9yvvulCR6rvqnxsrbQgO94VC93r6pn97JyOLQMDarTiXzVMkzlslqT+UhseEUfN1KBdj/k7uyfgucvVeSk76G39nHNqgWb0x5Qqnq0jDvabywh1bZSW2vMg3fWMd3m3F8u9xDVd0EovdDKNOqCWaxrX18ON6SnaDa5MkHfJ7cznhGeTyPMhD3jf4Xu0KZ0/DXaenBINf4DRWR5RO38hJvvpNZ2gh5+jr9n4ZphZW9wseDYmx2BvDzgl9xo6x9pUeKRWvwUWoM1QeqF+3H10zADYMskY1U3Ll8EV/DjgUf7CiVt+iqm5YeKrdNgQePsJ3uwUDQ8UVYushrm4f3Bt+d4RvlwZCSvnmVNx/HpOj+ZbOiCuG3PpScHzOCYfOw4Hk2GeOiBNrP+utXx8XX/1JO0Lj5qIyb58Xaqya62HAefh5NXwgXZpLf6+/9D/D8ijoM/5W7YYGgvvNcKfOHRXNf2IS2Mhx04ckjsSBm+KZOBm19PiwPd7+G7Lmfiro34APbYINuX3/UWbI8CDthzMh/C4ExuOLO9/NViNTOqrnbjLeQr+5Hz6Cf0cvv9q3KVn8+hcudAZbjVhP7nyyKx479f9RMX0evQ6dueUg3XZV3w2T8eh7dmNfxokwsqmxt2c38Wqsibkhasz8Fe+ZvjK+E/T5R9NoXFo0+dwZ6+p/Cvf5uyD6R3F1wx2hqUp+Lv31XqKBdkok54m3fUevG6pPqg3UM8oXW6LsYnisFRzMY/fsmWFKecdx1Z/3Os7dG7bDjCmCE15C0yGNYVOGtvreKhuTD9aXonp0vXVEr63e10stGkKr9LwSD/9HD3Uhp1oULhyvDdd7Hv9b6Uh+H20uG5wrTyGGb370rTqhMZ837E3TfU0PTUKh9L870/BD8n60PL++9vUmGy5pQz/ZlWPiIvsc2FLkjoJdj8IZwvQcnF8SlArXBpRu8C+oTD9Cxql8GPGO80Y4fSHdEmW2casj9gfJrYfZG5tzIl26dzQORl/ySC5UEJ/3fyfbCoOaP5S16mVYPXXe9Rnlcz9LX7doJ/AvlXVft070ePPqT3xWPPudNYVsdBLzB3NpV6nVfvCj9n+dukade9646KlFguebGybfC8NkQjbcX0/2JBCp9WCMcPUNXXgbn9xUP5ddqJxesvJvu3FWjob+ezdBL1KeFxunZwUV+3mwb6O+p72Ayax7TXib1GfaPh0LLvRNh/Cr4Kb9Xze8i7AIXToCNymjh/KXw3XwVF1atVke6tms21EvLwq7sT6d7lpwbfgJt3x6I/81l9PaQE7X6Hv/vgvtizwGfux2e8C7H4w7ivaip1aqr2/KKP+yE97qKNnqpFPDoSlYuyDInpM8uw3fHjKOIewz7xO+jAlxcF7NAcbV1+oLl6FOw7zkTWD+vw61fzLu1aZ7fi1BN4XM3/k0238/loTGvMYLQRXsvPZcvrHoMKQV/AiPxxqIl9p/XvptYZwu/B+eqsnfXodns7HZ3nUlfoaB3o=
*/