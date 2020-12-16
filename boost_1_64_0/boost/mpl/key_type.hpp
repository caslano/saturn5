
#ifndef BOOST_MPL_KEY_TYPE_HPP_INCLUDED
#define BOOST_MPL_KEY_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct key_type
    : apply_wrap2< 
          key_type_impl< typename sequence_tag<AssociativeSequence>::type >
        , AssociativeSequence, T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,key_type,(AssociativeSequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, key_type)

}}

#endif // BOOST_MPL_KEY_TYPE_HPP_INCLUDED

/* key_type.hpp
UPmAMKKEjpd1o0ljVoJco8+pDh+wru4OrNgNUEf3REd78T7Guchys7DpqVbO1fRlN31Cf+6cwPkv++j9yJM1lvz/YaOe9qSQTCTeqvFbQmwfCI06E06sSjXONU5XUAbvAQHolIBfOdUOT/hFO+BhUj7SXZJrTNbF5qtiW7aKYpUo1oJippJiSiwEeYo9TSuXTQzsZ0zRpM4AqnkSFS1CSkgVZ5I6AiHFsmkzTa5MDEt36dkYE+9jc+qG3lpv6SQ+XmKV999TtSyE5pChM6z2y3TtpaL9W2X7HZYc+sCh5VBf1oeacVUVI3cmVjoiqDF0gIpd450YBlKsQbDz2NeYravsjipvxBKSSb4aQggMF3YMf1fIgJ3CDAhUdwrDvKI+H+DZX6hEY4HGfBEwDxeY4eh3zVfhIqHleeHwE3WLFzU9/gygO+0S+It+1Hr9mTgHocWrJAuL7wl3yYRcpYjtaxyjeETbJj/xyLcFPGIFLaF/whhS61HTbIhJddV2Xq7BwwVYKcTJpYR19WvAyl7vt8BGAHouFNK1ArF2lJ8D+B9mJoadr6XsFN4CodwgqxwfMIqFZqa6aVNyIIKX8AoGda9apcv7l71IDc4IPQAVuLVzEW/i3A8ZUq39N8Xgh3ugly4udpHO78SalxVrSP5P4/gvmzVrHkeguRbRntvFGxZqcCNW22LwDig/76KOWLFszxQ10Aozd5LfieX9VQXRyENY7I8ayYhJTLBdSoWaOgKrW18IjxfJ4g9a1RjJIn5l0tTCfT+AhJyOZN5RSPZj3X8m9RkmTXgdERPgaFRGWWHOFCKgl0f05jGQRK7SQYJCL1Sfk+IVQYO6kwzsiM+B9f7n9nB7IbwwslCpW+gLNU9gsOEamUgvPyoTd7tmEbh46CZQXEumMqWQ1UMhqxcvwqktbn3ZBFaigHKX2uLWiVt65iM0lwrpyIo2rxjyPmFlhKLR31CWxS5s/XOH7tP2v+pOW8i0v2DBW/b2i+unmU598NtjhbRvnvqg/NKwXMrileVlK3mF7a2lzTVkqCH971U9+AdCu11JBzlQ3NQjkmUezuQ9HxhIdv7K0u6w82eNzq+EWylrwuBfn0rlX0isgu/eSmLLCooKtEaZIIHtJSrAT1MCow9ufmbTVMk5oLwXE024Ga4sEsddr0mTeyWGGenznG3+VZVDLxtihJ0fOhfvLgox9gzE2DMYzIVO2cXPlB3Jjoq42PY7p5Zny3lBXS7E3AIVxR/elfOoR5+go42nbWbP3ds73al78NH2zTHUU2w5qHOVkknGJ59bgXXkzUeJW2EeUHhq3yXfBxPQmfRqG8HFntzJG0jUelf+buL9ae934p8nHP5Y3PLIP/vB9vNTkqj/U8DE3x/nrGk/v7ha5cfojye3QX7q4GklZ+HoiBlt1H4K16xC85I3rGPr7x3KRoss532W6azWOhnGGJ11u3UyvI7y1P2JYlTBqq3RSFUANtVWxVLA4hE45G3abt08vlZWgJmRJSpAxgU0VvDQ7kRgZ0dbo42wA3DFNoWdPHEJkLVaZPz+M8uwkytRo11rlynUv4jpjfrDYsrKasnAf2xVZMvnoLyC6VX1imoRjCLxcV1s/LfEwf/5U4rhHcBvFj8M+09E/JvXoe9J2V8yUA0ddAFORelQ7nzIQwSGoJwUXCPqgVB4YHi76/8W4FfCwCNDAPY0Nz2kN3PUt78OeYBP3VxCxdCZNj5s2d9ykZ6SDwKcAqGMa+qiP6EjkJSGNtBNuxIvdg8nbxFb7zdYS/PWY8M4lRaqH15s6vSzRko+NL8m5UNS/bl+i70/c/xu3aNPCSeNpHuU8Nth0L/rtob3rxf+z0Sg8FC0pt0=
*/