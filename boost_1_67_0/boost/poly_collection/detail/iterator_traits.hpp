/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_POLY_COLLECTION_DETAIL_ITERATOR_TRAITS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <iterator>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace common_impl{

template<typename Model,typename Allocator>
class poly_collection;

}

namespace detail{

/* (Internal) bunch of traits-grouped functions for const-preserving
 * interoperatibility between iterators and local iterators of a
 * poly_collection.
 */

template<typename Iterator>
struct poly_collection_of /* to be specialized for iterator impls */
{
 using type=void;
};

template<typename PolyCollection>
struct model_of;

template<typename Model,typename Allocator>
struct model_of<common_impl::poly_collection<Model,Allocator>>
{
  using type=Model;
};

template<typename Iterator>
struct iterator_traits
{
  using container_type=typename poly_collection_of<Iterator>::type;
  using is_const_iterator=typename std::is_const<
    typename std::remove_reference<
      typename std::iterator_traits<Iterator>::reference
    >::type
  >::type;
  using iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_iterator,   
    typename container_type::iterator
  >::type;
  using base_segment_info_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_base_segment_info_iterator,   
    typename container_type::base_segment_info_iterator
  >::type;
  using local_base_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_local_base_iterator,   
    typename container_type::local_base_iterator
  >::type;
  template<typename T>
  using local_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::template const_local_iterator<T>,   
    typename container_type::template local_iterator<T>
  >::type;

  static base_segment_info_iterator
  base_segment_info_iterator_from(iterator it)noexcept{return it.mapit;} 

  static base_segment_info_iterator
  base_segment_info_iterator_from(local_base_iterator it)noexcept
    {return it.mapit;}

  static base_segment_info_iterator
  end_base_segment_info_iterator_from(iterator it)noexcept{return it.mapend;} 

  static local_base_iterator
  local_base_iterator_from(iterator it)noexcept
  {
    return {
      it.mapit,
      model_of<container_type>::type::nonconst_iterator(it.segpos)
    };
  }

  static iterator 
  iterator_from(
    local_base_iterator lbit,base_segment_info_iterator mapend)noexcept
  {
    return {lbit.mapit,mapend.base(),lbit.base()};
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* iterator_traits.hpp
por3whQHy5g1iP5bqpIQAludT7bWPHSjlZOa05kA+twBFK0Ra0/2Me56tMHpEaTscb3Lsb6bowVMbWrKHhH7WSUging/xLTE1cnqZ3nKZDXbAB9AkSD+961SppU2NmvEoy7LDrRYcBG7diKDAtmMoTmY1VMwfwn4656l18STtQarBzzhtB4nyn5x7KPDfdPLKXOiXIjyXCbxvNviTu0fP3nxYe5Bc9WrAddJSUD8ljQdlbkDnkH6tlIbDHTZslFnuNW5cku2IgN0WJAu3CdtTkl4k226xfDBmAm4XwYKuBWMLfDOKbbCDsWvK+LND6qc4kl+6C0OSTygzeZvoqSk5IDhyINHvIIJcNepNaSN0+5He/SuJMY719+IOr/x1myl9t8ZQ1uwrINFZrmvL/U7sC/LhCCrR9bQ5ROnNvSgaGa923yIHANVKKzQTEwKAxaXuWkqbFVBXl9LyDKMX3xhDi/iYNCvVhLCIAOsqVf+aBMkd6hz2Xieo8+6/9Ua4w5Q5SLDq2tSD4FV+MlGnAPliHCyrRDMHHU6S35mMCs3vnEet6q5dE/gBHlry4AcbxfUxP28Wsu03JXFxil4g/WirMxK/i5+n0LzKy7tvWAIvQKfkYoMaJKzxazN5A/l4fS79ylbrDseQ9dbSWxV+MtXX1GiKBTw5Jj79UjnD0nUyXde09m9Yh3uuwatqDE/ay05/aRXRhjN3cLP+M5gF0RxBnnZ2b4dj/wHjEWHJ/2ezRStunqurth/JyFpSZjlSX0025Miwa3sFhNEVM2xmlYW3nW4q1GuiWf4Ht50m/RqH+VVpQpRR2qlC2SoGAjoS9HMP9wYZ5TkMX08ePgFG/fVqE9WowHU/QZ3MuMDOKz/8WIt/0c6Vwc2J6Z8FIDBkW6QX5W9JRwTTrC/0sR4EGxuWFdV6m01/Poj+Sn2OOI2c/nvLjyhhNltO6capKrJMQaJEbuG1Lqibkb94EArtQVNtRZUWQDFS41/fmLnuEpIdDDJaxzPlgARX05VsJCgHl/A2VKRrgmPKsM9AbAmTAVDyb/N3I7Kgu6I+KLeimZ+oA7Q+IKpQfGMT9b/RmnbN//NSWfJ7YiKLE+Z56LY3m3ZInLt0wnNFm2HibScHgfTgNBpTkFQb5BlWV5ovxuzc0Vud1suZ7sB+HCrsNmwbFSr/yyQRV2VGNeiZggPY0COmJfBSMJHjiyfSHGSGdLxqJqbu8VhI5hzUMSPq76G01iH/ftkLSU5fbvyAK/BiYCIbCrQ8xMq4bcQse6zBxIW82h9Oe840NH7CianWefxp1FCvSP45FVibcz9EfuJO66g1qIZYbv06rt0EVDRQE0e/Q0Q0dAcnjrP/YyRGrBHWd6CBL7XtlAeGyH72zj4gUdhy8Re2iSGfG1B78yK9UKd8fEqyQuOlYOIkQ7RLMOgWD2VtgJjdc2mmeMm8gF+1Haje3IHRG6hT6NT9PdsfjYYlbVYDVa0BKsW31yAEivYCOYZ4OAqvcRPMd9mn6cbpICjSM/nPOJ7DwbdkYVieErlbfdc3PBg3E42T6tEkBuXKu3wQC5T6EWK1ptmPYGwstqEeFmAdHegwgD5xDr+ckhFnB/sxgnT1HyU5U2OhLpw03meMPyO1EFdiEeZG//4ITQEqL4+q3tTFBx7+9gvfmmpsSRmrB2DYR4FPURpXiA7nzmJrX9cwUcPUtFy0dDLAaJFHd/DU6KRavEsFH85nR/MQMQBmu0hQR9hWB3Pdb8TEtm1nt1qEPyUMqnQnIhfdRc/NtflkKFgpOU/mepOkzBMW5RmJ9o+NhyX/QagbSK2NZ0bYRAFQYZzqNJhrJl0/rObw3XD16f1JN/hAff1/Esw5Xdl/OmwjhWv/Uzj5Lq2csrO6oH4SCevH7Q8Y8O4rEWUZfACcol7V2himlW5aAXMzXMylYVPivPBheg7tBJ4JOXf0pbqBH3tB1qaixNRjCfovEll+hUgTf6Jsu+ddXk1ZedSZSsCisleU5xjjmsdcTbpa6zHHQC/LK7xtdXWHVnPYMzRYT1QMtpxUs95LAfC9ygn4YgHqmEPvYW9CfWh7Rnhoa0YEPJ8U5Djvd7KPFFhpe61aXHp9WWIjDPSSYPun1uyBBRBC5r5skRZ3bwXgjOBJLJFNbxI7nQmHmhAsZEdKdKQpdzbeUN7UKVXClsLSCiFkph/Ec0o7N1QNRPM4jYyz3oeA2BRl6Tp5VSPZi5335p3+CADXYe1Q2yweYZ5m7XTzqiXLqlf7E90JdN5ah6za6XgGkUURnUOzKLJA2rheFAdQ3WMOqGg6vVsSVCUwFI+XXx0L9IRwNIVhDrhoOv07Bmqs+K6eFhrEcMaSAbNE36het7/JTbDRJyX2lrz6ZqgJQax6KAz6gDRrXVmGOyQVjEwE+e51mo1orqiyaaXwHzllyQE9Snz7vs15z3eh/lg3GYZBxV+putQkAwTEVX7LgLOtBzSevZ6GPaW5/QrtjYXVcBAYqeq5C/a9I+RiKuG0tBR/Rw31Y/5rhSjBSA+coDBaD+6cvgab1yt33lp4i4Nu/Q4D0zzNmQu4R4Flg8MxvqVYjJD2WCaUkpUcoaedY8zm9jqxxEwTZdpIHjvL6Mm0Upp6x5Hg1YVnzLNbkTuuP4wK9rcP3s1OirjH3q4OI5eVGGLigi+1I6XglG4vXoeRCJy3zIiuJ/N6lmOP0wo5vLIUhlZy9NZcd9RBtm179e8QA581+q+ZBHc7qqLAOf7scSy9WYg70GtAYTKtjK/GMtg5MYjeMNjkmmSUZZJ2G2bnM58qcGP35kVzBjRHXhHQ3fuf6GzjZWybLaxe/7mg7FCFPh21qvB1tvvFgZJJAzrrYcrgk2e8lraLGlWOv9sBDOKNsaVrA9ekJgud6zLhLFq0MZQsLpxvOBIG3nXj7+hjvNOy2PTgLdmbKiaZ2M+mrguFGxFlIjLUF6MjF/BNQbe/tjboBHggz/npnIM6iXnSUUjQEhDHoT3WfAmFGpc7dEIt4VGS8wy3umwi4kgOC9y7orsOpRcjraDWBAUB5Kg5uuYHFS47HJVidql7EdGyNVovY9okllsARXm4VbgZ+XnWVbj2w93LyEg/ci1tH9Du7dTejhG57zxw7nwNiEoOd0Efzf3JLRuBjKqplXMlNtQKNiC5jhbB/lK8vuZdaa3lcjPQ6D+FwA7/H61IubQD0RiNnHxkfPcHLVfbCUcVDZ6MMAHE4VZ8STU58GYf1lRsYYYUuHWdNDdOf+SpL4EIqSH4bapnNlh12i2QLOda2x71jnHROzLtV3Y6/6gV4LnUlAQlO5YnMF2y1CsTW4KPG2OTkJDGF/cFdQiQckTto21JEbdKj66usgT0OrF2sVC4euvO03BO9cqZpYJrzv460k27+rSgxPIx03zRKz2G76ugcqUJP7MTNKMlXzL49cq04hqiCYbPQJzBCgjLLGUacZhEaKOGiqvqo3nBbvphGoQssmT2X8n+GQhMqwt3T3OrzuN0an3n4Eq9QR1r3ZoiSo5k8vPLni7wxI8T+yPdO8P1qP9WkYS0YZ4tQR4sNlEmgdH98mEUfaZeOCxuD/s7fRlBZJHMQXFGJTBmT9y5Ct0j6f2GaaVns60/7pGr6JYE+QI/DkkLeqHUnxEKq5XrhUU7gtd7hd0vL2T4OWdbBDVLC6G1PLVp+o+cxNPpIdJvIaYoXfK/Ru/sQvp2spFlKnWZvnnRNNqJgGsZ/37CDDgGVU7N7XhAFZ7CaVnvHskknQlpsNUEwT8MEIuvYdF5trc4JpSNlyNBpOFrm333Wrmue6Yl84o7dOdOce1c1d/5PbDmXQe3yU73BQOpxDtoDdufOvlRhjyr4PMdyg+bfU6IAVdrYPG2PwEfc4Q44XrgqioBc7KN5MF9bes8hmA1HFjlCtm40Jzvi43ty+QGCpi7zHxje8H9hNkSV7boSMYKiMh/gMOl763EBHkCqao5XJepD80tR2kl/pVChOVj3qVGPyMu7oWEVyhQeokFovBPZcvRcr+CSmis/M4cs0NfWjrwV0525iy6Rthv4rfganvAYMthkF8Qo6dHOTHk0JZKsJbOTrYvxuKsuKtnkylJMNgWuVK6Pn5kz1/gr4HwLsBU0jNAgyxcPEUyGKQMt1AVIAlYs4h9ty7KOh0gLTwPCKxhPtnhHJn4Fvf92r0nNBxyoKv94BbARtwwbeDlaNK+C/6cF+3pTrRymzfJ4TyVt4QNQMp+l7w7ZWl4UkhSh2j0Kb0yIXTrAV65awPkiiOivANVyRB53nq7otjml+PpC3xfX23QRlauTfvgh1U3NwOvO1BW551Z2ypn46msAbCmw/+2qRj265nrJXP2gcET1QuifCizpXw/tT+rxH81dIGfv4PnukzUEcZ8u6UoflqeEjoi+yh6d4y6QU7kKTKbESskWju3YjRe4xc9wBXVM4vQxvVljgogPTA958f1C3bX7BCGtO9ewqaqlOWnXAU96qPc5zHL4Bs9/BdaY5ZfwstnItPkbNKzu2ISRLaxUvvccq5MnxjzQD5Z1Rk8dFCTeVnVXBN1cefEA1TOZab/M6vQmotyzLuFezXC1R6g+m61MU3msNBZnPXduP4YtaFl2VV72VqzBIw5UDC9YP/6o0eteJ2mwPIpw1n0lndEQfyvyaBSJQota3W7htKkugX57Kz2VPUuxgW/fbOoiKN52tIZpONj64zN7caS3Vnxb22HJ+1qyqSz+xXX7y4Skdv1uJCqRTccGC/BCufklTP388vDwuiPbZ1Ve/4i1blep/CAL1tg8EiGRdDkqumaR18DFnhJWRCKuj3Eisf3VA17vpXht/HVcDboac3F8VZ1tuwUrzXn4MVh6SuqPJjfDFDMsIPo/9mK8BiN6AaLE/T+eq/BKfX1DfO+emos5Sq2TS3Z1JnuY2nYaiI65D0rxEQXF6SZ7wAHosMQ6Yk0sfY7HyMyZ2lTmAK2EOqYMkqlTPb2a8KhtJ246wvWLsHKhhsPn1Ciq4p27hPTLwb2efH1vIArWuSEkBJzrZ3rqjNXe5npQGtoX7lHNENmvkzqchcIlClhEsccPLhcyuePMXXixIjpNCxilIBejlqFoG4yQ9G20GY3kdPhFVYYiJB/wWue2acHOln0NIfNW3asJMYGl3ShuuHO8EdfYN6q07Y/8z2cAHDomfvWvpeUJHPiQOfMv+TMBU1AFa9JCDL1X+jmAyDK5gYfsu50+xgbcM+TC3dm9Lh9/MmX5a26takp5Fy+erRUBl/wnWnlahfSGnwtqrDVp7yMRW9rnbZ96C1W5zue/qLAjPh8TDpOcXwCOdIqg6NbR3BGP8AugP7mU74ss07yk0sxNxOu1Aor6WKEXXpg94L0wnYRdfN6ritXqlMamiJrYyZZq4ghNKdFk8h2Pu2X5ev9bc2ZeL9NpY8cBKHq41cyE7lcZyDhVMEZfKHws8beY2FwO86wBeFjnecUApGgQ6TDLQF1D66jVKUjNZ6+Ou/GNDNlouJyXvp380sdoelxKdNuCDKbaaWXSNhSfnVobdMXIzQUIUnpkFX8Ii84el4LNbxpwpbKnvE4NTP9Lr0zvUB4Oyo/PqoEjKZ+CXv2rciR3oS9Xey7vnwJf682rRN4lQ+dLle6D0eyqlO6r6et5/JcxZdXi1R+PIgNqxkW3QGPd07qbR9a+QBUGA1z+7rjPbP3TqDNfbQ4lPl/E7ozPC3p5WjC2QXI4vTXnBXnsZnmF+Up0Kc3no1VPwcDSgAhYXYxqBxXMjpuofI243MMsvwJhETBu3GLkcUl0ZXF/QQ8W7rcaGi2kY7Xa6zYn9aQjiyB8czOJ6w1/ygoozRYr3QpxRnt2OSWzFAKG8dJ+9Rw0983Dmytup2ZEJcuxW93ysjCwlZ2nfT1WxJfD5fggqzneHYG0AatSqbVo/DbSAwLjHPLhBfmr0frKlPHD9PnDRXXb9XnTprJL9N4d+/NraUJ7ufC72eFjgA2+MPTp+3dpoLh981Qx+rnd/at7kpezHkPxtlrsK4JnuFdFz4X7pH5EsZrsALsGCylYutcrAwhTBaWYgGMkoRsTLtRGT5cmv97I1gsRaFUbTU+Jh/xwqaRL0SdSRu3SH/sR2B5TALn3A7JpFGVRh5jKzQ8gEdFT4fFrZTJU6KkldRiqRGGSeRM/S4H3TRkTcOxyjDsCwKw9pab2DbE7d1446yqoTimnG5UvSQMUkMbpMamaxVqZJYOqeRastPbIWVx91BU4dJ8Lg0d0Uwtq0jsyiMgJ0PhBPAVwqE/AtXXEHrPDe9Bf9gSdHg/s+BUmazhmVBPFXvQ5uzIQDiP/zfQbjZG44MMCijzuFQeKOuAEJG99sDtU6v1xK13ihBDBndNvj6SFdyo66MQk+o6sKr52WXPpNHoZEoOTrWJwDa3bb0Djk5zwaBWby9zmL/PuCSjXWvHhtM+TVIgYSDTTx42TDFmCJzzlHw8tUTzmUhTiBYwoRwpqZKyCROXENLKwG9sgIXmTh4+GpWzB+mtTmdvcedvACePhOTJ9kNrxg/3bHQvX0gR0dn3n58mdzjlUzqO7nGOVSpp3Z588JwiJNJ2lwEgsfYt7CPNQb4XgFUwVYZssgzj5a/efuKP6j7GPsUOeqOW9UPFSjbZq2N29UmAIp9/q7Fn/AEYzpjJRFQTAWzroyUd4FuW2o3KBCNqBXsIKXwCdHyM9pnmNlG0IoeJnB8JVquXSNIJjeN1IDmZcdc4sadrTqQ7+XQ7r0lu5jiSXpr63/jwRM8lHjTdR6Ak533JjnNaMx+Cnky3l9TRjS/NHmZcvAWJFyHBRtYUffkBfS3plLTVYhgiuSNAdFKms6couDupx2TeI1w3xVxsLp9gz9MbJ++YquM1upakGCttDxPvKTrhkp31s2ZfStQKEddVV+rEv0i6ig7rob1j3LgakQix+NCVsEQh+ChkpTjxonuaphEXKB1QYuU8JEyMdQHgIQv2yGTmv4cWbjsEqwqKgG5w/cmZNnxX9bf4jKs+f4ADRERTPe1hZxzGxSRvxORuvtOvWkaxGk/tVPd+sbEhqUvU62dJ8xy3wjWVVLJ0QA17KkbERrWRvTYnasO/23B+iGB39lZiWes715Fti7tWZICOs9DgXa+brXteF68ytPQTCZ5AF1/r2fT7F2jqFkEkKN6//Sb+QXcwJv+BGRC9ePWfH+1+M934a4XBOrqAx0ruGDu39fCyi29GmdeLosI4LVZHNY4G1hbemi5t8IEo13NFjv0xjq5724wpmXOcGR95Ps3lfpmkD/W3tdHUKPX+SgJNrA4it87Ac5Q+NtRXaVyK7bt8S1ywFZzsoLP0CwGzWfxf/dCTqRLjt0si0IT5aYI3C4nLf4eVdgkvwMnoJiS4G/T+XzO3/wM8aCFzvxd4kWVidjygncPoMQgmDMimsakilznH/ckkj6C/+4rXh6yH88N1kpoLRJdHJD8XWs0t3ZGxdxU8+I4h4h4TpWDXx8QTG5GypA1x0WAKacQZpUIOJjOK6u2A1RrzEG5+82PlXoO2aXANb9m1AXTMkhio3En465+sIbj+3aONaJiJ0XMGFgokmy4BtVnQqEcnqQBMzdagBiXGuR54tMY16voTEtM3GsHVsYapGdV1OTkJ5IW1mi4S7RrEz/y6WhTDb7epnMtwJvVtHrOt3zRXWf12EHZS2HrwlmLgg3Knm43gHeFZ0GHJaoFJRfdGjJh2MSYgZuq+X5T9Lcta58CFTvLyziGpDk4hLU9HxNMon/viAfG6tSjY5mXCY/ZiuGcpi3VHjBiNHOon0zfyVybh/0/Y+uvVAG2SAPtU2HiQYQT688kAatQgR6ocfAgogj0d2ABt6D62xyB1nAdYaRTdtgYd+dmm34zdh95GKgf6tWzRpXDmLp3NWdm9LwfAzrnpM6n/ASt0gSx+ICYNOL2xaL10SBv/SC6P06r3Z5n2dN6v8spuyUeben0d0wHgcAy05OGgi3AlLfezgOy/UbwgGf9K+/2lF3HvhBq3G9t2imxlBa1ijYFJrmamNj/WTUMTpeC9V/nEzTTfEudr7oncaLcozv5WewmNG9NEbE9ELP1JMjXeR8Qw9oL/hzIIVsLLm/Xak2EsE5twTTA2wK9Ca9x1XmQB/CwhEisPlwK1FhUa5rHsp46bnxP/qBEexyCML88IbiMNjREjSY3nAkwZqaVtbjRnOkBFwqkS3RSlucav2Wxbo0gSILZhJGMU2xwNSr9DBR+IOowlobx3KFAFAauuFete4JzpGrFmI5f578PzmC9Yweg2zk6lXObkzeYW2lb6XT7lVNZeDV23F6/Qm8g9WajQkvGf4r+i6FWYQ8neFsGEWwX/jTI46ZnCLJh6L409JWgJwKRREDxOGxU7ekE9IIKS+A3ZmjczHejYJhrVLzpBGspLaT/OvgAlhAnTcCfP4ZOjZHckKTc4i4MbehjlMFYTkeZBEVT3qLLXrzh4gekCPIQknu2QBULl/5IBJ4yQWW/U1F0k33Kc4Tjhg/ZV+ajv948Qgn/fqHgdGk+1eA3SExw/71k6cBdHt+NxkrVvjMJoWYgj0XkYnU2K3yC6gSKPS2Rg6g0ldjf/BAL3Cia8mgQEn42KJF/SxdOhd9WeG+LN2nIY0gpY3K1ln1RG3whZcAJRo5jyP+xI0hzwX/Ivw8kb7aqohBe1urKIXL39k0seMC5cHYYpovrBFZ4QCEDdlyhcMCVN9YN6BCxT7mXv0HelSin4EzpX8055u813lr5DS7soOpskkJloxUB+Ka+I5LksX7k2PPlfGzig1sh29Lr9hi+uwE6tAStJ50ktco5mgRLgXZJ4DxOmP/nqVjxQ9M5I0vmUDmYiLteYyYVv2dyIjaOzwHl6etMA3vuDTaDdtZEueSvWCeAvho7oP3Gx3OLI7S36RoQyYTDdpg9tIbetJcmtClVJa0D0Z3wFzMvdY2jhwyduPa15ZB36CRAfBhwfULzr0i/VKJ0sgOTs5dBxWOr2a9hfvA6z2sUxOEkqrhN2EYyKhNPU1p5vOSL2MWxyS6L75hk9of9FhBd66Gs2lGMtc4ilNfrQAsq5Gsr6/XhfixXwz7lKckpyyqdCzenJJS3ZrT18PAQs9pnH6zDgxAVRiHAEY5ymu1eFQcujC5bRE0U1z/otAMYC1UmCi2mCeEJOHKMwPEoyx3rJ+0xuHvP83pV98xOwKE=
*/