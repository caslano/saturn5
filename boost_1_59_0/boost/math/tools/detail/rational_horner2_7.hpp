//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_7_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_7_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_7.hpp
CGubxVe8esQLIrxbJ2P14NWh9KBdyWmBAUlMhj0+yUEjvjYrXnYQdhlWxjhdxwCrQ+fbHjzi2oS4cTNXLa3TTOyBJS6yimmYT53xC2ifsOu3IYeqLWY8zLkEldMEU052q6WQtyUsDXv6j5KCKSm+DQR3enWSeSVh4Jx89TC+BTiwUBDmy6F+82MyRKGoqOrjjgepbDP4tnWiqNQ5xkj7m0ELCTf4vBZf7rOTb3Bq+4AgyJwmCLeQd1hW4AsU20Xl3ZoThVzgwec86GtjdtCLQw9kCA5E0VXaM8EEtoecpdlMJSXc6KF4yrgiQJ0JGkxBwRPjiSKhj+IGRN8wx9DfA3l4ONklfHaTGo4NI6g4gEA/MWAfMShc9a70AwaJxGEeGUR3PeCdhkQe86ieR9evsTd4ar6ONnw+di6zfQicloS4Pa9eFTVdmRV7n6K7ZcUt9Q4gTo2mq6mgzGUhvinK+3EGT+jaYrMeM8kn50fyS5Mvr6mR7p52WyVCfHApyLbiEchk7vRDZZ01CKbrDyp2MA9MGaF5oPCp2IpyVyRMQhrRevGZfWvzZhBOBa88W0s/hZhcITPX8SzEq0LojTzxK+d56pradP0Z/Ts4TAFp0YUFRRmx5znkLCelIx3LNRl9OoO0rPom56XJrD1SWezykD1EH4ZmZsSgGZiJNM0dypptdVTHmRYriXEYQj5SaEFHO2BydYlUvQ8fS8pIWZlPO9veDXBFH/DXhX+Wg14h93KHsetr/atl8G5PINiyKksaS6G1FmKhTnkIfpZqjB2IQo9avkWz+x+wkqrLiUF3aAGTkx/SfwqgG3v/wT9kIKjsc0FkPRVB+k3xxaoivAmHqBPWrzws8dsjn9glg3aHJ0LLc97tjKj/IdbsMzKZLNY7O9UrXAZGJf77yYfQ7kg/OVdNgIXw5vC9mCDWk+RYyg9bPg/bfwmRBV1lWt8yrvfwpOR22l2JsXjhU+j6t5s2VMJ43Kf6R8avxFEmEHaFcSazxLVyQ++EmbqBjBbvcEKOCAZt5dt+QlX/g73wDNhLZ2HIh8Y0tM6Ns7HovKQ89qtqaO6PiMaVw/aokR50Nuy4aLLZd8S2hUhDVlX93CDmRKbX6UCqnkORCnyCuNvLim7eNUbFy6WCXWRSwcHpkYkCr1qQrWUjgjGE92mevik4Q5YbBTlTdxezlOoil5Bw/rZDGED9P72Ffx++rsNMA+aa/oKfuw2NuVCoyTf4o+uoGKzr7e0FcHhf2FdcYIqPxqPT9vEZ+fkKeI37obKQurWALtdKAI6nJbim3HDnfPI/8NCgI3pVX1TbKfvKhysfHRSqE5Oq7TgM0Pwxcm2OuiDo5rpBV1ULOV/jcCzaoOU3hp5IVBC7t5tZdD8NJl3DNmthWgk8FFFASH0j7w8hu6UabCdRy95wyFPmPdKyYSndN2pZepT+08piuaMfqOHy4L4AvsJSgAC+Pz532Gir0bURbqQLCdRsy2YuYo99ES/N2vaLwGj4VVRTJKJMAfX6pyok14GvQUUgK3mO1g/QC/g4etJgkrpLeFMy0IQS/yDWEGLfwkQkqrtHFBNSGvoJmSrYcnMvMisSaV4LQR+hzMSX8deMHQRg2cincOFomUjTbV6CYtGCvSxoYt4FW4Gm9f+m2Yqw32ikls8qxSUu4tryNOvs4rmYXYWIZV86vxlTVtFi4+fhoGvhyunZ91Z9xZlVnLQdxY3CadYnEQA3FIkxe5yjPzw5JODcB8bUghBcWrNDcUitvLzmaYcDXnwnSSlfHfPcQIwOeuRdrTJmwBp6BGFNalNLZmdXJbc/FwyRAcDMPDoowI8AmXzHalw16rEJvx7+dVjIGp3M++N2Iw8PLKx0+aWFSngWjjU732xMsQseTrtOIoy4ysZmOkbQlUbkYySB3zo5nmHEo6mVyBaAWB/u5DMzKrfYFSF2Sa5ASVcfSq1FLAcVqLKRejOwkSg17US1XWjzOIO+Sktz57Z74Cz7WmvjtNvGt6L8Xv9hVvjxJy6Zfu52olPHrUoaMZlPbjB7628f1Wg0lGMuaj1u0LCWyNYybkwa4d2YpHeBj06o1OTqilkUXueSS31ESSxjfnKoBjlGQ2s517MJh0A/rcsOoMq4F+iWyJZOn2gn1NeInIonfU6c+StBTp0H/KoR33zgzRsXAt1qpUJTrY9b4MbGoI8zVsNHFM2l56d0CIPoKojkOpRHlt9Pipo7isUfmwzh+9m0Hqd6BTFH3V6IvFgc1eOeUKEEsGv32IgtM1r86w6JAizSKrQ8ZTTHQ5EC7pf0CUNCPU15JTa8pwPPKvUnJtlpsn6KwnMAOLmCCBaBSLHYNfHqu10zfJtgbJlNTQQAGjxYEtr6DsRY3kdVQfMHxs4nuu9o0ftFTNnbceyAajfbyutWBWeTLic4nUucxlIH6L0lvEZaKDKr2ZV6V/lyKKDnSZUZ/73bjSrqZzJrqNwZlGVusHWepJF5oZRNbTr8u5omrY3sNhyBrAyRYMXTdPgqKXrw6CDIsQpVnvwvwg5asfcwS1axd/Bmp8E7l+kCHk18Y7exjfPRLpzZvEeUf8C5zFZ/SkUvre7AG0D/QlWs0bsFK+TrqFuw49cpF5s6ausxdDeLY682rGxgny6rlLJcerbaAFXplNBwW4+cxHnsum0ZEld1TgzebX0DMW6UPHOpDcG4ALK51ifIroqyI5NKTGpJj0qSi44Sqj/8cV5OPR+PtfHjn9hroajZZ6Gq2udZRRnTDgJSgYSS+1tLSI/pItCHvNLPwdlodbm47H8e1Hp5Xa2XpugnuiDaLRuQpz4pCsfZqL+7IPxaFKQgbs5mStrmyuzaONXzbMUNbQ75F0MEZ8r5LOQCh3m10lTrCCnKrGS8VEh5DoFlwfoMmfyN+8mrsTWIv49RRbw4oFIs8NyTY+/5rosPhzZB7rnmFE9pfWw9t76SDHSs4w+itisI059xi6zrAT//GEutK+8MEeRrjpt+9oDwvkAqz72t1cVP/BCHIwmQ69NZ3iNXipo27Utrn3U4XB6hz5Zt1tLwPCm+NtCHOcOg0GBweK/57mrroxL7FGP9kmY5DAPYl2BZeAxfbCvLfA+TOXsYp+qJ0S5tvjC0NWdubu1ypIuoOcfj4y5/7b7pJgKwvZjZLlp/kmJgYJJ5ZMBcgcyRIAfGNv4MsTCvT4cVU4hwEtw/MKgHzxDQjUdgMdpLl6sDeFQGOdXueWC4ZOQgq6GG026ifzzY7VnDccaMSAQzkXskWJ1Y3I5YHx2BD6rp4tLHyalzxeaApIR1YUFuEz1ajKiv/gxrveaeMlDYs7Vut1Q/XAbwGT0rxie2V00Jj2MNenUG91Sl8V/puWrrFRmc6gfJpT25ArxZVZ/cdow82dgT0XHqFEVCVOZW3X/MmuF8BZh/7YpzGBquZo1vkPkvM1sRiKCE6DC19gIv4JYXj2gp+M6PzUCMN8ZBjj+D6fTH+s8Em3JUwkq2NJl5Di7icQH2HFvJjllZDkBgaBk9v1lOAj+bHXgywnlp7AnxR11Y460Oc9YYjB6gOLffBHxZy7pbVXhKAwFSX1RFVGzacxt1KOASDmbM5wWVXAAF1VH1XkbJCS5LO3F0q1+uStH+hLhlxhi8Dx5H9nBpzvmIgoZ1TRy/5Iz4O9KSuiwgprdxoxw6f80hH9638+O3x2EVS8N17EhSdXwJ3hVQI7idyeR78CZKMyM5VU9nWKUmxj96ssFKNeOH6HVhWOq6BQSk59xbq9tKwaqjDl2o+Zauehg9cqF5YqUHc7JuZescWEJwLzaxMTqHW7YDt5stQlLLZNxqBIzkaLCey/6lw8isIRzb/ClupazuqHz1RfyhUu4d4nTBmxOAXvaBh8cXYGca0aW01zvbgfGr/NbYRajf8H/6mlzIcH2y3tfO1/B+hPhQQimQBKUyBOWmoBcZ7MVLMdUMXxvCJK5b6REN0MgsEznjeLcOo2s1XO0ACf3SQ/asWiFXz+aOGjqjKXxCh/vrnPrV/2it+2xlDHg4yFUe5ec2R7xM+jXMHQ9c8EIS7e+07oTmB5fVtAihUgAcGKDEFn6Ta2xxnU3EOMvNZqIxfWezuLhB1x4hMjZ0a3PGf0Id/1o5gSGcYRSkzPz0uPd3ahtxrW6KBm6FGuMy4zz2yTeKjLPObNxVj8BextquCqF8nREvUBZi5nb6hmyPdl7f7SZU7UJMdoKY2NvBv8ZfpLPG0L5Zq7qLk9ssqqPvEuRCRnFNkmq1oFBEtz8yIxBRfLNkw5pjYkZq5aSn0W19YSivNekhcuSMRdqgEdWzThyDnK4rjRZzKOxJYy86K5Gwa71f7CS+nswhqol0fC/GQgi8iB79CA0JGlcai6IxtaWu+6JHAJO6UpYvAf/HhSa8h4vxfsQlmUOZWna6PUwQ18tHUUxt/vRwO0fp5Gpv3pPP0H4Cp2vCkL7iFe01Ibh3oqJr5r7KtJFTH+efvUsHDdv3loUZR90/kZOkIMFPVhxSLolEtPgG30eI3sJiDcRB4dNW7h5MDLX5NVymPO0AmlxOufheUQWDagpw7TI3JnA9cXLTMEHmDEg13wIAVhb8FIygXF4ijVXCYPbtjDMOCwQ4ALt0aljYd1+VyJklQmmEHTUgSIcgn0uA+rjL/MuROOezppPQ9ASzhOnM5pPhVu8qLpPb7EPN0w3b+TZE4MLIJDuy1XoeK4lmOIApjjq3UDXHowPIMK5jdUqeBI8GnV1B1BA6ZamuVh2LTujH0nLmXK2N2tdXWBESPz1vV8TbqWWGAJK6ENyNKPQmeVHAtppRs0J27KYUlElh25c90/yRrS+6OZc9SSdgh4ywkyj0SXEBGmzXGUawB9+wGBsevlD01vsz2OVekoej4PlSNjcnjeCYXU4JuQtt+XgmjfTpQWGk3m5Q9PuI0XW6T7AOitvh3Pgm7CMLA+5afqbrbiMEXzoE4qwoQrwZJB8ZSNIRe7uAV3emBBnL7tMazdGTzDFuCfgrYqgO+mae6Densj/efDOkf6CRsNZ5hEVyqrmSr1+g7WmDTus3V7Jku77VPrnAsoB0zKwOSJ3h8k72CAaG30DfdSzwTnxF6jQGd1Zr9cpF7v3fWwW8y/PBVsUvyTANkCb059CdzZO7GhcM4fttDW3er22ijNMtLDE2bWUiNdXIjeNidIRcTCssQxOMvjI5xwkR8PON/j3A4SK6HHzCLJXihvNXaU4IZNwN3XQQ/tW3FVRONnU25zkQ6+Ab4PCNcHL1Y12GF4ThGhK3IKDwI8z33OfmCwuFfomgnDdS/cCKNUXbeMhlkDgDtNxx6Itw3eQzFhJZkj9SzcYPnETAKnRiwVu1gNfphdrc/FybBngaKYbSLgV5qdyLkjU8iUlc8GDFSvT33QyPyjNgz6jntet7WYj1BbSlTqu42C7FeAZV3Z1VeVCMsCf01hd4VLmhKsIPk6q3CxF9HiO29qt9szTh72Gm3kf18yWSsVu9WHBFQoxpQTYffFmZN/Ga1IUJ16+p8ntgGO5UoiLs80OiOcHDWO+EezNFrImSczUs1QdPzJWRvIjOwa7r/jiYu/T9JJSwPJ6TJ5ElJ0bNZhjEIAeRev56zZ48e8LckSn8ZDfc/bJekN4X1e+zk+5HIRtiAwvB3rkDJUnIdhdlSqPMf+mQ3U17a3uY/qBeKKGZLC+TLXnT9Jcm93CG2bfJ5S4NL3ggBAUH6eg/sajAoIR3BKIqbvr30oZnh70JM1PTbph+n60Q8fauJl5jNth4pcBgHn5y7BwQW9bTJqf2rj/RUnWSSojcliC4c8mnOup1xW5aXg1mef7BdXGCvA8vpqDNorPJTChROBpcyhBoqyVwqHxkvfhglOKKDmPe9bJNc0lrjznej5UoJ3NNh1Lj0lPdQTRZ3y7v6UfMu3o5G8s+dCNytmu9+obLkNsjuJBZi3n0xtTD7nV496GM4Bt95q78LX/pq4/a6L8HuFz7nUwV0JwhNvplu1un5Ge2pJcDcyx4E3hZnwT8lY/8jUV0y/bBETlQsjQXOw76rxt03lEBdmkMf5G4BhPS5FQ0OAo6SJCk6hR+eYddchABDk64DUnI9HUd4U9YLA++2xKDn67r+eAIcakQVoH6+jVY8C1gTH8ypjMrldNtp8GTVUpDGqbKyYUQG4Mz7Lb2aofUGx1ZafqsMTS5dgNO68YfuhJDpHeE8fcpKByN7VsXHxpus5azXYO+szs4btFHOVupaDlETRBXYg7WdltH890qgDiMPu6CObRvCLZJTZ6xVPkGazH1XO/9GYA77xMolYigcaMUq+0b3nhn1e/5DnslY4ayEa0h4qoqZDM/3RHN2QE32W9ur3PbmVxVlxaIou0xd/qAJp4q1mWcO4khD0iGia8loUt7dtq243VpR4toEM8I/BMz1nvTZX9vZ3yNtRL6CKXeb+Ge1FLfG0sKkhsaCDEPWi89egAWkIOHm7E2EeYJf7Aatz2/7xNFGZJyXAWykJ3pjxZ8MacOuXUN90q++e2EWxard0cELt/Vcbs/XT6Tj/DWp1zMhTLf5PL0/OjzFje36TB4RnhqAKFqALV5bJb+u9xrCi4WXvLz2t7FNdlZNqbW7yZqvoR5rv3PA7au3rW6BkTYAD1A1Ud+U4C28B/+5Ef4r1+t9HG3Xa+7IrbgZW9TNaL3oL4cwrLwQmwYLLYirpWo4y8Z6JL+ArgvbEFMfxzfGsfOfrih7hVh56roBvGtviDAId8PsDww8CoY+wjAAs2q9iVffoj95T1zJtKAdpV34jwJrvgfbedcLn3aC8cZ+NCqmzuNfR7qR0s2p56u25th3sRTypXKqrly2dIcPVgGa4yP9jqvHjUyA8RcCOuvrjp2Yj8NrPMc7V84DbvsqpIdShC3/GbYEL+vocPdEEcCJ/3AmX8WBGEMpoKOdXOS13dN/HExT2F6D49wP1N6u8ESBvgrB3wFDdBWDe4+6WfS5OKBIwJmnfq/VSvwR3INjHS1XPNSNdE9H4/+EDQusNBCrgJxJwEj9BvEJnLFUiO8p45iK5mqy7yfarplfQq04KJRWzVtqFAeTVXr9yxr7C9uyp7Pgnghvriyp3xQwJiYY90CYN5luhP6GZTKN3F0e++dnQA3fOS9MJzmVIVbEm8yTesKrF0mVI+fAJEQTlg+ZO8Qo1LFKS4ayvyJna2XO1d4VffbausE//S4170DT2Gh/JfhSWi7LvrsgzIKqtc/gawGUo5NglGUxj/1Dj0KwooSy2P303/UAjt0eP+NZKt8WILQpDMChfDhFC707v2TLbb45MNFIDlsAzzsc0fruVJWjVDnIwOzdBT2haDVdr9TS+1mhqJpWFheuOHJik0KA2iIqSqj8fvlC/+BfZBBIxC+yqt5s3s5ab0pKffgUaPRWJHsWWOgI6d8SldglOVSCPMlLMH+l9nKc86zFQ9xJsEXP5zTMvEpmcT0tfWTF/DnQDAsy4KYZNMQtg0d3uanpq5p4SH/B7SLZiW7iXHYJKvQhqVRhoUKn43iLUFflybW1vgbFoOJnmXyH55aLmIoq29mU7XZF7s8gK4v8Plueo9pX/a4C/4IlfmprT1jYGN3RCOsZ0pO4wVbg/y34uYhVifuZEtOR6ln2l/8P/1T9hWsKULx4OVRCuuX
*/