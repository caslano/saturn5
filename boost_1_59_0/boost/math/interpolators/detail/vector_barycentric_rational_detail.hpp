/*
 *  Copyright Nick Thompson, 2019
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_INTERPOLATORS_VECTOR_BARYCENTRIC_RATIONAL_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_VECTOR_BARYCENTRIC_RATIONAL_DETAIL_HPP

#include <cmath>
#include <vector>
#include <utility> // for std::move
#include <limits>
#include <algorithm>
#include <boost/math/tools/assert.hpp>

namespace boost{ namespace math{ namespace interpolators{ namespace detail{

template <class TimeContainer, class SpaceContainer>
class vector_barycentric_rational_imp
{
public:
    using Real = typename TimeContainer::value_type;
    using Point = typename SpaceContainer::value_type;

    vector_barycentric_rational_imp(TimeContainer&& t, SpaceContainer&& y, size_t approximation_order);

    void operator()(Point& p, Real t) const;

    void eval_with_prime(Point& x, Point& dxdt, Real t) const;

    // The barycentric weights are only interesting to the unit tests:
    Real weight(size_t i) const { return w_[i]; }

private:

    void calculate_weights(size_t approximation_order);

    TimeContainer t_;
    SpaceContainer y_;
    TimeContainer w_;
};

template <class TimeContainer, class SpaceContainer>
vector_barycentric_rational_imp<TimeContainer, SpaceContainer>::vector_barycentric_rational_imp(TimeContainer&& t, SpaceContainer&& y, size_t approximation_order)
{
    using std::numeric_limits;
    t_ = std::move(t);
    y_ = std::move(y);

    BOOST_MATH_ASSERT_MSG(t_.size() == y_.size(), "There must be the same number of time points as space points.");
    BOOST_MATH_ASSERT_MSG(approximation_order < y_.size(), "Approximation order must be < data length.");
    for (size_t i = 1; i < t_.size(); ++i)
    {
        BOOST_MATH_ASSERT_MSG(t_[i] - t_[i-1] >  (numeric_limits<typename TimeContainer::value_type>::min)(), "The abscissas must be listed in strictly increasing order t[0] < t[1] < ... < t[n-1].");
    }
    calculate_weights(approximation_order);
}


template<class TimeContainer, class SpaceContainer>
void vector_barycentric_rational_imp<TimeContainer, SpaceContainer>::calculate_weights(size_t approximation_order)
{
    using Real = typename TimeContainer::value_type;
    using std::abs;
    int64_t n = t_.size();
    w_.resize(n, Real(0));
    for(int64_t k = 0; k < n; ++k)
    {
        int64_t i_min = (std::max)(k - static_cast<int64_t>(approximation_order), static_cast<int64_t>(0));
        int64_t i_max = k;
        if (k >= n - (std::ptrdiff_t)approximation_order)
        {
            i_max = n - approximation_order - 1;
        }

        for(int64_t i = i_min; i <= i_max; ++i)
        {
            Real inv_product = 1;
            int64_t j_max = (std::min)(static_cast<int64_t>(i + approximation_order), static_cast<int64_t>(n - 1));
            for(int64_t j = i; j <= j_max; ++j)
            {
                if (j == k)
                {
                    continue;
                }
                Real diff = t_[k] - t_[j];
                inv_product *= diff;
            }
            if (i % 2 == 0)
            {
                w_[k] += 1/inv_product;
            }
            else
            {
                w_[k] -= 1/inv_product;
            }
        }
    }
}


template<class TimeContainer, class SpaceContainer>
void vector_barycentric_rational_imp<TimeContainer, SpaceContainer>::operator()(typename SpaceContainer::value_type& p, typename TimeContainer::value_type t) const
{
    using Real = typename TimeContainer::value_type;
    for (auto & x : p)
    {
        x = Real(0);
    }
    Real denominator = 0;
    for(size_t i = 0; i < t_.size(); ++i)
    {
        // See associated commentary in the scalar version of this function.
        if (t == t_[i])
        {
            p = y_[i];
            return;
        }
        Real x = w_[i]/(t - t_[i]);
        for (decltype(p.size()) j = 0; j < p.size(); ++j)
        {
            p[j] += x*y_[i][j];
        }
        denominator += x;
    }
    for (decltype(p.size()) j = 0; j < p.size(); ++j)
    {
        p[j] /= denominator;
    }
    return;
}

template<class TimeContainer, class SpaceContainer>
void vector_barycentric_rational_imp<TimeContainer, SpaceContainer>::eval_with_prime(typename SpaceContainer::value_type& x, typename SpaceContainer::value_type& dxdt, typename TimeContainer::value_type t) const
{
    using Point = typename SpaceContainer::value_type;
    using Real = typename TimeContainer::value_type;
    this->operator()(x, t);
    Point numerator;
    for (decltype(x.size()) i = 0; i < x.size(); ++i)
    {
        numerator[i] = 0;
    }
    Real denominator = 0;
    for(decltype(t_.size()) i = 0; i < t_.size(); ++i)
    {
        if (t == t_[i])
        {
            Point sum;
            for (decltype(x.size()) i = 0; i < x.size(); ++i)
            {
                sum[i] = 0;
            }

            for (decltype(t_.size()) j = 0; j < t_.size(); ++j)
            {
                if (j == i)
                {
                    continue;
                }
                for (decltype(sum.size()) k = 0; k < sum.size(); ++k)
                {
                    sum[k] += w_[j]*(y_[i][k] - y_[j][k])/(t_[i] - t_[j]);
                }
            }
            for (decltype(sum.size()) k = 0; k < sum.size(); ++k)
            {
                dxdt[k] = -sum[k]/w_[i];
            }
            return;
        }
        Real tw = w_[i]/(t - t_[i]);
        Point diff;
        for (decltype(diff.size()) j = 0; j < diff.size(); ++j)
        {
            diff[j] = (x[j] - y_[i][j])/(t-t_[i]);
        }
        for (decltype(diff.size()) j = 0; j < diff.size(); ++j)
        {
            numerator[j] += tw*diff[j];
        }
        denominator += tw;
    }

    for (decltype(dxdt.size()) j = 0; j < dxdt.size(); ++j)
    {
        dxdt[j] = numerator[j]/denominator;
    }
    return;
}

}}}}
#endif

/* vector_barycentric_rational_detail.hpp
368TeblbBZ4sSnG5lMCK5KeF98kutpBI2QGlMOTI6UaN0Gu7izSX0tOmQWV1CyQz8U/hX44m8xzsPnrX4KbPSaukV6xwU9e7h80+dFlQHfJdSynx6ZYReeOW2lQqD1+7eznVHpQc0qPaKUAAdBLfwNcvVepizPFm4bp4jelTT7PlabHpiWt8TNfjyhFT4XQppgZ++eja/GZ3j9sSWDImnXnIU/2vqjyrrPKZDcfB+5n3Ud63CfyQcB716ZmrolplhCnjpuDQYgoyC5+tcyd2TNK3XSfmrA3GFCts4OLJwNBM0FE2BaOTRv6luBwMp8qRc6GYHd55QKSn8H0pXPe9HymITKUrp4O9KjShdXVr1GOgshZ8fTRmezt7QPlyj78u/SkZxJuyHUdLcbnJwXlyntxQ1Juzye4nV2KfZ5f2ui7BRMQuNIlit+ApTHxct5hXvfDZQ6JcB1Uauh+4tk90DmIP0H69/jBx/6ZAzBAKZG7vRR1StyNv2IAXUdhPimUYyDJYsL1GEqPH6zGS927qPqkTlUJP6bin+mHim+6K8yi2ueamIPnVvuLX5Ow8GW20yNjKc1cCL+rQr7CBfSjkP8kgiyassLj7GdafxBmrT7cSNh9gwlHhhrgw2dpJrJjInrDDVKw2GpieIxRD9n4jw3gmkOrveUhDueySo+cXAMtI27rx3mD2hJLSgGI1rc/TsKiY76JrYN8OXkqgGFqn71rc9PFowCLMsTan41jmzyrLjE/PbWiQoGPCJcCgBttI78Mu7Bb1jbR/aOqyyMI4roEzdnqrc5pr/Kt6S6Juj8Yj0pLG8dT6nnx3SLh+1H3cTsSegVWcWume34gOSQfdDSMhh9g04eOPZKcgcZ32Uo0B2F0qBc9foVSCFDdMdgdZP9yfwruSA8B4I26boXbjAgFZHWTPLjGnF74zG90uA90gR4+Qt1SHLPPhrI6ZwDmh/Zb7G2JQja0SQtWjOwTQJdEBHT8OBxddozGX5zWzuHXe11BIseve10/AB1+8og5x/Z0lzm4DSShw24a3KimSeKqcYy/UTCXOe37dRZvHyBJYSIwqK0U4iEmEMZKdRyH9EQ6Iwd3fSsetsHTEzKN9fn1e/AUUjTsF2qHzTvldBsqZGsPnOxGk9CvaqzpwyJFwE1vCH8EjEmgBRKTDzhOi1qljt+guxlBw46tQrx9I4tUAjXiuq9ZtTNMXHn6nTQBNuyQ76833fh9RSooQisYwe5nnhBCPJsbNXs/DtEpiexvvQsnIgKnvOwx6naBqeaHLwTFnXqMu2DsUvITrveX8OtmH883vBT4NZaROgvuDZDjndDs9jb63d5ZeOiEomdR6zYXlYnk9R7Oo725clHy9zj0hsZ05BoSVniDCcBC9J/tNQWw9WNglJaguH47nEgPFNHXvHmua3kt5t1taoo7PQtmkppnZmb4dF3fQ84NAXJ3IWGqYcT3/1vcndq7CaS+0RJz5wuzY6ZgH+rBkGTBcCHTNpTZUa8OV5Otf2kEVFYxmCspamDUvYcEUjAk3QNdU5nAFroqlXk0LJdJQ4ZJr7DcK/b82uTZcWYjJprQy1Ss7Ok7vygPZagTbt6w61ZnWO1uxfttkKzCZBULuSJ+NmHI2e4V6HS24+XhSbQJln/MivGFgcIJefzXif1B+QN6EP+PFyIgrJPFuAvK/K7Kl5+XR4F30vHT6D6HruhxrOuoNNhxCHe363akCd/7tksGwXiNEcCCJX11cJXzYihDZ9a4yzRXbSxgfiOAF8eS6A1fVlQsHp0iS1eXFIsXDZOiOLWhwwRTSx/fsvu3GQ3E6Lh7FfLZq9FwBH5ViU/AWVrB+EJMgHtg7Zrrt9ceRSZU2q39Mknx9BmLADrz2eCnIXnvAs/POakb8WG9m4wBOIWFjd4t5raZb+t2tO2yrW217K3CtFoDpyHsrUv/88FpJfoR+hCzXan2vK9RP2halDowQSn9zz4MNROkvSjhvjUFHSHbDoHqYWVigxBRGtv8Mzaql5OB2kLHvgIaa0t7elg1xFwRFZopp/xfy6VsuL3xGyQZaS4SMCypkycmQMQxxRCKlz58+kXQyflOuCyV9/7DhqbsGf9z6THu+rgaWRbvvMo/vM9AoZrgW+pTCtwTEy3hVbHRwvuIUMp0V93jK1Xm01CrlJkFkECTAUfqR0whFIlH9H/ajzGO35DQRIyRugAq6/dKlbZ0qZ60N1F3STPQ285GWX07z124oFhOk9QNOcuj2N87Fb7e1+5DNqXlB4doSypLqGJAf8ucN37Qwj57GFPgCdx3w5aSgjEa70dTc68RbCsEiXqFm+eDZpYxRb3gOJNsjmcbbpRZ+megtBniqOALnpnPvhmP9j2LxZT4FX9/hJkBh/37/mIv6v5J/pXpbKb+qKFTIsV/zev1yRrxGqWQUi667DZLfGIrAm3G18cJNztem6KjcQNI+jDarfpID4V/gDOl7wh4p25jVXFTBH3u+GF/SDrRvunKsBGNLHEUzeTPSa6ZLgr4tZNbTHF79oN/JwksDNi+BhwtQc8pVSe8JUGwStQDgMNcCN22a1ze2sWAKAhxHP8yAp/qKZiKwmdY0qa9IHRPf7VMwdvJfE8AfvnESqM0RABf84Vrf+5kAp5nCj3jqHhW0t2Xyoqg02zc2VrkxX7rJLgrZlGn2OfqUazTOjlrcBKM4rxYClPq7/CDZGksIPyz17vkVrJ4Qnp3Zy09uZge+DYB0Q5jGG1o54yV9FQ4T6bLArk3NAwbmluTXCmUKBEVPhXBP8c2NsJ37by1ECcc5thUQ6aoVbs0RSZ3Cqys3kiXAglUKNwGJgRFkrhk4KgvDXDryTP6tsxkYyyXWVtHNKtR3EIF5Gk2SSMsS3hb/gbZKdyb0U0L69s6U8rq0gSGBSd2DGWiYBUt9TSMyueniueV2dbY7QKB9CXEXxHNktg+BL25T6sFJHHvfm/XALh32vs6l6zvQ6WfaNfEEZdm4cR17Ib20OCASUOejDJGYNmbtQFe6lRgbD/iQmlciRDmfNuPqqLfedd+c7aa3jtvNB29FeaazFRx5iPUOMpNJTiVP8QKX64T4xXo+T3W3i3f9+502eIRcW7z0eg8DBj2n6yMTiTjhu8LB24IWg9a0MfqMZ0vzxHkn0akaBnoAEGLQyLzcVEOcoVi3pmldbYSY7WJuA42P0xgqtT8/umTJ6aElY7Es7ziDecBePz3hXiZmAoi3zA2dTBbYN89zt4Rtp1qtXdr1JbrF6hA8Gviatwj3Zp/seze4rfaqWt2kX1/wKIEOJBhuANQu29QCs5MtdJBkSABiqTnY5zJiwr1/Z3kcYOP1ca7S8zxIc2uU8XmeMtab1uZZ9Z3c00jXeu1i0GEaFzt+KR0+wsMTa/VdKA2lM7ZtWMjNVMuYLM/wbpjUHZu/roJTMJUa4dEl374e8UiGD9SgJcKlaqug9jp/HaV1JS/+9DJf8i6HsvhEt9Xs77UKcv9Ir85nmv4b3E3Xmy/T35Vb3qOPO/WVN9dtvi1kHZuxEw9Ze2qoW76JHaQbLin3bTgc7uoGQ0KFhNorp9unt512wCApFqiFHibBcB+OGuSBsvUtOF3gYgnXKDlb0s2sJcVcXarJH0rgsPrex+wD44of2+4U/u4NDFfKFZVtX2c0vtj+sAhbo+gwPJdOo2bSEl9kICBsXShNSW+wAVz1BZOj0KgiZ3sgjv7NV0OUbTiUom395A3Qy6n/5lZDlfvU8wJLTaXqEfZDkNoKZgsZonplIG99prBWN0jH/skMaNp13LSejjD1TrY3llI/KAyZPm/2tlZ553aLzHZzrJYavywQDViKNn/hbCpDMJtS3ks8LxpRwZmn2DOXbsMMsTJn0mJGjUiN7GdWkoruiaSv16km7DovWbVSq+8RcytfLeTHCRVXNpq+v4wcTWB/coJh/BZKAFkFWb9XR/dI1fMid0F687Rv8Wu7jeks2wxU3PHVk3/A2PDudEiiqZujpCz7iQm9PuO9dborNffi0D2c2037KwjnpVinqJoI4p8wm3jyHNwvP4FDhuHxenCiv4s6YnlQXR+1QT5Rt0deJvDNv6LJqXS3Tx0T6mb4v1tRQq0eRBGdR9Lytb55ruEvcO+o4zRbVhpR91i9PeKx9MvPQN0/2kmoQKXbRXjl9+32oHV2dsQ/qmvkPFfWbt7Xv7YniZSOcIi0izbSz3OiQjjHhmgcManFLb5JjadyXa1Jq5jomGtH7MsF0Xx21S2HvfY30GBBhdcVtDPIuwVeTe6sA8PV0GX6OkCFQ22QNkSLjXEfNcuklWotqOrghfKdByVER01z88y5+Kpe8z9tBxFXyxUAB5NNs+2OOBACkd3Dt4yKbIkBYUGc7jM0Hk9yPMH5LLx9zPF+zShxC8fhzs7BSswBgvKvEejdCNr2H7Mhewo41lm6dJLv/IhRBB+4MNlhswUE0QK36DsjzVqFoAG2GA0MLFx3ngsMN7ybA5DBL6CzzXnCIqTvaXmQa12VgaC6Ju8+pQb8UFoSYyx8ZnJpI+BINaK7QKjKIs5KuNBKtlAxknfj0V86My1889QSZ/vUpPFnSEdVWxbyC1oIh/vWsBvvOqq+cGTywAp7rabK0wnUiQGW2qtggmogsyTM0ck3QMvu36vUK86wN5NVpP2Klrlrgh75UXqJefayunCMCtrCKexygx+vRYkdxNbLnRnkZ3zhplLd2R9GjLLg3F9VoAgKNqJmBTfkxAPS75U+6PhD/pLKqH8P5To3ev2uq0D+Sqr63TiSfQIf13Eh/Hy8IXx+7jJ3ldwqWMXZo8918tz/Vk+rMugVHC3LTZa1nsUToim7hIQsYq5kjdtuD/78Tn/xOr7HP0ZzCwjP/oI/8xqdBxXPAEUnW7JxKv9mN53iaAkqIs10e4whVsRizV2ZSX/LQH9OEc4sglu+XBnsvbLmp9/gbVIdla35SITr/ONpnTsT4tjdkicb37Fxe5AT/fk4+y1W6nSDWphYGN7W4GiyGnKLGFkcd2uS7GBkbmxAm4MaAVygZxrePkMQxEaJLQotflkvK4f5dd02CXbmOFSRUUvwB66CJ/PjDoZ+wiKohGey3h1iuj6fsk5N0rmSxdw5iMmho0s9BVvJzUC5laYru4ZM255KE1w8ccKe83C85e89jx6lyZNGZeJeSgD1hqU8Xtb+WL5EvxsNrGlL7Ddyv+o949lfDVfcr1vFJt+siuCROhmvNiykpikrSPhCxQoPuav2YqidqDHogV4ipIMzcWM4zG7KS+DOHdR2BjkwjgRnIWUrr4EnoYYdCU/L+epcHm4AIG6QStz3ZkEb6hHRCuXAC1aBYRIAn8dqCOKrT22BJMJHcD4O/TGZhUMLPn3cRYT9D8XIltvq0vH4kaswrzTXGQiHZNL6lDfVf+G/NDGE/+Cdy0iDlMTgvN7P0NkzOOVUN1qGNqfa14htM5PGnIkiG3GfGdnNms8qUJVB6itWzBeC5JgWXRyiqxbX7adWam+kKGYPGlKgr4XrL2NH2NHwvl+Ycmqc0/FNRxUECsh+khKdWyLj1LoRGOEZpfgWU+7tooNp/llBksl6uZ3pwxWOdD+OwD9aaYdcK8S7Yi8NOrGJ+RL2Z0nL0iK2TE6a7QErsmZEPQk2JRKdZzvrVFwz0hf5XiVMbtQaHHhy5nKHpu76ymlpbVt9D4OG/IpjiK1UfeX83hSuKWRuJA9lwiF7dSjnVhR1ZftMcjKTmflkt27/bM9COr7X0vE4OHabdx9aIorCymx0hTrZVaUztRKfH01N/OeuQvqz1ACMhtUBAKei2V01orE8EHEzl2pzz56A6uH+2aqI/RXWq2mvXD50d5ny87PTjMieL/J7+BQQFf3q95/Pd/7c1MKTSaWbl+GWR6dkkB82il4ODDbkNTI87UaK68UpEcIaLJONp3e6CTYp/Cp/Sw/aglGCnlKaPKx/JEMxjSp0z3J9yTKr9iwXu5vCt/UA3aYoqlJRceGJ/tpF0q2nOXRaYX/ybuEtAGGKuLX+udW1WEJCW5L36HH1TnFHR107mcbIh/QyEJHW4V3vLO7Jll9W3FMEbrHXQIqNYfc2Hfcj03qw3pnskVMf1QzR6ncppAyfoxSC9+5k9sjvywB+YRwZvjz1GKQJvz3eY9oEc1fv4Cg3paoedTyzyqoe2TwmV0UQoCDUTMUORZAnBxDMvoG/kfZvtiIp224vB8ckMLV/NYq2q/g5gwvTFZ/lher82mFS/HJO0fp5jFv03VRMmutIZcvLctvRW4r9lALE3BD3qxrEVmI1uQMIyqP7vSuDaRI5gwFkCn9rSG1rebkbUQwFFsZVGHmB2ALgqvHXLj77uRgsO/ItLcOH4BYcobg35bWxFZgO6IIuJglhGoPLYQ0JZ2sYBbeT45Ba6+vq2czr8LPi1zMruEP7y6be05PXAUNiL1AJwOPcXUMxd7tE/9YX6yoxzGgr7I5P0kyyCUHONR8rXl17JQcTXNUTiUMz3ANLAaadJC6cm8w2+QMnaWN61nOUGlqTpPH2xXyfsmjtPI8qAfvTTXjRW5zWYtLIL5PNpHz8q1yS5Zd0e8SdURV0wnDCCEWUq14nqszGIjfsD5npIdj5zayU5oM//INPD61lz4kvXPPrbfcXrY9t4Wyed9/vllR7u3LWv/tJ649+5axJB6afBi308MCixF6YkCqp9zo+kcF2uUEu7H7FsKFuoq00U/1I/U2Ww2+RSYyUrdDB1/MQ7gGW5WrBLdSER7Zij/LwTR47A+GPkDhjwbcQlyBjWxg+vTm3FhJrINN66dsZZ3NPL+4T2N24jHRvWqeDWFSzyd4ocXaVPZEIGgCyPIA4Sn46ASZ2hzdlAyllwKwSEsUPErrc/kz+FuOJK8ABbVoXb0+S229p0aMuw3pu1tWM0SMR9VRySFkRHlJD6sXnQ1HbCPzlb2olo0gCq4rWCALP8v/ID++0FbE1t9F5OglH26ySMs09pXg+jAQ0Y5zVgXqav2tFaC7dUH0ymod3dnpytnI8paCzdF3OaIa1I0OIk+mfZlwXRzMopdFLoKhlrXHIUVgGp0BHrDK31jbLJjiTvzz+xVHKdANaV1HTpJmqSghtmI/qUS0qxFlIM0Id2UnHZjGu9XGBRMek71U5bjTlnYtTWMLSUfLUru4Dl/xA95xYZyypVQa1+wf5sJrkYsPQSdIGuMpx5OQ6oxrVumEMau1tq0bTVK8uNJbXJGs0j4ilpq7fu3Y/pR6zWnmF1Zl8TGR0y2zjudEy8Lk20/0kZbeR+AIhnZd39IZ8cbiTgUGgUzqHsBrfQG8ygaKkGdIdKR4CF4VbW2JUQ/FNAePTiHoerUWZtrdXeUgmC5aw52lltLEQPBlfnFPAUnIyrVFDP0T6e59x2HUMrUVZ5jefxvGqI/oRVCk9UP1gn2RvjJDnCFhVCYdEpyJ/8co2Ot5H1+iGoZvAyBLqvuq2mkRB4tGMYMh9tV9H2EqGdDqtDPD1N1fdPI6jjgsKZ0q9UJLmKSUb2uKy+kNlNy0xyuhoMtdpBWmI0foSAa83vLNv5Hn9KpMPVngfFdNYsq+KFePn/7jwC3dBXPOBtJ/ps/2mfybC4M5eIvSs9/wOwYC3tux4c7NqGmzo1OZ+bkiYSL9l
*/