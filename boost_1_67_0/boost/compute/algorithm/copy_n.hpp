//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COPY_N_HPP
#define BOOST_COMPUTE_ALGORITHM_COPY_N_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>

namespace boost {
namespace compute {

/// Copies \p count elements from \p first to \p result.
///
/// For example, to copy four values from the host to the device:
/// \code
/// // values on the host and vector on the device
/// float values[4] = { 1.f, 2.f, 3.f, 4.f };
/// boost::compute::vector<float> vec(4, context);
///
/// // copy from the host to the device
/// boost::compute::copy_n(values, 4, vec.begin(), queue);
/// \endcode
///
/// Space complexity: \Omega(1)
///
/// \see copy()
template<class InputIterator, class Size, class OutputIterator>
inline OutputIterator copy_n(InputIterator first,
                             Size count,
                             OutputIterator result,
                             command_queue &queue = system::default_queue(),
                             const wait_list &events = wait_list())
{
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    return ::boost::compute::copy(first,
                                  first + static_cast<difference_type>(count),
                                  result,
                                  queue,
                                  events);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COPY_N_HPP

/* copy_n.hpp
Tb9r6Xc9/SL1DZVrzBaaS6tvot4Z+EnM9scCyfaH0ok8/srjVotp/v9gQrfg2z+JmW/JH5MG0K2DasMYhbP8HC46zo8R+jTGtwGC2nLi+34EtTwOQQ0ovnD5jOpW+tCmD9ZpfNGjOIL7YtPONMsDtgC2n5/5qdUSznMFyETHFutJRsAJ97oNH7fAYyEvP70a12xdoMBwqDheqvP5QvcNEIYtNmYWkLevyAaPaz5HrhR+jDiO3/cGKhlI1UC+8mFgsbbvB4FbEAo5ETVduiYCCrYCr7MjAKUeQYyj9/FL/9VNOCpUgRDHRHApEl8ZFQhhQ0qtKgsx9FpD32fojYZ+iGe9AANyMmFDZSvhRn2roW8z9BpD3yU+FdsJ/mLYTnUxRkvJ+4P80TPwJ4Q3YtJmMGWNig5kf4JQJ8hkfwI/FkI82iRLbTL0Y4bebOgt4lMUxCgOMD1e+6FoMCp6oCBjuxUp3W5DX+x+R9V9GHEGajNU0QlPVWN7J2Xqgl+R3ge60HxAYjYHoCeje1DyrKKLLjZiiIpXiqFFphhyV2D5+qCIsjlRi65IuN6rJlvNvR+SxFRIEqSCiZai1Pj3je0WSGuo6IMa5nw3nIx16IVEkf74egTNIXzAnwNYKHkSopwqzwNVyF7C8mCQvIhTiSU5VtcB7M33xcAu+7c3ym1R/TiqBslXC0/F1xXuqkAePZti0F9ZGa01x+jhE0AP5plc3I58dayswVkTcdGdPowpzSG9CSOn4F9OdiQ8mFFphtIKj3K8XiAHdBoMgD6gjsgimvww40yyxHbq+RSKhZEjksD5SR51xtDI3fYSqPczh2E210xMAg1bVArDumbYLej/OYxA1AZAdHstri4+JNChPIY5hZ4Z8jjzvQWog2ahO0nAnHKsTEwCvFdx6Cx2OJjZYFF/hDf8vR+hknSU16CMpyRHOVpKITDhP2qFW6Dff8Z/JlRBN2zSGIIhx1lFG9xnVXScxUGNK5xJddkwbzAXxqkNniLomUHPshqNUCP8PVmBvyFVGLMzWgZPsIL06vxTsgUgvk9WACXDcCI6QtsxwfF6rdT71E4gxgiSpoXptcn0lwn/hFBFNTz1qfzmXydbgvvsMLSx7oo1WA49w1Y30NUt6NAcJMdkQ8V6SBFkuZeYQaDNUGZ3xUZIR4iklbk+2gLXpYt9MIUzMAKg092tFbE8ayiEZOaHqGX5qvER/pVsFel3rDfBZlpoToJRgUxgyugs6gFfUh2ZK2qB2L6FeIScki3EQMp8GKvEqATFaVIyAVcj36E+Wkt99CukeTte8ymrQWaESpAIMD6LrUbFPiJh14bh0ded53foJm0o82Tcw3qzPirF+gMZYScLgADAu6khe6rhgRvq2u3YzexXS7ET92fVE91LYMoTdNiOFSV1sno160g+CyH9Xh8/hJEtwqw5BwmvIMKxM7QA0dFEdPgtm3Bg4U007k5spy4LYcG8oq+L3JoRKiqxZgzAJS0pJzxEJiRoyTXXrsBJTowbqppFMdn+4i6MJGNUVLCuk4/8tEvwdw9SWFdNkT/DKSHIqeAMTfjYZPQ+hEg1Z59UjXXbUCOv24oaOQ+DhC3i0xCpaVV8usCg4ANjHYU6rCunTCUvowcNQMkyNKjq/aNrPi2Aiar+CTU3Bus283XzvhdSfTaj15PnpJA/eggDiyzHZgbRpUlw38zXQG7e/ifU5fdoLMGfLNQcCXnMCPa7KHQhhmkcOxW7Y+dsG3px9iJ8vDshDoX3Qx+CSggKbmSV2yRETgmWZFrAOsnTMH1Edm34Guzfoqnxwb5qqGoXQuDfPfA9Uv0ZkNwPCxDIe7NPAh8pLpjKv06W767Xkl1zMmPFAxAL31FQECv8U1ZF2Q5qw11zM7UhBWqRalL+aXg4LhlhrS6oFUqqh1pN2yOKVwC7uarII7dQVghEIKw0KJFqUPkbjejW1SbLHGZiqJH8EVXY6fnUTgSMbAdlWUxZ/JCFntSYACSu3ij3HkTuad5gWalFU4OTy2FoWbS7WRUOnooDeiJr5E2vwZSm/MDXhKL7zwuippWEYf6EZfuREG+MEFO59qPWYMf4800nVmj3+tB36jlWoBpKM19RDDBwui1rEPsuFAArKVg7cFNW46Zgb1ogyZ82lyldWXV+XLz0C3LbyjlHXnOmN1PSYtNxboZXYhrIpMcuBWNf6cxSepinK+bbDf3QlugXmwylBctrMcvjf+lBZXSMObMP5Ofnm2YbKE18Ba22mY9j8IOnLytJ2m3/ek3aGtElq9ENuJDr13j+o8C2zrmAe8klEtEwtt9Vgx7F8d+CcQ/oBowEloJY1IPRTnaYQTvRhSKqFybQ4s1gc2lFtcKwS2T7+SsNFNUT60UafABa3Ue0ia4lmdpNgF21Mbg8cIVU0BM2YI/KfBg7EmztC9Za1XCCj497Feijfoa3L8G30/DtAbS44LdilpRXz9u3QvMEkHzemCAtQll8egbQry6EIeAw46L0FAwxCKc2KDayA6hmNhkh8IeIjSsOaGPIm3w5uoBsjtW1Kv9iTXSAFZBklvNKjsCLc7+HuXdsjeXGsR6bVUgfru5jYTpyTfeJdAt6NPmDfwQoXcB6ZE1FvvhhDLyeZk74Hu1O9xl49UA4id2fyS67DSin+XUUMl0tK66IUNkZ7nPa0AqhJbFnM3207QEY8U8Y+TH7Di2SvB0RCqF7rAQXoRpSHgTgEG+UkF2GifzShP61J8/DF9guZmDczj9DaTM0QNvvIyKfgcI1CYRrnAH35/qIfCDU29To/hAtDd+y8GDsLSu+1e/YcOKrq+qjpc87gzGEJRZ9HFnnfYI8G50q6AppmnfKJYguWoJ4rgrM8/kHois02NYo2/8ORQK0Hiirt56RNpw5hrG7QLLCCHbVoD7SrgJOUa/IxcrNSE8zv3Up/Mmxuxv0ITCHvqbdVPPQnoJCHTsNfDMf5y90lbtBa8GgtwffpusmNrjpb7jLQxvOhvr8Cb4CuYkKtKs9/IH7c7Ojp2f68n3yid8Kb6+AksKvYVsmlZCR38uWb5UCcwQJTCcbvB7kjj8h3z8B6T3Olm/7X58vMNen+oOE7tIwNpS00u4AdMrrtXAZHsnqK05qN7NRwVpbVGklPitExUn972ZoDQJcqVf2JoHEfL0F30vnY34G0n6RjY0yH0YePYdvdci3MBNbTusTtFrDphZjQOdUDQM6p5ZgnOZyQgS0bMGWIy5YIJdO4zQWxgbpyfz9xyPAmt/XSuETzmD7Qby14wC9JTTNxu/tO03QYCqGnwQboyKkIRyJCsnuOhKSpXz8wuiyPAnJA9pAH9/bF12OB/koRaMNN7/ZccX96Fla4hwKFQ64UDou2du/wg7jaFmJdSCa0t6YYv8QJ70+GUYcW2p21wSUIQUkcuBODj+7KIZfaywbPYVp3a4kUuQGFIwWu6MiC+79w0T6Shguj2EINEclOTQuAfd5xVXnKN9v+u7usQV7B2s3BnszHZV/gLRg75jFQ4K912oDgr1jHRWvS20bo8xRHrLQTqZcwMuxAs+jfUiM9va70IqETCswE593MkIO/NtlajJaS6gW15+MKwqXjaErk1hJJlusSbHt2Ak47zLI5fP2b52aiFu5vj0XjU8J8gGO8q+xAXyYDFEK8kGabdo0R8XghAu403chd8IXcuezC5tdUYEGdH+D++HHp/HdI0ETYp7Fe2RjPUjhYi20DmHJeaho1h4ETgUxpNJ+1TkRzwdtCMHH/noO863HCIDdBZeb4DJ8Pe56jFWZRFVqV5rld+2G8i1eAE53LojgtrFqMN/bP0JUT4HYvtdM8UUBUSoaxHx3NCCq99E+kX2gIWVfcjpgQPK1VZGvrWoN/ZLHzdNnVJHTjbxyRtVm+kXDl39ipR0X2MX8zU+6aL8HyhDauvPzEtp5J8XD5IW9YK81kDBIsmaCYC9GI4Bv/A64sZ/fsCcW2Igzky+BgmHcqtwDpULXH4gjf1yU/GxBoZ0E8L95pk+Y7aAFUYM8aMZuagd5fnHFcje1Q7qOd1M7dlM7Bsa14+THF7Tj7afj2qEvwBAy52CLJVM1RZuShit2NS/TjAEpx5v+TW2aC3TudSLZv0Kyn/oo5pdEMuWYNyNYQRKNQAW6UKbCbSrtnFStMWASfb71/OeSLPQKmXsALjt3RsQRn1GCu3KxYbiN4K4DXdHopx9D1/MdH0XZHuzIPA8vo1dGsQNqTkMIhu4ap89Q2rJBnWYfMOaXGnmPGDOKXGWq/mMXwXjtuhi6uwzRXQZvDdGClsWp2eUjHx+D7kBpwsSyvR+fjQAmP1uFvnWeXWskGEusrK59GW7RjVVz/vtLLn7/I3jf/bmjHOWjfE0fFXttKL5md5Xl6Kl+K18FWV1lGdpUljfeVdIFkw7UlKeVDTWULqa0sRxr0VArLjT0QIZQYUeBEegwAp1RixmMBKWDeXqyPJ2SI/jOHKsJ7hoAHJdkaleEPB358j0j0GUEekgYaKgjCnuyCjuRFjAwt8a/Isnla1eajQNwTjwEkj8PIWoqZouhMp70nWEziq3hhy5ky0MrL2LLW6E4CG5mc6+8qJOehWwwrdpQCbYKnfMxP8FdGTy2dvTYC2iDOKMxFoCqTrAgVpEd8bn3O8qH4ip/caajHMNOQ7mzAOGs2UQOo4oIduSiUrl7Wco016QVftzSgNPRtSgD6Mgd7yrukjseZLmmDTrgA1zM7QsG+izatULvK7Ldn+HkjuJu0OmdTOmba+b74n3KBzr7GPyfLxHJLIwnb2S5c7JyF5o+pSUpKGvCSZAXSmOTcPdbiFZN/BYKtOkLBavj73Jn0WV2hOU+mJU7izFSEmliUUmQJ6pi0RyWOytH9fIjK3FVFx96/YI//y1MQWpH6L1+q5W6X+bhmYGIOK+lV7wfKwAg7Ys9wjSVHeVvYTEfIo1oUyo96iaeP/mMYBbGkIH+c0m1ofeoCeeyGr3GEHMZ/0XSSwyl4b1Tgs9kWIyCWcb0BzFkaHxwSZdFH8YYCczpcxgjaTl9IWOmrHmQpWTl2diHmJ71IWZjix70p2XtDX6b4gv9cEKPCmwN1iapwb3WmYC6mxgoreskJ81IFwBtk8hrRAwFHkafHsco56gIKokTQbPtBV7y2krGMI8TsJ+hrzFmr8Q96p20Sx/G2D8Tac+ko/xvdJGhXSp3AaOVmGEEVuNe38v5lX3dIjw6ui+T04bMBgU3mlvC5+/LlPLCUX5vYnRrJgbEjU6IdZ805zfxUe3dAlU3DL1gvIlnYHgKAcARBRjm4qlWhb4aLPp+17u+xitmFvvP+c/1ewLEYptI37p+uDMYWA3ipnrD2o8w7nIDBvKpmA1k9vU2jFNcbdGGbWgxPQ6U3jWgW8heJ0/Gpk1g4Ey27wFpOcQv4t0XTGnJcSkdZXfxQt4N2vNi2lecT/sKSXuH6ZhYg4WjT8KzRujVcjkmSMqlpAsG5wCc1NSx0FyKYtvkP7fJUI5hQw+ZNAQ/xGEFcPYkDUkSc9uXR8TmCXLvhX9CSFkL84yvehE3ka8BEUz7xDND+qFQoIYYSGZScJ8dEQAuwshGRL1kxw1lo0xCxWwEtoZT2LRMw7N1mWcLundBuG1sUNai4pXuM/lOoyuwGmMbt1glVSwhNHvtTFH9CC4O/QA6TUzqxIEiPR1shH9MyHMoH+M/amjmmvtxWYpPZujnEXTHMxnaXBRsoGLymb6SBWky5RYxz8qkKXY2bzxkp87DuD//0I97QrM7Ns00lE6xqIsBfFSLwpcIfYzQM6FfhJ4h9LT8mV52kH/5WF9/ROMhAyVzZmwP2bltiDnYbJv7ZfS0OkJfYl81CndTaSLbK/VC9kmwydwHtWTX3EzdhnbHHuzA3dgod33pAN9MvvbfMKExWO7bxi7hIk+vdi//y/cUZNPJ32nsMvUKmuxGYR/fdgSMw1vx2dmbyTgbLG6VObi3EnV7J6IQ9DS/W9tlOmOk1RTv7HQrNkf5T2mLBHlrMFxiRvQhBuuMpC1w92COFP8A5HpOuxuXvWp5yza5ma6k5lsEX/PhNvskIJlfUXTYpZL0cv5NQxdMj3KYREj22cPoOylnOV3uev1W8luEZi+FIYBAgsmdlhVYAIXHzunShkfdDk+8FxErCpl7v27dr7CEiMwFZWqDmGcpNnTfni5xWyED9XaY/88fAKJ/QPxqpZjewlajsM0o5EahGUlHAV8rf4E75GNhunq1XPxDj6MMDfukGDPU0Bb6lfyBJyOCIjPwZm4pmAWC9fhFXDDXhQ26KLYLdyBgTBORjLXxwUC2Dwu0leKO+pUrgE3TfoFdWI6t+mZ3l+Dl78XF0LM/JFuKurCn96gXb9dbAnCf57wXv12vpat/CX2/GueGWmYaSIPIxZHcHuoWZjAo2oL5s5KajCnFMpeR/2B/Rv4IZCR7Z0zNFbcCST/6Ay0AejEU7Rj/s7fPVLbZAjUJRa0C5Ho2zhH0+u8xLgOevlTnPqIn81sfBEDZrSHQR+sfA0PdeaB8didFRZhE58zEYDH0TirU+NBMHm3m2np+LoMkIm5HfCLJ3I74KF7I0Hu7qbWMQEssNDu0aJa5qAoSEIVrrItzS5KUNozoE/oxDJWhpfUmJMIUiCClk2SDr8UQghbH6rp8sBoPBaMQhGIKwK4qjsa6kLCNqsU/9Qtty3MRMSbpjkRHxfZYYoPStNQJsrttGcHKBFKekJQAw7eJJZmEIU3HiKatJk0YEniRjyuGiMxeGbCVDNzv8QQeZqLl6K4CY8qsGF/HIbQdg+GULeTC7cSAP6rqorYd5LeeBulBNcv6Lqzf5yvKi+oIQLBVh5H9jBxli/3R2IVWSiQD8VedZ8SFb0LX4ctlz/ANp0nwNHO9vstEeLTCpbdglP7ErzGioVk1y1/y0yhwxKj6flWlmlUFZ56DedgcFaUPfdgVRZFKSzzZLqWltCJGU7+WzNXafxPD2PBkevQJC6L/zlCaWbBWsvlxGPPKMVeg2VH+bZ+gefNP9JtJn4xTNTzH+BvQpLmyTcFap+orypVLU4bSBEV6msWTGFVmDrJ8kzOzm/FZE9L/xgegXALH9JdZLi5+acN80cxRoX88+IwmtPsu7hg2XXM3BrJD76HS8uabA/TvYRCPt5g3f3sWBsFrNEI+1wZA8kF+EJJ4w29pW0LN1pR0Z73/jppHUGLsf5f0ZmVUSoByLMmkLT6v4IynE6hMe3S2KwBaKpAkKTmq8offvXD5DBJnvPsfl8/is2S9G7d8BhJumqP8IMyKafB3B/51lGck0Z8HEujPwCR0fiU5Kh6Laci43pUBJKDYGxwrFcxAul5qdZ/K//SvqCmIvgRxK99TRmFY0I1j7oyuvB6jldf9HEPMylKZ0lxRq4+L7iK5BrJFlyeg/YnkLkxbCortSem2RLfYr6l5NmYrwkVkw2PjP3oIN9ezHpCuvdqz7nPaM5L0/Pz8C5ZQcTskhhBEPd0zSbrfZ3Lr7G9MLi+PYyH/DXH5hQu4vIeyPE1Z/vibOC6jf9lRoQJ72q9BWKB6o+6JUCW5LXl4P64VRaXURotpdLyGI+ovp2gu2/g7e/rxjy12bs9WfHU3ES/AhJqaCeTOZpdRfGJ0wVgVRwHU5KhFGAEJFCLeO4oLv+m4DUzvLLovwaQcJ8RgQMVyLmAKuveO8NQAhWtGZcD8nV2Cjl3x1PB5d+B5VzXYiaabiX//D+rLeaxwF8yCWRh8hMdeOcoTMNKKjr7CjuIfLpT72oDyLOij69gLpltqkNhBTrJqRAPEo9ALklOzDnWh//+3cnzU8GSoPfwTOULc3e0nMNZlNyHHWfy1ThM5/nx310VD19zwLkcBHoEme0TlIzhuAeg0ceSQUokjodE/2UEnDXD+6+jhWC/gJE74NU5ifmO0skSsbHEmbf7i2d/S+JnmpUdv7+3Cu9uhYwbi/c6zpykafFwOLepi0hgrMVoN1o0nx9ojB6E0TwfW3769K0rK37ZLUgp/Hd2CSjh88Tu0sfAkHseAUgRNJHmUg3aKh741CfzRR1BOCjUZ4aioRoueBdIQ2iCyhu7+5k8gIy8jwXN7LBYgk+u/kKpYT5fOjmbC7tqNBQXiVjV8BVPsOWpw/yyvuBVGTdghHdTu77TBmMELtjU/U3Iu2oZLzTa8+o70X9pqAtOgDX/YTDKx0FbAf/zjPhHJzUhgBx3lqCBCZcU+vvMYjJm8WUmp7KCR92CIfKMq3wCpoTINA4Jexks5r+DuBugW3AkDlwF6sMJ88HO8Iwcm2T22i5ah3O1naGN5cDfaNJay62jd/SC/5RgupXeYuR6bfk6Ye5ErMV/pif6VKUBdt2II779h4k+kM+SK+QdHcXM3OXQP8nfxZrEGV28ejSf6x9/AEFyM26sYZV8hs5fBDZ5YSKsY5buJVNLgsx4yQ9fi6X+Gn+kf9DGEYJP2Dy5DlD3Ll3xtjgkPKnXqaCmTOzGYlA/6OwKFzuiKnfqwiIVMoJEURQqfRiNC5t57Lt7ouu296LQDDpEwimrST12KrXTZeezfQQt+dtzqhEpz1ScgQiJ6J//F2/37+cxY+lMgAJL5QIzJqox6BfQrC0zH+hsxMzFOkEwtiYgC6At7m4AZuOTSArNJlQ/jAobdpP/Ve86JWAzJz0gR/Ni0F/1CCk9aO2kOnhH6SJSMJjckBpHPomkF/UYkRkFI2zIKSKIhNsAVwZtOIl9x9CyYP21e3LYyGb9zylWI575cqkbbCyahfjUdcUBt+31DtMEwSaMN9j5tHpEDM9wo7OHDv6KGP4AntqzDqsqyozx48pbvKZpbW8umYsiTXJhc1UZsKNFycWsxvVL6Z6qUXvI8FM+4hdP6GQc4gvoEt+DgqgcWRzy8mIUPBAM9FnOE6Db9DpORYXesHh/PjK+ogO+b9L2IDre1q3tFg9JD3rVl6Ki99/9LL9z7mRBID2B9pS+cKjtkGp2OEItN0e0+iljo5R883IeivDCmstK5T4+IYGvSHUn6gIa8jJuQqlS4uNGCsWijLRanhaWyI6J6oxxf1uCM0daiB99Mc4ZmpPGOP4J9upM03Qwr/9sfSTYuoECjmm0yMg6t2PUwfoNv4ZKjpSFlW2q6s6ESjeBU+P+xhko8NjLBIpJ7cFPI/vn14ZHvW1tBz57OpviwAQzMHtYoZlqDk50=
*/