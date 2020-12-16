/*
Copyright 2019-2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_DETAIL_OSTREAM_GUARD_HPP
#define BOOST_IO_DETAIL_OSTREAM_GUARD_HPP

#include <boost/config.hpp>
#include <iosfwd>

namespace boost {
namespace io {
namespace detail {

template<class Char, class Traits>
class ostream_guard {
public:
    explicit ostream_guard(std::basic_ostream<Char, Traits>& os) BOOST_NOEXCEPT
        : os_(&os) { }

    ~ostream_guard() BOOST_NOEXCEPT_IF(false) {
        if (os_) {
            os_->setstate(std::basic_ostream<Char, Traits>::badbit);
        }
    }

    void release() BOOST_NOEXCEPT {
        os_ = 0;
    }

private:
    ostream_guard(const ostream_guard&);
    ostream_guard& operator=(const ostream_guard&);

    std::basic_ostream<Char, Traits>* os_;
};

} /* detail */
} /* io */
} /* boost */

#endif

/* ostream_guard.hpp
k53WfNip+/JRZ4W3x/aA2Id74/g3v+zX4u1Tmk1YfkfCjV+VhLcPp19fGX79pv7cvHDn7DXe7t1iSc8fHvj98Bu8nn8NnTLgsaJPB+Qiv/L80KL03524sejIdV+veP76FR2ewPcFWe/pr5l50zd13bZ8cOewtr33DXwl3PmHjV9/ql/f2vj1p98q9tdMfV8JPNEl7xvy21T2VnxeBTo3KfC7kOf+1VrfnPitbSXHeVsZ5hDaOBtBm1/n0HZdLm1/jQR2BY4B9gBmAk+iLbRLaAvtMto8m0mbZ1fQfyltpJUDLwLeShtoS/n8QWAO8PfkfwR4CbAKeCnwBdqsq+bz12i77gvarqtTbNdNt7/JoGyZz+YmP/P5GPP5BM/lqAJ2Aq5mvp7meRxrgMN4DtlI4LM8B+RJ4BjeW/Flce5/mia+SvC5Q84jaWveU56PMN5HgT15LsmveZ/N+6m8t85BqWF8sxmfeg5KD+avN8vxRJbjIMbfh/GewnhPBV7Ic6IuBZ7B+Acx/gEsx4HAMj63bdftD2878X3agPuAthO3Kv4q6vG3nf520N9OxSZhFf1laGwSJrgC+W4JbAZMAh4PTAb2MeMCfi3hcp4U+CrDSQO9xXCuovyupl5cC+wFLKe+L6Btv4XA03m+y8U812US8DbK7X5gDs9zmQK8g+V4F+vDYp6XuAQIMpayPixjPbif9eBu4Gq6P0P3l+j+MnAecD3vzfyNtOcpkXfmL0bKjbYbIQcTTwXGAvsDWwAHAhOAA4BJvKcNR84vou5qbDgWUF6FwDTaKBTd4Dk6xaxPV9L2YRlwLG1pTuBzq3zLrXg05ZvHePIZ3lSGl89wpqr5ZzgtNfn3Mf+tmf80YBywDTAeeBzl0Ib5z7LmvoDtGF5T0HCG9xfqax0wFvhX1rtvgHE8P1PmAlnvv2E6J4IGM9xxDNf0P4bhuqnPTajPTYEyRgN2ADYDnsDnvYDNgWOBcUD7nDeGn6KpZ3uY7o+ArYB7gVZ+a+ivlya/XSi/E5iebkxPd2BXYA9gN2BXYE/es1z4Dg/ZasqlPdPTgec3daT8OrMd6AQ8zgxXSWcGwzvTmU77nNPPaaP0IKfdD7E9/BPz/SVtcx5S9fBg+HamN8vlRKAPeBLz24ftzMmK/KsPhm/nPmF+P2X+9in6W0t/7TVyakf5twemANOBbYAd2d51ALbjvS13jkm7a8L7nnL6O+X0A/uJf/K8qn8Zgfz9yPQtBGUxvGsYXgJoHsN7geG9zPDWAxN5fp+P5/d14X1v4GtsL96l7dTXef7VZuBFwDfY/7zF/ucd4DzyL3FDnqc1bEuU51XxrCqeR0V7ouUg8xyqZUDrHKp1JuF+B3Az7Y2OvCDY5uhwkB/PKkC0PypnTVl7gl5U7JAuyUJ8tEc6BjQJVEqbpCtBQedFAe8Gfg9MOeuordIc0MELbZulcv7TYdj4pO1S1W6pfdZTKbA3cBEwC1gBWobfq0CbQYdNvsFIG6g3z3TKC7FvugKk2jfdMR7yBXmH2Ocx2WcxpeNZBmgzz2MaPCRwFlMhsBxknb/0InAH90JZZy+lgfqB2uK+N4j2Uu3zlRYCl9BuavxW71HbqTxLSd1LNRw0kTZUy2lHtRJUDTLPRqoB1oIGI5w80ALQSjNM0EFQ/DacZwUaA/KDKkBrQFtBh0FpH+LMJNBEUDmoElQN2g/ybsdZT9ujtlejV/SKXtErekWv6PXLXr/0+v9iv0nZs6fOPfb1/z4jPqmHeb7TMPN9aHL/fqW5kwvzA+f+rfcZ9vect3ju33CQdS7DVNPfG/KNZNzYrOyLhg4ZN0KWhfAbSV4XObNmctD3HOE/S/895w2u4cc=
*/