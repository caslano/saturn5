# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_VARIADIC_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_SEQ(...) BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))
# endif
#
# endif

/* to_seq.hpp
ggafL+yp5wgau4uJWgab1ag8qGhz7cKhroMkHBeup6YibWi++PBRDB5/Ynbti3nfNJr+9vzTmm4jBYh7GnU134h92HdvDlVG1ai47ptjCEWPY5BDcLtH/HE14a7NpHpqxffVLUYJ5ZuucTh2FWImlA9LoAE68hy21ht4eBqN4fl8kRwejYenuDPYW/U0iM3b5fgMOqGPj/+nnxufRn18Ou89a3wa9fH5hl+kKMVCKa5Tiuv9Cdhd574+t5BAWcAAY/UBKMh1Kr9MiHNMGp4UFWO+Ro8b0eMb6JZm6zvPyR4nhz0Hc8MekRsD8ngqJuPcYjLbUFDrV7GCmnC7J/JOPg1S2LOeUIqH/fVHTmv5jDyws1hP2DNdYoRFVJhg+t2gJoSfR9oUDDujTyzH3SbgzHou6NsADyUs1yIDMTLeqhYjofz562hkIISJQE+qWfQe26LN4BFv0Ef8pr0Y8To1elY/CGJNN4BUemrEmT1nlWhoAeGMiyZZc3krLcYWHGZwfQewZc2uyk67HCJDdjp8gybE73Ebuo0rWLdxldRt8MmEW4gGsW6jN1AnZ5j417fHoN/4TJ4zWlQV03vyGduTxgEH0crk5tIdoCF54rZqfuyremx5XnF+I8hP8FKRRZ/rRyQ+bdUr6kd5QhXDaH5/y+2ODM6TapZNeo7gF1DmH8gTBxe1avqBa1t5M7B85ypdqSlupVnj75WpzaxKrofdxjpoeMvXTOrvIDxXdoAFVJZCBaDsqOX7Gr6v4/uDfF/Pv8zmc0RkhaM7Kzua+TfKv7w1tKODfzv5F9RI2WHhXyv/2vjXwb8p/JvGv4P5N51/h/DvUP4dxr/D+XcE/4IPrlqKtYc1YLxC+aQCknHvUOsJhKQtlM9Jooqe9yBU4vRjmMIrS7FqvXryGGI0yjw9xN5fIFAQHnc/gXBAnfKFVTwx5zi9gIab3ZHugBaGGs6/Dv6VOnCsf4joVFPFM6B3ZkW+sgM7gjLauIRcN4W5I7tNUy+E0BGq1jL3KktXc+41/LuWf9fz76v8u5F/3+Tft/kXDPRY3QpDYV2tsoO3qXbwQYQdfGyB9/mVlV5+u5h/S/mXLefZYF9ZCZZc+ySzQsZAV5ZiTMNL2eJY2TGVM07n3+38Kwc+yh+Fl7KZWtVS7P4ztaYkadP2CXztic+X/kgclwXnVfn4AdWyA5v2zjFQ+9GIJ7GtuIE2hfz7EP9CgodfXIUDnqN5QDCi8pUr5cnBPyUSlteHdSyXuK1HCY6k6SrpjX8/57AaDGFNwS/loNFg9RJLTrRqclj2IEDm/r4ntTgc8BUej8eVydBqMRbB5f0b9UCkGLL95jhif8Zw8TF+HC0fzVUJwFix/VKUh2n1PqYg1gDFKaY8jph+mHggdJQwlhN2ywSEPR7+eMy7/qD3Tmri72GAYXR5DcBwC8BwWA1JRk9aI3qshvUcqyuucu/WTaTDQSQonvpctpFGpVLxiGiJ/0npuLyClY57oHTcT1xXeCeHVWhnl6TlSrCmyl3doUr7SiXYKU0ulaBQsDUyfTjrqKvFfIQbYR0llVR6iNAG0eZqqaC/gPu2qlSUp5bWSecEEgH+ApF8wfBAgTrB6pzXGpjm3MSMvsO1jRl9qzTuWzQmPGFETHa1l8EEQuQPI5Z0E7BfdWTulQYeefbVlYiuUA/Tb7hibbqDfsITxnuJtYmx8EPEoGEwEydKflC3RMbOMJ/wgsNVtbiOVtK4GoNXiKaM/0VtZ1VkL9sPBt2MpdvQrjmDYlGSM9hcMkq8QEWqd1rVia2ZH7v2U1vsq3cq8JykerZP0RYMi2vaBumjlRvGQm5gAYG1uE6tcp2xl+ZCc2In8CqeOggsec4Fw4IklqRpC1JIONEW0GJbo6XeMxy2C/VhdzUtOf2OayIVDaDeuHgLnHsTVjE1Yp1CpGD6JE/4KL8zWBdUncFae1kGFDI02N8MoFQ+yhIY5E/I0zaNx5YR2/EY9zCY0E9nzNFPZ1wl1l4tK5YWtiwy9MDZF9CbXL1qDoK8Tzy+k22FhorC7t/8oXLJLtCi3Dx/gi/uE7nXUa3jqqgLRjWx5Cn2FCeN9n44xPINo/zz7+m7SC+/T0Iak0OTT10HIpJP4Aym0nQ8nxsQ7BU6nbAoSVtgiSRrW0Ag6NU1f2th1kMXkViK1oNS4Px35t7ZoQ+0ma7KgMN/0xT6l6tWi7xNLQiimZxrJFFmHMrhQJzUvHywPfvF7H3af9s+BpXsBHnYsjxGJWvmpjrEHQJr4WSL+N3xY7ADlV6zLWJ076jGsb2sRGdnKBw7KHQv/BDiM3WihWhe09ZDx6Q95Nk+CD0ACiz10zd1HTslLmSkmWoebdQsfmP92VPl9w3nU+WwQUB0sRQWRxLgzXHZNTjrjrmVVM5h+iYTI/TbXvCx0ixjwhM7DfIZt0ubdOFxlj72C6VX7Dg4veAyi4W49ULeaS1ZLqPC6UexX1xG4GvtRwPkvfHco9hvtEHzuTw+9EHJya5e598Y12u9wOxl6LURlo7x5973SOq3iWMjzz4+AjNS4TujybMcOMeho96Ad1jafpSkbXUpEC5H7FnW5UNkSTMCHHcPEkLiMMdSKWv9SYNVb5L4fnsLu87v9zUJyCZs6QQm5+2A1U1euAw7jDglmnQfH59DvqavkC8vHMY7HGMbTyRh1lw2wwijVPmVV/TrGYsnIf3lzhSjp8UZXqjTOJ5x2cdF+bphQW2xh9jZsr1F2a7q4ttUZqZU29NO24v20n0mGN3BhjPdFBygR54y8xR6lDC06Q16n6vDJfHv+pTsuz3eglRxWyNj2ID0O7kBLQ1Ir4YB6SVsQLof6VnD1FuJWti94pUHYRdAE873FptAHyk7EnyfKmw/jYkV14LoD5p2iTzCSMx8Fd76jFkH0mJ44OIbULOZ8Z6mCV1+/wn76QhcIf1vTKJJo77AahI2yJg4RVmJJ5z6qYiPoPRXpJa1lTjCeVreFOUZPIp1Zzgm7zP4Us9yu+t4MeVJiOV5QuZhcpH+CZPHnhzQFwFW9AC9upBCUL8uvAw8itSXWCBQ7PeKFf6ftFDJcFOg38u7dw+kWVhkxblfKOt1OWNY+T2Y4XeVAtcRE0I81HZSyzwyTj1QOjvNXnodljvma73i6R9atDBztyhkCT+t1Z8e46f1+tMD/PSq/pTPTxv1p4n89Kb+5OKnt/Wna/hps/50MZ7c1swjXoRIsQr7D+xi1bVrodXFc4n9t8I3T/KqNi1fd/szeHWbPtWc7sbgKKUgqq5ji4+rVE/U5Wksvpzxa6oKEwdC5EnqtIZwylPhHMsU8RVRRc0dJRz6RI7yGUSxkoZFsPn5B02dpVgV+PR0I1sAhU9ikaxv+ozyiKx3WzRtC8AlPv8EcS4ALcr7IT+slQ8V/LBePmzih1flw2v8sFE+vMQPb8qHFfzwtnxYxA+b5cOjnzCFOVOLncoD4v5PjvOafWJlGxRUet8vQp/tpVJ3SpOKI0wGa5Hx3mfbNOrwF/l4+PJZhCFHD3HA6WOiN5QKeia+IhCL3qE4j1TFVhM8liWJSeV8DkEXy96zRDUJvB9fZwA91KHPBv/Q8s+BbP9aQg0/qRRHM4+4TgeSnLPT2Zb7iSTWU2zlk7HJhaOGZnn5yEW6mdH6KKYzuK5V2wknL9e096m/7oPI0QAeYkI620sry4ogLv1hjoPaMqWNgFEs6GuL3xFJ9NsOi+lsyibUHuqdFpxhhAKFRBuL4jmouGuIZ3VeOAfGDL2PJt1Nf48W1EXMR6fVqe6ocw1kp+DjR911nzd92dC2e/yT1x5xH6z31MUdzbmuyGQ6QuVw+heV4uIiELUaNr2r9RFfATdTBHni1MTOWa2aeovPR+THJ229/+fH43AwUxFquCTpydvYlEp7cRjV2lQBJfreo3W+cDkoVi6Nzvw1J0ATxqs9qB/qBItaHFXcjZkVPm/4aYh/YprM0E9dxhI+tWIZJL6IXXU3qp4G6jR1XfFQY2upT4eF0aurj7hru/dqxgLuldohO3X7Ai5OKaYeIRaWFmzQu3SsoBWxioi2cq+0vwJkGCJ0Qvz2S1bANYqmpmOaVONixrZtwVEzDvTTK5/f7/34mBaLc0wY1vROiybull83izfwNdS6+eAIxNazPm8WT8V/HqgUl8ovD4pH8GWJ/mWiKD7ry4PC2+3LZUJ8wV/Wi5vw5SL9S7MYd9aX9WJA/Jf20omasf6wLAHsgfxtLwWZkF5y/nQNcREEe0iZrl2BVIZlta8QcBFLsI3BwSLpW1SplDcTb0PzZSjxixpPjCxZsjoQ9HHZbkjuU4ZWLcMhjoRYLeO6akmiWgb4wFlV+xMKAUBxwbnVRLkaGTTpf1tVE6K3+eeJz4bBmdMMQgxoa6ixg5hrb1QP6N26b/QpraoHnB5xnbJ41CuroCKeiy+iBxUxmItoVg8Ybb7ov5ZxZ3wZ1lgZB6mMxEIMv/jc9R/LQAK6nWM2/AV1ZugsH4rsiUB1BI4krLg6GmDV9YqhWw14ojCq+aZuIIRNxp3DCuuJD1cmWJXZNmXCaLFCO6adA1vqhZIR14tesV7UUy/MhUBFkRLrhfol6vF164OMI7V/H7TEB3G7i2+heBfl+2K64z/vY62kuK6YmOPQu8BSU15gmJrKHMPHRZdK9sT1WXFavnom41Q4v4uNOfQjGIldasIsbT2WsNjnN6gj+fO2oqEqZ81X32WDxFN3utpnF/cPB25ImJKncMnimR+Zn0EhWPo0/lSE2mJnqRBHJ+XeFmj1TWpHoC9sjeVi4z1zLBYTxD+ivI+Flpf2J4GrxOi0iP1bT7Iz0B69K5r+itmQdoTnc4X4xbfHtG1Q5WZqPlh+Pfo3mF7JCe3jHO79x7oZZz3wV6JBdZ/z99XiSnwPdPQxDco86/NqkRz/OdGgdfLL3eJfjfTlQv3LRHHyr2zztd7HL2s/PIanZ8Pr0D34f3txIWGB2VnUGhy6DUuCT1TxF/ZSP5EYn6EMfZE/tJdOA91Zij00qZikwrIQbM1V5a7BTJWOoBuU4kbexmjWPlGJrq/EBwhWzH43tDxx2dMk5LprQsU15pKamCD8NbEdsYd26Zjuyg7mTDPptrYcdnO1XkQ1LD4o90i0T/xwclErlW9qwhT4lfRqq3DuVfXsBgIO2wtcrMbtJXxbwfHP9vLeyJ+fkMf4reXffEoy2d8eN8HisIJtvkgqYz+3++DD8LGUzApXO+KHB5up09+DIfFYhZYU1fL9PekWo/xVVhT4ELjKizikeD87mx0Gc9xw8fWHqB5u6aGuE89VH8OJTerZxM3YSw9MhBiSxWLIU/HnNa9BZZOt4uuveRfyIvgOxfOzKM/d7E8I7bHlxc5vkpSyXff8eT3VILY8zl0sF3ONLVQ4RdMMp2gmkl07NT7jynFTq5KH+Il8rARH0N091FmBkXGGOvxYmjwaY9pATI//NEz0Y64WqI4hXQFCwpMsG3K1oGB14nYeHuP8ywTdU7MuGF9DPE0h9GDiuyvOlrSTvcKJDciviuD1rPGX1KVyk9/oWFfcuQG5nZq6zAZ6DRfmK4eAQ1mKZ1Fb2qaFlyHBK9PF08uIpV/WkIgs+FWXOTg7ftVlKWYOP4g/cZHkiEaEFJQHMIqMI51aTJpTn+EP3VZVwUeKw3DLpYt6NDiFaLlo/Zw3eexyIe8wMQGHsCzpjaV8DujNRQtMhl7G8lCqQ7a5yg3du0m8XkZNXwkWFprmsXsIIVYO1p8y+SlNf7qcnnTVcHEOMdx/WNDlfrrbAfnBPrUAccrUSQtD9y80wTfWpIcUTwNRGwYgQAyXDO461ZwP3S1N9EkPQTEJChAO6merTBu6o0NQhA7QrBoCF6FDdFe1aofqriOpsYDWCtcS8HDFU1QFbh7UAWHLEtXkHwJHOdq8VpI2tSmFoeIhWsAqj0rT1/JQVS1wyV1P6KSMW6i6G2bPUsY9BLz6aLyM0yl6vdmi1ZB0sAzgPBAEOMVN7xHS780lvFrZnMiogEET26qlC/xbUOh+ob3TCV+rYU+NeF1rkV7A94nbR/CkrhHvJR4nWVYh7msdGl8yk4Sg5QPpUxc/28O9UcxSdChsWePFbgc+u5q+Vxm7XG6xyAxP1CsZU2Sap5nSPM3jFE6URS3cEF6HkfQZZXyXSWVwm13WRXYfCCuSDyDZGl43WOZtUDgLv9p89heyoN/rX6Sf+8Vvfv6LB/kLLUiErJfMjdS/JhhBDmrEx2cIVit5dhAQb7iT0G14EMbii1/v2v5sERf81KUhG3nZuRqyIQEMlV4QTMeWNvIcredfsJ8gW+9/yIw+w06CTFje4InVh1hnxn9RtwerJQ3s85VqJeuF2v7Uor1/AF+Kz17vyg24ide75w58/P5+zvjnuIwAl1hyVsY/SbJ13aVn6e/6aFu4GSWnujR4oMEwLZl7E0HnvIDcrvoaGHrNY/qEF3+4GUgq571C+L0yro9//pi3Krnck/XH2NhArJGJ3ItGmZgoQjKRW3yA96JAQVjOuGYRkQ+27RDLoP3fI5Y/JlvCoVteeZQHoCSLBIs3sR64rVmSiqpLma4Ih1fU7CTCUuGYwU628I47XVFyNaKE9QsvRWO8CM3yDUErkiKplTcXK6SIYsHcbdPmZxXWPpPiEKbP9E3tDHV540Xsx+YSWqG2PkzTEF4EUowDCV7ds0qanKe9XZ28shJcse45K4/pOoKUdwm6mx81fPUwWn34CK0v4EjE0vRzNbnzCQ7iN49iebnj8EDDvet7+89oVclTf5XqqFo6gj4dum+gdO3Kb3uOOoXzHz11tb3XMivmwfMeVIYtS3H+z1T2B6xlqY/GqY1lJeL3VJ8xNS5I75oa5aZHabEjSNziai/GYYtyDeNSnXHA1bJoWDh7sVe8tsFkmuGqKk4uX0yvdoWXspG5eHoDjJxnlGNdX5io7tFd8bkdR9yOl3z1fdZQwXkZO9Vo/kdnRPUvsD6nqAU2hCmeZlVPZZxRih2KUy220d3jtvDoAR91ZNQpjzuUx9Mo0Vxlbp+t5FqV3HR1mkN5ZMgsZYZFmZGijB2s5A5Vxg7r8qt5xI1YH0fvHmI94rYdHTxEbPuryVTf5+3LUxyh3Y76keupIWLCLxD/UF9Qjy5ZLpHvaJpKn4wtwl/H0SXo39G0eJ8GythAl6dMWoC96aGvz4Q+6OVVvOni3adbNF1rSpOvNw1Vi5ixBjqkWU1rP2k1PJI6fOphZdxo1Z2SZ98StCnjslQ3iSbFg6vMb1LTlHHjxcIzMOdOocZUCqt9S1Q8yAkOTnAg4S5KsG/x0H1FZYO1dyXdp/CNMm5EaMywlDSHNchhvBA/3qKllg7HMUk4JTYlKONGhcdBf5ZGy9tjWdpjo0kOgSCk7iIopv3cOWHwrM4Qjk3Yy75PwAngf3uiUvV0qDSJKjP2sLv5UMUZjrTSmkGMZJ+XZrdranGdq6M4iZb1SJLaAV1WFcwwFz+elBOqPpMVsEygV0fcImy5nkqQiKNGPzqjBOvq+zR8RwTsqQeAki+FHmg0oYqMaNjSV3HvVtGkg2HLIsVdrVbRt4q7/qPi+lBxY0Iwy58jOgbzBCE+uzpwiTdsuZVAUMeNNLsPemF4a9I2wUJLTMHGoYrTIF7tEatYsQse9KthCB0Uiruhyl2L000kktjpD5efTeWvQflEW66yb5lW6++RD2b0Ay3YUPmVtfcH/JMry1erRfQnSanjarmCa6lPcDc4g4KIi3s3wlGYqcrQw7V2zVMTfJ6ruo2qukav6nKSks2eBuJAU26dQr0J3+HUcMbKqEY5t5r3d9I6WtyIHQ4MSn3YdmuGu0GP0Qf9pLuRXifaV+yWOCGP/X7r6vKuya49wpOLcsMcj5X+YPrkepWlHLl7/Fc0xvPT4eMlth2YF/MPwgFTkpNoFO0PsyzU5twk8ao+QYp3OHvXbdOescrdrHpEhrsxw9PgqiweqNKduzmPWm52C256e503Ys9wC7MeG4ie87g4yR56mgkl3Y2EgrPaz/hzwvMSVP5WCdaABBGj2GiWMPhIQ1CZfRdICA9C44PVanV+PIJc3xkPVzXX6p0i5lYe1464a8KWm6rc8KxrOlywnTAl2QRlY4Xqrgg9UE93BwmTeEbUH15cSKhd59ku3r0Ped7ktMV62gZOKyc0oPV/JdyhHXHXKu6a+pGFgRRHfdLbaorjaMGrxOBmuBGzRnUfzKjyipOIp5CjuN8WPdEDxb1ZLpeBkYeF30FdqdNgTZBG9NFx1P2qJJNvg0w+/gXitG/26l2cfDp+N5D7CfRZXAEsfTMB/ShPcNcRXtrLFhBoQu56S6i4Ps2+4hJ60ggEwQrNUxsqrjXZnz6DRe/lB4116Cih0NEk67M0Li2HK45+/2XD0cPQ3PakF0fXAZuOutMOVxoKXUpOO7qOqbHbYSQm0/3RWUVHs4uM3izlHNSho0u5COrThqPthOzpJomagUFqdjqBIgXnir1n7ZcRbg6We++Gj4ceXliWGD4xaLH33om4xjFHCnFBdeAypRlOl+AiJf48v4G9IH8klz1YYX4p9LUZkf0SXdW0TFb7E3CYWFkJ092uGDqI/PnoKMOlE1iAg5NbiLFab2Ke5Tx22WsTX8AgWUYDRZfO3QSMtVZ3Mz5teovWLWdsm69FPDr57Hf6WpYAKT6WitVswmTdGxG+uxkPbitxvZbMvRGzmkNTX1cpZqcTqe3zcxV20RHuk7J0bfeeWbp69p/H7Oe0B3lqJYl1mW0k2BEpaSZOVwm2KkF9MPynpWcTnS5EZ6kfuTxWEomIDXF3sA9Yj7XEqnisRHzdNDs6Mioh/LnF5w9YMz+klemLk+LTG7vFN/p/WTl7H5VO0g6L+gesX+wVf5nFmguzOwoc+BVXY8TYia9GxlAB1p3MPMK+AePCOMm6lIuUWRZ1QiAn4MoJzpA4qHtkexoTRNxGdVG9f8S8QYjfrtZQQy6nl8pFkYuOTijKzVUPYDbZoZx7GpiqTmsO39EvWemrZFuAr8Q9YpV4f2R3qGRWIOSmYlbGWZRxVmWcTR0byMnLDwzNCfT0yeNOETccC4lBKBonQRQYU/cn7iJU0T9yATPx2pn4dz35XU94unW3qqfDQcGHWsbZMsZZDMKvjrNmmI0HnzwbwuyN7uEQk7zLIdbFdxAC15UdCVw=
*/