/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_operations_fwd.hpp
 *
 * This header contains forward declaration of the \c extra_fp_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, typename Value, std::size_t Size, bool = Base::is_always_lock_free >
struct extra_fp_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_

/* extra_fp_operations_fwd.hpp
H4d7hvr0cqsGWdQVfJeKHnNcPKBppiyxSLWL0/CoM/u2oXcSzZU04F9Tmb53M5Uij9StRvUOTt/P1s1wT2fpmna+jNHozt69AZ7E3rtt5ywL3VRe5nSDkrJMBKnA6fVBxZF001tQoVOntj4WDmlLsi9ivX8ZpytCoGGrFS6tsDlik7bSok0zibqOF9fOAWde1+mrYB9Y+4eKljOb62dXO8oLVw0GXu0wMbkSEJiidJGt+oxuN3h0Zhm5b2meA6e9glcY2SffLuswNPOY7WXeAiWJTKCB+FJ3A9YDD6A+8JDNl0KUZ9iV11ycWGRM6l9FilqmZ3gTJyhquCR5ymRi1fmWWvJjrccDRZc+VUQfRhg9NPl2lpbM6gSOIMyuasarEPiwvaOaAv42c6EfPtLs+LD5uIeFo973B/+awfrPIEBdNItQKmALlxQ05Bt89JGlDIvYdiCnLajDLah5S7fTHno5HIvPutQAfXgb9hrZuluTHdyn7RuEMCvPbBGkGG1yX012bA0XtSlH+2CydAgAL3cpc1+Jry1DNejCS/oxK9zcd3LmoAhIzi8ZGBy0vGyCnBXwi2jm3LjnlHfG9Rqfnua73b+5pwq/o12CJGY8a2yQuEHQ0GWoSyGr4bwOTqn2rkN9OcDJPnXZxEB9fIbPUCrIC0H95Q4i7vYITWTLyBR0j10pQ83BizzdBO+FFmDr5tnzNawE33iB9mGBIONBW8IfiAETwGDMtRRbn70McMzVv+h3feeqOaVrO1UgmLfNU18gv+AqAuxdtpUMFSNEwcTOpQa2qMXELZOQzGtJXdidce/mGhOhDzTgChE8TajKEZrdEvJbiYhCgMFJMfti3eaBenelj/AxcbIBcbiL1Gax2UD0A4cZQPOBPB9NNDqFAIr4DqTbvSO4PVTzjccKdEWpvIHY28JRyARxvvbuZ4Wk7wJqDKkRA9YHxoJkRqspvWv3H4Zd5l/dRVR4RdiBZdpuy/uS856aMjTIPhjqLcDHFQDa02UAX4GUV9Iy2PL2G0RzZcpZbwHH/AM63wnkhf7zHrTM7oVMN+1fcT+E8QWwrEdqcqYhbFivDyOynEpmVncW4u0oG117ipypdT9HxdOhCV+Cr0cvoKCOY1ArvYqwknzSlldjDl/rsGe5g88VPR1MThe4tRWIpX/P0vFDAi92xoeynCjbRPhY1MN1tG2H6xHj9HqAeGOd+AcsqOMA7H4j/a17oZaIQpXpZ1xrngqI2McLdHFAK6RgoduQplfCtNUVPbQeyFYIfNUMVQJYT29NLGg+SXB5uz41ZwCeDyEI+h+w44AqAibkA0QnLtB1JxPgh2sYM19RFGPWF9D1ICbQ/qNN1mjUGgy2mpNURrbDqfRcGLIsOW1CDmU71VzMiwW2tI/WTbUJS0cSWOYXaWadXjf8+3ljDkbROwxovQ1W3wH4iYXW5vB/6stNB1WgqZeEuxFytnqLJmy0JbDFl/OXq1mBWEG5wKdbrmkxA5gUUBpweLc0TYpCgS9IHg9jDWUmVuXVYbsnRtM55WSlr/8SYttI7rHvgft4oGg9WU5EqbDPCd8de/JO6TfYi6Pc8l62HR/T3VGmDzBLibIV4CZqxSslIrcfcGvRkFfFOFhY9Xo13f7lcdM+j5pfvvA8z7k/g/t45e7XSfSRXAm6kslxHqmtMaPpKrWDWLQF940BFgfqUnjK4Jdudy0/kqaLg/IFUCYWjHxiBvSDxDhKafq3H8D7A6HOg4yn3UX6i4aeouvXTDSXcg8ZytpL8lgGOOp7inXK5iBYzgGm16jxUTSJmUWpn8DXTGRZv8Err8Pqg60iBpHtvgfsFOhp2P8wDzS0VnFUniFDhAd8SWoo82yHfF4jNwA5pK3vm704/UL+ZKS8Z2K6bGDaHrxEMg3LkE3N+SXrRfl00xKwdP2It66EbcfUXRmRYOgtLWS0QLpcF3A72+lK344CocB/NdUhMqFqHNYYmxa2nMHIW2F8DaD3H0cs+1px5I7MnED2sjk17g1mFtq7jEh908Ns6t/2OjdJHaAMoZPptWkTxiTvb6Mze1gCuHorPcdAfhCu2wAtUe938VDMkO4tZlAQ8SIGCIBhWmIDN5fcYGxrr8qzgKS1Piojzpch30Ieyiv1L5oDMZmTGz6Q3oS/JjHmzMiCiBw6LjjhY72PTap4XEzOdrboVrXjty26nyU77zyIFX9leSYz4dOg3BieB/LnHFIynF3S9Z0EWcKthA05PfbHmmvXZUKSQ5t6n/JY0LOg8F/C0F3KlMwk0YX0s/oJ++DUbiO5EMbO6oGhAW7gYugXFmGhgrvMqQpPXcw6N/dwcSk19bfVdKBFusFkD1HppSTl3/rMvUkBuRSwGgcP2yGftiYfsvngqbWFiIGdX4HHP5HQmt8jVf5zt75VOENeCEFNNh8jXwxei7SUjyXwwQDaOoDJdfVC56x3JB3eOgay/Ty6eXcPpZW2gOztMbMHaiAus/IGw2Dx65KHQ3CfUceEkFqfwDbeXIi8g6U4Ln+Gz/OCYNhMhJw+HWNgDmlhF8dWRZqfvK7BX1Q+6pO2hINITMueRbAI3ZVyZhQ2sBTAqhfKWX3hx2UfB02s80kcWSY685/ASS0tMCLROKlebyfjK6ryzsQfLZy48V/nw1FlAPnP1aSif1ac4JyoZZdQFpROdjbPxEP/N3nwyb3gLRDznEzHm2BkXRj+gx7QW/VoEocaTFSfP0p8k8/RgHZ9MiLcjJbTPRlbNlX6UuQ+zUW6MsX4rukI/W3X3Urnlb3KwC6RCdgflj0Yh8BhodQiIs6/A4uYwhioYnli9EBy0ENB3H0sEUGQd7m73a3YIV/DnhZmByq/e2JRoAyj2AbgY39Ve/6FgkY6xla9oiD37fQVWxfwcqmNCuxM2zKH3cd2KAVJBKSAJh6QLoJKVdA093523o1goDxi0xlAR7uJH11YyhPskEHuuUDpHHJp0JdtFMfbUUe2Ig3dawsc1P83pBa5RijNoQog/z1iIB9zNot2E/Pat+fgCZV7zg8o2Inh+alVXppTOvF4YDbCSOhSkq3hVx4BKtge1czT+kPwBQ213K7LzFfkP+TWVWIyHjafL/NdvVLe0WJUs02rI7O6Sgk8YXgCEkXvzkw8Bgwdb9n412Em/J1JEmCjyRWwsFQa8t2FIRtgq1ApI38rfSUlI9l/yAFkAACBf4L+BP8J+RP6J+xP+J+IP5F/ov5E/4n5E/sn7k/8n4Q/iX+S/iT/SfmT+iftT/qfjD+Zf7L+ZP/J+ZP7J+9P/p+CP4V/iv4U/yn5U/qn7E/5n4o/lX+q/lT/qflT+6fuT/2fhj+Nf5r+NP9p+dP6p+1P+5+OP51/uv50/+n50/un70//n4E/g3+G/gz/Gfkz+mfsz/ifiT+Tf6b+TP+Z+TP7Z+7P/J+FP4t/lv4s/1n5s/pn7c/6n40/m3+2/mz/2fmz+2fvz/6fgz+Hf47+HP85+XP65+zP+Z+LP5d/rv5c/7n5c/vn7s9/f+7/PPx5/PP05/nPy5/XP29/3v98/Pn88/Xn+8/Pn98/gOR/9yxawIsCFy4gaXRr88UGA3vkMU+azmHV/8ZEoKLEtuHNndGZdx+gV/X75HRY2G9MVk6AwkpNlgi8mSHmdvcElIc5lV+TsatIadtx3T84bwX5ekUVPaDA9YVp/npidVuLMS1nKRDtD5Zd5l4AG4H8n9q/CmQ+hfU25W1gdvDYEO90/+d/u3K4DrTyZv4q/0Xp8JuJe8ujl9MO8sQ5dkfQy+EeP0J4fdEw+3UE3LU+gATICXqn4YeDnzwvsan1m/RDM+q/MoYDDMO/XGveg44dgTRrFRwH/wN30INBIDskkRcH/gf+GLLeD/EfmAFok39Oee1Vb7y7haD3bWTMlXtHk1lnUc3clK7yJ5xbaq4t7s9H7/G94p6BWpTx8zOLchoFBC8VYjVhDn5xlWfN0anuAGcUy1OIG/Ti/HngPS2Hs5hgV5OhmP57yPD458Z1QysXje/a4qkv9/PKpRqI19iskWi7c7atgofHdetG74by/wAdgOJ/eYVZ954QLg9v615xV2GOraX3Rf8ddAXU/LcHyO4XAXHo9OSPwENGd7bQFjuchVV9kC7IfcQAf7kJS8vlBw6cRwbnpdfjq1eX2CeBT8pywfvYZwr3luGE8I2EzvQvuT1dY6uvg873At+nTjwf/DPlJy4tFaFQZkBbCFt+fJTturL36+4qfB2beM4tZnmOfXXk7mWQKmHZtL9lcWU4nmggs8UbwnJ/Va6Zw+jpRej0b0VI317Atv8EiY3eBnIkyJElYg/lDfLiXwcWcN21qwPhaU4TFl7KKygrKQAPuNxNOAWkad0C1qUZGreWh3vj+ZGmNXus3RaHoYteiyfSvazv95r8oZnrjzfQ1R6l9ANeAHIgc2C0kreNjaHgawSMn1wrXasY2e7La8AIe6Ge1HFJS0B5AfsD8XbwTV9bZsGP3EBaBiMHweYA1gbrg+x9d4lhRTPHzL1HC0502KBunUoLlv2diRNLTB0khbU2C4+Ue724GdmxM0KtIeg4iR1q7aQt2NvOLIW5Bvi8yLsiPzJ4Ak5JvRUsOg36Hf2J5x2y+5hCV3jxZJq2lOd8yK4DzSs4Q3lin6jOYWYkcQ3enSjLNWwxPDl7V5ulo7vvFQxtf+1Sra4kKf+BOWRVlEya7Hz0XKz6ZObED1yl1Re3S/VaeqRBnbksY6PAJ7kx72de5maS89mTze22W2dl7okc/HpfnKuMwpj2YjKYr+T43f/c1iBWH0QxY6la8sXtyMP8QjXae7yfyy+BZc98YL8kofbJRuO2yLjOHcwvLYtYBzyAedxGJgNzaOdM4F7Ych38J+qxhr5V12CkEJvzcS+ZDZe/7e28YvmEKFL05oDaK0XzxotOvsP7ZPPCGAcAIbq3Tuijm20FViGEDVv0lDQWTV5Qz48b/DUIaEV2z+ZnHTGrddn3SIzQS2w4dxX1N7HTgvQ2AUDzHtG6HkieqtT2bDYFOxCdMb3aWyycbT0DHEOyq0t4HvrsNVQbOpf67bnVYBjA5CtAhnC138+9r6kCdqNloKaqfm0qcuy69rWXIeR2EIsqNYWADKYFcKVKAeNIst9T3u2/iNhUxXe1yvhzfgDo8wKzTyk6RLsWnKwliDqM5yJgcDZLZ7Au+AIVUB3c0Hj7iM9F1lGdGqmQFMTeDt8JCjjZ0VI0A9GWcHbIdYCdxlNiBYoNk7AXHmpInLiBJMv4gTrE64K1w0lRLcPzzglqByBNfDxPAzn7LhtsN2Re40AcXVuQT4m6oQl3OwY+1OxgR27gtywb4AOHaQYKxMQvwHtVOcldOle490wH3Hu+Yr5lr93GwYdOnwiWOHhRCf3vXvPwXkn36N/Yui8iPOKmoMC4ERuoBQqNQXxP/LniWzA/gr3HapA4APySO1Azz9A3IStm/7Z2xRVQ8yK3BgBY75gQgS60FzZC6kHeaQM01CkG2bsT0gDNCtm9kpdSegiTYAZKkWnXRwmDSu22gjkS7MU5Ak+ApvkU/mmUjSg0gcxmU+9m0BN4B5LUQfvluNmSJT/gQejFnO8h3vHeAQ7hMMjAt2eb7m2cjaFeKkl+sDshAA39A2h3lKS7qKfG6dMXVfUgXUL/RW+xuTXE7z8uuIWPuB7hmXuaWqoJ2NSLbioEyKxtvc2fxw8ARtL4ZyJ2RCGp6waLDrXf6f0jNGCdUUFeTRI7cjn0FyREN7mmxZ+yZDGppbIEQP3ODWqau3vX0gJb6dps73GfjJhRutfKG26DKzqSZoaYbZOOu0yE0nd70ibXcIbYNerpmm8maL3pbwOv0M/omxNm+liG9kdA6+QeQJZak76H3lNrZ8h/3vI0kfSypaEjLLMI0A/QKDFJXcK/qKyH0Y//2gr/1MoxhBWvyTm2nBAkmyHyslp6N4Icv4L881GED0R8wTb05iMBefdSq+fDSoAH81DhrN0EpffEvh5x9/vscCiDE3zp1mHqOz3fYadGNk2SZ8hTIpDqnKpL0Dn+Z+5EigkifkfsYZnq1aIJwXHU8NSBOT8dbnxA57Jtj86yvo3VqbUhb/e3fe6K56YikyJXNeKZaqnHD7EKgUygFLvxfgTdc0/77QJGaV0JkVQ2UK8NEPuWx9uLTAmy0bZ1t+dNQfT5AjT2JL0miHd2zNqt4dGYEh91MhLOL1gKS3k/NTQ9sWg2PbdCzOHSvcB0/vRIhGrVD972ZQpgS4XcxqoOeboFnCjESFj7aN7fLAS393IYvfAGsICMKN9Weg87K11tgpU+HHubF48QhDp+arjZ+ESjVs8BccPdd3ijfE77Q8y/F8H7NvWF9AX9NY2J1Rpe27wstnYwN6IakpcjG1LAniF6qnxDkyEg+aaAhSlHgQvn9rmZsBPuHC+1SrNTj3yct+tCYU/zJYgg8725pc9VSxorP4RjjjP9nn7NY5YsmDw50+rPrphVw++Vtu8Jtp+EqMnnA4q6KnNXFk5Qe6biGp9uDW/4u1zZ9wQCnEMPeScDCwwTIeY8PxoHgrNEQDj1TwX4vQh8dOHihcozMRe+MIfLG9srJvRE7fELXqbbmGOwBIFWN3srx4n17aSnXwX1AUleo4rXlw48fn2FAmC/wxavmZ4dSGTDfJEAMPSC3gN6yCwlyekkR/noBht0NlY7A25zDhu4xggOn9dvtl+b9F/sO279rdpwzqL13mub3xYaNy0/CJTQ3XFB3GhmuBZifwR38oXf4A9IQ65qAgxIax9WoDCA+VLXT9BwTzzJIdGHNJZCfBq45EgEz8le4WZDrKgXoCJUjiUjaKEt8neaT846cuahWj909kBCyqnNjmmqjuIOXQndM6mnWwa9rGIbvwwpGToq8O0E3s16cXvyfE8iTrYnnksE9ybzDPPgXggmSGSI3AtgAADa6QU9YAzlRm5l+IP3CMkeec+4napxDGyXp0DL4c/KQb7CPduOxlXKf0tgUL5HOJZe1nuBah8Umh7g19cyqK4ehN6pKWagsL3z+4r08rFxvU9G8nsGiwe0D83h9zFLD725SL4jkCxQpCFTeP3D9+tz9+8PdRACfMkHD0r2DBFrRgTsBXL11t3rt2Uuv8WeEi/eLBJ8Nc/dD+SuqJdP1e8zFCOKhezAgjMdJF8HzoPhfzyDEiRrcEehMseMX/NhrwhbB/iXQABzYRUhXKy7Y0CKASvwNeF3R09BeRT+Qp4AesEH1W7iimOxoUfUNyel4vHG6xFZCZbfkWo2jbp5xo8cAoWqSGG5XdqTaBZqB6simdMDrR1iGmWl613OcqpWl7YjRHm7L4OuuC0liZ8EypJNYnwGiE7WCvVAovb+vEkAYwprIP81ADy/2n3j4dtFgR4UwJJMXeRhpysbTvI0iQSDgHBnC6aw2QPrKWg1D+pxCHDO4ZTEGe6SNNDN6yZQ61IqENDYlGmbTdE0gXIqeyI52DlDKEdON7s3ZHDY5aZ4JqDTPIG/nvYAIs49lROntP6stbbsSxX3nV8g+711Uy7N4PA9YywqQORs5fZo9gXrLo/xJniW64ddj26hyEhc/ZyihKCWlDVvNNTyRp8enU22Zb0LnK/Qob97V26HaaV1kqF19ceY2lcJz8PFJKXD6UL06k7I7kjNtaMlfy3Tb6/Lj9rpj4qvDfpX9uYsL8cVA+vTr718Kd/rcV7dUrf1Z7C96d+UHbLV6n4I5pN6k9RhIg/RM2V3ioH+aYMg4XAhHoHcvTWmM96AG12FUFgiPRZq41Yh3jc/VzS1JabnKKXrBDODTFjl2nsg0dP4t9gSrVquUYadyuNTwqUtd4TVs7Zgov1T8ixO2wDZBptKU+Vjrl7uZYRD1hqOolRbQwZkAZ7kOiGXEoS+OjE3nbp3SxoWxplmfJPFaCgp95u6VfIg9lk+w01SMUrsUahf7OtNJwxe5BbLEdttR/xq3ZXYw48DmS3vIDZwrKsH9BQEcjKcY1esJ+T8i44KbeEqOUknb24pS6+Vja3htda/PWV2BXfu+GLf1bK+cHS9y21Byr339lxpC2wpTOej6BJs1a6FMV8VC1/nx3kO6dDDBr2lIyj8NqEwuHzs95Ff+vh45rtrYGOu8bWtl1xuZCae52BISUl3Tgkdlx+MXzrk5Ql0JtQCp3dXCfk9XNOMVm4DCF9Hn+Zj0bzTfiMk0XPID6A8P5RPvs+hbCLfusCJ1vqaZWCR+Z2jctwrQ9jp6zqY26M/VM/KtgNubK8jJ+LgJidu2P8ewh9m9oEgc0jBBNASMhScQDs9/6CqbFg1GRh+s1fyvJDU94BsdzjB+zhy/AolXa+MMSZJohTFSlESfxmPkfedv1BsOsEnqEH0/QcIy3SbIroENUl+XzDLlAoDSz38pthKh5fc0jwswQyUD7QKr+bKohg0CbuF1RphDQDTE1Et0ph+74TUvCezQlOnuq8IliENqUsklYlGVGOjIhTSMnlm1A4bpkM8NkuJiqlP+XIybi8c7LYySi9jxehRaqSZanTY1HQJkNjUMr8imvi3aJ4EgVnFT+S9yReUQqFQK4lfEcNbdIApGQTfyMoQn980UMxWnp1jyF6pbXspW2fZO55rOxNj07pUXF/R5DnetG8myHFd0bC/65b+g321p8o8W6654bJ5yQXncXHPtjVbdxcv88Qg7f57cb3tA1TmiVGagMkMH21rgtlMh21roxiN2yPOzmLDWHmC5ZQ4tX+e3PLptAVWS5pHhNTFpj30FxgTeiow3kSVBOkArbpg2gbnSEJVhAZXusAnpzZRgq+oJOhn8zIDQmu4Hp2pswulzN2mil7IOjL5JvA/nTyaejo5wmZBVEE909sfWqS9WEZughLMf2gGPXWQQrPtoRIoruYVOzHDnah9e6ZmxrE6Oik7zM05Ajv1zyhfkYz/2Aaxc/OYDJhdOtWDvaat0WYhuKDlf3Vu0WxUW2IrzsmELnWS1Ey8SDwXTFkoRduTHjq2nt9oPMyx7orAXGuEJVW2bC5foV/d819J7ErL3FB0bAMatVU6E/K9X3NtojM+tLNvcy8bkvVJ+3CT3RJvfK2KsA/haWwj/+Mm20k7dHtTy7zrQxlH+yTYB5RA/k9GXTHzqcco3a5NL4UmyQdBi27a1sft1F9Tl+7hbP1kcKU8iUqW7JTpRr5Mp5pS6xrNN0zudnanemodsBw=
*/