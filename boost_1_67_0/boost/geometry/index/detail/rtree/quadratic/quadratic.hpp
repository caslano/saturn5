// Boost.Geometry Index
//
// R-tree quadratic algorithm implementation
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUADRATIC_QUADRATIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUADRATIC_QUADRATIC_HPP

#include <boost/geometry/index/detail/rtree/quadratic/redistribute_elements.hpp>

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUADRATIC_QUADRATIC_HPP

/* quadratic.hpp
snRAK+QUPYpTso/vOUWT4ON/fDROlizdC9k85jnCEhjIrLkKmVH5XGRGSKCidSb+3DXoP+AecoEoZg66rIZ4rSOvwVr9FM4LTQSr4DAX83Xq2qWv6YABMvLUR2ksL8OFvRsmeksvsI2bzCGPlvf9I8Pyehf9K6+nop3dZGKmGnRZb8G56V10BOfnIM1PTR7M+kvIrkqBp60WJm2YhMIJNAnVS8n8jNR6B9JCE5LPG1chHQNTyeuFOq1Y5z5e10NjQbaeifzBeTr3MVNLzXzOAvI+AKjYTaDCWvUjpG8DDgCxIk6saAWW4jrOymwwkjjd+mCqZTbWyOvKBYNydwC23h0TCyUl/BOvRdpDllw2PdMHsmyxRV1sUxeb1cUmfnwJLJrFmeVlDbQankXtp9hUfVDuYile9pBZvcmEACM4FyS4KfgTszSD23FCd5Y1wGAyj8nL5pnVYjO8kRq8iPKYQFBHFog8NUt+OcImhC55XMi1cjVW4jGpQ4J15hiXYvWOXWqRRS2yqUVmtcikFqEK2SjdCUJRLcrGfI0GvGm/OmaFYyeCi22SkhuwaPOzQ4WZHv7pY0hs2ey9nx+03Bq6xdazYDDz2lQbDFeQW2599BsG42ZWp9ugbKgE1g/SpSU41yzFLW5QrjbfBIvjWY3gGjSITUcUkQqjgSvNrBaa4qZsyI4eFzO/PyG7Ob4uTfBCPDd6kRAt4UCMOwUDMc8UHsp2VnfLndo8M7sW6OuPUE51t/JleWIdOsaCBaJY+EzIEbZ7oZX8G5J7llgbRaXToFJTeWKXkt6/Bd+/QLvWyzfGXx8c7+E0s5qW+LYPWASbBgwEaGj/KwZ5tDbfwseiDJlvCsPg46r4DXIS9K11hi8s4U58iKbgTODT+/lQYArIHECOa7crHdH1n8ObuwEBoAQiFPUNLPMGR10MpTWm4YyT+I5itU/wBR2rRf2aKN4cLeiUNV1TF57qCy02+bSsjveH2na6NIPzAmUsCi7kJd5G13EDqeKAODrU0k7+wKZBFCCyvFSDdzi887hL090xKOTjZZE3Mc3DC+CN4CWSnhtWTv+MWmHODzycnqOg8XctTEFyLoeGhOTVsnLeRyuXYpsW3GkKaqZFX3pEDBPlo+nArMCLYnnlYZhXdZkx++foIT6A2ckYXofLZLpdC04fo721fES2rTHtEK4poku10AJLQy3MVAuz71MLc9TCcWrheLVwAr8UiZlWuSl4K7x96xjNcVAtNsFaV4starFNLc5WizPvU4tzhJtIKxwfXDxOUka+9RpUwlE8An1CgR4R/QSFssJxZXrm6eOVUdr8Cdr8cXps1Pxx4r2RqG7dN04qi0Z0zEr0o4dcr3hglO6EkkUYULDnTsXPXDs0pWlnYY4B+sO9z4A06WGFltnWze591r/VB+tGPx/8dLRxe31PqgrMwb0VdAfozGLq+HSzc6ZZGVwCBDSzyfpiw1RgyXNA5qYoV/7I+rce46mTzcgrCzMBcbtegwqYawOMGUCftx0Hl3thyLJVb6bqNTN3BMe5fLl3FFq4bFeihYv8sqBuFI6H4bSxJu0ptATCjGUEF48XBrkyoHi9t8AcHAfztst21eZ8cut4NCU2kmsqPNj5ZNEVGBfViJ4aSTxVLCJVGMugKJzwmiUwuw3tdX19cV8Ff/12dBeypZNNVPkgEC7LC+Caf73IhG640IoCNDS8fRXdCVtQNsZfNUbZABUT6F+MpBfzChSDeRNYqDe04hYogUvtBpKb+3jzQJMUX7cBiRyAlfWYC2V8BzdIMZYjkkvbn4S3kxL2RhOQpbE0YGrY1iYxqLZg/gIMUVDSg3/EQJbToid76KkyUtyJvIolYAD5yecRK2VpfqkTMY62ClohWhZaiTV6+V96DBKOgiWx3dnRdmcyAwZ1kSdT89hKt2dGHZyZ0Sz6U76qAztoS+wPM5Rqc6eIBIB5J6A+dkLJYitohHeBcinxT/vIyzUIJ2YflnPVZ+TORdtaQPLfbZQkURifOyQF1jvFH+gzlBmsQQKRlIzKeprhiokmPUtUEX4PFCWPf8nLwGfZpacx0itl9mx5oBirTCg23nXM/vt49rsge2WFDV2Is2crCW8gUeNLNWuQFMUCMOb1wbqWpca0VlRzd0bX96My2uxvlXEk1iFtx2rDR0oaerUgQc9gggz0SgalaOsi0ClRUjFOmSsCA+Tht70GLHqHpbruUeDXvz/ai7B8V0OCcG9M24qC5e6/DpJIsKR5efHnES1RrohwDwLUBSZSSZVsmFQxnR7tWn7LX0lypAInpTCC2NQ/7hoPby5ZPEpa7rrycdeE5a7xgOt8O11XQMJVfN/3qBWP15RxmjJGU+wYBAhsMKF0JKWseYfQScx6+G7IL9bheN1FjnYPl62E/RjRl4kiNydjHK87wgaqbhsrsgA2zm3M3VcMPMnDbrZ4fbkN8Nec67J5SqgOMy+GVpCOAK2uRIcEkQs6iQc7djmXo3fd+kw9q0d5HDDV/BKBevBOBOqq0sn3pwEdtTSm3fLcMFuodhzGOAgeAiBYHa2Wm9Rys1pu4doUkyQYAVlWHxidAreQJpEl9RMgbZ+6FolVXYvuGHWtnX7HoL+YPHPwlFKm0G82/U6k/Jvgt3FpjUk479lO/g60roH/KbtPq+c5wTZDrNl7SvRm6+2lBjS60EcDoBLpkW/4cZ+W0M51dmwn9gduJX5Nvkkiy84+7u/p03jJnRad6tAWgDzodlMNNiOv6aELKk8NgKtHhge3Yb8keZDuJpeRS9/szWtSJgYXms9Xrgxuw+5I8lgt687DGF7weiGw182YmLdTseLqDowmp/AOtCeibdcCHDQpymxyXDrqhrijqtLEH4Hp0Vfpmxef1marQWzLbDbd7qirbx9RcHGTyu5B98BuNYgjyx8cQd5Cs2StvijqqxcxDznQKGpKRiwqgBXmgCoBwJrNz1aVNuM3qqtVVbixXgX1hGoKbUGSCCmt6P5xaBgS9GcUW8SNrNUv4IRNopg3d0dxUiTchrkYf3A45NrjgUaoFXvUigNqxSG1olkkst188iBUDlvF89aYe0bL8pNvpjXXtYe5jxtcsITbcl0Hct2HDK5OjPudyXNnNhvrmbvH+G4AlktPrrtTdXXlujrQN9jJdmtKh4//CAgosf8u9BcZEruvNMGCJxvM9lQTuiCV8zLqYKmpW3AsRZDbkEt08c9oPNQpwKb5reebcJkNE4Pk8wVssUJLeCakMaMPPZ57RKzIpKpPR9ioKUgAQD2/C1VOEYzdyArsjl2ghdISFSw2/ccx1lx/IcYjQb5b+PzBaJpGLW6yACCSkJWXC37NxV1OMN9/CIkUA7PuydKJoT8+CXaMSaQ3IDZeqQlD/RJy0fM5dCsrGE3UijZSjArgziAuU3kEM+J8Yw/NFNwdqiACYcZgh41FBLmw3eu1VTZ47F/0/DCblpV5iBDuBf65cAtYMlvcD65swKGAgZhjL9EOxFykeozhU2Ng+EWjY2OWQ9xtODA/EJvYXu31u5DYaPwT1Tn+2mnqRREGaYjL/MqdVN2k4GIo46q3Og+OsPEHF5LiDnJ6UGU9PU5lt9qhHbsQ4LH5dmYr9nq0GRN1qYJFF+tF+0QRVy4Udi/5WqircFZsAiW7mECAdrvCRlZkDy1NmHk2IiAVe3zajMnlsZmx0fpnR30hJpCFV/PMAm1/I/JPZ/4iDHauDutedsXiRUy2uzEV0yn46TeDTRLaSy8UxJnXKI8gN2w3VD/f7tWBXup0E04zI0wiz4LLn4lLNx9kIUKDF28ShBYRQVkZdDdjAnRmHOTfSEZhmx9hKj9vNMXNNcrpoP09j1ba3fwQjJBK7cXm3BFrzjWhDXcYKPYpA8aq6BShIqvoLXfSrTwYVqr3LWkRjOy7IdGfDCiyNUJP8fJtulQuYsYYz1ErIjr9dSbSX6IBjYLSTmmP2GlDiWAMxpswepN1Okd1/c8Im3Jj3rdyHiu05zXIE0WMYklJIMOjHcGBdkf4xAwThsYDH8GYI391cgxreDKw944h0XWX3ugyo9eQLaPON8hW52rC//jAELNEtQGipmYSdSGXBuXosVg0GKJcmLvAR6AorgLeWNawRyeWCWcGJ6P4tVb/DJvFrRE0tznqpqLl6+k6dSnKY/7r0f10mAVCE4C5mSk4u+I+a3Cz4MsdbGYXc3fmHlBdzczVk4vSIuQ6oLpbPULUNrq4HXXzmW18VpZJCp/nrJ2Le0GGUBy7Sjda1twPhtqctdgg5ToEq/LVzloEDcpltP8A4JO61qOrFM+lw8CAjgB8rg6RQy0+CC+KZsQsMmShYgYBsSgzRFnybSytBN9Cj60eiHgdPr8GKO8nd8ZW6Y9zdPK1+IB+nd8QaQ32+SVpv4Tm1B/ZgETqsHgaRSxa17QMY03SnGgwxD9HJ8Rpi9DgX2yLRCv57nydl1uB15w8ev6ui/epy4tQeFdYMGZd17PeNqZIrNzsE7rWgLY+DSAYSwtI0d7DtSHaJ/IPmGMxHMTKgQi2ILICVsTwL8DrVfPERI9hwYnRsEBB/Gk39Gl5DUoG20hgTImEh/ildhIBCggcDDHvzDtprcJgQb/59DCMdxx8PtpNlWx/ax/dnx5J92YcLyktnEZ/TThuI6wYgYbCVPE488eEYXkVhTaiCI3Gqyudxo2o4YEsz2UYoslmdhh/s4q8xV25QTTWBmwCAOdu93hn+NftBp4g2/q0hFDbjuwk9HTU0dmkyhoHgACAQ0sBAID/f+3cyFFbmtEY5HpQqHMjkdr1Pp73LvaLOzeiP1+5UWc8dV006RNw2IOYItI1z0QYijXAyspVKhMaQoLp1CgdF7h53j7Z7V8lZdp413lkq74RZ1Pn3lBAYo8h+3pcNK7OQKaHEWZByAKABTTEF6wYpRx+Bmp8dhdq6Hmn5Uq42Vzcpy9YDCNA07kfeK+TJIK16i600Dwi+7s0ILJV5+kBzBczmw/fQKHgVMzyMEizOufNBY2wYK7g5OiTVDoATqtKl6r0cA9Uk7fTWjUUykP5TmQi4mSSGsz2e7xeL/8a6KP989O6EbcfpMA9CewUN4C2CKzE0eJBnkuWOrW0Sy3VmYmX4F9WEdVxnLmh9FZEd+4OpvTkzmzLVToBZpvyvgGWn16CcRS0AKLgQMlJ3IDAjnphpFG4dssPknj/uW8bCmdgsCsfpokZCMAZZDmI8gmUIZ2wk2cuuWamwEg/4YnxhMLsWLT7RUDKm64ma8MIKOxmUZiFCkMBDkOZ6KhDC31U8b88+JaFtIcLYX7b/kU0Nlw8BSKprO9COJkL7J82fRx06gHe+pAW9Edpr2O0NojW71DC0qYWo6PbK4BmeEDAwE/AfDi6UbEcyH4FugwIIdVdd3EPKAoVO/L2W6takCqFKAaCaHQ10eLYQFzfCCpH3j5r1TpIO+nCWN4LFRdJAkDoCZQiJk9/EOUkW7FpTfwiA4B6XWsQS7xiBzQoWuNlOv74bGCf9haaCarr5ayA3Vss8HVlPT3NyAC+oTRZq69I0XWYeyhiUJkDK8LH67P7CbBr+F8xiU2E21w2HmlkywS8pobAjPtKMDeG7alBFD/hoYAvsFcb48KI5YvNO60e0VpVacVwAeU4qES6OnMkqs4oe1TlgKocUpVmkYgAShJ7Zc46WBjaCupMBagzrczVCepMyN1Kga9A84eMPbTEmlV8zvnJxj5yTF2FjXfxXFB/Klph+fkovq+13UprGoZnsCFpUFcMiA2qAoOqj6lXH9Q3B+j60D169OWTiOtOW6tUhI2/GJE8ptaq7ejU3UgzSawLWMJ6fhc1Tb40NvlnoYS/X0eUkK2JbY6X0SvKGD4Qq1B6AD7Aus6d2cEme2fgvDwXnxdHd4hhjbxrJ700AQQWzmMQ5xQZUJCmNYh5PNpGTNWoiajElQ1M2A83O1vwhjPnObwGJaJfUE4qKxiDCkfMWjTT3H1zth2WMPADQkWOXXn18nDnclohg2focv8xWNXhkc4VBGyAmCggfUUCMe3jqdfGFrOI4Be4f0DUlHcV4TudsC/iHVn9iNqqV1WbhcomooGy9tcnQZkNMSiLwuqEns04EmoivOpowR0gDfIABK6EUgWW4P9AwWd2lkbkkYkINjUJwfJBksD/DbI9Af83JOJ/5FUbT6Ab0xyDrbGNpjEzNMKyL640oX//1EQaC0ssn4UcH3rTfzeKeoilHpio20RjnPSMcbshcdyu5psy+43bBVBMII0Q+BJJASlYYQmYtKwHgFAN00y4j+bnyZUkt5qXiiYX9m9yUiYuMl34g5lWjaNMEUdSJuiTGzRXdYUAZ17dQq/fBiQN7cv6vZffvhnEEF0HUvmX0C22FG8al1TpwEYXJm9OJPaJmhVfNxDjf/nnICUSXI+0H2wiCaPLyC9yMe0u0gdyOLZ9JaFDmBxYIMcRYqeDuMt3iB0/Ym+pD4DoKYKI8DZffr2+U2Qym2qHsb/aE2UC/wtvIXSUrwYBegVJ20ujAHKvjQToCPZReFgglVqxil5agC81l5exhjm6LaS3KCaQ37Dp+DkfmEt6GvGha4TxQ1/MWYJC55Kkj1mxyehli9nfos43ULIddV41LeZA0x7U2VmSV1KYU9Caj5volmG8Nb8v3ii7DfV+aJYm/5w8pCNPGNHqV4aRi1dtJyaWgSEC8Cj9e2DPZC2Qfo7YAgbmOsxmFtmGUciSHhuvpMIdWUIes7PBHp9XK/aQnej5elaP6eUADizx0/qebJxW/sG0WINWWmOw5SqWHtAQNC0w6FuLlkR3p8yljYMwTqbAgHAKUNYqE05yQ3Rj2U9vsEiBBTzlaOSMXWXffaFpfOSNUcMpeXfJ9DrJ1Rfz7hqPJnp3KWQB5PaV8WbywTiZrIcmf67YB4t21SE0iB98bZRyC2WKXI15S6kQgFQeH/9nYaygFwej88I8txOdF6xHvhxu7HAD7Go6ehaIBISO6B9qSNw7jOzmJxMEbUdZQcBMLJU/BJ308IahFuF+kAewwapZTQvWJUQAFGPIECDYCDvhQQ9+yrPCAw3UFLDxA3sjFAjM5qPVoFHaSvEPJnUezWrZrobgoxgJgS5c2cLLPsV993RmBPl220Of6Lha1AKT7B+H9kd3hPbtI/Eo5zFQ1wZ42bX8/AEWCWZc+RZIFON8SwLj5pQEgHvsGybC8d2ZQOaOuoL7yO9pUy9gpRbomVpmhpTB6nRbsMf8WJaIhC8chyGaTw+jvocvCJ4yKucFYPyy8YnFw79Ls8Dzqm29WnBHpqPO4wn9yFzswXDZDQcEK4m1K2iOtSt8jToNWlDdYn2+ju0v8PB/foLBADkG2bRz2ihD7BVP/JWCOfqRCjpR7s2zSP6tCGUCh8+kSzvS5a+nJNAl3/FFPN7gwcP94g1ol/xqNM4oWTHtG/W1yUAXr3bqrDNgr3FcBnUX56HrAQD2qm9h9AUwwNj3i0LLySJ8XapuEaZHIHjjFmHBsCHvAkji9VcS43pApCZo4ouuRO1Lceu2mAZ5qnM1ShElT7D/Et6BgrmWxARGaa3Cs1uQr4x7HUXEGVJgnilF97F4+bYLode1Nmhp+CLWmNcr345BKjf6sx8GbnRXBumMDaAOCf6Z16t82Og69MBlQLKlbWrpcbW0VS1tVkt5o6tjIEVLgTIX0bJkXEc5fByMLayrkPsQv+pmqOgxeyDFF+XpL1/RJzbHHmMVzeHLMRjwRo/q6gSJTKYteQTqvzQIeYV2ZQDdFeFdr3KQ7RO+Iu4/aZTExoRDest4+jUmiT95PUx4QK55Cf1DrzlxnwBTAAHlfWutQqhIIV90AI17Ca/5SNNK4AJ9W0oVv/tjTfPhTofvuhGpNpPHqOdr3B9Rg26t2IkzzdzZ3UcRsPni/JdW7QhTWmmlQk/4lGOadn0DCIju9icoEtKM3rkqUK6acNWXmnnTk4MwVlp171FLD8BIm4v53yApvDfksnm8aqmNp70bAXDWAYszkA7Dw/mf4DnkNFKihRWZ2DwLzE+BOfeEN3e7p3gGBo9jEP/wz9AQywGnNlifrgeyf3hXBBvL3VCCs7RTNpOBAdoc7WPHd9jfTRgtPp26voT/EqN+diJr4jfAKIJo8eOe1ZpOHNd3JsO4VphZPSLLTbiHapZsrTqagiczWFe8l4LDbLGuaMIFVCRHSQYjc5AB9xjIRaBvwlG2RhUi0PfbTjZ7Th4tFpvCZlEqajsg5lYsTKENA7mu43j3CzTIhB6AjvJvWxF34oOAAdaZ3SPeEU9pp8mO7zXNGwrNwtwjqavrqNujvoJJfAPNJUmzu47P6QJ18wWMIJAztTfm0WkoL+vRLq49YaNauifkrikGhKSW1lBchU83NLeRXrSumLm3rtdWraIYwz0yMMs9sRKcpTXKXaxaRotN6ZKKIax6EVwWWf/mWmKkVOYGrYOzE7nKcfZ9bgUM3h7r305Wdy8eH6wz7pTOeB6sM2kuzOJU9iz6OJwmnqO1xH1cndnU4oL/N6jurc0nWlxbW1yW5hPNBz9u695xk2I61hxOOfbh0Xebd/GusRbpo12sh4fH4j6MUGgMNAWIU62AdQ56bSt/vAWDF3GIT37k9YkMtE/lnlPYFZt8CXNtgvlmBtw8JcYtNPMAXI3DEVzVRbYqRQ656/jvOxKG3hQb+jre9g0OPb4gD9NfVHaIgWOdQI7dJbTHDSmENlUqO3QyeLtN0/K+lQd6Y/mhOGre4G9hyqm1PB26IC5ZJwewESOFL7/BPEghuAhupTeo2Pt6Yuvgtmvj++PoMIXHZElJ51eO69PCvyixbi61oJWLvFv1XwFlWGI+rkL/E3Efl0qRxA72IxioEq8O7gEyK1Y8csjC9nv5kxhq28ym2QNSiUebGSnRT4/az+svxfMwynfFbbxnHkeyGNbiOyj0+VPdGJ8qh0qPlwhXKh6EQWoRbnZX/PCM/yU/Bp3uSSUMBjCpOdHOH12zMRNgVMUHFfuWr1HF7sSQ5ZkdufWqmzN3ly/3XQ9u4Jt5nDciG2lO8PjlNco5/pfjo4E2djbfDmz3OCiw2gG9q7oJHYARX2dOMOqhFH+/Oy7FX90Xl+IAC+yXAHd604Gimdd9Sr6huzEmT1zO0n19HtI+bhPQu7r8tObYBcgBD15h5tDMzhn+HdS+IbjDBsAWQEwMrEA=
*/