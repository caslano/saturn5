///////////////////////////////////////////////////////////////////////////////
// weighted_covariance.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <complex>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/covariance.hpp> // for numeric::outer_product() and type traits
#include <boost/accumulators/statistics/weighted_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_covariance_impl
    //
    /**
        @brief Weighted Covariance Estimator

        An iterative Monte Carlo estimator for the weighted covariance \f$\mathrm{Cov}(X,X')\f$, where \f$X\f$ is a sample
        and \f$X'\f$ a variate, is given by:

        \f[
            \hat{c}_n = \frac{\bar{w}_n-w_n}{\bar{w}_n} \hat{c}_{n-1} + \frac{w_n}{\bar{w}_n-w_n}(X_n - \hat{\mu}_n)(X_n' - \hat{\mu}_n'),
            \quad n\ge2,\quad\hat{c}_1 = 0,
        \f]

        \f$\hat{\mu}_n\f$ and \f$\hat{\mu}_n'\f$ being the weighted means of the samples and variates and
        \f$\bar{w}_n\f$ the sum of the \f$n\f$ first weights \f$w_i\f$.
    */
    template<typename Sample, typename Weight, typename VariateType, typename VariateTag>
    struct weighted_covariance_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Weight, typename numeric::functional::fdiv<Sample, std::size_t>::result_type>::result_type weighted_sample_type;
        typedef typename numeric::functional::multiplies<Weight, typename numeric::functional::fdiv<VariateType, std::size_t>::result_type>::result_type weighted_variate_type;
        // for boost::result_of
        typedef typename numeric::functional::outer_product<weighted_sample_type, weighted_variate_type>::result_type result_type;

        template<typename Args>
        weighted_covariance_impl(Args const &args)
          : cov_(
                numeric::outer_product(
                    numeric::fdiv(args[sample | Sample()], (std::size_t)1)
                      * numeric::one<Weight>::value
                  , numeric::fdiv(args[parameter::keyword<VariateTag>::get() | VariateType()], (std::size_t)1)
                      * numeric::one<Weight>::value
                )
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if (cnt > 1)
            {
                extractor<tag::weighted_mean_of_variates<VariateType, VariateTag> > const some_weighted_mean_of_variates = {};

                this->cov_ = this->cov_ * (sum_of_weights(args) - args[weight]) / sum_of_weights(args)
                           + numeric::outer_product(
                                 some_weighted_mean_of_variates(args) - args[parameter::keyword<VariateTag>::get()]
                               , weighted_mean(args) - args[sample]
                             ) * args[weight] / (sum_of_weights(args) - args[weight]);
            }
        }

        result_type result(dont_care) const
        {
            return this->cov_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & cov_;
        }

    private:
        result_type cov_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_covariance
//
namespace tag
{
    template<typename VariateType, typename VariateTag>
    struct weighted_covariance
      : depends_on<count, sum_of_weights, weighted_mean, weighted_mean_of_variates<VariateType, VariateTag> >
    {
        typedef accumulators::impl::weighted_covariance_impl<mpl::_1, mpl::_2, VariateType, VariateTag> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_covariance
//
namespace extract
{
    extractor<tag::abstract_covariance> const weighted_covariance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_covariance)
}

using extract::weighted_covariance;

}} // namespace boost::accumulators

#endif

/* weighted_covariance.hpp
vSfU1MebrzW7p1i0rlj2gWchtibzCBS0UwmeWwsXCd+by0EEd/Ctb+DJQuR66UbOEA8vn4B4R7A07R/hJXKIidiWFBSQgxy/q61eSPVAzFxYWyGXg0bF944G8rcpJT/GmfLOgPVUnsNrLyNO2fFUdXtXof5GHYBGKb/1JOP+t+Psmva19akB9fLtNXD8NYJWlRES8gcS6oTjAXVJVI7Vgm1RL+YD63bEM7dgvmjLe+jOqXDbrpwwlrkBO1a7lYcKrPyq81EJyZtywcgxTOYRYb5Cse3LcUYEj5bJVS6Kmuivg5P1oa28OkU22KXD3Bg6S5fsAIwXP4McP8F6K/gi553Hsf+UT6VPqlM99cP59S0bzs5lKKXIBn6uO4pdV+q1DSdvnydmtAkbM2iukyMOkRD3Ul4T4JlMpDe8DnBMAEg6jW0JbPbVXs+F6GKvcjCN9Uc9s7a+Wgylf0Zczu3bmx5H8q5brKdHqk2ax837a7KDR7z6704atH/Tdh37hU1Og/ThXe1nNiaWLgywVPLk9hr/y+orztwcSQhXVokp+GQaH1k3+HQBEb9Z167FtdtTyHtfGnTyk1AqM/bMAj5MstF+BlV23Jei6vBL9Dy8vA+U20ovHRXQD/wp40Yk8xsgHC+fI18bf5UzKzUhlUudaljciL2wrhHOYqk7XYQ8F5VpinUT4yBj2bG1ukFSTtnfhWmeMy0nV83qE2A+Smdutt7YlTGubvJID+7bDY10K4/Dpw4aEAJvKThRIkK20ao/cXEh/EBIiVLs1ol7N/kgnqDkNYQy9KLWvAil59zme78g6kNN5c6XGjdj2EHXwxsVGEw84hYz4EpFoWLkr94uvBNaxjDAy62IGLAn14o1cE/jLILq/3WcH17j3sD0YCkdjzPKpw5RKxNHj28kWeO3y4fKoedpSBHnEhSFYyKTGjml0bh2czXk/a2St+BTIA1K4KZhP9/BaoniMkZUIcQ3F/vCAiETVBDBZjaDGD6GnE6RjM5FJwpq49ttKTGSjPFNwtUIgMvFfZgq0jqHXkw22M+IvAtfQfoJlhvlG3snoppQVuDBIdNRbxGuibScPUsVbwdUTlgpxjLrB8cEJVKV0HnLVl9+b02UVhXRMcpuHygwEl6lIQqZ4LonCLSxXheB4Frc/+ytodskoCqF02ZbGQovtU7ttV90g4VhItgcj0celVZneUCPiE+mkFXRHufZezNhOaWHBUH1z4CsgGGrcUodzIiU7XHj9boD4R7vkTsZodQs1JVFpwJ1CQeMUCtdgEGrZcINWykCLknGYJcZAiiGSeQC/VB1gT2TPLhe9C1cCi53MJXJk3ktycnngecx5kHnqebJ5xnmIeeR5qHHttDW0JagCWc2hzm6EeQa5BLkIkSG8x7DaoKwAOX2T+BzzAuZazbnv6yBKacxJxyBHoHegFaBd4DvCI4nHGNGmm+UCwxgz6GKp0qm8jclswxF1wBjDrQRrM/XeG14fXpdeQ167Xj1es15BXtNeF16RXlte8141cpRl7WW1acp+HIiCg/nt0VfYB2uHwIdpp8kFVTb2abcYdzddG/hVeb1z+nIAcx94OSpXfz05ZJ0wr0PGbomE0xyJcFD5KyCW8nGOJTwrWhEsoNgA9fyYPHu/HUDeeWrNxkoV84lIDZVwaKv1tceKK8WHc0qIBbV0mKuNtIGykcsWeGhOzGaJMK4hNFp4DRBPEH5g3ACd3L+sTS8Pnwzezy7P/v4cZ78mPzNAmnO5JYaQCjY8AOZw8ErKPPQhuVjP9x0wP+cHKF61JbkqG/W/S+XJ5cplyWXATdPuUlZuHUoL0w8U1gykiaaJho/midaPlMmkz9T51MWd9Z7bCdgA3GuYrliSUKjHc5wy7S2WHhXQDW+ILchoeuhtDYC+F0L10vKPQUulSpuIWcrZ4CZiqmq1dCI+Q7YsnkvVdG2Kcm0kn+iRlQJmZtWWEuNmflnGEAAT6q5zvZqYFw2DXGQoFg77RiTqD+rqgid+VOwNsGkRbQ6QjegCEubuyvAgmU/bqY5XjeiiEDFOw/Qk+Xg7rA51JK710iGnUxWXFtdUL26KaBwjORDCaKwzsnCaPcm4tp/rNE3P7d010zTV3MvNTAmyaxUqFSkVKCUv9StVKNUq1SnNEk/XT5Yvlx+2mPn4/W54HmoJ4SApP4YfZeyCLSCWf0XMB69r2cw+RNowXEhsuj16RE5Kg5qJGm+hKdESXarJcB8Li4AfFCqI4EVFAun0oa4alqvm2bZiyM1vIB53YtJtbyWuVw6VqdbhTh1uvbYo1UiH16NgTOI0yDhtt0jWcmsWSIZS5R38+KaEiTGoytsqIwFRTqGPXi9080GTBhMaELdMprCPcaHewnyRmM/fyUhVk1+zxyA6b+S4mfGSNDR2y0z4II06iqMLFTNWJDtDpy1TSCoXldkp2TX5LVKoCZWJRYmliWWJhYlTYqZidmJGYqxnsRkyKkTLAnchraWJnHeSy5JLksuSi5MrkjeSu5Jbslq5Tflt+SP5ayKz8o3y7fKd8v3yg/Lj8pPy96KLouujBgqCYULx4ptFTzxNGlxMG/SYYWkozQGMyVxgoyPHVp8XuLWbPWgKrbYQrbR8rY7G6hSiQQ3iUr4TyEGluY0ywSwtqfEFXEEc4nlkjBLnsdIg8TiHEfls64MafvFrwfUThJWbluTc8lLFe4iisYlidX3FtoQ6RePG+X9xwvRpS/4Qw8YZfvHDUJG2fRhsGj3cub86GY3RRAPAsUEGkdYFrvozWj/ySPlAvmVfA9wN8h4aXxUcVToLY6h8OET4w6PcjzIxyhj5E4nG6CDrzR18ssBkhZj7E4rm8IqrmF1jEuAzKKQDw8Cx5r5/fcE2gvpteiVSfjJhkkaF30NEMPGlJVhD/StD/VgQ8dBej+RWeNcCvtvLum8k4a3cPdknWGkuvBdmEbuIbu0Yapqf3v647T+TqaSiMVZg/wfs/sPtPnoCm4Da6VKmd762t3836rcKt5XNd9MY03zzR2qEfoam5/RAVjjN7O7g2rqdDGVm7EhHB6mCbTVZDiuLqF5GTbYQ5kLDB+pb4Gnt89MOe/p7k7YdcuBx7zccjEgvfqTtFORvfvGoKAR5FFy2HNShRlMg6KzPR8ICssqzI3RMkTKImH6Vtslr95E9hFNz04XHxp1rHoCH0gqP4D6tjbqUG+11p0TTFaNemPFlTDgFW/HUWrv9HpSnsmyzbb3jktRr5GuGFeVq5YPoD1BX8TzTmPn+zb7Tg/TpYwGj45dG1ows5Ajb7ChbBTuXv7t/eUd+uPCPjFo3K8uQ8DvC3SCMhEJ7FQOOrOWQ7DnOygEJRBvIkNlGWpspV/umK1Z2xd12TU92HhR7As3R5rWxYslj/yFWJujbbgtnCyTYLaXany0XFKubAqXetJJk6xA+g251HZ+Wwqb3GLqS6ZcK5H2erHx4izCU7L4YWHVTWHH/uG4UWFvgww33OuNFkZ97dF8v1I2V48Cs0KzQrUisSI0raet2e7rjuiW6rbpLutWaYMVH3lvgI6zDj/vqCfsS4b7mHXMo1pQ+tLj/wEngNh/FopB33umC34WoSUelIJWXgjyhQtKskAKjdf40OdVzA6or9S2EYQTlLcGLod8BHPzyKaTECnA06xowE9E3D8o6miLOYbMEBVawkzNiWNG7XaPdol3s45Ntz87Cd3HCiqeftSeFoOwExVG7eNeyXnhGipwT82gKVanHEH6jj3NGur6PGY9Rj1WPX4uAgWtBfuMjFnr0xZHjnFvGLxj7MxqGngWs46Zb7hX+twahI7NbpAfk337ha0AtaxiAnFwdh9Yab5FCIY/erCcwfDzySdHsk/OTJlGE6Dq8RuOvqfOa/3V95YNy+VE9yLbg/TqRPMicxGxTZ8KKEnyxTFFh05p19CTZz3nFsZOWDGbZRxGsevt1b345F6UGHhiS8iTdfKQ0cNhPfx2x3N1gpl0U2xyGtBbs8UzuejQ577lPTljOznbz608OXMDFZycu3dC2BgBw97hXbEjZurCZ3ZJ+zAJw56coPOv4rr8KJUZ9Kwnc2nj2Hd2mNx6gcLc804ZuuzdC/b674IXkZRkGYqMyQ6No3lLTTv9N2nSQiq/Z9qn66IRWfIAV4usG3aZ9ZqBayV27Td8XavoJH96I9NN+rekQt7XpzM8Ew4IQff5Xz8u17wGbCOiM3zDxeuLwg4Of0fC7dM7qFo4EE3C4/ezV3ZAGcR+HWJNC+L0lULO4KtotL3Jbt253NVm+l6p5+Hkqmi3VtBXysR33TgzwXtZWWyV63zquQf4+rs+KhXQsZUoz9r+FMlY0/aQmbJg5P6MBinJ0l6rf5hfsQdvj7efGjlPLHvf+96KnBs/t10TcwtfnVNlcTt4XtUN5C4+QNQhGVa53i+h+ACv+xRtwMrNAzFkrGXdz+qx/SwBQ3i17rLQsD2uTyX2fyW9+L6TtKWogtGLapdlLEO1lpWBygfU2Pp8F7xP8d3oPyY+7+WheF8ftqo80lO6LgcqEXm/4r/6jv+c0lpsC0JzHlRDg4+VoRCaHTXIe8dI/gpcZmhNuEJ4TYfrQLSIQxLxRLVW0qcBI+be+7xwC7oKD1GSyERHwyo/YvFT6kqXJKxNt35UkAp47YxnUVRSMsrsYPdE+tJn+WIKJWeTsTk/tkpYSNyIuk0SkHXw2CKazF67kjuhUIMxSBUfyuqxAgfm0k1BsiGAySCD81UAFRahrFGhcj1IxZvwPrG5qPSS8vvOjbkvVJduLjX77VEAcXfpWGmwbnV66ocMnxhOJNKbFveFpOtPb0gRMwSVhItK7ig8paFI05FXlJ9/+3In2l3J+u1vLoUjBvbCy5QJRPzMYYDCV4qsw2zc02tRK5gEGgpy3aNbyz2ZUzbe2HtAUR8ERiGf0i73iiXq4zlhWg1M5LMEkbp8bM7ppWZkN+k16jQ7Mr93T2H4y5sUO2G2ogM3EIxGfm0mdIw7pJ2m3IycoJ/IcgeQHojbhzTNqNeKf0Em9UUTQhKcU9bFzEK/HKF9Ah6QHjAX9/KxNsPMq9/+PCxki5msu4LnTwMpsYZMuQvdPTtM1uhEKxpfmpRkjCjvxsmHnrt3aFDloBL51T3N5Q+Fg4SudvM3krSgb9jxrn7bfnnmqmVYeesF5b9LJItfg2AzGOfMwLws20RFXHHeedMsRq9kp4xLbUIRn0P80F4Wa1zAvpwoT1XczRPw/gL1wGaC3cEsY4MVqkf9G1qHHoHu9OE9uDscI4SqtngAuj/ZFpl8VfFCz0jL5pmcI+oo4W1kaR9GfVl2Idb1HFwL2bHj1wUKpy9L+Snh82TL6U/pnMHCtmhqgxRwedfU5+6kV7dykz+QhlZq2W2QhSaD0YuoRNlnDgS92IUQPnqSVh6euiy/wFQ2GAXjdgt/ccbz8HHLegyo0RqU+rWRpEMoQLh7z7gkdcPyGMX4iZYTMuaBIZyeOzjiwQz4qQ31emEY7cs937iDvctKdqGXPiR3TfCSCy4+UMtplHtQe1BTgDu6bK0cQYWgGj9fFmKpITKYJdcNR2z+FqnsKByvZeZcPJCOfRt5Cvualy4iwWIBW4a72G+XNzEjS082JKq+RNQWnSPGU6+0hdMqcqQsnUBWxEJ+tLfEvIlwtUd18JUfNGrmF+3ImTL/hohc6HNXEmmw+woiVy5l1pVCszL3kJecDo6H8MBlEegJF0qxoYh7oFX/edpk556kPSsOltnDgIiOJsnAD9szIFdhghyjzlT86vkQZXJb1YV5MRR5tsD//ONvW5wvqun+KEcv98e+6WR4SRYQPT2GMYq0RBghkvlL957v+ywMPW+4C1nrnKz5bMR5sGjW4BzwQ3EZ8RWHPK8k/II74nxhju4WqHOOt27FjgBWGOcJ0ximH3JQqTbfOcHy8Xly61LSyDtM8X2yU6bMKRYyXlPaS01GvWOqZZjpLhF6V+iNuhhIQIbMxyzmLBVgpACP6gj31Bm7CLb6ihI9XvKpi3GIu14V1M2dwFcAi1Dx+dvVcL6jORDK4uTrhF6mYCTrFSz045Mn/+yPMB8lFiqb/ftwJSpUWW8Cvvb9twnGNVES9Tz648LG20vDVI/4RWuE81cb3RtI5GwqgnKp8mcJF+YqTpJOAl/ceWprF5IyzAkqJ/HjzwJ/vX/5iPyBqG+eGtuHouPMnp3b0509/NDcvj4omiYuQQBXTC4ZNDlwfcXssTEjQ0icVrljET4shp4WiIMiqudq7M/CQJfJS6H16cumI9zDbZTUz/uegJ2Jo5VS9xqQUJv70XKxc2ksiZMv38lKk91Mm+YI3lgWl930D1W3X4i6Jfk25ZSoERx/LunuCqPnc+4ZqqyuB7zmMg4Ca3Xw7HKChByHvvEpvPUKnQ5h6qPu5kNv6PgECs3Fys0D9RMtHxHjYTu97yMFHg4BUe5XdgXqA0qID4keA/RdD2cfvIo+A04ndUX3dn/CdW2lOm93efH/0jbI1eF097yI5tVoGZ+M4sdLOej0TnBtgy2C1fCNikVdmMKDK/tci9f3PM9WYClWeKjvHo2/0HJI0KKvMiGAn5Y8H0co0Mq7TsPjLndmdN34RWsg47rIzMT3F0gJUw1SW5YWdYgbHlOz6kfsVOdgWEObVrOYrGg5vm+d6sbEnMHdCkpTqPPkPET22b5mVnqu3Pn9UWP9xxdo6Hq73R10K3VHWKDV5z6062HOjNb7bHd5gV49D90j1VVpVAcEM88o+u3XwGMAsYD/MMTLS7j2asnBFKx5+DzMj7fCx7F7f9gUG0qyx5LLA9dWcg31YreXPX2Yr0Llpr2Nn+/r2sGmcR+tIpst2U5O9FhxVRyCOspzNzKcN/FDlc6MjuqJi+Hbq8U+fxxlYlXdXXemK/2hiEa2J5e6zHzIi4NTsM4zgsScsYq5Tm8KGKY0v698ixMsok4nqAlAEVIzqsEd0wGtTYy35Nbg5zQIPKS+yonC8fvdniTwUadTuY+/pCwWVdFWAAAs/9OX9zxzGm40WPnGkTZH0klOlk72Byrxg91rJLN0BmJRG3wDRH3M3w02m8uBu8hfVg3ag1nXNUQtxQv8DhaHyhrjRm0bQDhXJ3zFoLHaM8GMrhnbAl8r64fYx7vo2Lwh4hySJstrIP4t4NfxrmLk3k1F6djr2En97PPvbQF0MgHX+hqP+3fJJ+fI0kVqt1SnQkWHWTiKu3YEapVo7qdBakrOqCsRQ5ads4QvQ7FqafZqGpNytOEPWNdLHGFF1epXq6uv5/mKQ2THpR9c7thsLX3BIOmSR7IE4QLPXSd0tLAyp7uQspG0I+lVOE15tg+RbzlBCunZR4zltNgm5m5h/lmJylK26dMlXTASWub4MM/yFibQb0F28aA3/rYnx2uMsGH291AJaYDpffQOdVaivJXblYW7QVeG0BjIqKvWQ0rPkZu6xWC1RLjOFGUQyHKCFByU8NOV5KC+7ghlv/5CndZhnKa3xfYn5Dq6voAwVN1WrL4AOamzc+9dBH0ncmGsN+OxTKe4jH3hqlTOb9PX+ClYMn+oaCDJzY2s8nJ7HfWnBa7wJik8XZ3JzSUmhh6REjmiCcqsxUIEz2i5zAzNX3yMgycEH9D8rHG3K10/N0mtyEsFN3DlXIgFlO/rahRUEdkWaFe3/7CYUF0CZ3tAAxLAPjwMjy1J3ugEGc8khJxfuntgp6RUl787zuZKKwvXyfrZc2R0T4PNvjtuf0X2/9KXfxYWTmS/u/fkk3C18MxYzTd7N/miKHBaujGJb1+/0oa47CVc6c/pJCumrNuoPTeCU04XIn8ixiChaQ9ly+3Rsfk87TOLpHxX37AkUU9/v9IfhpYwOOz0DYzybgZ+mPPdkhLZ8pdM9IvPgaAUhNkIr1frce8rhWc+x+7BYLhNO6UP97qHmkTSjyBe8sdNGH+jPFX7BgOk+fM4dJ/xQ4xYTP1Tkdmzl+CGnDr6RYsZ/ehDwc7fAYA57vJtjNUba20rnlNC6987/kIeX5W4VRX3cEQUn42wKYa7PxfKqHLfH/WAlcaEO8pi/euhFqP1vnwhXjekfLLlFGMwYQwng6ZsEQol+Illtsx8a4jrsTgytwlAuna8abZu/WOr/CeJgDUYOBga2Mb+jgQYapjtE87kNVsRVFemxiPHr2gZ5bvxDGz0nu/vqnBY45dgKgK6FB+SKxMKzWGLzgL2muVCQk7Yz0flPJlb0aEOQY8N5A64m0PxXbj71ucGpNOZTsiV4bBwg/EbJIetBBstjP6RIUWZkIFzFvW8cRMYfJg4tgBsmF/5CtjdoTD40/iD7A/iUO4fGOnZqE+sjZewW9/CRYX2fj2LnRvQyuSiuth8CX/3g0KURZTHjSyivgTC1u37+zlOuZOnG9W8+nn8VEDssU7RP1yDONwb1kMYfTJBMikXbl7QbiTEmcOYDiO+OGAPrhGWYMSICrUIMySooxo/F9sebj+HudQQZkC22DwZSDb/LfHClKq1Rwku2iWPxlOlLaJyFxz/dlVA0wj5TBUFGjaH8BhzZbGRuO5k5YS3r/3hUITYGHf2PqUQo9j8zfkZHC+57+n+JAIMY8BCV2O27ZLog+3+gmP3UYAQ6eb9BUxwPiD1jcbiCeyLr13GyrMSLUmk+NJE3ignMTk4FO78tFlpeWJx4rNhjiqGg0D0kJ3KLlb8EWk3lihHO5r116t3sKdCGNeNb+Jhl2GvYO8+bHIH3MM8w4TBucCtw985SQPErGzXXK7gXD53wLCHNPPxZ3mFayr5l/SPVumkjdFqd8WNSg82HTUORFU1TKa6HrSdsFkcKRAJPAhtTD2endw2ug73fbop6jSvXUO0ehdkX1wndJo3duOhg9zsQLhJLBo30eQ6bw8gWnGqcx1LQI5G7oUTPMvci8bszo6P/X60V+Koh8cCkj8N4Lca5OgpqaT5XKSns2EgZiknEs97pvTwTXAw+Daw/tqWlbD05zLSgxNnUc1E98JSnm3pZW/SOeg2SLAlKUushFZ+RRfJWgB3ax2yEDSZ1tt5rBD+QjwO/2B+CIqxO19/dLh8pe1ex70NGuvguY9ZBCn8fDSwjkO2YB2DOy9mg9Qg6aBMfj6RrVHfm1EclkhkxoaiiqZoiD5EvMEKs/aNn313LBiNMJhLJ0yjf08NobT2hsK1JTNZrAwhyHGovbE=
*/