/*!
@file
Forward declares `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIRST_HPP
#define BOOST_HANA_FWD_FIRST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::first` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the first element, where
    //! the type of reference must match that of the pair passed to `first`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //!
    //! Example
    //! -------
    //! @include example/first.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto first = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct first_impl : first_impl<P, when<true>> { };

    struct first_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr first_t first{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIRST_HPP

/* first.hpp
1VKRIMf5vst0QHQB0vlK1EzO5kyyKRPax8LLcnFjlqCQalLhI19hVe2HEP7SgBP6ilzfLL0G99+AGsxWnZnKl8k5RzhX5Cq33sDkiM4q3iBhukbUg7+5Tqdk6kLY23KylY8wvruuvyqBIdu26LEk+52s/yck9iN0CCWqI1B+JohnzBt8y357Gn1X8E7PyNjbhF6vJJDzR3z57DAQsoZXvbfVki8fLTmwfLiqv2ndtHR/elVJ3809+ApYq7hB3SYuh/jTqOhZMG8IJRlzrPmRkg5AE0TgPWAOSfkDN7ffvp28llKkSH6XkP4JukuUNYXk45ZTzR21IAM/a8cegqFHpNeMLtbLbyQm/mtmpKDdoTtHTq3juG/uA1a81IrIF0EawvyKcYmTRoiKjU4kFOIvV+gbRvO51HLCpjETlQxBrUanbLiHUXw6pRKwV9aeKQ/L3+FutVzkroFNOZx+KPulnClfi0FTM6jC2HTst4dIDO0oDh2TqI+9tXQKuPmKhFPAt5q1U4DLP1amer7Gx5B3wvjutpAP69D3T0VtvhA6EcNhkIWKxTTY5yr18g72SkZs2AuZ4KLgTrTAnFqHntn/DPeMdl7YoUWkrY0/6H3auTan70ermSc/L0R5LgSV1bVIKDf49pkzsOrsXliI2rKKVKCUBhkSsCWZj4Avb9Pw5VNdjw+vSViPQivKY7QqPHxtE3ggoEaoz78iC1jgb55hLPBhvFRzSHKVU2Wd5NIDVO2CNWIjPYCxwtEDWKBVjuCbv4DHKN1PynSXczx0YuUB6ykrCVr8JRJZG5Ac2wiFOz+kz/bAedL5Rg5g/QC3iMP6An8MwUG2qUBt7pgctAbN4aAV6wYnrHueshukQyJL1tvwiODXhoOW8Hi1OqFmTNbH0PnKuSsZQcmjpy66wqlcu5oIpAeUH3FbctQEoq3hUNAK3CQdS4jS/mkFQxryDM7dTCj/RMrhE9UihyWiN4gq8CaWBC3NA7w0I1iaZ8cvzXorZfeVWHbNP6MeVfuZPrlqnZ/TuxdVUvERwqyUFxp0lOQWFAXJvIM8AOlPmxxFeI7j2YyRm4L3XjwuPMPxGNKMaeIHJCTtH/NLSXKn7v3P+HmwY/Pcsymt62L4wTjfFPaWaAYry9fpejGAGEzjEI9S2ci+2p4OhIAiq8P5UXd41b5TwMLZukCzFxO8UHn+OgCSWuFqylU64SQDdq5cHa0XhbAhKy7rlODDI+7E/Xpf4n7Np0Yv7c902ZsABmHgX8U306tDQVxoTa1voGVaJy/N9dk9ysN+9GOlhcnJwSGdleIW1/maEMnbECPgsGbrwvoG0OPmR+y/RBisYpf0YbNA1bJ86R4IXiiL53FUOYKI8yPYtJqcyq8q9BPTKht4MCt50wqvtSAOLYaGjyclxFyTGD4FWiM3MYUtgFHrnl9+PKo15XxuigNNSa2nW8zcEGYHU2N22efuQmPO9A3xhJ6JKltqRGM6AfhrvNSU90v1/XfVENDgRVPq5c5TQbwGGs+RU2k8Bw6/vykhPHnbQnybJ9Rn87tCfdf5R6giAtnYyC5pEnDpEOpPgOwpHLS1XcF3HUGuDMSgje5qBnE5vMUV9XywzTSg1HfR8rMqzc2q/A+qYoxQvTuNUfxwDZBe4WpeULpl3FNZP75KZC6Wy13X8mL9sMvl5P67bXbieqlAAZFkfICVeBIh6lLRv15ny351StW45ynvl2s4wYabCCfIa9JxAlU53UfHN+6/TMu7gPPeG4jlfSrtO1jywfNnkf8jzp93lifOn9ZlyfPnKcSgip8dOPX5Q/XTAW2uIQnenpyOpYwskDKKDNC+712ROL57E8e3zWKk+/8r4vUlGFQ=
*/