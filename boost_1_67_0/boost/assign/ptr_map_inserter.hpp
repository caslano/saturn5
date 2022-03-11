// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_PTR_CONTAINER_PTR_MAP_INSERTER_HPP
#define BOOST_ASSIGN_PTR_CONTAINER_PTR_MAP_INSERTER_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/move/utility.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#endif

namespace boost
{

namespace assign
{
    template< class PtrMap, class Obj > 
    class ptr_map_inserter
    {
        typedef BOOST_DEDUCED_TYPENAME
                remove_pointer< BOOST_DEDUCED_TYPENAME 
                       remove_reference<Obj>::type >::type
           obj_type;
        typedef BOOST_DEDUCED_TYPENAME PtrMap::key_type
           key_type;
        
    public:
        
        ptr_map_inserter( PtrMap& m ) : m_( m )
        {}

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)       

        template< class Key >
        ptr_map_inserter& operator()( const Key& t )
        {
            key_type k(t);
            m_.insert( k, new obj_type );
            return *this;
        }

#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 6        
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class T)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& t)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, t)
        
#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, BOOST_ASSIGN_PARAMS1(n) > \
    ptr_map_inserter& operator()( const T& t, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        key_type k(t); \
        m_.insert( k, new obj_type( BOOST_ASSIGN_PARAMS3(n) ) ); \
        return *this; \
    } \
    /**/
        
#include BOOST_PP_LOCAL_ITERATE()

#else
    template< class Key, class... Ts >
    ptr_map_inserter& operator()(Key&& k, Ts&&... ts)
    {
        key_type key(boost::forward<Key>(k));
        m_.insert(key, new obj_type(boost::forward<Ts>(ts)...));
        return *this;
    }

#endif
    private:

        ptr_map_inserter& operator=( const ptr_map_inserter& );
        PtrMap& m_;
    };
    
    template< class PtrMap >
    inline ptr_map_inserter< PtrMap, typename PtrMap::mapped_reference >
    ptr_map_insert( PtrMap& m )
    {
        return ptr_map_inserter< PtrMap, typename PtrMap::mapped_reference >( m );
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class PtrMap >
    inline ptr_map_inserter< PtrMap, T >
    ptr_map_insert( PtrMap& m )
    {
        return ptr_map_inserter< PtrMap, T >( m );
    }

#endif
     
} // namespace 'assign'
} // namespace 'boost'

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#undef BOOST_ASSIGN_PARAMS1
#undef BOOST_ASSIGN_PARAMS2
#undef BOOST_ASSIGN_PARAMS3
#undef BOOST_ASSIGN_MAX_PARAMETERS

#endif

#endif

/* ptr_map_inserter.hpp
ubgFd2g1xjY3VCym4CHDJghTB2xb8c7Qqj+0q14wOHcoOrolUhfaBn9lR5q3gCgnR3PrSEkGWtENPSRqaQo3CPKnxez9HNA4MyiDYxaJWgaP3CX8WiA9WE+Yx36YFbPcd/b+kn2Nip1Su2KHhQeAFjgiaCTkqvNQb8BohxsPA/qZTgeMZWGvPpNRMtDRoD431O0cYV/dHOVLE+gpGSjmvkAwAvPJ+kpZogXSTg29wdAu0m742T4YXisPpNy6rqcLHK8/IcOeD6s3JHGYM6Gws4ePHR4N1zW50TOv2WAht+GC3cOETwUiOr7Ctnk7vk6idUVI+18YCNZPDKAsmrXjMP4jXlTd5KbMhq/rSQHGpNpIv5eVkCeQKc4Ieq7MWHqLyjom07QzrfBgtYIVwKrdsD2b7VgAQkq+hX668RacVVFoL5KCPT/f44ITvZw7u7STdRCtYR68FKapn8PFF+dpxuhlOb2uGVBmCklB3obGDyCfCv0xvCWhFzJmXU4yW55ztlI7Do2Z8NfIr2rTp6TRPAuR6XEtqDoD5nwDzSxtUjTtkWlZQAxes0fad+2reSTyj4pmkmNpamt/Kg+uPypL/Ta0oNwbPd4s/tIa8JaS2SuR/+dDtk7x2OGdHLWKIP7FFiblntWlwhYCYW03HtWhF2+M+CSkwIvvemL5sAufODrMS8OCqixq+LrXXbl5kb5CRYZd4GB5MXxuwruCYjiaXsuCBS2yjSZmVYxEVuXlfSAdHgJCWZSUFjk0h8ZcJgPOlFbSwdZTyE5iMrekkRiFYWAhlqYBn5a9lrjJm5mZOcnCKZbdO17J7xbpR0VCe9EtfbpKFF6wpZn6rBSy56+Gt+bsnsvJKrkMbWJ0vfSFYvosXVwiQ2fVSWMfFXJs382M6cXLZyiOSNcyPUrnm9jSJJ9nXHNVYmqeK74o34NfoeoF2md5lvGAKsYdeODt2t0NbW0Gyb/CRb8q/ro6P+5h8+OZiHj5t/3AqrK4RY2Mv04I6HJG9pnI7qx0wlSMojx8yt6wfWySpaT6JJxPJQvlgMMWF5OTjGdqw/KVpkdyE2KpxtJakdW+k4lpe7BEfsT1JUL/ebPQcBtp1xqQhkwVCcf7umXPsq1bip27e5UNb6A4V6qxt4FN77tNLO25kNsaMAExz4DZj7Y24TXyUasV+cGM5s/dRCEbjcVDfDp3HLuZgT/jtcn7MpNGtWwIaQPWdGLh2mS+SGaNLA4kIWgviIRyT4FghW5LekjppB14RD4oDyRB0dnoCn0ih0qBL1CaxIrrj3O/zAUsKTmJEis6UFZxNiv81nUBmZYndUiO0S6VXlJXUbKXwaMWZXMwVc7Mv0sVSxnzBI/ApqOxrT3dxKm+ENSHsw48DKsgaAGOF5ipIlvmC+OL+fvq0xs/OggmnQEsBwS8HffU6kcHQlsvL9cORfyWue2nr8vpvJQYJWdN8LU93e8q0TSE/jXSnRnKy1heaHpCedn0fTkKBsZhOXmyTLmgfJZjswjQ2kJqqkspC13pAv+7TdJAOpIQHiVKN12cPDkn1Rq4owSWDGtKjulXe63o4aooaour78qY2czLpMd2mAOumPNaqyc4HpkKCfpONMoy+S2H7lA85sjrIHZ7JWEqDnYsQHsUQMISprbyuoeAvSIfioh8xVmXXLRl4pKsoKT1RspD6IeNv1YibatYfQR8Yzfw6e+8g3+sDYDA9mCIsTHT3wussHX0l7pUPBIiokYSzeHYNkQ/o2tn8giB/SE5io/Dd5h22FPiCg0hcyanXUk8pZjucRvwXw7+omf2myEiEhcqx/rruWe8UHrBbZd41ygrqchMZWiDmNgWDGR5fOAB9qBX7HnQDEF709C6+YUjDzPN2Zri0qZgr7GrGGTVOmKZwbBPK9AK2dpQsZ9xpTf9W6u0PcqwHNbWZs6tVNoQRSumjPmiSVEmaRFvxcdk0p5nKTuUl6DN0Oe2NOKs755UPaRS5ohfcpshbuDrzplKLbKYNR2VdDZLssowtcaJWK/FtkZ+yLS27jha0uM0jcmaCAg+NTLoFUZThmWTJmYzEZc+JISm/mERJJftCW4sZtHatcLjnWhjwW10TbPDqFUrcRCxsCKiK2zn7zBYdm03Itc0lqtbPZRLSWz9p1SSL/+sjchUXb6sqxqHOmsGeKJXy4KgW+5+UPgmGGABLAkpV+zayfKHu2rPfbef2CdWZl5hWdmKtL3PXAq7alMRF++12LYAXErP/VuRd0UkuiV6ybhASFgXjnTD38WBSkp0obDH/K5kS+DGMrP8am10xSfsfCxfWbAqSg7zys0wUbDu6smuO0pW4yKSGusdk5jfxIBeyd0JbfZ6Xdbtn4VgQTBjLMrNcDv/1UievoC5/WJSrRPaWDBFScVzqVNwJIelk6lvOcWd+/GlpXCCoZb7uJ6Ba56IfctUVGMSfQGTQ9sR1QqJGzfvlItkBDDgH54EXLDkAepZoFl5rg1HXXNKgSdObkssQGWnlesXGu7Qvqi1lYWnsrZU1FChTfifseJ/VbO+YttKDbVhy0Roah2vUsmS5JpZEix70PnFmoKvx+4dN0S2ck0VdXNYjgJkRbBtHJpGZmGLT4FlZOhM6ndntmOHPG2mNc3Up+u8fqKWdJlZxDce5EZ8+M8H1dMMx+qjI3g5/LzpJvvPeOFMheVvZivncGTj7GMRvOAXI6Rv0cM70zOOG1tB7Mm08xgxr6oSl5woiZ6kK3Om3Fjqm9oFz8OPrnhkuzJUltGK8kKGIyIha71OGJ3tB2fyGnwl9QyY3AAjvIormoZYhqw17MijrJc6gWjsNLLaCllxV6Omor1N/ZLsbmxvaPWWn0sqA3FUGWoiJISZqmtGSEwX8FxM3IPGB+oLkXVqo6XgVDaZm18bSZzMcwIzCSnBN4C21+RMRBEXzZSKlCXXRvrfMtdOpE7DBnGUo7CEEy002mN1TB2CBNgNtpRR601B1/B0WXLIhakPWmBjDoDfMN03XDfZPfwmbwAGLPnTvHITO/g7X1V655qR5as7clXSZGSkltQip2Mdl0qcGZd+pkyKL5IJMcxc0/ZdU4lZ7dnORvqvymrphdpt//0oqjm7oLEvKhdSvrg1owHL0hi8mzMwLbERLXldn4COvwZdABPCRqszftEpGsMO647mSfm61spI7t3FiSzs1R+HxOF49ST215Zbo+siDbX+IPfpQcWdfznJIBfq3t1YokA9nPMdks12pfxgNE4qA4OoTJRz3lIn9EOHKPGzvIlw8GubZ8+PBQu4HYY3qnrmYcAc56ODC2Igt3BWfEg/6xPhHybes3xlILEa5PysLJNtynh1Ir16i9E0KhI+fSfbH+TvS4OWA6xUglCK4gwzea/795aT4uyXxVXSygubfY1Yl2Frx1s0iizApyYY751sJ/uGYevONpspgafvQLcATfo/2fu9n4Wdw76HvvqvLONAxbByuGvkmVwp+qfrB1tdMo1bzDxQeOK+4HY1sPev6yepYrtRbFpxERGNU/vg4IUNVELzOWiicJ8Yt6MzH3WQQvgjbaNS3aBtWAYP/Vs9w3Pwa14SZ6IBaNewldeaMhHiZGe0tTRJMPGgPF9a+EOMtjhf6EgouUoHsCCwiH9HmNkPANkCqOi9yTYx/ZVc6Zi8ApVRJX5YqSyi5Gqi6C9N5luypKLUKFowhlZJb62CE/yk9beBLMC7DZpsSrT43isfZmBRb4OGmVZUYicWtcFMFoL4Fr8l2vgxmSh5tfmiU4zbZ75r9614GYH8jk9JAv5W6AD4OM4WmndNwO0NQFdKHkVjCyI7ovZr65BOmEuXyUCeVX5C2hktufDJWAKuvQCUg6Vrt6AA1R2j3j8Uoh9WARDeOQDug16DmAcvj3zonYhCFB6MwG22dZeyRJEPWT/ANfrlgvuTtxpnYS4tmawN95g4/tXgaeYk20XkoHGs7NFFDKIxSpaIiDqsNGLiyHivuttmrNiP0/ka3xfCLLPBxKTBU0X9yETMZy7zqGOPlbKYAXDqNIZxhR4coKyulX5CNWPnyZ8tl1PXSd+9n7QKG2FEOqUbZWuRp63Dlg84BBsB9M5WIINNnQJBS9Dn2f6BjRA7JZdelbJSNuOKHYHNEbCAovE2RrFmbUUGfyXWOlMHs2q9EtrA6/wKpXweXfbzWCVv4djCHBIW48f+Uko8hFvCS/EoP31Iif8xOlXWYl4tPDnZ3CCr/1ZaVWsxMwpkfTJ67G12MRrQjVW5/GPLyADmixsIdtlq6sPCPbdFDjRMpu3aCvVPGOE1EI16uQbrsSjVYQ0XmCNZ55l69P0ftTOVaQHYt1Ady50/lZGjAJA8dCTsctWxnSqI1BeeoosHB/5amDQJaBhRS7lh2/NbjHw5PnkwLSthDgb4JPPzHUz/Y+j5fvt3eFoJPALLpQy0FTeRzvyHhiL4+xX9Ycpi577GUAf7XRC90QW5+hf1IXeikkfUlsu6ygNqNL2cVMqY+jEd39j9FLYi0fqWvVWOViWIKAkr4iQtS44t0adDcMdIQvrOXznsR5a5zq2zL9e6efZPPgiRGK/stTJM8cOvOQ/tispI8oAWPbWeIaFTBQO86btllp1CyoxoY2tN7SRqV/YnV77tvdViq5paWyDIw0l8N5jW4J1Z8ziWB7mn7ps/QL5jjanm2sD6epWOFfBBXnwhKvOEFJCzNq4tZ0slXMSRXJwxR4aCWB0wMe4MVLClR64MK2J2YuEYu5W0uyjUNwnXd4rcE5xL0oJFVLuaMGs2BLugCvBBwLiVlfRy+jpWHOUNDH17siGgDcSRJSrOh+ASNYY6CvzGPbirI7MCPe06EbO7v6cRp4R0ZGqNkUOoDiHM0BRmr6XsfEL7szqYM2sHYBZLgYleBrOvkdqaJHXdCMOFx5x/zdKB6sDS5gdFtuCpnw57PDUnsFM+xooodog45Gc7t0uUX+2INfbI/ks+bpkdkjUoTw1PrMZPHtScfG42qfLZijS1Ztbs1yndZjC9aQh6G33zF5VWz/OU1M3Hg/4WZ9U2AUDdZzAEd7Opsh1sdi9oRjD+5dmyNdtCBD/wNLDoElqogsYs8J6SZatATSpXhMHbIRq/06zPLGvYGdEtwEpUhIPZoiR677MDFoPkwJ2qE7hQHE185mWdx5rIOnB/tegXt56Xo3WqkehQXiVHa6e3sqwZi2vZzdL1x/JlqY2AIbeuEXUzoyTWWdGLs2R+7B/zbyyWkQcosWPWVNZLxVR1vmSF3rgbWvhBA0YDYk/XAsahzJl/2geFHC4Xp5IaPsGrHeeWoj1RQzagT2W131KqdNuy6LAjoxWzLAxRk4wBkE8KPPZG7dYJioMX8bSAmPAEw4KsrFAnsk2277U1eX9ZwYZjt0Giaj9UGb6/E57q7BV6RxI/IAV7HfmqNjeGeiMEHTaswCE7+ch5WYp9WaIoc80eAz6uYIKbdH0IXTSC3MaVeY1mLfmxin9TZWb40Tzg+zaqvozIdBdT28/H46KptI7/oSDA4rMvaSreF89kfbpzB8W+kM0iNOoPOjJtxtzNw9rgs/T1yA3cSNhw3RBbwE3JU7B212GPH8vq/o9xy/spNMOWEwiFlsMtlLlfixAb9npYN9jV8AGugu0EMzUA8ffpCRP6YMDn95Wb2VHaPW6nUixp02tt67+zJ2+LZSz2J7q/EDGH3qIOzlDEKbyImprB7RTL4FKZ3R3AX0TQV/fIXy22F1HK7Bm8mRMhJaTJACnKrCm+ycnLii82snf5VTarve9isGvVdr2m5yISBFGpEcp8RDUzoBMEf9ZvxtZnGllr9PCRXOSTc3i18/wZohCb7dohO6J8d42eYrwndlmSWgXN2RcZ5LAQdYxyur3iP5Y25Z0kAOd8XovzEo4TAbMAps61obtA9lt0e0jo4CNA9nx/1xe4eFyEwPi/7gI/4r+yyHX0ZUYGL+jlaIIU7HRz1l3rCEMLC6zDGGzJWUBaYnEngW+KBt19XGdAeHfmnnv0cCNrAOL7dxIBR+GH3Xn5BKxJz7hZtGvj305Er++bBGRFAYxDtSMjqADHg7nXXWYDOIOyhqR/JxeZ7PsgPBgHfOxHZFw9eTcYuVbpUYxOad5he23I2UHuJSg9X5daeHTzM908ICdv3HKSgOO2cjSwJsZohxwMWT0TghNPdnxwGNo8MBwwk1yqShakDKfaHHSo/gxMDAbE8XLvgcwzECQ8O+zRBrlnnTF8F3hHuck/mF7lr3TNCFwUjqc+ga/AX35vZN5d2ote7Lt8W4E4vY7veqj2vMiQC5HytGI5B0iM9aJpXB9FUefS7CKj8+qU2UGPNqE7X6q4jyzNRHTIlJyyfu+IM/CjJa7Yz8QiCNE1gUw74q91aSFj5whGz3weMCZc03af1R+0xN7XhDoQUINEIQOOa7k482xpgeYgK9ysCYvfzOU8awI/IoGKczrHiE8/cio8GaJC1kmm4A+9ozby669q5/Svhgs+w12BqQ6Pn+yU8zt59zvx5QRwey23AlB7fzvnbc1QDf+hBqKjQ+pWAIgqgXfys9Cw9nX3c3kM3oAVhu6ECEcX3KDOiEUm9i58QM1RxjGs8UKAi2EFKzfTinUB6AKoA6AFpr+doaLW/9P2BndBy0LV/IhGtfE0/p63q3Ox9mDGp8mIMolo6G1jKZ01wuYCaL0GhQ+kBVI/v4NkcOXDgENRymkC1anqnDsUaHumqNmMecqUqW5wuUoUp8f5Ih05G5IRe837Z1UVPgS3rmhZWB261Yw9LUvfd8a/Y6ops/fK2eqGwCSuYtvqWIbNIo6kH6FeCo5kqT2v8Tzy5dRIeehsAOUj1BEa6w9g2rAPFeZiK/8PxLVsBTa8TcfWWorqDoWWeqQOWxKDtWziJLaX921awX2ftR/AKqliHJNYI5dnJMtLi4Z0YFxIl8ViJG30J+mFI1XSgk29QX8jDt34rUB2vuIr9dFGK5nPgN3q0+AwnSKoEKJT0TJ8ylRD2FlYR8rRK6M6Lf2BstkNjV5gP3jNJ2qY3RFqqUQlBAUoMZm8GbU39qTfA3+1QncK7utQmAei10X5sKw22MtTif/y4fI958Ut+QNMKuLI4NlJ/bk7C/O4IQJBPR4kXOvOX+PLE2UjJHPdLp0hWhGpf0R0ZG/HY1PdLDC7c30T7Zf1sxWOkES56HksCruXwUNSoLF68qqBKlYw9EtGX3mggitYC+lQPfWoFeBcRJUStSLESvzebcVda3TbeKmbEJvFEvn/6HrgbZ1ikddCWPZFkFFzy/qzl8Xg6c2bi9piyLkWpWwLgJyUcmD2gGPNmiT3ANOADiliZZBvj5aHzVZ6Nbva9OJYi9S0Ql8XnUXGwXjliK6R/a6vkKqup3dZXXW5ZaErKkRtSJfTKRox2kD0m51LpRFyJ4Cl3BR0qcmvrbpx9/ybACP0Tlv/WNy9pR8+ERFAPaokWoWycLE+ug6J0LXY/4gQfFK1crvXXilKQmStkufiksEQ2fODll9zNE4Ql6p2ZDkcXbcMIeWaMHGY1eq540Fex8Q7fQd3WfoWENL13gV0e9N+OAogWbqeg34DceJRJPvsuHCss27Xqa7dSD0zorfIQGIgyG9CuEdrWqMsgOoxowMdXrh8TF+jA91/+X8EmLS3Mzrmv8Bpfsmj/PtymH3u0AkQZAeqbbpuJf3LfYpNI+uWJsez/IzctLO+mwg4puBDcnrnAtY9Rh8TQmb4IcXiX9b1uEXuKRPZxGjnyblrkRB5Gda0Hs1MwLj75BuArZJ2WpTHnNOyrOMrfMO4GVGgYOnPrzvX7XJmXVCj/XAl6NaXg+BXeqYd2z4ymDG4uVSzna60COQE4anCJYzGujeMDpDuf5JZsyz5EEXtrAZjDhxz9Dl4OwGfQCuHnvUVtr7x56JetlGLu4kzuIwDH475b4ghAT6Rdfansxrvl4BHHnR8dq/8WOLBH0+9bWe/p6tPQY5T/qwmzWWATBnSYQxvXHM0lVis7EPjO9KKYotupD+SyPxK7LiXkOhLxerN6GtY8OspsWRGnBwpxMZ7xpBOYTPDVi6DT9OXZbotFMJUcvxfs0RbXxXlZvbjjHxafMz1RPOwjR/qxqNZxKHTqTLTVgP7dVgg3JuJu2VUfjY1HaxiHiDUHgsx+tG9PcpW3twguwlONc3ml9Ufdr6YlOosacwuOFuIBOeiY8/Q9K39yGcYBe5KZ1gthZBU4SGXt/GWZFl2sxc6k0px9kCVLogK+wzvKk7ats9u8VN/qmiD/7n4tWyw/B2x2AYfxeOYA+M/YEcRwGrGQp64ICOB1lb981YmnfhIBEmHO7Sx91TFU8j5BivYjmDwd8aP54JdFAvPetonQgG2vqqz3e7nX9q0tLn4qR7QS78MyVIcDszVBz8Zo//dJDtl5EtA2LECx1rxRHOCElU/q2/2xUr3Dsl7dAZepLfiH7qRXNS9khad0ettmORsczJa7L0lhisb70crHN7ehJe06zfskJc2z46ZC9ITWN1/+Ca1mSkHdI57XKS1wNPZH1ppouNvhhcmO8aif34ib3pLICdBlHf0zc3636TurjFnE4X4ZxaxOueyijcIqQDPNursD+PmDXNeTIRPk0JVFPKU7JXEW+cVlzYyPe5Pnmd3Y8H+NW+QlPnQzxUKLa8yvrPDv2XmIBYwfURkxVEGFygZs7KX0ApMQlR8h21hsrsdWMzOcBKty9ycR5N3TIaZvKpm85j0H1zTBUvFMmZnx+EDln0RUHf0877y3oGq59XzHaUlQuAT9hbD57kgrsu6QLg7zXpnl+UBgKuRe9/VHn66n9o172bxxdPjDCh9ccPn5OR60+XRDZ6jBYsQmc3mDHqTg31rI3D62nwFmxJ/qNWJ+DuuNLt3ZSsgRWVyv5rcaMB75ES54zvjxnQnW42uxLUTqBvHgEJGrdIK9jw6PzVAMxfOhw5CJo/6ofltDPgY+9OXmpunkbTp4VEWuV8w8MTYbFkJlpVYvKvdviJJWNZE6m6vXph0h/gVt9Nzw2es9pDZwuNimNQEdZ2fO3mw6Ihqzy56mEyPXE3cx5ZoVOZ+OVfVzhCeIDJMcXXjYlzqpFeYLcwIjD0xlIuhadeVm2GXXpB6DNwu7va9AIGtOxtfFgXXrl8tNhxPQUly9Vw1Y0EmPlnU3gXSmJxXv3dXeawITeyMgrIuonoPastY7b4=
*/