//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// TODO: C++20: deprecate and replace with std::std_remove_cvref
template <typename T>
struct remove_const_and_reference
    : std::remove_const<typename std::remove_reference<T>::type>
{
};

}}} // namespace boost::gil::detail

#endif

/* type_traits.hpp
fOJmokhUHYtkfo5uU6/Deqq+zmUuT39PLtO2IVYFFDVWek8cEfMbhXEnk6A3enQbuYPQHgPfzT+dBq+htncdgwZDRPVUPhbdAq8vIXHGg2jMGR+8Ki8tC+yAcav8o950YUwdUt45qm0KNiSHMpgSe9oKGnyETgb3GQgFlVaaTMuJ9hjiAlYBp/4PmxHgu5mwHtHteVaatBNAWsOqsph7nL4t0tutZ6oB8O+vf7HmgoSAi6CI3CIgigSsgc/PY/zk2VpJtNpVKHaaVxT5mkUBuypQKEazWWjl/1dRvd8uTl3l2+s963vNS9b3EI/1IMU4mfnSaO3scLLt34aH+y1a5xJZ/PXOcb1y37B1tBsy+e++sw4i0gWYncO30WhsUUrDem5JoPVuRhYDaacH0W5K4Yx0xzJx2575Mk+cGbwe9q755KitjcJWEqdnnnZuQqHO0KcRrnKMdG9uZ+hrKgQCWe3ThVyZYhkRTLek2uhwDN6Ue5FOuTq3sgUOU3C/v7bef4UQ4yqdIP3msfFjdpidPe2u+8O/TRKbGD/QfciikA1quhZ84oZc+nb5Vxfyb3MHYm1A35v9vJ2+3y3MBnNimFp822TFSJ2rK/L9TlyaD4ccuC6574UPsCQKv+bQkRx4Sok//TWgynFpTRwuysFRuPcd/5grevCCY7GYjBo5kUCqQBA5dS4uNSQdmWIuPWSYIynf0Bj8E6k4nxHZ1ZJGdGC9I/4lI+SJY7E0XwDZ20rKiAqZZOH2O7L6wu+YkB1rSSMmZBgLC4WBKw4dEXFH/Bb12EFZ/Le5Wf8Qs3/yxXnxyfkgNyTkDKR7XFHafkKyZIUYG5KZ8Ki23fltlhFi5QkCLfZjCzLPIPGEriRpkVIGGMtIynKE4D9P8xowI388kZLaTvYGsffiOuea/ljjBfq73W8uUlOIntSdl1BmAsHh6Vo4z8Zkh0Qn6+zeTd/KtM5odqI+lxlg9znJqX7t0PB4cnQkX7xY45H1Ft8FuSNie3wXp/UbwmtCaXWfO3+JRr7ZnRpYm/D1vn1MLFnIJyyfjdNT1aiKBe20WQaIWOC/3HLh6HAk/j04AOy3s8IocS7b8pPCICXRW10uJsJ7mzuPtNhqh23cT553JyOnsE3vpNTfehzGrOqpvsElvtZq6Wf0hPmraKZQKvLWvZ+4jBFqvoN+d+Jcn7TnUbiUAXPoiGu91eoWIQJtjmkKcL+mTEkJ7k4oh3xuT1EFzAnY0FvVMfU3ElDH5lsHg1WA97UR7Cl3zH8mUD6iq9284I0O0ntGWZIV+c52ddnhXitoL6pqvWHyeMMLXyAuGeTJ37jPt+fmGZjvTKWuIyA9+Fa/F9H/IF1zPegcB2oiDer7U6EPxXms17XqyCPHjuDWNGMFLqQewQKCdk9UXTv0dvU+ZaqavDw9G7xeHmcMdXdgucRsIkXb9x8Ij77zdVdimTT3RqU6a/05UoQ07BQiDfrUXN9Z4RjnWWOYb7mM5/uYfS4jGb5n/bUHDF12Wn24tWo/ekxvg7YV0KQi/OTq5dsFa2Pt5DpJmfSZ0+BXGisJSRHNuCM/R/bP3Fo7nWzKUd47enOZvVLTkwHuu2OwWXvhsSpshNSaEKQ7cIUaIDywsTsL9IJlCJMLEhLBzVS7r+MedsKF+HbLbbXcuezR/nRNrZGEtSGf4YYm8Cas4yUThRrxEWpwPHh//GSb1Toasf3EOcshKQMUSeeBwZbELcNbEpEWtfiTxL+Mu8NaHx9rtbvLvkNPBWtm7KlFVGZV5Y+basw0lCFrlvcSlPB7Satuo3c8oZVkR8FkVKClJpgdlVO+7Mz49Sfv+2+TZTFvFf+zgoteuO9Nor7s+kRl7hl43MLvhb3PMEw11YGt56LgmvV5pKStW82NYpR+uQKtCd16ASRqEiBDOQxj+h9dkvnbd7KRWl7l8z7RX99LRiNuZu6PbDaUUWvZhhCFOY09RyszOUGLA3qheit/kV9ep2yHT7hWBh6+VLSHG7687ghmWeYvfsCTF4QtddyH9Mpg73Da/xlJQbwTu6yAH+z22BhORZ5tNdePrV6j/iSX4Gc4Y/Xn8xZb/o+sNkGt9zt1yP2gU97vJCLYcJQR8UCJ37ghc8PeBzzZn1jgcVOzpcYhwrGhAB8XmWSH+VkzHaVN+t3xXIvDPMcXo+GoQZ9oWOysUFD+ivG8500qZhNnfxV9zyrA8I5Z1Sxjwy7Yb2ZuCfGrQ3YwbXfmMdN+39NHVUmhdR8YDxU/CA5PwJEfUPQISnc5OVB+3t/byx4UEUUbXx5Hrmy5W5WdH4aUPOsRVhTHW+4ya+FFEz5ceMcxM472lP8z3VyJjBKfkmO8E8d95THn5K27d0U496Kz52LbW848t9ku1HlAGI/W9bscHEgOAuWmF31egy/avXEvMaMDgO90ejn1TwpcIjCcF3MiwHKUO4AcKQvSu0iQwPvbia9bNpUfenNNhRjCq0e3cuwXDE31Wf+Oc6UTLdV3AY8yYwsHIlrtJh975BHgpqQfbbU2zeJeidqletWavhBNbkf0ebaavPhVm6/ATH65k/scay0P2TT9e5cRrjNHrFlBLd419grxVN/V1Rradx+S7K3EGr1HNOHctol9d5sJsT2Azpmd6A9C6LqdjzFXREMzvZ/4HmR2YYkN2XlOx5yZAsp8+OrguAQ2Rp017pw9I/hutn/iHvtnuFNARa2EgLPxuBt+6JF2koNeRHDioFfehx1mx+/Cds/jq+5mvCsThSiBMKpchMLbXdzRTIwCMP4Q2t7TNYzBLMHtVTjBYFyyt+JdRzjOJPE4INUriyf81dp7TzjmR1ireCROZ0gu7hU4wmsnYnZfDmE/FvbWy32Vd074lewOTmU13OvW68CsBinnFQ5v7RA7UjUB+HLv/LYgNeook5rejrCdexH+K7QNl4Lold5duGnPw+q3aH7tt7G2epcSwPCMDJ3jfPsLhkp2yp23253UO6T06KDg7ptqVcEWc/nuSWjg/m395EjZKovlxCVrm9/m+NTJb1q+SsCtiGE4AkCvNodUUS9ivU31LD3bo6tiB2Dn7Buw3YQailgW99y7XjwuqBA3/iBEAi/eJWTRt4oIUJjbbm50qukembnZxh7SVMFD6Ng3vNiKvTmBGruv5LNhjSIrK5MMH/y4OHaLYZTqvM+mOxwffXldzJWnk/Jf6UhI3UxlKcYw3QT8Us0D0nInaEXf3ss6nVZcrCFgHS4klfYgtsYS1fe7KFF6+aq0zoA4AMK7CAK5vgUYRO8Y6Ty3xKDwsXymcdUw6SS/ZwgVgPi1lc55vmI2JanH3jvg9r5Aa9Lpqs2qyX1Y+rF549bDHcp2rKFaiHGWlVWoDfTqKurQghpwdgCT1+4nkVuZvSuVRH5xstEsRuovB4K8y1sKTNvwHeX98JLSIle8NRT7CPF7/Y4r0svTdp++eynwEusFzi+flV1fDlzsHGXovXTjY9Xbr2arBo9QeOfrWNsjWyWm5dVcBOygVk9eUnJYzaEeIWoloDu9eClBOzpXyM9oMV2w7fZO3Bt5mUmbca44hJynvD8Ctp2HQ3G4FsklXYz6JtwRgV4eDsDrID6TWR8/6XX0dy9Ibo4+dOXe/iHX6b6xFYRHssH7fkh7n6g92y817QXgg7tTPnJiJ9nIfinn3ByUepIDlNgdmj9KAJyIue6ASjzClY+vZ9B8/9gE3NfyozEFrezcpdqL11FIaq52C/AeZAMIQV4ExidOKNBl5O5cveBRzShAp7WEWnb2zJ0/C1dfvqRXDyrY2SOToAoelvohCOt2vaZHv4wlH1MvKU+NHJMDphUOSk3QhMHVr2MLu+Z0QzNPk3RCTi33yj8yc7tWkn1Mco+om0Nyw5Vfy1c0+qS2HQF8bXeNuv65l9NOQk96u6W9zMLl/4zyoT+gGAKhGub27wFP5HhwCg/DRTxfLQBB8p/47k/kPOwl7ykIRzNv3T7gwlBHJYR0wd98YjFIIhzM5c7XFwEcvtHwev+J485XFRHfDlJGeo3nyLvhbxN2wFgM7IKvtUjK4hhN/CzyutMF/w6V30YdDVyMTnjmtndySCLkzhvzu6MCF76i4t9RPbiSHsp56InI0OSivGKI7lbOvcOWOiS58J3+HI1si/3vDBuRj2EZ1I0D2uf5yTPOuvAQPJX5OSbB7VP3h7LPR8Yv99RdpX8zC4tiRYVMcJMaRZmJKKVOhD0T9QtfUf5JyKLOsxcn/o7s8v1lGzqWyfCmsC1BeC66HWQHVdj+jjlOZt/P/5kPru2jBTJHgNd43siAa4+oXiGmBqf0Wx+NJ64odSAJ/ANMzZcdhPOZL9UoPVgO3+5wSaR+tbYM8Ih6clmMZs6O/OeKwH+XPR6xTaNZr13oVOZPiL1nYq9wsx1YHHa2tS+Fsndm954Nu0a4kP5L83jNU5xIigYJ73VNXAz+yRJ3NX8DobXpdRoslBy6/KWPYN7Bd7pDzv2qhqx+uPRVijzV0HY03NcdsTudj/q1rYuoxm+t+/lO16ReUv65EWutF9C6s+9JsiWRegB6Qu/eZrGXRlkHSd0aYxHccFvqKcuPwRwW7FkuZwffzHhuo3/T+LOcza7SWxVZO5MYZhVxkF//KV1p6Piwy6jtNvckeJRr9dkqi75GYWcRKfcRbUvtnlC6N+I5UKXu6nxWahSam7gwIzR4ZU7tpQGMmEvxJKA4jwR6phA9vQaMGj90y4w9bn30TkB9ObPSjnBj6LzSaJ0m1Ieuq5UGUf+8WzjPEI94EdgUkvlde057J2ukh49/AOYFhUT5e/C+vdA9ueVkIS9HRwtX0c/KZj+Qn3gX+fGxKhTQK+6YADM+2iIS5s5bxqsHR6nbLr85utMu3w+eD1TE/6lsOt3F7cqV6WIvxOi17xlrziprI4m1tz+JAa5Yzb7C5QMTRoAAqJqtUYgno5b+zgKREwYIRaqWv3WZXE0x6u3PHGoXVIHJAb5MnBnEP2VFtQfsaJ4z2ln1OgSBUuXexig9hAV4uyESguM0uHBsNaQHlI9W1fIwDYZEGafo0c+pWTS18iUfq9fup110wziXRcfQY6JP41fEOKu/CeQm5MZa9FhJIGJQfC/ZOAAzqza28ubBN78tne1E9Z0gQtM3jMrNsNbvOJi0v92kruExIWJmKGr/qbm/dezSd78dPpnEOVRle8l4/DATatK31Jyq9fuAqNWRGgVdt6V++RbPKip3C2M/4CQQ/N1Qvo8dSxdCp+gHe23PKbOwUIFdnzwTxtgZCqLGo0JX3IpQqRjEjvwJkJpnTr16IwSHM8iMzQzel6Zi8Zcf8Hpxmnbfvl68CNCW1yQcP36CD3Yp5fHJijpx13hfCsU9lZ4cWROqdQBvt6/swHZJEI1grA9R7d0T2iq6u99SvtHy/zK/0sV/Zn6JUvQgUPplFf7wTHHBeh0185uA78pXZGX+ohR+qZN9n81KKtfoakfa/i/It1oV2JfltshXw2ajuEkuoKeKkoiwoTiMUP5Mfwj0cbCzDos5E2FqJmdVmD4AXuk9FWRdiwQ3oyvnCA6BPCsNFuSyUJp4unQltuFzzZUw3yfTUA6bFFfNPeiFmJ1vaqACi/6fMkYu/SxDVlKLpM9wEtVpBIzNlG4/+/hN49d4vdA/1F4Sdbu32jj6HdPlQE7wGtmWtgEiFr+EXCvvhzXazZGor+Uv5gwjfaSZKY4fw3HMDEaTrO4SR0tV1rNwy1pYvOdUtpfHGC4Rh8p07cwKMg8qVe6q7mlzKA5KVyaL4LRfLZO0jpXDvYNxzbhZU4ZxzHsfZ6ZK23qjobqbg2EK14IbwoHTpaf09gvj+Hi250YDGZqR9+XnyVswlfjpkf4T+2UjLxAX3XkHbRhnBu76aTvs/pUNw7SWan94n8zKGWXynRG8bsilgWDjYYhc9c3KK8+2TjKR7szpDQfPnleFYGzBkLHT9ws823w7xsRqpzbI6spc6UXakljwceLT/gVoB8TE3RkzJ1ywCBlXEMg9l8NQnaw2RYJwPqLzmkWBRrq3zXUnVks3QRQ4JdEHmL6nKfjDf9zjl5o+P9+k+G7p3OAf9/d4FGJIqfr4Nf2+VOdMNGSS1O3kQtSHambJ6HAmbuOYCYPqeWNuYpWVK8xweuNpkR+4+g7Q0RxNjbGV2wo0KFWmsWJzyzUG/aVDnr1fLno3TvYgIIhjm1pfWPn7vUEubA9x6FK2lvo0A43gXYeRCE+ulX5l07U7Hjs0J11iX0iuqtDPkXM8jcH+KKepeeL2kaTq1QKapMjkePJCNHJ1pNHVsHkfhF7mcLdeFDaSa03pBnaiPWgqmaF4rmO0y13/khwyEmUZYtE8pLZJYmW/55s/Mlk6vNSTFewBOAWVroZQRhkZBr1HMR+CfrQi6++oTAqoyOCw4ujGrIw4qAzXS8lC8fzSC189fB3Mp9v07+I0R4oktio4B64qt/CfCsMUc81VXUYdFYWGUHBeKpQH02rcac6b5geutJvopqvjytO9oP9aajvmYsdrOYRYPJcFRQVfy0Dw0sVwrlHa0jWe5pzkC+ChlGKs4MukfzdyLyr/HuQ3k73TwF3aQTDsl+Tj/UdJVEgUOG5C42dXpxaV+PDKxtt0CKGZpfJ6dm6GB4B3c0jqovFbKf3OXY9fwwBQqjZtdcs8p6EEfllvbgTSuV5MmS6bAuYrlzq+AXrxpQpMXDKxty9Y5z+qbJJ4yan+3LY99njAS+f3dvDmmenV1/KInNNybZRSJanlnhYGwwNW0rse82Oo2IFvRS0c2Da9/bL261sdmvGT5ip7v1d/DBscTfV8M6a45C8/u+7+q/KCQ6JrFLJCYK4X4qrCZ9zYYFv4otKlR5us4FyaY5bybHpuQpv4iFXTO3LJ4/yQkjeFa0W7nLDfnJnwbdGyl7eUoDenXE/7aA02PY8bUzeqCgguY9mRMuJPOxPErnTm1jyG2u/QSwyc2J0K/yXbtd9l3lXYRd113+XeJXX4sIr6jnAJA/j49EkYRvij8CfhDzswOx+9/2z9bf3LtEuwa21AfYtdB7OKYgPT87nngxBsy6fcj9p/pv5SGVDUfdRArQp0Vmes+6qBXPVJ7RP9n6O/bLvKu5gGtLesdZ81kHw++8AxfMLpb1dwcoF4Yu5lwRX5Y8VRfxSK+6okksPzIoL/86Mn5l/YeRGEUQLU/6Fu89z6c8R9uhv8XyrmF5KfMLSkCp99SJGL/nTV78JYkn45hA9E/R9Gn/+XEen/Mvr0v4vRH//nyI098e7NBRgK8o6KX+805ysjp+buFmVlVU3Qt8k1tQhKekNePyAckh0rv7X5KDYcScVzIqgpKXTivs0zgEHUVn4mOcVCDVi7s+UqUwTJ5jTw8+qfynklnP9p+lE7A0GTv1tJIP7UqV7wKXOikmPDZvTRWs1GJ1potINEeDPyWSoJGqLDro6lDL1X6KV85dfIefkU7Wph77fRx8Z/B0KEPknXR5dddRR39r0NHfoAhfziorGKG/G5Kg/A9EuQ+0scdxP7OBr7IaqdmXFBIqgN5h0HT87RU+ilvvcF6qoXeWAAjaTBF96dopIRHBvJSFhk7H3uhBuC4mD5M1tR6/sC5C5BICCpgzPJdZqgW2UR9RAh8ckJc92kNd836x5EN3MR92T6i+RB1LPWL4lEK/L5XuVRfoSkJ8zVe93u5LXINxRf3m4jJkJj/iPzddy9IjjzBgCh0TGNumFydILuErA3f4orurn0T/ZjGPXQaOD/9FvpjljBVJRN7zFVIRtOYlMQHZG7Ne4+fSAylT4QTXlhOS9epEZ/q4SMOMrM+iEnzEv+2u/CzeEXi9eBZqJlqkjiG73Mc0geMsSicw7dSQidUU0XLULoF6+7vmSRIBV5vG++xfLHx8HimiJBNQRddfe8D+jO03uh3yGzJLAzLEXUgnqFj3Bj3J0mOPIb4RFfrgUzFMYMGa3Zej2plZJX1k21DIObpaXNlHjGH9O6Vdpno5p6LXKmmFS8O26yi7+1A5wU/Wftmgr/3sZBtBt62GLXcC4lJ5+RE5j4TCDKcuvul6JeEeHmKs+JwBOzq8VYkc4l4q33o5/LCy7xtDcUv69XbEO5I+OerjJVHQyZ+ShzL4ivJJb199ELeQmLiOwb6yclMh9uJIxZYDmjGGNRCRSWQ4P6rvBR1ve0mr2G9zU1oNOys9EShuONAVGRoy/T6jvEBOEIghdCuduyLjfX2Fvxo5I8p6ZPhgXq2FOtUWKlspSmzoCEnVgqgKogbrDRV7MIYvuBE/4KRSUjHoRy5ngLIRr55Qmr4PzmOQv7EaCXc7qoj542zSsvP74tqP7NGco9nwPyzXYCzc4Ivd4g15i89+C2fL0Wb/g4qU0h5wSYjbaoWg+d31Fgl9OxlD0WbwQ8AUyyQOAERHUi68KAtwFQ/OvCyYYQFvrOVlW7tbDXovuU0lhuVKjmscw9zM/7CtHVJNsSDcRRN2fUvDsb89JEBBPwu3vv75yHBy8a40TVhpTMmGeFxfJi1Zj8qJMHjdxc5TFAoWC+G2lQ+bZnCSR3R01jxHOpNJil86CBJDfXfwZWxUmu2xJO2QEWPkbXSPyJ+siVqG9SeirqA6sqttJOs5kfC4Utvx+3esag92VZGt6kDi+el5Ju0KWCL4c0fUDaKGuqJuuciXBSRzsLaRgw4uVp1aMXZ3lqmNdJVFZnXGDvnqyoW4va7vgzG1l+xwIfg7kxEaGfoS/pgikBiIVjnvhCoHyR1X/ydR5T7gCMXXe9HDYGZzBZDrZy9ouHPKSGasOybOwsd3vQS5+vINqBT2fgdDNeLpRI5jonshLrcJi7+zLFn2KvznGcwXigvUpVZ6Tw6+yGvWk3SS6rANc+5IZcs8gL6INxkMmM5iYX9RWmKoHx8QghSjqbXSDd3NJ0cqhvOq4wgosL3cNPqF3R8gsL6JJt5/k1EZwT+NU7AtX5kECqgsYWz9K+z6XVdvKoM5RpfYt8R0pYuOpiXu14WguezJFIuUDd5MGLnd/YTkInXXK4dXHZtoe78Sk3xXpPZhRQty7j3xi8ZnbXHJOjcDxw7vNozGwW6/jQSEFiFveELKXwYOTTff7IWZMAFmqeGPVkvz958LVOJ2vIzWaAnkdRN1KPQMSui4cOAa6OusSTK9EXd/sFKYlP2xzzjwZUgl3evwyJ05nfrGRGqaiuimc=
*/