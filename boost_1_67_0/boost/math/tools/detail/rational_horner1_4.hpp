//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_4_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_4_HPP

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
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_4.hpp
OO10fv4vEolD4zaL/RHU4cvrUxTioNZvwba03iTY9A1m3vRS3wSeWeIT8Ag5qrDQp/GVPY8rIrPqi360mIje7mTcU6dgslQE0gMkr5k6KIjntUufx0olshjhFwWE9zPDrxSdq/NxkmTdkGMfMxtmVFOmESCjsHzm9DYkKxfJ/27GsDTScTiK5H0xQpRWxd7FcxGeICR6idrTREgAHvXVyaos+dMAAqDWIBZIlsBXPJjcQEIKXBugMbCuuLTHidwN4BFQgeBj38I8NyAd91BHpOPZD4L8hK9XEx9eelUcGdspdftvPRC6Sku7H4wFmIreT7SYHhpGPVGJ6PkVuvqdCqSl4FVDY3haBJWpPd6388UrxrNo6Ow0g/AZfxEL8chwF2fc/hW7IMiqdrunR0BPhhZcr/+XFSGN7dLrebh6zSk7fOGm2VP4OA0eKmJc5Ynpqk9D7qL0U/OrC71vTJU5Ql0TyHKDfh0ltHfBNeQIn5nmkSOCy1598l0w+PZYXf/JWMaNFGfwkMBWVNdclkOb+bkVsU+9fJW9jD5EkgOv5+2CNLONFAPADvlVAex4AWUZjbQL1TVBU0b+ny5FcIeTEOZmRpBpSrv5pyVd4JPSMz5lifl/2xxqkz7d+dgcTx2yVPf+9Brd6F+/8tFAtkrIuqvXt+BWK65f5P+OkIiNVgvMMspK2z6D/ouilyWDfB+yfX7SgNVuqG8rN+MYAhiwPCpMT58h9qJ3uU0lTh0QCQc3FOj3V9rL0JX/B6liVBl2hcHnNSF8EzaQ0at/wjqon//Mzivac8JS2tIizAq+Md9gh/DPTWauAgDBdVPa7R/Ws2rmaVgeRAIu8GMlJD4qsCJlrvMRVD8u83oDAGUFUvzqTpJANnWSNImbjdlHkjUiYeAbIx0DzlIw+bUQZtJr1UQbFGR8mdixnzFDuH/2J/C+C1oNNoMhwp4tgWkjl5m0YBhJn7YfR822nD3ZAgM/P428sSLvCq8Xo7gbzotqGhwRo3sE5Pk8MHoYAz2J2nYxo6UnpgfR8uRbv4eEgjQi4K4Us0puc+lprP13TpitXKrEbm64G5OdhScHVg6gYqYioopeBfi/dqrpNzJEMsuJKw1cf483njZu35WrrjJVKKkfeRLuNFmKTCFhEBOAHxkVAbQzOypS3kmRT6Bzshpq7UntwiU3oigydulOX6vbSQMhXZXomku5u9nY28iEEVvK1zazeZtTLEO2IzZKmnJK9MwFtG915uVRgfHwlDU4VvYqIMa0AfVQqN3VDVzZH75v0uuFtKgoDBUaI2vmSpA3zaCL2ryN/7JMrH9rwenFSKKGSibIacCg/ANzgRQ2vEyNFSGlpcSVvkHcbdiwJm9Q51yHJJT2lJiSRZa7ottx0BY6UP+77GUiKL3h/JqY0BvHP9twj4v7qfa2Buaq8a3Hn73AsuoIWN3vpS3mJU7triA30UPEnh5C1wSf3V59aQRwBIJHogYvIar3QJoFtnvdfLPSkh+nHR+2YaUedXLOTTYhMDJfM4rsgAJ4BvtxTPqt2nzzO++2u/lClEmmSllC8Tbrow5GjU+GYNVNtfw8JFtPhH/LqlcpuIz/HxGA7n+nd/lTmlI9C/HRkleNZDKsGgETCNS+P96V7Qv7d3VYXxi9ttdBU6EK7MGnJj3a1Ujm88YwBJnfmquqVEXikIfOq1f71IaPCIntNMcCPUC9zGrEgJin+PE/NDiHH0yAokyDBUxPBIm0IsEevNafBJVzbjSUm3PvLojGU94f9wkTBQ2gkadB2m2ZkYKNfKyrbWLWrct0Hq1BYOAKT0YDAshhdCJEQFICi9kRoqCmkAEMNa7qkCbGfjAfFgAVkTYAIOBQQG0qjUo24kSSzMTAumlvaJxw6Trjs/6F1hXgRj1CluekpY/48V9MzUxYZ4DXKBKVg/hwLer4oF18SiqqpMXwKyIFhh96fF8G6ZrcMMhZ1n6cxDLEVQouYiZuitrxS1pYg3o0125rtdO94umYn/jvO7Y+OlFzqqXncGcLv4n3cdSr4eCSzajXVi4yrv0ePgpHdyMdIyGqmBeqyuM7eerlHTZsdzDKMsxGR/pzv1rGI/kcddebvVKS81bJP6qrCASRDmgm+s8zKRdXGArA2B07FN6eP6zN3W260z0PENb8BSIdfwVmKLLrjiiFwycfFScPFR0d9xcpf+qPY4JYzIZ8me2IMbNkWlMwlwy4VphoIoYD26wODESgIQJhv5YaIO6oxWgU9PwPr+oNwgJyTHsTh24Kd3+Jvv0zZoEmaFcVqtq11SMLGryViEOtTfNYZlxE0E7QydA1fnCaoYf7UsLtU7tPT3Q3t7nVCAYmGhoLCuPgw1c4cizqJ72woKQT59mLmm92K6otLfWyC2kbStIlezz+ROSdTIQocJWX2Eil/L5SdM9o/vB9eIzvpkFAq79m6RPmnfH3f0aei6WPmhkpoPUga0gJMq4l05OKIoKyNmsCMcSkKKehJtimu74ViYdQBg4J9pcn7UMe/4M4fgvlwrX6Z8tlXj8HqTEV0iE9yx47xUD8nYTvfsEaZGd2e7aLDu7Ao6glQgDk0F/sxHnDlKJmFnLvLy897WBX/GzDAlqs3jpVqlDzdHiJWMPRl3GKDh4fXrkuVUCbsHZnGG2gl0dhIIhpbQM4YQFgCMcwMNlcpWHjXF+BN0CaaR4ewdXAfglwqHH4ZFUxbEOKSaNaM+E9K1HZjID+gXk0i31FzcCie5vakwaPOZN/k6Dd81teXUjeaGJkoEScmhoQZImdFeWs8cTjoQ0fyPcw40Im1AC8l2bwtsMsnBHgfVTi7Ky9sVKFz+EpplxhwfW9q0nppOMwM989loh9KIlnkRFXVYwIdtilFHM62qn+xEAAxRMIddvpr7+7XUN84j3Zyk6ngkK7k557fMgxU6Ue16v667O9IIhsPKSYEaRjLe9iHLnxX9qSXhF+NAzE/R8TYt3vEShuw/rnFEEY7GcDKB2tsTeX8fFuBytnU/NQV/vDafuvoFxvcFBOZ+68Gv0MUB65hrr+nt7rsiDpFzS2yqkSeSbUTxcgsAwQL5yp4xs0A/Lcu6stte+GgyaM52r0bsUQr6iVvlC7TWWlP1jgtJkHgACAQ0sBAID/f7eZYEeX0TxRyx1myox0FiNYm25u7w33Q32I1K2xGNBy0HabsviTwv3phA5uE2O5jctUl/8qDvLBU+sbZ9WaKQovs3kWp2tKacuSqrvN+81cd6vKEd7eInXln7TWB3wfDpgvhKQlFO+9QEU8tYmIUGl93mP5Z8One4HyLB7lLqoZiagKMPV4DY8wlKcHx3z5dcxK5n4bYfLDuZbS0e/rXuNWCFVffrQZJ0kKwdZoFdqmn+e4B4d3tRwSCnCEo0NTQMMHQHVw0KcwABtQ82tcGCtbCJiuGiiUPyJnmF5A7nqJpBnJD1fMbFAy1MsT4BwxXSyfJYOJfsQBjX8gVcuChjRZKVCJpEKvmj5Ht3B5kB8OAxAI6FEqsEYlxo13ZegdRVYA83wKkhAlbi4iYQRAFB/lznty15nt7wdkSrwjdjYGPbPJPuRwxiAPDek+Pgndl1IgF2gjKbzS9dptD0XeYuWKULZvtPLuG2J5LQ77sprVSQ5DU20wZaNRX0oGZhsk6IIOUF2Jdfk2KBvS81x4rtoiXmB54T9TgJiEMlQT07xKmnpgFK8JnL3E/nxE/6anRGPADtM0U+2y7stBxAFBmvmucl+bqYrp8oYhHI7+Ov4sud+N/TBWl82ZmdfVyPVuiUf8qM2P4aAnHoGsjtaVhB9l+79iGkmZH+BrUnypvokZUKRWVqSAGXsdF81WFJUFFTphIl9v+4lvzONYXBJgr5S1bhMG3c8VF2AnmM9JaZmRkpHYH/AE5+ae0+rsR6U3+OeGh9o7DEbpJiWsJa502PjTBWoFHV1093tqodCRku/S769Oxz+dGFKRu+Tr4fS8Dt4k+u/O9bMqvrv/lS12R0Vk+nTy9uaVhY2VQAbMO26W9G/MH6ThoXt0auTSPrU4S+d1290/1mrW/TYGZQ612eeCoKQtdHibUssmJq+OhaK8s+XX/Pv/7KgaDPracul2Pvv+YxeFoYAwvOHJWjjnjrIx8ScYo9fXBUu1pRlt1xraQ1ZSa4PLXwfPLgHA8+FcAkHfhcqRZyKDk1VeSHqBqIkPmqyRpsHPFciCiEV7TnbeTfRgFAbLjYgz6U9Wmnwgr301IgxRBxExQTQTPtzJU6CmIcq98QFKPFaEXoMhcIKLDExYnQbMIHo0nsazvbwPO3pmOgRnm2SHovcBHLU92x4Dn6RZ+r/fa8SvDuI6vR7JTeB6ejVIYGTQAmhf+2WUPyCAIdnB9WwmzvN31zjmDyIXA4A9P2rtyRYvIskPzHx8CiBAEwBADtdWeHomiQpIZvIsBNTwNzaNjAH3F16FlQ+maGWg8xqbfj3XA3WzJYz1Q7w1ugMjiSNGp08wDY+LWBvNdepcCgbkaNk6j6MW2yTrxV8iJST4DfeHK8QgX2cfDoN3Xldid99b1bpZJd0zdwtbFK3GRPWtFsV6VpDSeJp8ZmkzTuLLM+iDjr9dNEabPp1F/pkOHbmOzH2+mfZo2CMY56olFQwVT7pM+JtS+Ssnw9cry34aWOh7NIJgP6v3apORgiQpDOHh1yjCkk25W4DLxB8fDrzZZeOeIyWtW0ibFkr69IMVS5/fP6bR6+d6dtDJNaQQKTZG+li0EdZohHQwiUBEfdtK46zhqxjUK/O55Jm5khv6r/xJR5n/rVa/5ZEjRulNXtiMP7tiPN28wO/A1d3PhSDrUU/sT5sEJRVhvSIPN4hW+ZJoG8StV9N1JdMEUnK84x/jKhL8HEe8PflzEwVa3/HN+0QCunaXwNJrG9QVuM9AjQB3CuV39DIf2C736tNay+U+GxXeeL8TeDDD9ZaqzR9lgnCcfNl4cKKs6VXIH6OiqIhxKZcHUY2FI/6vkMhS6A8jqj9UoGw5hCOKdvBuOiwX38oCFUAUAX/wQYuY2ny2F/BcDsuf1NP4OmPdMSvxJrhaHGKg+yFwDin8L4mKIGS+0eDSQ8tDE3NxdgrzMFDf1PRqVmQZMPFyABIgXDDJaEOrzlnI8PM4EDhUtw5C1jdIj6RFVKuestiIpUUoIOMXuifAU3gQS9OyLZUj9wa6GcO2YPwUlHPbGSNPwgLSyMgajY8Op0Hne4+lrmHPmC0LH3pQHSIoUrZ1g1A8ZX6US/DSIyHN2fDjKR/DxTb5H0lokM41V/QMJ2y1tUfqEKhIkRAZxGsWX9320zK/eMxx4crEcO7hjw1vOSefBMexlqr77urq8/7+VkKZP5qckUl29ATJzBBSULJWUnRbrgdAoiMxIs9sgM7i/3SLDpErbmiBMT7TGNUuGkNvPE+av864PxXqpUybFvbju1fxK99RZ39xGKnXOUsZEf8iXciYLVOEw/Swl85u/ZSeXPMIU9XY2wgb1oXHW/Wzheq1aqoTWVZEuvxvZOPBfqI/qdB5FMm/4q7w+x6OkhBXjgRXWofrgpyvIgo77r9izmjiPK6Dyo+8zUfw1F9o7goHj6jhVk+gvIpJgLAAxy2lNLjIXTRXeJQBEgofxQ6jJbkS5nqU6sPj9b7DAcYuGoFj016aXkOeDQmARnkF2G4RNw0aoAahe7vqEfXdIl23P7N87CcJ5+7V380BHgBLGw99CxgEoFxzOMorMg+wAN4zBYziZElPWFkHHw+HE5oqCSCGpzMqtuFTEA7HiZUJkJupkymZPIFSiIpQkF9Jpo3AnsCMC5mVtcfpJFubDYsGtgHrzHiT3vUpmftOy++4pPIe95M4pNBXGY/kAkv0Gz55g/vE3n3L45Ods7pRA+rympKi3DQwEvPPuDr6w9rGzMuHsFM1LmTcfkd5GZU5nBd36qoMvh1/lnKe9t0uTZ8v06bypse7Wf9ZJe+eu3G897rCDKBhkh0cv3vPUD4r18FjdOdSwtnV5abubt3x8wPxLoDbLIX9D8jOWuf9lDH23N8kPS0MJuTN01KTlsLw988Lv/ShZLTurXTCbbapzLY9ZHZbeO8ehzlOjukfX2sKq6eazGGmC47vrJtP/a3UA49W3Tbro9xWRdFnn8NTNs0UgoE9K41bNg4b+/kK5N+UirWNTDwkz8KUDp8Fgw7zOYiszWHRbSI7bFLnrsYftUN3HsaGZogju0S/bfR4O47HbVqjs4Soe6xCxTkLmpgx9UpBq1QlguLOo78tUqc9ciau+VLxVoGABUtdPBNbRKWME+dCQtGiPHsge0DZxFSKxykPGLAXR6lJ++Ylx48EAGf809a78oiFowBZw0vApHJ4Jz55ItJaKJTrw2MB4m1mOo7f5aR1IN5K20mosqsq237ZGevEp7DMFVF+Hspc6kEQl0h+EmBGEPlbW6oOvdbuiy94z74OZLwKBUCBkYcbQUwA8RUDlpDdAr89D4epPuI8JPibLSJLmvw9xnjEoqEZENQ8bbmCZC4dVSuLWLfZRkO/ytNXMCNuzqZaD2nv+xyRhZamZ9tNRSzMjax71nv77L4P+kXMHNvD/E1sX3fyCmU+6y8hY3VIrSOXv+8q0Lfhn2AhoYHQJzlde8El2AExSxOe46YnbjaT49mLZN4OEi0GiO65b/l78HtwosazcZKyODjL/pEs4IxczGzQpeEPTN4tvEJEppO5trNKa2hKrBIs8vIgHQc/mm6VbRfMXfIRPL8kg5yOKu488uXr/AAALP/T/wEhP9RZnl/P2p8dRDFprQvcM39Wb6p6ivgWZxGiE43iESom0CVdHwSaaaNIqBmVAy3962TXHqxp4x5o7E8tIJo+LB4zflAHe2nOyyfXXP38g8/eXksOJ0KIVdWu6fHTVt+ArAFqsoP7RSE9Mrk9WPukoNIFcLhRLuqSDxNxKlizu+UHm2krQsm9Y/VHNQtYNBiW0e4SRMot9YXZCCjKe/L0gRBQfBA77Gg3USIQBSFXJEVtahAIS9wDlVq9l3eOcpwpb+4n/JCy5Db4suSOO/XZEUZuG+7TT8UoLbheb4+9n9URsyEEaNfehuB1qTjZZbdo7ER1yF1ABFAC84kgY0LA2T8oH5KZNmRFdbA0KoDQPkDB4Et4FnhsUB4WPxKCxxfAHcTS6xm+6IPDT3WC1GvzHPg2HZVSju3ib212pOd7/dWlBfxmZU9Ok2Euq/oOLBLrAGd1rKMZK9e6hif7D3/0pKOBeruSvOGhQhBgn+ziYpdN2edqPuJjN3qjMR+/QCHv1UcgFp5LQ8BISb6340eYvrLahtcEqBgBrzcg6yMl3d8J77K57hwON+r3pa7rsrI8lfzj3nEadEZa0LD+8OKVyicH6HWryExX2M5xS7lH73qWo/ztxrqahzZw6L6jbocHrzo57O3CGo8RqxRPevNhHZX76LkVe+m+IyI00MPhFXRbrbDHthD+PGqvzEQ2GtUwcniuR0yU9LDG3/qcOx3ihzBf0+9FG3U7flfXbQVVx3dd9iSrgYeFL1LAUggYQYSW0ULdV61OQhFOFr+LWIFlvgoUeqoimIbbZuhVrsQOZUJv4amgNYWbPPJKtaGaPusdGHE7CWVJADwQCSmWd7HMOnpBhC+JGY7Q64QS7zWQYUWyBlEAbUyqfIgvbeOv+hkGfdrsvXbOxz8WhIpassUnj8h4Gxt7VQEI6IgVpwe9Hg8IzvEy8hEbhG5BXyHnXvVcfL29YxDrNmQqYdj2caCjhLXIOWLGCUWlvI8kma94K8nHCoQlU1ixBcAXiNA53vmIs+okpcEL1r2KHx/zLs9SIzBJPsaez65Nl5G3HlF1/QCmq+/v6q4rW1x+qrdWzQVL1Yrcfvag50tx0pXUc8WaZcVaQXP5kL16gfwTlXtWlD2n44TUvZrmUUlbBnOF30MGs6vP9ZlgtQr75JC94Pyl1WrW3BcfF2dLdkzcvYI1jEbhd8pdf/jCEoUgnmOvWndQx3QnVCp/CykvONIUTjgTKrOMovIEq4JjSKhsCZQ3QTn/02E0t7uR5/q96l272Xks8/9Ze2XgYpWTEx/58//BfC/ZU41fgfJ6gOHEOd7tQO2xjb6mDo3IvYfqIBFL5w59RtLIMTTQFE35Zv9lEGQV5DCGM1BW3WjEc9q4wV75iIWATH+OF70MafFrHSAdJ20tf1UviCegoVd2ezhRyi26HRw02k1RBi7tpEf/EtpgT7AvYy/mKS6TNoc6YKZJijJwpMT/0OkAgwd1gYuEj0agOJCoTbAz+Y0Dg4BIpNXeyElI4OAmDdNiF2hIpQ1eQCe/8ptJJq+EyOxP1gVvdO1rav/noCHQHjNLwPui/Ok4GAxgPGA8hZRgVxdKBN+38U0oAEg6HUUR9Ehrew8iuFCTRDHrE82W8xEKy1IrKsiKW5VIEIplNi0yR9DFvhUgj8WQzAJJKIZ2g7dU7Nxv3CsDtg7Fi99tPYpVN3UaYDCyjDmzh6xOqlT7Psl+YTrJWUXOoe1ZVgJdGVu7dgUVcpf7/SJd9F69OSy+/oVP31Ytgv1nbU2j5T/f5y1TeqVaf4C6s9CXr3bNITSjR2M/tdxzr8u0npjNXr4/P99B6/JlKsTMQPd6sbHS1OkRi7kbNLNFdd8I8HDdR9JZcYoUohR05pGGsDXQjVr+hAXmPq9wv/NA3ZZVFb0aLl1Fu6//Y3Muwr1nCwKQit809lNYYFqo+hiSE3DhvQY5uUk9HN9utyT4pA2GTJv20NM7zD8PUqV94O/8/KFU0/YvG7Bsnfj9TpC0ktpW7pXOEyq/Fq1ZqmZfYSLaDdv1fpBQ9hwiJ/pDk01dBe4h8cTzsAhEGASOMU79hts1O2Et0ENCmBOiaJUQxg+K7w6HQVwT7Txbq8j44SoOVpV1zDHMZNjsAwU0d7XPcOJX/qkAYlhBjKl8Jz1XFdlmXnCmIRlBgvGewN3thv2DKikJNJQoZ6JsUHaXBQn7sdmzbf+kC3PpVFmQE3m5TFzlc/MJP8uRHjAW0G+AjvVKIuUyAobaPToD+u8pMov8cOy61dvt8bLqpLCR7K1QdPej334RD8EL5YTTqdvg8CXqx1stYQSIfmCvO/K6X+ip9u62MTZGmWX947BhpspQXXRdtkrVlvksvDuOuSOJdt+u5X27QVCy7T2Thy8IcK3c76C1QgxmcEX4MrpY5GP/b/zRh2I=
*/