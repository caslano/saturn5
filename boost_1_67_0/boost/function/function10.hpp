// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_FUNCTION_NUM_ARGS 10
#include <boost/function/detail/maybe_include.hpp>
#undef BOOST_FUNCTION_NUM_ARGS

/* function10.hpp
WmCBz+znxvwtUw4KwfCbQBzZa35pjtiaAGnNwwSFbFHw25NymuwcVaayD90d2wsx0SLZB9ZOGaL76DLSJlAH6fLHNBkqUw6GFm3L+6960QdsCvFwRPsjNSAqXBm01O8N+ugisQYwyH423ikkJtgEC8XnyAmHZNLknoOj//rT0FSwTodvJIBRyg1EKNIZfzjaXQqEd1o+F4w5tsE0fzc+X41D23/aY9v32vtiQpoJN8fIjoBYs4J9ceOXgu5ybK8pREQV3B2ILu6VzTzl7e7bhKy4UFcSadPRwKa3eQoTBnEhg4J6iLO84G/hCDV7Pbdo2TtZHXAQPNBrcK0411ouuD1aaJzawDgqs1FeBFxADR3tONhor1ksOZ5bbbjTTz6H8PhTBbdFTgFJagVTN4EWX7M3PVWF3ldPPJkLyemHzoCZAEVspWWpV3M8hwqB73MkeBuS1iO6hC0HBgak9sbmN8tnktsSs81+179woTjhPZHcXue5LC/dunZ07pcTIpWjlBNSU1MJyM+O9PT1zJUVqNs8qrntr5UeKNjQup5efZe5hnXvmbbE72vzRRT6KPXQOMrJSVLzZdJLmOQwU61LXop15AVSwlW9+AqvWKNp7hLqvyUTRePvRVn2gqAyBIB8tqJDDAqpjriOUyPZrnVD/n2MNuh+levtIGOCz0eKj5X+zP+7MYZcjgeEb+4dGYptblF5RB8s8ROrRDiHLdrd905Nt21f+uBR6874GPVqGneigCDcquvan5O2age3Yf1Pq7H70/6F6rMFj8VHpiJ+XFy4NeJZ1EusAACZH/30Dvaxx5Xqle3l3Onr8hN8BcztAKtxY/1AobHNpu3WXOj42TMZDQ/yVkA/n9JCVUIo6YePqdCOZQKLPgf4Gz6AgmiwV+9WFr9+5muQsya+P2iWNBDFFO2zctMJj6cKjeKIFKOpE0RWogZNvaCzCUF5XLeBgykKvFi/XGFw6Gf4/Oq/GBnD2l3fNkWJ3ImmBjIHh8tjesORqn93N/Vp31NOkgKPEmSq7mRqCrEy8vcLVBSTYdLrJsxfNnDxvSQ0iVSNGY9TFdHMMRWCol+qD+qt3WtnDJCt6pW81NslWl0Ko8I2/7Zfk2Y7P+j+PfTY9l7fqYKH/ld7Q30cRhPOb/3mKhlilGG8SIUUUhSw0XByjoYI3h3+vfeZkLuBBG5tXVCO1TBT45GkrQk4fgjHnNT4Yl+dU8vRte1sjglnykvE6uXmsimM3nml6I3j8BLISvXDYR3HbAWaJ8215GbdNOlnC7GgZk0nvyGZ/KKjVMF6UrzWJHvFglmk3bI5A+9e9l7FOUZ3bqxYNZtKonV0ymJjTNU02GHFS85Y03hDpkts3ZIxmcI4xrxJgs2kLfS7NYZXurnWru4b9/u4E7zPlHjjMK6U8mWh2Typpr1dOFE/bre7Uti391QWUNdcyFJ/3ptkh6GHdBO5ybKrWumpZ/bW47tOd1NckzUiq9ktk1SiQ24c415OSLAPqnw+pqtdLdjUJBZn53GR6WeKRFW8x6OeMOOZX2AKUEFF8HBtPfaqvTS3x1u5MN27ip/ln59tTRHQW0+JcjxaW5+R30DRpHS4ZjM+scMp74IyVp6fi8hT50IVoAsvTY0wp2MRVbXkLbeCTvIvtE1vzuxKsrFeaJ6wC1/J9oaSvbnrH4oVdjWMj16T+FWle/o2qqBFYc3Xa5yt4kbqXUN7tXJLTsPbYCvGrI74sNl388VH/jjpEC/rZlJbvpchn7Npd8Ff/l+TbpV/em63Uw1D6N8DbtKip+j8rPTCYJTWc3lwC3dqvsK0QQPvNFvjMwFfrlojQrr0vmmzAbq4woPWQcgcPgrfgA0dbZ6O8VeR1K2v4JcxOEVVx4oi6RvTrljHbMY+eyYq78TwM1bfPpdCE5qVf6TC8dTReheT6wi6Ts7Ap+bSjEpPb6XEoXV9Db++UdvRW/En0nxD4m7X5U/1rX+B7PaQdto25ld/7sBr2pZ2eR0auAff9cCwuTW7PmP0E0EGjL5mhGU4zIbmRSsA6Zj+sx4I+nFUGyaBigDzJvL7hakAorCfTedSC3jF5UWbAglJPALbGTYKHAnWEQE0QhX4KOTW2D0orC89N7j10nIUFcMm2rWQs/WEPyURo34jFSJ7xZzwjEJcDIaQOuSmgOkPEgqDIPwazJCi2vnkr/vM7yXL5nVAiRS7JuPdCqyJ6cmtitqy7luX7WlCL8wxsTKK2dGNnzl8Sw0YDQFlLdikhp1HsoWdN6Tsp5lqv8cMq6FK2qqXQTnV1XwSu5IBHbrurFS0edSVP/5PMJMZEYkR6feZKAG+YXmHP5M9kv3fPdT9z9rDtA/g4bQyVc7b65HrWwE46mKLay+TfY78b7pPsd36di5/8nUpRSu4r9lQg6Je8s+GvO9LoJTJLq2f3undWxXidp3DPunpVfoZ1+upuW5DV6+yg7Jwo96bt5t1YDnvgHpRy1wS/I564IvU1kR2F4u/HrnJw9JzKyLIrhzEaGriXqyUODgIDM5Q8sNU4Iv7GGcUj3CL4eaVfwDpCwfGl/rS892X4ahbo7Y+Y/7UnfwBr63sAHUmIqHR99yqT533j4A20QdnnS3Eem2B3ldWQbHRs2arK93PAyROVceRPVeylrvX4VeqVXedh70tfYw0uQyCbdozisZKFswV9AYobrHBqA3tGdAD7ONSZADSqMLRiv+2vpAxY7KqC0k+fPARmc92/GawZXVjDtFlNQyUsCAZpQ2T5oNEY89FKBtEhcBleELj1iXo/XHraAKPfIgxR2RrjwlVh/11sOboQNd7lLDHqB2P+7I2UazK2aX4WLGI4xDZGI/7NqNVRjHaKHFX/vNwDxnUes+39O6hRLip+RZIaxGm0ibAqAH7I7yNnnsBBnS+awBMdONGPO5xPlmOTZ13grdaGxL0wiVFxDES2RjtkvngF+BVuRL0P93bfwzT46bgIqz3G5JdM8KdkBBiuhSsSdFMrQK65OhcPYo61yeh2DqhHrbqovlMCh+RvywsusPaMWsM/LrTbqTpPzDQCOVv10PZd1KbOD4Y/BBOL+E7NBnlXsH00HPfPwjxKc0KUUPJ7z+UMAtpPy/wC/vOQ1yJMxKDGLb9R5FerichiE3IfPkvFpNsPkvvcpWMtviLCs6CC8p4OznehIbbF8hdyggUhMNqsaz0PVNmNZeVdcG6Knqa+u+RbRuNPeTw5GowSpx1pFdqxXdsYVIvU2CtqDnc9Ghj5uyP1kb/pdpnv/UGXSWkdvJcNt6qldGPf2hu1h6C9MF9S+q9mO9TnHGymBxNqFDtqpt1ftY3OByf4SK4/mYwHn+/3vHfDfl0DPOSTpJDVRJWcz/2hazXO6fluHWhfYdtxBifQD3EfaUFtHa9BZUXW2INXwNNJpdlO4vu/yzv5AKs5xxP4U+t+D4sy+0lnkWVP0qr9JruHcHsMxgc7qJAROGZgNXNdT9i7QezOoGK3QTXfjad80ehVC2O3YRyEXCZiSO6wegwFvFC+3AGVcCSsP+F40FMDQI8GC6wmq/io3UvjZpFExCKR68OMXWPcv+rj78E98ipgCOUA9PJLoAzFBom3p6QGOAQUwLAgWf/QpeIiRhdmuMxqlv/XdallyVqancaXdrd9fcY/lqj1d592QoyrZKyNymg6T+9oRutDkkEjDEPzbX0Jwp2fd2Wrya39Lt78S7RNsu1eLw7TF8fm9HstMb1tC1DWob1tCf+ep89K8iyXnK8MTVn/A3Iq3EGqG7aXJjrsXYEU6KaGTX2B9MOi3vltf/WzQgzzkhUyC3ZT57Ht2l0DHMRmRLnow+bN9C6ng8Nlf/9x1nvsU8HgF1F5xuimxKNe/mWhuZm6+mCYZDNfItN+aaJVWXKixyisXjifLvG7rAj0SaPOQaa0p+j9jkEgcqiJi0Yk9ayQIjC2RmP8E+JKqiTHyqMs2LnUTu4RWAtMlFTPjcHql+6h4Z4216HgWCKBL8RJuy/2e7+EX5cy8cTuhRvMW1oAVsl8bBhU9fcd0nbijTI7j2TIzbqne4DCenuTv/as3B3mrpzxmF3w/acfSaYtHdICC6urHU9XMJD8fJhU238B3Wuq3GcimwEp18H8gfpsY87KHceukZ0vUumNTuWzJ3Gs1x7m3tWDR5LYszHfl4j/d+zp50BxFTCIw+rvfnfuIkQLy06S64QyXHyhbqX0cdPa1X/ojuOpvJhjfTJHLsTHln85ocNagkcVRPq/rLkAQqz7qw7R85JrIOXU4L3cDRb3MMa6J/wfYeBLsvq+LhnYN0o1lN5I9zLS4WVc5SN70y9YdVxgOIHtr6ZL4/ITceO8u/LNjsjdmfvae4P/bvVG/LZ5YHPxeWCSCNuJ6DzPeqOlnyElE+knxvRL883F6K+TavzFjSS1MsVqU9GK4/Xaj3S08LrglXO1T2zC35zlwKX0QX9vrQd77qVM24j6j2c/gLwaO4flmCyu02Mj/qfpvixCaB9HKXcVfzf0M484BTP2GX9WZZn/lblD6G9rSPDdYXUH8+p/F8smee+swVvppelxsuViGDAz4kIc+/R2vPAVcTAcTDglWjA1V4Q4CWMRE/R78TYPQzObv/G1qMo9teSFVAk1NnfJ5ye3HoMTyRkmFM4oV0ob6oLRnPnkxu9jPB3YmdosBQMt1fkrJvkHg48gxYEl6UnFnR7K7p3GuoD1uNOa+5vR1MkCU+TW5mq2j3O/Pvx/6huHMa8Su0hvb1nzjNwTW3iWrIHDzK2Eo3skxQ+PQTuPmH3QRf51Cz99+FE+W4sCAzp9fpjLiXyd8303gwyn3m2YB0l2wz7dX8PY/T1+/RDnU/ijc1Fb5xuH1eH4pmwUpg2P5XxODMRxpO0Qd8wBFNM6bUoF6Huj7yFIvU+vh1DBXwdvIdDCi31VPyF+VTcJb+9sl4HHh0zXJM1f5kkA4fWtwg4v1H5jb7H81X5egS9ySVv+mzmx2cw7qX9jqQk+1LRtmQZc7lnA6sX4aUL0qwT4RC1tA807uaPoL4/NuaiSORD5vcAS0nOUnT7r7KNjQ9cpDgN1k9PGSJeZ5025fHeXreLarKDulm3NkIUemrgMXKrarsixszY+2OYZ3x4edsZG32L3NaSKJPeo9ayffE43Jlz/46JMe76WnlxHnua45QeVD+3z0RWq4IpwsuUWGMB36XmxlkuV3xa39XCnXftnzqCy7FdGw6HEanqfR7GfUZH0hHNMNajH4+FhOGz2c35smC5ToDTeWaD3bNI7MJ5H6dFjo/rRSUfkz6VIW+y5tzeXnPeVSt+8c0Q5tt0lZPTBbdj5VEPoxo52waJvEGGWpTe373+7fhy7nsHXR6dXchhhtWB6oVTCWAjvUXRsX3PGRQBFCQF/SyUmG61WaqnqaPml88jHxmflXWMcerNqSLH2KmESox4mwqTe4X+6896S19/859b1ifBJ0PkkrVGQ2E8OTZZQT3aR04zjHwSgBOrEYijTT1TF+tVgzH/VJbntLnLNRvSvjb+OkWWdgOfy39bfx1xLjF2OmzOW4Yqupy9NewmHDUUpGhgtYAyIkBlWTN/g+JrG/6Eh86H4SmmXE4WdToAnFlNTPVq+GQxDeCKL2wPDJkdxal2zNuN6HRca0wjcAmUj4kNjDj4Vg6AKE7kBV/1M3YFqN8eONH8BcxBRJi1b8mvLC8fLd4Ie3ucldQuQLx+3j9U966ZR9SvNfrIJbL5sj7g//168DPr35tl9dfBWZgOHtmCAk4vNxpFvJrxA1l1FayeDtcofFrE4cnfZZUU989gBcbThH71UsbrVv8oVdzqX3Bbd+Dyj7VH7MoJiodLrGs0u/AXmnkG3otFcJGKqxVAB0RCewqlYVaPWTyBz9ECuQeP8CYp5uCqESJAUl9tuzR3jQo1VX3N9c+NKqUFg3+DS7H7mb91BLYIhXF5SmB2RL1qxxWetyFuhofkdFxToyo0cbqliPLX8B3UwtZV4IFZSses4RgYfb2Z1EgkgS/BjQTDshUV7VqBJuRaj58GTTyUXIsh6BDEjvCM6fd2eJT0ghS5IyPjUKtEEX2zoD5lRNVmzJS7lWSrWr9D9jyh1zGDKKY6DYu17hgUoZ63fVwrx8Nyw8PjTjU9IVwGVf8Y/jFEKS+lFHj5gYPFNp25Ugd8UIAW2oK8BE+khHZ3LfMeiIFGiYRXdmRXOzZXCbokSHiEu9oHfLAgQ9+WfzbmHiWlXXL3jQEq7HYvlTD9R7s2BeMsqGdSv5bILbET23tPKo0mnWXmgoaO6qLWT8Wto4RzdVa7lNtNIBvroIzpPnsmakJNY/YdrNnlPcNzWWZ9ZsDRjmn1OTFrKMEFawE05hIMrA1Kvs9+2OdXKAvdu075KP4ry7r1eSzTlfwJf7sPR3Tl4JCkESdss7Le3d4pFE7Nv6DOhzfQzeC9Vwt7Wi0rWnoaJRIieJWxkPspYPNS+Nr1e9c0Efxv5i0zoxMKCLGed/oDCBxkkFm5pNabJxzKBli38/XO5IZX96Z8Hy9XgI43lsZVDFIEXhU8oa8dOksq0AmIGBDrlihD0rXwYwJSAotDN7t6+PNnO5u7yjP2czUsuqUcXPCYUmf9SptFX7t7Zx6i5J8sD2OKYnuG+o4KalECNGUSGpNA/Px7rw3d7TvegMYjqDKeewT3/OwYrReQQUyjDa38d3EImv0cWU/1na5oYPuTygP08Kr7Aqfqzh5Ae1R7C2f1TcCXQbXhQGqdxRHit8rJJ4MUpeu2QQ5GkqaET+gnVc1/CyqAwQNzSJQ7Teamn0EfCbSa70ZYqB45c8aqSVPCFimj6o6blOnqnA+khKp5uWOupRzIL9icuQckds1LnVa6oCDL8zfctA5V2FKueC6P51VnSKucqiucqtw5JrVsq0dkeLGad1hVUZw6Iiu9KVnvWmbTa9Ed8DBTE48QoBeamlo1arugde09iuKAmfh8XE8oHIzYQpfYcJc3uU2TmacoLSDWQrnTV35rfeyxD9SWRDtlAPP+AAAs/9MCzUg/v2uis+O/g6PhPJGlSUcno5r1V8Xj1ecoEsMyDEtIQKfI1CCK6JOWMeUdjGH/mmKi1xRlatNXhDXp46Buq9Ovj/VOM2/O3BjRJcFMdm/xSyLSfzLPe8jzkld0uJagMlkRJ6Pj3uaeg1o4Y85+E65rX0t3I3OqlWSOrdBE1hxJ0GC20yBRytBqZJy8ewyEbgMO7+YzHM1ny5ZPqU9aXG1anz2zIX6yHjyYlqkmUmtFf8n6N4z08q9TR0+1bsAQMsGIs3kuqj5lMCmgteCq6XEivey7HXKnx1xeXpOuFbSeg1TJCK22l1LZ6bZB0Jdde8bAmXeshhNSEmkXLNTQ2VTvg9OkadUbBEYTiXNaK3GfWxMU4ZZgj6mwjGZFXEzR1eZj9psPBhM9sxVPo8tpMbj1x1TaboXqf/GYi9viVDhVTqbh5PpyjtsGfxaUwo8hS2RDgiP6itfWf1MTJjRovn7fzEjmDREDjaa5IHOQr758wW3Ma9TrOSuKufu3UPI59L/abS/JYnFqJRBa8WyQgQ5gGxVy47eF6oaDBgofLW2YJD0H2m/HEScoTWdAWgFdrbr6/777Ubdt9nfhlSv60hniRVNx2uzPn++7mjp7EiYbttvxCOOa0d/s4Ymy2OlG4Zt2eWpwKFA0xpTIAM34g4iabTlIkhiT8Mownkj0IYsT3TXGTfca1ycYpLps0PQKUcOqj3+zX8ni8L1txTZQpu4KlJkC+7qsUALFEbXV8bbj3vETnDvlB8zPvzp6Wv8grB5nYZJ6XgU64+7HEavuzqM7jqu/ztHWSYKUqO6Km4s+BNYMp6zCaYfiXeMhPIX8yo61+iFNXaV89EfCf30pJ6azW6BGUHyMpY8KaH3WcB6G23pm+sRDUDh0K6ecbS2vM0/QuqZ88yGGfzJH178aMt02mngbe9ae2fuwN5X75LZYFerOLO1n8m6sZe1Pghh+Dcl2zs4H0pAqLvzFWr1GB9Fk5T9/EXtDFn7DdF27MJfXfRdcUtM0E33D+78n8uVa7Kg2sn3VNeytfv5z9pBukWlxo1WLdvu8pLQSkqh6axAmMk2Pad7qg0XmMJm+OftMilLqXZkZfxuQ0Z367YW5jemW9Ve77q79AHyUbOLd8X6MVdF7GfB4jLjqhzfOJ5PpOv+VzjkhrSt+Y2u1G6244+12n/YZ1s4uu86SpYRXCO8fj8c6WMgRuqkEmbi6xllRev8toga3HRb+R9D0MIWanLFoT8SAsK+xZhiL9HVrPtnXReOp5gk5jQNk++VEsB1eINug/w7peeZ7cE0xTs2l8Rv2qfEbmYWY7KGCSI/COLZKPjiS3PhV+vGPtYGrPqo9kjOKR7wFafOX6tB22K9Uz+RbuP+AUiNmXGethdjUxPuWvHfIQrvBQDMWPb3wM5eIzljXZPbs17RqEg45h8+msPD3yknbxRs8e/8DsQ3U521MQ3SoyfPn7OWb6nTI8/0xGy3I+yVZOs3l/RONUc+EZN1wMxKm5yYSFrntROAW4dPoJ/NAh8lEpyUZrZxpFvOHW6r+zjIVN0iTgfxRYBRmnRDUQndjdXKZSl7dCa0B7zjWlIqzcSDz308uC1rTzyPu9ALbpe2Lg+eoXiltAAuvTW+bkqtuf2OrrMhry/x9qk6MydtiTru7YKkkqQzQLajIoSp2dF0xDHgLZtSaSs8SrwfWmxPJviC+/tbL+0v73OM9vVMAyaXhR33Qs0gSY97yN72dOHaGBO9DCJfb2RVwsqNyXsp64m+YtIavEe7e+cON3VdC6VeY732Mx6T2L08n0qMZ2kN9eldpcaazbZ1h5EMj78N/4pcnn0FLP3i7NQ4MNUON/v/tTYrm2qdNiuq47Z1yHnC6CrLcoO7Ts+wXzVbXP/ZQ656cjYxYmWa9enZZNasDhHcLFPWa+wz+9e6eV5yav5EXCxj41su/54c7cc2h+6S/Fba20jeu4xfF6UhCw6hMePzhl8Dp1atTGk1Cg5OPqmTKt0LsiQaOT4c3b7YEG1NkbBa/jOk/m2+Mll+ydOzqW3z331cTKaWO3eN3KeWllsghaX2AGy0GJNBFc0iLXUCdFn7udJrKm+nxsgnHBFYKahrmJgb7KOURTeZxCiaLDK8CM+OAJe2OY4r9I86eCV2ojDU0e3tRTEapeGrk5F4=
*/