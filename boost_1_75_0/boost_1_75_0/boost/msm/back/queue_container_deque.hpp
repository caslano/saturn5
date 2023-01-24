// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H
#define BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H

#include <deque>

namespace boost { namespace msm { namespace back
{
    struct queue_container_deque
    {
        typedef int queue_container_policy;

        template <class Element>
        struct In 
        {
            typedef typename std::deque<Element> type;
        };
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H

/* queue_container_deque.hpp
Ff2nAvwPEP2nXj36TwX4+4dG/6ne9A99fID6GJcq039qMPjl/GPZyXXnTNs5LHDOtMpj+svKmVa+ijZ01pUzrYVZzpnmibNjKWqcVacoOPuanTt7DcLxqEi5ajgbyJqu2pMZEs5MKV44i4M+vjsQ+9guRcLZdSmh0+ynyWr4lyQr8E9OBvip7eLkqwZ/bDLA3y8k+LXJXvDvuQfgH4B9PHKPBP+P99QJP2S5Wvs6pGiLI6NMywbBocuD/d6QV8wE9k13+GU3xVS7o4csZB+6PjpCU7NWa41eQcsxlc75XxP5JQpKDjePbyx4Db4Ro/7G6Nfkb7CGw6Bhx5Jw3nAOb7ibb8Me7U57VZ1eTvyRtVQKBa/Ec86Wj7rd1FgJb+zkSu/GPNoaP9+nj8b56j4+xFp2fv5mGO/jfN7s6z7NevZx0is+7QqvqNvVQ7t/363h7ebxdnsEa5c1w9536A7MA9xoaQyAkH94leetihEc/eKcNWlaTQnvr5bada2AdsvVmbuqKtljHnQhtf+Qd/s2z/b108Ol9gt4v0U/7R8sCPfIcdjrD72m6sCZWrdSKxpyLDNQdS2TZBEKIkxwjE0opXngOcGQVo2ldbe6Y4cNgiHMjhKG92I9abhWSN07Ph3kJSP4BJB68VjiMR7sVPa9sVSsMD+aaiyDVI1ntvLwB2JwY6vYixH6NduE1B/HrcTmawZSEucEkK6PL1ek
*/