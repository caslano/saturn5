/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_NONE_07062005_1128)
#define BOOST_FUSION_NONE_07062005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct none
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    none(Sequence const& seq, F f)
    {
        return !fusion::any(seq, f);
    }
}}

#endif


/* none.hpp
wSnoCPnPxWE823vAW8+JCzxuY3AP+O9nD/iDrvbwi7fT/7q7oOcn/9pUPfG3fX/KRLtvXd/XfDy7z7bMJ9qtaX+kVcTXO5/j1YV7buOnrw989uL+d/35N1un3vPOwZym7xkv/mTL+IQDvPHP8APbxw2cqp2TKOfr3cj54hzig4WTLOJ1vCDxmH4OB8AX4aWwFsbDl9S9iMW3Kj7X/Ya9iH8scT9+AsfBp2AC/CmcAvfBa+HTMAc+A0vgs/BmuB9ugM/Bu+Hz6l7E4vuEj1rEhxkl8dZiJP9YOASOgVfBKyS/sXA9HAc3wvFwG4yDD8J4r/3xZdrX02BNuuRG0l2qsX+VpFtlYf9UiduYBofCmbAcpsPlcLb3POLj4zuL8yTJeabJeabDFDgDpsFkNX6c+N1guEUcuNdkj/bXYSd42Fte/Gb27fIiTbo6Sde7cbuI/4rvLMpTLXo8DM+Dj8AL4A44ED6mlkd8UbCXRXkOkq4dfAX2hK9q8nfK75Is8p8o7SoBXgonwQQ4GU6Gid78xd/Dby3yj5bzDJN6Ge61E74a+/ZziSZdZiPp+mnjJurGDfs5xdVyvt7256M/in9C/Bako3xKHEjZ80z2ur4fDoHV8Fr4CJwPH4VL4Q54K3wMboKPw4fhTrgP7oIH4W54FD4BT8An4Sm4B/4d/hheQt41cDL8KZwF98EC+AzcCJ+He+EL8E34EvwUvgxbSVyq8+Gv4Gj4Jrwa1sFM+BZcAN+GN8F34Ab4HtwJ34d74G9gLfwtfBkeg7+Ev4fvwuPwGPwQfgY/gj/Ajh/DjvCP8CL4J9gf/gWOgX+FKfAknAX/BufDz2A5bIDr4efwPvgFfAp+BZ+FX0s9pzvELwLLpZ7bwiRNvN4oeLnU3wgYD0fCRDgKzoZjYSEcD0tgnJyfehPfBbrJ+cPhdjn/PBmPcuEAOB9Gwzw4BubDmXABzIALYS4shIWwCK6Ei+FjsBgegCXwVVgKD8EyeBwugX+ES+EnsBz+BS6H6Mv4J74ITfzc/q5+LuOwxLubDfvA6+GlcA5MgTfAHJgFb4bzYBXMhjtgDtwL8+AzMB/WwgXwTbgQ1sMC+BlcBL+GRTAMHZywGyyGF8NSGA/LYDJcArPhUlgIl8MlcAVcByvgJrgSboY3wWp4C9wLV8O34Rr4B7gWfglvgx2wxTrYEa6HF8HbYT+4AV4C74SDYBWMhpvU8UR8FHCc7Xgv412lpPNx/+M0pTOPT4cQeb9Om3Gni1DGKsQh8Xf7wlvgGHgbnAHXwXlwPSyFt8N1cAN8BG6Eu+GdsAZWwffg3fBzuAm2I797YEe4GQ6G98LRcAucDH8IU+BWOBtug5nwfpgDt8P58AH1OsIh5VlscR2ZI9eRG2ABzNBel8Vew33Y33GzpPNh/zhTOrP965FKSfeh2L+78u5B0v1D4tWdgb3hP2EM/BecAB2cZ5oCmAtD4GIYClfAc+Bm+AP4EGwr9XIufBl2gK/B8+BH8Hz4KQyDbdAnHEbAznAo7ALHwa5wLoyATtgN7oSR8GXYEx6Dvbz2kPfHpEXWGeyxU+0H8v4XDPKRLs7PdJWSro9Fuse0cdQl3UAf6Ro05zvdSp8uVU2HrJHz+UiXKekGWaT7vfZ+Q9L18ZGuzs90jrX+pYte659+Tj/T1fiZb72kG2iTbkQbhxrvsPJu4oshtcgJJHRTSKMxEAfw7xORA8QW3F/EGp72rP2yWfM1x6lf9+V0ci7kAGIVBzF0MeuFEE8sxLjF1vEQsxc3HhNxw2L3OrFdsA6R2Ihc3EiPlF9J3rCxOImJxd5YiRXF+vVl1cWUHXkfOYOMLaEcJeZ1Z+tK9LEUa5Q0sNywDi0=
*/