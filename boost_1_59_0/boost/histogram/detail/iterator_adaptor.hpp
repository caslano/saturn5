// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Uses code segments from boost/iterator/iterator_adaptor.hpp
// and boost/iterator/iterator_fascade.hpp

#ifndef BOOST_HISTOGRAM_DETAIL_ITERATOR_ADAPTOR_HPP
#define BOOST_HISTOGRAM_DETAIL_ITERATOR_ADAPTOR_HPP

#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {
namespace detail {

// operator->() needs special support for input iterators to strictly meet the
// standard's requirements. If *i is not a reference type, we must still
// produce an lvalue to which a pointer can be formed.  We do that by
// returning a proxy object containing an instance of the reference object.
template <class Reference>
struct operator_arrow_dispatch_t // proxy references
{
  struct proxy {
    explicit proxy(Reference const& x) noexcept : m_ref(x) {}
    Reference* operator->() noexcept { return std::addressof(m_ref); }
    Reference m_ref;
  };

  using result_type = proxy;
  static result_type apply(Reference const& x) noexcept { return proxy(x); }
};

template <class T>
struct operator_arrow_dispatch_t<T&> // "real" references
{
  using result_type = T*;
  static result_type apply(T& x) noexcept { return std::addressof(x); }
};

// only for random access Base
template <class Derived, class Base, class Reference = std::remove_pointer_t<Base>&,
          class Value = std::decay_t<Reference>>
class iterator_adaptor {
  using operator_arrow_dispatch = operator_arrow_dispatch_t<Reference>;

public:
  using base_type = Base;

  using reference = Reference;
  using value_type = std::remove_const_t<Value>;
  using pointer = typename operator_arrow_dispatch::result_type;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  iterator_adaptor() = default;

  explicit iterator_adaptor(base_type const& iter) : iter_(iter) {}

  pointer operator->() const noexcept {
    return operator_arrow_dispatch::apply(this->derived().operator*());
  }
  reference operator[](difference_type n) const { return *(this->derived() + n); }

  Derived& operator++() {
    ++iter_;
    return this->derived();
  }

  Derived& operator--() {
    --iter_;
    return this->derived();
  }

  Derived operator++(int) {
    Derived tmp(this->derived());
    ++iter_;
    return tmp;
  }

  Derived operator--(int) {
    Derived tmp(this->derived());
    --iter_;
    return tmp;
  }

  Derived& operator+=(difference_type n) {
    iter_ += n;
    return this->derived();
  }

  Derived& operator-=(difference_type n) {
    iter_ -= n;
    return this->derived();
  }

  Derived operator+(difference_type n) const {
    Derived tmp(this->derived());
    tmp += n;
    return tmp;
  }

  Derived operator-(difference_type n) const { return operator+(-n); }

  template <class... Ts>
  difference_type operator-(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ - x.iter_;
  }

  template <class... Ts>
  bool operator==(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ == x.iter_;
  }
  template <class... Ts>
  bool operator!=(const iterator_adaptor<Ts...>& x) const noexcept {
    return !this->derived().operator==(x); // equal operator may be overridden in derived
  }
  template <class... Ts>
  bool operator<(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ < x.iter_;
  }
  template <class... Ts>
  bool operator>(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ > x.iter_;
  }
  template <class... Ts>
  bool operator<=(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ <= x.iter_;
  }
  template <class... Ts>
  bool operator>=(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ >= x.iter_;
  }

  friend Derived operator+(difference_type n, const Derived& x) { return x + n; }

  Base const& base() const noexcept { return iter_; }

protected:
  // for convenience in derived classes
  using iterator_adaptor_ = iterator_adaptor;

private:
  Derived& derived() noexcept { return *static_cast<Derived*>(this); }
  const Derived& derived() const noexcept { return *static_cast<Derived const*>(this); }

  Base iter_;

  template <class, class, class, class>
  friend class iterator_adaptor;
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* iterator_adaptor.hpp
4bLJQ07ze0NFUamRMNtlQlR7vpwUXzPs8ncQBG9x61GZIsGvQoOkIXuKym9ta3czJ+sC1+JQpzTsPUr0RERaUUHqUPLmWwDs/nBMQqmVqm99oll0cJz5TUQzWev622/EhY/RANfmieFE+y8lZlNjAjdX+TFePWQVcY5uogeTOebtEqIcz5HtI0gojtSKGgkEOt3XytV+ZbXDZXEEIlYn0vPB6G2R/20bYCblepdEi3sAYSHBsKn8N0PcxxsL6Wbngrznjm135wLoFAv5ZsaUFw+Uc+THKApSFQaaxKaHBxYVCxNGInk3bT01SiKQCy5bxJb97ECoT2JdmDyA/dg+CxW6DzVFFr6wjsOin+jH7I0CrSK07or8EF2+S7Rr1sYlA1S6pf2uanbf8w9PufkLE/JCf54fAAzNg8whJot2lvA0rQzBgfE14AwMun5mUzfs8eXoIP7UulMrjxZmCwWALg97zvMk5r86x9ZpUDYh32fY8QGrK+mcakMWBAVybfjrYp6OPMc6kRzL8rkbxOton3y4ISNF0Y1UUYi68M5WRjo8nowbuiSQk3yCJKUC1W+0rRQvqtw5hAd/nI+cLb0xYPAmXpANWuGmXlXz32qiDV6Jb7flpytZjMLXRjN6BDjrPcVu1m8XxGo6H+WsNiclzbf8+5Qs+g4fFQ7GWY5InxWmJxllqzhJYt8CK+n7WcHf/AZc7qxpRuATcRaXdTk6NdWEC0rmawqpxaGV9YaX9bUdTQEOTW8Xenj37xoOy28u1txiHyT3Yzkgs5wZ/1kvxHVTwX55nSc9bhvYylGGz6TGbtFwZzzbr53Pt6XIwttDydowd7zfcuukz7eB/d/e1/uS285Y1vBPt8Rbl8S2WNbhtlje22Ajn1YbhZsVaX3XSxax4U83xSHvL2fT4PUW+vReWsbsa54dpgvvLzHvlSa8ktmMF++PKtIQg8tGnVfoodia2Y+POd/S2Q/BndFtT9Dd0fFGw65YLGFdO5qF6CeQRYMLqILJYCp6C+qtivdstIWy4tT+M8HWBGZt3IW/SkU+U/AjQP0xqGcPMr2+WRbCu79J7A+ddz9KRY/ehm8+bRrqAlrXa7uRNPTfPLh3fxvJ870S1V//F8ybX1Hbf9yU9b2qhKPy/PMJRJroj5bunFJHJfzZ10vjeMUNXnoNqTd/4hwaE4Q3P9IqGtO6yzHQVDldmkLirMmDclpbT174N+SCnO7c0DOIMDknAiG90hibP3M2GgvEfEwFrRniR0DB0xI8TbMdTLI2AHlPMckampF3H/U8jYwJJy87icv9q57tOGzK2+pZnu36jXoRQ5oEReBHF6yysR0NVUBdyjyVLrwLex3dx4j8Mp4UlrTvnQtbd2p9hHoZbxqLgC988qaBFUvlSSq5gD3U5dWCRVAqu4Nuerz30L5tkSnWBYpsCNfcPv1nEhgIzLaG9A5G4alNUjBp/r64MIeO+IODjf21X9yA9NEHN1hQGSwc6fT50TxFNhvAG546wJfsIO9T2W50i9GdeT5ZGleJ285yQjEqjYis8eZLohhL8HZjcuQwjlZUzsCOtQB9x6XXh1slhHG6SCGrpmStIErl7FEfX45hXKKxiAyMeF2XlNaPUgFBAZ9/C037Xodvh6zpTUvqQuVtuWISZznIEz5gKnzqA9tYbzoZGPDTfahCpdrC0U+emzgQe3YFhhBUX1Up6ykvB2T3+L8F2zmcZU0n0eatkS7W+RtuQ/aolOkv6RnERwu+Ti+01u+CYiwKth/aE3Z9ck2R2tv7BtUmf+8CTggqrFTvjbGA3dHbyMy49Lq324MQAieBjZFrRXiHlwUENtGo/MhwEhzx7n80zz1w3km09JoUE9ogEd6aXhs5k0+k5/JeMXQMHSr1RPUxUjRarhlTyEdXiN0TuJzirWLnQwYRn7BNmAq10Cy7olyB0dUUclb1+AQpIVx0Hkz6P/cruai3/06Qo9xo77lfV/37fz9+OKiv/jj5ZqP6/HH54/3H2Zf7/En9ptYwWzcgAKeX2/foPfgx85MWz/3XToz0Bq9ht4ATbPDrisjHFsHdPHmuJsgXCFLRlGopcWMTNcnvQ3zulMWgnlRu0UV1dg1KfqQrxdvbvmLEVvuUtvZ0QEN4mPy2WP8/wUGnHxgyXhhgEwdyQ2xLS4mVt25ikVnZxQlkgYlHP5Fwv4ipAY34MPhVO+k8MVmV2hbdLDKdbQDqb00qJfAJ5G+sjTNX0u8CJD3E8wu1ZtDoqz7/NxicmCpIr3DWzwEcqn5UcCvB9hxjGPjfKF8gncSqLrgP2rqMSdv1xTjW2m1ba/t1f1lpEl+zG4H1DQVVJvEXg3L3aweglEtKm4dUz69/PcmGVv4GcJdeSZNukd4O4WC6CR4wWmrSB7MVv3wU2odHp853n1md3/kjF48uj2K+9o3zhrIiGAw6InWh9yW8fkEgJIx2uTMndZUGD8Aqv8wSRe5BW7M85kDAqwfslJIvBcTx6HSQCMP0fCTA/9uLfBdt2hvKeYwgr0A7MPsPD/rcNsYwSMXy2oE+nhC1GAD1ZoC1wp2W+m/k9WEi6x8YpZId3DxL8kyzgcntNeApI1Ms+Dz/DMfEmhbp21eVBTmrEdYq67LL5vHe/MgPpNqqNTyTO82K1UWk++bj1R/qybOUU2ZxeSI1sRK2Pca9YQJTSuNR8blq0bqTjn3855L5RjqI3ABU1nqUzuYMjGPqnwfMQ0FWUvsfEZqaejBMJkFis90hQGdiM1sDciUvpEyIYcd+drn3PuK1pa5Jc77BFhECwlsH+rxUSiBMWuih6MVx/osGIZNftN7wPnCyRl+59nAxhevlUIbSrlHGU9j7TRD9qp2z9AisLeuj1SRwOoReX6J5EuvEiqaCpfY1PCCcHWO3gcGZLblwItdAGHNOzuBb2yQoEeVj+OSK27saTIWGzhC6T4Y3Y4xDPU9PQ2ZgIJhkIfIO+8ZyNEjDNJRlu10+s3ObQmw+Ok5P+theOR8gSgJr0q4kUmzOFlQ+zDoDWBdaMIToM2CLNwiOgo8PwSyWtKnbgBn5mngOlA8cjiBXF+mpBkktB9hR8hkYuVH6sY1fCDFMO5Aqb06avWE2Xu8EPhi7rEnd6Akgd1MtkQV4voDbhp4i59HPCV2O4+Ep+zrohCeXBqndZtFQNh9e7waDMhGbd0kRuA4v5Q8y+SWgaxsDPHELPIyy+EC1XtMZNO+g9rxYC7ZqaJydZwu8ZSQU7rTtxCjvJTFvJaTK2JGG0p9o7yadcyK4Z/kD54LYojoeDVlv5IGaJwSVqf4f9sDX+LaiwS5gHPlv49sHnoSQJB4O2XMicT0j9TmQrVThPfQnrEmPVN3nfbBboEK3dsnzh//4vV9pTKXDC5aoFZJl8u7D5HfLFJy4lSH+mUzlTJFfPN9FdnrpwJUPdsoVnwFaPFJZ9S8jKjhBKCQ1DCQ533ca8M8buWx6is0HBxToADfWT7cHFETrI2uLIcPooyHDvJlZd+UGhomkhRVEC83XXeT+wsngSJ0sseuaESEAz58AjQ1emtIab7za083hGMwCnUF681k+0QhinR5Z4M+FMO26xL0qZnKkjoQzAghDZPDexaoxoZkNkd0ohbuFZbQjha9ZIzONavE9kugsJsHaVmZ4Mxrbjlz58sKZ90Sb7SBHnhwAACz/067HC4o9qgSfTAs9flmCTNcjQk5rhp8QXEFOuy704U3yCxE5CT3KBIBX/iSCsU07U0yTkjGtkjPVcqCLPPKRXvN1ox0O62jkARTiFFv9E6rsXMJuIKeezpMeaBboAwWcXjvUzKirzTVcc0YPcs+aOK3XqyRpGCS7eLYpgkFrE+pQR91Tysd4++jWJ6ouVSx9ZBwMiWbKYiGAv1YArrBakTl+8ELXzQSj2575qOFHImR2sIfC53uNwzJzLdT4rGYeaeaUI1jukCmJZpcrekRbHTMcgunEYZlv9po0idRZzQuuOWh++G/TjhKbXsLiaxVgctq2AfDTLn7WeP3znW9LtNNw3KOHuQRyFh5ZWpmL6GEaehf9OOHZHfH1sr9+QOVn8zMcKI9loB6xOM9D3ggyLn/QUh4tHDrDuHwIL+YabsIW3pJBM8G6YwMWaDZWIw0sDzTRr1RvsXUhsArIh7a5zpAyASWQj9oXYALwe2ODte4/CMpoS1OK59FC9i8/Q200wjWKZL3CJfLnZniA1C1Ewjze1N0VkBf9GqRPYID2AsGZuAEdKRVkHLeM3Y4c8PdV17e1HezyznpcZ9awOPaAOEYLJZULXbFh+gIlUvl6kep7i4p7h6rJ0tMQxfqwsjW/9/xsoWHyAAddKxVw8Qspy5a9NyJlCExRshmKuffnZtuloPmFSOO1tep1IjP1hQJ4BpNm2KYQcHYbGWACTSHD0x8R6yvlNiUFrzy8fN/eVKS2XKQ2YzWCOnKhvR86wM1Xe8DLQCIIqSAp5LXGsDhhi2hT+WjHuimY0yF8IxV0gkVggkzdcPwj5kxRIiN5NgLHsDh71dzgOPrK575KAoEebs6AuOiAuHtLQgjx+yKqwYidkyDiaQy9HuXkLCiBoCwsaASFXlYpEDJUgkTglxoC4iNxZ9Pz0mTsbapGEEMDeMRHyqAuOXiHe10i8PXX1Xnw8OGyIC6JzbndhhmBsbTlDh/LsLhXtBAkRBjZTwHIsrKXE1p1WtKQFS5Cv9MttyXk0wQ8tnfcszoGiuKvtNovub6a6kVUrdUbnuz3lm7oZOOTi3mJRfq1bnndQZbcy8sixtXTUXny5UbIYc/hUb1yLTisQpzFdYH4FuBFiZhwkD5+c0ZhDZ4S9djwfyl3DU7xJqhs7qz2WRzxJWhs71p7bOpwspeLDlkQM9aSyFmfQhv81QqzzhQzqPEt6pP2JOzeFDMe8S24owbTVjU+Rk1xJDWlqESstPvxu8YPY7p6R/zxj0gI7WErwPGPeWFCcJwzJAjvHWFZIfGXQkeOhA4Obvy9aPEQQwnhY8uEDblbVVqTRL4khLF6RtFj5/DxnWMGkWFdOkI/IESpkWPQCOEGHKaVZvNsCOI7q9mEp3fHxIra503hYbRuQ7JGlx4KQsAjsbLQwa5kPOBVokgOCaQZdiVKClZAD1RnHt+EKe2paew93qWMk3P3eVrdPHJdOdrLv85yMlSD91tiLML0C8DxZd/CSJP4aHgNjXi6/abLQX7N8ToCQTB3Yc17WEZqkZnG1rhoZWqZ0TupvUIwNakcVZ9scza67pZ9HSp03C7sckPuuZJrtvLvrUbWuDNgjZTaOvmJtnG7Jqcrh4seeAwcbnCxjuncvYL6iUbVvtBw76dn8DCnsW5KO7CrVOyTIzktd6BXF99T6QBBzrA0Kk/DuH7rl1xBHXT+JYx8Q/W50JCmDjBv13q+ftIzMxTsITuApyXDWhDXaoCY7k/1y3iwBrRWJoc8uNAH+03PgZRySDbNY60wD8EFjbFT+OpYWRq0JOadUUtE0qp5G7C9zeOyltmWxV0T+KelY+ru3z6WhbvbBw2Pr/T+AoFz7kZo1yHG7XSCOWVk/KBVPD0pOhVkgjPHQ91p6rsLCSkPnDpLAVbjjqwdrXv3XNcAiNnH82YOqxDuqgwKmre0O0Oe47t+hRHbzjoVcT3ghKxU+wvESfn85IqDR2ac9hB7k98xfPE57bOC5Alcm/inJzB6kRWaWq35X6R0mtax3UAbjpqgHfQWaZPMtH/lX1J+GXDki5TxTXYXtyAuWX7Hv1rMDaJUqwTbhdPnzltUUcMDTNRWUTuYyqXpG4bg5ms8VLFF1whGR7qs5n9xXOPOAOl8O0nJ+EIFiHidLC7oz30fxjSyk7Io1E7Kd69+w5l5ptWXXyvSIrMuXZzp1a0QMfUOaP9psI4Le7gDYoO+3BvWiyzXdWudj3hLwKzqGdoMrfDoTjC3rydRl+F3cilIiUtsj/fy8hNKEHB9XhKRDn38F6RglMx45Ghk2Vjl36NCWp37MX0m7CN4RpTrIQ+mnSsY0HqvkS5A7DaJENCKLXwX0kHNIF5vLHb6PJFceyAouMPPMCelqr+D9XbdQUAnO4uKgcjsv/nEx8gy6+fRGO1TSar3/B+1wvs85OUe7X39rjWBIawm+GX0zeqQfETsoBYfXyACKL4ukb/MzwVJIalipdNhFCJ6JslV8KbcgLX+9imJRQW0W9HbsXCFQhjtraVY14Ay8Le1f/hi/FmHQUZTpVztdfdKu5f9EKBCYSDIkAiUGEfNwGdMBRS4D2ea4Qay9Et5aYTYrSZGH2pLI4zynubR0YKfK031elZ3wBBloUltMHcbECPr6s0c42S7WD6qDJJe9plAv74h6etifsvqQZOQyh1IdgGCJ1q7ipi5sw4MZbzWdpI3MNql0buIWjSDvT2N+c26IJgST40vrzLbcd+pSWj8NITamVEHJNLcL0sE8YYdyHVGKUNq9+b5eoqZkn1jtkoRlbCzdhN5YveCyLvZuIJLvIlRmQ/GrPZusN1HJZb6t8tMIGSTgX6bhLPQKGMKE9JNA0vGWICvon2nr0ryAG5XXO5YdU+Xy5gX87muTBtC8v25tlSZmhDIJXKmkHCqcGo2zrJ0+hWZSZXNlXTSdUJvkbAMZNgkzLBt3oaWATlzvvXCI6Xe4JsHf2fXB+qFisF2hnEngIo1+zx/LO0LFIs3YL7i+72IWT6KxtsVSFcwU15ZPHsN/dxYpc3ezOwxBMuamd0GGobe+jwwyroEiS3Ckm/MEa1NgmTGOSqrXMM4QZteUP8pPFM/im9Rk+qebxuh2urx9UvqamcJ2W19TUNjpG9QQpQzm97H8fcNjxrS49nPsLOhLRfJVdxchZBecoyac8u9cDD5ran3avYRGqUbb/xwBS9QjjCAa+vjP/Q2UNG+TIFAl5PTNvqqYphzTFX6nj1KHVLL4/A+UuRaIBIAH/3C4uX/LtMDoAe+TZogBVG+JHZAUJo+3jwIYuuT+z0gnSf6V7uacO1TiJIbsbniWgNHJkC9+g8zwtBLCUQkFONe1taNGOcBPhmhugkKkNDtuZ5t8Uv1vfTO/B/q8B0PHh1r0Pk81mjyXrLcVAexdUhnFyffQd0J5Wjq3NPgWO5pjJE6rxXzUPnunt06PrW9Ju1whFke+02fJuygJ6hl6T12iqZhTdsCv5VOXiXCjpp5LSHWt2PtQPxGIdyhPNFhX5yqH9FN8G1ZM9fWiBkAfHO7gjlMYHssC5IhwRBgVV+GWIYjhKEyXQh8d5ni5TpnRu+qw8384tJXHyqJezCILkoZhw+jFtGg7wMW6/UexhrDl0kT7sOcG1JtSKp7MLDuQBV4Dmlt1d1Jq5pcejzqu37NznkmmRN3DfapD5XhueYkdEZjJzrzX7s93Hvr82FE2DISy2B03GS/rnYcCQg4wyIi6LiqqB34RF0j+pqbt76N/uqLmksi3X9BK3rkACti4baIY8Y8vz0N4nOt2dr2GLBoXQCohJIuDTBoB9gJyBOadzSDIV/a1z7V0lehyOJa/QO9e2tT+c3ulDaGmmyJIpkMu/FI9ug3D7KvtUvtCcdaWJ5nhBrEDyHHsK/3Ci9YwI03ghg3/2VcUJg71/3uq7MJP24QqbkxqXlUJuTUjjHm+w7W5PZ+wFcmyy53xJ0evxb/
*/