/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/functional/invocation.hpp>
#include <boost/fusion/functional/adapter.hpp>
#include <boost/fusion/functional/generation.hpp>

#endif


/* functional.hpp
axiP2nVBQbRvIJVTDLeunlZmc+RqymLz8zUi7AC0MrGQk+64+ocaZzGnB6Ni1lXPm2PSjTTHFS2q9MtKU7KK5Ii/BoXVxR9jydumsbscYQKjsW50lKA/MHv2d/Zw5bhbFyd1wmJniZzVWwFN4sAlAh/9DFe0PGeGoLEAwp660EFhid0y7BdhIaNyElt3LRhrbWc2UyW10Lx+LShiVzwbju/UKs60Gey5qGHv6TNojeJZL8EXvBsqCdv9kR4dbMU5PELOvA7bCfZ45r4crYLKZKrvFUI4dGBQ3id2FVV6GcipRPHwkz8A2UBOqREUgRsLoacMYKCrqmR6MianA0Q+PgG1RsbEecM+/sI4H2UnXlnrNj1+wd57KR04xoIBWUvRemDnI0rHd39yGrwsXeUUSUtrcc2DxH6npyeBVwdtC+akEJXOZh/4cbKXpnJULkv0nqB+ABrpaXYfMdS3EHkNh71p09wgzVi/ZVHbe0RkUzeorRMnN9QncHM5pHB8fZSCxQS28CMVammHVPvzhKHTnYmf3l6BCNhTrl5J/9Drb9zzR+ol1SirfEqbQtPTwdA054DaL5cn8UlxemMn2ZVHIKn9LcDKHZbGhbJuxYo3RN/FbZ74NOWAGIOKmJItNhooaDc7qQMhcpklcbZMMDvTA1doEbr8W0p98lEMUNNqN/A4ur7aFfBgtowOyRBR7diZfoLzkzA20XcrT+0s0UmBVSNi5NIWeZEfHiRtCoebIw6EAh0f0KZKrHHhGiaYeOSe1d3wL2aytZ9ha+8ysY0PYMSDblvCLg3S/qV42+CibmlTOrhNLE4YlP6y5ZY19bVm801y740r94b2aqkiok9N2VYI6CrZOs0GY1qTcf3X4p+XW/FSdvDgvRkwdvDLwdxiNnCcT814m+zo6udIAXwwrbrc1dTrNVltM+Q5//QwbgEk07d/6an7GtW300CCeyrta/09cTixVxqF7741TQeZ53T5vVJNYcU5oThvFWM/eUCVs6fb2q8ng7ll5NmVMwmuq2sBgzfCfC6tTo+MrGfJrtGJrmWyoyAvi3yueXScmfvW6NcprtZ9YSE3MltBpKNCfJFnsaL1i/gmEimuWcJr9Bv8T/ph/IYf8L30T4vH0XxgPk6XumCFUf+G7T82MTpLqIt1pFhKziSFzmzWn3UJdNtpS2TRV5rNV1jIKnY5BtmlVI7a6ftpVUO0KyJdkazLqdJgnxPuaoLKmpgVh+NOpjj2O0760jjSGeHjjrLZqGGIdlk6EXRFa4kuKXuWItgHZBEZ+Pb5H4pw9ZCM6UFtl+fAK2XKnvZEAzWh8mWI5rzcp43WY4X+uVFaUs7Bz1ytLr3EIZLmNobwirpHLL64peltKx9KvMNTGBeh42s42UPf7kO8zzXXurwzp8mFGPqhakBye2G+4ngnDMxAubk8tcZs14Eji38C3TO3/sB6qK/kt/ATEkKCx1jFz9uLcNoVPgtXJHPRLno2p/CKVk1A4+YyUwA2UzHm1GVeh3+Kgl5jBBDzOJv3GsPZOLb3Tiw5mhYqQG+0U3lxr+y71kwY1rqt7IfWDMBmz1fo3Ju25VfqjFMWwa+/VUtC4LMHLL1/NntUG6/2I0hjzEDgyCPCZhd15gZN6emX6q7au/74ZVXrLN63ASsWph5w3FLaDHyLw/ZOrQtYU+84NLXrEZ20BbVqRwDZVO4tFzv79nkW8wqbhV87AnyFE/3rbFId7HipwD8s0KGcMRt9B8PVgm9+Imhuht2IDBUemcoI7ajLt5WHXKCE3q4SNs0crS+9a1U7kptm/qg0O++blsNVA0eVRceSrubOYXvxeuFtAy3Nqqx1hkE4eWOzvko6xzNcNHxqcnJiWaIqF8++JOD5gsoZAEZ4GHWzG7SR7XSd6B8ADuPb9KabrlJQJQAQLHdcKUR/9i+MVe5lnut99VZ5Oy5SurB5/7OZomWj1xm2hPaYbU/Vzn1nS33WcfMaYUKHEP0RW0t/q37UmoKh7pgSm5SqN7Y6RGyb2/6oczwPDKSQEodcvBNi9b5mV5DcQz+spOVSq/aVqNatXukrWslXpvqjWOmrXfmdpPbVo/bVq9Wcr+pXpYq/UNE7WwHedK5saVf7npB36eNKMkqtAssyfMNVxLnil1BWYM8dQYX/I6xCpqja5zfHiKcubw8Rn94y1r5dSKuVr1NRk2mYVkpGpU5AJe/Y4FnQ5kLyKXSe5FxO3lVtv17bR/jnilpjx2dU+fAg30bIT96DhossZ5e/yRWGc1hyT38XtF2KPozWfvSv9egudTju1VGErMTsbWv9o9q8+AJlwSGLPUC3K7kuoXnTdfOzZjVyhBClrVBQswvBA+PktN3KwyleBVMerVZX/tSzT7yn1kijzWvrDfHHnbDyznzLQaroQUeTn4MeyUSn+3qs1l3id4mntcTzEfaHbb8Xyw/5hITyQSI6vLIlixFPkEU7y06TMvBIrh2hflES5aoOH2mcOhWXAn7LGdq8yZPT5HUXR9a+QIc7CrEz5Z/mHIJKFzbo1EkjRX/VCEHXFynwYS8aIjR8WoJrLZvRhaQiQg2Je43lAIY2xXiWoFZ7c2u2FWJevpXhNC6zduIOGYk2PuO3CBqbu2YU+oxAjwYMMeoJ+LpOW5d4cUE9hmQuDLZLBUq/pKgz2Rx9ULuBkPMujqtdS3botrzK1XqEt25wzWbw54s0FHkcUwL6CQFGprT8Cjq3XbJ22IoCgDOea/NqiW/ES/FFQG88GVyiYLVCm5SlCOpyZGb1/M2mf5ci1Rrz+p6Z2utNUdIT1jUbfpfPHue4wwWJ0tOxktwbQZ6q7tL03jy3DknqrG7LD/3ak6vFBucE44o8ELxv521fre0pDsdHOC/T3ncfdeobf9ZSpMd0T/33skUl+ugaju0Lg0M11/QO8okuEnFgEShmA9kxGFNhNPjmtVsM04yJAh9qXKWxa/fANPEwOnuzd/XfvPwmA6gvtcwzJtnNff8pn1OaYhWRUAz/YS692ZGhDjNuO/xYLvNNE3sKStEsfMfZzsbXTJuIrbYd5hYRi6GrcGuHiEdQBSE+E+TlEXyZMPI4nC5620C6QeYcLgs+1RwP+ZQiT+6HDfAwIpjutXBuis8DU1qXCJWzylRzfINhMtk7MrTuEw0OOA1lgtaWOfnRmpf5Wzbj3nkIpbT4oh4zn5JxQdAhKV9sIo+e1eYrQo+/JOA/89S52WI/7rVnvzir13SJofvdRkaQaiZJX3Lw1OZKiA0+adOMIRgv0wRZMlsrQHdfJEu/t6p/IhfLFMIcjbigzFuXPyPmFo5q9UeKu+n+KNjvOIj/X2bWSJY5ZTxPLioJ+dxL1yEHKlqadMqsWeE7iid5Yeaf2tFeLZ0vDiT+/O6aC16PQHzPWbLyRAWzCahVSVXHslJcGrcv0/vgmsIr5sWF52fpBubHwWXHsZxLcWy5uNM6QvfrD/0A54qjv4kewCX93NYaZG1+oPiwfPD9Ztjezq9NGTM2QjW8L9F+gcA/6FP6xMGbfg/04mMuJsvotg2o8guQXDRcw7dP5OuLmsMNSctYVAoTBksgf2X5wifmPQXBJVVarxwTY0mjW5+uE1+iw3LyUuphkBvOw1x24zKpPTHhzmiseA9qIdrdPuSlspXzUWH+0LjI7f895vFTOh+avDdfKGyrzRFwZuWh/wtaeNVZ1PGqg2mqhSusquXTo6ZftMTd/B6YKFwMayQtUuu4kMgZWNroXe8pkkxeLl6jVjK4rpEMP9nfq699qFwiMHf4pgTPQyMlp7CSE2gq1WswRUKVrWdC4jb3NyKiEv+gW3CRvQdT1Jj3UayyDvBn6GWsZQZsqpo9QNSa50e7KDoLnDNJWdM0IPcfmQF/Vub0ndmEA+KyqhnfO0JCasyVbCokd1fx0SSg/l3XU8jaBml3cSzF3495NsaDo7ILCJludYWV9mp6vQvpnqfivncla58MUx/Kxh6VB/rZnYYan/d1RPdRIn0Jpuh6OWL0Q5xR9dP7/uPOjmdKfMPQktb6H3OC2ctIzNpta8/l2IYCyNfbtsypCR2UVeO/U2AXsLD+9BuWSnliKIuWs+/k5pc9a0qmx5LZS3BGcGYXNU+nTjvpY5giXxG6Tf0qhCeBAvVlYS/zHOYpBWhP5im2YweOeYwmjKKqtotoMUtUD7vlbgXxZSTb15oJSAVJe+U3SoANOlllNHULw8aiCWqaQ/vrRvOh74/vmKmRmZxzAEa8vlZIT2wsYOryUfUG0pBwmNBcwmKTUzpz22NsyFWclnfHEbEihS27KsZG23lbJaj7G6RzI+5iYxqMLH6ubEwpMFHmNaH2JG8c3iAA6G6KBv58nesXKvJZQc4I3FQ2WtOD9P0qK3m1YLMdUCaszvUypQhIR9a9d2Gd5nil9QwFvWlhRJd1Di+uk4HI1dDJUIBQgo1HdC3/lp5yGuAL7RJE14ZjMNWqdSiPlH/IaLdeephJ/rTQTyPDK+xD7+wFwLXH0FdDtGKKQwvjh2sbz40E22TNplMMrtESb/jZRDhJhNNybqYY+dnk1rZuaErVYrGwsRcrzcdqib/Q8kw4KSkg1/TAZ23Vz1DiyVrnFbV+HNOL9UbPVPSAjD9CW4gvRcx5dW4vWH6s8MszfNZ5HpvsB8iyAj4ce49Gqz+h9E48s0Fjv89i0UsQgtDXJSbA3wmjKqGvAycM6gxhRoVGq+4QVnU9vFF4CxXWOYHiFyQtI9hwSNL67WSEnkdh3KGiqewIzANHV1vu/4QSjxBTK6AOWH0GWloPkUcMvN61Xkxf2Cjs8Ee0nWkW/shPqIK1t73lcn5u6lFL5WPA/QSZ4Qrnkz51oY16GQ62Dwip7pYUSUN2BKpmArLS6xheKaUxZaDzgy/hjWSy5yMmmh6E1YV3bpgRvwUNT4AZJpYA5wbozeRCHRr6NFX28saVQpvJjnIXPY+7+4Ekg82bbcJyEsb9qMrY8QYurNQvqxbqFM3YBhzVd25NXuF2ZG8BGjZ6ObEei7kHyEu06l3BiAeOXLDn5xsDP+nkzDqTPvkw3XRiYrSUJ+PFtlHS4rc7y0v74NIsMGmVwGWiITRbnqwtIdc6c9fWoCVP1tS0UC90AO8vBSBOvKmDO6LYnfCZioyqU3qYjEYkM1U8xCdGdPIefpNjFV7XG8uy5020l5EChe1Vs8M5pNYGEdoKWmHG6UEP9dFdQcDYwsEN5C4eE1jDvhw7WNaWPXMuyoMcCW86J2j0cXgTv+/fp72w+OgLlOY+2JFccbrZ23Vk58R0MUoX5izlql3OXKZiPJ582WVekOC6T8Dwq3gS0/5IejtYF9V7H29oUizO3k3KUJWorzLmvGt2XPcV++ueLFkXW6r5eYUX8FfXUpZSpx1VFUCuxZvD0Nc+usDx0vjjFLhrTE0M+L3pp5RWkis5Iq6xqVdZL0oILp9nRu+qYFgOhPXShdKDuvd+4ORAjFJ7syFsHFUutmjbONavk20cTmqEyCRbYWqF52NJaFMcny2dsJBNiNbixqYO75u4J9+4q9tkGqobWWaS60M2/F2u8bl/qqocHKn2rn260b1htwpIFaVPnhx0pL8HrlDNunRn587G08zAuQFywQtpw+w00E8rnNlAQtCdrVnXcBPm+kMRVsQO6eTRZcwbQq2TgFtjD5oqBJlHicHk6wcMr85BNrmbgZ4UpHtTP7OBfspgJBHgZFsQHtLMY7QnE32dsosIXRnrtrO5g/uBhOQxNIAxu63BZWTYqxaCCJ3fS9CjjQjdfgtF1F89gsqep9+y6ELeJAcr3rltBa/YWOKHvJh6rhd0B13rn2PveXNag9qxsspo/rvwo/Y1rMbsZfjDbsQ+wCleKrLi1fX0B5vbFie6CBgjNvC56i1ngMo2JOme59mn/aLsMgARKnjV9mBE2YLdnB9njr1OsY+KPmxC7XTfW3czOC1MgLTGF7I82GDhKINzvZrIswbwbN7WxbKwQaZ1kvnOs2szF5fwC0ym8yzH8yExHogve1cLgR5IYZZkUMWmUvwTrPTSUmI0PexxXYZimfzcQ6Md3QKllwyFmiuiwxotjdhGCBjBZUZDRV372bgMghEJMXbVFbopuH+mO/gc9YRj3F7D0DnA+2p7kiwDUVXBf2XRbncmd13GDMEV97sr8+KLwIn0+7LusyfP/xpRirigCTFuOfvnpLX36+oO3vyj91txQUMpJXy9Oyov/s4D16J78WIvbBOIJxKY3YXW7d46RMSVnqxfIxRIpphI3VRntVeSC9wJA33JgU7mPGBOIBR6kOXtg2L3WozQR15BftDq3Spjpz1wMso1m7mHuu2knxwk12mP+aoTs4t2qHaI0udsBacfupsqoky2+QDxa9fx3H8s9+2yLHP2ldmMxxi+bu+AxwGCKjxcblW0iih3aVc2I1M0chBCtG4V3SBhTbEkeXDliDTs80folUVNUcBk7pFSDKBpLX472KMOwhuNOknyvG/yiVbFb5x6RF9oFiY0Sf1PfeVnazsDnewOOLE02quUEjafQPflIyjfDx2nxnmqh0TXvD+ySESwApZ9pl/38Y73g13AW+vqJ/fkp/af7+qS3qqRQZRcPjcF2balABy1APumN6u6em+JEfw6a2ASsOwxdbTEhOlsAfvKROgl5MD7BK5TgER+ignR7xkUFv3xi9wLpEOdRobFA2YgYOcI1xxVZcfkv/YkAc10ylXe57sQFLCO0R2uqbxfyVMPX2A7fLpbof0fsxhz72/Y2L0bU0mlNuk3A6941jXSX4u+3jnwUYZoXcsN5LjnH6XN7XQSPkNwKT6Wqdd5FW/0aM9PN0j1pODflztHQzeun77e6PPU+8cCfNgs+O1hnxMzn0I3JBwhZNhxVcyiHYIaELKYCXT6NpUtxdqBA+7lPpw4cJOcSCDnmjFz/Pkh0SLrvBE6ad5sa1PaEly0iCkI3jf+b21S3YXjJTr/AvHY3Ez3MhmuUb6sB+7as1ZzKrcBwyq1u4HhVhQX84cXk7gnmL9qKIQh/BoOXMqtslvQmAMufPYQmGsKyvSJXC2z06wTowQgJlyqkBnxd3Ry19qL3leV6MqFlNkpVgRaFAPqGK/QH9Uo/iSUo6Scll69LiG5T3YLs49cazkZE1z9lX5ZKvG3otGQD2W0DVQZzP6ZS5RxV+YQS8AJjin18019ti76exn6+dm6K4DkcIKUFIU/H+ShBj8xPkAxk5wC/ZGDKClAJ/mkf9IgXLj0Pr8wAUInbBV1qdVtDjV3SWKLpauzk47AvuZ/o9c2Djea3iJistLp3++SFcziDmD21wDKPPk4lEVtzyFLBXzz6mApwBtPHscN/yfUzu+TC592CJH7YUogY30T9ez9Eo0c9mlKX9BGM8Rg3GF1d7xqJI1uV6C+D27NQw/j6cDpjmmQzoWur7plb6O96CD7OG4SnRA6CRwaVp4yeBCbME70py/h3F/5XAgl27mZU61ZZhAq756YPvFCDJMSIRmRJd2bzacWW/kgli/a8nR9PR3hFvd4n/sfqZ22DZ2n2T+6sxAHiwcUafjn833brseAFzEdPtOixUb005sBErCnb+MXxnKztNDrr2OlemWVZv+7mPQlg+O1w0aeyQAzewMPp/j+5LsfJtP5Wxl8EQ8y7hyPLycfBh1+HJliint3/6cAFRQorBntjNgqUe4oqDj+GpowG9y68aQZHEraXR6hHALW7VjuSzbTfc0GGgeylT2OCO1GfPKJsSAyD+B/wChaufoNtU0j0KbFNj5rb48hxKDpEYc0W82Qw1AYVjLQ683FRNQPhPlFr+iSM8QCaJREYo5FtdFCNS/rhngGex3LldXa8mtzT+gWP9ZPsai2pOyMafqDS6+f9IPnHICVg736b38sssXbeXyEZIbtZnMVz5oZd5buAEXN+L9jjXubAaAViJ1R9fJmskOqEPX861bWnhqfigPfWwXLeKJLbfJMQyn9wGLsg7VHL/Aw/l7NDmGsg7lquBFVYNWdfwVXe1CKdUFjmqoBWoU3QtM8ow7qGMjnFCozEJ4acmdeDE873/Oq9x2fZK/hdqF2TkPijBtpqTK/yhiC54XUq0GTHJR0Cn83yMNRMrAwA/qr5K5lBzq7IaDuvhfU4mdTo8Nj457xR08nDw+Kib/PFCpbh1gdFDIfXIifqO81Rsd+7ERPd+8ZFh7wGTs3dAayB5iSoTvQ3UFHgtgJ3esJ0dChJxo3+MYCh0KgmXowIu2FDBN5F06BoBRF48DJ49ETr5fLFLtXOkXF2ItTpZCpnWhgh7eAA/ECX/VAmrcqydhWWZmtHg2jWCfDk1V5uwdBAtH95Ml/zdb0XHp/EWPMHfKIXHkS81LZTqRuU/bEwl8ey3lgvtwGPx7KjBXAacCxUcqyPHrTMYpW/UHjNzm0E3i+KDtzmDXqCPUILO9i3dg3E3TkIcme5I4cOtOcA/pqEnODwt96MABpFGsCem9sW40Nysgy4R0lp0kMO0MGfRWEpreqMpvNCD85MgHp9nMVKeFfAyfjEZSCweWWV/jI4kmZkW4+IMkBA8nJiQPC3NhwG9r6Gk3cvoYvwgV/53OW5u0uhEcKrQnTR+eGTF+BTn7PIuAHrwNDWbfn5A0b4W0IT7Oacnc5M6VvJICoGtkB5nGlhWPbb2toCDFrorpahaWN5ZOofrnk9aqEB5m2dpEIuiEK152NB/7EcSBOg84wb6Ym5Qmubi99CDbDXXM6BaYs+PeHO0dWJ4mYAr4iZrwYsDctpdiCZi7hnhB7JVNWPHbZ0WrZOfPkB5zrvka1T8v8JFdQ3GBmfuM2du6OEWhdLf7NWZvbLsdTZAhdcuWAuZ3sCdjBeSr6Eav+dLAJRtkUL0YTRz2gWTdHUA02DX5bKEeEOhQOiYBnYtH5WNrjjye/Bv9DFA55PsifBrB6KHYNzScFoy77MYJjM/h94qi2z0S8obMfQ4RWTdAqPtmfdcEhXwcojb6JTeE46pkM3QaI+2BRHA9vCMHv417CsWdC0NA/bJD3ax0m2OvEdxdeRctZxeLffguF2lahT2M/P2Xipm/CnYcf73S42u6pdFPf7LrvDwOGun+/cjtAdLAZ0m6Ni731PFsmzUH3G5CrU8LMZHr2G2LRSdkz4MXDEimRGyZoJNP2dCooXAowEvS8TlanLrosPxqbsIHaDC/rzm5pmiuw7UY=
*/