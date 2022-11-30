#ifndef BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP

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
        template <char... Cs>
        struct any_of_c
        {
          typedef any_of_c type;

          static constexpr bool run(char c_)
          {
            const bool values[] = {(c_ == Cs)...};
            for (const bool* i = values; i != values + sizeof...(Cs); ++i)
            {
              if (*i)
              {
                return true;
              }
            }
            return false;
          }

          template <class Chr>
          struct apply : boost::mpl::bool_<any_of_c::run(Chr::type::value)> {};
        };

        template <>
        struct any_of_c<>
        {
          typedef any_of_c type;

          template <class>
          struct apply : boost::mpl::false_ {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
UKKJ8MlqtQnV+C4Kv1L8R1bH5tvEy/jHKoSn/cTFU/ZAqdpgCX5dgRiZw/r8qT0slpPUH5TEiElDvba1ubxJ+13Qo0mT/99KJTxO5Ze9vfyQz38Ki0KAv/77ZMVRenVNXJrqz5gk6OL/IK5fvplmlbMSw+NwcF9xyFRI/vQZrO1SrMXcWd3ST+kT5H5tNCmZWncsmCvTITyBqFgIb88t06Gaj/4fcsmbP2H7QZ8MNlHhyvKVPtPipR/7PXlNxa9Ue/1IX5tr+TzyITVi/WxvZX7EJXhdn+CXw9Xwn3R9Dr/RTzpyihtxruP5/kXVYY6BnpPElcbY+OTtuMrld9FNIQ2fEgwVL3bS4UkgOJkU+OK/u2UJXa5BeIPLx+dr4bzNLEOGNAxAKWt2t9M/fAo01vztIl99vkqUPfUq/wU/1m0cOWkcOrJoDYolKYon+7h/1AacnWaIaSp5cKncD/z15q7QDhNTQCE4/dOL7d5wPxc34i6/H8zvH96Lik3449w+sQxKxR2/z8L/DMx3ZK4I93JC89vidFwjPOSJK3vAZxXT+/qLp/zYfx/AX6H+VMLVSf89wUYfvR34tv/vnpF3B+qkGI7fTvYconNk8/UMf8DnsP+/vvMx+41Xpbfo/fMvB64YUYhklhG6z+GVvmxNUWNTwW6GdPD5K7wfb4lOvzhpPHv3tvij50jc+1HUvnALx7v/tbmzCulBBOlWOMD+ZdNuLizy9PBher58HZypiF9PkuF961lqKPO6dQsnSv+DfU4Exy9Wb+nbq+HAvuJ6tzYM9Ndl9zYcF9NPiYWp4Q7/zb+d+11j/LpvNrcRt1Dir39kVOLM2l+9ma9ByazUVQeZv3kJzP1/tLx6qUjLc8Xz2cKO+7asrInwinXcAcRfuY8tM4AE5/TAAJJwqYU6r93+NNZfEpR7dBsrdpwCrhMp//pIld1ePPbN1D+7bD7geUffEdztDw39mtNt6Bb4yfj2HInx8c2oXjTt/hjd+cjE7y2kr8J+WbW/49ssrxjl5pL0yNLbAo42jhA8wE9ED34czDFE8U//zwrBpbp9CLck9OYqpT6cCt/xVb+ftCXz9xv89u34ofERXyy63OuNcRbt3ut8bvZHNZlX0ThZZFmP474c6qeQ38Ovowcj1qJZvOFmk2+6JChfMK+30Y377rPiHTF7+YpjTnbSLJRsutsb5Zp70JtIz72bwqzvfv8jHXWfj/ljntLnZ/rc7zV8vyezW+bpFvHsZeVaD4Im4AY0UuK1Qhq2wT3v3i/+dkpD/ghu6GXCpggzITRQ3wALURG185n2Yro9x2o+6Qm36zq9Akv8h1vbJ10DG+MX2iRFdonSfyfzwMfQeyziCZxk83mR/clL/+V9zxn3hqe5DKLvKmu9GEP+e2kP1y+fdesinkYdtdMt+MVhRn1URfwg6VPg7xEmHwIO/maAxuZOb6Kj33blW94Alki3Pi7+X7H3olwNiuX9aUc9AvP6Qg9n+lX54YqJK0m94+00i+FcSn8vWlnle26yu9Eob1DUTXruyFQHCXF/wvs6cCrI1+YOZPzpj+spnh2jzVbDR6fX4D74cn4YCKLOX7mHcAv1uy4sVi+rzI2KP7fwe6g4hn/Ji7valPlnrySW1CV+G8fn9DQnTUtfrv3HeycPjaVb/YQHEBdrsLEPvwi1QPwZlUXv9J0/OP2GqdBHiu53L6O0ZNrYeXv75y8mruI8n+Q3kxg8PbJZBXODqrXr1nW0nOqjU1/cn9sb4v16z+UL8We4APV71KtyX0qqV1JbD9P17BFPGT/TqL4f5809xf00LxadT7KJ1/7TnvNUrqKEHca1U+/k32/OW56+L7bfLpvWuUm7mn6+iY/bvt/fLMlRynE/jcK0CaJJbQ85wpVed+fc1plV7jnkv/7MRjbudE4YYuaQsZCXS2WtffxmfH/fR9UORGZCQvzoXlWTFhSEzPqK01y50VwU699G/v6ZPp6KTsqK1NwFTXrJZjXpAEh4+4++nkmiH8q33/D5bO78X4SextJ97v77ZcMiBHlBadle8f+30afv1D3HAsHx1rQTjX1v5rw/oA+nCvj5+VW4xg5fbJr4h+nd437lHs94FBuvpRkga8wTVYaCcfjbH4qCtYY/XW9n34tR7fBc3PoiJZA56Ftd7BnvfuBb9wgJSz+knnSZFX0LjeVCJnH/vycfWSEhIm0xkcT1OCjYHxx2KyXHD/cWe1+B5Ee/Ce/955askl4+S2Q9blev7Z+uuor3GRphIgKn2zbYXBbjca3rEy4QCaCf84n3PD2T6F1AS6rDeyTeobf8Izfwn87Hbych+CP9Xszwx8/ReOQ+XU2jNfD6TwhWjj85eb5x3f53QErEwv8t1UqKa4+FbC3fsCR8l+z5W3EV/un/LBmTH2/MXBL7tMcT6PdlHCIJWGIFGzALLmDjT31AqIc+/PyRQ060i/pYgEFt27z/8mi9e/tUDu3E940B+i2LOsV+d70SGTki/wYnB1cgb/T8Th/xhhsKjqkzx++ITfu+eTn0SXL99W3EuEFEwpyKrRcP+3mLACX2/DT0AT9BSlRbdaShrwRNNo/3PkXPBPzK8O+RHZc/+CY9Nbl+qe8U8XOP83eMf4+3vbWk+U2Mp416e8Pm9jD28exntgiHJjOsOr/RWp+gipz3IK+Y1rF28PAKQbtAOOaYMeElHeh+96oEcOAICwd1gWckF0itUxzLXn8UO0kNjekNBA1EuvmKrUdJZcp+08mkqluTZ/ppLfFbBb4neWQZnTN7Dh9REVmNy1QFTrL1/0VrA6d2rBCj+/kb6xEPYFnCv+ONxQe09j0pjZ1Bqj71D+jUy52ilpJdxqyHF1fJCEC/RryKdpFStOaXKWn9NXzwJ9qEyBOwi/ya1QTTuffLaRct0f9vPsfvkdB14kh+BmOsf76/z6YN7uO4Hto5/tbXvPoyWevTvp1kKszfqzyWUYae0Ckleykp4ow8FeJm88osfif0y9gLZRS4Sii1vgoFn6G8n15eq96ELX30rCUempsPKrk4zq0Xv6x/3Vc7CpC6+DlcQ+2TOu6vbATKUUgi1iK06279+BffQfHRZUsBsFw7sJ+Onu2iYWR7l6ldalyvTZtf71aVfmNaDw9YNOnB0MiowhPCfPzI3vcfmGxjT89AjUO+47eiKRVFWKJV/OALfrO59dz2VM74TGEuG5oHwhKIITskHuvgw98/z3u1hEhRKUHxpVTZcyeoNknd7yrsi4fQOMQKUVy3uD/9wFs+uLvv59S1t5xHiVgffe1bq1qYAcjXwjOP2wvCBbRCoy6LJe0ALJBn03xp0qTN329JH5XNhPOMplpbTrP2C31rf5PsaGJDYxUO4DP0mc1QFE1uZt0YZOvZoX73jn8xqdI4r1gUpfFt9ANDb/Ne888ePiwvJtWzBMltNf8b1QM+rvEPTOFDJo/m78vWwx3rm8PM9dd3bPHdPhPkDeWKiWiEnMzE/pLq3diYSxzcl465vcXqtCMlqeIayOcTub69uaxA47BnMu+yyw3ZjTIy+3PxlsLt0pLn0efnZg7qr1fxrZ1cg5t3djzpHHbsOfslzosBzayLTz/twqsVEvXzNnc6GCoc5Me+R+qi7u71E/bHp+ftoeMCQkPjVz4eLfxNWOXcH475mwjpxg/l+InXzvzvX358+XKKP5lVUG+zihLmbVGR4kQZfhLO2AjMSYkP898xvFSP/sM9Cl2w/aZ2qLZ0GDYGF/VmPfM2BuVKOFrxc5txcbQYlVJGp+dT6J/BNK/Yy/alpdIs5+ELMPQJWeefh73SXDPLZmND2OsZZXBkbObp+4zpGO9cLvcI083AzSlesXi38sKz/ZFrQyT83wQa6W3q56xRYOozuPA1STxCIz63cItHshthpte/f6oKjG8mpJRfy3PAISce+Z9G/kwSNPfJ82Te9pWaF28Dy49cAS8zuhe/slfQT/GbFcAFnx+tLGbupGogNX6DcHOjl6NEjY2TZS2AcXW54bKc95yMJ59mxvz3/n1752a0b5hLfm6i3u9H05fjV8t3srpiUI7yyh6ZgmJPD0L48qu8besx9cSSw8T5D1oKxUur8Lk6m8INKsp8JB50oa9760XNZALV1qPo10RNqAj/jfNiFAl04xkszYsnqFX8lzFGvoWJYNoUmC08DFOoKUrPIkdzu74p8c94Igpp+sTPQqL0WUOmeINngktbGw/n/dF+QC+HQIQ/kzZYy6riC8u8q2QCqpI4Nz/0ndPduNf36qujSTDZAQ+r/ATZFaWcr7dl/NNfRXLgDY6y4DdS+yV2juhFolwlpKawE2IO/m49nnVgnHw7DHhsjcrfeu3oez7FBchTWDVT6UGYDwFxjT8bLWfv8DdHmcTzrV2ETJYPGif4VMdEJHgy/d3YVeCKE946SXrQ/qrX7G6W+0/UfgbBZADxiveIt04TmNSDvv+2y9eYJoT9+Z+3eKB9d4Q56Y91EV0D3l9HRmUtwMc6l3wmEzEZj8ds/hPf+56PD+kUbWzhzEzNnsxNJSQXpU6J2WG2VbYL040W/mQUv2Vt1nPifEB8veHBwa/hh7sv9ppMB2UYx1wSz8sKz3He7eYsyy9GA8Cy/yP3vI5DFsWCt3op/gTOZBW96hXi7/8fbFP7LcODuvQua0fO42hgsbvD9I9juDCdj7+39CWcpx26LjtbZbVWttoMr4nGtQ+Pffkzwqx3r/ZCnonYcxKcmMzXLutjX76h/cedgQc9YNbLCEDDTeGW5uyFfYSUpVuG/dpHj//zMezYNfkDvOyLbDFPTd/ugPH2ct+so5iX4i2+/d7ji2PEMl/454HNpERjLuYL+moNZ+AUkUGmyZvW6PR7QnL+MDBpaHoFHhmcSD8tOrEdC7LJP0qJnWjiXthSmfbZn2BLf+cwrDRG+Bqdic58HLf4KwerXgm3jKENy/Lz+YIhx+eYataiY3Z2jr32/beeIWdmsX7eeGpSvqSPVgQEJZu9WKj/ZX8ufYi7Ni0/BBmqabLWC4Qru7U0L3eVBYu5/l6fs0SBjcJ/lAMI7vJz8AH6KKT41X/6l0v3YXLpM3/+RQ44uW2kjlZA009hpjyZv+CNmfQamsqc/pCdZTjlsBvG+mFifzRDs+f9ww87WIgzHnzgRfPT2Z+miF85cU99Wrrj6AEMGT+XClImbBqqRo8ApKdI03g2rBP1jWdCPqKU1AdpLVyr3kYP2gs8M/ChyTua+h9zx6biV+EsjdGcvEwNaLL6+TWYUg7OnIpOSdEudtrYOm7Am5PljBpoAjem87wd8ZV+8BdyaJg0+TPGh60aLU13jtXMClIx0mXUrFGJ6Tb5Z7E1sBgM2kvHG/g2M/iwi1z2L0SbtKfuLpCUHwP8HnY9grmTWXZHJ3DOdn5LvTa7XqRzKh5ul4z1EYXinlgAH+qc8wyGH3crqnUpi1ESKu4WVuurP3jeoYr8HjJ0x9yqxt0WuyheHuqTcvZyIZA/4y4vhdv57Y77lchKeG5Ch6njGxkyTE0rdvlIayw5iuF8/qpqDsgYUEiFVAIFHldk4StkegcXbHqgXqZo7JKX+JLCfm6RBV/HmyxeCP87z7s7OtxKoGM5j82mnUt6tVkJMv4XVsG693cHqMimBeNfsuqEaT5ZaHz4vfE0ivi/ZA1bTZ5qL46juzNvQEWiuMxlSj9Nl+pKJCFhBCj1/Pewp9DIUc1gZ6rhP290o6nSUm71cYdmpK0sfWkqM6BH7+8iF7+8vLL7raT9/YgPSzyl8Mw7oGaa2ltVcXtojMr03gN1bRbZr7zojGb2dlZv0NC7KS9rxWPxZQyztOiXXeN7kl9GCdb4D7/VDdMn48wZZzGq23xoCPyVHYxEdV+E70K2kj+rOjsg4sHR0YOFoUraT5X4TJw826zDfD+dPwIG3Pt3pUXcxVNRAflvdzEJREUTmeLpSh7PAyAQgXLj2I3oZpk/o4JJE7Cn95tGSLOtBhrslXjl61SRZ+yi3Idr6/uEV+TNPr2+6w1mUrbtykJJso5eG7xr2W9fvhJEQ8XpcUmfPEEozB1oiLDshvQWrh0GLJ0/+x0JC/2Gbko55P74oRI/Tsh4fCsKxEzC3+7e1KR+uUzzwahbkfA6vtxLNg7Ec5/MqD5z2jhqomNFC6TxfGEPm6p1IHZc3lZ40TT7EQ6a5M/T7SNvXRYAA22j7fWH9ok5DN9eqZ6yBdEyeDFVDe9jx75HnBeWQr6ORdHntfTRY0UNnnu+ns9i1X3TiLqk+EzLBHCU4syx5W7RjMsYQmFwcHTpLXDpuhV99lO4HDAMBVGsdcFCUMQ9izZRP8pePaofSJewMbbZyM7ph+xAQ9/X16c04cU+K4WdDcR98w49PX+mAN8OAer8DaPNY5A8IPlJzT8Zck08T2I67PtibzsWzE38MYk2nydpSOEn+35U1TorO+wP/gpf24Yv+Fpf+J89ltLhuO0X432nlYrUuJ9YG/qGhMo73N6rtzCvRGrVFVqQtlLO2rHZZnSC7ZTqsEfvuBMOM4m/qCuP+H+xr7Cb4onf9h13Bm0JPwEa6f85nRwVFWxvmhsot8XHArhdWW0Ri4MeEbEuifmCPTHlqY9H/O1I3+/V61LiZUXf+vYdUxveR63LZYLJ+vVjCL/or+iOZqw6St3emaQ+yaLFjO1ToXvz3SpetcpevKmRT7kgjVsCt5+9FrcQAaonZcz2GJBUHIx7K98T7EPMEWd/5fTNlu/P/nYwYMbo61u4TOoHcPGXTnDk20q2fPPLJ8mSftZoOdzzUf+7vrQQYJFOfPGc+IhMBxz2Fbzh8/ZQ9w3gojhlNY9jHQ0I8ZnpfnI7+Y0x9e2B43S+ClfF91a/Udm6ET+glx2mUGzaAkS+CjVvSCLFRB8TM9/bxgq2l/oU3IFC+YNpcctsxkZclxMcYOjSwsBHfylwjpqTcHD/VCiV/wiP7xi1/y/Uc+JTYeEqKMASFOjlwIcUeoq6SaMLn3J+nftYWh0nv+8jtBH+70lsXaC2fnQ5oyLRRy9k3b7mp30R0Dqeib/u6o5cJ9Sjf3q0a2JHpNOX/v3hbo3rbkbS8LH/TSr/Q69DoEjwcaXrCWpkID0z/vnx/6c9i+q9YnF8uR7vZ6tng8jh+pqntZ7WV7/3le+XWTyfPNf/1qNt9oT1YwVnCo3U8D2IP1eNXTNc4iRd933+6geZ9mkRHObWXrvg9LFInogedA5TSPxv16rJHcUgSuwYeYQNj1mwOkAEsz/z+EAOFHAOKvaIy/kZo4yajyP9cgkUe/NDqiyid5yf9k+SNnul+PfnjnvsDz/Zv+aaMmqYvPyN72Fv6yhe9OWf3xKuOHfvzuuXn/B6GNA3bVdjfvycanUwLvg3Gp0RmQsvSxx/Ql4y/r913FoE9etcuHcL9mv2fFtko/hkhz+eWuwLN28xIYgd9SF+9kevHoLBSfhp1/30SynGhfjVE132YbF8lrrWBAF5jPLfjUdaSUidz+1gFePqMKPbvR163jh14tb4F7nk49QdWLOfp62c+K+e8dfjnyUZLodzSusrv3w2qLSuiWHKJPKnyRYB/3Ch61Fi1zgxmF6+JQE++8X3/a+zpt3b/E9/9lDRoyjH29Gz+wDPy23Dbe3i9UPY4B73gy1T
*/