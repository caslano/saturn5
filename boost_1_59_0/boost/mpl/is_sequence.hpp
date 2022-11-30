
#ifndef BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/has_begin.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   include <boost/mpl/aux_/msvc_is_class.hpp>
#elif BOOST_WORKAROUND(BOOST_MSVC, == 1300)
#   include <boost/type_traits/is_class.hpp>
#endif

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace aux {

// agurt, 11/jun/03: 
// MSVC 6.5/7.0 fails if 'has_begin' is instantiated on a class type that has a
// 'begin' member that doesn't name a type; e.g. 'has_begin< std::vector<int> >'
// would fail; requiring 'T' to have _both_ 'tag' and 'begin' members workarounds
// the issue for most real-world cases
template< typename T > struct is_sequence_impl
    : and_<
          identity< aux::has_tag<T> >
        , identity< aux::has_begin<T> >
        >
{
};

} // namespace aux
        
template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : if_<
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
          aux::msvc_is_class<T> 
#else
          boost::is_class<T> 
#endif
        , aux::is_sequence_impl<T>
        , bool_<false>
        >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#elif defined(BOOST_MPL_CFG_NO_HAS_XXX)

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : bool_<false>
{
};

#else

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : not_< is_same< typename begin<T>::type, void_ > >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#endif // BOOST_MSVC

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct is_sequence<int>
    : bool_<false>
{
};
#endif

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, is_sequence)

}}

#endif // BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

/* is_sequence.hpp
rtM4FNE6V8LS7BuvwG2UkwbzfkAV5+fTQ3iBdnzSIURcNaYSb5iMjaCPmiyI/7dxAX1nyhG7c5zrjp9/D/45y82m2W+gidNIglqDlyqQOxyrRDrwLMnDfWKN79SBW933ik5xK3dpgvFSuqIiib+8eOTABS50cLz+6oXrCla85fZSVuGZeriVp/Tl+QHKRIfMtFVZwbX1fYWxU2BUHiwEKUhABGqdkoqKQrU/YcmSFUwLvucyB9tiRekQ9gIFi6c4Do7CSPbkqNGEFKYueDRiWcV+TrLM8mECuYa0nac+14PRrDajNZgNyFqt/V7TRewa18utAR2jEX2uaFK94ZbS4+UPcvcarhfauC+tMZqhIQXxSETMSfHskAAPZ1RnfMydnR3cR85kIROkO286gA47fk/GnRS/4hFctcOIKdzyxE+jRZUag9xj8ujag2ZasiDcTyPOZGmX/Q44IXErix0aSmIccpf+ekNp0cSz/gyA8xUJLSvLWxt4+WcgnU728Q9XAcQYqAwXhgfkkxBEQjnJXLJUBI1fJ4Rc7TzpoI70lGogAjecH2Wm0JUprW+LEGtiZPZ3JiW+T/+2TyV5IDerDiwEUdl5HiQItXJG5LPv1SgnNF+Sm7OCYTvhc1KgcLmEw0O8COzU0JMbUuQuGMOLidCIlhl0iiD+a8jnIA+i1m2grIQDX+OTdH095DEfGm+XzcNMgRxKVKpD8lr15IAdlGvXBdabkFYtks3cGQlHi9eH8IeOcK1XrWKBldRktdyRx20D8h2RD5tvp/bPgw/s9YfPldJ8QTe+VTpBmZlRS1qcDic4IgI/FFgnn+hRuFHSpdvT84n1AT3Q820vPt9hBNV0TnusBNqFnYopf10QqjxKYgKniG+I1x+ZzEO65MBRmV0ZkkvvINxsFZZox9g6WcFkQqSSUuHTlxZSskSpL64cOkzKhKh2OmYeXE56QukC+sJDnCDeCZ7QLtK8KzqLuXstArViDdyl861MRG4tNZpNmQQPrf7uYy/mK1OjVr7NzeILIQiZPg+w/UGaRjspgDJ3zQG647PtS4TZqGTWshXstvDJUANDsvwIbRAq3IBJxSaxNrG0q7xUW4k+DOVQgeX2jcc5F4/71+U3NDhNCOMeLbiYojDt6vtrnbXDOrHC1S4eO0LW+HU6G/7zPBZgmy4TE4TDRnXhakPcCLOZok61R3ZEbkDgswQDnvcSArLRjZ8ZIX0pAJQpnkiklhWDLP0Y15/9uj4CmE26NX84kbjEmMATyrbh6y10ylSY0ImsdQp3Zw5tFGSeh24IXxXEVEwR10pu55JDpoT2ebgjp57j4gNc2wiY173SwM9iAiShFhgz3qi/t29ni2yf4NvKnIkwd7kK+7v3O1v/ztZSe6raLH114kBDb6dBoGJUSzIru5nxgj9Uy3upvUWwaOKUOOul9aeYGVpFh6+DTcWPsxyVrwPwJ6I/L44G/wit087JErsl3PeZG/K0uNEMpHwcdlZmuOAvyAc6E0NEqoZbPjndF3/8s2hiSW+odm/pwimQK6krUf3nS+dLfLE7LcevI89TYnsc01T++Ux0y0LmMEWV99z0415UxoUdaj06E4Wu6f1BqQqzcRV+3CWm+1MdoL7NPMnylyc9teoAzlEHLhtqqNMJAzOtkUwowByCWj2OlBnl31gNO1OHVGREQgguyDuGskrXvObB6b95C+7iR7ZlLpg794WYgHcAhT9G5XwlrjaSxCU5JvjhQ5NFmgrv2pp/kgZFeKe2P4u/l1dUyDLuh3cmAkTGpo+p7k8ubEXfOQzJ/133PfnoQWrybF3OsEwJYPLihSjn92+VmoB8sD5RMNJwPJa9axKyJ/yxbLhvdi0Mmz6jiZt3MvJsYXfigfBRQjpKsijcV0+3+Hh9zSp3yAQ5nt4HhLbhwleHI5MBd78HD+VfaS9to6/8Q4vfAeGwF4bh9BeIjnDf6+RHl6gdUGQgbQ/JqKedYlaBSOMrx8jSnAzr4mOh+qDhEZi8JQv8wd7utqznrSM3Tyb8asCq8t5dapYEjNyKtRTSZis6agyafMPiRX+fsiHYXkzSbMTGHBkTjlwzAwNfxpPp2/jtJOdgVAwlSNFt3jUBOhJxy+UBYcdMTASipe51jhdAGrG/cUgFh0q+kG7dJgR8b2dC6vb4KLSEFdLuXy5fYwPOqEzQhWr5U6OMfOY7z+x9gPnJ2xceGKNDUE1kDUN1XgMUNxzPfdySVMCbE5tW05svIUUw3+K5q2SUCfBUCCr2fCAEwdM0heKfxJxFW9wqcNMgJ74Zfkh8qAAILPfTQm19f1lYaN702oklLoiRWwJlNGnWOUhRkxnR/f4xbChIMka3EuXttlJd45/jtxxOhJYhm+/W1trn4kqhll53tQM9N53wR9wh8MHancseIx997jDmPPuHNtfpNVkhp55wj+mTCylwpwZZ4iL/jR0irGYRpfHr3fv2g44FeTMthyNSvBPfAX+Lf2ekwLbg3Tjp/yZVAvFkJApp31dxowtkhXYOnd82hsc59am1otDYNE0Gv2ESlXUjYoXJTKmYnvdIdk+MmkD4qtuYEyTUKPxLW1ubNNta3Y3jkj/16uJ4XSbLTbqq/sqweWtdBluOps1T0vAYDwEWJIqAKWXXbThI7eTU8c0Lx+zRXpnK24bHYoKR+S8pO2BGp8ENEcn9yJpq2qheiiNaZB8v3LfqVFWe+QovuLxIKbjm+tb2G9uK8F5pm16xayJ8OIs2HB3VAcsvcchbtsjQwALqiYvw440eAC62IdAC1WQNvHBgl+uPg3MdTt5AtxsMM6iy7Q+mgz0OB64GdXHK8NJFjPAs0dJDNyCz0DAqMzGZC+U1svwcPkw8mZeRkvoiv4U9DtnkZXCn93cRAF0pHpNIzsZOgGawERwQjquPGyZMt/z5hokgh8NwYfsquJqRN93fErie0Ujo55Sdl4BDAlGslS1WRJ9PpIUH7xFIN4qXEvqYIT3UuoQH9T3KbeuCWRzy0+VH67j3/lTj/2cKVMQ2ytCjYQKi/F5PUc9sc9YLGPimUHyHPw5KVSfD+E0u/OqiWKX0FXqYvGuJXshlro1pNWd1FcEvqE6DwsQ1D7hUv2D+XMmQsKy97NUK/Xx96yLsm5c5BXhl+VkooGMYOaMOywvyqmwRuUzJ/BoegMrKm/cuNOrd4KW6WYVCIw5AdpX3iI9StrPrg1/63O0qMt1Iqt8755TKjYV1lDxfXXTSyH7X849gvjUup2BOvoiEL2Knq65GILaQeR9U4Ig+aAPt0nRMEBx3sT3Z8Unn+JCixOtvD6xS+a5PJh9ht0gUa5hoEQbTLAsDhe5JPGA1yZdIdmtVml7aqjT0NtreCI/T4SLifXe8collVwqtC8JKfAdzxUT0kbQEajTO3+U3D4mGE+Xi3uGLl9oPcEQYcIV6zGf2dUM2eegkiAf3H6wl447oIlCtw38qfdZnz+0FkNLJZ1hi1FJCbYLWdnQ4/W/X9iOLKjRLIOwoszECjs8Tf7Wr7wa6RZ0J5t4kaIVkFH0VAbpgLlnr+UsgLI+7oJKLUX8U+oWV0nMVxmXntFw9QX3HwnUZxiPcl2GoO3zFHYZ1eMo+P7uCY467e4dvgE/NiGSPT79Ounj1eojn9nLF3pP9Fz2sJk6UFTpKe49UtasT0ltM2AQnUJup090h3P1BYgdH3mDyE8OoGwIU6aqYYtRDikOKcyi3BsIEJcEKeIAo0+jOzgZGnEIZZp6B8A3/UTveTZELCRTw77BD5r+a7rmFWnNRYmK8Kn1+GV8kdjk9DiRpe0cjpdah1tY3svL2SJLuYACjvjoLzMDy4oBAK6AzzLT49osTh/DrLfbFhOA1P2/4BEbMJC8W1J2aWWC7zsV2HNQnj41LIWbIVLt+FmOChRhjUbKHkQ8tIeQSoH9dEJ6GOgmipijstnNuIV6r24qTeVAL6EKO//Mpkrg3Tjj0JJ/IBYAVAlUj6SxTyxEt0bve5fGor1c1OmwBKpo/CmuGHvWBcUr++9nv506v46S8PALemWq0SsO4Iz/Bh9y9DuuDZHzX4Nz1RGQ+nmwz7L9lMnefiPf6TCc/nWL1ufKNQuCUzCcGhVATtvWIaReFFQfNgICSCDyj8nTZJU3I7jizF4soUXUexqqaHIlBWW43Pu6+YN9TzhZ3HQFzbGQGXX2wMWo/OhhwRtRc/2oJMMqVFl3MrAYxrM1Xgk4kq5sTYx+kAPT6BIuWBXnM8c6pycXVn2xm/vSx+A0SMvVz0sl1epi2LH20WFIWiXTGxjip4boobCprX66YFfMtU0TB5ajuD7upNVqC0C6P3N19TzlgHY+we7pD8ALhIH+IZbzF/g5OnyBedQH+0KYzpEQSHrshjugQq3VxyffmlhH5/vPD+2ag8ddAvd+xVZxZXv7tTrdPNfcxo63SYCqLAYpMg4a3gSjmtAWrr9kBTBPwb9nMj6Zief3R807b880KKVl30XDG0/nueMsVhx9oc9eUZOd30N9Gv1TaYyenKGXh4zavtaZgGFb7bPKE6ybaNjcbl8qCSyEIVPLNq54KBja35TorWmFoOUETGeD3VWjoI/XyzZTs9Zf8tZQgXHuzd+Z7l5+UcF+6riKt92fgkWm6u/l1ikjdaXyiNM/GUzkKtZHoFjdqTbmmrk7y8WGQnWt7fhnEIDpZoDqj5W3euZr28rxrNF5GapV5wTN8RvLnipHT8tj1U2X7qh/Aj5ABI9xP2OPZpcS1z4h13dpqiEulHaLaB4GcqKxWdyv4jmgg2oI3kz8DGlmpLC2irQunhvq4upBhi66kXFbBD11U5Dmc0wTXjMoq+WAK+uXumaZ7vbDfuD/8egDmpqTSRTVudgTlR81XUs0Ovik+tSJKeJcxa3QhdlU+q004qeG5ZEppGBJQOCoDOJfxzZsWAyRtWG7fpo1duf9Wm2jj/HmzMhVU+CoqTbe/cI4GKXdU7V/IUJM61FAblHP4CcPsJ/66PaZC/mX+usdm8pTvdcV9evTAHQxnl0Ofl+DJpop8dRnsMTMNDobiODxo0bu+GdHMSps8XGWsvuK45ZKqZdcMvaXdLI3GmI4h917MgmHKv/w5AwBOMJi3dOgeBBvW4Ild5PX85EsLOpQb1S5FIqI4XY63L6jnwUNhfCVVAQj7ABK1sA1moTII0vciJQtLUDc4ss5vmwEZmkiLn5Q0HQ+Kf/Iq09AltvRiUSHVS9xEw/XlkQiMxK/pFPZG/Lw8/VnDF+Jf0vpphnSbaXr4uQkFoC9UofqBNvSz8lqR+pY6t9FQdIVZu3SnMg233AmH3ZCRTx/+U80N8nJDuxv55c55/kCUmmEQFygVt5PX8t5+j90Gh29Dfb3FDe7SBmTYrP8vd4wehx6McsmmUeqJFWcNBEcyReKWBEOBVDDyZTY8IhDkOke8cvSyPgWR1tS3Dbm2Jvm7Oncmq/odK6cXKCPdxHEaib17/hRgfozCoU+54VUiCo8itfTWZQn3LsEB300/++KV4ilX5fm+nQsUBM9Y2ZlwjvOJZHhmptHsgb0vFTYASNgh6n0v1ixisERaPkvA1OJUf8DsCx1aqytNs/8y6qeti74WzS9qTjy214qSWmazzpvVKdL0AsgcCY8ryI8sMlSf8joYwVqepqgZp6fS1P3QzN9Zj8YX0XOLQGi2vIoQZn6xT/k8hNLDmvM4H3EUY01112kOxg2gmKmUc8rJiNVQLADWSpNN07+y2iVVUhPKucki4pGa1Kq3IXGRe+MtvWhSExv3teqG+vXZaDRIOwRr4BN3eTUhR3toVC+cP3xSIXUhFfnH3raN1qHarmvfX9zrxkPsA08N1GMct/WGd8U3GIgBs0TtQTwzzRwn4HoZLfZbs1shIFvtiZQvCzrtFUPn31f3NCmfDMnjrEqfprX/37/SevyaAQ7cIQR9yf/2jASFw178S/8JvLzNSfHzaG4tafLTZCTdztGDA7xITnDybWbUYSJPPSq2Ssiyu8O1uVEkSIC6QoXaixbVMGeHENasRyO6ro7FjkLBjXo9FmR4ZVyxQ7/OUykbJo4QayyJa214Grl52LnTefPUtnB5b5mw49CCva0bnYL//XONu48WqQ2UGv43cRG7Vl122o+JWCi5MB+K7L1Ow29NGX/tm3Jnbc0HCi0FrYDwWfzKdyO/5KTMcDM/mTOE1vQtKTsZQDi6huNVAkt8/Pt6aJdJOmt3X+6KsWxJ4o6dLTB9sCZSXXbJdSaIGYiq2V1LvrUoElICJUG4sTceMA1tOctNDyWuBg8ynisubymf6uKBsK/KWI0hAi44UEQZExKyZKxio8FBoeYgE3BhhmQyJwX+YGI9QuS+vHCfAbLkLU5IC5wkqsZnXILO8B/85KJK6NbNifANSCEVEnB8h0GOi05esSh0LYeyLW6Jb0Mr5S64ryMTch3twG60oQURy2DE/lBzz3VoH8mQVDmhzOqrazBa4VGLoX8euMQyaU402ptqZtEEQERsDd97Fnz1wHKPe0aUW0Le+lBeRGPspFF9bt+HPZoROqdTEQSMdfMpyCqseobVRu5FAa/Oecg3DjofGH6NJbVwhRJBm3W3umLOXJGD9yHxE5s5JWQO/Qot7t/qmQLhleZ8iZWNuoq4EhMbh+A/WDDZq7FqLsTSmiczhCXFNW2u6vuN7Lo4tRtHm7MVDzZMB1H+kX3wENblsWcBlLB4jRCe9JPTLa4xjx8GkQNC8WtCgYiNi4ujysnMGs/sWKlL6bVKetx3sBTioScvm5J690E+0u+nQOBWZ28koliybw4YG1N0ICtjdOH5s8OL5V5Ep8pISoW+CCM+G2WSNqC8FI7HxxJjZPM5aRNoEbVVjHV6ggR6pgoVyNiNRZP9g6iY8/fj83NFL539l00s1U22ixdn6e++NOdJSE9B+ajJ1pSW0ULhG0loqEbAUQHV136tJmdWSyyfP060HD14ISyXR+rfF+KPN1fZ8d/iVTh+bBGzXzEF35e2nVxw+PfY9gaz88RVj4hff+hjvm9E272JJINEL6xUK3kNm+OSvEatiyFm41h5vSoWEgk/mhbSqOujMuv0YFznKbo/4196yNVsaFKM8Vl8nfbRMHzrLoHpKs5GFXpMpsspA/e8kjd3+4jSjUvpJU/Y/cOPLSIt7d2ASrVYiRk9dvk5eTQRHIylxJuyoQdnDeaG0VkIBBVvP502ZBfOi3uokEugQoXTyPDz4EYxiSpxdLSRz+ED6PERnom+nP9lpHGGpbRU0ARMg2RsiK9xVt5I9E3+u3ShEKbfluhpMssWiZTYDHuRdy5cFJJp2H5RKWw3CKe5l3KTiW6qVjPUNoneunxviXZ8yfJffsei4uzm7SXYYDUrnVHPG4UeQqw9pfw3mTo6xzj/+hk1Ax2XL0XA02FsCnCkuoUptyvOa30VFXcT7aP+c6vs04U6OVhh+Qm/ldBkN4Lqghczseko7hEosVaDb6+CvCZVqI1rkbvzkVzfYkYcJ1NwsgAyvryDLEpjpEIQUjHNs4ov9YXxJF+jwEUD9HkWe0HYx+VMXuvpTWarbYqZYCrp6r6WBSkftVPpzcwyMPqepM0PmmTAdl8FvCT9dQkY9UL8AVGZUWcMXzCAOU5T7nNvjq79bOEmwzJ2Ae4F
*/