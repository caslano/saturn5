// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_STACK_HPP
#define BOOST_ASSIGN_STD_STACK_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <stack>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V,C> >, V >
    operator+=( std::stack<V,C>& c, V2 v )
    {
       return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V, C> >, V >
    operator+=(std::stack<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* stack.hpp
mWCFtHm7hPOxOhRqMd1Pywf3tZz4zwz3QVuvSeYm8COzRuSJcnzwe9Q1t/tHMCQMPCCauuVk9roSTHerPq2C7jN4PoulfAlVoqcZOoF4rRTRNeFzt2FgUJvG0+Lp0xMWatqbqsOobiFHmHlT6Tzd39WX399lHDOxuoKHVU5RuNrLGYl24G4sph78aKaiM6KGS5a65WFRJuBL9cYj7vPdMLFEJ7wq/xtTJeYrjRpcqTBpwVbyfXDRloZWiKvTpVG2kjH3JkrgCkvXcHTZyjXn2gxU+KDJUVFSas5kZhIEVOLQ6cYx3NOhusZA1MzcwbjwJdkAWW7PaJ+ZLaFOjDx0kNs9acQvpTTAs1rbWrdKpCgxq4UT8iqurijXTqZn+hacJGu6k/oYbYa2byYAXWfiGDtIh2ZT7hBFpNElWe0coBsCUCqG6Wn862/BucJNacNttTFCrCq9kNuEpSWpCF4tW4iKB+74n/PWgb2O7MeUPFJt1cBsgUa+B7gYwfDr+uMn4YdOw3xvP4XgOnrvRyU1RjUnCyg7M/y89OFhVWEcjcqbYq68vEP9aU+0tIJZbPltTk+WF0zr75rPsH0mc5ilMoJl8VYitUkCtm5t7+myJ3tHTWaRlq03CxpH2taAsBib4ifinEFpqs4Hc8z1/jfS0Q2XLHJ0Q+OxSOm7Je9AUxf+emxk+TYs4Ff6Rrew5hkHlupAUOuCiGnwbNNpetv2hVSkBHPLJgGQwudgajKZMsYRdVyESHhI+Ej4X56f98aCsLat4+LBnwV/F0E7xs0V9+E1RU/eiftIXWKncZR5Ek/0l18oum6HLmB/ximjz18b+4UQinkA/0ANkemF6q2+3PNHNQZwGftuuZbV4dmHvlqRHBrRUceZQH72lPucG3ykG3lnw1YiQ7lWQ1Mffb4dOXq/7cq9fZ4XDsm+WTBZijfDnsVrVNd0xRHtZSVEAUSj6k6lIi4xgF2FYjBj+8YdRIReh2JpY8y0Ii41gF0xQukqvbYQ5ZIk7nKrr3p5UOAe+7zGP4uZ2B0jnTIr1G1mhsLSpf2KF6cXhfkzdwW7n7d8pwvIkj9ihqnM2MoM3+AFMsvCqQhGyU5/TkwpLiLINclkm8QduOKGaSh4V26fGnkUkE3n+QhqWI+B3Etkj9bfSeCMCWtkmoogFxwumbjcwzpZVp08DIx4L5lcOfjKWdoSkTn8Q5ZaqmIYhFYigi24oIlcSVSLLyIymfEHE+YikdabgRhucD1qED9isDtqiOYyYgvvI22G2nmUfniU/v4U65UwZsTm02aBkYSBgqmEeICYxCvjEgWGBu4owP8O0d3r1r8UVfEsL5CsXtd5T2c7kxXDjhXAi3QLH0Yh/K8riKr0CKeenseEkqQkeLygUXy+YBj+SV1bqYvWlr80lbA0/JWERJJbYG5E3gAw6DBos68sgYnZfhmFx7rZBhlBRBkJEcZDGv8syrgcD/+5+mgAuOXtZ/ksEr2J+lzIwPBMx2TryAhrPA6iLciTP54HTdHsa/wEwdu7kCDHtohL9s6Th7HmfMLWO55YsmAzUvnNVVvvoFrcKCNYfAt3gtzzlymBYz5KJVSU2dfXX84wKajUOCRRiD8nzvrAxC92zh/IUwXTGgktx1Mi99Rq1UWSetTvTMvcz9HZvuPmrh/Narm+6m5w4rG/JMQfQqw0leI8gCD+o6QX5WCTXUvvIwWARJW7ogvHAb76vBz9YAcM4m8Psrig9SqiESV6mY9YaDchsaHNvQdBxYnLLiYutjuS1HIRqL6nQCOrsQE1fP2LFO7WjHfyxCKlaJDNxexIKv01rZPmgh8mw5xZB5kBqQNkBEuuYXM32YbUgaGHBhBc+Q9Bsmwuq02hd9EIz7WS56a6OCyWSX1XYp5Ow9nuGdyzNZ5tl79hML9rSHCDI3npirF46DOB5MBza1/Q0zDN5S2gKScoemLw/rkFXJBkVlifsY8p5j3qeIFLN+nu+j+lcCR513bw/Ua9xh5ZxBfV/Wx470yOaaKN3bNmbzLDsYBviw/X6y+py+Yh6w6m/R4VqNMg8nSZSceKFDWf7fWDLTGHqiLTe6/rmyQ9/YB+1RNHi3w1nvP3QuwBbMWlRbJtFCOsYfhJVbOcfVJnNJw7DrQuqmXEF+dblvYmn7UsoOz0Pg3qUCdaMU1zEu/HpJUyDVyDF7KaazYnAGmvQKKPaN3kTmuIvacr2F1qxxHubhaalayELljuZvwXRXw1HnC/hsaFReWlFQcVSHZag6upuevxuel/dqiIztCq9tC6q7S1yG+tCYP4EKSYa2r+0Mb1NO40V3JT9UUIMU0MF9LoGO3djQdXjpKCF8+X5W9ZqNRa6MKGiu27Yg7sHgoRErf6woPgkX1nU75NhW/70NtylgP8925U6nC04cR9cRtdb4hJiiCRr9+8lgjkvF2Bx0cHYg+f5TlREAwUqvnuq3ZFkt14ZmYY2LPnpIx0DPY20HvACh0qH4xc9Ky93vsHz/39U2dXX0+fZ8OTk9aH5sePMEVyXz1EuYgW6MPcu+3ZL7m31OmRLjG4qBooLhl69nEtMlaz5VvXNI/Rcx3hBQhyjJNtIg2XgclsHZC2qdYudsroh3HiPsUC5g8dUA8wjZcD7NV79DQFKv9IV3gLbmBaF/NFGHIVffD6VJzXjiL/M7XuxTDKVSToZB4cCmkjwvXvFO0HiC/SAMXQbDWauYW+fOkDPudj4GyBjRMdEznjSLv316d7tTHQwnHxMugye5X/JKOoPLdHaVPukMA6BlUKLGQKmjfJ42VCSX3uHyRtZH7CjW1qwWViFI5v8ZYRDVYcfbRsoSaMi/W4tArcUF0aasBDOoFGql8COYJ8nmEbG4YKV01CIbPlQc5T12WKYt0IPPwMm5IrT0m3QZntu3/oYFRgM62yMRnJ5WABTntUNI9dQMqf8t7aL7qt2fFutE4EgXZelbCllFxxNSl9SD0hjw3Gl1J6LXvmo/ER76EY/scnSZZxdrLBTIEr4ONtTrz+IW5mZaQUkUKl73hHyvObmyLGY5kvSdCmGGAzgBF6QUuntzhwojrr3J79er+yWt8wXQnUMXwzK/qtcYqlAmJBXaAFl2nwBSgtkoBi/njPPKM7IpzIzbRCuYeZmbwuylGpRml8z/gliuDhW6SuiBd7Y3Cs0yFonVhI0jRfi7dkU/izZ79umCXWfOWiYpNyv5awQp9Xwuzi6rrXLSYT20b+o969wiucvq4QRdXWSMTmjSVsI/oP18uBcZuxSJb664jkdGjyELWDQNqMMA7sanmm+dPYy7estVkngBvlC9oN/odUos6Y9eBrkN/NB+XRqlEWGYoR0HjZI6HXts7gSzrmTiuQhupQyk2mOuQkHl6qMnw3khx7yWG3Fa3gSiQKL3v+PsnlMWXuGrM6vhKoF7WfLfywd58K6Apyp2HEWP6uq9kEtz8ti3WSC7OhpUAhHFJBp8rwDWcgpJ1UVird/KEVsMcFj6N/y9AcOyAyRrZ+s5qi5t/BPvEloVkMUaJ1ncFZ/giarHlnY2zu7SRJd05xRoqDgVLs0EC7FW0mt1E3h29gJlbU8xYTvhwFNIVSENbCVRCYTWDtCJwPyj4ZitwRMHr9v9u0HqQdaCSxjPMCe139p6TcqIPzweu7tvxP7oUWg5XVSS87EajOWmwcfSkZ8zhvPXN4giWxBwyTkHgbHTYu/QFDxsixU98xoxbeRN4lURAZKDNH0T50EgVuhfaXcRVBr7hleV/5WiPuZz13BUc9ajlzusmWOuXswtwlfONAroNob+9mcvfjfes2Jr2Bopf+CrVKIzmhxP4cO7J/O3YNjCeqFCcRC9bCNnvaD2eqkB/rlqnB97atBb9xqm2TQLjAZpCjuDBMvyKRinupM9YVTQPGTqDwX8ANOsr3I0dA+6iSGOHiLFOloHm7cebB0R2fNFCkwFHBphKOg0/AI+gg4PLZ1J3VlfWumoEneYrTkYbLr1Eq8go3FOz/XJPWpjcJbxxrV2oKxB12HxBSVbhxhRW8uf4l0VYRV3sCM4QEavUi3CGUdk7fOQFVw1zO1Id6xau8EKKQjdAiBYWHqs5u8v8mnQli+b6KmytRbKpuOw90q7oKERu4eaov0ttH9TTp4/F4tao1/BSsFUIGGEUCxnb1x2laiaun1o7Db0hUAYxMFAPllsHjAmc0vhZGO+Cct5U6nZ9I96IlS0qfoJmTmWpcBjNzLIQx77PbUsmkSlKtNIVT/hT3tGx/SHStBRN9JKGlMggPUBoPaHvo0IQ0+sKRJQXN5J5GN/KmPrOmUxdVuw3aVNPc/EUVmjnElh2T+jb5uBVbOAVzOI10JZ28H9v49ybYKf4zM+z0APypUBQu4wFx8g2dUNnylPmdEw5ZIx618UHuhrPTofiQC/ZJO+kOH++FJ0E39SuiCmHoB+HXK0f5A6pPySHhmpiMK8yYeozowu3vs5BulZXFZQcsvv3ISC0XM/g91qrU6VRKZy2uBS6DBddZW+fbmiOEu6Xph5IDDJ8hG7holq0JhmqxokuKIifLF4Zhhwpn+CAPU/fpbU2D0CnZghYQbEouyMl8NdKUx7m5Ee5p3BcDIZyoyfd9XdC0STyENluc20FcoPfAWjdFUS+CXH/OwNOEWwEWWIkNH9hQ8yrFKZCFyoJxpNYOd517zdflaVCPqvtOAjQ/tPHmg5SQXmrnYclVYal2l48IzxqhTPQcdNfNleq+hCfD4O9/4WFgbEyLV8skLFPYtWiRCp8fkWhQaLM3gkJGx/X3lyAyPRV8t8lEpSQavV51bugUpPZW4DcuSrmbEzNoO7qkXwrRYtSNLNoHTfIVNhVyY5mS83I70FUtaxmMoy0mBxI0VPnHGyhvcU7SUDZIGUre0HOKKNnQBMwW8YLZ8aEJu29ugSILeFOSfXt8pky8soIefmo8K05Ov0KoLJjnn3Q/+XHqPBIAAyz80wcgosVgBrW+fgT2B4bzESEBSAE8cr1LyfW9TwAmNcGJbUU4roUghoqIj4+5dsGJ0MEd2UBqapxB+pQLrBEIjXjoBF+WZJIIVuMmqrv4DNKUYD/1q2X9afRVCNLvTY90Dsd8oMrSXwaoZf2xKhYKMXQs9M8jHuELx2lV+Id8FYU9AmHVhqvbPtcgZm/KbKGXngZpBfNAtobGtoae0ojqI1AwLvdCBw9Zg36i0XZyuq++MatuaYoELgI5sFOv918U/DjwKGSvzVpkyH2hDO9CseqMhm96ogl80WFHpXciflhiWKEp1eW7RfeZC3rfm/qP7yC87WUd21XjCZ1ADXAOzd/LFWV2d4xiCzZ3E/Ivjdc2q7wFUybru/CVCmsf3YfxiXKL+pgdiT/09gPp5547/Ek7E6GlTzWNKfqgjntw/bZiYL7wCP7g3LvAzVA5Srx5eybBxGmI6qGsmU9ErUFLD3tyeI3dedSqHU/1YrO63zILQglWAy6NWmiYNKD3XSg3yO0mxg/jFCiXCQG9Q6/wDBS2P6keyFaTXyZYigJkKGT9oQnzZJkQZ3qEyNlMRHGxtWc7fGXrK/qV43wk0+3L/d9zfLIw8KVQnwmZBcxehxKwC6JV1Pt9SIppXc4QDXw6i9HaE0hqk8VwpfZQJL8ihaWpNUevi6sHsVL947MllE7uqwat70kYXdXe65PZGovEW5v8pCS47Ay9q83mWxYnGOwNIQKp1wMT3VqstxNYRSdf5c5yglYMG+FufdFhnnp9EE7eXzYxwLhMEdnOP2iiO8lGE/CCj9y5yVx+W845galmptMd8RnLj8Ne70rEf6kmnkEYFQvL9Mqupp1UpUUhoxNKHLu5xU5UEiJj12DKBq3a3MMLPp9ZdNZKkMq5SR3Iw7C7aczQq6S2hmMaNo3hySntTdJ4x2NZrrt9qmbNUrZbP1w9TiaTyD+NKeCqE84B88dWbRq5i+YdyWkWy58GTjMLL/Bq5w5D0TR6cAKmCTkzDiz63hCBxpNnoZq2HCSTHiLcVE/MF+QpvOtciSlckVXvQsYmqOkKE9WQHB8ukmqEiWtHSBo7BXVUo6WlPoQvb0x03Cymm2PZBPtXbQpzhzJS9umrRoSBGXaV6fdk/aLFqSkPh1kfZOpjnZ8WWeJn6nTpnvFLiZOOnF9VOlvEDM+B55JJzG1KEzW3eIX4J58NuUhducTZ6+g2z0PoiaVHX5LmVT+tT9cDl45mlI4acnlS32V+z+4T1neq/U2qOrKIU1dvrZ4xUGOmdV25f34k2rH9DxPQyZDaLNp+Olx5b1oG798jgHFd/mnnvrc/M8sWmlQaXs9tLKdJt+u+SeVKT/BIfjlOlI4d91/+Yjr9l4uqtz9JVaEJhyw3GePXZEAms7+NCIDIpURtKiCT9XTYR73VDn0xW6JfWgbwl0u0D7AZT8pntuD43f7qYyZC62ktpbHjNsoBjKN8SIyVzXnleRvn1U+cH0nTe54DIHP7onZ6/zBTctXSx9Z3IaxC/ouyI/iY5R0IMSEAEqvf0TY68yJSayaaoh26vgKWzQZE5+ZVI/ar8oW5GsWhob8TBUs16LFAAK5GHAzRIKCMH0DX3xH1nZclBfJc24M0lf+CMZHRkIKGlpRMfGvMEp0BJec3fux1RfTHo3UPlCP/qFDm9SPCCQb2ZN+DTFV44vEleaNoc+pmZ+0ufuKAAHyiH0QWLjx7HAwm4IdH5Q5gi/whCZkVIMgPu4oD9eOH5+UOwKuWTt/7VG8Ib4NzgsWkjYZBPHP5na4g2EMvmEXkZwFGF42CaCbzWCQAURcKgTYKzlnz4USTsPox9pQezNfWx/WXu3IjfkiTOJudMMeknXKicUSvFbN7mBZSaM9lZdZCFsEXJ/euJJ0JK6D2p9jJaRp8pIvYagWkA0mNh+w+R5SBvLF3XehJmAtB5hIGHS3/JCbfUnSG9l7jvLEywsE456MEl+/YITwz62ZZTPyUxViFGf64LHCn5PUT8r1mjki4Zh4HMdNws+ejpoASjAPP2B8MjE958HGeYsRwAx1udytufk79zrOuXWGPr6KtsWWSzOV/moBpoJq4AnC1rzqqelULqCKv6nsC6WloCkjL9fnPL+A7pMIxnfLh4aKOHjBPKrhvcMPu9D+7vdVnb9r5wu59OA18vd13oxL+uZJbPUO+w9+8+nqj30nWPWbfWY+wULwB1syEMgHISzcSySzuA8br/3yu2nYD+bTDve+Lr5DdPSSeiTatX5s/K3/izvcUjy/Gat0zWA4y992Ef7kKP6mMc9w6HRMoEBK/9cqy9nYVP3cLovesb/W/smtukqwD9n5JoaJXiNgffzNMfhREgFLo+txjady+KSj0Fr8cuwRpm36hrMQ4hsraC7RXH7tgYh5GOY3RLJGvq/4eFqmXaq++PELENL7XXt1UkbEPFWmyaq/CPUJ8e2ictE3aR5oE5qlzDRic1amDDRjQi4wGuRyn4SkqPLjBn+/6GnlfjlCviW6rxbmn8vd+6et8loQ9offmoVlfrdyP9Nhi9m1zvtip243GL6E1/RznDGSTvOVGwytqPeHr8/jvk/isNxU+uXhkcYE3w5YzqL311MYO55VeKS4jyoZXllBjzBwqmykjm5aqwS+saCTx7WMbUz0jwckEjqMheVJFsh5LMO5c6fIwuZEBN7hP8HZ4L9tPmrrpN3RyLi7r4HUDDY96Z2zx99dGf7m2GKRXr15kLn6Yx+giIzVgGw9HzL9PRbHp96yKH8AH0lEYJ8DPziXDvGn9WxTn+kSdswgRqDjbbtXP7kMEOy6r99N86tIB/S/i/L1mosbfDthzYcHGCh4ZZd5iRKBimA+Sr1R5AITEWdNCnnLRL+xuLzNU3I+HkTWNn3YgXonJ+JjCpx9eMEjqbJLSid+aN0C7k7DManyS8ztuUI4iBMTRIzR7op4bxo8qeAV5HNWHTetXoPyDltsEJpyGJL6K6cgb/8EteDA6oxb+4tXnGWS+58Zf1qHrSeX2s7IvBwdWo2axXW/3uzEAs+6/ygeWy3voePSSWciKKVQpZUY3YLzFTXG0ihCYgGD49/Ylr4foKgn4nB4vvK0b1jQDt4f49y5zGFBVwKo7nTJX8dUTJPV6Hs72HrnLc9QS0M714LMQx67s40pv34VzEJudeaf3y/8mxjUAan0EQurN0xZcCRRfq+K3tt4WBxRlzz4yo36ndSDrKC36sS6PL6Zz4wCGzV2cIeaMxoRXtM4dNNbSlGDuqaWTnNkfAxEb2hUMrBWD6s4pRT3p46Ry/Yk0CBYGtcJxH8zRIeleNsojOBhLvS/eAYuy+Dlv7zX7HmzmqqQRwoWt/TzyFwL7VnzyB6F54XIIIK4S7YOQscWAR+PhJvQGmlAELssDXRVgPHRnROONxnt9MIsMmwqphNysi8+fK9g+HYkVceDahCLyUllJq4yIWwu+ApZU9AYf1qF0PhXKDoy0vwfxXiG4/ZBOYldAQtDF5DpVxa9a/zk1v1i1j5K0Sxo0HBerP64Q6Y2MdWgav7zsolMpt3IdH0XPeGoqt0q8bSq7olpYlMmSW1io5FAZrZK6mSGLIUe5I4ER1wkfpM4GnutSLZM6Om4P9LuQh3t1UqIzGKzJPtsHoD7CzTsd+MputwUgT0PdTg2mTWumTb81O5/zrvLzDRsI8mFZfxoav0lnf0q30+wZ7UgYiUnnnHDsGiSX61B6c41+UtB/PjQrKRjk16sgJt0VRnhPXifdbHB7Zf1DQLNC0YLiE1WldcnVir+Ty4FTpnT5kWzSHYIvYn9csbb4mPPakmFXbIkyokBFJqNvZPld+E4Nh0JHKV0AVR68SEYQ+eVD4Pb0D4Pn+tQH4iW/kkhbsL2ddcjnUT3ty5EPdDQNFkf1RxUlAGMmdsc2vosDaaGHuCiRWSREPU0YTsEjVa2sEh9BFlZSnCfm6WOaH/zvuT67NqiWW1z3QTxRIhedU3XAyoDVl7oskP03WZDRYDhADspjULs7GSO9VI7QYn7IIHv3MFWMW5QCaExUIC6JgTUb2jvYgUNlxwTKYI9zHhQstraa242DhPQYHsY4xnO/5XH9JOFhKKF9ndZEJBOCPfMJ4S5AUtveN3Vq9VIPsrt9tCrEee2hcIIWBpjRghAXOa7b3USNwelY3JE3k5ldrPYNSJR1jwN5npfb4N5jxiWiA1qdKKRRvoASNjMsxTUsOiCAxz0HZOM=
*/