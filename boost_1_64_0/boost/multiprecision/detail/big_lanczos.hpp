
//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_BIG_LANCZOS
#define BOOST_MP_BIG_LANCZOS

#include <boost/math/bindings/detail/big_lanczos.hpp>

namespace boost {
namespace math {

namespace lanczos {

template <class T, class Policy>
struct lanczos;

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
struct lanczos<multiprecision::number<Backend, ExpressionTemplates>, Policy>
{
   typedef typename boost::math::policies::precision<multiprecision::number<Backend, ExpressionTemplates>, Policy>::type precision_type;
   typedef typename mpl::if_c<
       precision_type::value && (precision_type::value <= 73),
       lanczos13UDT,
       typename mpl::if_c<
           precision_type::value && (precision_type::value <= 122),
           lanczos22UDT,
           undefined_lanczos>::type>::type type;
};

}

}} // namespace boost::math::lanczos

#endif

/* big_lanczos.hpp
w1nuEz34UGCMzRzjQIdqwWNn2PGNeT+G9Cz2zqJtdStb6+rADg6XoZLXB72lbXs/bVsUyakC9D2/dRvaNmDuUIyOtubSezyCJSeTATPo0Mdn5D176xUPHSJom740o/On003tnWXUl5Zivk8xtTLC6doih96hgmB+TvXGeyO0MmM/qhTRsJg/f6cYIRsvdOcZseAXmPM3yXgFXUmjosakVm9D/Rwxj7tJ52lyXBBtNWIw9MyIeTbFNJWMVV2FsW04t0fMC3NMTPGvYqdUy8Zj8/XJuT/epN8ZjVFd60MO6i2MNB7HVoGDgWttZyMrH6b0uGEu3M5xjnllZVe5YSjQZRL7dFdOH1gtKlXZ1g6A/oummAcUY0VXGW26AdOfTuk43CH94TDgjXFdaFjxaGaJGtfTT+W45zdNXRnVWJZOGbZv1vWh71+ifU8pxHgtFrS5Sq8P9N+m9JWSjY4ysPTZ2rvKkD78vpBJZYQRQtl+vS6XNMSdu0X7LpRXXeUrVuzvpY4+Lsd5JmLl2yqpzuC6ZUf/WswJl2Mca7nksB5qNhyp+DGNZffCnH6ta9tQWcdxWk/8AQ3pi2ROcdhDsuVp6krIcW2/RXWt474zVcvIO5j+Gwa/t4uxCyEG3bl6sbj3LJP7YHkH9q4cF2HshHQ8MGoELHI2vj/HPL/l3AljWrZ8rdfrzkD7QUIrnTIdF5z1r/Mo7Z2c9gWVVLyJMbD+NR6Vx0ep/JrQCmmg3+MbNZqf70uk7shtK1qvWcrCCZs51d9vFmPZJH8W4RwrHtANYznknNt+XcLRE9mQcy7RvAvu+T/X0+DJqCfI8+Q9+/U9DR6QkQbrOexpxt0eibCeH/Y04647pXnSG5AGd8GeCmm2kAZ3I6zoCT3NHUpjJXwmLnLt9eU/x3JclGmb+zG8uIF042KX1fVq6PtdPQ1ZFPIx6unO3SBtyjMb4jjehTSo7ljVE/o2/X5Jg5rVl2Pf3CaWj8pB2tO/P7k76GHBq8xZJ+8xpclz1n1qVXlvT0J71FmgITpG8wXeVZYX+QL/XpajzQxjj2A5yqjIF/i1lTQ0XyC71wqanhe++8lorjnsCvp8nb83LQcWiH1nUVaO0w/7cpxnxTiZc2U5HadPleVF2x91HyyHQozZO8phUg4McjlMytEfDn0NvkTmN63/a5NyWv8L71eWU1+k92P5uDaU+nru/JQm19d3TssHESPNjynNmH0y4xPvP6UZ8ytB2bQ8scHyCw8g5ZM58Z6yvJD12QfS8nJOvAHLcY2c9OGbUxrSB/mgaTlwGfMqYjmuoahTGO/kwSUN6hXSvGclDZX9r3sauqbROf6Gh6yioXP8+ytp6NhdfSjS4L5Z6tmdFTS5nj3pYdPyUs/e2dPQfYP26dcraWifth++iob26WsLmmSFBjryujibv4/IaPAFfuY7RcvHNTKr4/iRGQ2+zsdyUAgsH9eprPzdWJ6vM9ka9mgsJ6+nUSexnM7xvA2XH4M0+fwc5+603Mp87j8Wy/O5Ma4fWF7q9NjOw8chDdXFbLzPPB5p6AvyfO4gTSH/jOZJTwCaRUyC02X/QUIzlf3jnojlp8r+A4RmKvtHPYmUT2T/XlI+lf2DnkzLS9m/G8tPl/35p1CaUvbvJuVT2Z97Ki0vZX8Xlp8u+3MXkOZU2d+FNKfL/tzTkKaUPdpnLr4ut89EZirl66aT/7N9BqJULN6Aw9nywrNgrXlbshnBBfHrNw4Ps993h99vp4Jlru9nwO+PejXwT78fgEvI/AhzeD8Lyh70Wlr2+ttHs5upHPy0nwPlc/BsghKwOB3uzhauTMmEtSx/Xlm+WDfH8heswO8dpvLxrHYBbEhfPhM=
*/