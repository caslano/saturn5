#ifndef BOOST_METAPARSE_V1_NEXT_CHAR_HPP
#define BOOST_METAPARSE_V1_NEXT_CHAR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_char.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_char :
        next_char_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_char.hpp
oM8B3gVcDAhXJ9tyJazs+nFrezvcBAeTot72nk735mWvDfwp1A4nkc2Av0n3T1G25FTU9ZPR5p6Guv4RxIO/YX5Pf7+g4xgw/xmY/6OY/yyWf6LqY2fXkw5YGU9wzsF851b0tQbzJQWEP7mN7FP1+gTy9TaOBecj/U8SX2ATqjr/YJaV7WwI9vXwSYFyiSV+LlTj9FZXPkPFkRGaH1xk54rJkf4ChOFZuDdnvLjKOeOiMnPGT7n5qawWG8eTTeO6qxcb/Wlhf+ASvT5Yz4Nr+MSUUINR7mPYZ/d4EOTpOAx3SgNTUF8vCfRrMrn1/Wm8787W41K3XnafL53Jl+L3Piv6ud1F7OlY5tWAAB7vWM58N182kRRv4AxnYbvDEX6yiHeDb/cad7CzaGcu5/3d+pFgUbzi2Td7R2svNY5/DnX08xXnL9QY/uah/v8F1R+2qbK+iGVdhXh0ZzrNMa72/Jcq18lIXnBpcHJz1u5vWD37shznenpb+fKZ90n953jWT/tVXa7DulyLNud6rMtXWZ5vlGJ0sH/U2tjd4SRYbmzLr7v5+60nk/R8GXrD6htV9sFy6zbfxHUb71zAt7iOkm/VPpxJJci1kuCK59DH2CcycvgOnzuj7f0u/MIh3uYTnRtQht9j48bRbNy4UbXBTdgGx2Ab3Iz5b7F4wXOlceyNm/JvZeXfxny229V4ckc9/JTP9kPk50eVfPAqx2X3zuFKfbKK/QlD42dKhneqPvlz5PkXhAf9mJ3rVPl/jfm3YRv8BvPfxfrBKUxuv1Ny+309/JTc7kYaf/DqK3whirGitQW53jUV46q9fv9H3u/HWJ8iHaXYMIo5gz1X5O0+qh+sSwadb8LFBLRJ97v90NwljPFe2B8f4P1xB/2sw5h8H1Lyfbgefkq+j2AdHkXc01TcTjsMRB1puMQdQtZoz57mFaV0cHzZ3MIHf8rdn84acKd7Poru0DewXnd1BvfbJpk9QyaLSBVrZPsIebuR8WyP0x9f/ziXdRV71YHz0XHaTPd+Ua7HdN6Dh9K4snnS1ZFUVhBy6Hz23zn/44zRmV02zpRCTMU9hA71+X8wXX8G/+Zxoc/Wm29py/+JOvYcsyM5ZkeeV3O0PHy/gH2O5mjyHtAXIX0JzSmDZBG8QkAzzErnyjv7OlZ6WQnAZPJvxv/LzGd5pV76LK8yeUGf8cWbvq764xsoqzeDx0mwQVK2byH+2/Av3StLNms0pPceap2aiM0zIWLzvCz8BTNi23MXNL80MNpveK3eyDlVKMW8wvc0my95IubbDcoNuTC6G+1fgAexJ/NTiPMf+I45qfleWR+H7+nwncfv78P3DCdfwv8zfM+C9E34DcRg/XVTKX0ifM+B9BzLP8/JUbpZ76b9DtfW7ApCr4V83n+Lq9zbXcHs7OSIbNcpEfOT7ToVZb5TpELM2zjnO4beuyLy3sdpbl0GIUrEvaTeoXWYXLI/n0l7st3qtiHcR2JDC/i9Rdk4olp7bOcTuzAZharw+QP9rXH0TVO33bBu84NsZXcuOZTa7PIdilg40aB5azjyznzmuoj0meuZHKaOcz0ycI+qQmxr4Hx2B2KW96mRY7q3eEVxx73uARv7ahrOFcx4Te9mUXA16ATmg77bKe4UaoiY/tqVKbQlh8xw7sFaDKx1qGBp27zznF4bs4L6GAW8xR6sFLZtXAXIg/Hc3VgevD0IR/M6rT+Facd6eUuJNP8bdhId3s28Xp6fgv6PQBwhJdg5zTRo40bWxtkxY3bwngTlOzdhf29GHbZxqGQzpiub8e4I/JTN2ANp7On1g2Cb0dtqbgDyVI8+y8fmVbEeYcqdGZG+7F5GLrjWAb2P2RY=
*/