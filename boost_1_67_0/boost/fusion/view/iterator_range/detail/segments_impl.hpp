/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ITERATOR_RANGE_SEGMENTS_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_SEGMENTS_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/sequence/intrinsic/segments.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/view/iterator_range/detail/segmented_iterator_range.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct segments_impl;

        template <>
        struct segments_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef
                    detail::make_segmented_range<
                        typename Sequence::begin_type
                      , typename Sequence::end_type
                    >
                impl;

                BOOST_MPL_ASSERT((traits::is_segmented<typename impl::type>));

                typedef
                    typename result_of::segments<typename impl::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence & seq)
                {
                    return fusion::segments(impl::call(seq.first, seq.last));
                }
            };
        };
    }
}}

#endif

/* segments_impl.hpp
ZH3arhVrcxLJsK3sxSs41O4sNsqQWMBN8tVm2ygUj1f/ng2JSRcL0aFUjH5LdLDoc2wK4+Y+W0gzVVv4lp63YqloIWKkkMaHiQW3ESkYKHSZig2P6WmnSpN5+dLuG26b2FYO++OfCwZMRSnmWcEng0De6OUu/KZGcNC1YzGY9NgxzlIwE3wcEueDnycRze1Pw2nL1qjj4vukY93G5O9tJNwucvoDsXeGVwwwv6Wnzs+zmeETyazkz/l1rVBKJUa1ETBca2jKvxJVasV1lbV/fX38e0NvfGRh9ofo6h3//IldydOhzgmoKItm89JLgtiMu3uMqxcesL6l/9Z/34F5+FOwwPWEEd78HHoFf/ruH3cYQT7+/NMEVf6C0lbA61j+1SigKPyT91yNtgyajgK1BIKAWaC3FFwHoogkO8FSINNcJ2rM26NYCA9HmsSo0dWNY+2yW28IamSElXm+pC9j6mndkm/lrzVv9uzuA3kTq954bzLVtn0JwuSuMpNmQ3L8Owd4Ec0cAQK0oUJ8Ld9crGPTG19YBPDmsx/IfQqNPFLySShMQJXI2uHrltkHIAn+JYqKAUfln2zkgKOF/3iRUZPXUOfPZ0iSrWIsTQC0Fw7WLUjvKeQShxqnDq9WbbFlMEqYpI+USZCwEBCbuFdcCz/4Jq6ndSUav4asso/V05uFloiFqa7aUVPZ49zzjNqtKVQvrVHAEJrw8PjRA4q7snvr4VLHZyCuF0X20F3MSH+UwDuiNL3HZGAz1sq0R2F9KFYBC0TUZFe1VQKQRBESRWVldHWOOBeKnVylK8y6Qb12Aru3LcX2kO8kXEslS+6qClUEt3tUmWqCYofOh3j7eWbZLq56AxfE6NUfhCiGPsfei8O6v/y8DWnaMiLbCVgxa1uC3jEjtFs+2VwzdPgYIzN7f7EV/Abwj/sDBz90/arSVrgH/Uuk5mJxRSVhG0ErUsqfTWHJdA3iKtoIF28KYnV+o46vzXqs/h3oofz8UvNjPTu5csJ3Bfwwi2spC8k6dKnjD/tLb65jsgG0nzx5t4JFcZ3lMtNhqIaNVMkpk/CdzWcZpvcngPy0a/0BltAdpHYgmzXYOgJI/D6ZWjTAdkwEjVHQjLjVTG79+mgUbOaIvY4FOwuITF1V6dYGdDgKr8+OKTVtbbY7uWFAfWLPE0tj2mLSYYjVEqbGMNSSz+6ETwACLP3TE6rwYtNd2TOofU8lwjLbk0TlarCTDDS6hjF5RyUJmL+s0zymO/Xc06mTI2UWVC0Gh4rnLPZQidchh2V9VtOoe5vomQdQaoayHrNAltPqjsQCOxksIavClJNkFhWCsUG5ZB1f6cFSamXQO//Rj6byLzWH1RVyW5yk7WnmkxvgbLrnS4MzL+5i1N2lYg1dxOCfVHUXFmtwgp4JeqWv29/w8PCOA5RNIt08Wqz+5wBbK/Px410rkPxNGXkEFlrzXMpBmMM8EhIefpXE/xpNoQDIJRzvE79ttZUIy4bL1Jd+Xe5/Ai3Ox58nRlmKf3ARicJyRYB68Af/WMAECCDw5+PnM0gi/PmXX1Yv/0d9KxLWtrgKw/hFSa2tDaGk+6PynFf4qo99ynSBHAbp6p2o8fOVVQ4D7fPp+WKpuqAULOGUnYu9HRdT6nMTvvk07S+vMNpjxqvXii2/aKxZ4/SvwYs/7d621RxWxkt/TUhWGwByVyTb4rP0GK20R1/frODiJ83Nz1cOR+vBbCKBfqtZJs9+x8ePy35Tu7RUqdVJ2pbB+W3m2YHc2qsG3jxtwS6Fde5jyNckdaFaGKsYKToy+W3wCgEaZAFRNsfkPt6WLExLJ4gh/K+TXIhBwfxghFgUP58QDO2eDi+xDT1dG1MGoWFDZg/2AJFBQX46sAkU7T5YQ3PB1rigRcF0hkCTG7oxYbNx9ejg4OHH+/Jg+AOge9veYoH+9lBfbz8kjKcHvoWdZ4GOpXL6cgB2l2LHEKvCeYaNJ0IQcyrSyaoSt5PtFCAaO+xYxqaJs04+9gtjjaIzoPu44zraPl29fHdcVp4phy9GSv4VMlaRbcHEp+N3ibo8IQzPe0t7Bd6cdi9Lu3lab5eH3SkQghufucZ/BTSr+IVvcJPf0rrFT29xqWvnLhW8Dw6uVRn/7/vfNu8fdu3BLvYnGjKvfVhefgLJ/jPr4/accKhYi9aeOE5g9oH7twnMLc0YQoSZHgLYWARSIpwrRsNAO/ERKIszjmhlaMwJibFWAgj4enw3kbSZ5gBT1BfXKJMcklyDg7nNRtK9mcY8n0hIdizDQargDOwqmI9T1kV7FFEyfFU53EqL6YpqMNNy6mnydenpERVwArsiBzC6yyJkkcXEyGv9v2SF+np9OKOBOzGKqDPFvmpDTo2TrAGTM1agWPjlhLO55969A0SHV+Ks/RfvnmuwdsyrsjFQcqpuP+S50Lo69m+x2uOFP+nm2Om3+9jOXr9sNinpYUyaUg36rtgjbUvYIbYVhflZlqBaEeSmeKQ44MyKYtNJsSON6lt4YMTbw/T1h/12fvJJICYotFYA7mGDI3o090EF+ikZ7+29sC0xNW+8AtZhTh8LQDlvGWmS1EBFZXOHzGNWTjLjpyzPaawxpNmMqcs05F+FvZ/EVQE1a4yhaIbAlOtZVgew4LPf67y3IAfhvLcmncbwMoFvPN8KJNZvOlOOIRgnTRvur1Wc1x47IYhRXid3o6ZoJWcpJNjBQgvQFkXa09LDEMjQDLQ1qO6B1+vGq6jMx0Wqwu9Uw1E0xUnGJZeVeNBpsvEekFi91cJeHuALMGVU4qtjzeyM81hS+QolmkFHrDNI3RRNDRCcpjEhF/DzqORqYaZJJUyGW9Z7RC8aa54bvHaK4H/2sUUtQpuOZDaI80hIjomEMUYdKNHg52AxMozyfSyLqE8JCCXOow04S+ktyzhZF7+98f3tFpalLcJyaFsWp5mqBL1GmuYTyXtXZBuQdXOKaMXEsAd5dq2SmIbi2RL7V0xrcRyy2UHF2UZULSecZOPZyCdU8l1r6M6vqZaRaSUkSQ/6FHQzNuTKh0Rj8tkNlXff5ML8nOPZrC/fbzdnBUVyrse9eU+q+lrsvPBzf2hhbQM6TlPQd0nEkS69d0t1vhIFizYrYUleA/bppbspwlsjqFswEZ13yQlzlYu4zLFXyQtWrQrLKIeJ1dkiUlWy//SJHNzhv1V4llauFv3H7BPAwyfSeFEQqxVKTo0mPdFES0kZkOGmCO1AqPLltrq35YG8WVRYKy8N54eOx9shHmgRzv55GrZyRWInGfYKAHsTpsLy+0LOS0AfILGPT1H/q6Nju715if53y6fPn951V8oWCtbAbQTEOoQ3ItK/K0isYEj3sHBjgl3ZlBQty62/LSLS8Ur1KZa2Q7bj/Ak4Ao9vobbHhM9SjlSU5/LmcozYixbeVNyAdqpCd6U2alzxQq7/IMWjjwQ33+QN6kaPDOvsr3prdE3V+6rYs3Z/e10Wu3ulSEg/KugYFc2X97SCX9wlahqoQlVCNIo77Zb0BZyzZXCXPGLOERdBNcy9aiFRbBkYzSH2VcnUx3aEaeLo16jW697zPVGDg5SkH3uIoEq1TZylJurpURleOXd/8YZwLZ7Z5ppbheuLguieEHf9rABk9FRXVIjxxNZ4U4hFIec4ykg96N2s8Y+IzoEOEnL0xBTPa8Ytd8LL3BDtW4KmCjJwD39lAjsUgjSGCldF5848k6Jvvy6zebh/GXvpT2nhD5FfOTfnwfWqUhwDu1qI9h0pfrmUrr8U687h+0s3dkIyG5VmdDvEh240mAnLAL0rOZhyQuNEAh/ZVDseNU6E/mC0P48VFFoKfbwO+WRntJzpZVJ++wwE3hQoAJ+eggK+Fapv3U2Bkb5GBw+cEI424TSPWcar3zqc5B5MfLufYJgvwm9/Oln8j5ofMow2I8hKTiu9Cdaf2OaoS7MODh+e9a9cgUggEOYw+QYl1FQxg5oS6YNxCiJiQrJZjIvrK5f7uYtUTAAkUkCAxenDxZvFWCetYVzo7VoL5e0tmDK9zFiE1thetQQcRWg0bJaA7Pr0PMOkgNrPCDxLNJVFeIQiUHtTMWLRH7A0qyVJJO/ZbGSWQw5WunTaW4k4rYelB44FFJFtyXzKiSKTtuMMhQYq8zFwYM3TlHQsG1pE/TX3eP3XRL0hS4R/1sjcKa4X4pDMfhvRoHAeYl1DIkZcm47CVZwlaz7giO5dCJvthxL5jVgG+TFH7oeR2zLjoOtjp96NkDR1GjDFrZxwPI3TwmSHTi8h54Bg0G49bILBDgH376vlXYEoZKThawHmpL2BCalHiiB/N6EpwjKBbx/7e51KBlGeTSk4FWQijmV/SIkGTzrOCuOyZ8rsaWbR7BZqkn6FAbW9y5Vz5SeOni+Ent6+hPc18FYa+FUaRFPKaaLmaF+sod/gFkVMBlUs7RJoziEkPqev5b66kgZiua4C2Jwu01dPtKX3kL+hQoG5LAkhXBmW9qDpFGRFE6W1/FqUR0uyphgqsCpeh/cR29eVIJVC8lTkhon/hsHDpzuU62RaFqUF+NGXr9xB7yMoAzU26avJwAyohAnU2BNXCjauSfD4tEbvFPk8HBHpBYeF7kZEcfjnX4oFZDKkVx2kFrKkzZmZWC0rewqvjJMSxuVIOfc5pouaw8k5ajkg0vWKMbwr9bjQxIWVjToSbfE/oxLuaBVrZymcdsybOxRkRQCmowJr9cEpWII3RAkLf9M6XGd8M7hfDYlPLgpOlM7uWiG97DFEK1Mu1yq3JmADVqqu6/hgQ7hyr9x7nNkeSiKlI3Zzhecds958Nd6WlhGZwfldCVq4gcQzkqWEY7xLJYv+QiPjSRru9J07OUi3hn6nYW6bjdbgfDOJh1Ff3dfRfZDmbryjGP4mtlNyUK66iUr68VQHe9ICBqQt+WSO+yHI8NriKhHzj91wNLgvM2NDbrHf9yLRrVxfY1CTBP8PWgMZ0Gb9vgJzxm1NE0+FiWaNgKdb3IYRaDlM9HWPLDuoCNAKEFWN5Zm20cyc6WMfwBkY1DcnvKG3EItng6RjYnhs1jSfSr/ojsMkh03O58qvOBg33wB3GqONmsBayU2WvaZIhWnczyQErsJAonlUCm9LMOWF2HEDZbVQl2PNZPuvUsVdT5Gpm4A8223gxlKzTPbvXkOE+RmTpeffdYq+aewzTuQ6sxIWnqbrnotKyHplFV0oBSk0DJKp+FjWcF6Cwi422yHxyVLgOX/TZ37hdI1C9xdb9Lv02RXUHJb+KwGuwpoivmlv+embDJOWc/Tqy6KGxWCoo5ZvxoHJmnX1qsQqOek21g2xHOBh6jpXHfKLOkVZPQSrVCJa9oF1i4zir4PTJOeAE1ohsm5NAKO1obVRIZUg7hOP6ioRdUvmneB0k1fQsXm1sIr1dgP4vhioq+hCxC6Y87sLRtQvLIW+I47MiEMZgE9yOPz1VBZrgcW1+MRTpYvi3ghzf0Dx88wofiUboTuLC4faJhU+e8czi9Av570WAywnsL0naKrhZOFe1p2qVRD4assR7MpCzxjKpVYP5L3uJ0VEhWoCvUFbmGZf6//aTfNb4/71simogtFHDaRcNmu1/G5OsPis0e3ywhZyo7LradyXy+S+QMJRuzgOJdNaNbb8Qd3ZqHx0HZFuSpiuXCpF+OH+iMatX8QnWkkAGIPGdmmRnGv9CiLT7CR0VMHCcmFJxEeop8DPHqicnDJbz4OOPB5IIzb2MMcLc1yYRTMUlm/wsTadK6FT/UTkm0IDxWYwcbTV+1IzAVxKgIlUnpB+gCunYd1fNuWW2KJJmLY4SxBKZYf08to3RhORY1pZpkp7Y3jaxEYTGsLueBiedHXFONBOZyhmJDh8pTElBL9yOERG8ugyzw4A9qIyxOnHNAb9kqpFOxsyC8eOK/HampRbVlJTsD+IGHa3a6tRF7hgQ2AK2Z0gmE1YCLd1kw1mYrqhywzGWi5xQgCX1q6PH3753WLnlbPjE9AAI3y6jEQo+NtvsfyPG2/kXt7gb2pPcHGg7J5/OCCo/O+th1J6Iklt3QpjqGknpICsrzhxVdzqcfE0cvsoRIWLgDWz3LYRhTKydVHbF6RrND07BYsoXyGeojU5CWj5W5MsmFj7PHPSUTMzogWrHKqo2ljSqA16SR7TmN03qmw/mrwrBvxriMfl1nvGZIchnqDA6BwPB/B7dGgoaoq0D791wVRYsPwvfvL2nQCm9faftf97TW8XEABpSQmwlNvt+d18tqbtOR8iu9+u44FPVz/gZUKxAEAXzq7SXALNnRpbOBtc4JcyxdY8f9CGlpWAv5mtg39PQI11u7Eyre80YIArIsR+698QJGQ/sizU4XSYEFO1RYGAOqPHCZVeR/t6SY0AkSbxgzHMmsqDu2JTkAvtu4aGQoIRzKgi8CkRSKWH7LUAilgJxngBGkq/AiuGBxFNOoPmsxlVTepEijucFXKGeRDLMZqhL1xViQYmtjQfDddG8mEja5lOTvVqcG250cG1aIFSw4j2HJ7+qriYXCrRV2nO51mUB33qt2hO2PKf/xAfpcPZ8ezaQXn/jf7d+ruHh2Kec0Pztj55R+D2QnCzYJRiIgqgD7XVt9Ez/xQ2+SS7bYQfnn6BSloGwjpWm9g/U+B69fdZuPOy0otFZR2OozWPj5qgaes72Kms5ZV2vdZzoZrypAhA55MSj+VkS8wqO+da0Ey3AYVg7dLZYoEdTl/rqt4Dbu1E+NJDq4x2Bj9fMeaiutqcxN8nJkY//vECUcnySw1YPRla6aNdefT6u6izZYLq+jfqxOVcwv73eIUV+rXeg6Waoa4FbrPWrp0gyT/P4uLKetELy/mmr8tFNr79q8wM0NPVvf2CukNztjM/vSs8XH4N5cJQ4aXvKtnkGtaYuUeZ6n1+fYiDDB/spYoYJJD7phEAQK8DJJw95dHLfWkl7sIORyS3Bv5meMgapnhZas2pF/Ts9kTGvFhHHrMDexkxQI/YwK2+REsnwAusGLalTNf+joC8SgbJXmTc2yOzVl0XGfbHfbHeyIm+nVr5uNzUhyHqm04ILF6s4OUsB9x2p1XxiwKoPxl3ingfdO56wr1i6B5KsfcJWOV2/Xw2lVtJwbdzWFrqbnR82DhHnK/UKSTIRT00YeV8+CPLaiG4uqQGT+2QkBmE6+sqnM+AgtSBhe4S1cpvP54zqVd5nD9p+Y8IqJPfsHbq4Iu/k7vx5fpRTFn8nwVlR4+BiUEZh05RDmS5wnw4SXxg8cXFExefbdifGAAuoGhZAoc4QYA7brFl83bkl8uisFn/03QXSjUDvS6cTQd15+PddaMAadpUoc4AkYL0Y7xWe3ymyp6SR8K+4WloQcw4FrxPkP63awpWr72FpwUPrc4KkuZe05MPbzSVq3TRSvAJK5TshX32y0HQ+2m5tqLe8lZrdwul/IUlXHaU11582UNgZYCdRs5Dt2KyyIgIxhOCBeLdgyTKGHhPwX3C3Y6h07EABCeD7JNR6Zeu+0KRRDw+ib7cvLYGZiYnt2LLh3Zv+Rrc8LHXesCTASibltWbBns/RSU+1sDxgYdbE2mkQwFIqQBFINSifACZ8+Co3+GQF8Nnw+M1SzhZ20dv/tcwLFoG+ujfs+cBV7p9hPnUiONPj/A/HPeFpo76+2eAxiNKlOCgGojsomjbC84lFjMNvBeHx6a8mQvXbFhnpi9Xg7MvBm0I/9bHcNsTT9wBupkHv+WXjlzt/bf61jfj7bYzVY9MpKUUICUQOUEHv50lU2OD8iJ720MtnY0L195emb56o5IW4hSpf36bXQMvJjraS6Kojr/O07cDQWzdXTNT0MBPr6y1MiN3nW8bpwMN6YwISV+c4eSOTSztQz8W400wvYXL3ZeAAOAUSqCQQ7z6R1IyczJ78TO0dKqXE0ZcNAXqgw7V790zJ2mvt8fBGw7F9Tt76JAeiCH7fzo3997yL2+9QR+AgK9K9/U+8K1Oefgxrn9LzlmHTDPSk2SKRj8BV6uXHGlXM0ouALAK2ZGAjIyMpQJrX6VJ2zGWybgrGF/QCU3SDxsSzWoe7yMBu8/XcvAKuZ0xyTr/rGLbjirGLHgNq3CsEgp54dj+rPt2oX+/WGH473FE9GFZHvj+TjqS84tfwppN9EhdHdrWoOsiDF/o+69ubsBEDjcIXfPRd7UmK0mROAYKuECxXH1Kkb4mzi1q4Cx20l8x8dnHbDVw2AVHPBMKB2bpDIq2bNAG5NEBxG0gGvBjD6iyHqsngihsyN2FwdeBEEA5GgwFnIGSsxLYC2gej4ByJtD2H+NBl2/MdwfkeDykmvDr4QJzRYcVQfxBSTDE2AYJyall6eCpLWEjHAfV46ayAp0DSs+tbWLE1twtB0TBtD1rBNzA8dia6Hjmgk9Fw/J0RBdtcDathNISk0pUKptxrhPJFTjn0Vbl9hdtMJLIFGKw16BGzT1ULpSsrSrnX9XA/22yXRtZXGH9yo5Km3fzkfGTWSVLuJSx5wZ825iwqM9/seciaWN2NrMH/Nv0uxzUs7rC3A3sV7QK4puW5IhjQ+CN9eFzZNGGEgHOL1/66uQPJCcnRra3YcekSrcMuC/hJB9fxuLkJfUbf/HpkwZNB6pMBxgZyvo6ubDGNjwcxHZh+dcHI5O3cd7MuR3/pfDdDKBU72v3t0DBzPigWGliUfvDi12VgOEebUJZv2iL39YjHo7Na/Cl79MOwIPQJ+TYM92c7cK3V+TlsgN3Gs/JlustRBtIOz1QJNkykjeXtp2Zk31dZqAFQb7Xdsev7w5/TMgrv8DJxYe//2+NWKiVLAkW6yd9/12dWDiqvvM7dvRNfrhlY78t2ndxAdi/u2/CnNNFEnlwJ+dOT8IdBXFkPoygUc2AHMmO2HFpzB075JCcsEF/LQ0YGLhDQLHfciVDsa5zfR2f+4Z3b29EXFxaP+edj2QG/8MlrIKhjcceKLfOkQ2s7al1NCabY7s2jflgvOc9J856CBqAzwCsm4a2NaOAlrxJ07YDaYTdulXtNqRkuinLEnDCYMRJvAeo1idE3JgOTG61X+iBf9vuS5i9iHnDPo5v+IyhR4Fa7Fz8hYG8SIFmYsmlFqvWtKdku89xaANjeHLzHs1D/F7OYGiFcdaMg4GihZHPpNMHfgzO/sq90a8jjz1bl9YWVBEoknrFs6nde/fjI6s=
*/