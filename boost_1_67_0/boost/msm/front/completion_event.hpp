// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H
#define BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H

namespace boost { namespace msm { namespace front
{

    struct none
    {
        // make every event convertible to none.
        // to support standard-conform implementation of pseudo exits.
        none(){}
        template <class Event>
        none(Event const&){}

        typedef int completion_event;
    };

}}}

#endif //BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H


/* completion_event.hpp
EH+YRi/SUtsvTU3bNxBf72TadiE+RSAT9FGE+r6FrBGRkZHJZWQsRmQbEFnpFvchsjaBTNhFGF2zw0L2e3xbqvRa1rBCFPqWURwFmCFx1VqSvztZ63jwbV4fo2Nfyc1UyX1loOy+EhIZXVlCFUGXaHyILgZtT8MLzAj4GN1eGj2lPjZh+RjdXm6EKZDu2McF3nofsr0rNVb0uYcemvq+ctYjtneV3lfeCtCsCU0MfUycmG3LOy68ay64TBWgo4KObu8Wdgnm3VI7m4c2GHfbJnkM3AVNaAfdKiMVEfCcsi1Tqu0kRraovh89KCxSHMmLJLgQW4vIfOyqSMk+ZPa34D7EvlyGrk61zb5UBi3WJuI+FDZxSPPBw04UTR//8ZCppHfkYdv0S1mZWGubqn33j2YfqBbG9Zw0NW2DD9tmX7rDD9falmqRR+XLIXHiXWXJsmz32x+2Lb4U+0OIh3zRkqWMBj9IeBK1oMuGi6bZWVTm/Z22MknC4qIXpjq7dV/wbVEi8aUFoEOX2Tvko20rSurnqctn8Cr8joD/Oxxa7SL5gwpKmNCX+DHqB2zn21dR5nexkvsuSsG96FGZZjpRRXFdix8p5S9W0PMy/i3RWc2fRkyH+Z2wb3fssi8u6H0dvkuKS3ishrrkH+AAXvTr4rzDmt9SNs/2QIZw66uc+ipoPfoqv74qUFLgi49J/MGT0cZhSutYC+gxP2R91oQpHoZd+D4tBrnfWXjAImE4UYX967v1WG2ss/g9BGBMDgSgUvuIKrXaZK8TUsOv8WEWSiVaKO0T14rEgsaIr7S7h6qapa0kBIHhB1TJ1ya3IIZv48NeU2Iu8OohehOI3zXcDxUaU8DBo2Eook+JG7pQQ0tA67Y2TyiwcWFT7WacuxPQNqxwJhoBo5u5BCovayulbrZNnVZFhHUK/ViVF3aE9WG/pFvsTZJHsiiPxBb82GI2Umxt5i9s1lwuBe1ee00Lmx080OCOer+3J8Iu2gcGrWYSmYLKlJmYBRqDaOQArZ7GM4NFdhl95z4GF5xsb3h+Y7Pk8BTE3VUkDiSYWUFf7AGBmZYApSJw4oGZDL8HwuW4LZtdPNsMgaE/jW+90iXyAf/8UWm9uKTiyvWiKBb3Ub6pKC8TafB3lVgmwi71tMuUxeCBbkpUJUn4W5ioxibn+Tc66VUZnF0dULSJTK+C73+TyhEOHI36i7VQJUXqs3bBo31OiAy/WtGqfo5CA6qezWOhgZTacQRfhbLMuQYHRoPS3U1IBeqpybXMgk7rcAk0XV3Y3KqOgJxCaVmSOChDfQ02i5ah+i5ucGhyPbLvfisDCURuKgaTB812UQ6ypiPEIX7XUGcetytau0wrq2jh1OexE2/ErgX9sPDT5vFysTzxsS0WUCe/iIrOjN5Mh0e9pbah1a15MpJlaBDKiqCH6bZzyvqn44r1Dx46Onw6HMFDnogcd/DeT4oRE+fpxT19OARA/H6atRMLmKOqrgFBnBevzFnTVlG+g7EtWYO3vGvwsQ7Yh4wNjM4T3ywcU52FWZd5XBQI9HHGpO9fMBzjm/lZ4LXjsDTTQn9nLjlQJyWqMy11QgxuC2KMINzFD+jYco9ifB3V8xk2LXUgcaOsxB3qIGxrHsWLQQbWkJhp46bvXpmr/PyG37MVP0YIppWo3jqmh3INy52JR/HbMtVNt7BZ8W2OR7Y+x+rIsnkBuqgdD5PWHZFMiD6mN4+x/nEISItZhjdCvc+ycJC9AdRmhLgcBQLDVvh1sdYxfH3Awk7ZfIeFcsb6U6RSLATC7VO8gSV51QFndxotfpB7hv6KIQxlxN9mYW11meUkH7CzD/ADTJLuDKbU6SvgpFQXGy4IFfqiPna6y77HEGdqI0Z5Cj/IiPL/REw5vDD6PpmgeqmaAs2lCyLQ5OGXrwVnVd9cgx6Gz/TqOsIfisLobhxNFUZl/pUoBiWjMBLmX0S4Vyavro+if94eZU2oQLCv21CUEALiDoFPxrdFmpdVApdwiD+eof9im1V2gxBj+CXG9IgQo7kAv401F9RRW0ttgFo/tT5qPdTeRK2TWonaPN2O5qjNUjtOLb5dL9XPtov4eq+Hrax39ugVkC/QqTdN78msqHBK+j3uYexVSuzJLFLZ7PnUnp5tb+GtTmurNoM9i+bD7vYcO62vcJPilR6WqHf36J+3UInlPdvesNbUsR8TJt1aGfX+JAcq/1Tm2Onu/wGqwN5dYUMAgENLlX0LfFNF1nget22AwL1AgCIVyhJdlIqVVm0JrEVLKYKQNDQR6IPdz435ui4+uCm4Wyr1Nm3DGMBvFXE/V91dd1e/9RP28xFExJYIpYry8EVF1ue3/1sLiqi0vJr/OWfuzaOtj6/93SR3HmfOnDlz5szMmTNVCISFMF6MnISeMmUvhKSYk+0/Pc+6zl3ObrNb5ZvESIlJab2g9A5ZPUd8Yd3Tsw1SzB7cAl8wwLnKVcNSg6HbzjxCWbm6BH9nwoBrbnWWqyX4NpSn2rGUtlQQGHvIgrI95LGob5chb1rYQzgRqcExq/lx+CVurRJAKTiovCo5SiyBHLYR49lDuAjnLnfFDiuvWh3RgE2JGpVP+4yPIbxKbmwVFSPpTq/aXY4rYhIbx5oxq8v/3B/TJVAL85yIRmZlXuvyaHi+4d1ZBukTeL6A5zw8Q6BWBqNJEODDaE5a/z1uZU2EwwbEz11jgpE9dkhpNSof9T27DtBprEJJFyoGig0PL7Fby9R9XtpZ6AHJlY37CTjPYE0SASFQmx+nSoOGcFgPwQrWCOFie5aTapmp9AryFBAIFO/0L/lTuuS3LhMkl/rvi2n7GioCpUd9DU1W3ECNiRH64QO+H6lQaQInDKZq8FljH8ZiiQDWdJysaANemB/xujl5RWsEZ2gzRsYO6TXXkFtizyrDunPknmVjeby/7k9E4UOLEC+rhhcQxILrlwNqjC0IcWLQlESQLRhtgupbtCRKr0kMfgRYAHmBrtB9nOoKD9FVjMAb20wzWGsRa0LQ5o4ao7kDOYdHsKYtHOeF9kzOT4izGGyOQ1xot7jUiRwi9E4LyrbFuHxDtMDZBFUO6sshKq3ncQpCpSUV84hezFRejB2LaXwAxSNVzX8k0XDbbkomkH87xHSn+bfAF4dGycrUUEqyfvM56puSh51EkSJ52RlfKN3XXgIyYP3ihTuwed/6JO9o8ETII7Bm7B3QDpm1E9hCexazPVymZpEBmYC2XtCHHMfu+l9cAQUqiVv3VMOQHFpkqdI7FCjS2Fv6jTcnIQNUslZ0qQfOacACUlXU6VL2WjzqS6WEPVeyo/H0Ji87u7rE1/AKl1NiZGQgq+0TCSJAGgQuESNzTMN2gxqhzSOiWoRVjMw3tX0sDXsNENPjXKqHF1xdFaXJhWAMWBmoShYtgVO9mieoQns75bNW5Xg+2qv2snkgn/Dfqb41DzVlxP5oYAqqRBa2iRohH+SFq0w1L9RaQTNbzDtduFoQm4ZCks4vOtNyoamOpU1dhlaz1k5hW3uxvQAL76yw53cW2/OPvPXhR6dfTftNtU+5x5QmBr8ioSsee5+VW469rxy3HOs8lmWHchwulPsSSEhnMhY3cywulFNxS+wLgYMRbnLJnR2drx15i9RELGxO4PIjh3mpkxtQiZRWjT/SYab/OFo8wW8//CAtGyCEFn4tdNbZ85W9RuxV+e8vtBcMRw0CuKag8zZ7wYd19gJgtIJQ8de9jtUCBOWL9w6FbgLodx47wnpgPutW22GQc7OT6sYSEvVxm9vOj5AsqOfr5XctjKVMt/Z/R/sFzmjt51Rr+M+k8waf9SrHZa6fvAqI3sENek/hvgVbayuDoKwQcHS4wp4D5ZNyo96yEAeXvbjh2+usXUibV04e5lTb5/LFdcDd0Rm4CiqcGW+IR3hDfDM/iR0W2u/I26+2zeeKRF4HW2K3+dhcCUZ4AOwLXQ/DZkzpHRa6SxCb0bgVhs1bSgyS46v63GPCAaXNCESXkOISUdvxJuBsA+LajlbYbevhd0vx+Bi8S3UH2fXY28TmZ1AYKbst7jL15rmESxcGOb6Cqkr1nYCTBKBVK8xq8HeLMB6KAcDwu+4TRLD7eSh+xg8Xj4LF5gsVL+gjBN5kuyF3JntdvQpER9c1iTKn6GVuWcHL9IWEBYlCP8ZC45m/gQ7ZhUz5wzQAnssGHLJDxew8p4HyG8EoBp/GYXQY6Exdzxt0JMQNIQxdgoi8p4oaIiGB9a/8L/NalT6hbkHYc77tc5Oy2xhaYs82HzYfhm8JUmSHF1jC86RNx4pOKq3ZnUt7lTZJ+dx4rOhI59Ljx4o+6lx68liR2rn0m8AxFLwI07F3rbjpmNAOuoBjb2eFcr7uFCIayGBmUKu6R7M6e6abnVKfOq2LXAuwI9q0GXC8cHTKQ9xqxQ36CJSV4Kxb53HO8gKILIBwK0Bg99nXGSgtpIM0N2hpYIwdXmyQxgJ73QffI+fy3yu0sLfhe6kWFoLv2fCd3P9g1BAj85a5PWQv/Na/xMhGXIkyn57WFn5sP/xaM1TpNdYXgjyWJzC3hZk9MNT/i+wRcSKRsR316+6JbIHARnugo7yuR1EEN0AzuJ3IVP4rcMg8oBZQj7bS1A/GBxzE2tNvMuIwZjKwZjwmBCwPgxHbiMu9tTB0/vJbfaQZWR0fapy8KH1Y0PQ1CQT9WTECM1QxUpruC40VI05QmD0mMXIIR0WnRdkdU85aiX2aX0NFx/7gkYUGad0a0SDf7Gs4cyEWyGIG0hBA58ksA60yMNuAnGUPLRK6J0CgpYxJkMDmKvOqS2ejaEeG5SMp6GZsL3tPNZ4hE7xfVVdBSNSnnDEyKeAnsJBrCuUCNoIaxIfFQI4YWWRizaiio9hmgnHKbvYQ6fLWoaDCx2UkgiSVeiOp+0LDlKTREyP1cl6aRZhjMYTVr3oJq3c4VlTnZYPXuWHWd9f5l7OS6lzM6/ymejvBFoOBGK7l6rUOTGAWbC+XV50+K7nFMAGUiZChuFFYXDFH9E3VroG6PA6KUK0eHNV3Hd+N6g7HgOZxedle9ZMezTpKDO7pS8aXGQKX60itdVBntVGObZTDhjl+F8+hp3RzFHjKpkTKf+9LqYBO6wSSmYjkGAdV3g44dk9IVM6GkM/MxAoshAosEpDOoKwCgaIagYak4B4YlyBo20wiNirV3W9SUcQQ/8WDuyOEz79xfHL6ETQ4M05QnWbqx2QbJHSH+vP/TI3AekqohPocT9y1FNpPI+pEHbGpMzWiqhsoldSVh5ujWuzQmRoh1Tu02DEQS8hm9iv5w0KaCXWPTNRuPwVZAYCFtbnDNxvXSyCfGw8HeqZF4QfywF71WpAmy7t29Wlgf8FpcEV//i/sTwPIivaLXY19GroJVJYUJhEBSuGp38TUnj6NBFJgko7mJRxNfIVkf8NkVyJQLTq9MKnTqi0YLSEUXE0ITO/HH50FCf5IIOrGTEcvUCasXD+Ge6KAM1wKumhv2vU33HKN07OuIBmTvq8hQRMk2PTYAoNUCs/f5xmkx0oN0o3z4Rveb1qYGjbsRoP0nzfydy6fsxKaW6a7HIT1GTFSvcynnBvKToVh+K8tEiNR1NCvQoGgotQ/Afwp8qUC//HHSR+7pYhLEpqiYCVgSMwtwrWhrCi85gLXS06QODuvpXS+4NHaMWyPGHndh8qCLwRcYVK6jAGaR+XCJAoKhTGOT6WAIKvnJs1VbjIEJsAkBOckiywBuxgpNw2DscRCY2b3pVo4zFXmmto+koa1gSTmUcPK1b9/QR2BnUROcXTJQ8pVv4OP+aAEoKpcicO5fB3HXddvb/aIkVVAlb6h3jDoSbXXipG9+tQl00E2ktwikA1jvyPCSFxRXXBdXFHlBzisfFbtVv9xjUaK07WZrF2MvInnv45BpNJqAVIcu7k38BWor+wmi9eJpqxi5F23et83xOrZuCBzlp2Uh3jVp2ZyNaT/USD6c0FpJifUVXB53erPrqGejuPhW77Qzzh120sE2mnk8sSWCkA5XoATNZxtWQLD4gNFQbRQthdz21M2z/oUnrySr70k9mUsFppnZc049/Li/BtVhElxZrFwZrn2Z5xZ8loJFGteEk9eGFkHv+tzvOoMiaqVkj+f5++ZnZK/Z54VfVDIl7BmNO5z7JUnONXfUY8WQhEMChHUUGQNLhzcat3qzju6Hetcvins7GOvKR9PepnUrf9lr7V1pQVv25gtj1TOzpGtytm0CYd73gf91Px+2Bn7sUnZPkinzf7ZPky3hNL1YrreZJDGHwtSaRXCpX3KmXvEplKQv+bHcDEmnLPcfMJ8ojwE07nQbXa7Gi6gWjv2ovIemKyvuvlXPE5LQrv4eF+5XCdd4WopILIe9S/HufndX9OgPRdL4eLL0p80hmjBQh6Ccpp+8vVCDpJt5EtIuALlU5rxmKuR3WbPrpHCq7OBQ0s9Zep1hE1mD0w60YxanuhTdqHSbAjYGm6hieg9SrdRgVxWqEEua37OiGtggHuOuGG0oOkfrVYIkFBVp5XjjWgUCEIji2UNFSM3WH2z5xggtz0wjUWQJnkdwdPihhdx4635M3w/XJgpPrAbwAx7TfnCGPgy2NE9DjMmN1KbCk3UWCA2NphReN8AsqOV5oy5u9Btvticg+EvrFvhpTXXLPgCtr8E18B7jkxoVT7KS0NjUIdZDF4HKX2g2vva55oEQPdpOqgusOZtiP0b6vsggLpUE/WbJADT08ZpAPpMKQAeIgDlAOA5DuBhBPA3BLC4gk7bsHegBad08QF+M9oFNOMSp7PG7C/C6D2g4y85QTp+1+2UL5dOClG+bhWGl8X5ClDaquyx0mEa9o76tkraWNc8Sj/Lf72e/iVKXxRPfwNP/4SWfhwiz+Y56ZgRZDigvq9yxC4YKaaMThtRTKsW8ymuHG5sRMtkL9sD1TZMNPpCAVP7XFpSV/ed0DXDxnQzMYUUfqgFYsq8vnbDJEw7on2uxO0ZEmnfB1QAQ8BUsnbdg2XMW+PUCrgopYBbE5n+YtIKWFznQugTUqD/LJGwLhn6ZKzS6DKq1X/18lqlGbUR3VIO414+9TzByT5UnzqjnXYVG6/F0oB3u5BxWR50m8vLQGDnOD1e9T9ySZnCqSm04HuABnEEyOu5XF5fBX226zGD1sA3nIK3+1Gmqds1XU+h88LDfKGbNF4SI807aTJnDM2FyRyeIoDZ8chQOcyOXexbdeP/02Z1YuMfyPJWMNTOb1hMy+Y+NlfwhZqtPNxYOwzGpdBGJEv3pcwrTQPlJ1x8+dBQMwWNZlH2BsxuLnzF5coizIakApL5lN9a58gTxMgCKzvU9nlauPiBgkRP7Dk8GVXqHEidJSiqURMHG4XzwHcgJHBDhC22gXqACgtMGvPlJaBNMNluk69gsRqTR+2FITfsEWpMZepNRdQIU9Nw1wfPmO2F8RYhZgbeARCkfeH6lPoA5lliLyhTf08DtoXNk/TNjqTdgaTtD1oenxrfHTDJGf4WkLLdSwCVbMDUxscs1oyJPW5ajbbC2DQyPpo9SaNZ9xUpUHHPoSC+6C7I0/378fxcBk/kdKlnudqAKx5l6n/PILZKCHSlzr7QIGd51dGXYdkVfMDrgcHVqx4kjrK61dXxXInxPDzfILgNUj485+HZAs+yJQbpFviuh2d/GeiN8M7g+0Z4/heelfD+CTxvw3MSHn857dmYJSEtXdL+MgQBPi1Dhg6jV8FqhTf4h7/h0ghJEvutp+PGXI1RDfZoi4we3F5Tdm0ju6XAEI+6wES41xhA/a3uie8PmFivtl2CWwROj6pYaOzBI7TJGo2rHCFKbJEU7AivlAJSjREAjeXFVVUu1TZiHG1ub3gX/gpUJu83ofmBsz2D+3TgF1wcSt168CZ2Nxp9GD5C20w4wvVBx9Vcd1leldcKxeHQ9uw6HXhik4PvykhiMJ9gcwy0XZn4vg/flRll1PdQcKKkvjYrviuTmbzbExaKzK01RlBYk7a5tugsl53Y5hKD4aR9HsmptszS18Qkx1yDTFP0G3FrRqs436CpoW2YlO0lpfU8FZaybVXujFOOb8/I12sUysetmW+W4p7LmPwUKml7NzY9gUv9Ji8lAbWiky9KQRi1I2X55o9aFqfalppFX+8G/sKdQRiI5YtOl2QLoHbV5xsCMAEpWdZ9qUe9HLDtntCDm/ImQ0okcOMF0mQF0GvuRdcvoaYncbBuwiE7MEKMLFqWd7jnKx7KNmNoWHgQ7QCc6qfTkSQUZAtjUFmoCblcfY0ittHaoiXYEWrCYV+eF2yVb2BNPH2Q0tcYXOobmJhC2WZMF7ZSnAsaQ/3HdOoBDYtwxd2sLcqBmIimrvdj/6q3GALZLB3XanlbOP2WJ4hd75uhbW5WRdkiK7CAta1rqPKxMW+ffEmwdftUSBVI2+6ELzZW417QMz0ztEkP5CrJftIEwEe4/HWYCpef9WRXJoD7lPplxsBSX3vTveTET+vygeUedWmfvta4SGsoTuDtn/HCjyPYETiN1BBw+b95gtTdA1chfBvCfwq9vwWeQjSehsguGZ1ias0+zKOm0U6J0G1W9sU8oSZcFFY/xlnGImsRziKabjNqxs1V/fffgH6sSSbF1StPQZg4FwF+G3kFwcStXjSwojSkwdaBUhuLBabp5VvYLiywG/D4dRHvar0NMRx014qv4Fe3BfseEOBar/r3HH1aNDmxGy39Bbj8CdrUPMrVBhwPog2LCJnuDA0HqI0U2oWToBBhE2qqg8/q9qZ1GmoDa6hxtlEe568AUP5cLKkUPtSs+XQ+AAcs+NNF5z5sLnPUqzNgmfqTHJ0pUTQ/TdGJWIGqIQVjsgfdvJRzNtcYPOcPmKo8bG0GHg8RJ6ifTtO7EKOkELsJe8Dr04jLjY9iFN8prY56u9PI3EQNT4tvKLcTbGqAsZxuZf7HoSIwpP7tSo0Pq0FsUM+btd3AjS6GK7tIRxSDqOgquwjG6nH+JiTGq0iMD5AYYiknBu+3s140cC8Kyi7yLynP5pgrnxsdZ2WRtTHr9rCw3fxGYamw6o4UMWrSxCjv/9aQ8GL3YpitFlL1am/YxPFjti0O2/baywAOALFuWTXpB4Dg3jKBuGvXct5WTNgxmPWDlsUhvCiXsM29ZI6lUcvpF/4K9d1JbCZP17pWZfQHio4=
*/