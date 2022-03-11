
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_DETAIL_HYPERGEOMETRIC_CF_HPP
#define BOOST_MATH_DETAIL_HYPERGEOMETRIC_CF_HPP

  namespace boost { namespace math { namespace detail {

  // primary template for term of continued fraction
  template <class T, unsigned p, unsigned q>
  struct hypergeometric_pFq_cf_term;

  // partial specialization for 0F1
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 0u, 1u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& b, const T& z):
      n(1), b(b), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++b; ++n;
      numer = -(z / (b * n));
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T b;
    const T z;
    T numer;
    result_type term;
  };

  // partial specialization for 1F0
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 1u, 0u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& a, const T& z):
      n(1), a(a), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++a; ++n;
      numer = -((a * z) / n);
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T a;
    const T z;
    T numer;
    result_type term;
  };

  // partial specialization for 1F1
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 1u, 1u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& a, const T& b, const T& z):
      n(1), a(a), b(b), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++a; ++b; ++n;
      numer = -((a * z) / (b * n));
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T a, b;
    const T z;
    T numer;
    result_type term;
  };

  // partial specialization for 1f2
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 1u, 2u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& a, const T& b, const T& c, const T& z):
      n(1), a(a), b(b), c(c), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++a; ++b; ++c; ++n;
      numer = -((a * z) / ((b * c) * n));
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T a, b, c;
    const T z;
    T numer;
    result_type term;
  };

  // partial specialization for 2f1
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 2u, 1u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& a, const T& b, const T& c, const T& z):
      n(1), a(a), b(b), c(c), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++a; ++b; ++c; ++n;
      numer = -(((a * b) * z) / (c * n));
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T a, b, c;
    const T z;
    T numer;
    result_type term;
  };

  template <class T, unsigned p, unsigned q, class Policy>
  inline T compute_cf_pFq(detail::hypergeometric_pFq_cf_term<T, p, q>& term, const Policy& pol)
  {
    BOOST_MATH_STD_USING
    boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
    const T result = tools::continued_fraction_b(
      term,
      boost::math::policies::get_epsilon<T, Policy>(),
      max_iter);
    boost::math::policies::check_series_iterations<T>(
      "boost::math::hypergeometric_pFq_cf<%1%>(%1%,%1%,%1%)",
      max_iter,
      pol);
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_0F1_cf(const T& b, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 0u, 1u> f(b, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = ((z / b) / result) + 1;
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_1F0_cf(const T& a, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 1u, 0u> f(a, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = ((a * z) / result) + 1;
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_1F1_cf(const T& a, const T& b, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 1u, 1u> f(a, b, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = (((a * z) / b) / result) + 1;
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_1F2_cf(const T& a, const T& b, const T& c, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 1u, 2u> f(a, b, c, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = (((a * z) / (b * c)) / result) + 1;
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_2F1_cf(const T& a, const T& b, const T& c, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 2u, 1u> f(a, b, c, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = ((((a * b) * z) / c) / result) + 1;
    return result;
  }

  } } } // namespaces

#endif // BOOST_MATH_DETAIL_HYPERGEOMETRIC_CF_HPP

/* hypergeometric_cf.hpp
tLl6QDalVYToFl4Tu4QhRypRCsoDk/E6LmOMwgBvM80up+zt4GbhEzy3fYv+91dUL/ewaxnBgfACiddraxwSNkaQzFlLzLccunCQy5d08HPUUWsEe6KZDx/+bo7tU4FvGJwXeqX/ShP+zx3+Tq/T2UIlfdftwBV6rvfxO7rvizr/z31jbrv38WdyoymdDl8gB9dMlUrhR5iGzkgOCQ6OCmpy3nqC0EmciKF4uth219hYjRSiKREWeStRwXllvp3bQsM12FrOYbxzYQHRNvweOZs5VrvXH/WMvTHyydS0d1wlm8FPOR0iq0nJdalEdRkqI09ux7+dfz2lObn0FrBZFjm1VJ10R+eGIQpvoGz4HM7FHSHuxlzSlw8lEIXFYUYTh/bLOe9ZncCYBhfhDnlZZMWLj0YGdEadicX34ry4lJS68WNf3wPupzXUa29ogNTXUKJr6XFefrfN+/v6KBZopIAVgWceedlkyEZAtCQZRz8RLiu75JyWBCeTpYNU4V1pNPRgGGfjmbGQdJyy19+gvFsyUNxeflIAg7ZRU8a8DhFV9n9LKLKJdc7omMq3YuqwkDutVJTDwak9n+49r2e+snwPBKYvz7cLIYTkxINyUJLZ3eXdeUKEkvE0wUWiLKjzOiLnq0+Na3+k7bVRrCiI1G4JGWLSKsHgiJRElOeVJ2qj+PHtkec9Wzd2yZbRaFulW5zXckqVOnqSFpL3FxfWFEJ66FVroLlQWCPK0Iel0CKimtalKJs9JIlAu0hgcUTuCipEWTqIBSfunyOPBgZjUzrMpSaU/kmvcXmWy7i2SFdkNHg/K63xvdilX/EqpLDr0SyomFx8Hp3i3SYkJRgUPY/MBt2174oOirENxfAlzXTpWK/fW6ijL+n8m3Tj1/tegPeZnbXl27BFieM3Gg2pbwZcp9fv+TyHpu+y+wg2zW3/Dt55S57tdbqCt/XdAPc95CUiwkpdvBPaBDwIaMMUjVIYH4uA4iqVykbmLCcJpir/p1lco3KOst5NFa7OKVmsYJq8neVsmgY9WWN3YgdLoL2o1YAy2/e+q1q/hCvZArdsrFuobSp6LyKCIqssI8uyFIYhFUn1TxVYuA1X/qTT6uY6IZPSvCHYrOBxL8zShEBztaUTFkZXWkjSGZXtTbP+327jQ1yrhDu3S7o7XknwG0zO37hWiMl45R7kAsx5lIhn5YPBFbrHzID76BG5nbayqE7Wu8W2RU/bBfbvzhX0sui7I7L+P0ZLSPI9sPEkoKaokb2Hp/hBylnA+3fFMEOn+A1i5Ggu51BIkoFEezbZyHuWYpdZqgGkaGjfYlK7xN7o9H9Ge9r14+MZUWuXxIwORcoyIhKdp0oZC9286FL5Do6Z7jr1vcIzXVO7XqrV7S/KEhRU06vsfzy1v482jRO5Mv8luyfLNkFp1ZRxrhnu9NaTnsFGMK77MjBlDVSSgvsQmTcxQ2ZQlzb+xE+jTn9TVkpTHLsYtLNVkkWzLobDTs5EVDx1a2/AppA3kzbnHUKlkJ62h2VCqZHTkE9NTW3RQqtRpvwbvBbBuJLfRGvVq38LnvwbSWy5Im157LhYwrTwr2J8qONpYblSONO42cfdQHdjfftIPJDz6G9E1j6122YvB9k+28I7TbRG3O5y5tpSdb9N7dTQkohUXX3RauzX7st3bebsDTbo4ext/R+rr6Pez1R57gT0Gl7Hr5fv4Z970bjxwZvXmMpMUTkxvt4whC2xtshrlomZooQ4EjGK2SIpFSp7QzLRwjAFk2gbsvLDooTfuX/tH4mC8dZzGQzJmYlpircQtY+X8nuisHlL61q323Zja9hLAhnzmDPNhFb4htZmCIDRFqMlIlLFSd2C+HNgULNYNyv8hfV4UYfhqfreMInQRPjxJ6rL9r0gDbsZr/+bKMeP3ucU9/zagYQjqDw6QrV9eRwjdsC83NYiiqR2XnyFaSYiogP9gHOWTXp3i/SqTu+Pm6y4vb5A7CrWjc3uhWnc998ohQFpsohVb9+f6euf7V2Ra2/MnTjEJ/IQWVInuoq9tWLKESI2qrtuAUZjjJGuS0UUjhHYoTKqeCWwF4PjaESQ4qHXiVEAUgh2Z0KBlyyTIAKc+LGtftxGPxQaCdG2obKhKTuojKRkmbb2jPtHat5aPNQZK/nXb/iu5EZtdycreCGBGUB9QACgX8C/QH6B/gL7Bf4L4hfkL6hf0L9gfsH+gvsF/wvhF+IvpF/Iv1B+of5C+4X+C+MX5i+sX9i/cH7h/sL7hf+L4BfhL6JfxL9IfpH+IvtF/oviF+Uvql/Uv2h+0f6i+0X/i+EX4y+mX8y/WH6x/mL7xf6L4xfnL65f3L94fvH+4vvF/0vgl+AvoV/Cv0R+if4S+yX+S+KX5C+pX9K/ZH7J/pL7Jf9L4ZfiL6Vfyr9Ufqn+Uvul/kvjl+YvrV/av3R+6f7S+6X/y+DXn1+Gv4x+Gf8y+fX3l+kvs1/mvyx+Wf6y+mX9y+aX7S+7X/a/HH45/nL65fzL5ZfrL7df7r88fnn+8vrl/cvnl+8v/19SExPB3e+a1lSJSdEdjOWlYutmfAVuEDZupqvh6dlpGqaFKEYotYeIOLU0/xKYJqpGLhryQXd+viTCQQe5H75rwjOSezR4x8mKWS3RXRZMLTe2HXRHA6z7E9WGEyIoBYtl0yg1KIf7ZFlDdCVJI2LQketAWjo+ImBJI2aMX7Ik7RcL0O7pm5MSjypalsbraW96LLw9DTtT8ZlQGYdpvHpNaBDQHg3slfF7R2mjCdpjg01KmSw3gmGZYG9oY3t/6n1fPH3/PKz9d/MRk48NeuL5ucX3NhCf50qC7y5cHqf3sZjf69r1+43/GzjoLHP7ricUFVFREEVSUhKjUSuNHTVCWo7JgsGwSdUknkWulSW8rKIIJRbz7Z6Ik6YCIfqeOCA3U5XHzWbgX4rTR+3YVmrveWirjZ3TBWn624JraUhK828TYd0ZCEXdxoMuuJayOrbq01WUzUNe78nXpeVc2zF1dxjycA944tXdsPdy61MYcDRv6B58bpeequ2Jfgu8EWkimp3NX3Q8fRYeO/T69KVgeDytE6kSZ0PDb+EyoQqmr4iO1EKN6VPaS1glaPXQkvj8t+W6GLz5g7fFfX0h0yUcov36rlnUG65i2i93e61atAlCpdMqJ2mwc/q9f8679FKiMTR7nY5lc5tt9447KlkoZyOMxtA7G7MNS++SoQTZ39GAVEhjKiAvrh0T80+HeWQzjBFF3SiGjmMfcIRaTG2fDYnzVEhwSyE8tzzwWCTXdLPeuqfFrM3+3wEKnS7P6AvvHZ7LzLW9i+tMnV6cWI+6khkZLPoMuz6RSWIHY64V5tMyb0hS0SmHl7kNNbJ+FLSZCRJnVkhJvd2/kG1ytkO+rTH2LqsgPwwYMHIyJC24eMNpJwtkzKryIbjYZTJV74pchWhQLkknLMlRm6HphDZcvMvMMO3k+7bFl3rm8FGtzR5zrnG2LU7b1p5nVc/rs9mNytoesxP6HOayqYHYpXMybGvLVlseW1M6fitKdqMTljS3rrt9Hw/FDZR4CpL9KFzpupWZ1XDct5TwHX2BnhvfHS+xHYD5nyj8F3oK9Rqd+tz38lyuz++bn2/5r6nZz6lIeb63w1Tfj9yvg9rPZ/6P0d7P7t/56h165+XA9wNy3o5LMZryaa/DFZW0vC2iENI/wP2ZZT+AsjzUqDrun3glrbiIDkn80Grmyj+LBuVqHnQjIuiuTQeOJCl0vq1JPcepPepRGG/8SllGc7JmZnMCdaR0PNhjYCJgPZxELFSMiAWt2fdDhGahZGHuuWp5hajs7ocs30/cf4nWm/lVK03iHyQ3ZUuUlwfLRJRiHKJkhB6PcO+gbFUSzmLkjkUV9RYxRSgx7R3R0rjLu1yQzS8S5t0/bfjIgHLNRIqn0dN1kBf1z2unYOeTcbN955ynMYhXgifz0buMWouUEsOWfS4jNiPWJBDWQnUg+REBu1ccPVDSqC9kEUTAht5R716XUGycF5KE4NlqnkAysSMxNGKE/94bMJ2L7cDHzAVUMN9P8SLQQpAK6cgCwgSx2/FVhKpnMub0arv91semHIrK3W169+oice4GD0grbvt9TzzdP2lj77dfuiIrahAvTm+6/GhtdjUJSMPeLG7aQzyQ3u6YSBNanJxwMYBLWJD7TVgVCA+VaVUPw6K4CA75pF6Ol35CTA/O0NGH0/2cisqFoBXMjpXpbvr25iMuJvEaWbiIROpNmuogRflXOY7/MRlckGqpvoZw0crZn26VnVMujkcNYtM7nBw7v38HvfR8WGeZJy3NidnfqOHUyqVNvXA0dsu6eg04efyFacMCvJ3msP93DkJNXpOpLQEzCjs5PuFuV9HVpAF+NTK5Em27Q0GwIzRaQvzWB85nN7H6fpb7fYae63U/Tv+zTP/1qe5zkerznfpzvPOB/z1jdPM+E4pypyR2bDPEGYfEgDWurkkCzsBkE0CbZ09A+lQUA8U0PjO8VS4fagRnu/NI3/vJlDp7VbfSNFWppnTttjvRUra7ZTE913yYZezdYGjvdrpscs7mLhcis5I/KQWbQwyoMKnbFZqvLd7E4MdtvbMnHITjPmPFewtQnsPUBDyowNHhGHm0hS3jlFe1AuMdmpyyQCf+LPdqItvaEtcgVExMXloBP5ZIyZUpqNRVk88VeOIIwV1/axF8WM1h/qhX7+cpavzwVUIdbp/qB590XVm2BdqN8HYTSR9keTvjihD8RKdnI9gJb47+CCih3SaHUL7mBEKIhGMt/JmT7DEXR6wax0SwjVgewaaUbikxH7yHR/h3+YAvD83i0XNayYmBcBeNShpGl90FVTgqZ6h+Qfk9PqIScejf4S384jYRFVf/1mCKiyoFGUm1hIWKpB18bcMBEU8n/8EbtqumE+3fkUB4vrFW349Ot/1O/r6jSHgC71GGKoIlBu7I1QyiGHkwqYo8G48KyH/KJLIC2AERqnLiYVJY4qmwYlZUnyw8NJuZwi/IU013MB/s/OiSBIoCm9wkJl1OZtUSNm63UrOTuWsndkeZ4WTtEciMsWRZgwZNF6yqyow42/3MVqIq/zsLUnRympx6NtmXTK2OOK5B2VSs8O5/MJgJM4h29BpkhVt+8TZN/kN681VzY7xFfbEUYcFHLEuWJKi52T08sz1cB7XfvJqdqciQZC/iyS92Eo/CiUJuDb2Ab8QVGbS0ory8Y3fwtcxzbXr+3w2hpd/aNZvlez9Ojg+4/VLi2nPTyf+I7Psxy/9d86ILKiKqm1inSt5iiikVXyJVQym5kapgB1GDhPlPu3ksXfNog5Wo+OHgS7uBr2vw/BbOemOhlRqLsqjheFNuelD95fMy2Pps2VLtItlUMUV8lGkj5/35mk2BYpK0fGafs3CRk2trhM0FI+fsPSNwMI9WKetoHHA7+txe8XjDlNPxSFGK1ajZirPDOzBRm97oCoieUApnnVW4c0BaHK20gqnxijKRTFndaEQk0SwjwmIhTjWOa9ApwjZb9By6bIZhK8QCfWmc0lqRtZsu77w5PDTzYu/EGfosR3QCCh/OLpegcbQPGdGnCaATuiUsIAFrDneOVudYAMrOIwoAzx8swBl1K2AQogTdqxD4D8CNeGwdXZbHB+kqE4bsFhamR5X2XmFcoy231E6o85gChXC+rXbINsVX3xx805ZfOhMKNi7IQAH/qq7cDuqy7h8MKGt1Di5zzVbBJbyIOdRSif0Rh9Adj2PV5w1AnJINZjyPW8IeTxqc1JlcQcYEkcGMUm0MyOn0/ZkqJbLpCFtfr3d51RCG5CnHIMx69Gv/pbbJ2EuMIrIIaY39Qk6oZrkAOwawbu8tmrtYvg+7i3of/CfUV3ungK8AJY8EqkGPafzPZ2avZ0f94yJXu+hXC8yy4tIcWQ0a7Xd7no/dI93tly/+KXyvd2Wen6nGuaeqD9LgKQ/rpsEEmy0j91AS4EjVWM1QDI1rTVhWS2UwZBWkxW80SwsvD0Txcdm/W1rGvdrtrXv1Y/pnoXwgWQU6HL3iCVPf/Yg3Pm6h3ODSeprkUjtGxbfUP/s/n6fHyW6Ffl6R+C+9vrnv/0orcj/Hc72sjPB/Vlu7b4Dx3yt9T8C3n3NuPCgq3ZLjJdVs78sG1Z72yYaHE8MOYaLR8Daz6zsct9BDWzn4NMcc2l3e1VqYcorGZniUyR98mo/9G5lnbFZkSsNLykkonbxPhDvJTJL/8g0z6uPjjM+1XBM4LypYW+eX91/oOnGFZtkF+iw18rClXAWQmVt1KAtd0JJ1pmIuRBUGAqeAt3Ks+wY38OTr0+bdUOpKb9QUOOYrqA9YaYkiliOrIjnA/dVinjd4YkGdfkZbkPnDNJppXeQDQBY7so/Mi4ndt37HyCEl1wnPHKmhD68brlR3DSYHbxIOQ+9/WFf3cqpEATyARU+bBu7NsdJmQ1gOxIkc2wn4Ii9uskXxHXlyVMOBS5Tfh649HOOG4ynZOzQB9c7qRKsE1qUtvKPYQQc1xpC1HgKjm/8oxo8SUlNqDQ5itiG0A+vkLV/D5Kwc66ZpeBrdQu3k/QfDoPn6d7HlUmgjlzlOS7yu1Y6h9bunx8cTWKxXuT1jWnsPcHm8nqBsfT+n51zDHmUalIpxqirfULKv/VjasBerMbUbabe/Wph7CVz8zlESJU8NJIJSTEUPd1j8Yo4T8xPDgZgwhTv333bIL3f1yO9Hc5yNANuxOWl80BmDfR61pSPgeb25bx9vvBLkfe/NPaTNJmTuAeH53yFuPuJ7h6Mtc/fK9d/4295TRt33iX8wpz+Z+Jy6Pot39ipzP1ZwLneMPy6FdXqfzZe3+s5v/Qpg3VtGjV8Aa3o/qdhtaTmsuJelTf8IpvY6vdHY+p7i5H4NrLjtHXskjXPpyVN+IWF7JKjRyNvUa9ESBZAVM34LSGRQsMVRH+236257m8fqfwxICwKxub036n9iZ6rvRyMut77a83+cfN34+v5g995hr/jcofvejfC/i/+cUq/w/ZzR/8j73vC/fbV6fXz0XtD7XN58vrl2nXDXwgHv19RAjQuyvpGJQMjrlUq9L3iaAl/YxP3ZEupFwtfit4ofxW8/jNW1SmMP3s6zXZkybZYpSfbElfRzLyOVtbhBE+/p8lSvumGwD+kxpRiiOG8zGJ+Hho+3FnNtk9fMtvP6APPWP9WVaDf8uORUCc6ybMKKRhg9VRiHLZkM07sawKl7BKUXwxzFVI0xqFAqUGUPOqyXWJYteYY7NZcKTYK7c56a9w4u0hWpwPAvsh7TLmMr3a+crqckYjruEhY7ryxcLhp84tHSC3aA7ujsG5O4x7tRD4NXlKkGuxLAJqG1Q6KLUQatpFJ1O5Ov5u0Kyl3t7noCaMQUXVMT2wwCaNWdMFfrTnbLfq8xOgW3CgtTpQ7uwacIXHwJXnKQ3cG+cP6zFHxnogovE8mYvnzXJjnWTESZrzuH4VHSBpnrdZc22+uELo9Za3lsSr39/ux6fzsIf3d7JH2Zs1agjfvHmmclQThUxeTPwjILN+6CiI4dJlkaNZO78qxd2BqWUwAjWmAD37BN1i278pLyfJ50h7qMXLpV5svdTpNb1MnWWeU2sXEW4Uh0oW6MyoZKIy7e18zU/HhAqn5XoORe9s4bYc9B6DdxEuQDM7z98SWdKb4H9dMn1D6r0hLPawz87a72dkjpg5mFBq1tUK+mZoLjJAOH89Lt/knO3onvta/RUnbdJbqK0t187x2iz6P4D29L8UlkbveI77f+N/smT5e0LvXDFm5HIuroqDRY0AJmMUzpDzHP45/hoH99TSqbbkdB+G6jmRo434QVxHdHPQewaMu9pKNgU9259c31sb7P0Lmd352933emNbxf5dw7D4W+Z1tRQkKpsCWnTLIzxVsZ0ItEntqs4Oy1zDRwlFtCVqddN0KRzVx6Sh1yVhQODk5RsMH5loEbuSj0ogkRk05EqsrhYl0ofCiaVcsLnsFT+IT6XujF2weHp2FPhrnXr3EHhchokcgp3cxbvLPL26Qzet5J1Y3o44mcVPlLGJucnDyHPyY3soEkkzUPdTebnjsJ6c1OTz2zQFMTgCAwf8Fw/JJoQEQnAMwnkcyR82jBaDMaXoXhkOuE+Md/oEKv9JkGv4nBBUNpmUVgQJREJIokAgIApgBIJGgWmRcbH/WWVJOT02+6O7Nn+a8rc/AAggQXgkzq5UXUes+ranw0k19yPGfe0HqzhB39FMRLHASkzIMqHQ55EP5FYfAUwEv0B06BmpCAcgYl9anMCZVhS3gWpWmkOzSgwhicE9DUGdWzwqFnSfTzYhkJHGWDkhHbFjweaE5VDQXcCpz/cQAPQUXgZhDFGINojxa4JDgnbAdfcKMFbCt8Uq3Jt8ep8YSI/EZdio0Ysk9ihvR7n7clRZWwhTOgi2hlFDOjgahCcZBskApCmLzU8++JXM190XBBZIQUWqh/pzhW4ow5nyfmZKgfQK/V/vzWizagTmspe8HC2HzZ3bgbG4TfO7wrtAuR6BGPQdyGhxCORQESghjj9M+QTtZQHeNMnRjSzOL1vnwwxA7OptyUGZ5WuaxaXTlmsNBLN7SmfpbNCS1HLaGkqOIuqxRWWdpa2bm2L8sUJfUEVSG0FjRsJ7aoMKJ6LovYUEgLb2kk9rjzj+xwLlKEbM7x3NhwungkhrK32FRZkeetUm0sJpJ9+y6gqrOA08eO6vCQrbRQ1mVVJq4Iyc5gOG0KsOl9r7i+qX7czVt5ki39ufJ9gXfi0lQO77ZZVsP3PiXkdTaUxve6Dfje6n1IfO+H/8y7vpppjq0gxDFbDNPKVxJBrdBMjFDU1beEEpoi9V4hPnlaqmx12n6iUvj6+Jnm/zzc63GsBXp7oYE7ITKdyZrP/WjPzfR9HcTX+7yn/7l/0v8c1u/63E/N9T0q/VnvpPuK7v3S970V9z2/4aU2lKC8fCy8QMazpKz8Aq3V9ZF0sdUzeu42m8AICavBzwNIaRc/9YAblImxVZvD+WNQ38oelpmYDLrCZmpnzTpRAKHTGeNhwcnLNxyRWXBFSQMPBjOp+7gF9AgsBHP6gcf5F0Mb8G/M9MFJXp2EsIivnQKbL/FtuB/Zozf8Ox6Zuwx2pBRVFYaCVnsQrqhLNzyEAgYKmjMOzP0QwRKYOcbHldocDGs=
*/