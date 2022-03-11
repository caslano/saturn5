
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_CONFIG_COMPILER_HPP_INCLUDED
#define BOOST_FT_CONFIG_COMPILER_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if defined(BOOST_MSVC)

#   if BOOST_MSVC < 1310
#     error "unsupported compiler version"
#   endif

#   ifdef BOOST_FT_AUTODETECT_CALLING_CONVENTIONS

      // enable clrcall calling covention (call to .NET managed code) when
      // compiling with /clr 
#     if BOOST_MSVC >= 1400 && defined(__cplusplus_cli)
#       ifndef BOOST_FT_CC_CLRCALL
#       define BOOST_FT_CC_CLRCALL callable_builtin
#       endif
#     endif

      // Intel x86 architecture specific calling conventions
#     ifdef _M_IX86
#       define BOOST_FT_COMMON_X86_CCs callable_builtin
#       if BOOST_MSVC < 1400
          // version 7.1 is missing a keyword to specify the thiscall cc ...
#         ifndef BOOST_FT_CC_IMPLICIT_THISCALL
#         define BOOST_FT_CC_IMPLICIT_THISCALL non_variadic|member|callable_builtin
#         ifndef BOOST_FT_CONFIG_OK
#           pragma message("INFO| /Gd /Gr /Gz will compiler options will cause")
#           pragma message("INFO| a compile error.")
#           pragma message("INFO| Reconfigure Boost.FunctionTypes in this case.")
#           pragma message("INFO| This message can be suppressed by defining")
#           pragma message("INFO| BOOST_FT_CONFIG_OK.")
#         endif
#         endif
#       else 
          // ...introduced in version 8
#         ifndef BOOST_FT_CC_THISCALL
#         define BOOST_FT_CC_THISCALL non_variadic|member|callable_builtin
#         endif
#       endif
#     endif
#   endif

#elif defined(__GNUC__) && !defined(BOOST_INTEL_LINUX)

#   if __GNUC__ < 3
#     error "unsupported compiler version"
#   endif

#   ifdef BOOST_FT_AUTODETECT_CALLING_CONVENTIONS

#     if defined(__i386__)
#       // see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=20439
#       // see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=29328
#       if BOOST_WORKAROUND(__GNUC__,BOOST_TESTED_AT(4))
#         ifndef BOOST_FT_CC_IMPLICIT 
#         define BOOST_FT_CC_IMPLICIT member|callable_builtin
#         endif
#         define BOOST_FT_COMMON_X86_CCs non_member|callable_builtin
#       else
#         define BOOST_FT_COMMON_X86_CCs callable_builtin
#       endif
#     else
#       ifndef BOOST_FT_CC_IMPLICIT
#       define BOOST_FT_CC_IMPLICIT callable_builtin
#       endif
#     endif
#   endif

#   if (defined(BOOST_FT_CC_CDECL) || defined(BOOST_FT_COMMON_X86_CCs)) \
        && !defined(__cdecl)
#     define __cdecl __attribute__((__cdecl__))
#   endif
#   if (defined(BOOST_FT_CC_STDCALL) || defined(BOOST_FT_COMMON_X86_CCs)) \
        && !defined(__stdcall)
#     define __stdcall __attribute__((__stdcall__))
#   endif
#   if (defined(BOOST_FT_CC_FASTCALL) || defined(BOOST_FT_COMMON_X86_CCs)) \
        && !defined(__fastcall)
#     define __fastcall __attribute__((__fastcall__))
#   endif

#elif defined(__BORLANDC__)

#   if __BORLANDC__ < 0x550
#     error "unsupported compiler version"
#   elif __BORLANDC__ > 0x565
#     pragma message("WARNING: library untested with this compiler version")
#   endif

#   ifdef BOOST_FT_AUTODETECT_CALLING_CONVENTIONS
#     define BOOST_FT_COMMON_X86_CCs callable_builtin
#   endif

    // syntactic specialities of cc specifier
#   define BOOST_FT_SYNTAX(result,lparen,cc_spec,type_mod,name,rparen) \
                        result() cc_spec() lparen() type_mod() name() rparen()
#else
    // only enable default calling convention
#   define BOOST_FT_CC_IMPLICIT callable_builtin
#endif


#endif


/* compiler.hpp
7bp5Wv6suAJNHZq78ahCYVM+uvM9jXWWjbIViX5FGT21JvVk0GRXrrPmCVi251UIkw2jdR5ooDSAfpkI9bp+AYfywkgO1r/MXUcgqEtr16UX26D5vKQDPHQ+GnhR7B44UYYOJuNIe25IDsee4XMq9RtteQH6EiEUf4DSRECUZFIoiS/NrCdP+RXdMqFH7QlgCKV5WcBIPqoRaZU0lCif4RX8idTs5DVcOXg+Yj6eWnBMnVFvkw/ntSFkXD2Djh/3vzKzK06Y26bMG3cEdN4CjpgDVMklW1kxVNWbMOVMmwHtHBZvjtRcbtu1XT0BV9UZ0xJoM8pXfJbZVIGC5eMOtNUmN/OklXxZkTHwWVycm9+z7LfPzIJp8GxYKIJEIZtCp3Ml3Vne2585BFAKcpt0bJIYMcySWYX89GZtMiJcGdd4rQCUEDbz+1ZhjkEmyx2BQkRVHQz+XGJvCKaD0dMIICvmh9Epx/LOM/reZ2ZD5Ed0qG+vYUuHGBl1syX5yxgoit4Rd/ChXdXBgnM/aEzPayPbArFgqWwgOPE85y1Iz7/6DXCb6JS0BLzljRnn3rBuNQclX/LOPWlU0PFJYX5WGC4qWQnTiJ5LKpYJjCo5FR9Vk28fXnDqUI0mZEOP93Vq5LVKvcksHq+MF1FkeSsolzfkD6GyiHFLut039X0zqxsqGJX/l0kCOfPfJZFE5unrscNbpoUnbwJMiDdKwGbeOWTepu2AT4KjUFd1YFx7BCsXlVmqFXVSNqurOut77og8jS3UHsKt5kLz3tPDE+5f7HyEsoa1I/+3XFrwZGZ4UxjzQqnpUh6owBV3hPMCFcQbiYllvxmYlMwA1d4xGWMySvDwS/h3zjU0D/hXa2d8hHAw5IsqzvqRiRCNwn/otw8psKeaLL4x2cVeAhMRnyA8Yk9HfYJmn0g1aj8LUYW3TjN8I1g61MZEtabJte7rRVRXjiQx7XXSEx5rsdYkdUalX6ELc5FtxhCWDmjDBkpA0vub8FwlStbwIX1sogMABSs1ARa00gYa2/zqtv0sARNrC80jDuYtxBnE7OkUZPSV4K+3YAH7SFCKGTy48ty95MDDvd+lRWK0fXJN/yj77MAKUI0R91d0mad3iLt4TBmARHN0l2zX8YhW9BaFBm/+3c7i9MRys2BE8k8Xgq2VueXfeJa/AO1THQlVFLOm203IuhYWKltD0OcnFvbPYZz7DZCXf95uoKCgGWfxQeqIxbKLNbyOtyKFx2coSpi/FEE471xGSwMqnLcrGMp5l4UR9WcGgUcuVVNv175Fvuht/ttkmP6nfYveNQmb+8AUmqh77E1T8pvEFFntwL1Ea0kCFlwAFhQ9UAf+VJLQNQYrOufOb0F1KYRKqHRglxcJWvAm48hripOSJ5maKaiDZr/tqXpGNFD4nMWTJvU4832eXvwzSHzWD3wqls9IEsnM5LVU85weO8zzRKsAVHM4mIO8s9OHVJrZL1YXhBf9pKLZS69z4DYb0fEvllDPEGzXVBekpacxbq89znvdbonqbdctsbaYJIg6VAhK+26ACoRrprVKHPC+724Yyu2WlM++ewprJC2EE81lG0vrB+Ta0i5VuDCG5gGz9o5uQKQrwGBcMqeAbTANn5KdMPQClwvkZt6xYEnqU9VzvV3M/fcMmGuP3Xy0WoAYO5nfaDoHAy8Yc/9KcPytAAVPdhMvlCU95i3ABwkdXNJjQeNMrcA3Id18ZPJBJaDopfx2rT/5hiWJVSorBm/ZPuMXkl6q11w8/xWjEw0uH8ZSp7Ws8IgfF7pnV0qUUTy2wa8m25YhTtrk9GpClWKIapBiCL1lGoN9fgNajtPaZFJBY2DafsSUGwX5STQuY8xER0PkpdpNbJLB9LDlGild9xKubwi+S27hRcjLi36gaZk1Qpe+7yq1SgPwKNlAnX8E7jZB00SFqQPnkDbidDLJXderj9eQCekALQXw6kEJrU6q4cyiFTOjtHbtIlYjhVm6r7ZL0JMHy5/ColsazdMWCEU9HeBfhBXLZ7XfsZ4sHchFCvajzAz7HW8azuA1F8SCsYZ87MMMbLuSePw1GdRkNEDBPL9En45Bg/CcK2OEtL9L+194L7CwneU6WnpL5MhHWeUaKQJRGUlLSvAnU3rKu4gsPs8nDYUR6YmabI+i2BcN90GWKSayd2Gb9+7M86gfe9klSn0S+Fe+UJVnnStgUJws/tL4L3++8HFoFF7YuNxyKK3aEMKYqAbAr3O9iVLlSzYzdFytio3Yf88eTlMtJyzOpdiRUXkqJFTjc+BIVUnJG94yyAN82R+3ibVdyx8HRn6xPYqT3XadjxQ7DTwSQl0pUkHNfPKpJSFz1FoIU2D83uyMSWoTK2Vx+FajW3iVfayG8ZudTW4dwgXm9ZPYGy9wpnfg5GfgxONV2zOy6HvP1B0ud2WP+SDl8E3yTCludvmh17Vn/mdbQOZMKNeaph5zdxs+918GyVNNyU/uJxGhHucjvE4/ghapmFyIhsgQZuUbiQlFJJn/wHEUvD+IYiX9TVt4+bvTwLIvphWlgmvXFNhdW3Lc+0jZlVuIGTKuOYt5tJxxPtJyARXXdl23SRsGgq6Kj8cHgTkLBsnGngFtGl5oOt7pZEBmBZ9/aVF+afiOvHVxIoC8iOgdiFOYIIo9laxT2QtG/oA4XiVlb0kJC7ODbsr3u7uUQZsReKVbkuRlQ8xRFVngNv0/Ec+fN8siU97aOSoReCu1+vJbnbGcmbjqv5/fS5gNSyNLEoPjR+3mf9qhaz7ERtzdGcaElm0NCOHLff3DBY1d0gJAEAhGoV9XEfRHgMdu72t1M0VBsEWahfMCb+MAsjBY/QmERcZUXPK+ytuaaRhNSRYsSPzaMkUbHBAfTQNDgy/joxReX2+3MMVSLzu4OCLSWSJKb0QTCGislpXvc8LPEG66LyMPF6bcflzemq6vYXBUt3hkeV32+gkLPSRfemf77UAlX4yU7am32hKnCWKl2Ul9gSOlh39Y9GveU5wwGlQj288zi7zrU8mSAQsLs1jL8r9VBOIM6d9Qi80Xk5SYZkuckIVxuT8MktYCibNXsdz0v+ephsDG2hJ1CwuhXeMzWCb53jqbuLFhHkzYE2OQjAu5wWgnHfh4TTd7VDDVfxuTbPNMnp5gCTNwenJlwtikDSkNK2LKJpAUYbEWuvk852x+V85sYfWymM1669sN97HyUZy4GC2zA5jg92O8rLKkaoFMST/quZ8dov7JotX4UCwNL+pW5xsx64JE244I1iTDD4wn3D3+DqkU7R+IgMDilxJ7fWNuzMyZxOXelgPGKIuvix7Gd7UXnSI/WnCNTRWOlUJWPeWfCtxSPx7n1NneGpEvbGNF+N4fXmwy2YB7kRAUY/mwJVa39Ak1ZMrDkoLVrOXBkUOzv21IsjJjSm4Z7QnjkP3NiPtWJTH9rLTfn/qZQ77s88mL9a8uHwt7HqAGvhvZQ/q5AyVDIvmIP+PU8qPTLfKf6xZWxkDYBgAALP/TN/epNyIn9t41vutI5Uw+QaAj2XgG+JwBDQOCBNfFrX9vH7l8ByvPILtEHl8gliPNeORUQj04upgnY321ZHvXFv2yksINZIWNFBVPcr2xyYX/yTTYniDI6BhU7UlnkrKtXJ9s+EER5PRFn5PkkakaWeRbMiIartmT9dHdovtaILdPmd/3Jqzlj3axRcb+5OIjnOlT7TUXiJf4WuMLAyrWJjRhVlVMIdFsjK6YuDqyNhqB5/LaFgoPwZ+xj+344Xg5sBd3BMg4d6Q/yUcIUBYD5uYWgPt7U5SZAIL+ue1qFTnhT0wRBxj2jrdJkxmPcJi/9AHEYLh0ohbZJb+eMYbGrfvA+gK8HnmNTVVZ753CwfXDs/3HNwJWzjjjzc16jJ0XRqbQNKkj1brEcmh0dXOlC06XO3aVVF7sVqZI0vlDcZ0j1AfBj220QUky2cfAGNDZ+MygFTr+aFUK8pl3t2cu5dOPoEbRX8lAN11g8FYNlr4w6xTaK0NbhzOS+/NkACnrxREWmZbN51nJBulTjzzweR/NVq7i1w4CqQepWAVSwlf9E3r4zSpweW+ajZB7xqYW1VgMCQrfaCNgpDUOXVT1JaxOdKpO1jqX/x4ssE+bBr4NtBUym7z6M3RVxNYpWTcuaYdYu5lK9n2MyCKNAHqQMukbgusdQ3hl/U9fnC8gkmAHesdajtlUGVG9/C63vrZeKWNbvu7F1OxkzSOexqSUOEerpba1rHW64HIT/Geg/uzBcEGvzihoJ325eW0xz0Icv070pbp73rpIsDCwu7ib19zZ3mMFM1MkE+K8lnc36rrzpG41O6SuRmdNwyz6pB9bVd3rwnr2x/Grifae7gm4wuxTsXjGbHTU0U5neRdRbJvanjgTqk2P28pV8Qoh+4/nhWNSduDENOAqdbO3zy7M5/YDvxpvhaTOW3a6mOo5/vSc3EkBV1C2QekqodBDx+1rgBfZbFqQhu90XANzZsvReButFbJ0Z4r7Mlfxw2QXbWQXafznUdVyB45x7oW/2GgtHfbpl1flvFtqd+uyqNtdyKZWJutrDrEdPPdYiaB1cPM5q7t2x7Pvhvmd7ilMfSrsKvZpd0crWh173uVhPcdOijXwOyO1d7R6JVgAykRyDkOfg+NYBe3KRrcUiY3DJLlat0NsL3pevm+aNiK98juasrqnFFVSjwgqwEwWFHY+HLWBAQLaJaqz7NJuRvll9D5wi8HvHf6vUG93D8ZwrgY6Xy8nhaHJ14X8GuShNJIvG6cfHHD27kngukLgQGEUkN7U0sOTCmkRAdt20c/T3DYD+F8QasRjXDzd+2G7HD/8y4WOrxItnMgzWjWPU9wbH9XMs5ZvUTT6he4kCLyp6aTXIaEp27UUPhfVYR2IFKtl8qBc8QV6uRWciJXvtN0rQsAXuwpi24C/K7Nr17Rvf7cZUtsx1POE1h7hwCzkI3HYfLAWSsbvMCX1Plioo6a5ZM60mKa2ucwyhq13eKM5MYJD/5WM3xJA2/NGl3hA9LpGLt7TcUpkRGdxrrl8K+5xaEl7fCcSabgnzUE9uBcUk9Gq77f/k1FHpGbj9EuV0IzxkFTsgoI6hMl2rUe7je1cXp/VbUrbMn70porhZSpN3kdhTFQw/vFIqkYdmAKzAhnPJN22SlwMvY5bzO2/KfITz72yqPf+3pX2q6ufgvJi4HoEOlqg15RN35mtJ05Y2PSDQ/+aEsqn6lme+CMprOMu/TzCZlGd6ThskItKyzKJjD8CCRvs8e2IiD93Cu2En6LmuaVzQjnzCcKSbcn2dXBVQIlHhDhY8t1WzDgJ32fziAAObPBNlFQZQqRXGAjkT6wBEGTFUruAFpvDMkuHJSYGvx/w1WLEROU36j3mnUHp0gWplPpl0APnacGoBGKH5/bNlo1T/lcc1ZBvNNE30u9bD1larfPqpNbQoZHZZ5u//+o4ANY/B80gxRmmvp1g86vFPXwFOWbLTYBkEZtkLR3zidfXNh3j3DjhNeH3+vubKT4JsbJxQlVykG6TafQD9ZSRwX1yb6MBAGPMaXG5wqQ3zChiJq+QgxEG3QiDrU3oW98/VY8hNnSRXp3iqxeiSHpDvmra8HGfwN9b7yDckxoSQhDMfSCcqe/TpOymbg8Na7xSGJZQANrltgxJbm1pbkewdCW8sVeAclULxryWE0zZISoaLRfdSFbGJowrtbiU7cA7bsa20Fi9eQ5/X09PdOEyxqPEORtXSJnwe93GokCQ3ZxcHLzTFnlfppB+6Ad1QsWLKLUOEWC22Foz/KNz7MMc7+/fP+x9XXjEN2Lgosa1YyADp181EaDQwA8y6K7ZUWyu3Nh4GDBcJbmtBXkF1p6AxLLCgtYnMpCIqTWPS5oM0Ofpi4xnnFirhlqzrNW50+3kHyKae7a75S/qXoNsPq3JPlV6cWqtaj5g5h+XlTcKKFQ5Q5w6vXGdzxclYdiVyT53tbvZ1BvG9+mjmkcErVui97bxZ0Mw97F2xdhK+iL6tnFi81ljKIIGfOy7CndiLdAMACI/pn8VPZWN/co0WCKJ7aSXgA6gjztFcNhH7GfoDJeoInzsMkBA55lv1VlpBbhCkj4cUq8k9WN2LcXU9m1edawWXsYmR94tIJ9KU+X5aPMryYtS5O88vkda9ck8Hv84Z2gKEbaM4NoeXp0MW2XzjyaBdC5y5xr2eF0d2q8BfDDvoDbuUVJTjSnf4ax2fH6Cr+5Ys0OjBeD8My3v4m973GLUMPBgzB1ejZHvs9LHvDwpfDDABIkUNY3HIUMbhL3tit95pXWwtHSimiURVx//ltIajD5zuGuUEjHs9hiwX0AY38feyteHINWm33EFAxVwelqS5nd4BdnpRVHKCdGSfhuROwnHQSLBUC0AJ+VUHJm61Pm6AeTAR89H2xbHraQnSuXC3iv1DL5xUA4S6KG5+DoMidEOsOQniHpHVRTghYEGI6dSPASI66d7NFCx7Z9OPnWUVKQR9Po2lFtZa2SoWdKYOZhJAZOy7kFNW/R7hhtf3kYeXAvfdSS2BmVgwHRJ2UC3ivvahBqcCz0k6HECMMvv8z4pmXQbaUGZp2qXPoMkPSAmQsQp3VYgEbmPk4yFojJhFamahn3UKMttzewY4vSXRcUCrXStpiXYieLDeQTFEvpM5otVIVLkFKb/ghv4a8XjUmZyzv+AGjjbe/tRg04/ptcNJHdkmVm33//iEM0zK6nphwAKc8hIxFvXQoEBLB//dQvfunq7qXgXQ1kGzEsu/2NST8aIr/cEGlDpA/5QiZrmp6DBcJkpc/OUaxEDeVdX4ldb6yS13lk1jbxV+hVyZboke+zkVv2wK1zXv6TxpQwQMIPuH92039TXmDHA/BRl1tLwJvLuqTLfgkx46y29P86cnw0T5HgJzyCGvlK6WSYHm7UolpmU45kA0DqGeB+WtUDCOkR+lH6uqCsV0sJCWm4B2jafsNhEB2gIIfhUgoZoR3fekpxWf/hJLY+sTEZeIT0epZ7WFkOEKBsAhUbNfyV5xVcP1VQpc5Mu0Pe5dSKzJRlekB+euwOqAnqaB7UdWaEfdOR2JemK/OYVtSpyiXZxoe9Zg3M20GMPN//1kHOygLXBvFiY+OMVCtu6UTkXlKodhimDZsKiAS7ztysvXfAl4ftYny4GP8kcWaFZdjmvoW5wtIERCW7xkfglv+CKiXroWCK2Kn5RyN9qPOE9kQYT/WeB7xQqfAzxomDpj+cajxpw+pi1KiEnXiVuW5X2PvQCxvPAhMDMFmogpuWfWWimWMfNSSMnPgtZqoVcTqbywS5YQVUGk1bOOeMEcOwY6eMjDsp7BurQDZJv/t4/XAoxZERudwO+De4Z6UkpY1ktCfYw8BCM1zSHN2ykqLfF8U1AMaNm8iy7jZ3zPDrjfo3M8Xm7ua+p/HURFNHWYfg+W2SX1XdVqbMUqIeRGWM4z2WDTVVssSrdoxvwjPokFrv+1V4PL5NlbcpRai6JYXfrJM/OaibRalp8dH1Sq4h20CEbWZiuQ+9kBmKP9QikVWCvtXqjtPi7wwwxClKcUQdYIOs5xgCpI6YbPu9j6Qxj0sh8yDR9m/68+BcG0+Tp3tRhNNW8vDcpSd1DTS9kpe6GrhO6gsvaTjEP2BtFMMgH37zu1GJD+Cs9KIfztEEL7auuck5SlWsRM2fYViZZKCGUbwtWx0mz7RXmnKtpLKwZmaEbp7fv82xi38tTKIoDbESgZaREjduRYiB7HK2vveOI4QDwRgTBgOsowZT6xn7zno1oKz/TUU8/UkBVemnUekxTyQpc65n/dm2mjFVlFURXQk9dxe7uNOhzJoAMpTGee20dBMLl5mvIr8cUiTU6c9TjiwcSHTnZF++yJE+qlRuGC0cSfigML0xaXrMoONK0UPxv+nOqzgMrvgNA7UR8h0MMNKi28AHNhgWdy3GHEm6Au6vbtrm1JsAaZzvUhxQDxVXKnPHr5yfspQyD23LU04Nf7/9QSLHlmE10OOOxsRBInK+Bz2IppeSJFyTDowVwhsYrcEjuGHnle2gbeIG1C515gdQ+/hFF6DB8GP6hOpt6WVX1Dm0gRseV0QmM9QY+tZui//7zsoh4GBuILy3veqnqejk+AG5d+wZh65YtYQ2yx3TB8SkwsRMcTz78sZZwjXRACJm2kinWGYcpOQJ8is8IhVBgJh32HAhV/Mgjg4DrVheaGyRobQBFlmZnMir819wNq6AwHQH2yyUMhKUWE34cJPzOP4ohyFhwPgFcCtQ8nQAWMSFH8m+QuCRw01N5L6CEkF4USZ+sBxTLKAYJBwT/qN7gvNxPa30RsLgjFF5pOBX5fRaiCr7qk3A+Imep9Tvh2Lf8CukFtcCcWkH2CfL+bhl4N6qgIVMVwZpzd5SUtTgCh6MtwT35nfCiFzbjdIclvKRlvHfSvoEak9Voi3bAv8sxrxE0Y/60XaIG5bkJONK4I/tS8ZqQRay8OrO0qYbE+mcbuBT59x4ugBkZGnRKH/hdE+v+Ie6sfyTTWb2fho74kcwwWJl9z70Ok2zqrreL5NZ2KxbC2Q1vjOounXXulgiBJu+UGaSVeljiJHg8LuskTUjce661cwwVjzZ4Q+wvwxCSK/Thh+h/7r+P17ow1O167gJsXtTr6N4q9RH/sLjkQBXuZYWz8C9fRxJdRI5/2wku+wHj5sh26DD99+mITR94b+Wl5NtPDwky47HMXYjGP9QKYsGyt4NwF0jkSf7xf6MzguL0BW4/nIlFLLcYkAWASbowxw5MEVZWK6QqP5auCqT45p6F+GkwwcRfjQiL/k5QhVXLYqCWoUrwm85wvHSz25Elxpm7vLReyTHddH9s87x8dp7keF1z7E+wjkgR/BvOYnfSDvevEEeqYPMWKmt4hEaBDBXkBbSK9RfXbgqjzpkNMkhVeEeyXRyAncGTs5qsqCPjkwvGfsB2EETUe+o2NNSK77Q6vAu2PngoZ/cpCLfR3vmo6WOz9e+cgFV9iygXraGZLAofETSYaZbr52YNUDNynEDrcVUgoW4DJ8MNqm6+EJAWA0pV8PVQbf8cF+nQ9ozX852mn3LQ9tD3lUprrejDi8X6apxlFw64gnacKMQu/wMaoi6ngFS1pgA4qSLci3bS2gWachrhSAqoAyYKsDudUV3BLamqSioqqsVwVpLwSN/euxb+HZI=
*/