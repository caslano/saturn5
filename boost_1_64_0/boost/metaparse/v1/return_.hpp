#ifndef BOOST_METAPARSE_V1_RETURN__HPP
#define BOOST_METAPARSE_V1_RETURN__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>


#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct return_
      {
        typedef return_ type;
        
        template <class S, class Pos>
        struct apply : accept<C, S, Pos> {};
      };
    }
  }
}

#endif


/* return_.hpp
h9h6DuJ5NZav+HJjg7ly7kGMvUGsyZYWiO+dFbn+EAvqtA+4hR88pKzi27BIrDm6Jmhfm/1x3/oQzNMvEczHyQ18DGLQS6KtqYm5fdfI/Fhc4Gt+lhq9KEQb6H/C17SbGZdoM92494CXMR8Cl/EtHyvqtN/vOTFvAq8UOM8VxeN8BrLLBCy7+/R343Z3nYq/E9DcLubkw+tcGZoAM9190kbn0xwU2lesGVw7imiPKe+W0T2wNav39Xkce3qgrSvD8ZxIxi4OhYtWnU3XBr1t6b7Wrrb2tNonTRL5jkIU2+kIYYOnBM0tc1uXHrJgVfYJBpkR2mO5BzkDb/601vG3otP0W7J4G07reTvGUKqOv8cdXsJr+zTlWxqr6zSNNaCxVq/hCHfoe1afQ5mjUeZ57kuOHY409aXbe4SZ7AdA5wAuULvwZRkn5tujiG6+WGu1UbooGOyjKTO7duigvBK3/mrrCst0UjpBfgN99M0VNKhPUy4i+mBfINdn7eFdPhtDflJA99d8bpjXReWnOD5TFAwbcRPHkcC6uZ/demJ9XyvhYLrNpob0e6o/tKW1Ob2+N9Xm/HmcY0z92t7OVHYPPBSc19q9oq97xT5uXZ0+0+hHP/fVeR0bQJ9lgHfgkPy1hHcxXd3MlcxlXtabOjfUmTgOqPMY4K0YRiapzr5OGuALelL9x/SRj8ghvIEdBoHXqJuEXDYJuRxneDwePB4LuZwAHk8EXsP2eTSisQDm6Yum7pOMfE5G3acwHpVh3k+r4++xp5ux/KU69zO+9qB3pqC3XtD7suHnbJTfAFmcg/LnCju0TvBwvuHhgjr3M/70oPEVQePLgsbFhsYldfQzNC4FjcsEjeMEjcsNjSvq6GdoXAkaV5k295k+uAZ4X5O215T5BsqcBDldizLfNHjHGtqbgXe94hdzvvV9rxvim/UI5pLwe445x/l7GdtvtuN6fr9ZrKO+XefKaJ5u4TWwWZ+qv7GG0Gvg7/G60JS15fS68D+sXQl8nEUV/1KXUjBI0qY0timEtkk2aZq0pRSoWEjTlFJ60YNTCZtk2wZykd3QlksERKzIrSIIAooHAiJyHwoICooop6DI7YWK3Icc+ma+/7fvyLfbLciP/TUz782b9968eXN8M2+uhw5Xj9XfSSfWyDTeAgfPcg/k5hrxjrhpj1tZXpz3wrwTZW+v0fPQrcoxtwFu3F2dO2oEjqULnLvEemBKDa8h7Jrj7mFrkxDf4v2CZSS43s+819A4Ng+NXzHf4XopwTiE7/m+n/VFOBZOZ+wFHyeb76m/i+gLPrJmX/Yh9A8qq+Yej9Q4W1XrPsIJ+X408plYq2AfsIB96rj0j6P8CWPFuiPB3zDRfwy9+PnxkzV6jz+BNzj8GUT0y6ddfSeJOXJN+LPfE55FO35jdMjL0ZE+EzpdXqbTXx7LaWkHd+MsanWNhp9j8CdIONra8WDPhf6jRsPtvdt/Gbj1b/828Grjr18x8AkG/pqxRfse8xumr9+Ldt40lseNY6WdYT/0nRr+yX3o/7D9Cjxtv+8hfR1ioT8+lvvDkxUa9l/V3+LP05TUMn3VJihDtJROErU6/dhYsbd6CpcdGfPNfFQtbB1w9Bmz78O2vm0t80+wWF9YWiti1KNZZfreEv0N7I5KvO9Xq9slWieW17Idrkb/H12r5bJ2VmH4ZBpc7w5Gbw9Ec2PYCvjQ+1fmTML4XD18DrjF+LeqSMfw08cKv3/qWPaZBPM63lHIdibaQPJZXSt5430ru8c1ifDWDIs53UIhp+lqwrreAPmE2Uvv++yT7mMQxwr0a2Q8G/SajAWZHaRAhunBBS6MPcUxxPs/U6hO/Bftt2fopGw=
*/