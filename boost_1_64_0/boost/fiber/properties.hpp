//          Copyright Nat Goodspeed 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Define fiber_properties, a base class from which a library consumer can
// derive a subclass with specific properties important to a user-coded
// scheduler.

#ifndef BOOST_FIBERS_PROPERTIES_HPP
#define BOOST_FIBERS_PROPERTIES_HPP

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

# if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4275)
# endif

namespace boost {
namespace fibers {

class context;

namespace algo {

class algorithm;

}

class BOOST_FIBERS_DECL fiber_properties {
protected:
    // initialized by constructor
    context         *   ctx_;
    // set every time this fiber becomes READY
    algo::algorithm *   algo_{ nullptr };

    // Inform the relevant algorithm instance that something important
    // has changed, so it can (presumably) adjust its data structures
    // accordingly.
    void notify() noexcept;

public:
    // Any specific property setter method, after updating the relevant
    // instance variable, can/should call notify().

    // fiber_properties, and by implication every subclass, must accept a back
    // pointer to its context.
    explicit fiber_properties( context * ctx) noexcept :
        ctx_{ ctx } {
    }

    // We need a virtual destructor (hence a vtable) because fiber_properties
    // is stored polymorphically (as fiber_properties*) in context, and
    // destroyed via that pointer.
    virtual ~fiber_properties() = default;

    // not really intended for public use, but algorithm_with_properties
    // must be able to call this
    void set_algorithm( algo::algorithm * algo) noexcept {
        algo_ = algo;
    }
};

}} // namespace boost::fibers

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_PROPERTIES_HPP

/* properties.hpp
pv8c0tVlR7HInsu7cL9H46z8S6WwIuvYrjh5OnUHaIlSeexlHNXnmxsovoWpPu9Pwm8WPjca5fDK8q7NEXhk8GL6eo8DKCn3K8BfjkUP+K+szo4N1GnEwu/BTkFPT8A2DVWgH1RLLEnmPrPqP3v0fN9vD/zsrjKcPivmX+a/hkabfkG6NTi71HwKr3gkiGFqUq5mCel11eitaiR6555jT2/HCZ2jZ7XiLpspaPFuD3WO6VfJsTSx53Mvp1wwT4l5Ph9miixKvcoVGUVvqLw9BAXEud+H+Xgc+VWgC0gI/utmDJwixq/sGJD3RrmBEEkNT4PuTTYrCpgGVwSoQCvlHjob9QFMZeR90UJq0faFOFwsxeHiGh4u1l/4nzGz6ud/r9LP/waTOh+bcZX1/G8omf3mN2eQrWbx6R3tB6+eYd0Pbp6S5P77FAIlqPdGMlTC+uvli0e1d143W/L/1mntnNfdeaW+/z8yyf3/K+P2v3/dmf3/K637/9ck8z1GEJi4gDs4qckBjmsrj89yhDKcxhcXkf2qP8xG10Ma3Hw9EjQXeOtRIt6Gwtu/1J/FLvELNbq/+xwMm67f0H2FOjEJuSktwVDzc3Nw5ndScrQpVtZ3xUH2ZR2mspHXiFQqZomywiLmowOJxmBUAqhAkyogt/WDRnkGdMlvVLLx+skduwt0+Iv7/tPpSzjpS9ASn6qDwyrGH9vsFnnb6Ybtxvo05FQBZFkAtmoATjsAvwUgpAG47AD6WwDO1gBSGIBvJle3567srlK2ia/sSFZiOvezdUWYOM1GyNgZylv/BiSQCAzCVBXuKQdnhPKpVXyiJQBxyT0oOGWYK4QCq3bqqm4Oq1SVbMbmignWG9LNgKz81HpixuLE8uAglVgeGWFPs5xpvnsf0SynMoSPHK3mtoorevjwevlmwcTXnwdDT1HdrCR5yeKbegRkEvdWij35chprDair7s9NYG2fIcAr1wfcyBpafwJHsETjneWKEpYUPMs9MIrzrVPrXp4GdxrmNBseU6bTnGmGdJkz/abMFJWZXOUFb6rrCdHyeDe4nXHMYHJG2tz3Mb35fU96MzMTl+mLZabEZfrTm5NjjPXBRPa3z6dSpyPTAulZm9xaReBkjjMLV0wq1amnFqtUl54aVKkpeupoFK5mw4Xyn9ISakbTECQFKSkok8pDUJKSRsukMgtDbicOC8yPlpjH7GiJ+cyNllioEt1aYi6u1XBQ9Hnn9YN8YMUUXnETtpgPDB6hJnb45R5WgzvyMiBfnlisBpvDOeBOjhgaGAP2qWa38fwPCkuDCUsFrgKxJuqQSYWGZZEZi8eoZyyLTFjG4s6HdHsvFMq3hmWJGUuG8UvGssSEpVIdyiKntmYjJ4VWtoAwV36bXGwjNBMFvWub4W8eiGoZPD8PxFC1EVts/FqIjhf0ym2G0MUadKkZukyDNiPL9a4tAwnaLnFVSFxBDVexGVepGVeZBVc54xorcY3WcAXNuIrNuEotuMoIF7UiJkEPouYiIQniAzYpfeP47x/EB1VgrM2nDeKDKlDZ3lezfK5c6l25de9/n4JpOZhW15ois7F4QBYPqPcCeMdpAcMzDno19HwBPKc3q5xmYwDikYXzJHCeeteA80zAefHA+RI4X71rwPkm4Px44EIJXKjeNeBCE3ChBNabBsdA7BMUboGe+WLoOgPS6Dn81nfRqHlIwmZpzHKahySsrpboUon5nMhDErCnJbpVYi4k7rMI7QU/W9fWDZO0Q+g4c5lkotwyIzm1xHyTTJRbZqQULbGIZYITaYzIAylNDSrZx2PlasLIkUO9nllM84B9ZinaROwzWfOlUaRCdpUxIfgHo0jB9kE=
*/