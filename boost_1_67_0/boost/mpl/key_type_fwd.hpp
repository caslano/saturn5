
#ifndef BOOST_MPL_KEY_TYPE_FWD_HPP_INCLUDED
#define BOOST_MPL_KEY_TYPE_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

namespace boost { namespace mpl {

template< typename Tag > struct key_type_impl;
template< typename AssociativeSequence, typename T > struct key_type;

}}

#endif // BOOST_MPL_KEY_TYPE_FWD_HPP_INCLUDED

/* key_type_fwd.hpp
nK4AF2bXvHOyRvO1/0PQOA3weuO8naDrUXXeZpolGefto/IGw/FLOZloFTpKuFTuAfrnwLkMFCDZBDW1HVA1AgIqAzwlZJZzQ1DzbAJL75IviqkXYKni0TQZe84cJMGuCxRI2CpMgRStX710zcHtyfHRMfOmxE1dpRfHsPqtC75JPbMt89jkXYGrxLVZ9Bpj/V8rIkG3dOomrv2FaS6SMIJxanow5NgRevPmFWv09ksZ/ZKUJB084cxqvNFAKToHpqeR+ekgDnu2Sbzw5FbRszK3wpYt3fq4ON/q/UR3zmLgqNTr19LO5uSkjenfb9TogTrYDHYXQMYZmMFoZuNRliG1R7mLTc6/8viS/X+xb+AHojWSix50HJX2W9qpG2BkEWoA0CYd/JIHGqbzp1IA0hAflfvQQxj4+C8fGo4A20yl4c+mfKxA5aNgoZDO8Ikpxl8ZsB//lQG2KIVFo6UgWkE469NAZNr358AgAyeSNe7D/EtQWJWRkeaMgI/xIe1GfPwPfV/qLtfJ0/Pnb5zFA8AWHMwAc+Q62ZMCSquwIq21QyVN/u9KWvH86b8fSy1gSK6UV2x7uuh1ce/r/CsQZZz3y2Cviv1Cg9JegPk555JeDEEz7HB/j+7Dzl0VgS3otQu0tD/ZL7DSi83MHpEPONkkce8fTBIv/skkEQk0lfsxnxNxhIy49PMjhtYI8zXm4j16GXOxM236sZE5jbM7Um2BczoYf5G/+w90fvlHOi1BDTQsdq86sV88vaHPdQf+bva+Y8W6YcyUeRMmin6zivo58L8MigjsXsVC9LrUFvghVYJ/8A+Ef/4nwt+BllVVEDPsmUeuH7YFs07mnuQf/q8FWwqoT/vxCigyGXCkmvnUl4gcqAWKadAdFr9vzIlnTg0UjsMvYSM054/A8hjU97w6MAcbZTOKQMYFfksG3lQfDmrDVmDoDJG/PrXzf5bS/ME1J2l+C+i8ouyN3v6/NWGZTFCpaCL7qBUKeKRWDoJPzNI3tbJ7f1qWx6kf6ramvPdLUdaDWAn9CMU196t2C4MlKt9IUzZGrTQryQcTLDPj+4MJ2n2QTUNS1Lv3ZX+ZvzaHLzMk5yvuvsMXiMZFygJr0ayuzpcGFFGZ4HshC34PEhgQBuoZ7If1gADDdDAB3vBmEHhTQOVFS8wuYC1oxiKdjzU3JZrZnuTB/To/DY/u1Hx+tJtshJro9g9WqK0XPmKGAtz5qkN8zIX3x/jWC8ogN5isDqPa+rxWK7BGcqxstf87MqtkMqX/12Q6ITIf6EFGgrj5LhYBO9x+wK6If/q5CPNvgZ3UoGp7/vJ+c76t0poFpaj4oB8adsDjM9bBQ6nnO4PCZlsCWSStpoqOC8cDwEQwH0yE848fh5PBQoD+Ao5DFIYoPiAARMCFtAZ8p9gjM+TWkUUnc7ZxcT9xtPuJyLN5dGhGbmKhg4lLi1E/d8vVnbkW8M3Y/vR+3wFb3R2MHOvKa9sZWRw6YvPe8SJ4IcXSmcMPd2ttX5FvKk76uRnRp0T4vCKGHpoeevcne6OJDwuI/9bKB+aaSaJ/g2e2mcD6N3icPijXDBhflyKEZagXlP1XOK+/I/qOmeTpf23kWyYNryxnLprxm2Mz9kDgjV1Fior4F9hE3By4MYB/8hDYgVot78MaOtiL4e+BGu5sfkWSwL9QTNpZvs2dvbFJ++i87IkJ5fXk/W2+4HjBxnw+6b5dnrSDeZB7Krfo0Dh/sTOkJre158/UAyMjW9gPGTtlZEfvQ3pxAKu/MOnZw9tnnouAhyOO5Nnz564Aat+v9rc9Ch2bNPbEHopm5jus1SkWvHPvW/CSPs2Cd+4fLXjASvL+oOXw/wNpRiZd+iHSwUcMxM++T3zGpxE/+4/Ev0a0rzH8Kbnn8mfN+645J1iqHi+Yi4VqcB5/0u19bhLcPo2dk27/yA9/ImWuNLSqlE1LeV/MnkhR5KwZk0h5OF5wAg2ytaitUj7QWCmf2Fop/8zh+RQwTIquOjLN2JB16OMFRUiJPpnHn7/wPiPJFz6NkfMX/rnfNJH6fKKm/Tg5c0g28MsATbKHZMo9KhdczecPYd6a3RvxBNifBczuNYi5tofvDf/VATBFBXodH6VYa1vV75IP6iwSJfwzox0bgXWv36FDp35h7gG6xcyVxFHHmzhAlecQlOHUvpG4CHe/P4+KMH0iyx9Ci+mhC2AnndQUdBdebbqW+sCh8Lpf/RW6v+xgZ+FXoFldIl6ezrgORYUK/i5V1GySVXvd4MuSU47t2QIQdoFPPYvNyA1fNAK1Z4r8vU9S6/FvHYFmRe4ttFT8ZAu5yXyNRezns2DD7mB/pWz5vyLSUyZS+j4RJENkMvwfn4XOBkQHSYyfFYnxh7nEMFFF892ZghtoKO7/PIVzBtfeWZwodvFXqArv51Gl0j1T/d43s42bp3kop1Gqp88H0qBaup/Hl+H5C31odw+XsVgpY1mVlYrBIm9fars2+8u8dTl8BWgv/VWFPb6s0EThIqqTikywOJFMLQBPCqhUMFOA1R5CG9AE9L6Bplx74OwJiLZ54ovTSWdhrcEDD/fd6bmpTuKQc8lnp5+MrwMdvNaPAX3uXgo6OXKnex00uY+52By27oQ6LScWLBEeZzwG1i9zvdo1HwFZWL3+kB+fiCZ7+CssuO/nrcSCe3oen5vyXxnG96cYLeP8VeLGw3e2K4j3pfJVQpHKih0dd/DPY0pH6/AHlSPos2PvKGMvfQc76hEyfv7FvyVwC+FH3eme0p1emHcnAzXcTKcLjuFmOlbAP/y3BI+B0qqN9fb9tnpo3lRowJ4u+BEN2MefoTrng7fvrE4ssm8C60xgfZMER25R4IjUV7h1042BgXClICVlViQxAIM4TvNjcnZEgjQWu458J1f//u8QQ3xE+8O9MseIISNpfvPxyUcu0IlHTiWfcTAyeCc8f9gZ3ZGLNL8/4JugYfSOwHHrRzkY2dUZ2T10YPb0vSKcCYvpoMOxF3Lspbp2CvMTJ63ZGC2CGeB7+mDY9lE+9ianASQcDH4DqR/yG5hZ1W8g9R2/ATCoUjZ9LpSelaLMHCXqsArSkx9CmlAV6cl3kD6TJd5BpYueNO+iRgpY5N3KwwrWMaTXfIhEclUS59/lewNgqnYMgz8BFtGfxaUADCwfXVk16XLXNrhg3Sig3vW/OdEcVAO1y35H62yXDoBEc0+1wNbz5+NdnKWbd+rAQuySN1IADW9nlpbldkFqmm2f7q0bDX4KCNHIOqoUEjTC22r/nvlN5TM+ujP7Oh1va1e0B0v+cWv72T9uOWtAS6MJ0lxvTkca4S6wZEEen/a+sjrr03TVtH/Wmc/tQhqzgbRZqa6dsQXD8FEE//t29lLACabTbEyH2az3ncn2yQi9XGUVeU0+IeJ4wbeY4vI8/tQHljGJn7iMOeX2n3RzL4E/lWLgDK3CUsy4Q7krGbwP/dGyOmFX5Y9ApNAr/EkpVDkwYZ5e3Kgcy3Hs3Intm3UfrqJb9+FUmj8ZkxgUOBott2Eb1JU+9iuRWZigtopr7OgrK/P4ce/VhlwVw1j+Qey0sROG21fhRsd3kxkS/0NFjUP1tAB2+5jjrOEnJXif8LP8qgRcN9+F3GjSFP6V6yyYiObTyl2iz81ywod3NDeaKSJnCviyf8G/LeL/I/qsoTSFJagwYEHu52mCXkJuyQBjCX4twcuchrn/qgEkSkH52Ss/B1X+LeYhqoz+zLAu9GJm2F0EGSv/aBCaqVHlF/8L3oNR5Rsp8GUyDb5YoWL4CZRi1/mffgU1vdz9Q+yXGHy9U4FOcQ29mfXZvb35c9IIaYRgOJ7R7PS7b+w3Ld60cLP4f2KqMXqxnzs3EmgNbq8HQZZ0RQC1IcGYl0Bh/90SRxpKLF25i7Sgc11Y/mCpB4LawdosHIx/uPNBN9hKQ9r/A0VYYXrQLgCAQ0vEXQlcVNX+ZxzuvWo56VwvKjxn1MystCS3ckFLlAR97lupqUGLllLmwlNzTdFxy6LcsCzzn6iIT3FBZRmBYRmcGUQdBYFn5qNEwDJ/l3fG3jvnnllhZgTBz/9TSV7uOef3+917f8s5v9/3p1XeNcZiOyy6P0jjLTeu20ydIyDW4rfoPGzYbeT/0xgBMf8X2oVjYusydtpOJ2Ha9kkG9T8eqPsLIk57NZh2mqm5TDLlkPn2GflKn4dRzleucCFejcfUYgDfZN1J6AgHBHyH3UaCj7ONrPQhNOG7KVl2HotLSVGTj97jyWkx1RR2Pqj+6aIHn0bbablAl0gglvQ5RxUiROSQL7hqPTs/ato7NQwmNd+1COYU30r22KlwYlBOqSul38Rs3BSjWs99PH/eB2+7zmr6PSnxmPoRqirqeA49+Kw79eLYXrIqSLK9VNEowh0Ghxza8j7VlhVWbelUrIkNgLVeM9ltveZntes1k+tTrwmfiJ3dGWXnqhJqmmlpSaGH0pLbLqUlhY1RWoKeFHcTa36FWvNCF2vuJKLDSVhC0IN8vcDk8Skr3Apq+YrakkpZUS9R3RY7etUozjKjSuWs6Rwh66CBv5LqQXD/TnWR3JXUxhCduMPXrm0KU521zZVUB73OQswvJUJcrYfJWILuBehGfvUSX644jKoTZzn9XkperHZ64Ax8iQcRVbpIqKQxBDRHTLb6WZ+i6aBOdi6Ohs06GJvHT3MrhYG1pTCtPlLATOZaenpzJpylkwwqIh5BBy0N/HUP4rnjIp7rjSEeviRe3CCs/i56z27/H7ft++aAahy7dPbqyI/8l2xasmWJc5U3zXrxWOgN3dyeF9urxozSrvUjF465z7KB7ZQ6IW0CjFNCK5PY1cSXQys/EyawK7pkEr/Sp4WSI9/2Qzm+HLW3dOUcfxk+IY8zIUEAAd8r2GquqB9Gy66KvsBu2BVLTn0JDoB2eIVkhP8sIr5Yee9BnD17iGyNLtbmGQ1p/E1bUtBfqEWNzJqK2hucf9ENTtsWP5knXJtnMKbxxeFijc3sv2oPL5aGQwtLie2swJqjpHXKZuppd/Xs5wJactrwufjA+oufH/RyHZ+XpNyL3an9Wqccp3jvLpl17juS7tyo/dGABxdDU/GqYNdmFc7KrEjynIqlwXzBB5ardgqIqxEkFUefyF1r5KtO2DcZdtnC+rJjJxO/3a3ChD3A81YtXBwxY4o/KTSUhtJiROXe3HUGXtxbe/Q9OhovZ9nI8eKCRREzp/jz9zKq50mVizYhYPV21zhcz1fZRFC2uVjgq/Sl+P9C7cK0FiZKtJ9Zqw+XCMdulsbEn4J9a4UKaHYUJqnFeUMt8zj0zKufhqn4xSholECBE4aiWVnQz1E/Ca+4KaGEJcDVsWaSAjEQf6leWAzQXfzBbc6btXbT6fBJ1HgnAQUWCXqXOF4vzTaEVVwg+rrEAfoAzXR1xn2AIQ+2eVO9c6xzOxWM3tTVsWQUunif+yOsklZlwix7FeqqQhYC0SqmhEVh8B2ZMgyWMa8QfKVZzACYFWKDqbDnFdqRKlySD2mlKrnpYcWqm52GLSGs5lhRMMBX5zw9BHlnBR0jgzPJskqzYYGOr/K6LF8W730+zKa4AdSYkN9d6ejt542KmHXZ4mY8zIyDfu+MQxs/78vD94VwUpIEb3ahYLKFo5URaPm6bNgv3WU2GMwPWe9vtmExmLVJi+DdRTJobZTrQSvkHGHQLWkBMHDgm8tcxBY5lIEvh6Ez3Ij3GAVaiPl6i45pbpAfgUzh+mkGLePcLgcx3I1zeI5eUxhYE4IOca9OZVzSPMEGYT9dSvCc6yW/c4+n9M61Ti+O/cQVT2y1hvU6a7XXMsNkp9MdmCe9j07AKBCmgwFG/rBEdaIXqg2eqP7c+1uXST92ezk1rwPGwP9WL2aK7cyMsOR43SFq5Cey0m24an82UrRKn86FejEUb2dobJEjPL1Mw9MLrqsUgVp5QLdaWuVyvVY5YT9uvzYCpnqXG5qph94ucDlFktjKa4lNtKxnkCz6tff+HhDKVYAsGfqpq0OGeYLOySR+dpBLOX25Jy4uY1s12GGrvo6OTYfmxFbB7VrMFWk27fpWfe0Nzp4bqyW5sX1hA/RtxNTYvuJrNpfMerStlZ0yFcCGgoafbBfAf21zW3k4nER4CJJi7EGNyMVRsb1Xj5CyRoPpU6Yisn5hI+QNwGQodPiUlc4+ZYlTfPzYcrt1Ygd3DSxCHkPOx0dQ7GEpse/KnInWzbGJOSTwFU18vJZWkz6PXoZwFb/w+JmYuADRJxuVww7Yk432wFdwLRtVsnOmxcwK4ONROHoe8zVdLbHNgR8MOnpwtUZlucZp5qyJQIMQuTZQpRDn072057LHppOEB/98yDfxFadhs4AF2KIzPH23JKU0EX/OfY8XT7wXAGyBSaOeg+PnUX9/qUvPC9D2c8fG2pD7SP38gDd7h6vXs8UzXknpEoCeRi06oV5qMS5N4IutO205ZKftwbcTBL4CFD8X3f/jVhBSoFYv9++o4os79CyEFk4QUnR/sJFRpEJElZOr5kCYqJD0M6/3BDKx+wLH611AJg7ZQCYqnMzmr1aH1Y6BJeigWaMy8KblVa+u4DCrFbUDZ4zX8Tc9caXHXN104arAxhV/Y5N3C/p4n9Nr+Dm5MajOT8xqU/lMT9x9jbnLdOFuv42735yMaQ41ppl0BYoyRlRMowCNQddqmeP1oHAkRJk0GJEER+FzHRM3MtU6TLSbwNFOPg4bJQb48gZw8BNmwENy2hYpF7dzqB4zpcQc9U/V5fPJhCnTAGi9EiuLqP51yMVN/vIkA09+WVBU6V9/hLgeNB94lA6zTLhVpu418UmYXz5ZkzbyXr2I4JNufZGTbvavJ+hMY7+LT+PH6uajsj5W6Xuij7WoIS+mL36u9o+rnH5cRXSlNKmc/YoEfwvbjWtS+VOw3e9rlr+3sEcdRHkqRsvscIbqQ29KEyZL0Dx3DRmp8rsQJnRLmJr4qeoTJHv4lDHpzLrv9qzfFUCgfNTeoXwkxECi7NyABq4DuVt1RVGDDOYgUCmrDFd1vPnh6EE4PrevyhdBAOyyquFPnNTwTzY1bMZq2JwO27Nl8IORQNqaBeiDzEYwQ7901A+222hE21EfTNHr67Lg41SQpctwdIW9mTjB0I11Q9Au4FS/QMtU1BLP6SwJJAvh7AVLZG+zzHSCpI+eNPK/1r3EiP8vMCl1rWmzpxqS5S4bpGqQVQb+0Ap3uYAfrnBNBjy0okY2IH/QR1djF/aMm5Tig9aUYlsllVZWZroCG8z1KqTqYt+mdSQzajEL+2DDDwY+yR39/3AlP6km9cllwNqDAUpbXhKmrYT44iX1om6v991fG8l0+/ey4aD16OyIW7nPqyH3IzXlDnOcto1PuqSlHVnh5ORTnkg1C+YKWp7Qn4CW9WPraN2qU2z8/UIKZy4bSOHMRQOf4pa75TW4S6nNnamONTENqPU7cdZD6NBI+b0rizzMD2OlXAErLir0y4EgrGyu18wUPJ0Sr41X5x43ZIDg754Jy3TOyuwXX2g2fqH6ZH7k+zP8iWUg89vB0hbnbDHw19zwQDnAinH+4ukzJ/n3AZnzKUDSseTE76RTAMLftZpQalaoVazEJbTVqseMtopDrW5uj8Ns0Gx0B57gsx2n+GwFXvDZjnvBZyvwgs923IrPBjulTOtD1N867kxQA+o7e4sT3bHoSLDGDG4TF/BlDU5TLq9+01Mu4TFbET8EZ+00bc3GFrQ+PPD3LouLXDOgs+z5cY+ITgtLq8c5/HOKOFeEp3tE0DkYKiY4pqPUFZfK4Cf9IxG3rHoBPW6nhAGHp4rUPxJhw8R8OlXDRbYIi8yNF2UVnuSfYvHx5kchczCWn4dkSHSwJs5rrITwenTnV3aE13HOCK+HOmaJ3TNgadaaRUr46gJfdvgdp75s0G+nah8kMNAmAynZmD8YYL8u2HEsIP40acBizsL+nWbGtnckzNhXl6pWdmC6jbnJzkeHGcSuHLwsImDOnK0aNY6BSB6EDfJargNZwwOAzmiit5C+h7SkFTHzsi6vYQEqi17ztlga3aiwhgJjdHxVDZ/6wXhfvszbVsdb0qkXcbCxb71Xx0fWA5mTF69ZNF6PBylGWBtYK4c21Wvc6TjnW2bjW9y8unOrVybJoD1xnLBarV7p1d+aW72ffoYQWb2fflNzq6OIHwRDsW9CJoiqm4/xEbamMgjJkUNITROdXHJeo56yg9E8P74/gYlbQ3zq2xKkUNXt6nWufnFCbbe4inrFVt594bAcNmDePbgNnTXZ8H8ZsCFb9qtJFC7Kf/UziTtY4zltgQqGske20c/0s6Ufvo2tKJrMvFnE3UgbOfi1CWED1KjjSHiGBfkvv0CTu0FliFUvxCYx5ptd36sgEOYzZ1AO16Ffv47YpXqd4NL9IUbL/4AvBTE6wxLNKsTm0sXq0dLF6tEZD0jLootiAgyWnQe5/DxWCLTJ4gR8/ap4FF9Px9fTxaNYCOfx9SH4+tlAfDkZmsiTA4U06SrJJXjLOssSOQTbpxnPomA02GnOmdY58V1DnSZFPfFdjhWG0RUWy2GgYwkUiO9xrKcWx2SQ/lvQ54Ic+kwRLoiroUUGagFT30BTUbMx0IxVdIGQDAintw2/IM+FEAGaoagLEEVvDa8xAoUjPAq1g67wT1kGHJXDNOgqXMvJvXZtRO6AAWFhAwbkhl3Dwh1OGh2Z4WXyr1xM9iPnqGh5f8H5p0L80XPLLC3tm1XloW/WJB+PfbOe8HH0zZrkQ/tmfVclxpG+WTkjzba+WUEjRgSp0E2/Wr20xA5ummnhG2s32ELjJHhIWIk/ZbM7GEg0VkK2g1Xy8+6A7RSWAB0s4tMnKQo+ai6q5KNdwNkU55fnwfvJRckwNQ8L5nY+f+847MHWHPWNh3bYSQwK0J3eqVEv0TOa8GVTUJtnbkCrD1Wwj41JZtBpNvpHzYEt+5qCTvp7JgtPHK4ogtYBiQkrsEEp363HDoxm1jcT0KuoLZKjl8JVYZO1bPR8TfjmqKbj8bPpBJW5sCZFBmHpcnEoxArn2X1wjtm4c/0O4maCL4pmTuMfEM0QB3vZxqWqfegco2U/EEOZSSzi0BZm1eK1CyTvae3eVXtUmOgt5DdHLaFCuugHgSkWdhL0YBUXyUd3TtwsP0e+xM0Zls3YF4RguCMzwx0=
*/