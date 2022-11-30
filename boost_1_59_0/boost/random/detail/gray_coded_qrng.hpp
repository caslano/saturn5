/* boost random/detail/gray_coded_qrng.hpp header file
 *
 * Copyright Justinas Vygintas Daugmaudis 2010-2018
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_RANDOM_DETAIL_GRAY_CODED_QRNG_HPP
#define BOOST_RANDOM_DETAIL_GRAY_CODED_QRNG_HPP

#include <boost/random/detail/qrng_base.hpp>

#include <boost/core/bit.hpp> // lsb
#include <boost/throw_exception.hpp>
#include <stdexcept>

#include <functional> // bit_xor
#include <algorithm>

#include <boost/type_traits/conditional.hpp>

#include <boost/integer/integer_mask.hpp>

//!\file
//!Describes the gray-coded quasi-random number generator base class template.

namespace boost {
namespace random {

namespace qrng_detail {

template<class T> static int lsb( T x )
{
  if( x == 0 )
  {
    BOOST_THROW_EXCEPTION( std::range_error( "qrng_detail::lsb: argument is 0" ) );
  }

  return boost::core::countr_zero( x );
}

template<class T> static int msb( T x )
{
  if( x == 0 )
  {
    BOOST_THROW_EXCEPTION( std::range_error( "qrng_detail::msb: argument is 0" ) );
  }

  return std::numeric_limits<T>::digits - 1 - boost::core::countl_zero( x );
}

template<typename LatticeT>
class gray_coded_qrng
  : public qrng_base<
      gray_coded_qrng<LatticeT>
    , LatticeT
    , typename LatticeT::value_type
    >
{
public:
  typedef typename LatticeT::value_type result_type;
  typedef result_type size_type;

private:
  typedef gray_coded_qrng<LatticeT> self_t;
  typedef qrng_base<self_t, LatticeT, size_type> base_t;

  // The base needs to access modifying member f-ns, and we
  // don't want these functions to be available for the public use
  friend class qrng_base<self_t, LatticeT, size_type>;

  // Respect lattice bit_count here
  struct check_nothing {
    inline static void bit_pos(unsigned) {}
    inline static void code_size(size_type) {}
  };
  struct check_bit_range {
    static void raise_bit_count() {
      boost::throw_exception( std::range_error("gray_coded_qrng: bit_count") );
    }
    inline static void bit_pos(unsigned bit_pos) {
      if (bit_pos >= LatticeT::bit_count)
        raise_bit_count();
    }
    inline static void code_size(size_type code) {
      if (code > (self_t::max)())
        raise_bit_count();
    }
  };

  // We only want to check whether bit pos is outside the range if given bit_count
  // is narrower than the size_type, otherwise checks compile to nothing.
  BOOST_STATIC_ASSERT(LatticeT::bit_count <= std::numeric_limits<size_type>::digits);

  typedef typename conditional<
      ((LatticeT::bit_count) < std::numeric_limits<size_type>::digits)
    , check_bit_range
    , check_nothing
  >::type check_bit_range_t;

public:
  //!Returns: Tight lower bound on the set of values returned by operator().
  //!
  //!Throws: nothing.
  static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
  { return 0; }

  //!Returns: Tight upper bound on the set of values returned by operator().
  //!
  //!Throws: nothing.
  static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
  { return low_bits_mask_t<LatticeT::bit_count>::sig_bits; }

  explicit gray_coded_qrng(std::size_t dimension)
    : base_t(dimension)
  {}

  // default copy c-tor is fine

  // default assignment operator is fine

  void seed()
  {
    set_zero_state();
    update_quasi(0);
    base_t::reset_seq(0);
  }

  void seed(const size_type init)
  {
    if (init != this->curr_seq())
    {
      // We don't want negative seeds.
      check_seed_sign(init);

      size_type seq_code = init + 1;
      if (BOOST_UNLIKELY(!(init < seq_code)))
        boost::throw_exception( std::range_error("gray_coded_qrng: seed") );

      seq_code ^= (seq_code >> 1);
      // Fail if we see that seq_code is outside bit range.
      // We do that before we even touch engine state.
      check_bit_range_t::code_size(seq_code);

      set_zero_state();
      for (unsigned r = 0; seq_code != 0; ++r, seq_code >>= 1)
      {
        if (seq_code & static_cast<size_type>(1))
          update_quasi(r);
      }
    }
    // Everything went well, set the new seq count
    base_t::reset_seq(init);
  }

private:

  void compute_seq(size_type seq)
  {
    // Find the position of the least-significant zero in sequence count.
    // This is the bit that changes in the Gray-code representation as
    // the count is advanced.
    // Xor'ing with max() has the effect of flipping all the bits in seq,
    // except for the sign bit.
    unsigned r = qrng_detail::lsb(static_cast<size_type>(seq ^ (self_t::max)()));
    check_bit_range_t::bit_pos(r);
    update_quasi(r);
  }

  void update_quasi(unsigned r)
  {
    // Calculate the next state.
    std::transform(this->state_begin(), this->state_end(),
      this->lattice.iter_at(r * this->dimension()), this->state_begin(),
      std::bit_xor<result_type>());
  }

  void set_zero_state()
  {
    std::fill(this->state_begin(), this->state_end(), result_type /*zero*/ ());
  }
};

} // namespace qrng_detail

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_DETAIL_GRAY_CODED_QRNG_HPP

/* gray_coded_qrng.hpp
Z1u+4Ri48MsFMKAc3+Z0LChpmAMwyUhx/eiTNIpfrGAPNqAcuj9Pd9hJYbx1AKGTT82zZv5tp/cST5PvJBKASe+tne50JFfruZZV9sjEhFW26mKsecsma2XISLHIqjUPKSvkVqY2Yrtmies49aFeapGEvX/8cUVcMprJUpgOOAvjvULpkpw1NxSZZo8JYKz446zokSE5ZYtd33JV3wAk4ViTq1R1bHJMpDSzKE/KW9yMrrdgfq+ZCrQ7EOrh/bJvFFU9aQYkHVMrFNPoQyIAspYP3sZOp+0pTqfxw1RZzV4wJWH57KN9ZrsPFtyBsWCL/O0TTisfJFh2quun5rKEO+PQiQlnuE9VlyKz6d8r8GDuk05H/AAGEmeSzswd+DAihNc+0devydlW3Jm/l4QWxfUsp4lu7uCQ4QOy4AkQzBambmOpPe1/YDXpMXnzpF6zvvO7tJymdnjB1K/41laCcnCNmOZ6BbucOO5/Q58cXeUeqfujrPRwaFmyeB3NytERh1yxHB6gcLh63qHipxcmxvNmBa7c/jCsuhn5NGv1bASqSfe39PSnLyPnoL9x2UVaeNIWuuWuxZMQ8Lm0bBKgH5feOAkOhUsvnYRsHUtnTIJlYWmx/w1tTHzaJASg3lU6KY3+Lc2flI5/F03KwL+BGd9gF+12LjtLuXJSHw2PLi90aIMrI46qLFdqyNn+SvmreHq/9Jdh8bGc+K1ppsItLD1Ki8nOFuu1sGmyiKE4WyAjN1Qm+sAk/FG/ZCfLKuSZ12MlPXc1yZtnAO11j8e/V1tQqeCNZnHg7KgdjH7ap00Liwm1yK1aeNxG2XdUFXYmj8fZx+ote5RIDRz/hZ0pyQFSk+nY+H23/9Ly+B+H1Gw0784AoRb7OaZFObzHs61PHv8tjLG5xgK3Mc3DqR9ybPnmsqR805UxrmpYjpPDsTzi+K5iOtPPjA7iq/KS2b3sDtiTS4T3/T/SnjP5dpjXlIdtK1jZP2NLLCtUob7+RitzUGmhL8tbh6TXSL9hBPcYwRYb5mpPMulUZFwssI8WpvTXehAivccTC+4rN/UWmCL2NAf2FbNLnEYrdmq0utOhldKvqV0Kg/Tbcs1w3v/lJ7rHsQUNn01fKgblQ3HCLYw4yiPjEnOl5JTskCsidgg+trBPv/wBCs40ab+UJ5FSJRGhyRuzlT9phFooVWoQPakhQWL//PZJERoEVsCYShMun75VRTQSzana9hr05sPhROmO54nS4qikmfTlCNqMY2XAyDTccFStygd7uwD7g2uZxxGd1PlVHo3lvBxxXHdHW8z2eBq2RDXs+17hrdhb97c0BRSRaeWlZPi/uiO8tExv7fNpjOwvR9xqTakdcN02EMBzZWWSX04bCgutCiJin2U2GG1XXGcd3LzEdYXE9Q9EgrAM3zSXdk5sWrHIid59wqGNtGtZR58UOcc6+cXfqTeDW1hcaNBG+suK7hrmLxuzbDA9aD8whx6In5fKpJfLgTN/0KP6Fbos+JhZyUGxsk5+X/u/OK6sEH50Jx0WqA7y5UUnnUD/eWuBbitnhvljJd6aN6TXDDOd/dl0ZivU9A7LM6cnWIu693Qv7a2S2mDUHcPWnmk8gP/R1/Dr0FYQp/wSDmN10nYGf/0enh6jRQwFISgpQVxCKbds5lu0y6vmjiYqU7aEllmIj60eeQVGEr7dXHxCXQvJrXQxcp51x624gz9Emdcdso7YBKnN5A88jFvGD0b4MWuf5JfMao9gwporctQd5YAhoyWwGAGHL+GK6tpyYytX3NCpDkLy6nywjOp1DTmRNMOpvNkr5GtvZCDT9TU55eZLmG6cKCadJ0psshMKidGNgt8GZNephdRaY4pbtuWnylRv4WxVYWyaeqBZzVzBv7JGU1BkrnrjM1oUa6iz4EACacrKcFQOm/aduSUN/q/4kva575EQM1JAJjDvhP924SLGhvzOW/s79gZwQ+a4i+Z7Bcn5wU6I1Gl/6sNq0caEOFaHyjdO6WPphmfJS8MVyGJjJ1R2w6nJVTf/GySO7r2uWAGwIYWSm3vcu5p7fBjkIRQvw9PJYEKuR743PCGXNNOhvHeJJ6GEVmgARKvev4kDmThPxyNQMyABMsM+EA3I6/kr4+sKmia0FGpQ4V5296+/maZTExEMEL2aBkdSvW3RjvI/eTiAa/bJg6MD7tnzmkRjSevkkveMMpdR5jbKcoyy3GiraeQYIY8Rym8uLWgBqSwrNMqKjLIxRlmxUTauKanIF4ONHFHuMkIuUe6Gb3w5PeYR5fQ8Xc81iAUtz6eKRHmBESoQ5YVGqFCUFxmhIlE+xgiNEeXFRqhYXD2OqsX+Dv38o2BfBvhqwExozlLW2R9JU9dy09W16MuFp6E4T9TgQGFfgtjQ5oQnbOtDIQdmvUf7FbVwsksEC6Kt6USpcxM4Gujx/Ijj+pCZN+YlqP0LEoYPqg77XCQNUQZsGMjZgTvcqXdkiaCHOOgM2TCehsEx1mnB1rqJCi2uAv7a4C230f9od+HSLCj7XqCt5WxccUTPrsK/lzX6bd+FhcshlSTGLj4Rlj8fChups5y2TiJzs2cjScXSocoNNYn5WyiccIVFxEEMn+Rmr132zgVDkPyYaKEjutDlSDXsRBeSMJw223A3l4LNo2H2zDtlvhzacsp8qb/t/CFgQcMKAaOuS/NVcmLB8QgjmahwRQ6fn8AVGQbKN+pvSuhXAvqL6Zy8rpU+Q4oSO8aDxgoutSWt4Up/o3aamFQAuXDtavY6J0Z/DgN/nCYm5KdenxCaA7hOjy9YoJ0V6S23cEZFwJMeyH1o7Bvvdpdx4keE1sfPLI/0Jm7ISQ/k2zfk8A35SOHiATO06GCfgtq1ui9sTphF7xFAXZnLL8zBwryCbgOgOk4tfFOrPXSABgNfaATdRAORDyXKGd1Ey175lfIHgHrjbyp6l2Z4YIzQPd5NDXQ5RByFXkRDa+oFNDdpsvIIY2Dl1ycyLe1Yh7yCnpZX3UHUowg6jfvBPez9FaeXI6Zgnruq6pKhCPgedx47TE6JVhemeevA+iC1mmz/UL08+jaRQ0dFBb+E5hC9hoq3yp5/ZdpZMT+kW9s5ndKqFQ59TFiB0XWNscICbxOlt9G/W6qqPMhAKF8fwy+cWVU/mCPOn+VzPWD5ck9CQ7SLT04tcjgGO7SfbZnxC+ozPQeYkCfbQltCdEoHW0PQuViZxHFYIYNnkCC+iD6RBmbLtdTBTVvG4dee0FaCHL6oZ2y5hP5hQts9X0qcLfVLBTov/oH6esDhYwytr/fw13dslX2fQDswQ80uNazi7ZC8dr8dFNohX6cq5J7bOb1fAqTCI0qLord0c91EHxvlkOgRZ2xm9/UhnjSBIqym6JGB0YY0Ynim3+0gBrXwB1Iw0ARFSiFdJVanVpfSsg52MG58oaqjN9rgov6yoMGt+ada3JFs8R/eSUlR+csFnuT7iHDB7sGjJLPPpdsGYZbTSGWKQfx4oLBM85TpI8tVvfEs9b/cnv/v8NQusCG4P47ec5sjXAnXPQACLP3TD4B6F3NuECJR6d8jUUg6zyDovMx+qANokqADk32wdatWIEjgC+SP3csLN3bVONMIdFBPUq/ERwg9VwQK+pV1clk3RmU1CIbIA1FZMJ/aVSTy8Clb8J3Xs91FLt7HPVXyjrxqPrqJ5hhoTfyI1bjxqaPjVulXYxiSD0Q6UCNp3wsgExzg1fOBa5fLOpiY3hGrPqyiO4xAm2+JS8v3LXHrGb4ludppEeTCRLoHjinx6QUq7nds9J5CsPaBHDXW6fHTV99T2LB08Op7zmpYmr36nv8PAAD//4y9D3xT1dk4ftOkbYBAUkihuqLVVa222+oCSizMotxSlegthaQIBbcXfLvMbSj3Im604tI67nuIY043tzkGkypubNYJEhQhBaRFKhSHWkd1nevm4U3dqusLVdPe3/M8594kRfb9/PyT3nv+Puc5z//z514eX5sdttclsnxx1ngqGuiqUaJyr2JoPbrWFdK1bv7x/ZLk1wq1b7KbHRVH1Dn+NU4t27/Gq/qMmcuWTvVE5QFjZh08sBMKV4+NGmH4FxIVI/+e3XkeY+YiyBMlEhdj5XEVR0QD04yZCuUtEs0o7AT3QQMskFyx3Pf6Uu6od0lHDxZKzFjMBmpZvTMYYo2F7Hp2wvipM0uSFHzosUlSZNjQHL54wg3AuxR2jI8/Omr44pUrli+tP1gg6rOAJ8j7zxlGS1wrOit7bdrFJtyaS4DAAs4g/+Nro0biUjMBc+qsnCcgJ5KTFalyZIVHw6NBMb7l9Qe9ooPIQNm2gSumenyv6nJSQBvVXNHGgdbW1qh8Smnlj2mSxAJDpc7IqlNSZFWPhMlMLjzX84V4pM+uIA7Ck2r1wABfvxaKygPUQC80UN2qy/2ROPSry71hiebIxG8hYa/XmFmAkB5T+L+OZuAwvhRxaOFg4s6GqZ6Wo+r0SKNTUsdF9nZL8I86idnCNkNxRK7AfKn+oEOUN2auE6NHtPLdHaNGCp2RAW96tL44jtcvF8PEykXqAv/ce9Ty9PDDRqsgiVYB8zbEqULDhbmqBHBXLE9Ms+jAJcgCR3KFGAmOY/hOHEex6PycXCzZEJdOrQyfgRbUiduoVj42kpiwjeYvH5OUhVHZo/B3OhH6IhMRsottWA9NIEU52YnIsE27Qsw1FA4/qPDfQnE2E6EV9OxRjLfCDyYaIsNZ8KLNqhWlX5akB6VahX//AsVrrRF5kLKXQImlCb+oZsxcgJDxeReoNpYrqO50KBbOqiuVixX6U6KIotsWmIikUudgfsIwkRfKO92BSK4/WCLGHwyZhN3oFKCYxXZ1/Cd44NlkCmDzaIfF5p/v6d6xPUXm7FoOJEV4Vr0sF1hWuaslrk42M7RJ5+YXS5JDUrN9Z6tADp1tiOVhLzxeNAq8qn41MmfjMiw4LjKnGR9Uz7Zy6LDlrDZjWwNO9pe2ecV78baV+D695ayaS2USkyONriwtlx/7hmEksrfdBWkIm1PA5osHgcX9skf1+WUSaAsEuQvkBHnrETHO4FhZhvhIXItVilLyQdQN8vvOr5KeTJIiC8fmAzAeiySdkVhbFrLj+PA0yH0xzwMg44hS/Agt+OLIYZPGiNVC5LwJbLHL/wNsQM23iMwiId77KhJ/2ZhWvOrV/oe2SshGrm0oOwAZHi2b2EhRgnwH1DFyjCrH8sSXUgWx5wJqG8VOwpU5PkPz8DXUkSkRa2oijYVSrBvytOxYj+jCGVLYcf7ladC45mEguF1ReRiTrsoD2pMLqkH5uOA1OsF8ZbK3GvPXU4IXatHrt+E10gj8fFx1QhpUSoxnsscsz2+H7BAUe3UqkmNKi2wzZ1jBXvirhxFa5wXkN8wGiDRXMLR/JdCckMG63ANyVg+AzD7Wyvd7EJzeqOYRIr4V6Gi9XZcHwlJkwMOSLHAK8lpbma21lRKiGharBdXaaigzEHS1gdnZMWPzZpRlE0n4pFp7VvLATDoBA9Bk4tpnpUrx6tHloUThs1KReC3U5cHElGelDfB6MYxcl4fZRJyMmhoW6EEJy/sOZaiD5xdnqNSgpeacKR5HzD53KIO7hcDO4PDj/EeQvzylCExpbXEAEsF3DiFaXVb+AkuHACHe256hQ0AKacW+N/yLi5jN/fjBsGRohaAzFhK6DM2JeDA2bwXsINMWWUQFc+M7Gl08vLBGDwzrgWQ04KoJOxVe/V0prepqapCs+GXfAdRWOiLxnKPWPBMNsq+x48bPhBEBD2hEsGGWA8+bmyER5I4rYhhqLuJ/VuLiyH6vDRlALmATUdhoOWwiDkt3pnJcag2bWEBpbGIRDlnGR2pyIzVJTAYMVkj48Oo2NrGEyhVCObmITSwTteXiDmkzctcdbKJiNnjXBRtURIOL0g3WjWlwWbrBTsooWdEh7YAnQGdxShgEzSkE5KOaP35g1KAm9Zz0LIvhAuaxOZcFF/LONhUeD1n0VGfRkzANXUgvK9otenIpmVKRVD3BflzhN7QTUXktqApxmviMf6K9xo5DUfXLolHRh8LHXaDVDPFcZsnAZVT6dPzCMKSMDgT0xXgmYZNAXmSHySXyBzx7x8jidHadyC7JzEYJ61LzQChQNW3qtlkIlhsTykX5BirvSlkkYJhm8/bLR4xzlV5o1mEpsYmsshgt3OxtRVQjJa9KxsgrlocSq1bRA31gKxqPlgONsJurv1Q0CLKhLMI96iURXq56vhSHxrWGDpk74CFxETxk44MHHnLwIRcecFxooUZW9YLujq4psOzYHgVlFkiwWWi1nushK87QuKH1845voY7oYzYQcv3G5llZyLim/TarBgWPU4p0GoDgcHFs3zmPhy9fDsMHcZ8D5iPQtVLmM+YDGjxE5Uo5YuQyuSdh1xt7RNKMdG6lyO3F3N7IEYCwD0zNUfgvKvdZpmZtNNDNq17NMeWrLw648ss9yL84/X65d9syMRs4x+j89ClYZVYiR4oEkgY+XwLV+fUAaUqCgDHjijzYILGPWA7IMKdabGwmdNMbMmjJmDfERCJHpGbYH5GBApyyyPehJTthWc0n2QeYBnsc6iKi1yfmRxs5JUUDwzWtEXlgPGgNZTXINbsMjaBKgEkBBcPHVkSB6iTteoxvgk7BHUpJQWarN7YSzKk3hDI8O/YRTsyry2BigKbqXQ2zL58Cxrgud5HSbom7W54DiUck0Q39oS7Ma3KiyLyY1JkyGx7d4rEMijdvQOFqvWpXpAppZnmcSLN8OZZX0KObs/0BtPWuNbSuaCDOI4dyJMGxkVVJCfm4W8H0pn9b8xTna6FMYr5oCOmkON3TRemeJmUyfsKVKTRYoAvb5X/YN2pEXzgMLEA01WrS0zKgJxx+G2T4DD9BqN5KAHby9w9aAHbISdQIkOh/2WNDNY3coHEgAG3A0ProrY8X/8OCvJPvg8qJZUzraugjccjdk0YNwHhFB0iE5y4ZAVOpH+hI6zNbzIvKcYWfzUUbipp2R+WYwv9OCdgHNBHIwpcueDo4cdTg9y9N0y/pDZSvKZW+7+UM10Go/EWZKv/JlzMlYxAttI+QzHIE3eN7Tgatp0l8m2LZW6T+F72c6ULO2Qm2lbNpqWXhLzQtfO0WIL1qdXa1+tVqtaRavaRa9Var46u1W2Jv/fGklFgbu++pPinx3diG3YelREPs3v1LpMTXYyN//4KUuDP2r1eulxK1MWPrVimxgBqaW61eX61+qVr9YrV6UbXqrlazQQwlvhIzJENKlMQkMJ8Sl8EfeLs4Br9SYkrMwD+umAGWVSIbSkppt/h8yQtM7DGFZA/ZidyUkUDv6sKo1nNBL9gkVEYECISZwwQRWvQ7VrvzIElaPvmllDUHY1jK+25DuerKwLbvqD/ghXqkihcX6Fn+gEd1+cF2z6P8hJuahART6oGy1W04K2Fn7JJhYP4VdSiVnUAQUpogLI78SjAaGOD/PnA+P3oUTP/nvyyqHuD/gDJpt97iMdD1t+8FgnwDOsnoMxFyWUwP5KJ+pQZbiFIvBZ/rZWNGLxuwl/zzelH4/8agj++IPkyDsDbIZh4Grwpd0bSfjPIxbMfncJbvdEivH9brkzy5EmRhysPFMrWiiFXg9EpJ
*/