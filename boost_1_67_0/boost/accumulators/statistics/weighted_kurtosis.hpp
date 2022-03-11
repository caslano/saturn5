///////////////////////////////////////////////////////////////////////////////
// weighted_kurtosis.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_KURTOSIS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_KURTOSIS_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/weighted_moment.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_kurtosis_impl
    /**
        @brief Kurtosis estimation for weighted samples

        The kurtosis of a sample distribution is defined as the ratio of the 4th central moment and the square of the 2nd central
        moment (the variance) of the samples, minus 3. The term \f$ -3 \f$ is added in order to ensure that the normal distribution
        has zero kurtosis. The kurtosis can also be expressed by the simple moments:

        \f[
            \hat{g}_2 =
                \frac
                {\widehat{m}_n^{(4)}-4\widehat{m}_n^{(3)}\hat{\mu}_n+6\widehat{m}_n^{(2)}\hat{\mu}_n^2-3\hat{\mu}_n^4}
                {\left(\widehat{m}_n^{(2)} - \hat{\mu}_n^{2}\right)^2} - 3,
        \f]

        where \f$ \widehat{m}_n^{(i)} \f$ are the \f$ i \f$-th moment and \f$ \hat{\mu}_n \f$ the mean (first moment) of the
        \f$ n \f$ samples.

        The kurtosis estimator for weighted samples is formally identical to the estimator for unweighted samples, except that
        the weighted counterparts of all measures it depends on are to be taken.
    */
    template<typename Sample, typename Weight>
    struct weighted_kurtosis_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, weighted_sample>::result_type result_type;

        weighted_kurtosis_impl(dont_care)
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::weighted_moment<4>(args)
                        - 4. * accumulators::weighted_moment<3>(args) * weighted_mean(args)
                        + 6. * accumulators::weighted_moment<2>(args) * weighted_mean(args) * weighted_mean(args)
                        - 3. * weighted_mean(args) * weighted_mean(args) * weighted_mean(args) * weighted_mean(args)
                      , ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                        * ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                   ) - 3.;
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_kurtosis
//
namespace tag
{
    struct weighted_kurtosis
      : depends_on<weighted_mean, weighted_moment<2>, weighted_moment<3>, weighted_moment<4> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_kurtosis_impl<mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_kurtosis
//
namespace extract
{
    extractor<tag::weighted_kurtosis> const weighted_kurtosis = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_kurtosis)
}

using extract::weighted_kurtosis;

}} // namespace boost::accumulators

#endif

/* weighted_kurtosis.hpp
PyX2aWJN2mSnKMKCS7LgUKr6DJqLzkY/fZZdezoyafgRV/jQRW6JRXiJRW6JRLywRW4xfgufBk7Mw0RAQDaEYuBLnUUiRCiWGccVzBXNFcgVyRWKO48VWe5Em0KfSYAMMwn5FXNUweyVGpxxchd4BCp2+NVkcPJzcAtyXatnS12XtSYJI4glEVLp4eRow7IYO58KfgJhCBObuCJn0xa1cecNJUzhphmxBTNXD5OIDOoq+ioXDASQMlYZFT8BVfTm+ckkpAw3Ogua19vgvhVaMgONNFrimDfhWatlQy+nxPbKINDDdv37VngM4YZeuEdRtfVjZK+Kiz83VDh270jsSq2ZqDIr0h+FL4qwTw8vhNvLlSJlkvvRzYlAhEIr5H+AGF+k0nreGnHLjCgV8uT1DgfkZLTyQUByqqMfAIf8g4H1CvMHKXk92Mk8SENvZAoSjzxn7q1rMb1PWZA/hOmmQ0WfPJ66BzpkggGhSBxVJoo0CVuYmmFBUatp5SwqZLIHqSSEQB6Bk/8VxYrz8G8h3nl4R5hAGmVOynNMYiKIA116mlB6OpO4Jv4sPKZQ0voZvyEFTepzNIVmd3+MHQLh5h7k4xGXk+7Ago91L/qylQygmFmXhxENTccy0uLSrhdfEL5JcXultRhg4QFTjPVhqLoRmbBCvU9b8gfAxBrRfa+gCE0D2hH9BCFvNLcZ9H5AbND8CbKtlHskjkfUAJD1gIH4EjvOK6qgva7tYuJkTrZ8RpsQKTH5qM2PdFRsb/jMqHgpI0IL9chSGFBPinrEBoYelgGI6JWDzfWFDFxcFbY7zm3kspQnXdLm+wGELrTLX8r8NUrA9bLgc+WhehZXDeyOq0F5tLvKbcCqGqDa5rCFbBDczWL83b7CgiLAd4Ou8jCwKmLoNk/cPmL4G/5+Mocmrmd8/TWHgSmNTRsMth5RRlXQ7e34ZxeWY/Plwntfchs1ghb1kDy92MP/QbWrgq75hbq9/4UURLWigXcoxMT2YgmayRM+NCbps0XwjBFD5aXa3s/MbXQKLBv5+KHRxdrEQ06tHw3vojY7Wsg0AgR3Q+jXaZQ9aZTKdhXcFws5Zte6nxzL/GWhdGmXikQYsVzLwmXFJ1VJR4t0iMFSJbs20Ow9IH+XFE6VHNtAc/aA1P1TMv7wZNDNY72V70SX+JoxzjtVsuMzxdLP5GAdYrJUycENNMc/J2c20Fw9gnWJDf6cFNMhRkuV7NtAc/hzcmoDzcVDTJdY6Y9JudOjrY3mpKUi+lT4JtWxohNd2nVlg9TIpqTPvYcnR618d4wonX9O0qeG8Y7cH3Bdtq4tHMY6df4OwcIq2FJX04ik3eIZb/46O+0M56Zz+81hXyGEsHtAfo151fzrwtu315Ss5djJw2+1mFmTM+C3wZFJLygk4ojWV6xHZhQKuZuMZnPgqZ6/yiJNVlcbUSqn/Wy5laKRalkfVU6YD+3Rerge+8qPVvVNlyKY/XvQqW90ez/jK3giExILtobfG2cVrVqKy/zVbCVD80rCNWcmg2kkg4uAnZimbxj0QJBmgqUWhWKmRY2OgKc1OCYSis0x1YNTU92NzTEjgwCDw4/NMdYDDV0d8KrFyOJASzp9wsjWboeSMY2It61go03UVdo0tCT4tGMRXV5CRQGucbWYUvLj2dcN84BGRqqCiBKxlg05mYdss8LYokLXKRk+Z9olC5xNXude1Y75hFBKyeJj7hKkq0xRTqmNklkOam7yMqzWpIwSHJKU05WbjdWpEeO3X/dWX5Clmphimsm006t875dM9JwdL9TLpDl//6IMh0T8u4nf6GQYsW+jY+pUaIsytVvZOKPahgD/zdGkWpg2J8/pl3IWVgmzT/m0KtgFcc+j3hZ8NHQupn/LYgK8oX5fyhNJT6iSPnddwfOCp1m+QLkZebbrowvBeO73cOPveGEeoHvI0XFy4f3bNhqbfNkvzftp7k09Lb3rfb1y5bwv5PkWPrX0VmS6G9Ptxlpv9PVWvONd+BQhWff+IFxd3qGM0pauhLDS/uPKOJCSnSel8GLfpnNaH1NSJ5oLq+Z8TT6cxE3krgljdSALVfAg+MqBqi+Ol8x3Ae74dyy/tsGIG5guJvh1qNshWs1wjGgsJPcDzFk3vh0+3hgv2aZUrP72d9QHuuIOh7SRXmpKC+WRq3pqmJeDhlfeiDlxK8TqiJfV9nG04V6qwgsF8KvEaqiXuYFNMFj0Yr5NOBtxhd9rJrzMmjgx6OUH3jpoYp18IBSJoMAISzXNCwZvn4cptvQa2YVgZacWvi4LTayOw5tiGHK0uEVMD+jHTlabfsvB3/q2Er/3+trQQVpOPKKhyXg8oZkSQZ4h3go7SVWV3tLdHXBBU8aYFjHuGf1hzdYA1g1B1ADRIcSBn+hCgq+nyRLZi4LYQIcgrN2hipnRoncRVQMXp3LlNSdGaonB4QlbNN14tRsl/odk8xkCIVgvCFgDOwBZtNVUtVsM/kWlUu8iQAQXQtPAjpRuD8k4pD3gHTP0+55FIfUZgkF4LxAD8QexmvM11gWIgZsG7yW6aVBFHNLuidn9Ru3ZKMHU6Cn0+Wlbf40dxeJL6T4Cugh3I0q0vfNwTnX04w8y5CAi5DnZakyyWFtNwhOx+9dcdu+eBUZi/ZzriZjrKt5GVhHOWYh1HFpHXuqGVrUornhIvggrBVlPh35qmo8sDt+eVkoTT273/Lvos4NhsV20Y2gT8lJ4NLvXLJFExOfQNAUzFUqHr2MMt8TbRTkidTHPkWepXcWmCN7G5jcVLDoQ9jsQnseuUcvwfCcaUMLUnaJroY5k/E70RumwK9oTxhQzBP8ceajU7ZVEOwRr5GosiDTFy1ywGIDXHxv+G4Qx0pNiSKmqPu4p2msrbTw1nPEAHprHeEhaDfFqGTXF4fdmR3uEGQzxIhotGuD2CsT+BlmM+xURbQ//DRIT4SGaArQbZNlE0vygmGqopxu5MhNNVIMV0YJ5+l15qFwWWMXY/xPDw4Vm80sR7j+obS2Yor9Q32ikGpb+QgUVJHsrl6dhA99uqbKtliFSBx2iR6G/zX7yFIXPqW1/qRSpcsXyrC9HrS8fK9cN0dunPbPUILPUyNNohW//KcPUL3meMpT+kucpgxIoj5NInps89dkIXEipW8iiTazIIYdknltGAaqcXt60LM2ZJ02IHlMRKlbTGG8cZn46tudWvIjqB5EqFmzP5Jqx8uiQ0uiQRbxi1H2lvOkq6rMbrBBJ6/6CT1geapWD5Yriei40J/JU4jMb4os7hbC8DYO8WZgGl1geJYnke4XkVXDUPZXUJ+n+5Jju8W6xNCI12B79WsGGDCeR9bAbquvJKmjIw+SHY/QnP0VP/GFvwhAcQT5JKniVsFbAGlwyV+xEk9tI7NrLaK+tPa7YpiaNwSZDhBUZBkwFjSgYKfsi7J5kLVgNSzK+WuweVqt/F8l0YldGiey4oGVrImA9PQBkdNnKuA+79Vh1YOidZnUhv/gNgpZ4FPsm2K3vWRvF83hbVVqul2+y6yLbJGqpTdgcDAgcLzVEDh5kBmM+hi7cJysyu5SOpAHevi03HX5ruZpFy8zUz+myjG1f01Fd2GBsm9O/UZbMb0yJfGgdwso51ZNGYLkyhFRvvxmqxeUkyrD3TZFuaHRGsRdRIULR9Ansf4CUaUS4NrgXzUxJZUsdMoYB1YrFe8FTIj6jj3GSHHdo0R5izJto3W8kIY2I/wqRloSMRDUaogwE4vAx7MaR60ebXxUMMkXeMfesDMCGkcT5XhcMolAQ+0a7XwFXVwbCwwTTN8OAxNH+V0Dw1TiyTtyTqL8IesMjSSiofaNzr4CBqwMqHb58G7u/RLBRJBT0vtHVV5No2Hz7uwOTHQ89bILegj+lfX8mka/rB99FvfZDO2ESeRAf7IS9xiF7JF+PSxkHAYnCqz7azFibopNx5Zt/C1E1/ObA+/6ZbMMkmGzwizWaV4I/R8QBZ2toUn7g11SvnwLlu4opmDD/+3CGPrA+4b6f3kxRhE+e96PikDOKEIIUGS6F1ZVaUIg++8vfR+43Cydhw8eLVTmWfHD0AQzdp1XYvkuvVi6RfkTNLxE67aqPWqEROq3+afSZVgwJnjBPGNt369WKG/JfR9m99UeElSFb9hV3Zz7WTBJX9HfEXT2HYD9FAPo75Kfonbc1ji8KqHkAdvZp/VFmVciWNwPfltUKtz7C6LWW+8h0j1PH71khr/1gr8OeAqPCCXiKR+YTlKdgYLJbHfd6beUVXfRd76Dg7wMSM2yEvw10REEf8D70gGCmOYQ15u8AlugDbk61/WbNvwVmV7uVIaN/C1jF1yu3q3/JfGG0gvgLMMaEtLJhH0y8bJL9DbJ9qg3C8w7tQLASbZLHZLeCaPI3AQuHs+8GVQRvx16CJyE+1nOCjMCsUPRnVN5H4fiyIZj1OzLJhi8XBdFHKa/di5QY4ymij6W8jkkn8dF1jbaH7eYS38ajWwrwXCTjTtoaD+raRHcEBqXCWCZWop2fUWRV8iYpTY//hOzbaHOtXdtLzPfgnYewfkcwqxvW5khQcntWcDCo9EmSZWKxpf0yH1QT6/dY0yki/k+niy2TLHBmZxpcBZ09ePdYI9tV9hJ+oKLwRJREn6TCWCd+6kRtWlusq2BC/EWH27O1a6kPp/HRDeIs36OM64a9mNKV3NgKDp66WcB3WMH77UBKwk+c5YYuYVw/Pvoh0vhM41lB5ZjSRF608y+jFCAYKeX1Trr9qdcV89ocp/wsHiQVbRrF49FbBXijkqzZcaZ1DOnjDc6g0T9Emp5psBV05oO6OLxdZS6hm1fwj2m8+Lrvw5Gp5HZFfdmLtyMlMafd2GgNGrGUxLf4gqQ448J2F69Dk0/Up+0s8+gu94mASlWIJhGkZXh2f7opQKUihMfOCbAvJDwKdQANh0L+WglMJw3a3gS/K9kCoFH8G6SzEWX58gLsblHAf3ccUCkJ0USMtOzJ9hvkMh1MJxXanh+/69wcMF0AphP3G+RuBFRuFFApCNH0gLh8w/p7ZGkW5oj3FuBrRtJ1uAdxleUD6KxFWXa7+FHsD0xdy3/B/G1Jdv+lZugj3mmA7xZ+16EORNMI0jIPp//uAqDS6W8jsSCEw38XNFUY4E3ysMs8ZP67wb9HDtAg7eNIURWmo/Z7+AMBEj3gTZWwyy3k/ruRgEq6v0JeEzf+kfpqnc4/vgog0QGOew3/O+TZRGdrgFmXfSYM0Be9j0sS9ZY3/J6o7wHZ0A+mpjNoZkl475D0wu0P5Dw2Qb6CUBChSQJ1DV842goSWIkm5gObL/CU+JWqpB+IOw1rqEOBG8uZWV/Y0paf7/317K3W7WNwn7c1ygfuQNwtWMNMinCHWNLfI5yBuEuwht4U4ccxvyK40o+LkF+jjqNIP9AF4lbBGvKRhx+Hk36gCMSNgzW8Iws/DiP9QBKI6/fXCE4grj6oGhASQvoBJTBk52RGIJoEEuiL2ncljLoGI/wrQjEtHK0DA8xG7Rt0QV2DF46mAw0Mta9JpLqUq/7auIjBnDn7wwx4Ha7wHwH1bwPsv4doHxjgRYxgAwyunxIEf6R3tM9WgVl8XLa4gCf29bbmOgjJSa1E8SuD4Ee8OxboupIl2zZYLwiLj4tv845e3zB6xkQiKSIQG/wPREIgNvoXhMLjGvfj54H4xDgKKhJJ5AdawlfrURTUJJKKArG53oTC11yBJw6QK1UfN0A3mETHE3pILZjysJFCKtEXtKPSlV23lIhMSEl0XLhfddiT7awkwfOG0e70HKfkBq+apCaEy58rnIvEAdYB1wHS4adfo8j7HPr6wzFo9iQffNcP/33wv/Xm/O403k/gZFTy4XpQkOR6i+LR+6+JJCIPZH8rkHgw+FtB9w35S33I3ahXPmjvmALPxas7YL/i/CBiLlFFHmL0X0as3ood++RfCSitk4g//BzkvF96gJwr/9cgptfy8NMCqBymCnkl/xFuk/4IXn8Lqifuju7HiCn/L8DDsz/C4j+BkWdjHc9OJs8Nb8ezn439vwHyQabAu1+Dv+wIuYXvVYe5Hfq/BQsvjH8sF4noA/DvBPrhdwjxfmQnTGIPIYOdqNfY5Esi69rh3gjxdmQnDGIdIYONP4jk69rB3r/+NtMIe41N9hfED/F2hL8E+oTX/b8JFAiv++IVgCc0EgL9gyW415hrt1hGndgUS4br2tHeUfF2wBMGiY7+q+xffsqBPJEl7XwKciBPpP8QLCuYFp1hMz8EmsjYga0p2BedYdqDTgDgA6YGva7C95JGkSsMneuyB9lc/SyhTp4AX/Zlf+5akIJQsFCzEdeUQyJekr5P8NAj46D1edctQ3LabeOBWK4VcHYMt7AYV9R4iba2Ot3TXxUSpY+A04nN6Mugc6eFi1x7RPomJMqAzgeVPmD+Dm5hU2GZQzA7oR59JhYydI05GrvLSAqMLxTzzxFiJ9TRGyVSQaLN3tuZHQfn0NVtxP5xvMgCVkxJM+rYEUXCrDwuHtHjNmd+pb7fmDQ0Fj8xfldioF+bEMfOwTl2dZuwf5w7ssAJU3ILVInSE1WnrX9cM7KgFlQvTeyIMmFWERePrINzyuo2/f8VxlWGtX+84F9kiGrkYlxc3ebrH/eILDgF9QhURoUwq+SJ2uQeVcCKJWlGGzuiSphVxsWj4uBcvLr9on88LXJtlSFWXu3HgCp/ZEzEehpgVgUXj7aDc8PqtnX/+CyoEVBxutgR9V8ZOznTfcsasEH6ZIi+IcxXWD2v1GCDNPLORiNXG17CNvaLNDFg99jUvBa8DwD6kvuv8Sc96JLS+dgzqEaT6GJ6CfrRf1Cgi2zPUX/GzLpyH035dDtcsWLbo9z943nyeA3x7strkacbwS++fuxB/CvXREoYcqFf1kxPjnzNUYkC/eVWNrjHDkkNGO2eMlpqZCT6bRi0uMt1QgL83YZ6Jv6JfUfPI+Qzpi+U/sc4vsd+bl05aTVHZqaANb6UsNOXxA+qxp+mNB/ORp6l3wFAMFJwfCb9YqG71h5mtIeIj+51R5wKxMGyZlOQ2QpydsixGV17UBiVPMQVlg9AIRv6aN3iKUK3iFaBkOcOEONZjDpeFeMhTnvot4gWNXzGT0Kxc40rjbJR5AeGo4Y/j9bjGlxNRGYtCVtSrOjr0NJoz/Q886Hmnf/tmhLY5UCBP7wRTWcGhpwK2qX0ggZciZ8x3fKDvWrX/Qp17knN1IpXJba4DkNPe4p9x63O1AaRy25csfZhA7fnG0dtErnGB3v5lvMDFAmwZFufmWG4p98qJirimrjDPpOMyDYubqwpTBM7OU3YMDk7TbjgNHPbfju4OrmddBmY5N7JCYdvEkSDUm25MOSkevrxJjnlRc+wgzahPWXQ7cbK2AqhBkul2lGBFw5ycwVcUwVKU8VAPCjNgNSyERR2Wn1OlqowZuMzZsN/EBUmaksQaLur63OxVaJ9+HXZMvu2VwnsboWaeuOr70sU5EsXX1A/23vtvK5iRHa+to4Sbfo0PSi2nNtmoKgYNJ6vOO/qtsO1VqCAAFTBd2XPvlAdXfiS+YPvcn02XiB4xn+9uh4TH8klQbuKWxZuVEge+19ABNZwr6ON1kFIFJcE4+rOxa9p3Obw/zxEL/wOGIg2ACtBSIHrEP2q718iTCJx4I8ZlW3UnsQ7j7tkkdmSmJ/Fx0+p++5EhphebJXwJRhOo2sfZJo2O6UnPwDFckUYXa4iwmWLJJt+oHeMJs1Jnym+n9ibcXzOmn1X+iO91eDP2wg1IRgKm7ShDJYK36LaIRui82PTOXpc6RL7poYtbay4eVwFzZoPxN5JsGSttPRhZ0e+t0euPlJNCinJp+fDMsk7b/wVWSmjRlAQ13Sn/dSjoqR+o4qZ/Rxu2SJBiMvnO+l+xsoifyhK4PZnqPFUhHwmHDF95EdR3q4mmJjP4Xdn7/GNrI7JCfFwjaKMohligQ1cH2ZWQQiVPWTh1cuHqVuAvAWP76MF1oqflEbwI5ku2kOYs/gVyQRWyMTGCVoYahiaJKok2gAqDrn8Pb2XEu4unBG/wTsqkxUjAz/8Hyxlrvo7mL3vcs/sWNO6Wm22J1i2Ygbc3d7D+B8f7Ho1fJ4daj1x3b3dwrReJeJkszVljz7fFBCR1t/6HmSF1RUE0AZ7xpLVGHZn3ZQNVY25LOxfAbADDAZ3fenYhSgFb4J6FecT1rhmM33r+N5I14POvQHLoJDMTvgC7BkY18cAK33/ccAkGCNEE5SQ66dZbjWAGZg11FV3s0qX9rtOFoCNXc2DIYzNGw0D7o8Jqo5zEfKOvccqyu7rM5ixKHJYu6m00MQJQbeYxfbTejQLTbX1Ux88U86N33HbITPNEuJ3oFYm8cviK8s4DlouRk9BMDMayYPZteWp4OymVOiQJ7HKS9N8lBb4uHPzTkL9hZl0Qxzbc+49rwvd78i3tqJBEl8Zagz2ME5Iu9QBIwIBnSS1cR81reMYnJqQn0ZG17ULuAUYN8A8HIR2ts4wTrz2EbsBRwR/g2yP0KXu7wOAv4WtnLWmmpLILJdDAX9lTaVTO4vsXkFkbzMoAPld9IKMbX//fKW0fpbM80KcvIQVnWGOdLypuT6ivf5h9CBXSTe3RLiAeINoUAh9meir28WW9SrDNAr16GyfwLfl3bRanpSBRbJzAKLWCbK9b9gV4ANgCPASlhTinFHxMKEIkArxDroUBsAQZMXhH9eOeETb1foMJRfwCtH/0+JLFGuOmulpN5qhCHaz+RmEQiipO/aL/CB9k1HeK6yLzCB98AXio8971+f7TlJD/reQ2R+hM5GamBZw9sqQsvC3nhnFzKi/1kXWuQUNGBeJmWiZBZBmY0L0NXWTLVSGmJKpHFKmkkqf94rRMUMGfnMD05kGHOpsNpXxPhYCnrHxynanB77lXRtxwkXR5yINcBP9lsxGcOrbiY2p2oD3TLq02GAgUtIIxKcO5zQeIhDD5Awyd/l9RIVnocp05tH29RSO1SB2UNLPgBHB0PCYIEjZasNZeTgO8cxVVHj0gN8xxTZPlqRAdmC8qHG8yMR5J815Z9Z5B9By9qyljkp3LoXRRiEVe6wobgI23JCGYcZdjEVrLIHRJ42xPYexIk+2dawoa2dC3rksLhSBo2bhXBQCmdZ1LPQN/zaAhBP1nYJoCgI=
*/