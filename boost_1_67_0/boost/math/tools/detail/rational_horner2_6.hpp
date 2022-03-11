//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_6_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_6_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_6.hpp
ddYHDf/0rYkmPIwnDoXhBz13iZ1s6PAQsTPnJ/Cb4FCfyqI6DB0esuN1kISW1wj5jtWQ+ERApVw2DOx0TZma8F452t4mevZTzvUK+ELIDqItEgbFALJvSJRvaBjXTJB+URY8tdoS+pqWCdCwvrAvc9+GyHdBXXMjja9A6LwxFrlzjdSHAxPNF5LKDPPUGfXjgw0MLPXlOCM5Tp95atSZtMSN/wnZJXMqMsguX3nOQf3c8bIg5WvLhwjBufmSYUbruplYtsLu2Bi8RaDOBRFX8LNnnjfhfXRtDmw5t5Bu+PECas1PNBcPZVwSClciCvVfFmN38lfrB1uWHRqgq68PXCw55X6yiv5sHYpON9Elk/Ri8nQ+PE84baCk07bsuhP9gj5aCUges6lwl0/v/P8d6CXjs5dzq/8FLNaQjvK62I70Ahw5+xUI5mblCJhJ0IonC7DBsBmE5qejI2ZNiqWlvIHSfuq+kDvcj5j6rfVDFVJvm58ZBw52ohHlkK0bcpkc1U51YUJnZXjIYD9VjlYvfrO9+cmxPvpHiEcrCyRKj+nsDJrrI2eZjqhzEslvln2C3k+TwtyiyahbyTAvoTSIUTaa/rxbzBjd9C+zi0CMnAeRQKVXbXr+TcnI4joNqcemCx8qt8ANeQN51KtdQy9ahNlmUJFRuPnIa90uT+7e5Rye3os2ftxTTFBvuOLqtHqG1nY9YU6wwwhwv36hcJXA6n6/Vqel626Bbo+bo3w1anzWboIFa808oG/H/8kCTeC477DNOCS5QQNvoQNVpnm0TBhobponuALj0dnrUVYl1mOIe0nBqc3d4Vc6aO8C1KIrB2t1zFyds239SvWS0qvDLR9kDwN+m7u5KpEmiPILFxxmiTsxG3kKA2nejrCfbMXtEvdyqLDuYRS0zgP49mrxcN2O0u/R4dj4oRTils0PAK6gRy5nT9c57gMBncrvcFKuEMcA9VbRtB0fkmZyIa0l9fwHmKKDApLUezh09T8BelzBOArOPzJlciS5r74IqAh1qlL95GVXhvzKB1YgjJ28g8wUv4wMlZ9pYag283UBRpDqXvYy5lQSpARMQER3Hkq2ik7GyACku5EotQk1ogkxe4gFvjOIpBMAlaISORifTYENVZWmYi7QF5HqGHjOyalBa1ThX7DRwzsKBCHziu0L0lHgO1k22wQvfNpm1zTlqweXp7FN1UTQDlHHlEVmuYaAIFDck3MrKFEgdfpBNEqfCrRgjKfto/mg3OuhPmrARn3Bqq9vYqm6kyZAP/1PC1bUfGQuZ9scYy1sxyjIMvMc1HH0SOlY/NAKEcPo+jCCCSaZGmeQ3fvR5v4cEWgW/kN/njaLYCiBON/u/hnc2vVIiEb0qAufCZnv/7Q0u0Bf14DpnWBZ90T6j7ne2PMjBVPNoO/n+/7XQaMrOYm4PYXkYSE8EWIc8LKl/d60Kf6p4NWgb2uGreWsnoLwj+/MBWIiLHuzb9jGYf1l0Zeg+btiEHCgQ0M2mUKqpR9YPUn2AWf5C8p2LHTArc3cGshPMx9SqoBGe46tFpC8TswzP+FnqSNSz9SiPjGL5MhkcNqyzv62rfi6S99n18e05UhXJWsy9FxEYYdTOLoKdueu8qHPh9rT2RMXTSPz/SYi2ahDpSjBmAyxWOWXW8FVEZ20hno+4qNXTR/MaXXhzHBVj5Ex63JEikSkpKun7yJMwA39ZV8aXT/nYv5GI0YS/7Vn51zG92WC7ZJxqG5rIT0dX7NRk3jLAZwKesrtSaZQfl/zoruTlvxJPPJNh8RX1UmGP6UBjOLmJMeWrcQbCmrtgbnCfm8VzlV3CbnFD3G8ELJX+te8rNyr4zhR3XtcVZuBupz9ZmQS/E/Nq8dd7nIG3uFWmqsafZgKyAxRvxx2C6Nc3Imn6M6nhVY33e3md4MYhjS2Gi3DKHV0MlaMyoDgAD3KvDtsmC5VFbssviSdTqM8H0uMUiaHfpcn9LcJYf96EqEOsFb9zTQ60bQtUQ/EUXHdK83uoN44SCy6rlGYQl4wGyKRzz+oh0SSBrwEKv0p50fYW++NgAEfPrhBCvCcsVJ7z6Ycp5Eg1sWyZu8QkXinL1Uk870Scj5/KsuYCdPYYbx1jxMaLaq3uuD35azrouzPvkOOJ+QbOHh6Ovcb6+wBPEw3xgZiRzc1HuMfrdtWzLyE7PY1tyOnuzH05Vw5+/e6/I/oyIGiEOpe+FrzCByFdz3XCWmG6++y29MZABkrhTQzjCJP5kjVlZ46fN+rEWcwzXKs0jtoJ+WikAXzyJrnM7cGLkZuapQ4BDw3TW3ydbxgKPjDOHnzNEcApVkb+euQX1xAOOTD0qVSzhO9kC9Pn3qNCHbha5InrN0zGsXtQ/GqK172WDYOfiHCh4TAE2NlDxKBqKumNxfx0xdH2sBiWCK/EAXajcmZS7noVr0OOoFJ1MLp4ZNxho/JS8xW1YNgjaHTg22iIAPsDNlpTi40e2BKtuId8V3lPsu14hauyE9u8RsUe5nnhzLvLmJHeeJ9hJOyHczjn7++bBzAkVPtBGnObK+f6eEJAW78TL2ZTOOjSE0l1tH4qENL8Ip8WWfpuEBh1xEhCkTMF55WcCN+exBNbIsVbQ69eaWBXiy5W90F8T1qIm9JuvxKacX/hFD4oQZ42vIM+P/Sj3UvPuKyZRAL+NCPcB2oVrR2cEntAdCB2JR02v1lfLtC53X1m73yUh0gN18lhpnEdcudynB4uoPhF0XUjbGZnTvsVRYvlXn9rme/4B4fVIdxPWNUlJN+6WkF8yPF1IIBQc8D8eUxTYjad3UA+kTwghiFRlHmkLW9x9Nb9oQjDi4a4BnAMA/4MxnNyOciivruUPv8wnNShWha2CCbj5eoMlD2vAFTg2RvUJDi+v2qsbxgwm9mq0AMFB92xXLhXsjkImbYw9uPzwtGTFTteHukhPYU3hRJxl2ipy9kX0JcfQSAADug/jWaTkL35cJQF2qsdeYveglnH/dVuUqIEtEoWQ5EhaXQHdKiWaqXRclqfhstJXXxxQTnSBaJak67PbrokIDUvTREnyzM2029ih2JBPJJedLKau3Q8uLY3kPCVJy9o2jAS6BhG47c7Fija7HCFPkIosJ0iZ/p9p+jg8/KVYSsCZiRXqQDDpzKBqU0cbcQOGYhyIHlO4zRRz7Ib/OdMiJxOB+uwHZUpXtRcBZTE3igmaRtTiIFUBjzXsf92QCbxQG+GEeMs9KXGcqGY8n4BzYW+g0CfZTqdKlGH7j6JYKHvph5FuKG+ASOdt042aqtRL/BU1ud95ePPmEyRv7FNAK93D/cDUSX5NbV0PjO/9oNgSQqTLouGRGudBB5eXfEnUhRb2cQlCshQnfBtpTTT0N6N7/x+kLQp9LunkVFc82M4l+aDMTKpKWwjzXtunH3Ec9a8q1ahdz6UjaA2kg3M1sAYk856m8xCq2zAvpgubkd+y3rNJiLtpttJ7wycr/3XF9nuJw51zK6hkMgRrR+5cNAm/Xy68rlC/aeqX9UEPIDKFVXzlmRBehUMMpR9w54w2EQ4vroCLd6UrPSHDaFxp8RlGSl1pMUHVSpu+H/tAR7FsVeXFXYZemzJMkmgrisOfnsdpulAD6uWR1Oygpe7FGLrRaWgvEtJ/J463lOKoxC94pmQwW4jkxhlUnXllC4mAz2Zagih4ulJRHt/sjICTKQHzICR40daUhZO5NUq/XFqJJa83rfQclGE4nHP08PD/LQ5JKuVdiiW5gFcdAYcGGF9Bm4h/WchtYtU2lv7k+kGxqvNUyTlKDVyaKVqtUqQkVSABdI7GNmkAioTHWTQYZPkUF9vzvHG9NnldUWpwxTX1mmNtT0SWxyeEfi2Ea05FyOATz3egAXOJ7oYTtPKYoxq8LfBSDEVRnUN9RAR0momEo7VFV28jzKeU8Iy+Knhhrxo7jCdeeT73qe1P7TnE9REK0/k8SnB5z9IMh/6jsb80QllDk7xtUjCZK1PMeJ3TFcldSmEIl+oQVOSbnPoiZP6JYUMiFPaj4OBuQFyUGwbHLC1DeIYsXWIphKI4dKuEdYVdzSPFHv7i0ots64wTg24Da+v4C3zBUBdOUrALnDjlPNpMD8PV34VIPzcmQBTSLtoBXV78hHU5t9xJRPdPWgdCoRFiUaG1z8KuCkWpEr5VUphMWTyt12CnwfZDKcUNowbNM/GYcQRlFUmodAyZAk1Es2zigbTvYuhM5dAu0Eh+IFEnAoV5HQkYZBcoCWv2EaPguZ7+aovZFBIbmfhtwSW8EalY74KK5SE4YKT5ZwyM1eYl30ELlrr+ZJnlaQkTlrU27Z+Ckhdaio2sailp0IrVk7BYxL6hrclPzmqKlRvK+NNZXSsFGa5pSNJVFICIFDjw7e3RhXU589janDDBVUKAbyLpKLYG2JOfYjMNdhU4VA8BIlUHVpW7MvIkJNCf4045pV84D+BFORkEoF1BOWs02RpM1T1auBu5d3jPiBWZrfUcILuo2+EFf2JCqbL9ToV1OyOtjJwc6pCZjoMtbyTCl7CRbGGWrgk/vr+2dlhqxtWFsUWyEoyD0V8QE1rT4xSLZWVn2F9N+HLQ1bfZlcaCf7ONuZH3jSCzbI5nQVAK0A+Iie4wK8i+1+gaiooyvgbos8d8DCqKvpOG68yMfmCi4c6HsPhN/YDxhdEhn/CYGkIYi/Vzv91VPrIPMvcvpiBN8Bv2+pmPbz+Cy/eezox/IoiJMtXPbrWsuNXZHWr4Dh9/A7DWMWlrMAcx83RS08Bd6Rt7qqUUIBWTLxzCLerDAw2ERSbflxAaReC66SiAany6LKjxhQkaYSpP1XAS3DAqOxvOjUia4ba/OPu8LUqf4O3yrIMUvM9tj1KcR6k9RAEgEJpN0nvQRpaIpkw8tX8mdrItLTtfmhe1q8yC/9Io8pyp3ECPutYX09bPV9U6IWn3THcShGXplMJuHhtp5HaKuVYFAmfcYkvKsTC2e2ZXSxJ4lSRJxNMtjbAm/7uNP3IQf7VdacdWopgkOb5ztMMiaOtqEaKSfXZLafEhsBWd/m9FZZ7UpoY3+lczoFWRGVpBtdAkDU4yLg+mSiPiVeB/DAdqWGinzC3ySLh7vXQL8/VX68fHOS7s3QrP66MQGsf/+9bMVnSopGhB8fJlZndwtgRWebKricY+QaVbBl/2Zt51Sjvo8XE5DdFztqcXJX2BfKpqTd8nMaWu+c4vxOWx1zDtOpEKThUwiJ31h6NF0BxSprZUQwO+ZjoO0b3/eUBVTS6PRnRBeZT0+WGd2eN4MOjKfg0HyjMpJ9sc2IUzGgnaRRfyq3qR6pvZxdYqnYkg7rIk8XNSpfEXkMSDHyY4+r388o+HBgr8Ix0MOD8+GqUHtRFgSM2oMMjX8XaeSEro3w7Mf7c3CR5KsB3bWa2i2U3D2W/ikoD+WjfYBkRSGTYkYkw4wsiGRvL9kYCsxAwhWc7Z3CTsRR1YAjnzlid+AqZ/w+pxVp4P73seY54xGpqHynu/WclMblkS3aJX+2g7DzIUSK/SO3Mu1753MTuXaz8GfWW65A9H6BW+0sFaDCX23TMLcNykcu3e4pdJGTn0K2ybFjrWOhZsQjB0scCkVKJHidN8yM2MfGsWEEng9eiRNgwv/iwKfvjKcznL23HngYbWj3LDjY78gPA8uK8GLmfcAbR8t3Rma4zNHaywX4HNF+IEx4UCw4d0bWsSDuYxZ160W+QB6A3l8Pnz8tO8007n7U0/xekwEXZb66m4CYakOI0wPyY30cEMd/A4Dt9JMKd0S4wGrOvAvbqgDdnNBGhhjb79eLc2E3W7Jf4MGcof3ycJa9Sc781k8/QpMOhOpL8ax8WVuWaZHAcjznNwTcV8iCSDUoHU4BZ3gjhGh4NPWCcg9ESa8WG3zlbwfcVUK+mg3pcHyneC0C5wa5O7NQmu+AuCy+XJ21FuFqwMpg6YJxsM2YLoUCI2amZICtIbVOUki9G3CDnC99EXUAKnfyf3c/VD25CuOFNF5ngHveDV9AeD7CjUTNiz5mv/XZb7v9SwceTFCXLvkd4H7He4xhO6J+Bt744Z/gPRHzW7GmoheASpXzFXP4TS2oJdZIfnJdafh2bpEY4NtUJFdnFVf2vWcmK1pI6xwoArcu6jZOz+hpChUcxYZUBTeu2XCY75D02JXSl5xKmFxXEKUfkzTXOH2TqFDZcwckxopi4XhTQ3CnKYWYqkJC4Xp5Y7MLQAF/+hMoE+R7W4lqOAkJNaxf9rAl/2J4NY0+luOZz9LM0kDNgt+FZhBqzpeLceIXfPTj3PbdmXJtlwhy8JM4Ag7m/p7WHH4RynvlFf44Neo47uGpFHYgmAtvDG712xyzWdFd7M8PJ5dgW43TM84nV89V6S4zgrdxHWh4N8z61SGntl9m3a8st2fz3rQRH4TjRhhpqk/qt+2kC666fqJLiNL8TiwLPfEwSJxfIXajckw9TJWZalclZBEZeP0UEBHEBqdcOTYnHe7tRe3gsd6vyDNPUTLndo8PyO+f7qaUIooyQAskxMt2ds92c6PGgcpcJaKaNb1c2KBqKE1OZwg4QFWQ1nUga9CWL8xE75fYtggatBAbGMJbun57u/TZy32qdGKKcaDCQ3Ekxe64i4dJ6QMeC88Bd1MAz9+Cr7dVrAsL9fPPUiU1c5BilD0zNQT7urGOXrY0XNymBshUHcOwTnO7QCBg+A6CEgWRtBQRh7ksJg65XUPW1J52i5hQo2TL8P1iMnBJ86Y71ZdQTii6KZSddS2l0sOUdn3A7yXhAfn52mdd+yt/8YW1NPy3vf22XYnuzqL+60wYSL908vBvH5xCKXtrzzIIDSlT/QrCDLcxlVohsnbQMiGzn/62TUCn9IY5gQwtYC/ette/DQO9TK0NOEDZ6I7B6z8zYN2c3LSg4+c3nDSO9sdN3K13nil6Tlbkw4nNtsjCJYzFOA2sDr7/P9awRWRM/9D2fAfzNK1ED+63wvhL4Quh8LHVd4NgnBSrDcsuK2XOZVgG5dqbznF9F6Ijzpt+Re+CAfyHoPLLbSFWqoIe3ha+IXgdrwcbBchnnHiBW1GslHBKPGmb912eINRJhWPraOt+Q2EEC7v7ks+VIiRXpoAXGN16AZMoATtCr+Rx+RTf3wN+orSQB80gMdZ3K4HMtnKwFdi+2w5+lYwmXZaicFF0s3N3zZheF5b6f0+SqDMICMiXr05mV2S4gt8XfCnF0QMWGsHW/cHnVbyRtbbWVrr1FIgqQvz5adPQMgdfE1jrOuNarbANICEqakS7xC3xUkh/RbcAjHcAzOCYPYWnTD/Srts++jTRx0NWBN92J5vpKmmZ0VhdZK7MbJkje0+y2/1V4gmaWOcxVmZpw+1VSOJTmxemrdEG+Dq/ij+rDEz84MvusgGYSjUIZ3r9BsKrYMa4OJpvL5UMdsCMC8UYwIHTtN+Ebl8FxXxd+E165nTd4a89lVYrMoKg+oPwcA6KVNuH52W/cQ1p7zUk6nA7biNQe/UWiX5/+7lnAdLJkr0SCwCkE/cD7d+RgvkLFbDF13bgXdoHDepgkZGnXQ4k1a/LSND5fmkVJwR+UcUxlz9Jt2O37D/L/0RhrArmBhhR1AUM/jPKcGj84xMQ9srYgMSAixC/3/gF6soXM0vFJd/96cYw0+gUSFgvQ+QKeq2OozXXF4Jk3iILyqdgJXdj7HmDOhUSgw0SOxzCLcQgagthL3PBxN/IyPndH5k3zq3TQBJk6gVBFrtGjJlmth5rXowNTK0ReicGElE/+JElEV+gAB/EtwW0iYsQvjQtiP9coBIh3Mk6EB2YDqrFAnbB132gYfQT/I9GGxKIO48b9JHCRooKYjgw4h9HjAG1aftjudomZLF73Z3w83JvXmXPBwHWtQ6XHMJbFTw00KrJ8Erfwewf+HlR5d5fylUuf+bMMXx/hqwbnbTcHE375+SMU9gmk/xH4RzRUVdcQ/wS7Ypzuz5fisvQA/g4OF1H9LJAYPmnvUwM57ay8jl3Yc54BKU99DkDppsjrW6Tl07l43zGEbEcWtrqfuRCTi8woRibYjwTkheEeGmUTzQlLKS7tCkt0FIwX4X1GqTc+1/z7SFTPX3SV38hTGdQAu4FfGfTRrotoWvkL1vm3TbE/hiv3rtfsL4qMnDuLXqY/YQnHTlokX+sbirWw2gj+AIwcnlKYXtnBTNyYkIJS20YEZfr0jEyFDUcRNiuaU3vzEgHZ6lbSeAn0wwngR5IyEqCy7i397rM1+8wkQtImIxs7qgSZwjSYXdrhr7BvuS+rYSSkBbnB1P0Ra4UuITm13VDP+CIVpnQqN7Dsb2wuun9FyM5gL5qZjgdLo1fK/9go43/BmDKkf0ygkG3Cdk1PsOZiCn9q645+jP9LRL++zOvsJ6QGfdn5IfKM/7vT8iXo9OW49BO86GFdOYibPwmg5o3yMbQYyCNQzip4GrMe3FkaaywyrSdonG5SVSJkCsZdu0LAPD9Vwvf0R4iOdipaJLdo2SqNEBHYLCsbvhPxKTqGXPvf+8w1Za9bkQYkoIAGF8EFf6Ad5QLW7QF2luabOWJDOEgMGjhw0bKAeEp9MC3Re2fTA80fZaHykGIYgOakuca2xIORDQkHcor1w+sI3IgapL24blJGvEGEHNIa5XKIS9aFceQlzF5NGS/N4qCqDBF4jiS/YtBVBs7UnfCpBGJEgdvQdEcszpFqHTaDWlItMeGO+zlWAJ5IdTM2EeUokd1YzGFjl1iVnH6IK+DjB8SO0/NiUZlXvMZx+SaU275WYpZqJwwU9XI6EzdwGzKVJy8fFXPMdcbM/6Hi1pNjI5xZiJzljkUZkZmNW2mCy3L7TJRxu8R1XLDQv4UIhpmDheqv0zygnIMTMIosRd/t4nf79U6wR2nK/2P2Z/Gy0s/szbPL4g07K2394N+fM7x/1jQ56sl2am0DNeqeBsyY7KrzIrb1lh41F5hCBLmMh5xfietDgD0uMACDhd6VrSvB6nnpxL3dPMAP1TrrQ+mnsFhqqH/h+y0D8pVU6wsRC/NYayx5gam1nYeuu/lsL1Tg3QmQ78zWCQ2GFHIF6KX/zewF5NDv/jB7FDuUAh89XFaDIeJTByfnpM3UC8L3MbJpjnmmHGbPM3sGHezjPGihpv64ZN562nMaY5dbKF3r8XoZtp7rGjOIFofAUnv5h0ISzE=
*/