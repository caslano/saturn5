// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef COUNTING_ITERATOR_DWA200348_HPP
# define COUNTING_ITERATOR_DWA200348_HPP

# include <boost/config.hpp>
# include <boost/static_assert.hpp>
# ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
# include <limits>
# elif !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x551))
# include <boost/type_traits/is_convertible.hpp>
# else
# include <boost/type_traits/is_arithmetic.hpp>
# endif
# include <boost/type_traits/is_integral.hpp>
# include <boost/type_traits/type_identity.hpp>
# include <boost/type_traits/conditional.hpp>
# include <boost/type_traits/integral_constant.hpp>
# include <boost/detail/numeric_traits.hpp>
# include <boost/iterator/iterator_adaptor.hpp>

namespace boost {
namespace iterators {

template <
    class Incrementable
  , class CategoryOrTraversal
  , class Difference
>
class counting_iterator;

namespace detail
{
  // Try to detect numeric types at compile time in ways compatible
  // with the limitations of the compiler and library.
  template <class T>
  struct is_numeric_impl
  {
      // For a while, this wasn't true, but we rely on it below. This is a regression assert.
      BOOST_STATIC_ASSERT(::boost::is_integral<char>::value);

# ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS

      BOOST_STATIC_CONSTANT(bool, value = std::numeric_limits<T>::is_specialized);

# else

#  if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x551))
      BOOST_STATIC_CONSTANT(
          bool, value = (
              boost::is_convertible<int,T>::value
           && boost::is_convertible<T,int>::value
      ));
#  else
      BOOST_STATIC_CONSTANT(bool, value = ::boost::is_arithmetic<T>::value);
#  endif

# endif
  };

  template <class T>
  struct is_numeric
    : boost::integral_constant<bool, ::boost::iterators::detail::is_numeric_impl<T>::value>
  {};

#  if defined(BOOST_HAS_LONG_LONG)
  template <>
  struct is_numeric<boost::long_long_type>
    : boost::true_type {};

  template <>
  struct is_numeric<boost::ulong_long_type>
    : boost::true_type {};
#  endif

#  if defined(BOOST_HAS_INT128)
  template <>
  struct is_numeric<boost::int128_type>
    : boost::true_type {};

  template <>
  struct is_numeric<boost::uint128_type>
    : boost::true_type {};
#  endif

  // Some compilers fail to have a numeric_limits specialization
  template <>
  struct is_numeric<wchar_t>
    : true_type {};

  template <class T>
  struct numeric_difference
  {
      typedef typename boost::detail::numeric_traits<T>::difference_type type;
  };

#  if defined(BOOST_HAS_INT128)
  // std::numeric_limits, which is used by numeric_traits, is not specialized for __int128 in some standard libraries
  template <>
  struct numeric_difference<boost::int128_type>
  {
      typedef boost::int128_type type;
  };

  template <>
  struct numeric_difference<boost::uint128_type>
  {
      typedef boost::int128_type type;
  };
#  endif

  template <class Incrementable, class CategoryOrTraversal, class Difference>
  struct counting_iterator_base
  {
      typedef typename detail::ia_dflt_help<
          CategoryOrTraversal
        , typename boost::conditional<
              is_numeric<Incrementable>::value
            , boost::type_identity<random_access_traversal_tag>
            , iterator_traversal<Incrementable>
          >::type
      >::type traversal;

      typedef typename detail::ia_dflt_help<
          Difference
        , typename boost::conditional<
              is_numeric<Incrementable>::value
            , numeric_difference<Incrementable>
            , iterator_difference<Incrementable>
          >::type
      >::type difference;

      typedef iterator_adaptor<
          counting_iterator<Incrementable, CategoryOrTraversal, Difference> // self
        , Incrementable                                           // Base
        , Incrementable                                           // Value
# ifndef BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY
          const  // MSVC won't strip this.  Instead we enable Thomas'
                 // criterion (see boost/iterator/detail/facade_iterator_category.hpp)
# endif
        , traversal
        , Incrementable const&                                    // reference
        , difference
      > type;
  };

  // Template class distance_policy_select -- choose a policy for computing the
  // distance between counting_iterators at compile-time based on whether or not
  // the iterator wraps an integer or an iterator, using "poor man's partial
  // specialization".

  template <bool is_integer> struct distance_policy_select;

  // A policy for wrapped iterators
  template <class Difference, class Incrementable1, class Incrementable2>
  struct iterator_distance
  {
      static Difference distance(Incrementable1 x, Incrementable2 y)
      {
          return y - x;
      }
  };

  // A policy for wrapped numbers
  template <class Difference, class Incrementable1, class Incrementable2>
  struct number_distance
  {
      static Difference distance(Incrementable1 x, Incrementable2 y)
      {
          return boost::detail::numeric_distance(x, y);
      }
  };
}

template <
    class Incrementable
  , class CategoryOrTraversal = use_default
  , class Difference = use_default
>
class counting_iterator
  : public detail::counting_iterator_base<
        Incrementable, CategoryOrTraversal, Difference
    >::type
{
    typedef typename detail::counting_iterator_base<
        Incrementable, CategoryOrTraversal, Difference
    >::type super_t;

    friend class iterator_core_access;

 public:
    typedef typename super_t::difference_type difference_type;

    BOOST_DEFAULTED_FUNCTION(counting_iterator(), {})

    BOOST_DEFAULTED_FUNCTION(counting_iterator(counting_iterator const& rhs), : super_t(rhs.base()) {})

    counting_iterator(Incrementable x)
      : super_t(x)
    {
    }

# if 0
    template<class OtherIncrementable>
    counting_iterator(
        counting_iterator<OtherIncrementable, CategoryOrTraversal, Difference> const& t
      , typename enable_if_convertible<OtherIncrementable, Incrementable>::type* = 0
    )
      : super_t(t.base())
    {}
# endif

    BOOST_DEFAULTED_FUNCTION(counting_iterator& operator=(counting_iterator const& rhs), { *static_cast< super_t* >(this) = static_cast< super_t const& >(rhs); return *this; })

 private:

    typename super_t::reference dereference() const
    {
        return this->base_reference();
    }

    template <class OtherIncrementable>
    difference_type
    distance_to(counting_iterator<OtherIncrementable, CategoryOrTraversal, Difference> const& y) const
    {
        typedef typename boost::conditional<
            detail::is_numeric<Incrementable>::value
          , detail::number_distance<difference_type, Incrementable, OtherIncrementable>
          , detail::iterator_distance<difference_type, Incrementable, OtherIncrementable>
        >::type d;

        return d::distance(this->base(), y.base());
    }
};

// Manufacture a counting iterator for an arbitrary incrementable type
template <class Incrementable>
inline counting_iterator<Incrementable>
make_counting_iterator(Incrementable x)
{
    typedef counting_iterator<Incrementable> result_t;
    return result_t(x);
}

} // namespace iterators

using iterators::counting_iterator;
using iterators::make_counting_iterator;

} // namespace boost

#endif // COUNTING_ITERATOR_DWA200348_HPP

/* counting_iterator.hpp
y3b+umM+mv8BytemqFlLGlVaUqqhxtpxMJY0Du9RIQIje1eLrwqbWC2vdp7eWKCq4fSzAQeGgEYE6wAW84zCLNDLR3dv5sdnclJPXzJlG4h1HxNamFIN1t8gSPMjaujaOjMJ7R1lWTkN1p5TgHTfJY52XZU198RsNHUP1Ce/PTryBBeT7EVO3w9+xaXyB1GieBLhGOgmeoVS8aQwMcGtSQQ6lL37nTtg4kRz3+pEyiRTHIatKZyjPzrCCm4fDBG0Op/hDs6ULevL0VThXCpUgLnWFxtPGwgNGqCyGSr+AiF9qFAFxFGxxK6KDfpxVeJT9M3dtfusuifz5/V5oEScD/hJ7f1qgynYk84WB/e04scvVisMx0gJQouiKksuTkOWGgcsiA0jIV3IQpX/vsyt8QKG0EGnz2koVR3HPaFotN902/I/yXPlmOopye9F47x25KfV7jiPGdkySy+OISR4LUKDlg9u2243H7Yzm3dYiuQ1MT53isVRrLXBKSiIcWtlQG//5WqPN0sjPqoK64QcFwLYtDLhsHgM6HCNsHpIgGJgP0YBkiRvYCgHVu36/VyFRd17L0ceEqWSnFugNsAqXXatlZXm3GA2UqPA5ihdLpzUs73TqXGA0m6fRkihaQooDRaS0iuA1llQIFALIxqmeGIj2+ww/cROdqb5HTmzp5uu25wl378oYaDAYDy14DMuVmMSYt/iY0K2lN9xG+Qc8OBlhwuXYdqFJLQykXhuhc4GotJv6wtnMmGE/wwNsrAQyEXDQ4ueiRblPsUI4i0/L9H87AWnvOETq/zGIYao9fQFOfMLnuuBQmhfdiKW2owabVscew1WiwuaXyBDLkojT1554O+glhoc3LsJUHI9XJSpfvkXrHkXDpHnWsfRHpTKjAAxLzGpaBMIax3Qw7vZw3cyRM9xZDsH7O8Stu7ZgoFhV+9ucJNW1GQ61yRKmFAesUcSfEscGA2y2ZqTgMS7IEdgBEf/6q4cm4ZgIk5oMQn25WRO8SBRKsYpDIHKVKD8K01TwsgZU0zztk1Bongfb3lZSV6j0HDP9Wan9N13k8WdzKmdL2QRV/b5cP1YtkM/kj8BiZtEGeCF51u1PT+xNkRUdIPO53n7rv0obJqgvWOw0fXhd36QBeb+Waf9N7bhBNf+bVZtH1p6ac7AXr77Q9Isy1WlY1bxcnK1OuwB4555Oxjbr/f7LOF7Bj+ZpRjd3SuFxrRWuWTRhmaabFdVYXMwIPurzmww23vdnsDGHEx8IKVHzlgAOydocZ+oMk4ANhxsUkkSDqW3tIRKA6PS/4qKQzA9LgNmG30qRUsXno9k5sfMVd6yUJPpjmdz9+q5M+Nc818oFAK6a5zEffmN7IsTipLWf6VNDVaTRCUtbv7AweyWzkwqgLGE1fpXXh4JEpmkUb950smlprKQwtBuz++tyJklZc7JiYhjRgrm4I9ctYyLt9NLHceAQ1Hwxf86Z2Ke614U6eHaRwAf6Xn+czloX8JRDkuRuClo0kpfj55Oa5GHCCvR1bO9rmD5tbRy8pMQEyyw/IE2IWphStEYZH3eid+Wdfgs4MRS0EdHH671tI8zdLBx8pnolt+QFLxcrP4XRBrEQ72UiNki4DJMHExl/awJzgPDWUbe7fPCfnB8sS4Grd2h72z7bZ/eoCxGiJfVLUXtcW+Ro31eV24spSJ4UxZDQdBTTGlIEZCk/XwVgjWOwFuj7Ap+yVH7E8A5S5rELCeDbg2jgt4rp4SSbBlZ80PspD1X1VrrjZVFRe1cK2muL/MSXJ24W40BQePjMKKaLto+ajfqb8bMqne7AcixBoMBQIAb9ChWAI6JGbOr5o3yFgd5+Zue/8m/hxAt+C/6NSuZWtuqdl9HI07zaiZM9bQki7PNZX9JNS9ZKrluA8fI3wwSP3XsVmqo2uYO29aUJvSzDHE/2Qt7JY8PdRy7D1SfOiTbRbLLY1/4H5fbIIa3rWNtFBayGg3W809fSBzjWb/QQDQEoZSX1GB27Ka5iEaGGDojEhcQ6Yz552ZWlPUiWFWu7zyYuIU6nLd0RPJZgZ4t7CmLMuWK9dzJAzuKYCPNFVvheDthGQCOxreXkB73TFf/gbGOZSPXZ0O0tZKM+PANenrO1gcoiSIDzkkIyA1HVqEQBZaxKBUjI3OTfwcPspfLWvsxFoOL3WXcdfX4lw85qucCnjoT2o4/CbuPcVr0dM0amjX5GC1zCucKFO9FmJkv6FzXyqP7ysNt7TeQIf4ch5WMBRC1vblMPlRnpiHdLYfNKWKXwHK4BV7CD+9CSTKLWDkFOQaT1AmgjYRN8Bt5gkMLHfp6DXVKMMOzGa1fykOzwQRVH+aj+yWlLpw+QbwQgLi7+CSQbriN6RrS+M5IJoNVxdrjvflyJdCHE13OAjL8A0CU83SEJke2G2D3rWwJmnBYyX+QrYcRML+OHlugcCgjD2O0LuuIEj/DR8OgRr1A4AzpDz8ThiZORKcDW37Ry2akg1iIpQpcRkTPNxSIykVVojD9akZmYrGESV0Hvov/btbrRiciUm76lovdn373Kw5Q+rV9XyNb+0mZBHm8RzkO2SSdxiCdODJd5d7oMN6xzGBHtc2yHTBTbw1ajIRW3yFUHeXhN5mvGEbCKLco8K1KCyeglf/xRWkGY126xQl+6LpqgcECeWdpl13Vo75w+YyUY+oUHg+c3j+B8dxHM0q4Ui5fYrfStdaZ+dsouyA43TWcrIZx5TFU2dpHQG8NH1tiqilfqzCe4BARmvDCYPWqzUK8GCiDc0JEcBCUWUqxj4MVgEy7lF8SLC6yBYVwLAEjZtmQQacPsFK1MvmvBnRvsCjPwAZ5JRk/8ZI/vMqUd+ZIzoI+4yLoqUO828TUkFa+uACu5duxeY0LYYBrewxB/qPPyVwbMQZb6DJIDQH2k1a7Qv4OIuvKAAIs/dNpH6mv7nKLCML0mr+3Tw8r3uy+oR7PIPtQClCbIj8CAfD3DG4kAIWl3LxOQ5uU4dVaeuv8Bv0vRssCg7bNBdZZw4NqLTgMy5eeJ4qn338BohBdovGeZC0NmlLjjRTbxFs4thje0keQ4BgG/37E6NeQnZogaPE/ZN4gqxsOaqVxvnfVABJScmJHNW1QOBbGljqK6rb/NNRA6COvd/EgpCQDMpqRWHQzCVxN0jUI2aD3dhvcxNE15yg8N1ulkArzrnwLAzVgPY5DlGd0jPFHSJ6dWLORBV5fMHx8XhlkbwtbQrLcZOqTLN4nN1F44MFPvDh7VJh+YWW+j+8ECC6COqs7tHEQyBWLEKOaP/1/OuQyuPEVkPVEKrlczww7FIBOMBHzuWtsqovLdH2ixDzWzFJHQMSNqVoUU9gNUFNt0SnRobhtAkhPgx24Vr5mPxdn6d3iN6WE6HdqN9ydrlHmqwqobAEaskI7TBbEeG3oDm6UZl5PFUFxHlxylh2OAJH2RasU2ZhbXEErjtiMyVPgbuQ6dE5o0MjkMyT3wiLz3QWq4Psh3YiS8rdqYBR+cXeAGTxw2DTZoq11pscXg2OT9x3+OUgSphr64kXDi0sEDSL9l5kPbdc7nz7C0EjEmmQLpxrYExLmc08iTdKVa9sjSklNW//vYS7TqFKegUhM6tlbP2qRqXfpYz4wL06ecXrWI9oYoUkCGgXu+ytmtL4xNvg7LxlmB/5w8+SBGoa8WTPqKKO3ouo8yKzJWzVwz/zs3VNfrQzyP289/HGl3OiMvEA1ewURGBL+mpbqeXb84iaT3zQwrqGIICykn3yjk05NfjP30UDRclT/kc6PzzZnA4288dpD9fSnhygWxAIxbIk1s21q0+i0MsQxqcHplHz8aAEOLHUOxObH91UojTVvVU6XYRU+LGpvLfkdi2tJuZWBFVAZlua44H3tyjbBNW7S65oXUf1k1CbYsyGxT1NCioJzeIr2g+31PQepOdzIlsdY/zF3ONpIJYzKjZb6K5U9N5kkCqe5LHdgGnQBlv/aRbLAvtyQc6O7ZovHDUq7308wLxAQWqmOj404eLR4rBK1M4ygw0laTnxkg4DqXRWTQidnpBH9ykNbOKWCmxNnlSiBsbW4m4HeFHaKisoyJvciRPUD2wkVvtS916+tu3htqUs0bW7G/xNV+IVqMQQyoJttYBAdwYFZdHFSQ7Cejl7QFZ6b32HZQCMTaMqQEoa39vqt0rdT4ytHKjJS8N9GfhDUFGVFSpD0p2Q9JwU8hu7K4mGBXytKaaJdk2DMPt2rAnzpP1RJA5a5PIARS5DcFFK/es9pAWgHu3MyoEFDn3KaPL1RLNMQ6c4tIcgMYrL2AkDemKrwAnlcNXBVO6RYCDtXApOK0Kl+THiQVBcA9JU7yRyhNvZw3ymwTwRKgmJnHY+7gsLWUMxOqqzjGZjffqqzLfm6RPFdhzirxI240zepSArAqKnKU0fcUWzqWyg6vFVJxRLOddD3/1TcK1k08tMgyhPQOUpVGkCykCZqrq8EENkrwF7sJJBbpWFode6nlAwW1Wwmdof76ZZ5eygU6Mi7Vfvhv3OL5q9bxBpz/a9rzxvhFqontDsp0eAa0VQEj6jCm3ElSMxaUSxbpwVdun+PNOdaDNxRVB87rAcTlipQrIj/FzRQI5/HopWpxRcA4NCDcpgyhle//NqD8NniQz9d504/aUbW+liZ9l85iw9BkIcUfyUSfj6LKhFDikTJ4/MJgfWd/+GiHxbIjzZy8T9vc3b8J5bcrCsMzG4gp7t0FjqizAFsJKifvJbqNq0xLJ06BUtirNxNesLpjmtrFvfTtV7BsjhCONBuBpv1e36qib0ySpHl8hpTTmMhRYCZZCnmqUiyuzOAATDmqZwNw05g63WGM+zSMrNad0n+jLuIcpeRzHxYIB7tVmAfBwRz3D2mqAcgPQhXdbip/1IMfvkIDtjd/ZKY+BWEyBZtXuhFH1CFwnIMv/lFKXlK3DeJRuoLDcf53LzDlH39shi1mV7wn0RE9Iekpp4AmMJInXr5eZJN3AXpAR+LoVDVeDdle1ICMc1sdrrzg0wvIL03Dp/bCknHDWs4cpCaaGxHhLGYQMpFNFR87b4FkZo98BfmK0EImcDMovHSQ8opcxo0WKjKpYkE4gMFg4OnI+cNLMGAcy/jloNtHj2aD8/7rWotCfyGBqDu+nMA1rsnJRXoG1PO+akgfNh89PTfLm+ZbHSBGlzqNuV+xoQ39OnMGpcbWhNqC/UA18yCA1Hx98crGEH5RRqNEf2BFAT8g91Egolgkf9T6DqxWxUSI6w/DzwUTPHy6r90A0JNZNiwB8ffKq8bNOLFExyIkuLztJP3FmoKPN1UAetskZM1Gt+L6F9UMzLZ3FSM61pQo8E+M8lcLnA/5CzHVCz8cDeJCtCc35/Dl6Jbg0YZlG5HNzQAAR0kOHoFghBC7ft+MedHkHJ/PTPoBfSkD68oUiAok28helszqf9X5tK7XXY+oaANyzxR0YOvbHqMXm+iT0LpPRhRSkcgxxZzZe8ZEZhbk50BcsKv3NqHZrJuIWfSM7j21MjGMa7lR6eNDHoHnQ7YzkJ9s5PH3P7guVMGsLNSs3KSgqVcKaAM3rxq5EUwBdHOZHRIdqI1fAlmU20A2wO2s8wvMlj6xcJes2zZM1FmSCO88k8rSfOK6S7iQPITRXnM5ThxUHu6V70PC5q+RHvt8QK0aFydMh70xf1ukRV0F//ArXV7qkNzEtogkaU9ZohjXHiCRaQVqsH77SrVaSOF6cTkASo0yfTSO436o8XxWWD5HJG5pbpMqUmLOGBEhGYI1MZpuerYwazhHmFgL3XLYlkwe7Qr0y8neR4v2mAoMUmtkUlminEl+N+hrOX4FDzsD80/Umm/CPiU1yJY2leDwyUGaxK6xljxQhlYnu8xmwO/aadvfrMD4+Te6BAdj6zBoq1eQdPoUSGO8wV+hILkbYhWWQiHnVz+odMGmi2w0/zmt7gHHIyWxom8X7BA/DOM/yIR774GybZIduDvWGDA4xGYcZtGcuGHrqNAp/0L8ZXw1W8+a1CSSIjUp3zLvL2cFBpyBBKMqMt17+2L2t860vflZgOUhew1VAvT6t2KUC7wOtODSdUJ7MSfxHrq3hA8C1ZTCedAWUhQhslAKwkwqQXBFc4tXoY3ibdjBSaR/5umCp56ZjLRsG+lg5TIjHcM3PxZiKBcHnEDTsB51kiHDgAvj9i7zOxMZpNiO49a9ScfhPeilkmJG5pHThv5/aHpgoPHdYcz1dWkDTo9GAZl/yRuDnPfYyhrlYksUvXLGSNUSk+dOp64hfMdEOdMk1ReuiWMjm15MZNf7JFZrXCGjw06sn16txU0MKxrrQpNTFxRBoPzzBdqszBulMbL90VuTPvlVJe+0TiifRozoamfLjYhP7FeqyeDspL8TykQ7V6u3X5YVDGj4ao3Y1u51C4duMo+lsgIQlmOsmUwMFnArbFrg1EkjASFZMEo1VkyY9O+dhEp0Dd6G9gPlp3RwdbOuKv+VMbLiA6wwj9KRWRNCezUoetej1NxeoBk5Q2bvYh8O79BsaIsUv7+a5955hIu6a2RWsK7DyzL075HajiePC5hd+WxEPQr6viW0mAoip1ibnsu5FPshHaYnekXzH+neIhaZOOhHPlHeZTFj81rcOd9T6NeaxMpOlkurUK1wK1SzxqEDMLAI08BK2JbCusuhWchoUVD//7CaDSXr57nv64E8J0e4/3znT6gB1gqgvMtKIhxdm6gdmRWSn5gaT7oRBIsLiJqyXb+/5ZSOajbKR8bot5VNdk4T1o11xp1zUdojpwdFGN4WaYcx4a423Bu0kM20XhLeOrytL8lnw9GGJXn3ZPreuKcMSFwjYvAzn13Shcy+kf0L7rjJTUvlUvHlPk8mo8tZomNGOd7LDPdMQ2kaxkRe8LsWVPZ4KV1l2pmKO0AJiR0F2uXCog/0NUvCyceZZhHUZL0Q/vyrFZOITa1sVTlZGA0h9cd+CjTFiyoYC0gCAHTxb+JSe4OJPLNXWhA+V46mjxMpICrzomSau+yMCPWxz/ZkaL4aPEk1KlrK0miMcrRUexRc8AsZ5zFat6j2oO+Qwh0gqAUXS5xBrl3iu5174Cd6WkfHn1YXcNJZNsV5eOG4tFnKMkkFQqrt7JA9DwwKYm3ZTPpuURhAoNaxhjEqO3Sd6TuMzqpZfB/6NsO5MhesRbOf28q8t9/4M3hTj+ocgixNJe6N9pbFkyIYqg+Z8NcmUtWYZ1Jq1V7dHGes02dczB5zHcuSfdvVqT2+BK2xObd2bQdYjVjZGxrSdmuMp72L30FrI7m55XdQIWTnZzB9FNE6FAeMhrrjhhfQRl4CUBmoYtUqhkkJgJ0UvDGy13KTTMC5qWh1BlmfCxfavskAB/4G55SRWfAWMgwoKGB/AuqQ6hNDUDTaZlKHbJlwHlJy7FfOYbaH2MPexrWoNBvhDh+r5CExu7O2p9DL/7tBJmnypqUPW1mAG/4he8C1ESV+4eIB+XE1ZDrmeNgvhYsapLKpPjyawjpcooeEkysP3Gm8jq3p4BVgEGlCaghFvJA8e/pzF8Ek/3utIQZWSxS20+nR713IwymYI5mflsvArkQ2lorMqsqGFyUrhgJPD7GF1/AoGqXGXPysRxYaqyShQgDsEYsHlUp
*/