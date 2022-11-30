
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if !defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#else

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_MAP_TAIL(map, i_, P) \
    BOOST_PP_CAT(map,i_)< \
          BOOST_PP_ENUM_PARAMS(i_, P) \
        > \
    /**/


#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<
      BOOST_PP_ENUM_PARAMS(i_, typename P)
    >
struct BOOST_PP_CAT(map,i_)
    : m_item<
          typename BOOST_PP_CAT(P,BOOST_PP_DEC(i_))::first
        , typename BOOST_PP_CAT(P,BOOST_PP_DEC(i_))::second
        , AUX778076_MAP_TAIL(map,BOOST_PP_DEC(i_),P)
        >
{
    typedef BOOST_PP_CAT(map,i_) type;
};

#else // "brute force" implementation

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Map>
struct m_at<Map,BOOST_PP_DEC(i_)>
{
    typedef typename Map::BOOST_PP_CAT(item,BOOST_PP_DEC(i_)) type;
};

template< typename Key, typename T, typename Base >
struct m_item<i_,Key,T,Base>
    : m_item_<Key,T,Base>
{
    typedef pair<Key,T> BOOST_PP_CAT(item,BOOST_PP_DEC(i_));
};

#   else

template<>
struct m_at_impl<BOOST_PP_DEC(i_)>
{
    template< typename Map > struct result_
    {
        typedef typename Map::BOOST_PP_CAT(item,BOOST_PP_DEC(i_)) type;
    };
};

template<>
struct m_item_impl<i_>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_<Key,T,Base>
    {
        typedef pair<Key,T> BOOST_PP_CAT(item,BOOST_PP_DEC(i_));
    };
};

#   endif

template<
      BOOST_PP_ENUM_PARAMS(i_, typename P)
    >
struct BOOST_PP_CAT(map,i_)
    : m_item<
          i_
        , typename BOOST_PP_CAT(P,BOOST_PP_DEC(i_))::first
        , typename BOOST_PP_CAT(P,BOOST_PP_DEC(i_))::second
        , AUX778076_MAP_TAIL(map,BOOST_PP_DEC(i_),P)
        >
{
    typedef BOOST_PP_CAT(map,i_) type;
};

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#   undef AUX778076_MAP_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
AXRoBK198x74YaBY1uFAUisQLstxFZ8VJ6vbTEov5nqu21xqaOeWuZUGkbzd701nbxJz22h56WJcqGAFTp1+VOoQP0bObChEXFopxyKRT1V3MI9aYRuTZVAihnnoHYY7tT7zpDVmDYn6tVkoAfDTKJF5JGcGodq1afSva6sYD3LVhkURG9/aPnbg+9Eri+iwkOZRIrOk/mmvtm2OqJzk6lFicFR/OcNF0ZsQW15cwIh0zLfUPmVXYaVHR+aFL9Q/An9/r3pJxkC03fDWUxr3fYl/ORv/hZ0N9uuGq+6heo+In5tfa5WfZBKT8fdjPKW/0zwXq0FnVTyW3F9GHLII95O0s3QMyn5c8Cdb3kpXixNQce/i+WetxSZ5yYVnDWLm/Ys15C5Srp6u8uWfud6ryoL9WLKK2vIiHsWE5p7B+Xjr8nEZrTbG44Yb9+JeFMrXdtPJoAnM7KL6QazWt1/dZiBSaGhoJKSkoT/deClUOwv41nENirp00vdic3aZBwcH666A7Eb1VcIvY/GGF5LL/4on/TXlNeX+pqr4B/vFuKmO2WHS8bblXBpmMaso6Ty7UZu5N+beF2X7Gre+7heqTfMdm/ppksF/fFSD/DCyjoLbPp5Et2DJfhNRqVv4hUyUY7Pnj9pme02tWWm9bliF/nnO/NOJUuX+Dln8Zbkfn3misdZuFDmcLTq95MsAbNqQO1jPrrplXzkXKoRvLL0g7zbbawMvYw0XS0j5TyeiDktLBd6ThPMyWtsXUNdaECIspsgXgzN9dXXdL6ljqGedHB0RMhZQxsh/TjCs/IW56TjZ8Wpj/0nXOOp04L1pQkVW6I4FQDCh86bVTjMhC0gJ8D85MXralhS95CAUcHQ8+pQ/V164GM+Vw/6mmgu4ruPvsesa1CwsnC+h+uks5O6bux8bG3pFeznnomgHL1aMCiWcfENzx0BEQESrkPYXDdPymPT7SkBdyx0vj+v792eVy09X+8Nzp102kpKSJuQPuaazc3lJJIT+8yNdtOJ/uV1tFL52k5gvfnJ76MqsJ/1ovXedUsY0w1nzRQi0YmWl0E3NyszJuUkBODOnmpcLXtWqMRrvtJCurs69/zXtlNezwsLmqtlJzdHmmr/RE0QWVklvzDszsdca46FlsfIUK3++5/tQxpa3OklYDnXZ+CYopRy70SNdWfM7y/gjJ5bkfSmA7ebU+6zNsuv+dbEfjOjFmZbaxEA0otS2dHi47MbqGF+zmrLFZbnBOpvzYL4MHZ28a/mb0nf9TdY23oMZNoBgLO1QR82pQsaf3D9hS8TgQGHxw6N7w/wp3+qpWhsFjc3lYrucedjL+YWJ80cziz4toOcCtrd7kOiX5dmy2pEAwWmhr2U/uG/Pu4KiSn9ObGzoOQbYVW2ERREIOlG+K4ykbwZFIRIwD5vjDSxAK19snHy03ZMK/9B+LLx+V1qf56xZKbxXV0KiKh7Oz3c+JWBeC3uMNnvj/VOKyUjRWlCwsWpryzT2llZ8CHb3c0CWewWZNxNal3j802N1DZCodgndeC3Y+HMrA5Mi9oG2XfgMQRVtwBU8THPwnvLPQ8k7MKnf285rBjSYlu6TeeJGc2tr65wBV2fGcUVPSVYfjT8voin20jj1GZYpe3Em0iTYWdymDXK9+So5n7dtW2gIzsys+fNi1DL+urTUe1Oc44DKDx0TExN957RtfsoV4OrT6MO2naDdEAQX1gPAvWxMv2Bj0QTNy05u767b2isXf1kQ74IXT/b3T04uF16+ywPWQrdMgHcJ5CO9J6GhPaGl+QcecRpMpdNX59L+NAebh4clM3cveRfAJm87aiG3gxx+MfYEBGv/+Rr2oPuq3wG28gepqoT8ovkUJSNRWBVQQkL4UaVA6aWhif0Di4GFD+B5IiyRA3r9j5wHq9aGgCCIYJe/+8ULf28F+9+l0a6O/v7+8i5aWgo/vfemey3k/qYUFoYW9vUUDJ14dXXx7jcMojeP9QCdtUbFo2I+JI9GhUTkRJQMlvffDj5oy2uVihUqvIeUDx6W91u/zxd41go3ejPvhY8frhVPQAj/mjr+g4m2YqPOhaFRPX+mPMkh+cpv2zmBdB988MyTML+jEXzfo/P0LKCFoAD07X9ydgHtazap3DNpCo1spxo+cZMTkiFiv1ON3Ou9gtj1y4ug/K5rR6GL0WLPwRXjSNqh2eEKlEybBGJvNIjju+DVtYtNg/at3SgstxYA73dTl3Jwi2D8+4smIs/U+GeJD2y9dwYhZkyX9Y+J83E48ZfB8WbRrchFP+7vfpJMkDSHxystShuog3/Sx7JA+rI8MSnqEeJrBQiOqNafqwHNVKZ946e6f3nEs8Uan/0CcZ1vM/qG7fEVWuEoqmGf1n8fsFod0N+PebIohZKzkEnFJG9FLrIwYrxxZ9NzZ3wS9iWpmIqjoeUx1SeR+zMROEj+RFMtw/QuQuAOpIgAXW/VDoXzfQ3GOL5mmUsm3rJFU5vdUqzaCPR9g8Oq4EmqQFwtF7vCOshAqpJybGVTWaOU8uhBUeEaEr6lEHGC3z9kg4uv3ZFvRMQU9/ui0Ty215MVp548Cv7Hy00EHIZPZbLp8J6PXZmClMpEvthZ8d/3SDUBKoV+9882dNwKpH0V4qqRpKp8Dj+OyJRWeZQr2vnIpkg17VvxjKhYR+vNQlk1Gr7WMTys0CU7dFENlbUwz3sQbp+KFC95oDdoihYfrnn/hJjE4jX+5hQlVYlspzGtZt98ryt374Dru8QgV7Tl8pLubJD9RFGtzJ55RD1ls+sLjqdhks7IWQzbklDCmzDfxU+jPqYJFCNealDDuJegyVEP03BNKGGb5mqiZhanR1BrX/6bUMtos5hvy9iyZeE4rG0Co58ocYn+qd1sfP/A4fDyXo0lV4VTiREz9MNo0s+h3/jYKdulYVwBwiWRnGxvb5j76tRHi/4Uv1Rj8LOxkD9lUbq3Z5tQJc6QvtU99SJYnuIgpStXvchnwWPTKuCSY3pgLFXDE1V0KaCNRZ/UfeEQGxj2TiPsLDnfPmJtcHZUQ0D1c5NwQ6qzvE+6XG4q/RspSh3GV4T+FzKm17qqnm14b4r2dHK/kTTjyu4cs3+ZK+UsFvhATRmKVY67wLGG9ql+uC2jIiHK2cx0XOp7pxGW/RshDOkHrhd4EzppX6P3pQTXeCQThllN1n5/3NzfHz4eoGBkTIxXwqYoeygSk3ySNucef/e51u+XeMv+ZxzKT/wRZGa6md6on9oxWtN9C/+Mon5yQBTYPYaab4b/zXGbvmbTyWQKf9wWm6N8Vdhzg2dcSe9emxVL1fG2r4ax7R0w5s4Jo9UcfxhOhyh/C4xPVLF9LtUoyCBfM/HCNDj6jdFJtaNlzRjs8FdutRpNqoshTtWHJ1zL6iyqw5EquNurMX1zQX3NsWP4HPqNOmn17UXb9Ys86Y7hY8hN2ExUcJgRNuzcuu75CEBXpq/3MyOI7HZuYSFYoWhbGbB6EbcSC0wuL2eiymwEfqk7533pqPJt/wJk7NbmeK8cdJvPXoENmdzK5whyZABVmAyENzOp63XRmPNb7GsaN3x/cun7tBiNfeL06ka/nGEhE8jRLrQdbGfeMKb9NF5L+n0FsFp+7grXffVQuLf77jg48uz1K42DCUK6F4G6JtcbHSmmVwMLros1FuP8fh4jD4KPce0H/tC5xoH0x8/Rqa9zmwxA2jHfXYxNlvdYOt0YF4uUqcKtrQ0royE8/GOzvzzubjWsg+qzgcrUORuTz/Cb9ttT1OHwgQ8/yjTK3q/bSD7+q3L/drCgJRiZFhhoEH0yEsgkznNx3eMN/FNkZVvsarH6NecqxMOmWb138z//Bc7k+4nw+gWQilJyHj5s7rwjmsKj7kTU7WsXpOM7PPEA+/fYYw7MvOwcx+3mVpXkoZeclpTaX4ujTjSNi7DZ3WaqAEBPie2ku78uBImfG4suRc/I6jQ7Uy1KFF8PpXADDL/KVp4/OH3PrrzfhMWcDV3E7YePs1P8WYYygYkkjm+dRr4wTVKz7URB7oiJmzgrhwbL9pvAkJOTUc3FdkEp92+Q3ovedc/6d0btyuzvC2lDXQaYiLqD+cXWwFQZvuyyskIvFQMs70Hh4RYEiTfQpfvoCNH7u8TAb6cXcaEp8h3FrpZzFxbK2UpWlnVfLXdri3VZ+aWuxlLGeLFkBNPhvECQb69mjCA2Gt+IhCaDyauciFcvZcgsbRfetQkcUWar4QhmvpuY2ptopdRk3UpDYbm8qvdB/9laNU1o7X0uGJ3KF13AR36zAfhb5tnoeQzZ/plrESSltQx0EklUA4VW0HMQjV9tlaNRJ6b6KhqkYPurB/I9ZjI9von7XFD/In0lrG6GMqL6HG0pzxBPshtTrLibjGJgnk+ig3ZYYtWyppPI7pto/92u8a8j58ifPylsbGyYeXmT0LGJ5N69w83Kyqqbzoio3tKuE1gh/GukbO/gsDX4nbxKOCkhPt7S0RHP09PT0Miob2qK6PyDp9tnDo4uyn1WuWPV+/M9pTYuUVMi974TZg6pn36b1cOEK8E8EUy7oUAB3ichv63rRhTWd6YUb4eifcWDlSov2LQ9ZexV/UhLJqM3i69JgpxlrL5hJv9hC7kYwCfxtOT/oIf5zrSJ3kh9XKegBS3UOM5NN+A1qyYV69WNgK+Ri0LEPJESXfL9mBzGbxUNUieV7azGOPfln4MiIhrJclZZ41TjyS7tBBlqExSVQNz2ERHWZUdpnsxYtg0PuobJVtarnwRrVd4DY6ZU1FzEzAsf8Gao8NREweG+f80pjBERCn8ZXxoyqPxIe8MjXq1SMWBs6mEe7kvMXxIQxwIKYrvqGiTxDRZ9Ao33gx5wWKXvBkC6tCnmb9Q80xS+j8iUYL9jHfERje333voRLlBjOi0XDyJ9ie3EumpB+XvsjZIBHSqPcZvSvEoPDJfCbFo1MITqw0AiK0svDnuoBCehZOgPEjYKVZriEJVtkhWjn/c5yvoRmLFoUyywIga1xsS1EsHR9y3y3N/TKqzUJlKYoyvuu8sT5uXgaQNtKcVR6lkibxQndXK9CdIuy3RS++LFE7dUzvnn9g93/Pdfm46LDCc8pb7k4ZPzihWvOTAslgFTJQzt23M1KWhEsrtkrPYtL9PW1NRcXF6GAoGylbxeDl3k3xXpdbK2438dqv38PavzgzakrU2s5PfvQi7exHnXDmZZ9IeHB04eHhXlBo6atBTfl3FRx2tuc+lRBRIcL25+6OlRmqkoG/G8eJtzoZEr6TITNO0hTFPtRVr+Wlsl6AuR45trXYuPEdnN7G2rSts5f9Xn5uY2/YMwj49ryCoGbk8WZ77B37ydOuwwSSgdprN3dFQYP1s99FuK31Dl9l1Zjz3Qlrx8uwOUfAoOzGHlenLPzDFFKDMtd1eVdr/KB2xEd0au1I5RbPym5trObgM+hc6VesHQJFbGOehJg6ta4RypH8mirZi+6eFcdoHXg73itoc0Zqi1mVK8zw4ryGyZXh+RrGbs8itPw9X/0X7/FFXNMD9uuG0m8uod4Ro9vQVAmGNM0/1g2DrtbH1wqKZSXZdoJD8nVzy18jey3VfzVnlmmhaMEH11ROxAx+KHwvccuzl/W6odzWyAbkn7RPNVDuApCTBsNGvg7ztFb23Jj11v7R9ezL/ET8zc116zCxbl2Cr3x/ckinpK9NqmIzYlyKuCT+TGpXaKaC12Zr/e2GBt1TLN+8HS67a1S9GVe9wGrMw9svExMJgxHwv3dmhVMKMSsbiUcL9e1yQyWz/zMub4ypbamP2ve13dSH+D4ajDloSKHLAMyl9Zl0H4eyezPfYgENQdMjnERY2dlRMbh1qgfFcjAx8fA+3FkXN32IgPYENQqfcOiEPyHB5y02r5Q6zvHkzeJZM5/ZKqh5cj592dTb60oHhvEcQIN9RDAa50wM2plB34F5ewTkW2PubBcMrK+hzqG/BvBDDi3Kzfu7VrK0b7vS/JcrrOUxLHdh23dbbznQk3tgUdLYbEqWpbtkARPXvKJk+SEJAt5nL+pSmh0VaWGsG/obRk6wgtZo4PTMspKpyWiScxIsq2XZh4O5O66Y5hP3YF28icvk9EeI6+a1J8+D1b3vYtyk0yzIBLJ/VreMeTZ8GHP27u7qGtraKBQUFGZ7pubnwn3eafO+jUGwMN2zhlZBhfv36tpq2tauSChuf5UeeDGy4tLe3o2Njn5nfs7OwFduKbKplvj/GkcKD9kwKy/+4iChubSb6+Hzq05xmCL7BKOb5l7y1Em5+fh6xmDg+rNLW0NGy0e3l7b8/wYow0GRQeBDPkkdLPQndFCkWeHm8YC4nCHDoMnbqJb6QHXXk7+IUubvIx1mT3nkdyDvN9asw6vuHCGn9i9P1gLSpRi22IHTWOiXExHRqYfCNFp6TMzDpW7WZ5YsXy4aV+LG7qGRPVW04Xiyb7+i7WpBIcfTVELwdn7Useztq2HewxSkM26YS4OA2Fo5Bt/SmHf051+o+dy412168ZNgQC7nz+ObG8gZ1NZOZgp1FN5Yhfmxjti4zEL8eqdwmqbSWnRZSs7RpFf2orExy3Ed+/EyUjkw2e5PoodqemYOwCN0gd/rtLuHtPaiTe3r3rGTFm8+UdJlRt/K96o0wAXzqkKV+qRvoJ7U2+RPrioIF1+8S7qoV0CpjRs5Tp889nuj0ASkCgDb8Ayn8/UAkUioK8hRTA/1C/Dn+J8v/7VoAll2Pz+v+OnP7/ODKC4v/PkXKEfCQr7Xvo/z0yd1X9ky5NpAHjx9boMyNB4XFrh6w/n2kd0v99jiP9bOgXQpSl/0M//YPDl8+fVQy65afZvs3SfZu/FgpeMBQyMTRk4Uwg7slu3s/R6KZ9lj1YMYHjRpAo4NS7O8PwI//zxMtTJnG4dtayyxGNJYLE6sSmJ/sWl4/01YxNG5z6leQOmfhiNa4ePg7yh9lvoTs5Xdo4X4LeaIaT/iIStLQdJdiIc3N2LH+l5nYcKjaPqoDDMlg6Bn9p640nKJW7zBgpzke9P4tmqIafc9JOT7e39q0mjawCUw/7v/WxQT/mToCi/CagVoZoGp/F1zDfbroY9znt0X/sF4+swm7INWZeonY7CfH9X81Rts/G7a5wP6yAO9P9OyLDYefaCOE6ovPwWzfAqP9G5c6S+hT3jrE8N8leI+tUnlzRHQayszGEJw/r0Ie1YNm/5kCccxsXA/5x7lXiXipfnJYBtjp0xt8MXQtT/Nw5s73CFW22r6GYpznM0QFopAj6CvT/HJ8wjnh5t57eaXQ6FvdrsiXDYnzNxTbdpMWnn7yOOi/K7jPB3QxNbe7+L5epo80Xk1VsVVRLOw8HGC0cOnUqDCQydDoMzMh6nvzuOmHwsYklgn0XVBicGUr3+W3AA49t+96juC+qeUT4BR592MC3mEUs8eHhO08X3sUG4wJCkb7uNfI6H6xTs9BNZ+Zx2K0k2v9aJTuOsATKJnS3fPnKf92a1e33VrAjO6jrCwKli0B1S1gMy7X/na/k7ktIgvspzgGRW7XgxUup/f81C3RgUEfkDib9v4YF3GHD4A+n7T6NxK30MhNrrfEyIJmNK5hETshHtxcb0Y0XpDnh198SF23FbbM8X7VFzRNntPFO
*/