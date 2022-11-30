/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    eval.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_EVAL_H
#define BOOST_HOF_GUARD_EVAL_H

/// eval
/// ====
/// 
/// Description
/// -----------
/// 
/// The `eval` function will evaluate a "thunk". This can be either a nullary
/// function or it can be a unary function that takes the identity function as
/// the first parameter(which is helpful to delay compile-time checking).
/// Also, additional parameters can be passed to `eval` to delay
/// compiliation(so that result can depend on template parameters).
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     constexpr auto eval(F&& f, Ts&&...);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [EvaluatableFunctionObject](EvaluatableFunctionObject)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         assert(boost::hof::eval([]{ return 3; }) == 3);
///     }
/// 
/// References
/// ----------
/// 
/// * [POO51](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0051r2.pdf) - Proposal for C++
///   Proposal for C++ generic overload function
/// * [static_if](static_if)
/// * [Ordering evaluation of arguments](<Ordering evaluation of arguments>)
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/identity.hpp>
#include <boost/hof/first_of.hpp>
#include <boost/hof/detail/result_of.hpp>

namespace boost { namespace hof {

namespace detail {

struct simple_eval
{
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(F) 
    operator()(F&& f, Ts&&...xs) const BOOST_HOF_SFINAE_RETURNS
    (boost::hof::always_ref(f)(xs...)());
};

struct id_eval
{
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(F, id_<decltype(boost::hof::identity)>) 
    operator()(F&& f, Ts&&...xs) const BOOST_HOF_SFINAE_RETURNS
    (boost::hof::always_ref(f)(xs...)(boost::hof::identity));
};

}

BOOST_HOF_DECLARE_STATIC_VAR(eval, boost::hof::first_of_adaptor<detail::simple_eval, detail::id_eval>);

}} // namespace boost::hof

#endif

/* eval.hpp
OyrmMvND8qz7selJT1EiUEBzqA5P6CpSGO7d+PefEKsGD4aqt3TAh03tGUsk6lf3bC9o2xf8WgDp+GieRNrAxplhaZB0HLT+4EUoxvTogQC/ch/2tYqdRblktFchseA9ErkWXCGXHppAWbihIdvi6exAVvCpyMmZ1lNk0gAPLPDTvt6CXtCLx8gBcth+OvK61GB9AcUUprvjlL2STPdB2gfB6Vg6gd88e5bGR/ugcXR1Q6bBGMVPMV3+Os2L/mopw76sv1qhrWDyvAf8xGN8FvuG6rR9A8GHrRunyggjBZgyw8dY4wlYl6HGF7I6u58d4N9MpOpL1gtNQ/Z81gum/W+L1JZILsBy6fMTOEBbIjgfiepoHqLaeBWpmKGyf4us+6GbA/zXL5J6mThcA8NrMB0/IvyIV6c9JTTjcroQzTHQzKIPF7BW5Dz92LdbX6O+TbFQbN67jccbsqe46N87P6p/UXlZyerf8bsXG42K2b1TYbnEqhUBNa9IdrFs9q+c0b+TPszu32Juz6uenLqP/xPtnlijgtoZtGCgE/pibNgTx7MbFqtay6rWRMvZantoXEIbDzzP2rZyoc5VzJaU/QbXS9g4KqGICo0KL0CxkYraQNFlcOCZPxKtp4OvRThtGcRTDwXE0wGP4Mq9ALWYlFS4JR38PQouzAqeLyfDg7eH+qVQjxSuOheKOLU41sW29U7cA0J9tfFmLymdLSgLr7DgiSOsxIU8KlXHVFFBNONTF4ci8gJtHG1SmgaHsVHDTy0elkP9hcPWUL+VLF0OlD4fGpMIt2Lrj4RdZTFzl4UDaDKlhJXDiB+fpyscZpOeyO2KZMAD+btCBAfvydcNZtjafN2wSXSDA7ph8YRuyOwAM5PLJnbA1Oy2O2jc56sViVBcMi9Fym1bcYazCHMXZ86HPD1wmdnOZ3I6IPn90bztT4a2558JIji4AUahXPRCqDuzF4KiF1StyVXe7BH9UJwxHYQ8M6M7zAyvoGsxyFT0SJx6ZCC3R/DcVU7zgb1q2/pYajYUp2cD4UuK3igbRG2F5HxQzYb15c6HZMCPU/2RTmhJB6c7JCNfORke/A71SG9GjwyIHsEjkgbHumY92RtLsTegrgPDk9P9oWSXRx2CrgvLq6hDKLOmo8NTq6BDerFDeq1ietivhzN90yTUN0Eb9XJtoMkaXpUgBbjaV+Okj6ItJMsqu+0BlG+xBMy4JqjbA7ejAPm4BJtobBbsioYnoWHTNqrpTUKGbL/R+gEUvlY4NlmHKLbVpIcSNO9/0OR7jasJbb4fFgKdp7fDoa9mFUKG/Y7wwbcL5Mu2brajQ8AdchJCHBQjiAuJHe0Gy6EjylHyWh464YQOqcSrJdPZQky4OoQYOoaYDhZiQiCR7XXBdMCY4anB9MO4Le2HscP0w3g5dhHC6i50zcMzfiVf8VocN3UV1IN3HY+jyL1c6BPCSxQvcnYO2wuEs/LlirGFYFP5TmF7piSly710+dH1M6Hxamdi9joqSexst3UhxickF9ABF1YcQYCpns4e82QjF+THEsB4DRCxvrNndVrKBItfR57Fb24MOssXnTSws5xkyUKSNQpfEZxonggwZVpNpkwriJ2yLBZPwHq5hpRWSJGF3KALCKBDxpr/CwRIXDncQACAQ0u1fXt8VNXx+G5yEy64sAsuECVK1LVGiRpJrMFNNRHywOaxuyEPhSRYad2mqAi7iAIRmizm5rAYES32q0h9/GoVLSpVWjWGh0kQBETUYBLF1v560oUKPmLC6/5m5tx7dzdZbPv5fH9/ZLP37nnMmTNnzpw583DM4ucNouiLIqmvADZtF9o9wkFiuJSG9yiXsndwGVTwtw8JERpFVbywMEzjZ2y3maCZkRX8t1qRIseM2pqGTnV2VJnI/f5QLH2FmXbc45XBIGKetvzDvKhnQA0GD8ILnktfLXiq/DF+LX6C33XBIPzfqh+0auGxzhQs7kHhgN82b2jsleD8cICX/0J7XvgwLIIbVnZsEW4Iyzn/8W/61fa8I2boJ44lNje9oumgKxJMpuYmcirY5Z/VXH2kvztYzCd1X3JIv98JdAe3HiR13U24nvdxZzGmZeXB8i4PL4Vm4VWV9iqvy8Ut+CpRb9PXxm5ofvAV7Sb17xhq60FHHMbsde6wNr6Bzw+lou5rOPkpeV9aGx+FEk1PvUYePazQ5lZdMnxpWo8hS3ZKzt2+dNaCGktny0b4BE629QksuwLN+ipdHvUDLE0BTnZalCYswyawZrwb5/FPApISE7LQZEHMIE/pHkBL1ofFTX3Ahed3PulmuqJ3wbQB9uL5UpDwWWAWslo6sJZ/IogokbXgyBJSEJwPlSexhPJkFX3OgU//RUr1l6Frg8FT2NWjj/Wr3gUXT7OJZzd3fgYCXqE85b1YiGBjpj3+bBy5rEnWRlSrGvwccf2qmM3Avdh19ZfW4F040CYHoQIHE8zuBo7L7Nb4QRCPg5kq9rhwpmYVUPwEtJvAn56EA8vCEFhoEgBd4dXZ4o/1q7PyrUoQf1WAh+NnDuqWkKj7xgqTgK9RnwvPI210P//rcQOkau5GDWhBCrLZAptYGpq9Zw8ZgNqEAaiM5qBAvCcPwVIJ4Hy4RGG3toYu7hHtMa2bp62DUKS4hw+OhWmbCBNmV6kSlkYz/1cw5B6+d4j3ydr7xz/QFxVLPNtKW/GDt14r9FuvMWuQiGAAPRu1q69gcK4YYCqMp2fj87o16H+4dINBvPgiaHju2pNqQ0dqpfY4FR5781ZHXYTdgFcM1at789aFr8GugHcAU/W65qa5RPkyrMNxzU3i3sknB1tQ2xyKyzjAmpCogluRfio9wUctNKOPYm8e1rKEbDFbfOIfuWitwLgoHlcdMq3yHg+/8fCgOr3vPnSnGMN//Q9VDS1n/sO45loomrDvxmCwBaeQFR/knjX9asOSJBtQ1oiFCaxQAvmpkNbNOlxvbrWlRYAr6vC1z/SpW69YNcG2g+UdZiajzbFaBe9h2FLUD6CCVsp/OKMb+0aK11V+Vz4OEzSmfSWyEDPyEHvGgeaWV0WHLgtwSRE0cc/KDly4PLhFVfEYfy36DBlLy29rXzGXWpjQ/mvyEWOJ7Ss205cxK7ehGxf/Wz48LOd9T6I/53LenHeksY3OfCOguY8fBq6Y91ZGv7MdecZFH2q6043OdsX/luJvU/w78QdZ+yHWSS/a/hojCgqDUM1VstLamJwQ5SuZbG0clRDlK2m3Ng5Ikb6S/5QojwJ+/Zy+WvDrQQmvhZfQRpQiHPKCrVm0mYBMlNm1q4cuepGa4TkbnzU6R3dD/TdZXPwiSV72MazpDYjgskrNtHrGcVVtmuGY1EzOdriuvwC21kweePj0YfwwGIRLZGTv4uKEN/7VbkKZLhOhA0kQ7a7/PVAHDoK8Jey86HZIdAK9YWLS4X0NG2lEk3i9w898QTdLUFuHoyUSjmRHbxevMfoUvWk3TTu+EAOwd6NF95GU6DFS6xtR6a/dPIHUmqlPRCxwCCl3QwUDJ0UObzQgH30YHrzPGDyegqH7oZOsgXABgqBdXGEC1+Eg4NUW7z8chYeIhnTQDh6OAE1YX0VDd92HFGQthZ85AKx9Nx/xJ1UFwlzTiknJjpJlq77/afdprQ7j6i3+tLh884Q3HZC1f2jLacLuhBCPgqcDb+RT+asfkXB+zsp3cR77sozpirzhK/2PO7kEO5nlKDSsDFK5K7qHj036VWFkD0X/cQ/bDgyIwPK6b0Qq/9dB6kEWPYTujbxg/W8H8LMDhKW2aCytju5hPFuFMxH/rotCs8PcndwP2wlaGQXcZ8QF04DZl4fh8XLg1ytfA3EDDhr1GWwNySsDzAxPyc5VKMI9YJ9GSR8XWxS6mGb0JGJLl/o/KguuIvGN7eXje1UMQzkJQDmvnbxkzcE1KLe2r3qVNoIZuXiVUz2Em4b9I2aURfPSjfFhXmptXBsf5qPWxsb4SB66OJ7S88GJc7lF5L6dh7yLiB5zUyBO8XzjewDgLH4FhAPATOQU3NGdZxHrDw2Cwi7YCfdfIBzkhR/DocP8f3rtujVYVyi1B9oRLUyicmSS0tUnSvO7oSyUimOf6wCgbQwtMmHaFUDrV9gRGoUz3jebCbLUSMjmd+fJBmQpwyFLMSAzhyEbCF0OkKVGQpaKZQ3IPuqxU3YOtlwm7CDDtQPmuq2NV8QRLA9uh9k0NoYT5vDG4L9O9CJctc29G3D1617eCyK+L4n47qWLXdQELXeIJdz1BQ5V1OghDtL7GH0CrKEUQkPkW7HsMRPqY9EMAE09IzqP+QO2EFCRs2Pv3ojeaS3Sgu99bMmQ3iPeijVLvXvP1slZf1hiWCxo7VDLwdwj+najZV22MorbrNlMhPESvGloyaW1GW3OgeWYNyh1yr4QqgtTneh2kk7v0qZ8CO8wQBfmZyCTEOQUObBjYGDjJH7rG6r6fXfZ959XUhBgUQQ5ShGfvBVEyDHRbvhkJ7NXRCogIidnfv5tv+HtFOUx446KHpFijlzF4+B/pdjvcJnGmSOXscgH+lJ0DATWIyDQt2uKohHG8hgjwgAsr9B4LKjFtvAn0iuRy1nbnD/tw59mWJmCZqMaefvQW9TW0HFEuCwBMmWxTNDZ9tA2gfOE+y+Ptn8je0aZs0N2k6sOV8y1JxEdGO5zaBgD+DHrHTI3sulo5G98Fy4t/v8A/iqFeIQYowxYBhuMhb9N/5/w9/x/gL/n/z3+6kwaBhOOCQzO7LLT/vHd4A/gb+DtMP6I+O799qz402VWm3DjFX7D6BAMEk7usUO7eoocyT25A7SvAhwvHVHVKI/zCPT7btRJ13etjnXfFB3jvov4XICrzqwJ1GUfUsCSt/6C/2r6Dn6jqjU7/rv2bNieSWsvXrQ3X2uvUWsPndv7/nHE8CGuU70lzUOVY0hElRmq4nPISn2yUp+i1DuU+jSlPl2pz1Tqs5X6HKV+hlLvUupnKfVVSv1cpX6eUu/tADzhzabS2kifpMFtXU2f6+hzPX0+QZ/P0iclbmtFS1Y4WmwW7mJJI7jdfVINrsFTUseqrXq05snNFEHdorRSPPhWyoTTSknQWynBWCulDm+ldK+tA/RJ6cNbKXt4KyUPb6Xc4a2Uy6yVksi1Utqy1mT6TKFPB31SevFWSijZSsnFWym3eCumFo+4Km3YaTNkEsDn2tj4RGxqIwI0oWkdv1uB8VByCbzxwwNkx05x1zcMOWwVxQOgQk/rhYbilK1qNAotF4XY3uGTgf0TPh/CvDyAz9pYIzHomW/9CymmZWgrkU/aSnSVeRzd2iUymMTVQrGJUAZ7zSwyV1+gRSgiC2Nt6S+9SrwM/RgDDvRcYPpDurjD8E/pTcCHqNL3j6oxAshpP89xOKZ2o73aX9Bcr0UsTUdHIm00G1qIoUWEpBHRdzCsgtDX0MHN53BER+HB5XJoGyxs22d9vejYHyFB5XdjjISvtcMNAt2GUZA+64sUpkbpbDA0FiQnWWeAXWRTTByHPRYRE0iE3qH0N7MoKENyOPAORgQiJhMDlqJPl4HEtmrzD0AyNFzQpBjwRIQMKn2d5tL7Fcxl845hsfo0/1WK/Bg4CnNrbTyCSnOMIYLS3me0uyxzpOHesp+Gpm882ImmmHjObCgmfouMqQ4JqENpRbb1OBvIODHlhPWPJ5UNiJvgBtRQKS/T7E2XpsQ7B3w5lXDOePdlqLSPOdkH2/riGjrVb14U4bleEOxPmJeKw62Lxbs9ruAaFEv42/+HRvjYc6gd7MoQKryIHc5/0/CYS5ZIFPa0bhYbX1LPBUuMWmPC+kANlb7IHmyRPdw8PLKRJTKukfi567im6cDNNmZP+m6aFG7J7B8LXf/5WRXvmpIMGcs2tMQnooTWIbyo2EJoufso7IOza6px4i0a2sVEiOkJ/xYVTwVjFFKkCZvbw3/1GdnlRMTDjhmPohGKsfZh4Sj2MIruDUBLj2OWPLG9uxjF7KY3Lv44yEbGFs1W0nw/7KOZpmIeF684rao7Iu1DKNKM85DvCs2qpNJT5nLzpz4lo0M4pKLnSoW7kr/Ui9CnoA2KsPRJmh0dYkTcHz3fPPzKLJnlkUMiGva5gsVdiv8I/xdmW6qQMnY5P1CKT5FxlKylZJDgeOkcBJEMlfwf+PSsDdKbwIitUw45Pyeb1Cfh5DQkoaoUv8+5zdqAwi/r/KBPL9+1CFuPi98Wq/iicfSWepep9/gOQDxam/KKN9AUBS0g3awLzvMVZR6XUs2VagvdYi3tjjBALe/SrE/f7Ym0PmUdQ4xPlWILvwkrlpD96a5w39uw7wHKKVuOLzwVMA/X9VBRN+96GzcpOyu3xX+IlnYnMXpQvazUSH0DIhcO83NWfMRVwRtO463g798OG6B2wg6H1njVMuucshtG7tyn5HFrA6X7K5c9bB96PBXbKuJ3u11l/GmcfCi+Hzqc8iFMmHvbCWnKiUoQH+li6KbTmnWpTViXFneFTUvpts/8KZmWhm4DgBAyt4xY2O+BvuK3u/hfT6H0BXClA1x4XbOPDUwZhP4xa1mFy1XJU4QJr4csTbmrsoyXYOa7chsCE/+hp4xvOCQMTfN6hL3Y1rdi6pMjSDQc33zc3KOAoFWihmGCZvgTdDaH/QmAau+RAv16kAAt/69bnvIxoAT9jZ37F10S6B/y/h45uMyRXDllO8zG32GwISjim4yxyD+hAs7ti8YiRtorXSJn9oJTIoSTGMuRN/XbWtnwfgB0bo+2PwVI+4fLT5pqYltvUsYujXdWySLmmVLoUArTlMJ0pTBTKcxWCnOUwhlKYSEKuh05RXFhVxESbtykJ8rPrgzWZ+Etpi+ZTNMqZXcl8BHEPyuQXPxGAtau1EpKrazUAgtJE9eFPxKjUGrSlJp0pSaT5SeLH0a/qRu+Jis1KUqNo2Y25hroY2pUvB4Y329YLOOzck1GtGH4BExPxnNfQWfIpg14/RpsDSvDzGyfpiLjV12Fe1867nTPNMgm9jJ+dYZAhE4ZCUTxPr8T3pbze/4iUL8Pf5B515XQ4Bq89cDnEbyTnrdoz4l8/RIQS9fg3ZJzN75J0BMSCOWgGO8Fok1x2lA24A/KhlT6TEMl8SOoLVyF27mL9/8ZVmorJuHDW9+T2KbZN4MV2ERTB/4scFprU2oB5UkwA0x2odYhGSPnzZxzVEzKC1CuUkwJ30B1QKCeA602zXGk8Ivr+9VgSbIRVm/ht8KLFbWGBgXYh4i3Yf+6I2y4iQCdl8k/9DgrKQRy2V2p5BdZGy9JMJneMZOobQ28b9Y1VWLzqgyWJCn1dqXexh/aHVKH/JTK74eXGBVkpzLPkQJvspQqSQFqrrLwUlww9dkinhXbw995HA+IgIJfoLU8sJySQhcmQBQBSO5Bd8r8QvSvwgyCbuUJyjTIL5+CF8N2l2Z0095IGfjM3PztAF7ZYG7Pt8jspEl4seMUlG6lKRA51HxXQ5HVVMTaeJ2EM3j1Vt3XFk9J0ab1sklLKcT3HR9QgzWALzfbA6NLBirZ0o+CxuLfIu/NxjBx5RZlYm9ib22SVqk3vrdWT3lTq9+pwgQ3HBdpWchZdB35R6K/6BMS+ouWpvKGBSdRnb2V1NnwfK4fb15Lq3gd
*/