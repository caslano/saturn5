/*!
@file
Defines `boost::hana::remove_at` and `boost::hana::remove_at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_AT_HPP
#define BOOST_HANA_REMOVE_AT_HPP

#include <boost/hana/fwd/remove_at.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto remove_at_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using RemoveAt = BOOST_HANA_DISPATCH_IF(remove_at_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::remove_at(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::remove_at(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::remove_at(xs, n) requires 'n' to be non-negative");

        return RemoveAt::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct remove_at_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto
        remove_at_helper(Xs&& xs, std::index_sequence<before...>,
                                  std::index_sequence<after...>)
        {
            return hana::make<S>(
                hana::at_c<before>(static_cast<Xs&&>(xs))...,
                hana::at_c<after + sizeof...(before) + 1>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            static_assert(n < len,
            "hana::remove_at(xs, n) requires 'n' to be in the bounds of the sequence");
            return remove_at_helper(static_cast<Xs&&>(xs),
                                    std::make_index_sequence<n>{},
                                    std::make_index_sequence<len - n - 1>{});
        }
    };

    template <std::size_t n>
    struct remove_at_c_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const
        { return hana::remove_at(static_cast<Xs&&>(xs), hana::size_c<n>); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_AT_HPP

/* remove_at.hpp
w+76c6diJwd18eJhUq/28ytSPeX0YIgrPKV3A9UT9CVJnIUu5d0ehVwfX89p1aZ2aUtpF3LvuwzAU094F9/B9xCH2DQXTyTQ5GcY0AkOKuzaO9hBZRa+KA97dOjzGtvrKE9goXUAYLvwCvqRUGVsl+AiU/BSs/5pzyet7oIL72SBF0QkH5SkcQ4h1fQyZMrpxrvBb63/87jTK2pULQMjvCz+GSnZWoxZvoNN3gtnbGs8FxiBjA2UktpcTsV0UW3SBH5a9ypa8HfzT03IMCA36ZdmWuD2BJM9ic1kKmUvge4axSFU/4J8EAb7L/UbQVGByYRu5wySm+pX16r0ieejkDXi3/FehkyaDSR62gMNP2epSoJzgXJwLUyf+X0lM2Z0v4zamePWxSLGv088feby+Xyswk7jiu51n6IfnI/VeB9mG/DPRhPF9k8/1TYYi/tc+5KseMC9N+zRW/cj56/qDJ2MubScPBOUVK+W7a3NHV5g+3DCoME5uGV+iA+LW2EMLKoWWC3c8ooHEjF8wOQI5i5qO8yWqTYJ7ROasQddNWH7FdLA2LGNN6SU+XylfgpYSlvr3SA4TnbZX8i+JqVR+a/QdJdvWmAV37qBDb9ca2/o6NMzwOyycY7POQ40+GmZMnGf9c9P0TlC7uP4sMaAYNXywXVcOr0btMRNuN5SXXL8XL3JyeLIcO7Bxw6H0eud6u4F37aSjyGVuZ/VsVq2MgBYVgZT+LZKz37/6d8ZAYf6z5F0fm2qDfmEmc0EB8NT4ef4MOvmrBBrwxU5Rozo3IYyJb7z1kLFOVL72PTgz5ivzYQI1S7nQ+dCg2nJ/TJSPQMRJoiwjAhV/Vb9rSsHPxEMn1XzbbgUerhiZVkDlgH1VsTnUCJouUbtPKk++T+k25LgPSOhnxgy3SvZK1pRe+BNX4F1kDSou4KJgcNPhPoLufuc5geK58PnzObhJTLd7CuwA7m/Z8XgFyPBbaY3pt8wURnSbBRu3K/zCwXeXWGrjfsnHMC73JzH9IDpI5QmUdlf6Odhb7aOp1rtx9+8Ol/OmyvYSGbdu4OyTD7jSnwtqoXbF5E88TXp8aEfPtU49+Hftm/wzPYX+EsqrbW3RScH7h4Srn3b/A5YLZ5K5X6ldYQGc19MpS7cEbZ+ZKhDWZ1+wNL43LD4dlEVzt9JTyUtPfN5dZVMvtuouMg+740+461ilR4GRJzzb5xfPvBqXN8izSE/r/3ry8tgzTHypoBNXY/jLJ3IeXbpMY/KrP2EH5b0XEj3nC2s4mvTKPF89SIg1qO04+WhYtcd4y9Ni31SgqPm6f7+jiusn33zM/o6h25e+PbulqjuWc1W+PWWsUpiQk2ouvqwzFdLKNr+yPARzd0+U5e+UPzmaj4A1qCDfyoQ5M3EdJbHEEIupoC/xXgvgUqHQu3OXxjcPGdjc6aLKOKmVBnx6FraubOXbG4/6Tyfdv5i2rkedtY5+9y8JFf9/DzkT5xunKLC9KPr5+xtMs7a2LifjoyLfhS3WJnOaZgInm1YuRhOXrZNtwXAnNCZ4BvlDf0ZgpzrH4U/Bl136Hcf4SPihqxcw2/32uOHosAfcgBv25936rKOWAACLP3TrkDokCnCKIJ7w8iXO3QFwS3sTJYbTDcY8GkkJwMVRLQYW6Xx5R66RvViWG16jvVyz0JJk6oIdnujZ8z17M3Ybezml1M+1Au92GPVsvD2FGALMnfASs4lLrgAGoaILq8NE96BobqoS7wd1nEgjMCK/l3EwHOjQBMzKJfoM185ymkjzP7TwL827sryTus46fD2Y/bCXyIGGL7JUBTTyASSSkHzISUk74DRd8okh6a1CrF5O0BGK2VXeNSygCi7mhqkc42ItqSiopCeakl0FVbN8EHlsVmyyJ+ja4eGPN8hJV5RMmHucDgsVchAReDVHKmoJJC3DRINdmsOqBZ3QzRNpDFDVJhYgXRrykw+8DTdhdC7+p0RBcqbQjv+ck1aieiXhJ4tRaEF1s5bMXmF9V1wFuhh1MDPKT6wO5EhyubyXlDNNVOVvvXohqu86iVLrJ1y0+xBylh5ah3Ug80kVAFfMcjUZlAKQuxk3gWbTwa1U1ulcikHUGp/2D5vwJk3d6MsbmFZlSRFmC/q10/ZOJnj8juD70wUT+rX04trdcGlvhSjwGt5SVjzxbDLyzYGMoJOieelvUGHfpsD0/uNpGPz6Wyu9rdRc+n351uXW6XsW2VfyBfcq0wq7e7W7TEnf0vRWqUwIqPN4eYg41H13YWeP97kljWcM3HiZP+iwFzLbEPF1adx4udsQxlqaTn3EaWj2a8TqwAb+SLMflBqxUGlkb4/ZHr/q1HNHuxutlKrGBO3m90qB38PQa4u9dksPipuBn7DDDepV/K07wTAp5Q++fMTW/xfCUmuwPizpLjXadXnE0wUcSapx18Uvczo0v6k2yobmLXCIY3NLeNb7fvPjnKIGJGX5c0TdjMotRWzj6gNhKtZbF1qTyCxOXD/M9201infO1qnyb77O4Olf47lk2WvhDlJD8+nhUq1yFpCHwsHVL1ecA2ssscqPMICpBSbKVfmD46aE1Hdlpho8MYA/PxpbxDtOLf/PRHvQOJcdKJNLr+S4SwDwzUhvwlvksi/lrQtk8iBN+OCnKN7fk4GPknQfeGnEirZ+hMu9X2IPmzEcdlZRTBs0hEyUIohALrrADjgfgFq1PUhpeh9oxBOkwz9njhNOL/Cnnup2FcZdYrcFE1Ptgr8+dMYF1ETWebiwU8LfOd3dVE3S3sHA852e+p/VWo9FeOfxeLIFHF9W3VaR4dif3EJc8KX1nw5e+dS4OTTYq7SzmzoceonDk5JFn4eMmxvSpa9Tz9jFZjlVy/DtzxfmxSdhLD8NTWPnLs9sO/0m9+aGsWS0dTNA9YeJdy+tAFCTYG/lPcTKenovrY78Pw1C/RHa3n4lkW49M5L7nDPxdNA5Vz8CPl0mWvnj2OY6C+bA8m5qG+vax7LRD/pr03id9ArN2Ec6KYn6xaUJWUdSHM9lhCBB51eVWMssOlHO32/6yroCr0cabWsXpQH/2EzarrJuXmJLIeqwNWGouPhy+epeI9GIdlaoSuO0UdeuJg4GAg5DE7rZuzTKTf53DcZaBepu7PQngUdFtKkRj9c1A5Lec79fo2mvZit2Ek43cy2jcd/3879fobD/7CacNSeUyeIjZyzGFWi2q/yfoGyaaaKUJvNCqpWp5JE2AvJlF+uH0j7gDuhM6Sb5VzcIFIxE3ZhPy7CzRygCG6mSOffRn9rnNiYQc855j8kklVNsxJlAJlJC4y0ARjNpYrbEDY3ukaN621EvL5EyQNoix2AJ0yRgMe5gbSMwk3CqfDHkwOo8IcscjYSls5RoxlP3Z+6NOOSKbRrGYPZlv51qbyWJzMWiVbfijtxns+5/Nbd0FKRG/z4nAB7wQy7khPWoXsE3MVM1XVDV2/4qqDL28lOx/2NV/nUGsMLHFu8B69lRma/bm8ehTS85UUelG82HFoQ73WOD+/t8M0VLFMrsA8iU7XQX5OBt0RhivogEoE2UFX1rTgFRd3qZU0kkUaf/9JDvjUZ2zQ1AIMBJhCZxwaZtxdrDN1Vr0JPCsyo6jUjobeRnEL5VXe1C1YbIKxazlDCC1mtOe5EzF5m8/Iu3q7YNna2brf6BaWQwmneawPMurUEIcPMfO4GP9g1Q3lylYg25/HtMgWs2FMZcoQ08JAr0mFRtHix/mgYmp3ZmQeh41fhmybQezl0GMnRAm4WRsL3zWm4sgQWxObMhfsjXESPRLehhp9OJGW7z37/kQzk8AQkrYVY4RMFkDXy4W0f+8gwSZxlf3JGMDwXBCTOD3XbkQ1npJxCu3VqWT4kNX14dxyNYIz8gTgDtrszPBkhpS0wVPa6dg6AvS4fd+GGBQeN1dI6IDkaJVQ3unYya542nZWeRQ9r/K2DXg37EWLYD084hOwa+13kaxhwiO3UxvCwgzNV++ERW3tw/co6JmXqBXcGKc5JFdD7Y6XAoWPQpjSZSJQiMBq8KO0rE24uBp4dpTWXv1l5jHCPQ2M4kTRPYJAdBfKbQZFEQhdTx+e+oWce17XWHTDVmiH8+Lq2DfxSGcu3coC67NurHpeZY/MzClyXgr4LruswkECQsqDaBWmKIk05P5Ks8MKE9l/LEXgzbE/kYoKfrEG+oxuRcIKKeQDGK3OFKdbQFaZIbW+IaxAC5jVWNiFIAbqdOIRk4GqGLHw1BVBjqr7l7WWyPXvcEuUS+/cLYEvmFkYRIU+t7GAWOZkuv4+fNAxKkYV3pgBbmaqvFwHlVXQaC3+oH3oS7w5PXf0z96WzpMaA0kbhwk/9Q3x1cbqQoSS6NtrZVWXSiHTKQICDNrsKF23hoMzSAg0TTG4glJyQaV+xwXMcyRAJFhD3CRIGI/bAB1YMmdGOPSey2/C3Y1nod58q4Mrzv2FlM6ggjbLygZRPajJJnwZVMS+4BelrO0mQUTzqAcYY2p3uTiBdH0AFP/2vm35JG7q2qKPcSqt4OH3CmoxvHuwNlJbvEeRgOj5BotPFTjemWrUXXbJYqu8cOWSnMq5RuiSLkBbPLR//Dl/yfo9qtpZFT22rRTkZLecfFOBgPqrex9T9DJPuGVsMnPv0zSla4IV8Y7pMtFBDgHQN68hvYNNnyHb7AnzZgNNzPlo48No5aeCsdKzttG7Zu54KWH6aF/ku9i042L2Qv6t7/3xr08FAaavynsDFd+320UFmVUk5B+egXiTF5uu225grkH13f/PV/OZbXZn0r01rXfHYp8dLWYNup2hHM379PH7OyXzpW21SC3lStxYzVjr2/nG3rredva356KmOxvPnflukEMYlZsyJPgxfVlvT427DH9vgxasd3G1YRTYmJAA/O+9GaK4+Db//VUypE2PH06eEa4VUx3QFvF4wHPBOL+krU5eczJmBnfQzDlINQg425tP/doA7xrY/8/1+O5sFNJzmKDkxpKKNXuaNdQVdyMZc4xVIVkv149H0pXDO3NIAmr65CHMQ3LZS8lJlwXxlxyjMff+y0YiT6PPc8F13MlBNJEjwalPxWduviys+hJROzYcA0wop2srv4lejxrGb0JGgplY3yFXMIEiCRj4xoA8Ska2jGbLAr68DmDuVLEL9D8Rrds+dI9vlIKk5BX04YoIhrgGQDlMx8sxy3tasIMUai3eYZHP3hGAJn/9QW/B28I5hlx2qgeZXA8DSRRNoZwph49/C9G2NO2HBa4BAO4pg2/aDdXjvWgRiKKHfamV7znoR4UIirMh0CLPVX0XnzEY0VKNkCdyZv3xfNCDh5lcN+3QaZw37VJwp0YaNTuT55pnapP4gbYaJjo8ZwySc8uKlyzeHNI5ai2xqy5Ve6SqyL99M4KJvksmXgUnt33cZzp7B2AcMeXS5tfySw8rj8CrK4d4p2hZK3R72n8Mx0a49zuaKM4Fi4JOzKajGuj4muIXwAOSb7YM+6FUTJnmb1qEWSExNb1JVIpCdBkj1Fpz82SNUjBKzOai8MkskAmOCba2rpnC9Z9BhNUjF3kBHkqmS4kiW3X2W5NI3rB9mBkNGeogGJAo3DB9B8XYFcVTkAssAkXW5jLdduw6dCiYuuxFAmRmtOuRWBI+W964+nEqqs+UoLHvAohF4+TDGZmoN7xQJERWCZy3M9kLRy+LMaFPsymzy2ls8CgHPCudWEd7heYzIIsS8cxiMQPQSzO2DlyWZBBWEbYIXkmE0qUEhdzt19Y+5SsscRrLBshdCHfu1G/46VWoCcPXDjAFdehclGZZG9MKRRjKNtTzhBaGT8uEl19uZpxaK0V/OXznPwJbQVmEJps8u9midFtLeNOLA68IewFjEAPx1hKfwHX8V3mrwnBss7A7HRwuwKbsRagrvJdBOZrTQMwZ+3SJX/QOCreGgvxqHc5UvoUl5SwvKJtAyT8xlBHKEKPAlqrDyonCv/ctoXskQLoxMfpV/EeCfwXNjWKqhphxr9FUi4SSSTYevIbK6U7VCz3OK9F9wHWR4mS9IBMm9AitPqbAxZMMkhX5JhsN5UobzNutT4FGXAXhWbQYF814SNDDkCbyzL2Tj8ohXYfUpqw7rGegyLkUQa2mHzC/E63O2juNXN2YvYe93hqCvILndR+zv/j7mzkPk0knXBrwGFT6GkEMfEKN6EgljB8Lh8MUDM6QQ3jGQYWEeZGSiIXQSQv6KS8cXVg5bSzKB/Yi1ALc1CWrCj3Oy8bmBT1x521rc7cgKm0FLpnAKClbOzg/pT4bleSLIr4lAmLG/xKcEP6et0W75q3uyvjm9gtStW9qE+6GMzOzzdk31RQbWtP05Rf67SLyjEnXi//EeYsQZw3RBg6piTIBHDtxcgw3l6BmO/YZqtMsznnZQiHasLU1hJQ9CvDWnIWwAGHYlwrEIfrmxvOYSMaTZDJ6Vx/IBunmSWv+tNOF/2L6q7vCvdAE2mgcDNAKDMBTbwTkv0I45SLiJaJFRhDSA/qO0FAz4htWs6gkLR6DOKSKMpNuvvWRM3eyOPnyCgxHkHVCoEfjLNj44stOm0Zi2H6NGhS15Kv+ypnLGwr8zzfWnOIfLkYRH4YgjCPg01g239hp+8awSXpBAbt4gwu95jL9fYxz/yIp28c3Uz1NveXLieSi4iz/JKwY29+q0N0WBDjxAqiDtNkMe4FweiFaAqbI8j/b++yoLfGxSBUPbM2BJ8MkrpFxbvrh2MgCYPpMBCxew4TM8J6qR+/s+hV9HAyblsoEkWViURyzKO/tgAr1qrkJffsIqElbn+Sg/z0dVumGVaorXO5ZBczXcc8sE8uLRvwXgUEHGW4DlkBrAe/GHEjMKNZd3Y7g9qGQlFzdcloSgpwUs7FwlkTFeVO2CfiXNycau3p5fJr0dY+C9an6PNi+nUtz3vZLGPa8eS0EEUb2LaWjIUfdWmUpwsMjyzdc9LVGAz+1EFdDnkvxmR0Pa80PfSbfPQzQ/C2EXqfY29OG4iVv57kJaAzpCo8xJ7Y0jZDvQA0EMQ/IVV9GlCn+0ZSq0MWH1AO+Hu2ky3pEy3maQGLP1Ibo/mfc7PM09hIOgBhMt/pKLavNR70yGD6bAB6nwi5yg8qo8ZHyssy1OchqbHFIamwxKHcvGN78p/8Qh2ETTPS3QV6VAqo+UdWjsmLuqGllHSBwTv4zGJi6jL60Vmq40D4K2LUdPEPuUt6eyO01dc66ZisMfI8Rm8MZlIkaWaYvkxfIHSCM/Yqp7TjOl87yVxtqGA12yo6FUs7Ovqh9ySq2CqftmSE+vEeFEIiyIwEho7hyRcOcNyyenlNvE62FQDxir/X6FQkilmXZu0illbQiwCbvZBDNsPEUYu4fNacNln3J9Ufhn/2MpG0Ecpw0Oe8FCIp83UlMGycFBCPr5R/iIqjnHSczeSfvhkfStCO0Fd96ZEaZPVhmXr9ATYCI9yakUwk4E/QrgFra0a5d9hnhA2o2oP3tHFIdVguAqIZEl2dmH7bGcwej1JsOhKXAoAiTpkaJkAu8/mqmjSv5hI4L3xo8I78NPrGNrCD+5ToQjiPAGREQebCj6FhwKqQf78sef/SAuLy5hmaJf+hdw1ZVT2Q6b0WPmKbA5MjOvQBYGnDjqmKLKsPI/k1fzXps2U9EOz1opmGfcmm0C7KAYUA8JB7YfccnAstQMWtOc408T+0ONFAte3bCXu0r4oVcFpILqxfdRoJ4ZlE0kVOaoV3tNWXo5ZJV4vST1ORtak31b9Z2igRx/GcdGdV1hobykd3hlTw+xaEuJ6KTIRQPHE5TmyE5fInhAV8gdPcql/KmQSVnlXJmFanglrAhzCNy54luHPITkVrQl9uP6S+ccLxMJFlQK79UrryRQ4Xezvgey+BH7YtajD10NlonGnMbOG2dEKz8PjmkiJcSAO6i4voWgF8XCkClK41RPeIXcM/r3XV2BfRsFGAAuZpmQn/QJr7I8tu8nLtXNx2XHjJdyXkOiWafv5HLlCscHPcYg2PP2DPdxJfPJe+gUMStnS8YJ59+LByNR9/Er8eNrP4Baxhi76qV3/ehUiAIJMSABwSwpilEEBu2eAq33dC/YpSCmN5kTAap/4kb59gM1BVVvax/1X0QKffhfJhyHyMP77fPg9YC3V8WzX9ndIKoiXe6nfzu4YtgHoAm1VbWocneHIPulKfQvYsuyawi3U6G3dMKFH1IM3f4QD/HeJRtjfZMb+SIWDdzmODNrvx/8U1RObJvhs3WDo3kniYSbrH/+6WcJtWc5qRc94IbHUWCoKWTwZ98wdWkZfnZ1xnp/P9TC64GiR5RmeQXBP+OEoMcsvFMBl/1SgL0cB4b+6WtTl340Zl6kV4ZzbT2Bdo8/T1zk5eAHTMz85gbJX4IhWp8ko8BvcoAm05a8kLlwO0RmO6XMW6brRTYkpYF5SZ98d5HcHfrKX2Z7SVLnBuNi+WD89fB66f7WwW5xztkQ/OUD2a9VA5NM+hsnte+wRhkEO16t8BEe1DvzghA91t8NEXWLUDuwYlgmtiNMqhHH9LE3pzRTazA+RMKfHxLS2YPSizrEZtqzu9Pfa51xzST6VCm8mUZ7FgIs+m8/Li0t1Lfg7fdCPkG3vTiJdHRSFztwjNAgrEOfk47pT/H9B4BZwCkdTE5U7t67IrvWq528KNCksXHntU1Nd598uFfMZ3Rmi+mm9es2xh7bu52zxeLY+dt0/LWvpicVJd7gjq1vG3gVmSYXcpJTZuW8PLsBZHYseZNrQsN92n+U3w8zJcIez5Yf3hu2OK6J6q4iRgtjdUZ+21ZfIbxI7NRf+rGyZKi70Fe+Wv1s7uW6T6R5xn2MEcRZl5Eq0JV17YwI0MaIwAjpEMznXhIBj7zA17H9n29YgVcOQNt/0VZUm8pl4XuRrFcqVT5e3z5hmJyRdNcsuHUEOA5ZZS4dPEonVHj+wj/+hTcCpQBhUJepqud2mv5M59W5PzPnqEJfI3R97hBuCHJMLxusr5OIrZReH2pxOTGqlE/zV80PzWYo+VXKmKyDfFCzR2Jpq1niPhtneXO1IvMItDGkIprd4dv9XqpmGjjALh/7iY4TLe/etweYbcdph5pdDt3ISv3QTvj1W/zezM7vW+85WXz6IbKec+Ky+cbbCrtdhSXfqGztP7lzcIOh/lu+sOCbwt/vlLPuel8=
*/