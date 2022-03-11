//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_POSITION_ITERATOR_HPP
#define BOOST_GIL_POSITION_ITERATOR_HPP

#include <boost/gil/locator.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \defgroup PixelIteratorModelVirtual position_iterator
/// \ingroup PixelIteratorModel
/// \brief An iterator that remembers its current X,Y position and invokes a function object with it upon dereferencing.
/// Models PixelIteratorConcept, PixelBasedConcept, HasDynamicXStepTypeConcept. Used to create virtual image views.

/// \brief An iterator that remembers its current X,Y position and invokes a function object with it upon dereferencing.
/// Used to create virtual image views.
/// Models: StepIteratorConcept, PixelIteratorConcept, PixelBasedConcept, HasDynamicXStepTypeConcept
/// \ingroup PixelIteratorModelVirtual PixelBasedModel
/// \tparam Deref A function object that given a point returns a pixel reference. Models PixelDereferenceAdaptorConcept
/// \tparam Dim Dimension to advance along
template <typename Deref, int Dim>
struct position_iterator : public iterator_facade<position_iterator<Deref,Dim>,
                                                  typename Deref::value_type,
                                                  std::random_access_iterator_tag,
                                                  typename Deref::reference,
                                                  typename Deref::argument_type::template axis<Dim>::coord_t> {
    using parent_t = iterator_facade<position_iterator<Deref,Dim>,
                            typename Deref::value_type,
                            std::random_access_iterator_tag,
                            typename Deref::reference,
                            typename Deref::argument_type::template axis<Dim>::coord_t>;
    using difference_type = typename parent_t::difference_type;
    using reference = typename parent_t::reference;
    using point_t = typename Deref::argument_type;

    position_iterator() {}
    position_iterator(const point_t& p, const point_t& step, const Deref& d) : _p(p), _step(step), _d(d) {}

    position_iterator(const position_iterator& p) : _p(p._p), _step(p._step), _d(p._d) {}
    template <typename D> position_iterator(const position_iterator<D,Dim>& p) : _p(p._p), _step(p._step), _d(p._d) {}
    position_iterator& operator=(const position_iterator& p) { _p=p._p; _d=p._d; _step=p._step; return *this; }

    const point_t&   pos()      const { return _p; }
    const point_t&   step()     const { return _step; }
    const Deref&     deref_fn() const { return _d; }

    void set_step(difference_type s) { _step[Dim]=s; }
    /// For some reason operator[] provided by iterator_adaptor returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d) const { point_t p=_p; p[Dim]+=d*_step[Dim]; return _d(p); }

private:
    point_t _p, _step;
    Deref   _d;

    template <typename DE, int DI> friend struct position_iterator;
    friend class boost::iterator_core_access;
    reference dereference()     const { return _d(_p); }
    void increment()                  { _p[Dim]+=_step[Dim]; }
    void decrement()                  { _p[Dim]-=_step[Dim]; }
    void advance(difference_type d)   { _p[Dim]+=d*_step[Dim]; }

    difference_type distance_to(const position_iterator& it) const { return (it._p[Dim]-_p[Dim])/_step[Dim]; }
    bool equal(const position_iterator& it) const { return _p==it._p; }
};

template <typename Deref,int Dim>
struct const_iterator_type<position_iterator<Deref,Dim> > {
    using type = position_iterator<typename Deref::const_t,Dim>;
};

template <typename Deref, int Dim>
struct iterator_is_mutable<position_iterator<Deref, Dim>>
    : std::integral_constant<bool, Deref::is_mutable>
{
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename Deref,int Dim>
struct color_space_type<position_iterator<Deref,Dim> > : public color_space_type<typename Deref::value_type> {};

template <typename Deref,int Dim>
struct channel_mapping_type<position_iterator<Deref,Dim> > : public channel_mapping_type<typename Deref::value_type> {};

template <typename Deref,int Dim>
struct is_planar<position_iterator<Deref, Dim>> : std::false_type {};

template <typename Deref,int Dim>
struct channel_type<position_iterator<Deref,Dim> > : public channel_type<typename Deref::value_type> {};

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename Deref,int Dim>
struct dynamic_x_step_type<position_iterator<Deref,Dim> > {
    using type = position_iterator<Deref,Dim>;
};

} }  // namespace boost::gil

#endif

/* position_iterator.hpp
VH42C99vxv1kCk8FrZ3lKzsJKI2GgDxOjC0n/lAdn9949XykOj3RFXB5i6yw5gt4Q26h8S9HCM0UG8nq4o+EWnMF8R3t29Ok1FwOvIuKM+Da4s1lLIincGJSObj/aLdZBynbMyneBFD2CwEwaIS2WbHoWvKkauOoUNerM+ds5djs6et0juy8v0m4NeYq549X1rUSPVSfRTbbHIm+AJd4Bg0kCnRYmLksm8T38BLcZj7KWbZl3IL3RziGN7Km6GTHx5mJTg1u+cus9IQcCeLOjsDnboHrk3n1gwKN58fhr4ijDRzaiFOoRsuqoR3O/hGFXvZhwmw8pIu9cNEH+gHk+sZs3ke4g5qYQrPCJydCxc4OG4ydU9mepU4yW8SK6tyZfwlLT30Fv+Lzr/Ld3W4ia24ioSfRe4/2pzdzbUB7P9X/Nj8SMGT0NSeXh9sxpv7DP3qph3vo5W1/FxiGNZqevGeYei9UsX/ldiGbT2ngCfHMxb8LrYWk2qSOSxig8BAXdVeQAZHHfpWiO7WzHK7oGKyWQu6eEl4kPVoAvDiEVssNwf4MKZp6e7X6PFJAZVVUImgsU/VKvaXrbEjHoTKC+MF8c4yKKZPILnbn7SNAeafb0PoXigYIYk/A8xb2X3+yJbPTB/4ohf1RxOJqjGOxJeMZFIxMZzxsmZxUu9684rHJLT6sv1ufY1uVWYoN4piAGsSrY4roQ5kwXvMk/L6aKVD2iZicGxR3DJM0shXd0AmR307y9GgEqefdA2GPhs4hgx0h4C3/q+byq+q2KBP24gyngaizw/RTSysZzy8FrMmzuA/jQamaqq2TDeOi5vwmjrGqWGaK9vNjBjbJ7BydTitdjes2yKnxHnonKJt8ta+6dUgjyC20x3AO2EJ89qju2wxom/T02X+rNwiausqOXcNR8a7V/8F6QG0j6X13RNfyBgSu4VI2N9+avPrikK2PoAnwdsOwlK86pifvwJfAT1e5auhCt9Stcq2CGODROl9Up6Yxa61ZwzvX7Nks8LvFQtgDhxai0QPK6QieAb55xd4mBVKzpV9D1q9vd6prN2qGUrNNWYyYwT5ek13CvWf8lFjAcmm9Rc1M+uW7tmkeMzMHaBLnfWQRbyvjRxJOetVt4GivJGtmqqwok1nJ/aQC7OKDlFGjuPkQgddNpNHLlBkmmS2KrSam8IAnzaR0ewb5EPIlINn1l7DegW3kZxufQJdJJXeLp9JXfHAJMcNU+nP7CQKm74We5TSTRtDlzJJnFRijH9cbvS0mklG1ZxjM4Iv2gtDbxtXkG1A6EqFTiude6c2Cfy4QO/mVPAqeCW5jRkwwyrUyQSWVduRzPCVypFAVv+xb9u75lWsMU2m3r+xMvLAbqrgw96mFSuEbHJ/Vnmrcnq3rfGU1WIrbYMH9t77tpJDsvAUgRRCuiwjmDQsjuO8Zv+Cfnfiar/wyMpTzj5rCtS/5+8Tal3K8W5v5t+Vl6aOF/wXglZkb3oKWjN2RH9mg4tMVw7V2e86nM5RkhsTFDAHA9lmIneyngY/dnrcG8MMBPXRjIWew3P2B2NCnOHsRkqoCm6R7aiLtqtTamCxc8WMGMZYE4PU23CUJZvWgiBTzvkMUuwKwutf8oQMenEv8c4GTyb/GveRU2CluFncBudeG0Nya5QW0bDJDN0sIHNd1T06LhbmQIn9Bxvoj8aTRFEseRSxtfHEli0tfFFusDMHqX//puFTyoiplx2rgTmPi1OTsEkrDwcPDPzOiMtlK8hn7oNMvl0jY8JzdrFRiHsW/vAbFDee55INqliZFXi7xP3G5d5PuYR9U3FKp4ulpnm2zvHYlM7KBbOOrMRueWYI6a5+VkFhPmiD0+LWmPDDbWsQeqTE99FrfboeE4dHwc6jTfMd/hBELtzDABHakEbhXjHCMgln9P1hhrcivnz3greDgqsIFXEC/BtrYb0tfgFP4zpcbCkZTGxGCcOGY9LEGooYZzUSH9KMInM6Qk5gy5mtBm2fIDN3+j1F+yzdOTHviWC1d6+ldb2oV/MMwJQwJ7DKav9DorhUPodKh4JRGJSIAvXuxnb3RaebzL1uN8RhIBM4lGjN0vXdCZPNTEhHsFH37AAuHhj1f2TkoNpj0/plwKVQNkN1PVj0sSHVdC2TL+3lF01EmH2858ei5R2o5RrX/yIDcb9ZA1dG1FxFogSpTMoZx77pa5PvRFbxhxSLdxVVGEhUYGei6P3wga0E35v7TjthdRyVFUPxnfLhFS8H3LOsT5B66KX9OEXto07GTZZqKJoAOYl+GJSo9fM5zhLFzH7h6rb8G3M/YDaf/zDXtAmN2LZQ0L0ew+471wJ/NH/NkaMnbl0ykY8KM6slWNe5CATQukZ16ombKbm1VstCu2LEBczx6LSt55ZrHZmnp4QEV0CVoRupfEc19L4xVt6aAK1/H2ft0VozwUsjlkRtAcHNAICY4kl54GOmLCBLUdW9sPT9KPK9yBg7bjLN08vsBNDY9w5hdZbjKu2aTXCdWYOwxeVza7BNk7Q3abgZ59PbEh9t49AnRaCJkQ7mGxDQHGyNGgM+KgKAsuO9sV7e7XJBZ7UVQqIKHVLeE4Jr1Zcnsm4Qs+nXeaKXdiphimCVzhCestOQRJ23/Wh9x2PRyH3vohhC29DZr9DItaYvLMK7nlb+asRhCU8ySZzBlLZy7OSbU0PR7n0tXUe0h6QcgCZfFUGdNbUeDRC6C0yl48F0V+QGe2/0ayVzPluy7NgFTAUe7DGlJROYCjG/CHwwuc9Lp0cEb0RY7Vz4X5wKm2q3Xszn5H9cGKqyWqam/gYqqfFVKRo/r/HYAYxcVseoVbMYBabZbXt6mWh9rmBTcthLV8j6X1iqri8RCjipZquGwxKbV7nCqjRovbkSyjRKURUn1uWwUcPQCGewq2+xPVyjbFdyRJySdjHcj6WE0ifLxkRI/nZRChvD4PiBUro0cfN5HbZVEp9K63tmyNcQxRgmY3Ql+5L//GPhIC11H7OJWnV27G4FkpoVAHmyv1HkcedAqDuaeTnB46tVCBOCy5pHex1lu9jbFydxhbxJtBsalphjFfEWVvNq+iUT/o30d/qeO9qTYfCrnoZcdjh4uQbiHg4PBA7YdqL9Vf1Pij/ntDfaD+nMiMWDRpoUyuqnVnZNnGzZRxKsXlz7HzdUuuvhoxrGp8SZniW2wCEEbN7LKioJZ9Pax5x9xuE+Bgo32NaewfKTzIn6fHMYQ5UQBJboWX9B+c4sz8qBz/ZN+FxnXnNUp1L3mmyb5Gny3n3FnptCkECTFvLk5MKKdBsXafqRu9ni8T3Ag6MIYyl7daz3GIbFrfDfGa/x97vTLT7DDC5nvADiYGybvP1iO4jPIIH1D4qOEoOYAea62WaotXR86OIT61CBUoSn9/9vJ3gj7KcbtS4VQ9v+ODXrvIESxYXdVCCcHQLXtkoI7UJ2PDbI4lOq84c067ghG69y0G3saxXrFYl+WQb+Iztjqz7pk3FsXyaF+YQkkdwh1xr/TCk5t6xKCoalBOT2O0mBv6KY5gvZn95Hz2BzbjpSBUfWmXWmfJHTowKP7Iau9ARnWXXDbu76kGSQ6kjuZjG4L2G6N4L+yt9BvE/QXRcl2YMaPVHig9oHbOl6P8pnmRlID+HIvk4MsODUKcnwOivZlGQ8vwmepslq3u24O3Y76LOyTa7cGqki+58XAP3sjWxXA/K7tOsJ7PR/he3VNxsDMKMmPlcsAMDBsfzz7hTc9q+jQNiMD+28O6OtZDY+q9l2P/PrMDKAY8/PVZwL2bN7+GpVMUsnQwWw4VTO4BTBKtTfNffM8JXrdcI/FDWoLagayy1pig9K2tpsFN6l4+0iL/vS90yLTBW+fVDNyGDPAGxNA8/P8mUSnTwOoz/y+cej44kEjsKrX+xv1Fj2Z3QnboPsb85YU+QSQIQbbiE9HWlhbm7lULsNE40mvDr+oKxQ621V3qEeCiEvw/DiKXww/8gP0gL3Xu8+hSMQTsCgOFGOmkaznHTz1x5bk9qfgzbrl+RSwvYcCBeOiizSyXdImRyOxPA4ZaJRs0cCDL93xIJwJAmrbY9zcb7tmHl8r8kllaqsa+R/UVsXHLpu8qfcqlPSj+Dtr2HPg0VYdY7UsjstOML/LOO71NkL5IoOpmeeLczlLhLVJGvBXg+nxZD68/L0WFEO6UslRp9zuAntOiznnzQGizDdGUgbwV2YNZ8Y6mD3LTRcAeKtX+ccDslNEl75/Ysd5ulyJzyuLJrIttf7cNnplbXrq9GomOwSnprUItl7w/qLaOUDYLbaGCqZ33F8i0h6/717L71OW+e29v1+luonCLptGeKDDlPNreIxks6Z7F/ocwdNgInAUiPDeA3WA2OPJuhc7dDs9tm/lVZvZRPeCZhS5KNB+3VW2TJnPaKrkUWL5UFk90dPN3tjNytz2DzuktRg0S0ogWeRHon6REVn21GO4+MoPtb0+0Z08lHcthxzCCz7cKMAjL7ZnbZcRwdm4tjwNdtrEW87QFnXjppTqgO1g2HqzbJCF+EMAT9bcd2EQpZJvXUNmLhpPq2DyaTRQ9lVNGwuGLCJ1xA0F8J6XoEChjMilhd+D+ObCmWJnWKlAdEeUX5TWizUF2T7JKGW2fs4fq25VGFGcJU76AeGBootoVKRqBvT3fAiRh1zp4rQq4hrvtKlDjs4U3VrnqizUZ0BNqdX3h1LPETgxyUmavpb5mzYF1IdaF4xxRZtV4jk29pR6AK3yz5JqAI1YVIo1aoxowkVaKWWLAkSfpu2d20V1NJbD6zKhF2PX3iWOV62LP68jP0BHgbcyg0GxmMUjyBjmq7sUfjmJNHhUIXpbOaBXvDmv3LXU2Iw5KEBcIccABsXgANlosDYwAF2QAdeABsUjwlGidcze2qWPlzBAXSm1sMGxg/WVJfzjxnM/LH4oPcUBusaD8C7fAzaYAKcLv2AxRsJXcGGN1AZnRmBuWP1yWABs/23g3zYYgeyDA7yBh4JKU0oxBB6GLy91MZNCA3D3Vsm7HvhjNdjnLwSCoplKqd0z+/XGx1E7tpoMjSkSeMPguaUE+YUXxJCH+TKDxUYmLE78/AM7egbfSLZG0HA6btdSMkTUTTXv26+GkKysMVH9rdvGttvxR1K/oEfdQgFfPCceAfj1g8jdOHqooTIq1wPu4euB2Pw4Zh0eNbNH6UYR/c3ZF0W87qiLWJnuR1B8cR4ZWQwjIkvd1y1xSoY03ozXgHXmhHgikGnPPJwF2BpTHeaj6xgPvowWhmB/uVwKQX1CcjpSgx3/hp2r3UEB1oWG+ZePPPNSFss4r+JXftkxOVLnG3vzjwqtHA3Ic314pQpt4hlGH6mwEs/I+o2TOr94yT+CSajGEFWcE02xtxRmC9DoDUdwIojkg50ebNZhUyDlM29RAa4RCgSJRRUkeoOdXbgeFqWah+OkG9JEUV0WC2tD9xLmfNMcuOuFHq4UYezhhimulWL8v87pFVTdE4UmI/N9pJe3GY5NNtJfmKdh84HB+NcL34G2vaL9mgYUc7WQO6ITBO99tO65+QVNrTBFQ0aWrlQi0wzOeCvs97tHuIdJTn1JdIfL6ezPx6jgpZ0+hFOJUdJDyO7GET9AKC0wFJkFKL2oPY/DwFg+ULaPkFwasmbfCVE6tdF7U3yBrBxEYo8+gJvHGqfGnOqnAa4QyiVdGy+O0l0JWPiqKhY98uUEx6yePLlmVC7Ne4TU+DQONbg4lO4tR3EGxOc0fkcXP0l2QXdIVngiE+IdhRkqAzvnNFB0iQrKUmnSztYR/bXz6nMU9VU6to+HYE23xoKXA4yafPzNBOqrCud/9psUfA0cvW6BiJ3synPwdu0+2QU08JUFeDgDtcEpBUnx9FuHB64DasVgWh/VSoj/9Le9LsSOkmzvNasLXCkRIe+i1RXqNoIDM2oujLK4obkkMjo19qIAtw+9k7hOjYLteyPWXCkEzULIle9oawzggWaOwT3ujMqjrzE0fBHrZ9Hq5kdD7RzXR+SJGp5QWZiKcBM//lNpQOQKREd2FPmp6JFUtqaOpcDBGwwhmKMzSt3MZhGpPAeJRGrr/2Xa/4ugBMARBqC/bfCKez/w8J9SStFmKJtaMEtV52DYFnNbzCl6SwVxksBGKstkwnR9DUeunrrQ2noQ1Qymbh0vlpPExGglsmKxkUlD9iJNp5YD+vPZ3Iz8jwDtelGLflITgLFCY09JlQ3JwD0bBuz2OeB+WegAaBkiB7gQN9Q83BqXzQLXKCAVWGwMLNZ+kp/FatfH0Pd5PH8smbp6QGkspwwiL3LoSRjgPN7X0S+adDJlzAlTHCnVUCPwvtzvEXxK4TX4ZMK4pmFEgrJyhIXcld6uPqHfiwjGAjYzKTaViLUIYVHlqJHYjwJh0vMqm85axJZ0u5hPxfEYSxFrEaK9zm4fv+nB6bd+KGvRtTjLYWC6S+z616K81fAnmbj1sLauItaCyrY+cS9WKaJ7B9j0Crl/fSU69bEbLXaC9vNnhFjzT4ZYzltSGWJ5shjOjz/AWAHvWj3v/79cuvb11VFR/XjrZozh8BAHFQUdEZlpIGI0zVJQEGPEFVZMkL0ytS6qdJO+Vd10RcGmoGuzrJ5ZfWlp3bTZ6m2xrW5NDWqHSam2qFuQChP1tKhg0MQABCz704A++8k7y/EOx8RY3Pz++fn4eB+f3vaedc57zDk74ZnznOUkrZL6jqoCZ/sd0QTtoKzQyd8SHYLR+ChdMRRbaDQrUKyBxRS1I1g9nkhQpNHGZYq6RYdjiooPxxwpWwEu+PqZ8CvW+GcWoFhjJubIdI9yGECuUGxRKIbY9Xju2cKt4f0frAX6zLfbvTg7THM02nOfETZtlG2IJqIEAAPtUzfKu5mLIcmezK9phH2dKHDmcBtQ8UGgu+MyGNa/pIJVcGpi61xPJhVqsHpvL2vSYln09ympTfyGNCj7OWNdwDL06x0dVDxMOTy9yow58srG4Ykis06uVtVvsH/wMCZpjIsCXMJgTO7gzAnVFYEgajpYZgRraJVgSdXTIhEY8ADgjfE3HRNZ46plCv89GRgqvNjNJixkpEIoz1t1f/E0Cfm4tWNmNyXteLhfCHym/XPq7++7gx7pLUUv8h0C+ZkIBb7aUk75nDbYk6vDUNgZqUrmVqNIGcbOSEja2QtRVGrPPK6HYHZtUR6S3amepB8oy+gsLw/L7syn7gsxSaUBfBDgXhlTEWqn6j7Ly6HjoNdODuFw+gdQH3+OJEtQ1Ch6PMW6TEA17WEFazpqh9YF2AbWcY1gMZ4Lmoj1MKNfIdNUt2vZE8Uv+Z0F9tO+lDWAT6mkkwk8vaAlrosJ4qpzvycFFtDFDbRNAxD+M00I4o7qb9IA7m4O4YARFwYokNyLKj4S3qSET4c0j70mDsT1NRwKAPty2OkK3AUXYI8J4HGELOyCTaMOvBezv0d5+Xq0Cnt3JAYPwP4dCf3h6IxU/OnoSFjt+i9Cs/ZINLgmTcXKiN1Q4brJ992zA+OXsravgbdE3GGtb8nqSL6A+OwoPnDj4T48Z5WmF/JKjZATeHXI1ZSw2S1rEzF6pny9Vm/FDjVJM1vxbMtr4a+XW63SVUpNJK0o2kIQTkync5I/b3dSvENFkv6sDRCF+/50Rihfl9DtNhXQFntV6x4M6AXuVt22Z+eq3GWqX7q9wtSEQXps31bdWUs8mNwl+nzcyZ2FWvx8K7RiATjJrRaiYMb2H+yIGWrSwwqwQ9b3Y8LMB3MVy9AgksqYZVzCwqVUPXpof2I/jLfBbZOB3zGnC0PX+HRgw7gxipoj4QJFxuN9Hj3MVhD3vNX718Qx/hSRTofQA/RK4n90JDPVBTNKyn1h621RlhHQ7Y4K4Jk/JB8olMMtNEmKbQ1wbiAU+SYP5JX46CFJnMBSdUpSP8LS3+1gP8AoUWhJwwlozAXG/6GIzzbINIrEK4rXJbjslO/mKwnaKhNyYno9EJdeHMjNybuuMdRX1wRoUmWIfz0BLBXARpVmxVeh/ibq80wydOLQon5YNyG0xmlWqdePQabSaigR4ZqFywdij16vctrCHl4C+Gfqw4c4mm2xfJHc3sIUENnc2mCcoLR0dECjhURBkhckXDcod1sV7yqjH7tZ525Ys36Zzl5RsxrU4WkVZVAbXGMLF88kfH4gsm0e8zWIhDIEHeO9BWkXdT7HTpuw2r0xBtDTUJBxg6/6Ja+Q2euUI6BjFGWMR7G/bLtOi8geuo0phcREJDBkbvVooL94lzRzBXTarAeBLh7AxdJMjZSYkWJhChoWzlAPddM98an0dN11jg/Q+7k07LaIYGCuyHKNdme6RgEXAX1ZSZIIGEMU/EqBzcfd7Qp7iIc7CN4oC6SLFXQaAxzz8z7YVoR1SL1/+KnihVn+AHhY47/fZGA9EcqoM8osnPok4kNqvo4bZBtj2jgP7pS6Am+X6sMCvD/M0Z3TXeMyhnQ9VWiy8rShMgwpayGM3GUMwcg7+ZUcTECw7t1b9h00ijDznEypDj0Wnwhj5a2FOgw5nzwwDDm7WJYceHJO3329fwBWvdrZjxtSkbS2AO/q3V6z85xahJ0VCDPyqCsNJXs3WXn04pwz1Crjlt0ooNzziWdcS+px9b9cwW7k9Z4Az28+Koy/6Fyft/Fyo4u28NaHbuWpgw12/ke48qKyi2Lo7ca0xRxZo4FywIi6iEq1og/02GTEmYXv3Pc+ock3/wVzQHuQG9bfMM4GaxGiNEH+IlHH+6oQYRvDZZIN8wOiB2LLPQGf/kQAzXgHcdnDUqCn68/bLDVsrS4hzOPGNjVHoZLBzb2o/8GIpm+uXrM8Q+hP6R9slYqTqHa+Zy+qVUgtpGZRMlyj8M8qVEyZ+gms6k0oqVeEVfhKhfcSkwB9Yco2Z7VD52TsCewkVdow4hEtOHahAIr+oFyROFkqVsaQsZIK04Aor0YRRmZR6RKe0H6Y3pSsTHpPYqutZ8iTKlMehAANBkRxWCBhxROq5U6NPktkCf0GeWPiqrsCzPwUIDi55gVOpwktVG/5VrK/pZUePWgvGdBvrhx64fYCpI98fAwtebf0gKzSmNK4+qcrPfnuNOpf+LoCCnrEDd8C7vgVYVv3RNbdfbGBBEjo0i26ZT5J18RpMo5vUTAEZevQ1XH7IWpJFYowQw+5NNlTCs1l/5Y=
*/