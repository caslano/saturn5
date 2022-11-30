//
//  boost/signals2/detail/lwm_win32_cs.hpp
//
//  Copyright (c) 2002, 2003 Peter Dimov
//  Copyright (c) 2008 Frank Mori Hess
//  Copyright (c) Microsoft Corporation 2014
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_SIGNALS2_LWM_WIN32_CS_HPP
#define BOOST_SIGNALS2_LWM_WIN32_CS_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/predef.h>
#include <boost/assert.hpp>

#ifdef BOOST_USE_WINDOWS_H

#include <windows.h>

#else

struct _RTL_CRITICAL_SECTION;

#endif

namespace boost
{

namespace signals2
{

namespace detail
{

#ifndef BOOST_USE_WINDOWS_H

struct critical_section
{
    struct critical_section_debug * DebugInfo;
    long LockCount;
    long RecursionCount;
    void * OwningThread;
    void * LockSemaphore;
#if defined(_WIN64)
    unsigned __int64 SpinCount;
#else
    unsigned long SpinCount;
#endif
};

#if BOOST_PLAT_WINDOWS_RUNTIME
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSectionEx(::_RTL_CRITICAL_SECTION *, unsigned long, unsigned long);
#else
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(::_RTL_CRITICAL_SECTION *);
#endif
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(::_RTL_CRITICAL_SECTION *);
extern "C" __declspec(dllimport) int __stdcall TryEnterCriticalSection(::_RTL_CRITICAL_SECTION *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(::_RTL_CRITICAL_SECTION *);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(::_RTL_CRITICAL_SECTION *);

typedef ::_RTL_CRITICAL_SECTION rtl_critical_section;

#else // #ifndef BOOST_USE_WINDOWS_H

typedef ::CRITICAL_SECTION critical_section;

#if BOOST_PLAT_WINDOWS_RUNTIME
using ::InitializeCriticalSectionEx;
#else
using ::InitializeCriticalSection;
#endif
using ::EnterCriticalSection;
using ::TryEnterCriticalSection;
using ::LeaveCriticalSection;
using ::DeleteCriticalSection;

typedef ::CRITICAL_SECTION rtl_critical_section;

#endif // #ifndef BOOST_USE_WINDOWS_H

} // namespace detail

class mutex
{
private:

    boost::signals2::detail::critical_section cs_;

    mutex(mutex const &);
    mutex & operator=(mutex const &);

public:

    mutex()
    {
#if BOOST_PLAT_WINDOWS_RUNTIME
        boost::signals2::detail::InitializeCriticalSectionEx(reinterpret_cast< boost::signals2::detail::rtl_critical_section* >(&cs_), 4000, 0);
#else
        boost::signals2::detail::InitializeCriticalSection(reinterpret_cast< boost::signals2::detail::rtl_critical_section* >(&cs_)); 
#endif
    }

    ~mutex()
    {
        boost::signals2::detail::DeleteCriticalSection(reinterpret_cast< boost::signals2::detail::rtl_critical_section* >(&cs_)); 
    }

    void lock()
    {
        boost::signals2::detail::EnterCriticalSection(reinterpret_cast< boost::signals2::detail::rtl_critical_section* >(&cs_)); 
    }
// TryEnterCriticalSection only exists on Windows NT 4.0 and later
#if (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400))
    bool try_lock()
    {
        return boost::signals2::detail::TryEnterCriticalSection(reinterpret_cast< boost::signals2::detail::rtl_critical_section* >(&cs_)) != 0;
    }
#else
    bool try_lock()
    {
        BOOST_ASSERT(false);
        return false;
    }
#endif
    void unlock()
    {
        boost::signals2::detail::LeaveCriticalSection(reinterpret_cast< boost::signals2::detail::rtl_critical_section* >(&cs_));
    }
};

} // namespace signals2

} // namespace boost

#endif // #ifndef BOOST_SIGNALS2_LWM_WIN32_CS_HPP

/* lwm_win32_cs.hpp
brsnt6dsgA4P30p95ArxsAdXqT0ZuT1hRWgnKG/Guxu9O8pgrqFlO3PUbHskCaYb+XYE33NSGr2FBPXKDr8kP9LxVZOUT32UysLabsbWTouU0MAeG+zo4YD3B4N2zkmLbjMC8r4eGJbRkX8dhy+S8epPG74IYSTbtepyGi7wN6bdW6v0U6uXUkrL77GTqzEXkYvheDC4UfqqhBqd8N3OKku+LpqefqxvOXMhSJMKXfmQelTYxbIsIo6XnseydfHNESBmabvjl3VYjTp6ZDATT2GPqxxKf0Y8kqHiGOVc8zrl/Pg2s7XD0nJbDPnqmG7ujKkwVlmxxA59guA1hDOBzEIIEAR8tqGGyIQSyxRwBBg7LDNKrKGdsyRw9IqKHRlnZIJhSOglVGRhfOGfEyrtsgTPiA8etbznGAE5nf3z10Pi20PwMSx0XxqM2t+Eh0UOak9co+5P03K76OutYunDJ8AczKP5Iaj+Db1JVdUaeXIAAiz902ZrK9GkV+NQp2Pltyw7FiDzIEFb8DxtNTIQwCnD1EcxQu6v+iRSjV7zQcBwXYmFDY4yprP2y+h0rrzVcEzq1rfx4nNDwP6hCWNGpcLaFfrW8YP93YljbLasJIs/7yZyv9Go9e5YrVeatTq1lVCaoBEnaIcqDgeRNlub3ZO5h2MY0Vl/kXYDIzk73MjvTsCjFY/7HdoNaeyNElZz+936lk0DCLO9sdv1xp4dze5+O/zF5wBAgDTgHjJq+wXDOIxeO0qEAnom1/FjCb+hl3DEWowFJUguymeAvjkOoIOI0C6dr3rlksPcYbT27CoUORy8kBs1TH7OkIcI4rywdTzH8mI1cIL/F+cxHf/yl126KBtrepA8NSZwGNFK/HQIl0oOWe5PI+gr9icupl0Vz2CNrVGY1FY/7mQdFdPt/Z9HgvRjqKkNpiJ0b82seMsnV8VM6JQwfTaeIElbJ6kN/MVxDQsvrRL7HRHKL6Q3byUwpSt8ppUjQosxn8Mdo6uiL3LaCjBumLW1HLfIu3lXBQLCxO0bD5MyrvJDFrmVDcX/yUeikOL4FSAFsVwaZd+px9TvuE4/DxBmWIcR5BxJHaG/uE5kuCREBbg80XVMz/eLpudO6JE7N4gmat7nUH4ppxG9MUI69wrqyyfCaazELuHwMrgRNLChtnotZqaO0HO3TnhuKEd6mAPEaJpV3LjPbonaH7LRAsNasF/8qmEzIpnauNLLI1YGyzXB7jbAMzKMUZXrFZ+zxOI3iks7sqgyB9G5sRk99kV0RrfdbOy9c4nOvaOSscxQIF7e2etlFCi+rugr0XHar7v1GOcWak2Jj74aRsiQuJNiURpUFuInUHYgGOvAWO4AFsUw1sinta2LTJIBkVhbrpGXAhuF/ZvnsH/z1jyZ1Mx2e05eEUcsmt4s7TPEGag4Ie3tXwUtYLwEx3N9UX/pi9KkQWBB1F/6T+sjjFxLZ+9OVtQwg7yufc/OYax4Jjp8TgfuQJTsOJuVVZ9Hx5k7v8MMsXUuTWNPOXVmG9A1sCklOr1b1oKVwsE8GELlA6byhkO8r3fpEP0YRoVEueQbV0+S1JzjmWB5e5g76JekjDIlbq37xLrwXpHhwGckrfWxCl7rsyTREo3ZJKLLRUvS10STvi6Qn7/H3ppD5Kea24UtBUt96M8HBxNecWkTYSAsvvVAwVAppsXJ7BDN/BY811PaE3QRiRS+1ySDQPB1KRu17JtVX3vkDMqg9NGy58AGrD3H6I63M5gmPn0Gdhmm2SBRRqChYKS03gKLBKrFVQHyt2UGhKU5o2N4Mw402TNwIF87KtY1GXzeiNG4eUmHI8luV/kTGP2UdK32/B1/QmA+V0WIYXG/uIsKGHSHWmhslhu1A5m5TuP0yYWLm1Y1t006uuEY8nXizSUn9Q0NA1Pdthr/hnr5r7Tjgv2rYdP1UzrCnVnqhPMblja90I1IYga+uKTOhDZGFnwiBc+KQ59xaM84sAzhtkSV1O2i0Hoc/ZaAvo2zMrkmZqXA33d5v+g5p0q03hU8r0JfwiExzqSO6NuQSi/98WJ2OK590+8PNBn1u9PUN8HMmmD44KdRMMy+yZjFiwtoo0vp5hqDkKHW6sQ2sCP7xcoVJzisnPJJ0XyJcGgstFPmsquTfMK3a5ptOOSMcHO9JtIg8SQRY/Th5CfRPrwzL0pyEIkHVIeAKKa8Crb0R0FgJ0VZipE40X71rygolJkVuEJL0nQFcofupmN6xM1RV419228048qY8KgXQDoRJ6QgcCrs0CZSfcLATT5HeOEsZgUy92z0THEHz/PkumnTzhaeh5lrGURshDrVoWXdrIJBSSTiPwoxXf+wsxdfCQQ0FggvohGJeWIQoq8oehNxuMNuKZ5D1YrHN/70MiLxO9pfazrtcZcR//kuJtV7duMpUr1ehAsiK0LWBi4co5MrsqApuiKX3kjbsSuzgxDUyWBf7SEQgvBQQYi7uvOYXlBsbabO/8pmWM6BiKOME1Q6czu1SgORnqMvXCBNCj+dy4oC+1XfEXHtMgOQPtZyjxBx6cCt3804pWGc7SqHwQcHY5jwo66XWMV3O3U99BZTw3ODqXBkApLFEGt1UeaWr0HCvAUxDSEKeFXno0iOae3h6JjmzsWYEE+Q4PAN9LEYlrli4lwDeIaCbnDnA/7YeJIIGCDVAuJSuuAfvXyFhWPxiPb1wNaKEjMuLBC/mcrGhb9csdvi1vWq73jCtL3DO0S4A45Vc1xP7GDNohU7YHCYF7U4DL+x3U3juYa6lY6QgmL3OCvyhS7Ey6dXWy0R54atTMIHbepC4mCERekT6r+LiAw94kKf9wrLR136C0gJsTSGyLaHes/Dmn9F5yFvjjHeO7QtvFIdwcJQ2QJLMADXWtcQ0aLmpImXBQvbzvq6m/0CPAVXwYC+VtXXRocCMXFsfrtfFN17UpcIVMtZIEfFdIF8xu7PF0f6dOpzaXB7tTZxO7QFZdiY6N5oejfu7D6FxNaOUt2Zh5n6YxldbSXECXxAQrmxzWSNWT5w1v9H27vAR1Vd++OTzBAGCEyQIFFRo6KiwUoNKuOgBsOEKAxOCCSg8mjrI53SFmWORskE6EkCp5tBfBZfFKuptMWKBTSWhwlQEoQCKtUg0aa9tO44aRslhACR81/ftc+ZmSDee3+fz/3zYU/O2We/H2uvtfZ68BH8AMvPQVorgYMUl9rAQO7vUrJk4VuYY3BE+HEEBI7QXhATs4vUSQDUw/O2X3reDhxRRAtNShkMYDBKwXRLMngxLziB44H7k77d3uvfOPqgtQyyn/vzzfZzD7VHVD/UsXeWvpQm+uK0+3IdNR29SO/dfgqB9ET7U5PbXyInuXGczwTdP3dO7AZr+DIsUmJHRZpRU86sSzTLywzMcC+g+uTliV6f25Dca4uqByIJ6kd5A9DSCVMqmVhsLHTLC90nTFypUDvLzrkNRIaLCD5H2RD7OXe3dxL08/LBUM4f42uIDMqt9w4chZF5uj4YSykqy7TTiruz5cl/nIBCb7RwhnwhizGdi8TN86n4kDtRKFUQzzQnF1e/SaaykheexVEHPzg8wOC/bfDUq+8mAN4AvwVg7co+/VjheiyIPmPWEWOWRQSK6UfE48y09UvfL5BUc/saPFWrsG753ViKzxb2+61L+e6zTP9EzMB+zH6fTlOZ+p4ARNyafRtx/ubsw+YLLw72/ZRhF4OJXH0xnY4Kl75bTn436azSmQPOQjuzdyQd4Dd/FAcpp4stkNJPr8NR4dD+Atp57/QTllTqOwy/wxfJxV8ewx3sN48PHFSz2k6OtHIUMZ/Q34Nm6w1h+eSpr8GNi5Noens6K2noi7JPG4EeyA/ltcFCRHFpWXd3Zob8ETUp9/DMmX8Ee8K3I5xZXToinKkIKbiVbtsFEF86QnuUijDDC0oVJjGmWBEGvqNqqhQ+1M7HQbj0bJw4ahV3Iu5LnD3vJfsSnyNqwH2gRpxbXBxSvluUrrl1f+Ndje/af1RlR7gy7aqy0dszaaNJfaoyQinSik2tB4AzOwa0ohS2/rO7WTcptilUWOf8kLCG2n/TCEH2623GSAZDdkt+0gzPoO62C2j+S6OBdcp1k1xeHme1r4MSzSsLmdW+i1nt0reP8PKqEV2m921mug4OXTcjlDnT8LcagSNtP8ExbUYfx9VCiXJ6JZ+Cp2dYibj/8Lex0pcyK32XpwpKLmClt/t2hZ8TbjEfbPQuZqO3U29rxFLc00CMDowab0G2lln2qmqqPPVYl9noh2dxB1w5KH73Ogr1rBUw/HjBCPqUTaXOcBmBpvB4GxiNFf5moLoi0EKn9qW+wJFKJ3VGBFqj01JSVGeIcpoaNKa3ythtsGoDUYhmR1cBEVZ9Qu67YxMhQOQOnw8z9oO9t3WGM4KhfvKljRAXqHTp/ibClnD1JAJNFDFArz/ta6pk/i5UyAoyfYFm1NmcMqtFj3Q4wgPtCZCXP9bFViPaPdX/YMH4Fp8f7cP51JzibxWzjqiidX9rqr4j1ber0u31tyJFq1iKey4rJoIYqzORVupPaVBedBuMv0jUs/VRWuKaZc1snXGLMdslP3q4C3f/ef9yWdKZzbgQmtnuAiYib3/+NG2K3HqYdrYl6350aRehgbxnHEHF1nWDvwSWaRlruH/2PNstcytxu2u9s8fBr60ZGwhvV33EFED1KWMIEIuCUcEiEXCDkyvlY6ct02ZooBFx09H2JAT78o05bm/BuFIC/YRITgQ5EBxFyIhyZRB08Wj2ExPZ2gBRC32LcfehOOt+t7yvna18hYbXOXdT1ypjLr46a4V/luZMDRI2LdRSIghhUguWNJ+Cey+mx+H64r+w2G4edwO7rIVHBE+VE+wQtXJ5XIwARwNY8HpJLy4uc7gJ1MApmVJb3yc3TVEa30sdNnA5gBPBf4TGqMxauKGMmbQLwn0b6WxAsoJROQ1BeZ4v7r1DvGW5XE8h0J+pzLD79oT74/65RA5cl+qAV2DtiKnRwdFCpyM7SoDExkFvpxkbRCWKh7ODJcX81TtLeqpHgszTWtHxpkVdZrH5Fvaf6C41h756o+0wqtkaK/k+XHI1ygwaxR1ybnaCyh/XC3U7JHQgErldpYa207cr0sfQDsbODUZFE0jdIRfRBPsPEgBwwplExK1S6/c1OQxtL9zp+Zt1s582jGDmUNhLW7s45JhB8x+tcFxBK0NMP0h7SrynmwM9VTPhtMDMfvhy3bzUU/PvFLxd5qm6nB9GhMt18wpFW+jmyPBPLYDgqR4Pv4qDzaFN1Md3IO92f3WDpzrHBSvEA5uVdua7gJqygt4gG3wwCBAXFetwXRs5IMf8Q6V6DuzEiHVZSB9yP2jDcZv7gTH9oEW/hIf6xAGA0oFoEh9ZuJfXNwO+0hrY6al6EwTuB+E0cR1RSOliA/O9CQDFnKa/2feVpwoUsKE1seOKAlHu7po4IkXcoGVFJ4Lxqux7af1xLHqq9+AkIojXpZ3j3YAWaMsTJfq0g9pbbbAEKX95EUGe5HYO9gkkIzKDxrB6GuTf/TuFjmaiq+mqkX3FQy7VSnSqkGaLWhngVn6RmmjlGruVD7u0zF7NTEMztZGUh4oZrppoAT+uK1EwGvuG8LPbqxUY6Dy34T/Q6G/CGdAGdoXVdE/VT/FZx6U5XL3yPfYGXoRmo45rdeQgyHxFbr0ecV9C2zY6gVaTf6+p7VXXAT3Uu4m+zSih4gtrSb6CnA5fh6dqIlo3JEgJmYHcdiPeuV2b8KRuGD1Va+nFtz/c9zbqZmvMaUxvthCMD++wOY+eKjYznhbiW7smblb4cvEW31TQV5C1IUdoRBmb8rOxtjYoGx+fOAJojdgTHlgacsgLOkyz7feQxXOWKKM4NF1o0msYnWcg38UsSRqdIh4qiDfQSMMQtn7fXsJB9wZLowLSA/Kqr77m5Yzzmf3Aiz2x1QrQU6EyM6n5fbj5CfxIy+zdGU81A809Unz+LUifdRGBFgv/AZ9/r6cKuoI4BZvCQ70bMOraQNhB4pnBgHuvZ5ndfnBXr0NWhB94gr9BnSa41NoBfdc0yySW8LfCc+0YQHF/96JRMP90PWhWGv4BoRS+wYD/MBC1LeqRCwIpS60UedmwCDbAWgSZuI2B106LlB28UV0khNLrvoODZug/XA4j0MGM42kn2Llr3wH1bX9w4JYOFwWmpxqWO/T7JIV2R2MfRHbyzPQwOw3OkAr3Ac8XaWWjVwInNINo7BQ5e4IlI/f6FMgnwp9aWTanYKm/IMTHLkTVK/7kcsx8Z9kQh+MVFO9reDjNGIgn5Sldbs2FGLkElIe+By484dvL39EHlIplkC+3Xl78D2Urs5Aq2bF3b9lOamfdA+jns0fAmYaP8mp2X5Fmrgw62feYLR+DRSdfusPpILLqJaRh2vD8PrBaglf5L0JHDfbmQmfhEXU9tIOvh1o+O0Zf2EfODm2A/M9vOq1X6OvuCBcGbZrkN7vjNEloouX8IUPdY8JlmcF+U7wXjsUSOoe+DYI9+3nMe3cakXTB3ynlcM/bNRAqCaqmlQ3DFnzQXrXcRnO+y3bPA78gxkvw+2Fsnc+/cFjiXc0Y+JWH+fsnb0HKp6WP4046Pi/6hBYFJ/I1Eo3NflGMl+B1w/sSEntW/Aub+KV7OR7+WeSC29iKANon350MuU004l3o35VGeSwsvx0QLX2MRjI0Olo9mt6Lg9Lc6oJFO/UeVM2nCebkjRw5GifFfJfxEhzGGC9N4w9j6PdGfBiaCYK2Ou802xzgSixfJPGBKKMUS7aOpVdgPEY1OzKpDnJSeOzRpnp5gDzV/8Qmfmk+P38C6MzDU+hlR0meqkZ85pHzVG9OZfhoAqQU0oA0VqMIBvnPc84Jp3mtXKUwID3KPmqUGx2axHOscZHzf5VKTcJgeleDlvVUA0B5Z6V7qt/F+Zf5AFaApxqbUmxFIaVyY7Y61sGit9uzxgFE4Hnry4WMFnziVm8eeiuGbxtUqQTI5NK1cHLmWX4UgPIZXq93dN7ua/BE/0Yxefh0GWXz3dbpefx8evi5K2MZ+5SxXOkseymKDg1NBzG/TcWp3SQvuPykaYxtey7FbrG12uYWF5vsTKq4VH5xkFl4d310wiTwHlgsT8CaAY8zo447KofkPXecl2H1BxphmystisqENyEM+gQntDsXi26gjquN02YsbBVvu9sxN2GwS+V3f3rahM+E1MbqNdYcGS9Bf0feq1pxRQdm5sBpk32s9W+sftFKxvVxaYkq+VXV2nP3adN3yrP8FYw9gYJ527vBma6nOFAinqoYJmgOKIqJoCgmjiEKdofgRed5qcGYONK4M125qAIo4CXiKxzxUB9f4ciHM7p4oTrDfZfcySeqdUh/J9+GHeYmLBvFNoDNB5XBbWVIoXes+Tzr3ZFtgQFe3wqaAKYCxN71HbjwYc86/Ovjde9Zfi70WM2JpcUK1JhDmwk5MmoY+26U2//qSuh3Tbym05RfZcLBaHrdLwF13/5MkTHtOt81OsJDEveUu6afMNtuAeDiuxPNra5PiLKHBHnVJSlKMOCCBlyjZL1L3b7xNkXIdWBBp2BpQSs/fJ4ozDYmpRPFYCzADUh0YYYyqNguMgjJbzKnVlSzBbcOOhup
*/