//  Copyright (c) 2013 Anton Bikineev
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This is a partial header, do not include on it's own!!!
//
// Contains asymptotic expansions for derivatives of Bessel J(v,x) and Y(v,x)
// functions, as x -> INF.
#ifndef BOOST_MATH_SF_DETAIL_BESSEL_JY_DERIVATIVES_ASYM_HPP
#define BOOST_MATH_SF_DETAIL_BESSEL_JY_DERIVATIVES_ASYM_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace boost{ namespace math{ namespace detail{

template <class T>
inline T asymptotic_bessel_derivative_amplitude(T v, T x)
{
   // Calculate the amplitude for J'(v,x) and I'(v,x)
   // for large x: see A&S 9.2.30.
   BOOST_MATH_STD_USING
   T s = 1;
   const T mu = 4 * v * v;
   T txq = 2 * x;
   txq *= txq;

   s -= (mu - 3) / (2 * txq);
   s -= ((mu - 1) * (mu - 45)) / (txq * txq * 8);

   return sqrt(s * 2 / (boost::math::constants::pi<T>() * x));
}

template <class T>
inline T asymptotic_bessel_derivative_phase_mx(T v, T x)
{
   // Calculate the phase of J'(v, x) and Y'(v, x) for large x.
   // See A&S 9.2.31.
   // Note that the result returned is the phase less (x - PI(v/2 - 1/4))
   // which we'll factor in later when we calculate the sines/cosines of the result:
   const T mu = 4 * v * v;
   const T mu2 = mu * mu;
   const T mu3 = mu2 * mu;
   T denom = 4 * x;
   T denom_mult = denom * denom;

   T s = 0;
   s += (mu + 3) / (2 * denom);
   denom *= denom_mult;
   s += (mu2 + (46 * mu) - 63) / (6 * denom);
   denom *= denom_mult;
   s += (mu3 + (185 * mu2) - (2053 * mu) + 1899) / (5 * denom);
   return s;
}

template <class T>
inline T asymptotic_bessel_y_derivative_large_x_2(T v, T x)
{
   // See A&S 9.2.20.
   BOOST_MATH_STD_USING
   // Get the phase and amplitude:
   const T ampl = asymptotic_bessel_derivative_amplitude(v, x);
   const T phase = asymptotic_bessel_derivative_phase_mx(v, x);
   BOOST_MATH_INSTRUMENT_VARIABLE(ampl);
   BOOST_MATH_INSTRUMENT_VARIABLE(phase);
   //
   // Calculate the sine of the phase, using
   // sine/cosine addition rules to factor in
   // the x - PI(v/2 - 1/4) term not added to the
   // phase when we calculated it.
   //
   const T cx = cos(x);
   const T sx = sin(x);
   const T vd2shifted = (v / 2) - 0.25f;
   const T ci = cos_pi(vd2shifted);
   const T si = sin_pi(vd2shifted);
   const T sin_phase = sin(phase) * (cx * ci + sx * si) + cos(phase) * (sx * ci - cx * si);
   BOOST_MATH_INSTRUMENT_CODE(sin(phase));
   BOOST_MATH_INSTRUMENT_CODE(cos(x));
   BOOST_MATH_INSTRUMENT_CODE(cos(phase));
   BOOST_MATH_INSTRUMENT_CODE(sin(x));
   return sin_phase * ampl;
}

template <class T>
inline T asymptotic_bessel_j_derivative_large_x_2(T v, T x)
{
   // See A&S 9.2.20.
   BOOST_MATH_STD_USING
   // Get the phase and amplitude:
   const T ampl = asymptotic_bessel_derivative_amplitude(v, x);
   const T phase = asymptotic_bessel_derivative_phase_mx(v, x);
   BOOST_MATH_INSTRUMENT_VARIABLE(ampl);
   BOOST_MATH_INSTRUMENT_VARIABLE(phase);
   //
   // Calculate the sine of the phase, using
   // sine/cosine addition rules to factor in
   // the x - PI(v/2 - 1/4) term not added to the
   // phase when we calculated it.
   //
   BOOST_MATH_INSTRUMENT_CODE(cos(phase));
   BOOST_MATH_INSTRUMENT_CODE(cos(x));
   BOOST_MATH_INSTRUMENT_CODE(sin(phase));
   BOOST_MATH_INSTRUMENT_CODE(sin(x));
   const T cx = cos(x);
   const T sx = sin(x);
   const T vd2shifted = (v / 2) - 0.25f;
   const T ci = cos_pi(vd2shifted);
   const T si = sin_pi(vd2shifted);
   const T sin_phase = cos(phase) * (cx * ci + sx * si) - sin(phase) * (sx * ci - cx * si);
   BOOST_MATH_INSTRUMENT_VARIABLE(sin_phase);
   return sin_phase * ampl;
}

template <class T>
inline bool asymptotic_bessel_derivative_large_x_limit(const T& v, const T& x)
{
   BOOST_MATH_STD_USING
   //
   // This function is the copy of math::asymptotic_bessel_large_x_limit
   // It means that we use the same rules for determining how x is large
   // compared to v.
   //
   // Determines if x is large enough compared to v to take the asymptotic
   // forms above.  From A&S 9.2.28 we require:
   //    v < x * eps^1/8
   // and from A&S 9.2.29 we require:
   //    v^12/10 < 1.5 * x * eps^1/10
   // using the former seems to work OK in practice with broadly similar
   // error rates either side of the divide for v < 10000.
   // At double precision eps^1/8 ~= 0.01.
   //
   return (std::max)(T(fabs(v)), T(1)) < x * sqrt(boost::math::tools::forth_root_epsilon<T>());
}

}}} // namespaces

#endif // BOOST_MATH_SF_DETAIL_BESSEL_JY_DERIVATIVES_ASYM_HPP

/* bessel_jy_derivatives_asym.hpp
6dK396aVPpGtMcuXThN01Z5pX1NhFLFsFqXwUnZL4KL2kBwfQEahw/+Ip71Z6Lk1tVaav/59jPLfrWta6b+YnCH02ZCL8pgTMJOSVh2cQ9YQPYSrxuifc/otp9IIsSLqlQIc/slzFp7G5aDHEGKJROBVp9EcwjOORANxEpwoxKtKStc0M6NLV16gSjEg57G5cBCNp+F58vB4+FE+IqzLX5QnWvFnG2lGk+MR0cyLyMindINnG+xYzuP3HiWkd/l2SFn9c4lsXySPtoZyglHyDRfNF9qno78k/+lFcuor58RfV1faIqvIVU8vL6N3Iu6OaolVH/Mjcm1OQRIa1Lqnmfc8bH9hKEMq6jsdERn0d8sGzLVUw9kVN1VSTIbgBnrDrIVupJ47XOq0UXBww5tbpl4kvdU2OBdIcsf3mQ9+Yf9Mt1l/z35QLqfNhKiKspcelQ9QXsm/mqlbxSlKokiSp1jDXsGw1LVAtiEknp4RmaWIXGHq1E5x04etqREPvjXVasZo6Dko3OJBc9auuOa9/OuG/TC/U/mowgxXv8rKOuCUuj6SNsspCrWUe7lT+avWuhAg9xoli4ggFMXQeL8opOyHETqJF8bU4GWJ6jNCqLQS+cbUghXZv1pqUSYfOvovRXpxvXfmIX0Ob163vDUhjTqoXV2yQ+i760ERQi2wpt0jMSL1OnL/qDZVJJ1zmJ43NHmM75zEY1FRe+FOogJchPsGVN6uuseJ52FLQV+Ky1GkoL9jJ0Y512OWtQLOai983pyxxBMpJkMfRMqtDw6v5ErFBXPIG/HCCW/0AXhpe52AuXP4GM1TIE+6qWHGXbvmKIbiW7m50rDHBSGFiPuy1KsDw6YZHT77OxekPJIrOmmVqiX68kI4lKNXvyuM++inv+1rQx/uJR+/2uljqt9WfWVCOdSaQSli/HTH6Ehl6Uxg3O+4/tlI/+u9a/HeUcC7GzkVCX7Nz3qZyIHo2b6buo8PwFxLRdBYOVtm2Ir/vsPrXcUnXUP8+LmpZrS2fg9k6rn5+aKTPEkAuHeCkIYzYCBffZBFibWPkWqaUEL5EGAVbdqj+c47q1z3lMFUAO2MgPVbn8S8KWa8PgZ2DbEshSzraBFy6tVv5smb83c++ByABlvK21trkD/+2/W80AsPRbLmOOSL7IITGC4z1+dTsLZu0y+REkz6Q61xwQji/nmJV9mp2alOF4pnsepnVrCB/3/BYQIyblQAZ504uoBoGQc7lxhh/IkKitH0PJUHfPbRNQxvSxaAsqtXCJqypzXAyWz0fOgnPU7u6l59kupg8NdSri+1+aWvpouPIknPckG81savD6jgZ35qCzhNWp1hw3jsYkPNLX79J3a8LwsTBb6rYZhPr+4zKE+JfPmepu/Cyteujkb77jHUpIZ1hHDqUguLktLfKSE3HEAUNC3vjt+0/Mn8dyyth4lSc9Cuq+ruOEf5w9Mebc1SgjTONYICdcsmEYPrUrciUXOoMb7sz21MxGBcWhFslmKFOb3cJGXUrNfUCN2h7sWDMJZJc6kjKxMLvQ4vro0CdwUZ6Bgk6VcXowqegHOhLHJcO7g9SRPYwyLYxCb+tlNa22WKCIVmGhef8m3UIbk0f7+hgG0IvV4R8cTDp5vernviNQ+aX4XaaijPZ/SmSudgVoTd+JC2U9N44kXhxvqMzSGgeaqjC5C5ysI1Z/Tpek+cPBJ3od7xvwTufFg42ELXB4GHTHCrFCQY7xziU/ljctBy8rhgYx42xK4GIbX5+31R08/RqCD2ozCdn2jh0+X65Ex71e2yogv2Ju+WpwLDD/l5o25Ngb19p9zRyXuvSqtyMkLP+TUr4K23Yfrr63N+tTkanpQoCSZTM6KYvvN3aTcySmfUWHZpXcep/aUKwkm1JG7VwSBEATKbCi8+FwMjZGTu8r6vNnIiXeKAw5jtmBnnImAcVm2wGLsvjY3M+p0vEvSyFa9sTqmY57LZbmwhkOBSgMGdO95NoC3U0r07x2y5YlHA7xsxdgfQ2Ujpz8uXZFAxSYEw9F/s9ShdmgikuhjIr/g+kSTZTBU1PzbCQmse7MBY1rjdkHrhVQR8Zduqdv5X4NhD+91DaxQJxd9eNiTd9bZGTW744eVumMYa7yfhY7c1mSCwRkuwhPeFzOfKK/TZ/vBoz2LhRCjHoNSRhaoijYoKJFYZHU76e0wMuwuxzb1qZJ4UzjrTI52/CeSLHMYF4DSIQgJEINh8RQ2r3Ba+iNMFIWk5FIYxVW+E4DcwMGu9cJCee6jRxZBYbjgoqoi0ToI3hwtkdexRG3QSZg/DXMvUdyj/FpQjbwT82e1mQY6zAqoJNzgI79VNKSWz5e9fPDE///r7ICTeVE6bOuVbz+TwBzGFvFfcnuiV2TE9xj5v65ogL862MC8TEI78+zDsnb5Jat8zMdv3LnaDAtAxfkGAj7RdWfD/hgKR1l8bHHrDppKRbce7wEFT85UtdlI77BkO9JKxsdjVPdfQvhXRmch/L3e6KF8pRew98VtI9m6ZdRAPi9HP0kqQ7Ttd2LHYHMTYsSXRaDMT/+qZHZicM/k5Fqg0nA/jaVNcs73Dq2jiBGvtOqi50VR4WEFtPbK13jV5TcogOU8vz39u4lHUVy9FYKebRkry1K4pXEcJLgSjzpR2hYllXdsC/1jOrnk6yjxhu2WCgzN3W3yVUajkZtfCGkKX8tSxwCDfRqQF6nNwPN7HXHywg0+GmLSrExvS8NVqH0f8zQVMTOCEN26OExuNpkxY53Jlqj5tLyrt7c5sZyAQpgJGYX48zw3I1I3Epf8XQrDrH/4PIQw3udbChtRM8pIeXTEet6nfdnKsbX/bMHtraHj8OfeDkU9dhk7QQRIK3D9qn43CQF2BGy3wLHGQPhATNuZcjT37u5F5P6nGjDd333Oa8MG//nfyGBAFXoNJmhp4viJF2xrNqeNnNWZF8qDHGOL4JB0Np6KvSv6NVnZC6lzvn1l7BUjltWuO1ur99kAMEmZudZyd8R+HCk3lGunkciRDVg+HAPzZckttgX4BxmhkOIyhHOvY5bJ1Ciws/Q+2SNtA5SiyiQczjFQ2DKlOHkjl4RYUDuQ+aiGjBMI24+u24f7orNn91HP/lS1GsR7jPCHx7aUbfhunhObO845YZ/6kfVg0uk4vv4uG131/vvtTl9Svp+vjP0h1Dh/7cfKdK6WPnewBGROjDwC0URxUtc4i6ulLV19y/D2Gzx8+ddKfryJGF66frGVBDzs547X/70aOQIuNqB1gSBfdmv8aFyr8/q90sX/n7BPkNCFftPg7CHhvw8OAofvvjX+jisfXyViu+cUDX53+20u/ftL/bNg3zR3s+ttMuuQKsxYre3+76eLP/8xgCHW2jIKQjf9bfua0bhazjuW7azz6K/SRW1AOzBCuTbnyJsv9bMrln9PNFcob5iKPawv8UYcUNX5mJzwj6lLXGp3dX3WlbytpU+IUV3voLv73cQ6pxcgrj0a/uxi1/3NidV7XZdTCGRFCRGYc/xV+kHKRFhuJYPcjAXIO6OF2yetRVbrLFg+Kq5d4xd4lX6SEeSCapuxleonEhwh91vdEjUbNTIJlJyRZqcneFAGou/mn92A0ZvIbqjYjtX/0B7/4UcDB3xrQ84nzVvtlGMEQbnQD7A1nIN0lnxYau7sKj5aoxf8oQ13EQWKl7czXqjv9Evc/pqH0/8iNnehPK2H/wtdSlXsPiv0GS856yxAQXtWHsUeLeXz7SIjVbupsNQwu49+9oTMAx19AQHGYSCApDxxa23aEErIPbE0uWTZGFMr++gZfpqPcjeG9nX9yzRCfaWtPqWgfJoGCB3O+7POxyKcyfTrP5MJZ89ijvNp7EVrP9mAbtXNX9fvHfn1zpFp7L5EfkxNU4ZcwHYWRGmvb5RiwckMk7RTfq/+vq8tCvp598MxrqX/RUEUPnQmq8cIsDDZ6ssSUO4k+QjM+AUrNTbbeRhqs2y+X3f2zMBjutr/LXjkQnF8vK4BmpWZ8648W4wZRjNq+o//rARSO9eKdz0izeqADNYhXzjvDhGwMkLTQHIcRqxiWX2iaYA6PFlSIzI0kp4bUW575VUs7Dst1mpa1N+NtKYEW8esbk266mNd0gPFWDfA5/UHblRJx1GU3JJ5/ZTqwrlwdgrL50EpKJE8XUhHF9cCE0ufyW3+vZ/JTrHHUiMC9Ot3zDwHI1aqSSmqSTxUSAUcCw0mabsI33kiWYkmGuq4Bz5EDzX1ZDYjJMGFdMmvnyeb+38FoBn+yGGLvPehmfGuMjNfsI1fNxIUPWXXq2UZjqCFh6LE8UBXTW1DK8Eg6ecOwVnprq8OporAQ/vNn0Av4obKfA+DTUSdDilz4BUdrgP/OfyAiOaPKk0OXCMGdOVmuT1SG9WmkaP1yaLE6Mel1jf5MSWfgXUK+7WbDiZT2rFQoTpc5k/aL7mg0OxdQtnU496SgbQD7bydHQilTGMWB25519yea+gJrw9V/lANTR7Yvdl+RE9+2gHpzFjjiTH+yGxSO0A1F6KMkfUPZYR+G85nmERmMad6vsn+wgnRuI4iO36WO+IKFgjcK6hLcubWrQLs4F0H1nkq9WvFmHmova2Q/kV5xATV8PPxRiHXa4vcw7M0zYrA4/wn3vFmyjycf/rgHqMZv68Ydz3fxnRmbc46GI4FE2oyoOgyCbOY6GsjBl3637edGSlTh7ml1II0zUd/5c85FdHhJ59X8jktURwRDGomgNN9iT1qWSrYLDhpMl2YIqXtrbCSW8xZ1FVV42vyZeRGobwV2VNH/m7aNyAxtxZrBZqxzgvR2Sv4DO1dyB92lFrwSd85J3H79JyCNXMzWDXw22RfX9Ab7F8f4lVLs4ytSgXp89e9vk6RLU1rUh6M8/+Drp8sq2boYNe3Nv/yXaX8QjmqVZswlyNqG1QFx8nQzoG+yP4zFt5FB2hjCdDyETjNVRNohvfyRHkVC3TzDwdjsB5HbwZUuq0bnbp+Y3LHe1ndD3Jo+8WM8Jvol70idq283ACnvgG/Zj4x8/BhO3aX9Zm30cPTUs/N27WPas0qSNxJoLEAdPoggr4MJyL2OuypAqn399UwUFVOnvW34z36P9i411q7HoaGl1mw1NUqdrcMGJ3v37QhoGEORWV65LAeWCDgtIOL0A+qzlyqzerpxUN1Pz6tztcmIMUJvHjDBFcu8r2Ae2vYttb/OpYW1jPd1TKDcBgHDGbgh9bodfjSiZ4DLRzQZcEY/tqkp78x5vwV702J/8v1qOmtD7OpP9SCsNcqETy7Q67tMMHqc+CaWwnVZpTwo4LePyQz1QZ5I6Vc7k5eiDMgRag7szcZf7acp/TXblHm5FZwjkJppZd7C3mL2Nvo50p4B0wPW2+JQHQU6SsUtAXsHxovNdw7mUJGdvvYEfbt+vmaEACVbZClex9HYEqxBE6C+CShpAz3IaG1bWUnXg0R/18ysqVwl6jyXhMXUrisIAG2WI7nuJsgz2aj4fSGCgfQWAysMuL8biY0ywcRgBny6MXjZuPMsN2pUsPWWqVoszVgV4pLjGU7HepmsyVGHrylP10tOzCnj2LTAqXAgHJOuQXKp5HeP5EefWjlNn4lhEiNtryYiaG0H0DOHffEZTFdh8yBbS2C+OmKmdkbe7J24uhzFpyY3/hrJfwchjTYa/nrq18DpezXqYT1BNE5O1ntgk1Cvyav97U0JbweKdNjAKmb1uqM2lTyydxfpCAXKEOwo3nqFOO4aWVduvCLC1eNh4+zS09Qbyy9l6wOfa/qoB3/WEic2nnaGezkEJ+8+kkWf2r+0ZSpj2APAAu1Zeu/tEHoHAcvKjh6gqRHx6IhKiTkkBVeNdBk8boMwnoP1iQhQe9lPOmJovcS+lyOnb9l+zY1pj6mdqVnrbVP4uOnEzIM3/EJHebPiuAW85O0rVQZzU+ZBh/S4NrTclcwAaXyiHMKfJcS+eQwbSybT+ilRdcPRCUttCAxt3TAqeX62/lddzdSp0LR1Y9CjoBZPcBaKYQh/56Yb94jJ2ECTDUbHbU9Hob8DWVmKdbRO5VCrcUl3PnbHPqXFqPfZUaE6WoEQ/oqSSoHUIFge64U4CPB40mj/erZwiKVnCyKo0j6ks8hQbMSBf179yCVvSPyZ3HG5JAxBSZMBJLvJf3zXdED6Xvu4Y9YQnLY3BAMzDJkEyPAICXbDOWOOLFmd/R3DbtPDgtjjbO0eUrXdoWUnvbeh4td7WsiiyP40ao50/3BzPCXcYv4Wes2Hiifh6iVvKa3M4HPhp/ZBm8di+Uqwdq3QcnpvauuCvgpz8U2uc/MO2z51VM+NxU2mi/whu3/abwMyjRotjbdkEeJQNBcRh9/PJg5QTmZg9l660pEZKc/qXdROz32JnYsycl5dK9/QUHNdcsKumLKNPGZ4usOyyWsv0Dm0ZZAHvwvNW0HTs02NBhZGMPOxN38KkI/wAZav3wSAZ06Lo1syX9ZxIZoERV4lEc41QyPJxNGNy5w6BP6xffWLfS9te3LknEs9Q8ZU2nOpUMkgbuns/gIEKFAeQ63xwo4WXWdtFpNLqzjVplDohqtMGgpyDV3ieqfwb3rEc1HRSrNq4kdKqDMZBRt19UgvoE/nHgLxqSC4H2+7KtvBS3uGbC6RJ/ac2xarqjpEJu/X6ZxncFdLgOE73KRiKyVUHyjm6sds2TcqUJMpr7j4anmstVhZnjzGmzX3nip1zZfHrg4ZW2fDOKTx72OtzZru82FzQ1gUldRzMZFoOz/iYiGgCC4oAhk+vxxFpdqmCAQjoR8n9sjMPV7l4BxjukWx7eOuNbv/nDnLBovl/k0y6Nv1owCWW/wLrWY92i4YBwEEuxmL7NanZYkgPIs6wM//SqZ6WybKm8pU4bljSqHK9UdoM7tzeDVyIsXuVjNLBner80w8+oe9Sb1ZTgodPjPhnlRGTtU36cjYsY0E8Pvy/Ko9ajt4MLcbEz76QAP071r7OvtHhXTTBjnIP8uqk1NMLrTmVswODpLldiOyLknRO+UUMLk/+3wvLmITiZ0tsuOM44ZqYrJ8u0kk6N/b8nHnzTewxwpPK8sX3umF8/Rc15muz0haEWWmwgMj2sblbfMNB671G4rT6ngoG+WZ1yF7atMMVygclLXkJHSNATLsndPz7EKt9EfFJB4pfQUVYb5BgRLCu0H8CWVsh9C5aF8jDtLoyeE0qU2pQm2eS9U2ZTn3MaIgU/ts28I+6hceEhWJPNyFFlvVad3+CR1YRnOZltaLu04Dw8ONLY5WnI0tCXZ1cb+nWsehdaidRZkirKp7x4Wzc7y9Po1N3mTZm1K80te/45dutTJY3sHq3hGHzAhDLvApZUqtScnEixYZGufFmaHIsKszvdaqTVbOSmHeDNJMxdv96drUoOy3L5zuD+YKrJWr1Oq5duqDOKyiNLnvFv5fDlo8hj58+2msn6jZ5e6hKME01zdF66MvrTrGwnNZ/TZisdoyX3UqJjo+rfKU1LhrsYhZqpolTkafR5mLvs2AkxAvF/p9gtELZ9q6x7M9P1L5pd47SUXjMtfRPFlDUkeLCuQhLzX/Ur30SmCcpvYkE9husfwZMYeBzsgef6yftJmuYcjdrlzabB07aNxh5KwHuZupzWf32gAxhiqCYaeXtymAxKepWk3aQjl77nOJ3PbEoUcCiA8lKUvjbdKnHfOeIYNi8+TrbqdQ8VLL8SvUPorWOYcgGovf2yiJZ8ornQuhx8lQL7EJFjk5X7GLLUqK9ufMd10WnL3cXfoNNUbdCJVr8rgthUqYjC1p4bZW0KQbTq+Qq7phpXcUv8nnRVQnWUZUJl1gUbBt1YSOA6XrdeTn/It2UffBMnPUQayiSAEoLDhFZk5bOnh83kUJrhNJQMeJptUtQafkwOY4V6cmYkBnh4k63OHF5JPxrANFkCg2p5p3Zbfm+H750KDiXDoW1gJGQibSSTiHT9iTiJedVLlTk6wsgl+aKythC1Lt7DCaZRmFyes8ozN1UqCqBi39oc3dJdntg7kuVx8cc9sQTodPOU49rZj8WH70eV7HpYtZgrQzSODE0ePATpaK3OJLzjtfkzDzzLzoLZuvXe3uld0AKGXbkfoRHJq3xbkv2hetZJcKkkMS7wtrkxReVsfYZFHEUebhY2gfU2PROR3naVvxpvRpOidP2D79xewQ4r4m9aZqc56nChGlQwjyIBco5VGE9fPeuW4+mJ5go+j5HpKuEo6VxO1uG5oDXRhhM/y8352QQn1p9LDfeGy323df3bFLJxamxVUVK4ZD3T1GX4sUfnU30YYfRP8mWyy2r23dva8KB8KOJ7GkxiPH1eh9DpmGfT8qrpleY4V86usQnLbJkmRiPBsTC7+a8x81REnBJI/9xrIzcUK9JZZ43eE+5B3hYRVdQ/hbfw+mYxuNrr21hCRVu/b3PCNUlezztyj+e9X3k08JAUZ8lgRSOy7ZW2d88jVs6r7mTgPAWzc/5d33qDOda0SQrj2KzkHhXGc2vm9T1Vnw8dcv5YjtaF3gN4z91QjEeH4s3zV6b2/VcJyYqkvwDgZmJYp8/U15TkF5PhF5D/nbwpBFC51xO0vdiZ/mglwhByscRrFqylEiYKkp6Few+47jCNnwKGVxtVzM8BmsUnoGrCuYwroFn3crJHVLMJomZUpcBketG26d3M7v4dv+5qh14UAF9s9YdnP8ps9ickKnzPIS1CW/SULCfiZ9dnKR2m1WLonykAeW6ZK4jZEIdC4hu4vDLmVCfB0EO8MB6vvNoKrYaIyB9+fyS1+9ZiPY4Q/up8w5xF0HtC7OitBcHIXTZabmvjS8slD/WyvhraDLnV3usTLPE65UGS1veXgKWvUzOPKUdtysLh8qIAnCZtg2rsZly5hB/E2EAm+OS0WxeGllPHU2ncZ1huBfVTyoNUepKPfqvTS4SIorldddqJGTbcSKwANZBrJjVLo2MQFcEYWm/hRjfhmo/4AvifkEMg7YmjsfnczJEVd3qQ1I24de3KCi2mQ0z3ZZjds2INNMhT98BPrdOmsys1YWd5eESFTIse25C01qLmTkC056t5dxRgko1C1T6qOVBIARAAgs99NJH23xfHVz/vRvOohh5mO6B+a8WCHqtfudOxd13x5OBjLqCy2sj3dfV1EnQEo4xn45KInuZNJN+LpZZCYkggwLNzU=
*/