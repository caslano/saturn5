#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char D, char... Cs>
        struct is_none_c_impl;

        template <char D>
        struct is_none_c_impl<D> : boost::mpl::bool_<true> {};

        template <char D, char... Cs>
        struct is_none_c_impl<D, D, Cs...> : boost::mpl::bool_<false> {};

        template <char D, char C, char... Cs>
        struct is_none_c_impl<D, C, Cs...> : is_none_c_impl<D, Cs...> {};
      }
    }
  }
}

#endif


/* is_none_c_impl.hpp
/IkZPQ8GzoUInp5nlh5wn9vyMWdO+nrMv2dJ/h3FekqgRz8WnLPH2fzndJZ5+3YRZwhMH3ge+kBQzvMpLM/zv4DCRq5u3czjogn/ppbDJp+v1vq6uSM8d1nKmjPFaXPPN/QbGULInAx8/Eksmn+I85+Xd/IJMesg0zy9SQeeZ8zfIg6DzoNAlWTa7PgC2oQfiir4oegwvixR7su4XP+uvGEeF6fgvF7TCh7gHgB9s3/tl1Oe5u3/V4C/RZzLfSXC9Wg9ftvLpgE++yS/isLUVha/SsjHaxnPxrwO64eXq/saVwblAe+NwKP2dfyhv7mTfqrstwCX2t59i7jT/Nw3Ma5G+Ao+k+uUu66WaSKYI3Pv7OS860V8PfJ+t6TL8pDv77TV8vnnK2DLFTrct2Dep2S6Wso0wpshK3W4azvtn8QPDgMlClPpyaL1yUxnsSA3H+rUZ5nmSYvzVZXjY98b+sfwm6R0Mp3390MBMzookyQQwkbn0M0yPq/yYdc+zNFR7XQxYedluDqsYNrvsb4X0jcUlw8/zoHCXvwI9MzW6LzIVTIN2TYHfCPdR5HuOr6vKu9b2QsHfMYjbh58MeNuCKvxYbvI9SnxSd5Ti5fG4ofpst30aHrME74M+tN0Rc3aMXxvhH0oAM/4N8iPpYs0DpNvwFQetwr8fD5m50l0f3TSs3fIa4jvH5dzozL1PcD+IZi/8VivubsFbuq78LvThXG+kK/gXZFZ+HK0le6Dsj9nGvXhb/YTkGFdBOHauBrPhOV9G9xBwW0/OY7X2js+Q5MjyVnJT+Id2DWaQxTnt07EpYJbLwWOX8/xu2gWm7UXCgt8NqUOdwypVE4u7rRsDONlcnnnppeOZybHqQQSrfS4ieuHD4kbRRtuUe2j+kAk2xsdW2h46nAhPc6MYxq8gKeGfQQnuTB+lpfdZPr3f1kuIuc6R1FX03c/jb6LMcMZhz4LHe7rsSrvc0Ln31eLtxrE2yY3d3Lal3e4Y90XMC7Vea4vry8S/D7k85lOP5/bgPtpsab9NUXbK9QY+dXOsmtAozF0YvoIbaqvo94mj2906nFdjUmo37cIL3K9qkIdbcr9jrLlvqtsgu+per1T8JTGQhtHf23cD7k9KB/EC3pvN2Nr5JpDsOTgrzg0SJm3M9XKz1b+xLGdI5btXJDlfyQPK0z7b/buM8qq6gwD8L73IkVAqkpTinTpINL70KQXqYr0NjPgFIqhCAEMAZEiAVGQpqIIFhTBgigKqKCIvSFdERERIsVCnjuSSNpKslZ+5EdcyzXDnXPP2fsr7/t+397nnIx9IBdsWOIfnedv5nahtrnwTNCRvzwqduivdeDBjHzNqFsy5ngoAz/ThgxNjd+UluiZORnb7C56x3tqHC9TLq59csWfl5Px7vf4zWcX7om+UNsc/tt+W9P4jW7xkIhfMmOgf/thxjz/IZ//B9+P688vG160h+ei/tlXF/XPGvxVHyv5r070Z7w7mmGjC721vznizzXU17/O07F/O6RfS/9/+BcjnvxXzz7o3+/P/rk1IwYTR/75bsaLP8/qc+ExPG3EyPDnz3L4rMvQtMSBf/UMhAGju1/07/z+3eOifxeI//0Cjv/KYY75m8+KxY/LuK8wzj+/Pk+gZPzYf/B5WZ83H5qY+DfPjLxwz6e/uRnxYt6rEkZ3HjJidDdPSxkx+qLPq7HHr2/8+PW9/jUusku1i3RPrTCkc9qAVskj03/VXfUyPmufnubDizVWo4zPM569kfGu77zxd29c5MtmIf4crk5dunaIv8ShW4YP/+oTvuv5D5+5lNDyb+64r1MnoeWvjxXIONPFHzT62y9krA+s/x96DkJce33LNhc=
*/