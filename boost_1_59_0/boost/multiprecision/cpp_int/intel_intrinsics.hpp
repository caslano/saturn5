///////////////////////////////////////////////////////////////
//  Copyright 2020 Madhur Chauhan.
//  Copyright 2020 John Maddock. 
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_INTEL_INTRINSICS_HPP
#define BOOST_MP_INTEL_INTRINSICS_HPP
//
// Select which actual implementation header to use:
//
#ifdef __has_include
#if __has_include(<immintrin.h>)
#define BOOST_MP_HAS_IMMINTRIN_H
#endif
#endif
//
// If this is GCC/clang, then check that the actual intrinsic exists:
//
#if defined(__has_builtin) && defined(__GNUC__)
#if !__has_builtin(__builtin_ia32_addcarryx_u64) && defined(BOOST_MP_HAS_IMMINTRIN_H) \
   && !(defined(BOOST_GCC) && (__GNUC__ >= 9) \
      && (defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)\
          || defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_AMD64) \
          || defined(_M_X64) || defined(__amd64__) || defined(_M_X64)))
#undef BOOST_MP_HAS_IMMINTRIN_H
#endif
#elif defined(BOOST_MP_HAS_IMMINTRIN_H) && defined(__GNUC__) && !(defined(BOOST_GCC) && (__GNUC__ >= 9))
#undef BOOST_MP_HAS_IMMINTRIN_H
#endif

#if defined(__clang_major__) && (__clang_major__ < 9)
// We appear to crash the compiler if we try to use these intrinsics?
#undef BOOST_MP_HAS_IMMINTRIN_H
#endif

#if defined(BOOST_MSVC) && !defined(_M_IX86) && !defined(_M_X64) && !defined(_M_AMD64)
//
// When targeting platforms such as ARM, msvc still has the Intel headers in it's include path
// even though they're not usable.  See https://github.com/boostorg/multiprecision/issues/321
//
#undef BOOST_MP_HAS_IMMINTRIN_H
#endif

#if defined(__APPLE_CC__) && defined(__clang_major__) && (__clang_major__ < 11) && defined(BOOST_MP_HAS_IMMINTRIN_H)
// Apple clang has it's own version numbers.
#undef BOOST_MP_HAS_IMMINTRIN_H
#endif


//
// If the compiler supports the intrinsics used by GCC internally
// inside <immintrin.h> then we'll use them directly.
// This is a bit of defensive programming, mostly for a modern clang
// sitting on top of an older GCC header install.
//
#if defined(__has_builtin) && !defined(BOOST_INTEL)

# if __has_builtin(__builtin_ia32_addcarryx_u64)
#  define BOOST_MP_ADDC __builtin_ia32_addcarryx_u
# endif

# if __has_builtin(__builtin_ia32_subborrow_u64)
#  define BOOST_MP_SUBB __builtin_ia32_subborrow_u
# elif __has_builtin(__builtin_ia32_sbb_u64)
#  define BOOST_MP_SUBB __builtin_ia32_sbb_u
# endif

#endif

#ifndef BOOST_MP_ADDC
#define BOOST_MP_ADDC _addcarry_u
#endif
#ifndef BOOST_MP_SUBB
#define BOOST_MP_SUBB _subborrow_u
#endif

#ifdef BOOST_MP_HAS_IMMINTRIN_H

#ifdef BOOST_MSVC
//
// This is a subset of the full <immintrin.h> :
//
#include <intrin.h>
#else
#include <immintrin.h>
#endif

#if defined(BOOST_HAS_INT128)

namespace boost { namespace multiprecision { namespace detail {

BOOST_MP_FORCEINLINE unsigned char addcarry_limb(unsigned char carry, limb_type a, limb_type b, limb_type* p_result)
{
#ifdef BOOST_INTEL
   using cast_type = unsigned __int64;
#else
   using cast_type = unsigned long long;
#endif
   return BOOST_JOIN(BOOST_MP_ADDC, 64)(carry, a, b, reinterpret_cast<cast_type*>(p_result));
}

BOOST_MP_FORCEINLINE unsigned char subborrow_limb(unsigned char carry, limb_type a, limb_type b, limb_type* p_result)
{
#ifdef BOOST_INTEL
   using cast_type = unsigned __int64;
#else
   using cast_type = unsigned long long;
#endif
   return BOOST_JOIN(BOOST_MP_SUBB, 64)(carry, a, b, reinterpret_cast<cast_type*>(p_result));
}

}}} // namespace boost::multiprecision::detail

#else

namespace boost { namespace multiprecision { namespace detail {

BOOST_MP_FORCEINLINE unsigned char addcarry_limb(unsigned char carry, limb_type a, limb_type b, limb_type* p_result)
{
   return BOOST_JOIN(BOOST_MP_ADDC, 32)(carry, a, b, reinterpret_cast<unsigned int*>(p_result));
}

BOOST_MP_FORCEINLINE unsigned char subborrow_limb(unsigned char carry, limb_type a, limb_type b, limb_type* p_result)
{
   return BOOST_JOIN(BOOST_MP_SUBB, 32)(carry, a, b, reinterpret_cast<unsigned int*>(p_result));
}

}}} // namespace boost::multiprecision::detail

#endif

#endif

#endif

/* intel_intrinsics.hpp
9WBHlodbgGXjGf7WpvTzNfbojc9KekFx3Pdyhkt9un6tEpD5FXEf6dX/9n3R1Jf4rn8mMfjOPo+xmQjPUsd98K2CrGGFFpLZ9IW+HnmUPfrGVKGP1PP00xwiyGsEJReIxd74PlGlPvP+2F2mePsTyRMM8NyAbah3P+crL4mVBYTA35cMM34lLt7ax27j0duOVfpV29XBPlEOCO1nCD0Iefb61FuHLSn5JlbnnX+dfLrf4ltMaoU6DFLhxnBztQI04NXeVAr1CDn4ZR188ZAjWszGxUv8Jl4i+bxtb8ngAEdT9VTxapWkgplZJSSEmpdcCO4C7HKwiO8GMLzKtguBRZEc4zztaj4sHmQ4ueTtQvsnZD2NjckQam6ZKB9T8Jllxicyx+h/WwwXgssxqJoHMah3Aw9VTcipocv/xvEr0xfLYlekLx5NnM9NF26GOTRCsDdTFPjk+CqYgYV8GgwIyB1ADAmmkJKHVHG3WbzaBZS4A/FdBrZIfwOpFutwNhkXdVdQCSlirTqoBbTqTa4nH1FugrlDFgV7xYZEPRvWozkKGUDMcaE9kAIyCdbOZsxmWSOFayStBlPrNUoNwcMiBsT/t5OYc8pXji4Pm6Z0bP/oc2DD2vUpzTaK9YhgXsprK7Tvhl7GAd4FGg6gqU5Juw6Ii9tILt43F5wHdwNAjZ6gUG/RHa06AacsAvbNr2P4vGhJguBmBHoi+S0UDTujyGULkJFRYLY0q0Lythcb/3LzeSIhQ3wPlPp+EYMZDwUHRJRzBy1dzlFlVQfmkX7PN5fkmC9k2x/picwmLpGG59df/awHKgBqPFkesZJtAr2p3YMxGf6qKhJ8qAQgcp5yPQ0P22YJN0r12qDRe1Xor+At6XaqcOj+HamuSMmd2HkjDApxjtY3uMO4ZVxzTruPZQmB5qRMzal+yZD361Pk/XEj7ouoH1WHhtB2KIa2uKm3F437Rwn7KdNld6EcpvySreXE7whvBy0pTnEhKaGBWnuouRWdh+FvHBXqaqCdhAbLel7uVa5S63gQaqAK1vORxR0YquMq+iBblDnq7Mgs8MLxqVIAm6dOAP8azQPy2W8s9lCuhV0vr8LCPlINM8LB+e6VtwjKTDKKEc7+J38dzj6wAVi5/koHm41sPRsAMW6GtuGVm8fOeHl5JQ/KaQ1aYCMPsfCE8krUV2sEfLUb+W8mmmf3kRkIUskDM6LrNgdu3FXy1CKBv+7hI9+Xi42eBDP3BITGbMRydvqeZENPwJyDPmSBOTcTzLk16Gk3OkCDQFtIDnvnFzA6GGC7koeuUGaaOPgS3c/T9bcNyIUqmQFdYGjvYnJC/9P3BehkMAjp99mgsWeaFfb/6iZBlqG4k/jpmaWPTR0/QaHXFf02FuRLaSpr5n0rQJ03C4GluhoXpqfGwfHRY5o0i2qzkM7UAVLLb9hDD+hXUqKBHHJGbRqNZIOtQIbC+Zusw9ZhENvvQ4sNmDbYxWv9lzdAm8FXJXARQrGAE9oIi5vC/B7VqencD8bfEhZGpEoYYNE92a2OeEwRi47CKmhEPtP+Mkz+ESoua0X5gv3BXtohQR7wbyHHi46ExWrroHWwLsxXhMUfNdRpK6EP5O0ij4AdQV8ldNK+dyfUj9+vwe1iax9W4HezjllZx2xuLXBzPOgIbYR24k/tR0dughbse2+An0UDYE2CKNxbiI3m70I66NTXUqmPlmCtUFF0HEYBBkfubX9z5GPjko9SCH15JPhBjvVwb9QajPL+nG4kRUQsx6Tygexu/BXOt8CYZ0M/gPT+c+SM/I7BAcmDAIDCjmrE7aT1ZH1dgxsztO7NYwbWQFFv2FFBv4T5ajCOw47dbVy95rgE1BooclFqFahNWqgnsBxJ1DgKJBIr6NidBbSy4yTaJCdIhDWBRJo81H6URadABoPK4CuhUPXwqktE/y5zgIxEvrJQbKeOGAjnUM8Oq+qSQjFlZVmA912PNut8ms/DBTzVrTM3cvYnCcAmzu5pQcgugUVOreUbQoPKbUB21S/I0V1WGAzSJKRhYevFDdCMVDIM/Hs1hYc8/J+hQZ+NhRxZBTwZgXHdBGghDAagWZQv2R98Ks6b9cA9r+vk3o356J69AIQ+XlQLukaExgftezEXIdr71Hi0vhEW9yWA0JKr5Hfa/0zBUBj2vbMo90FtYL4srO34HdXsjUJkhsHdGCTEGg+X4xKCToFfVTQAA/RhoimgQ6hneuxn7ZOjwH1OEblPJANyX4L7MOsPl+A+oBSdivXIeoI2dz6bbI0CzlN9kv4IafHzaJwWBUiLwBIkglPISARouV5nLXp1GFnLxau1YgKlFPs5GJAwFr4rr00Ea8IB/FFBnZE8mCLV4Vv3RXfMMyjmkVQJOC2oidU7P2OUMdgQO6/Wog2ngn4RYvpop7EHBt+Yzv2uC6bzQ/RMEMjzv/p+gNrcBrpIrUUNpnqEzWqzw4jK4hTQHKoLDlzl1bagK/eqmG61PCG3G88lLvmVDDc0aONjGzgQWRj2JoxHjzDQD3jsmYL8HIfiE/AbL3hs0vj7ipiIX4PZD8BnoKH1jXA8wQHeSw0f/UWaXRYWzvBY8IeFPD/y4ZlYjMHHZ3HE9a75WRh56+i3ucQzP/L0e8b33SPuYo4baXTrL9h323vm+o6R5b83P/MjL55Ofn7rw2R4H/4l0f4GbP+L9ab2hZGnU/q37YPkZ8/pZPhjf060txHb+29ze+KI593k/lzzbnL9+a8kP19Tllx+7KNk+P2DZnqJI/3DyeWfTnl++N1E/+7A/mUn4/twCj4vlqbgO5xCj78kl+8/kwzvgdPJ4708ZTxsHyV/H/tTCr5nk+FNqD+cDH9zCvxtKfDHUvr/1vsp/T+U/PzWy8nlH473Tz/v1ii463f3nr2O47Q9W77LciFQWUJ23wj07UveT3LQvSQQhZXU+5HYXlLopO+aYCkYz8EdPKfMMXaUZug7Sr4Z3ZKF70CzlW4jkarC+tgJZsWmxIsW43tgvlwa15Sl3aAL4CkZOPT5/9zU96vpKUFjO41POSvYsSOP8+W6+yvyuCs5LWjAf/KN6a2H82w9fAK0zEvirP3fP/f45PHdLBS5ZCg6clcEjp5vbPCQG0jz58FPJNxonIU7D5IX1+0F8GvntGVhPjSWTidbu4MpAXnIn0X6wrdyWe6wR6oPr5fcdSrq+ZsXIPkktYUPu0Sg/qi9V6gODe6aCe3i5qoH486BIrvc0qzOTJOAshUPuGrzfzdu4tdGAY9f2kjVaFCTytyCf17oZGC2l5S1ZdW7wbONvd4CWjKbrq/SUHrJ8Q0Qn8/RppPfDmSRi8Edly2BXK+WBaVpfHFSEQUT6VoPGd09DthVBITd/RwncZEczIcXtY7K5wHZ8x5tC9RobpmwPoX0w+4BWhsBzoWiKMywEzHQaaGenTNbvYiQ85XxGJh8fElPJBejoW+gZBJ+Cy3uKjoC9oz8ml8vuhCKWoeMiiI8EdshnHBF7svQ1aK+3Nf9Ai7rLEWF1QgDJl8M37xzmxWtVqdo7XF73WGxro6NBbHBaMgbo/YH74Xi6sbPyXyM0L9Z5W9Pm4CFVBYk54HqO5YuflddO7iSP8W8Y2CKkJ/STGRqF30U1CoxNb7EIvN5X2+mCbvhfFz/BwP5EinHubh1Blht7tjbNE47jZbgyrcjIFdel0vw2Tz0U4rxkTpfI85pnDdOAb/1Kgo4brv0JAGePF6L9VdTwmPnKxhU+OPLQiRdLBVfG2fOMNtnimd9ykiVRFMJtsfeL+npSx1PFONLqRhfZIjxOcbBgBm6cuA5FMV82nj/nMfeeZwZXpgiFzOEN5AmR2hYyd1EdUczyn1cuvUOWGmkv06gMo2HvY23KnituwpEwwm1BDylTbQwWPCgcBqJjToYD/VBW4uJJC9QSnElxcsrxaAeZK+gfAeDT6wWlYLgBYvvBlyScTrqUcF5Qd0AiANQkwf/7RlS6wj2izALn23Z1J1ldCq5A6TR0bJJ/R6N4C9x3TgFm5NUlrEeDrSe1no4FQ1eUl61gI6CyDiZHbEBRwvDzOqvmKfYoh8bb06KL7i/YPL9Jnb+Jab6L2uvmZbYbeRbCFce8AFbvYFuygqMsTHgm6E/Bvh03rB5ynfsRF1S119p6JK0+7etU+hDvUMTGpt0a9jIf/cp2yIqaSDfQp8rFNvxfXC0/ZsAPbG7jiKCz2tx6PlDgNlq9qb9TSxyxZSHse+jaQksrT/huJ7YvCNzfslN2I8Jb5dg5LfM/SUu6WoeQM5DorF5DyFSA6YtF0afbc9NtR6uy6AhFiCELswGQAlTCMF+HsT9Z+OxmJdBKBnGWF7+c/CztCXPN9Pb1aJfeggeRyZg1zvosaY/aoegHrwzSIFRvRje6mIWcGWG/khjrUzKDDgeJWOeunjMyPnxmJGzEjEjm/tgJvSZ7UeYdL5qjze8E3d9SnpCMd+NRJHo/qL9pfmbwZAs3KzODvZmbQ6uuFaRKuSBe3MPXQt9YG8rgv1Z8sDWUyAbNquW5lR7yQNtwVh0U34SqU2CKabCjhkYeVo3SM4PLeqpgKp0PppWHm3myRYfr2DB5PFRcX+3USAWXFKxHmZR1fC9LwckIFmuFmMSSuUyqeTxq7HUDl9rJLwPgp9SrEvTfSp610Qgs0BquKHzbXwFWAwwQhiiTIhn3/EIbfxK8NNxp0//6vuAnaOrw8OSLqEet2quw3nnEuIZRYS0+3XFZv78Tob1ArXmFNC1ZFjus3feA82VNYn2zlZMv9SE4ZqR/mEfl6UqQ+x2Uskg6T+Ep+7Of2Df13v+ndwjdWxxBmVlFNjXuIK0iNS8nnwF6dKTNGDpOYxyreln91S/xnZJEoBOq01468k6KSTozVm9CQw1cywOCd903/UUg0SU0wTLnUZkMVC12nQa+HR5aNj3PeIccuOlKrdX+4MVc9XgRcEGrdeKyx8FYedZmqyA1JzSVoyjVlNmDDjfRzs2IlAEoKmSk2WN79sfO0w+w9DSDaT8LE1Xh59PG9LaqdGBFKBGurUUIUNk8XTj2Z2wd9INJg2ofhdpkgC7ZoxSHxc1mEJbwhOfTrHBHa7ltdN/A6mDuV9Q7px/b9HY7g8/i0V3xYMRS9rCmSCrHkB0021XURU6yT6WHg9t8STxerFP9BSq02F/iSZKbLO4gdxCvbZiCZfhgKyhsokFOAblHgtvdQy8pTKLL3sEHPRY4nwEzddlf6rXYu0B+yA7GI1tm9k6Pwvs758cHI/RBchtdpxONQKepKHiHZ1K2wSNny6I7sT7NrgkGL3Tn92tAQ8xyDBnrT1MHBldQG8hB7p/MPBbsAExfUh2yeBmVTAbGqQSLcZXA4bNR/O5ghPCzh3kkyaBWImdiL9Cr+NV2jWfRA8efNTSDDYozb7aAi1uit+HQ5Wb4Ai6TgeM8CSaxdGYMttbMsa4oUXvB9hWC2WX6J+Hi6437vYmf82sSk3jH3328cnyPdK9ph55VJmbxspXnQIwh64A3LhVN4R1RhPB2rXtOfAivYdAx8PB8m+i2qgz6Yxg1L19of3Frhf2Y2q18FP4a1l+MUzcZbgey3429e37BXx4EP7/B/z/L/jPWRP/LPG/skxvzX9P/Y+bcB4DTUq/GF5XapGP2PfuAZTk4/a9mP9AruXbS0EplAPqt+y619oDfCUf8X8M+iLB4ds3bUUG274BcxYcC9BEsFXAYXjOe8ctuNV22F9KjhYdkY/uKg47bkFzuh5aoGvmK93aAIg5ywqwKHDNXCo5CWrZURleaaH6pcWc/kof3yMHTcl+7oxnix0FVjUNM/ivTSIYQk37MAsvnnoIDds7JUxvyLwGNsZWzFjykPZrGF4UDZfLnI8qRnIKfS50ozgaGUbdtGLPVVzry1xXzTOqc7/qfKLL+XyX88Dmshx753bcxvtWO/i6Hf5nLPbQH6hofIJTqoittfDAfnSB1zFHHQhUAo52r/JdMDjdqs38o7WKpuR4SLVp//A3lP/2zkoLKpHnLWR+NzVj5Czlpg7/AU6x9TsPWCL/ApLkB3a2gwUvuEgBmQXtglhjzSwYZ81chLq02nIy3/5SVjB6v2KNOZ8IRv1KYazmCWVJh/95i3J1axfrgHbgMqt3mOqw50FSbQ6WLlP+FWxilf7p++e2ZW5NQ2JHESsg88/xYVZR74loMLrE/uAjVAaHnQfbCtza+hmo4f6vtq8Bb+K6Eh3Zsj2AQCLIoBQncRsl8Qayy0akgQpSUyxDtsgZydhim2Cyu6mr5227bCKteQ0mUFkJs5f56tcP+tG30CUhTUlLd2mbH+ffxtQyCSm2wwMnOMShpIxrt3ESYpvGWO+cc2dGI1v+ofvVIGnm/pxz7t+555x777kOxX8kwIAF9HxGOttmqv7VhCvyteV3RQrY/CBi8Cain/bZeSnUcqqKyJdQ2uLYBXt8N65yb2zAiWyf7IP/u2XfXnmWzsIr9gV5+zHfob7ChO8QTaLvw8MMIWt7Xxc85IDe1ncy0wlp/4DnTfWu7vXpF/5yfluOSmQ0+96NLfbnxWqQRm+pZHdgw4eqYRxVe09GrpGSp3lcdAC4Qwsk3cS6+MP4/VCxu4TIPWFHK+6LaOJMtSxc0ko95mX+fheekS6qEWCicsP4KYTfAvh1wS+qp7h3xIbjKhBMtsN4cdOmuIhYtTF5k9PxhKDLa+7x/DKADKAMtyO59JMcFSNQphsVXwGwMMTihF9HKKjxtBq8V281SlpfgGjFX6DTAJG2EM2kNQLOD4iY+QsBVg6rKJDnQp19ns2B19kQKUCkpj35R3ZcFGBEynNAg+S8tCBtvH87tf8r4+Ulg4M5hTAoLdFvxGbTA0jEjah9VR9cCq8viMWC8OI8lM/mojqbswQCew4egqdl8NQNT9Xy7BXwmMgphu8uCsgvoYC18H0KAw6uw3etawFvuQ6nP2b7FIEFQnSx6udKY6PWB/syCFYtUDXVzPkpklMtO6g5MulGXP+wwYwbH4zO2KSUzqbjEYY+AvOKyFWSvMoANkQy3+Hgm/JM/o35fbglC7RbNKIzuRnUfmg0OUbGmEpe6f4JyisWXV7ZT2aASeQV3p+iNtk/AgWYifTz8QPaNpYg5ElWJt8qVpaWKivW4E1+H+HyAVlwQxLLqsmDHq6X6d6q8RKpNlg+p5lAGmDSECV5DmmcEBH9cFPV2PEFNVZjVUDUZ5Yaa6rKzPcVD33dEe/k5c5rxHJDe/lF2eJp2pjRXkn1VWuup2eeSqun6OgE9QT5QegUlVXtseEv1rrszzW8fASlgT2H4UdZdXxji7Lq6Y0ttwPihqchaD98noDPT+CT+tOFAfqbeKLPor8M8tEOk/2ysejzgqBeeGe9YMyj/WnzKKpqStc56vTyKz34sNEm7z91jnYGyvF2ePAMys9egF9lT/97yWRQzQFO722171oCo1qJY4ykKBgVUG+FAUQzYHRmI7LhXhtuticE6qswPDUQWsjLIgd0EWZt+/MEKTY8z/49vM/WXv9t+I4Ni/Z6Pz3MtccPZiFChKBpdqCv7e+GXIMtMCOjXfmHi46y4Y6k/ArCkp9Vz9F+D6umpoUUBUNU56gR3HcLU9rO4e2TmqKHgY1lv0RFj0B7BhkBY3HM
*/