
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#include <cstddef>
#include <cstdlib>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>
#include <boost/coroutine/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename traitsT >
struct basic_standard_stack_allocator
{
    typedef traitsT traits_type;

    void allocate( stack_context & ctx, std::size_t size = traits_type::minimum_size() )
    {
        BOOST_ASSERT( traits_type::minimum_size() <= size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= size) );

        void * limit = std::malloc( size);
        if ( ! limit) throw std::bad_alloc();

        ctx.size = size;
        ctx.sp = static_cast< char * >( limit) + ctx.size;
#if defined(BOOST_USE_VALGRIND)
        ctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( ctx.sp, limit);
#endif
    }

    void deallocate( stack_context & ctx)
    {
        BOOST_ASSERT( ctx.sp);
        BOOST_ASSERT( traits_type::minimum_size() <= ctx.size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= ctx.size) );

#if defined(BOOST_USE_VALGRIND)
        VALGRIND_STACK_DEREGISTER( ctx.valgrind_stack_id);
#endif

        void * limit = static_cast< char * >( ctx.sp) - ctx.size;
        std::free( limit);
    }
};

typedef basic_standard_stack_allocator< stack_traits >  standard_stack_allocator;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H

/* standard_stack_allocator.hpp
10DV80pc4wLo552pTkRihz3fJgvA2y2f9TVFMsGJWp0gAp6LVvazxb7H7SZ+GlDnMAB3x/cIHJ1qUIpSAuwNzomDTiEwegO9wDGLYhBDWgB2+kb38A6Ib7n8gegXcnC5X6D2X2Im13oFNYwOBUjCBcHuEV+GHIsIafGJo5QMhWWrwy5MZd6BkSsKTsGvMHvZxUpJo8GGYOqJRXPmKT2zY4LudiVYRx3B1FAIwEdqG4YssnDGgcxaC9kCZl6M5ACs9eoWf638vu1XmRF4bC64QI2yJjwZ2gKjuzTEfnA+tkKWkKmRI9ewSUQ+48jPbSJrjVvKKsdgyIgwC4U/IpeF+Mzz71zTsnGh0yizphgYBDq8QzemLDy1I+vYfXFjbEfMrnD0FFOX1akLSRhRmLT1/vVjc5U6QDSyVFwLr1u6VVfZk+1RihQXkn9d6rLY6ntGuL6V2jDb7V8bhrfxEDVDHuntPp2+SXFkt9InSPMcqZ9jO1KinLHgr7zxIAeEj/oMxDknr3wfwQ5yiRw/glh19Crybba5Fhscx99CSKyLqvEZ7goYJJ6Cg4pUmukeTwQjViCdvnT+1xq/sn0zbNxU8bZQsfKMGztrUyyVzxyiqoB29wEFfE9h3NxNMWVhTYzmj+73pJ8BrZq3hKlGAX3EmrQq1lJB3UFR3PHo+aBiL8Zvg0tXpk4xLan47ceayv1Eobg9VI3jI8anF/mJ6yACtEGdFSLTE98N0ltuVJtMjthtdrdQAyYql886M2q22aLqa5NYieuvtptWjsCyBuusrkfQWVYYVWKumb7VRBUeW3sQOCV52tqLWWGGT9sNmiasvJWhwRDt02wBUzAoULHDbIEHZN29n8xtHkJUMcRt+uIUuya6qgvHJvkCIOCOnAzj1uonA3+FEv8x0BsgLNY0N3y3jdbZF+ZKaVWljcjpyMS+aq/P2EkIl6NilYsevj8Nduqep0ceeyuOMq6ykwt7RSW5Yj+CJN4BjZkfsY3H614BY/LpCowCnksNTHiVy886sVgFPQNIyzY0/8Npp5sp6GHZhsQkby4ovi1GdmN45ESqAkhahkSHq6wLgnO+kOxCydGDHUw8+l8Y3MEpYurBoos0AUc1QgFMbrj2UVjQiQ2X7BzC4yw2ksH0iQcnoWA+4MJ85ZOQ6ZRK41H2MzxHNg4+qL1GyAwscPfndILhUgFeVRRmVEs8dTPBYmxSoClZvYZX1WpCHxz36OK8jK2erixurrdthYehGX42FhsQJqaeg5AyT40GPpCi9VKV17KSLAyYnSP2jsO3ZrdnYnlUCIxBoNsOg8SzvBeGeYK39bufpseSCrbX65P2sNh4EvgHRA4NxKOYx7lu95ckjySGnrYa9B3/fKLF2TNZD14HyGrFZ2ZF/9VA3HozKvWnEHZN52TWM8o5z/t/67d0UxGJZlwUfTUuk5/VXatgaNzxqOStP2rRgDpSrPmUdexZjbRG7HmgQuSQZltqFqIbKhq14mRP3Kbj9kPIbIb2eoLstxdq1MHDqe/7D2ELV1dMjwUumpWKMMSAk7vTp2P0ecfgQs7XOYBDQ63nu34qVFWTcSjmXV9pVcS66hDyFNES3+srdgZU1WxX/771XU8WPsYMbUpycrUWVAlLFa3aq5NZaglJobYUjLdhhmlvTanQJDd6q4Ey63BrtZ18tJkFkjru+MCKi9CrBil/Fu4AlT3bEcqD/eS/zS0gc4jMS7RPTSepAGMmJUGbrVzfOwWbYCHQXFl6T3PBRyUy7Kkh5bCBR3o7WYIZaQItZ7WPpMA7QgODuNfmplQwbiZ840OR226DIHhP31UxttNwv977LEsvU/3DZuaIVFPGpcn6SH4bONTn66zDCHeUWUoRW8UxylQN6K4qRlvWYXgVMxDuoWuPK9Z3RSrePPSgF75ByI4PwajoC7XrDJlP3IjxloZg++FbbyJV+pADhRgihYVkEDeDDcmXNcIqezTyH9l/sUWL+XzPsHZROAZFEWz30LP1hiS4xfTILuQ34c99a52rkdPpavstjxgWSdbXdhnRxAGl11OUA0dhhn6nC1FKgse0a8DKeeoj7Q48vXMnsEm6zITXh7qo3/ELTQJ5QGe79RNIsDFP0u/76MB3wweP5s24IL8dp8+8AhtsiXr5LVVRhjUaDQMkYFEM+xdc+y7OFeRp9SsvSeJFuv6xmL7/N/dUj7S4euUZIgHCdV59xmhktiilyaCGXDbnwRLC0jBKIIgxW8rEq0ym2TFqqYoPGXm1Dd0QGt1hjo0qqiPSzYipfLRQLsNJKnHYRqB8P/gja0yvSIoJ7OaFdCzOvphE9yKYkpWcT5Rfs4Nw/Aiu1qpDTAcnMWhRsd6ZdD1Pq0SMV8vSzQ6F0fjdmeRsIjeloex2vGFNR147uV/ZgWljcNmQSMOwBTfeUelCjiiSnRsu/bI9kYm+YvHlebA421Zu9PTSq+PUZK4xg5Xf4693NFeQr/AQwHxrPurb4if+36x7rpnyHdZ/sOK+3aNPPneVrlTJfFarFnW6pYVSNzSzLE4u66nPFLAo86lSKJ2XFHwnfqOvnYBD7uhgt0t7RlqXZZVP4/buRZ12y8I+Sog36FL/mh3gG4BYvziCeDEb614Pz3fsHVfXGEw/JERkVT8bvJiBc2EMmLcSuYcStmULYBK7Sr5OQn3xVUqoHtSGJJAVmRFbNzbxwR43G2ORH6VwiYYclTAN+TDjNJnKK3nmwP4HD4Dwf9LJL4jVmRa+W481iU2CMJtwg/iewqua1bSNbVSI54XLhr8eHFN7gjLjYMrsRrzBlnSzzfyW+OBukumG2uMcfWs0RhvOZ8GvJ1qTqTUpoGFYMLAm04yUDf91c1y2lf1PT3EdkxoH0m9Ut/Xdz0F/dTfSBwbSZ0eLO6ngDvxg33flNtYfKez4YRxrPY0SDB2h7lFKuA1SCYO7ZSo7E1r8m0jkHPWts7zvIipKbXDrVJ6q99tS2Urr3S4khddiSvfxrWvGW37vve7fk29ohVFSoSjCfg6zE18jTzy02y2DE4ORzR9Tf0bEwPF9CLISWQCUNnsGs0LSk5Egvkzdkm6SXi15k+3EwK2uMv3yv2e+Vxt6Qh7peLx6Dmg92ivQnxspd8J25eGplkkPlJmD0+ijSHZxDfU9RGAt3AC9o3a2K21HrEV5Mr0eFYnHB+5UqbKtytS3fsz2+5C19rL2Rmr8KphlYWp6AIF7F1eoJ2ihM1+aHsTTKGLGQneE46DUpJU5dpgja1HPsgNk+L/u0tsn3rzihM/s6ze0l7FY5AcHzGPlXvmJDC2J7jFMLOtk0eNYCptCNh8rYUMHFMqMgxWF+F4f7vH+ldVT+cAiyY4VS5PRGDFEbp73JHIZ2x6abUSSWHMy3fhgIqYy8uMc+3LHGiK0LlIeDhCZW4vVVFzNbqunGNcZhWbswHmCa7NRNN1Y+wC8/LphkFEfkXpmkg1Uur+bPsFPduVQlippr53ZGWGxhiQQt6LcIBgXHqNeD6xNpbmGVhh8oz3JpyXYLXmPJzG2nDmEFEQcanttxa6fI59tKQwj33dV42tH8dvkypoScl2j+hulF6bSpIyqLg0MmOIMqiH89Md5/VICdLXhj+CXL9kFXQXdAH9blIcuvpXqsrU0F7fafPtHTvsSIws+wCbUaOAbCGAE2jOrRIQR/9rke6B6JstlL+/5Ipln3LN+O6ftsZn4qkt+7gACLP3TtdkvpXRh+dNXgAZbFHarUqWz6XIcLKMULwN8GFuzouCCMebL8wdmYXQhpo+ul98z8xd/IZgDKQIdw6qeN1OQlhvslu99r8qNBCj39+wAgEaV9p7SfV+ZPdymRPB53Slg8Pg6bYzF4gNxC5k0rsDe+yXd1HITSbosbsEizcj6eVPBFpmGFTFklb9Oc85tILk0F++Zpj6ujer0Vaa93g/+wkkcGIk0hPsryY8vH6OqNKegs5PTv/kMiwHvuF4FdgZbWd2euHUl/xpsjIvcRJmXunaSNsOmskZg3RZxvKZSkipOKZuYfZYvGwlluMo6XuwNJ0RzljcYzRWc7l7PPpLKxcOoJbAlbmCh6/tBt2nnbTkEdrbLZ7idVBUmIlzlp6V8y7zzw6PD5q1JpiS2OU4W9VZ7ssRqL1njU9sWNe5aYSWa4egRG08RpqPbTouZR8IX4icuGLQ/MvjnZ4ZN1TJ2CdvTvgQS5kaVjDYi4TGXouO/n+7SOophYO2jdvzEqqwzU+2o2xEnXid+s/dZ9cox3HCo4Z6p41SP96D7Oz1A6qfe2b0a5OrOyz0p9abslshBcWCvKSEc513pnLnYCFyGGRb+ahtCJQPkAVFcpN51d6Y8/VoL1FoOOLuLZ42suadsNsees/b0H7QVweOL37HWs/Urs6KyxUAp5CzscMvUMoMf1OhBYTfV7D5u2Qc7Rjc6jkzGK84PRt19T1LeJIaeJ7i5GRvqEmXudf8D0Vt2awVa/fsALizNsp4gx2TlvGbXqS8EyftX1xywbSqMzI8JTYbiJEkL4uiXfbMgXZZ4wEz5QoDwYE+RmkUv4yAox29vT5nnrRNNeN5LYmtlcCM+NhDmMHNZmoGpFI1tICamesKSRzWemTE9WPjCFF/N8bzaVk7p8FwqSfRSiFBw6IG5WEAw/Ngx9+6RtWAVX+pNWt61mvvCqEGXA0QpI9+KODRfvpeTyojGw8OCUljp1iahbZC4W95NfD4FwTpilQ5R8uyC7pJZKh9fldjss22qK+4pPlfOHEODFN6vAjhmC33toNyRlvS6nW2pHhHRCxNd9aq4Q3rVXs4+9ssbefc9RG9IXanI0aTXhTWziy4K8F9kbvyC9YE/p0s8Vi3aQSFJ0XmMHBFQVzR6t7IhHAxjDGOYyausklwtomwbQxQlM+zVKgSzr3lwA1pOGCzzYjGb/uhSshh3fF/VCD7yefxev8j9tURbGn9tybR93Zwp39t+CmKUsfCMQIfjnYsgFoPtegRTJ2LUA+eM7BlRn3QFHdw7eEptlC+OyKV5F5qhKTOxhdzQgiRYrfYWuhFMSeDu0SGpzG76SKpgy+rpIcKiuTgFQAIugEaqZMJPDJNcBOj3dyl1+wptRd6jqfSGuIis2Y2ythC9OdRmv9NAgwKliZnCT7mt5GEk8cnn9T/19LeXbiK82LJ/1xADWMZYNS/kTlgcKeaS6EwIfU8ET0u6BCWH5MTEfwypg7g4bLtjo8sR1UhOBlJw1bIPFItkHwE+IwR+5quVDSo2Qajao51M7/ki7MVRrCH+Jn7gS/xE5xg2mR5ioeqdMakAaFdoisTzQf1X/OhtP/tUzJeuEFXc1gmYIAHyPQTnhVnp4Du3khG8uE7bmTTxsGdH2wOJOgHgF3N3uj1oWexuG3Nu0X1JQ1TU6DxmwsgzK6cJrUUc8H+awbFeqBxa4sgQlWb9q3hrfoihqPtrjW5WCG4gFabmfAzWXsa/9S4p415Eeo4m3dkUyc2VIl3k+NH8E0x93AljYGzooTZSUjGN4Eu+6odjAPpM/gSXxNBE/GSw2UxbeBeGHMX2oJ5Q4zrikEz1wKQl7q/YJ+CjNklj78G40vHNMCFaQeCsmihAtWHC+Eb6jq4LsKSysPEcrVm6QMMvGSZTa14jn08jEH1Q/exLzYYCRbfiLuITMWJjwgcTDfE/AwfODzYqjLKkb1Qp670KXX4koxhM2uKjQtTY1Hm5qK4WjsJx+D19883rB4O9Dqjxyfb5+0ZwBxUFF2jSmODr1nCijQxXnX8ABD7DBPpTSPlTvH9kxall5HvOL/j5NDXcxX/OT3t8CY+2G447WZ7RtunxxjVSSfbpVLqoa2xeuXNoDGg17gPPkCmcMFg02rzPh6aeYcUTIUAvbC9oMR0Hg5o0NUCuWvNAEHDOqzDkr52/5dQHkWAHUsNkMAHsHxFGPzdUU5fJ61Us67+DINNt9red3z+D1DLfTAXin+Rd7wNgoCtHBmBy++UTnBkYkQ+rutbg2NLZjd8UYMChjE7eews7O32Q4Qhb1IVLaW2HTTD3SXZwIBEEPHdx6vnwMgKt5e9MBEfKfTfiXx/puiR98Z83Ewqq/TZfkteCMmddG0NkpzO9+9DnXLe5ivOxYIpODgMIFvJ7ZVpdUWajoI8HHDXjVfoACxbbFaPsUJydH6EGED7VxwN1hwcf9Bn0Uq9bql6T4arXxCVOPmmpdChL30dnNCzD8gmobgsR8rCL5Yf91z2SKvakfiaqwwazCysoJljelwTcxkXHDLfv4kqVG6NTezst/gC6N7Kjr3A8EIeExx6skAO1J624e9NJp7CrveTnZvlGCCYM/aexGBgbkGBX2FcGqfowfAjtD2O9Hx7uw5rwUlIH/AVsJxO/fxmM7mUbK+t7/s95Kp1JOyV9XUNsKUekvtdCzKVj7sxnHOSTzhZhGs7+tyeW3PUrV5dFTom3CkIfbekXw6YkgDKhmmGkkg8un9DB6YvooIa2Z6HMr76iTQuGH3YFRWV8Anh5ttPEFZl+NJ4ogfYSutCbBA/4ioqdSK1Bmlno81PJvE+zLyTlfTQQhrO5K28DfQSJ8G9zxTR+kO8js2reHYuyFV/Dy7xo4CPw3iGKjRypda2qBcrQCYaGgVRCoPSvyr/sGLm/gMtXf/yTT2iwh2rZgQRb9ClrcQfiqpbGM/ukj2QxkeGGDbqWn16SnW3urbbARBLf2pJypKXUEa4LU7T6QRrI5vYuy1tJIs4nfTZQlFzzSOgtl/zgGpzoIl0nP4m2xqKD5dwMZvrgQkHyBKFWmmo3bR4PtBrihcfa+1c/pdUv5hmP/KPT7DSbPoQFr53ymxmfFNczh2C9ssOKYChLi+VhSQa4OuwLTBURE23hS9WLHzfP6UtOYhR4cXtrHlCqmAz2sMT5tAIaVvyHKomax1sck2BO3syvFuSpfIqcWgc/mWuB1BKG1LwRzNDtBZPqwoB4FF22jCTNTgXzNpvK4BSlYmux47+hffm/B+RVaDhA+3T5DdIZgYHTm/6dpcF4aVADFDakgRPgwhQ3uiGAYdrjKUaHhemutA3GYd9boDb+pO+OvGOL9XhbOKrj0AptBV7kAaRmDnM5mdnpJqvicd0TWz5Id6cj/WtvfAKaviC4ZKWlLekdoWsqn4a/k/0W6pbxYvbAhgRU1xwwqk4EW7JeucdqWx2aTgErA8QcQa/tCdy7gQyEV4/raEXrQolrgEmun/Z4ykTun+/gYSodQWScKufvNxMLqDLDTxR2knrGd4QCdgWBFS4/uA0yzjjdqNqy53/n0jrocv9P0TlQKfo1PyGqa+nCXPD7EGq0Ni6uCDpyWe9tHD7p/5AAj+f0za9g5/0I3Bdi7wf2rw3KLO6i3zHstJbNXZjIVH0h7Rwbxny28f1USYBu9qbJVC6T7kQ/HuzaPXR2MXHOOB7s9KOo2t1cvZRlkMYK7jy1DweGzIfPiF4++/gH88bXxFe5aU0nikgu6MLhLjkPSefW69usm6ZUHtbAK+uqcFc9+Y86VkC/bXKS84ORwjrTZkhxce6FEyuyOTqikzHUVtxOLak6Y1293Y4eDt/t6IEetVbtNzybg+/4fs74yoZePSO/1esq8pV8Ol0+4XXh+LKR/hi4j5Bl31h/Jea9SLfV1a3KPhIZnvQRbyOCLik885N1Gj0BFdLMRe73tYbqC1tRLEJ9J0xw3xUxsFeWCz2Zok7ZEcecc9cpqSURBD/8UUt/zfxZjWpdPNlpM/1K2EezzeFuJwf0Bt2C7kDt3w6Gyl0KHIu6hhObjGWqjGOWREL7R8z7We3//Ip0RvjmUR0rrZx7rBNMLpcwzkupKyDDZSG3bHsgb5VfNRnbwgdVZER03UBejZuLBP3fyS8uOf5p9PjSoFu6T26kyQ2prm1MIo4LjSIMj0Nn74cegJDSL31GOPt2HEsqaLgmfuLBaS++49KeIGOeUHAywqZD6XrULexSYUhvJpsmeUE2HZgiq3XibaMcThzu5mTrkBWlcR1+MPJdg4oRW87V27K+ph6ML41lD0LX+9f74xpYI+UxU33uFYDtShQIHlDLOGnrE+HK5DQD3RJtaTPFe64kgvHysTuozI0okPTG1SACP8alHqvP5hc7W1G2oKetFTVWQCA3L1tLl64TH7tw1hnESSYvwwuyWUdulPiwVS5PPLuk1xvdeTmDoZHQA8hLboV75guPG+C0FK+QQBn1Y5P4hQwwPpGQcqZ4Uc1Ko6CRb9SIZYHEkGSKVIParu4/ugrG1YCSHjO/y2uQuCOlaE/DxS5LBq+x2Asz7Xu+73pnfL3OdGHu38GgvsGVesYO/VUhpuCqkbiWJ4aRLVwp+WLYZwLo76nI+v/bAIj8IWIqJIW4NLWXB3jpOcjQN6tw3MavPOKxbGVW/ez56Td8ndCAcsTUSg7MXrpl57xXXdlM/+kpzx71juaYO0bnhtz9u2FNBAwBBLOwA2mx9/xvI51Oyb2hVtqZtZ1gLUcSU6REULbZM7GJU5UwScwR9joeSi+NokynWgQ3JVz7PFxDpCrlGJATGzOkO8OANmmh5aFlNRFpActGxUm5jAF2iGEd59nBGIGLaqGzwzPa4PCfiytTFIOynrV4/C6LUJf6W6qTfRomV8h0EA3xt4/46YkPJVDTDpPaJanz+6GkL7J22BpwPEPoGb1AeXQn6NAqxnzroi0PFIQ91NajzgyVPZTnXCbMqcrGeuX4TNg9JHPJcuJizwapBWXOZaDLA5EnfNg5inp33wQwWfbAWxgMo9KD45qpHzIEwU8qz9GxyiusxyVvwG6je9PQTUkjjrQwKe0dUI6uLal1MWuz3eJumj0J9SArcO1ng2mbE+LssyuprQe7LZTWckUeNLXn13ICU8SeFI75KfIvhHh56p3mWvVrRZ1tlTcMfUPjhOIhzaWAyPt4aSVdFOwx/JkPE9JQJbtT2fWw+wWfcgasQif/c5ahpa7hhhr7de7jjqzFrhzMfcO80ErXlmbGudF5o4TI6GNJH7H5ByoZF3j2K7GrN3tB7IlF3CzMK/9LdR3iFFmInWQTOGS4csScI/ogCTffIeoEjfclCLd9HtFL2u1V6d/VAlJZc6ZrDrWSK5ncrzCQlcpRBau5n/bDBE4CPji5HxX0360bEJClxUDUK7t1pogSPzFyW1mEja9BIvxPDoL+pzxRmsGJWSTNhhX3PhvfUq4=
*/