/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_05052005_0432)
#define FUSION_LESS_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/less.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    less(Seq1 const& a, Seq2 const& b)
    {
        return detail::sequence_less<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator<(Seq1 const& a, Seq2 const& b)
        {
            return fusion::less(a, b);
        }
    }
    using operators::operator<;
}}

#endif

/* less.hpp
eDml05PKV33rsHniIzQZHi9cZ3d8/DH4I5C1nNi6NX8jFRFIio4rAzkcafpLFFDaUF6DTRclBpCOFeL7R5Hll9L7i+/SZvnvhI+P8tvCAfmttLeUtv+gt809ajlYpKNbaVOOMozkDOQXcEB+b8lyv4By60835EOA3mg/WfjrpSXuZ4ErMpsIq+W63XhLlluZgLpPPqnysQq++XNgyfPdJb4wXm5J3LseoNxYXu6jFtkff9F9Clzp2wdcI7FE5RvTIp+FE08VSUAl7qNwtkH8wrZ3ZqzoP26Mh6p/L/U7JR4pcXcA34H29sbD/Zl5Fn4SP09bkEegoCFLEjEHdS6zqzchPOMlRttyfXuBw41HAqprtmcuTn98Rpd1972NeOBe832tGWdHpNkGmPh+zT4DT9zrKjsvquvvBLceNwjn0k05juZH15PcjHDMhw4qY2O/gNPqQSmPrMyVDF4P3JxwyghMEoHgP6jD17dQg7bx/OAtavDRhGhXbmnBhAUAwQ/eiuBlrbKbCH6B4M28H7o1h29V7sU4F6TMVcLnH92mzfL52whcIG3jKnPjI6l9rduK70xuItjXS9igejBGbmE89hNv5xctWD/zdL7Xt95OwEk2IXu8B96+/D6ZCOvD0eCoabf6+RK2tlX1phQeDRvAg3eU8F3qcoIt3SBg1WpeHUyZTeLeOxNM9rGGfc+AjbcqSrJbPqBhLxhtrK0OttdaRp9++y4CjqGpSqV5+ZG7iu8NhmDG2J66G+EYBj2ar8W7l/DJ849UmwfmFdX7SwV7VH/1tNGWl9+Dvls0D70nwdaHu3qcrpffSVYk/j55L/G9bnDUIhvdiwcFvNmDQVhuPljZGt97Pp7c7rStucQ1vFfIStScJ4v3sfFQJ5Xz8gb4ZGsil5+2Z73jfS08aVmqcd5h40i+Nc6hQxKH2W+AI6Ntb23EIa6orAfez8aTNVJZnyxx7Kzdwnhd8y6Es2Y89CmNz+ebcTRnRhuKBzTjyj6jMn9a4lmZjswyaV5OHihxqzCcNJevye8jYdIPXQumLM3Zrz9IwOg+R2W9+MHiOwqqaqGyfqm+o7DyljfVsAsPEbBSHwsW5DknYV95qICplS8NtQVcybKFkAdhvTHbgLEo3kF3todmjNeJeVfCVakT5UWBJ0TbRkTTnDdpCpgmIHhfXohcHSh+2hfqomH9rf+tT6rZIgWBF8JDnhPhiD1c0tHds3Uzdvec4Xj2VNtOmndv0XXVXdfPJPwSuwciED3s4WKojf/fe+A9W7eGL978vhQ6iGN3xFlXwo2e649mw83+TMWqeMATcNaXegyjgP7s9IaAC3+2O1L+Lsu3X8AfZ8F5bi3H9HWTZQYWDff9OqZoQFIkOABULtw76rgXKydRlqFDOblgtpHbz6/dhODUB6ZcdsWCY6WbPlILAi4Mfg0cY30/cI+A17Oc0Q5M+8prmvD4fodDtwnH3u8uNONhR9E4B/Y14FR7IrXtfQLHPhN0GTe14LIE3T8XSxxuxVXdm+QdN5NzdLo7Hs60DuOXOdM1+CLLDNR2hjmFxv0tw4VPtwvLTLdU0Vm4fzZxHx0mwoavkBan0nqScE+eaRm40KYX3UJY4A23SS1Keoe9hamfEArNrA3dyGitpnfYb+IdFSGb8MjWq+qXzFKZ7zpi1I8NocjabuQ5pNs8IfEWC25P0MmDAhYpnfISjZ/e9CmSZRk0bENmN1ralbEFKZA02UssFTVbjTTBC4jQKjyKSn361pjHIXvy1Ax+5WVqjIuaHh/OHWnutf/Pfc29Qe5rfM5Ue9UQMufl8rscSlwNn9efVT5pEr6UE5yg4u79z8fLWCeGnP4n/Dx1wQy5omE=
*/