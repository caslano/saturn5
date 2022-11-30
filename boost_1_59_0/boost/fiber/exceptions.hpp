//
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// based on boost.thread

#ifndef BOOST_fiber_errorS_H
#define BOOST_fiber_errorS_H

#include <future>
#include <stdexcept>
#include <string>
#include <system_error>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class fiber_error : public std::system_error {
public:
    explicit fiber_error( std::error_code ec) :
        std::system_error{ ec } {
    }

    fiber_error( std::error_code ec, const char * what_arg) :
        std::system_error{ ec, what_arg } {
    }

    fiber_error( std::error_code ec, std::string const& what_arg) :
        std::system_error{ ec, what_arg } {
    }

    ~fiber_error() override = default;
};

class lock_error : public fiber_error {
public:
    explicit lock_error( std::error_code ec) :
        fiber_error{ ec } {
    }

    lock_error( std::error_code ec, const char * what_arg) :
        fiber_error{ ec, what_arg } {
    }

    lock_error( std::error_code ec, std::string const& what_arg) :
        fiber_error{ ec, what_arg } {
    }
};

enum class future_errc {
    broken_promise = 1,
    future_already_retrieved,
    promise_already_satisfied,
    no_state
};

BOOST_FIBERS_DECL
std::error_category const& future_category() noexcept;

}}

namespace std {

template<>
struct is_error_code_enum< boost::fibers::future_errc > : public true_type {
};

inline
std::error_code make_error_code( boost::fibers::future_errc e) noexcept {
    return std::error_code{ static_cast< int >( e), boost::fibers::future_category() };
}

inline
std::error_condition make_error_condition( boost::fibers::future_errc e) noexcept {
    return std::error_condition{ static_cast< int >( e), boost::fibers::future_category() };
}

}

namespace boost {
namespace fibers {

class future_error : public fiber_error {
public:
    explicit future_error( std::error_code ec) :
        fiber_error{ ec } {
    }
};

class future_uninitialized : public future_error {
public:
    future_uninitialized() :
        future_error{ std::make_error_code( future_errc::no_state) } {
    }
};

class future_already_retrieved : public future_error {
public:
    future_already_retrieved() :
        future_error{ std::make_error_code( future_errc::future_already_retrieved) } {
    }
};

class broken_promise : public future_error {
public:
    broken_promise() :
        future_error{ std::make_error_code( future_errc::broken_promise) } {
    }
};

class promise_already_satisfied : public future_error {
public:
    promise_already_satisfied() :
        future_error{ std::make_error_code( future_errc::promise_already_satisfied) } {
    }
};

class promise_uninitialized : public future_error {
public:
    promise_uninitialized() :
        future_error{ std::make_error_code( future_errc::no_state) } {
    }
};

class packaged_task_uninitialized : public future_error {
public:
    packaged_task_uninitialized() :
        future_error{ std::make_error_code( future_errc::no_state) } {
    }
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_fiber_errorS_H

/* exceptions.hpp
spSGlwAWLOnT+q2CHoMmbBKpV528MnpEZlroByw5MkHvXPjW2b/wKcdvwtPcrPvgsGe6yfNk76J+7gLIM15xFveL3h4mcB4aCc6QMqZjZK6PvSkd6zPuWd1mUnB1aeJYFr7sKyHlFwk4VZaeCclHKMt6cmh5OOKwWroakK9nMhxfDmoW7uJ+6dlLTRQ6+vyEeFYjw2LctT7mkFn55uCyo2bFwPkPQh6GT8xnK3A6EVMsBts13YOxPZrfnAbF6M4MyDU3gwJMiwG4d1bl8eXtjm9ZizKOE3DCByRztDyQrU08mlNAiRIZA3bFc2+A1O8mAfJwGjTDuw1NgyJDKf6+XTZuh7MvO6PxnR0oIOANQg4E0zNYP4DuG6rW9ljMmgRoePDOj5tERO4sDPEA/kenSonehBVzE2P1dBAYZpH2ElbK1H1eJYE4+tIs8uCkPxC5Kx/LD2H+L1w79KXU0+Lf8KsXuyttSJ9iLvmtMlc/s0V0ulqzVE7D92WqvVKO3M2Fw0J6JYKrbU4Ql/MWwcf3/upEUKZ7u2reHOZ4cu/kp6S//D2j9pI7qUxHBcQHPf+x1ntBgscLybG6hrD3SLuhGiVXpc567/y6igf6lbZnuvUtjL+hoz+oCL6ZCpdsOtDQjJlBxX+vgqybcEdTzJpjxF+2DBzAma8M6g332CKOVTLLGaDOji7lG+tdfGlVCOFftNdtbj4GlN1Knxv+JqVAuaqOEfk7oqFIPvPmOiUa9Qg1j8LecDIzppC8d516y4+dQBwjmLpkV590qOR0E2hrNHfkYe7dvIrJF9AeDamSiGqq5MbUrv0RYg/xbkPu6o7VWg8dLuByGLaAI1aLyPaT2VJA+hM4Mh1b4GivYuDLFpxwZvud5a/n0ZyBY0AAUR8GgWFTjwIVEmtL4Npe99Kfh2m9pPt2TKkYU/K/HfZdoe88dnZw93Rri4gqKWQsrd4zS/u9DpCz4+oSHYHPNbrwlZm3a88QGY0Al/8ZYyp2ZYsOWarFYupGS42THULR50lD/JcjS3JJLGAj+/0InWIoaN1pViZiMxKmq8n6+UZ5Z5Ac8ZO91iMDncmFtiVCzy0bD+FHB1XpBnF0SCvjwAuaTUlAGCdN2Zhgtu0TGw9ErlH26oVw0hTCpKtFm37a2f09gnKl+upozXRGERZd2vXRlKYr+Anh9AOUHSrHM2zzkYk5yzrN4sPZLG6bYqpJ8HNfo+hzAe5KEdHZZgj3QKhAakcpb4R1MC6IrBEbPPZ8JoxWxqpriPQU2fIYV/auMcpyXpzSLtnxgg/VwgndcrdstvOVOBq6cimZ3A/YkNj9efk+Sb9sJvXxVSYO58+/o16WFe9eCB2uChK2SBE73X4nyr87/hOZhylEhq1MNC2DwdTYXlrPgcv0qoqgmwzD8WveM05PgujM5Eb5WWN+Ct2KJ/YSIAHYvvTdMY4p0CUQOjxSemPKf25M5eY5TsoGW6fQpGtYH1R+jxWqDnwwhd3MOPCBa3+o/h9zqkk8EtraFLd5SlkkueYXqStM6upJcfqxzhzG9SzIoTggE8fjmDKSuyqIJCX/qyBiAo6toqkY1suspvac2aEfcciiz89c02pQaH2O+dU0a54JdpixUtweimNOX1ZSN8t7XgI0jb9DpAgT0zZoZoOgO93+3mPgnm3sXeUwGGEq+VVJyfFusWf6eqB20zo1aq5NoSguoBi37VXHkbd26npLDfSDUw/sSoDEdY28uvKxLUvyy1y5BLUNiWdv4yyz7lCOTofToCZWS4zCVac/NuO31s5pcr5JJJ3WbbQlYnIraQI1q6r//v25w5AvBk1KtMwR1+1LZDq21ABfDmbV7TeqFvVqwLx9xhHOjNdXn2Na+zi9Fiusd9gkf2Sv2/t52Q2Sqy+qYA98bLx6O/LiQ4uEjS8ztfzB4fq5n4gz9wRnUcsBeGa0hBBTbJ/BMyj3KN1akPqktpY+2yGjcTxbETlnQlnLgBXpd/PL8w1L7eSHS9w6XQKRw8RE5Se+h/GmhitPyILX1MXt/MUtIrbwtXk2yYS49gQ4m3FMfXcqSifWWhm+ZXJ2Z69XZLvX7djURF8gX5epxTD1h0RnZugAsQ9Buz0AbcsQvG9iFGIjgveXrDmacFKvTJLmYd0WyPhZ0sUoTmJ88w8hBPm4DBzPmIdYUYUfLd6tasxoGY65QTPcfyU7VPqPB9tBcs5WH+731h8S7HR7DbBSDBeA3ycOdQ74SzsyIgej1S/wZ5YbV99myeW6ORnVVXlDjAERHfBIX9AlXr1/dYp/BlEJbw5dd/5rqLkvBeLKtO75jFNNpGEyuPY6A7557UsJnLKXMhkKQ1MpvlqX5IwfbCEVfvhhEhZ+AC5D+Erab/BrFX9ZHdqtz8sgG/8Sjq7vQ23RvRO9IMsFZWj2k/F2k1nRWOz3V71i6L7Qwq6JC6FXtfwyZAPdVxWdCisaFo3d32Qf5j0tjCBiuM9xB+VdP2ujimWW5NgyZMHMSdFc3m3hnDmWS5YmFxV/Tf4Zj5yf8t2NycvNhiaAIsnk0VObzSAbsihyqg2Lz9GGUfXQOHwx77Xty8fFsUZqhtQXhhSp/voICFvB2bK37ogh8eiICT773kwXC8p3Yc/3GWWonOW5k0oVMN7OVB9v/9dUqvA3XfUGoW2NCTfPv5B7OJhPqiJdf/XC9h9pEskFf5AptYTo0ZtJxNeog1eC15Ka2IugkgdIYwlzyo45TTey3mPrLjvXf5EcW6r+ML6edUn4CRwcJGpe/fuGzq0ChapxZZSGeB3kLNPgMwfxyAxsA7Y+l+LebejPaTwkjaOmcGLj5l5bb9jjfCXu/K+gRj1hq5xLJ33hD70qgg76wqPs/dtmcrjQaLpdk5zSRMgZP2/6IsSCPwEzH+CCucYXeqNyFWMYwJm9Mg+J+prVU4jfbsyXACeRplyrbVFcemhkFx/2seG7T/O6NgHJRsSOo6IJijzxkClxMKakkM8tumlP7wmg74GfFqlgDZbNbOH98XbYgINRso+8BBttQG/9YUzQWtMfFZfssjKns+9f6Cnj0dwgozXLV0kwt41maItvef6i6/6lQ7fG77sj3mFeSXO/CEeU9SR8yp1MPlB8I6OJ3aqc+vLPlQusZZ3V9bWvylqawC5Lvb48YNmsMt7ds9PdYxydyIYaHvazwx2vS9mfhvcJTLIVp5cBPCjYnllzHJb4Y+LZk3BS4jkW5ZJa/32Ws5ySKOmXpHbQl5OWNGWwWaDgRRHrrMufGVs8jjl91B3FpaX0+RmkDRbGH26sZaHKnIYiWHx8FZx/VUaN1TJ19XzEVVl+D+B2O/mnQcBw3z9WzshKpq7nB65yxZB2W1x87GPararMtFJfWekCLwhj1hjC4a9QVILnC8M1c6/gQ2omWE4L83971a6VmFgtZoc7OdH7Mjt587CbYVcfGWoPXqoDaZPP1q9+aBm40XVcXSvDWdWaZwEp6uEYVYJ4jvb7Md141O4ySW1X6xeCp1XdDjs8v3S/gkLPT8pPzuby01LjwNwPWfZ+0h+hbuseQMWuYRZrQPU1kwBsrTeUGf6+RtvR6+e6OhY54GsdU6d9sDAWSpZaISaHUFFklFuDihc3sBxT/su97cGq2UzKAYUNejgTphi9g891gllW9ed/WgtltEV7C26mjWld3jDNAjyG1EXkj5zZJYPqRaGXPFiUXb6aPWMdW2a8C7ATAo71FryfNNqffRUREbPJaSmeRcwiLaZggTZgEuq1vnpCTxYKg30SJtM6mVQ7B59KfyIQVYXw10iq7uzKDLV1JVvFaWEHAwi9FopTfyJPJ7exv5IpWjEBHh3oiPGoZOHRSeQLtWSP7qoIGjACSn0LiUYLQ/LbSQNzLg+rbLrbagRP+u64FXKS5ddQ2RQunHPLoaWbKMGV4zHok3abnyeOqLiRWLC/YSweavDYrvvX/fK831zCPmn9/MuT3FG9p6U4TzKAB9k3zD5lB2x+DGBW1sLqDy4mje/SeCz2g19RGn1KHqZjr0NfmCtRDmz3+/RJGU2C50uAwHJuC4zI02v9dMkSV2wW2egd/K8Rmd2VxR7hipNEccybbguyJGrwViPL62i3PrkkDncgwTTtIcAR8DtuRBBzwJQoZ29NWf7s5GB0tlSJ3f52acl0tzAVaHhvQ4XURDRjqRSrFysh5fmfNcyzI85fMU077gsjBxEWoyzEE1WiQ0rDT0gBhRa184rewx3C72nQ++FuRtmznelovdNO1jt8KZJtj33J09b0Ro2aBUrZ6RABVVzc6REFAtBM8t2emS3MhFQC7ye6Yvstyopyt5VzptCjNDxS3b2w82HX2emoHhpBvRLXAYM6ZxmZ7XykMZCUdVMK7ks3d52Fl9/1D/1A/SlK4hPWRsKv2cD3/fJBwhmlG4q2RP7+LyXeEM2ue8dqpRq1NXlgdfhRceHTZzu8sl4Knzlq2aWydGA8Qq9mo+lAYPsz5NT6rEGZdacU7Jq6dqMJkkViwU6zUXAW/UcLVccFGD1ec1QGNV3mmqJDougCtPTZNS4LuQDnKVHrMJnJjnyDc8Tuthi9iOm4oC43tdWbzhL8mnzSdWr5PsFtu0+metc/JmwpiuSqiqsKu0WrzcT/EmGPASrpIrt9t9VmrVuPiRO9bPCjwmMG8gN1sJfrjTpWatXwLnGN00NSwVNxBK/lhQtqrR1RFtK5MPVWY7jtftEaB7PVaZgD56mvP/rEH7xT4EZi/MkVk0ByibQjt4WZUBh7HAveQjF8t5tVgiXr2WQE7LdPMba8uPhVG/fY1bpdx+dnNwKixYPC+8MCuWA1uKYHh82HoHkNoast7MWyFgPohOOppl2h8iMjmZxX/DwFm42tHeIZg5FgKTtD6NZz22As84mvXGwjNmLrarfNm8Y/5R6s7BLgohfi0ASZ/TvZ83IZLK7rYYzzL1knaEkN/DNzqr9+tRfCtVvYsL3JUd2VCKmvecBNYnXplqYZYdZ/Uc2YvZfNrvUWlf8V89AWMtMB1QXuMpeHsteCxyZmlReKMLmdAFE/JHkEP9X2gIRvXt7IASY3jerpR1puyQFH/JCazRoAtDLoLDbWw0r5qQW51x7kkrIXstQoBL0fenjVZcaDdT8IbeDB4Mnga3yo0sgu3sP3oS/1J8WOnIp3b15XpQtTb9ArxFSapk5X0ZApKCfKT+GEoZ8mdNrU9ypfsZ0w0nMKDTI/e3m/OZWN64g1bUhmkviH7FuNl9uzG8eaGWtYGFemgGeCdZi2ehIdDwLq4EBs5k7l9KYwiQHJ8BA1qeZr5iepTCRWeUQ8eZsmr8w6MiO572P/qDkc7Zm5tA34j9ItDLtYJ14QkNXKgSx+IMdYfZiOAqLTewVC4MF2f/nQ5Bk0nY2tk1IHloJYHxG1EsWoUXWTOUXDz7iK5cGoAgbLJvbfsrhp7v5BJlnnuIf2lknsYVVoArCXVm1kqfLCFXKWFJoMc6t0idxN4+V8U832uYwSUnGurKj+0NDcKjep74Bm6oRyvvr76BRiJEhpnAMd+YuCZIsAaExgTyl+2BLK9QOK9k4RFyeuUI5PGfP/ASOA3H97ljTEUWQHn3ppWBfYBYzrpJyfThxZJ3TqZrZeP4tg8fPhsdxXvaVX41x6yP4Yyh0oSHGDPvkI4aoPzbqYXKiuMsk/1+xaJrneJQaT3GV1fqvV8J4P0nDOkUPnNA58frphCp1DnTgfohyelYYXzTYuPbC7btzwX2tfQqkiij0aiUbaqstLf2+e7hCOJrPSVTsPCfjIu1xvLb/cf1p+/fppmVSGm/QFN/fAT3ikrmKkn4aqqQloUcQDog8QzkVIlCW3rvq5j+fgLEvwTo10uCPE4VyRWaZ+Kq/prB5M29mTWuH5eR+YeV9Xth4jwlQjKqfOiP5K8IojUzczuIkW2BJNGd4EV/Mh7AmEetZWGaPT/LQUkT9c3xm7Y8BzPmzYguvix1PgxbPyCzSVvKe7H8KDoz31dX7hFJv7lvUL3/TSw7tCYj030jK9YTKY/qKZrtdvJS8yVSKvp7xGFywvbgV3l0uGgQJBzpcNZjk9AbYMNpYb6nLMZkOhkGiCyr9c5Buc7iMcnQXCiyU81WByUwIEt3zIjGs8DEwqpWEneHvRVfsftwL6igFyY76ujtJGGZ1P/3h8EkRa1ZvcXxKrcQ0zd4DF3dPzN8mi5NSbthvjN8PYrd+Mpu0WOSW9rPahCADY3fzEQFpaVSturRqox8DO2yW14i3+3vA37IpSuTv4o4D6kC24TSHBg23xtjiGGq18CqjVdwBEgW43w1FGpkscttkofdtmvak2AesA5a7mq+Mkx/CCuP1wtGNQdHz3v2csF9pWG5Pv9fbwyUPY5pf6+haCt/jtgU5CIDpGvI7xkA4vW8YpQwAXX99D8B4f0VYsoi21VmUkFkAxNVvHTIwssdAbEDWWlU9puzP2RBnVgWA3+zsegC/MIxuqzFQ2gsbLoao8/2Az12r7aXmRt6OyprdR71rsRRXSUZoAHvao+ODkHZ41KVhqAbeblDZYlHvITEKlIXPfKOxmYC/3bgngAGdcmZ57OQPdhgkZAaxO+B772d5qXvbp5tvdwzNZVCvqOl+FMH/z9Tn1a/XB+zK3iPHotuIrm6mDZ7XgxFoj3dqpk0bzrZqyw1n+cZZ15wZDiE8j8svao+IEtIRGcLBnyUw+3JnjzsSXq0JeLP/8Ci6nJgKsI0tqxTvMqzSi+0oJ1BdjOH4EOQuPUB8otZ5f8w9QnhBI4zBmP/fG3yXMC/LXzL6F8L1gKx8i/izpP7j2V0ss8FsO7gD7bv1hqBMCKRIgnsKDF6Pen95zOE1UN86dPCSuPSQmcIbFDgrBBbU9EgyWcBn4eDOIjY593+lvHP4tlk+GnrF4flIIUxvDDbjge+kq14CeGyL98FW1Hz766F5yCyPEmZZD5nQYbSGlUMDeY0/ZQ5a49pj0i9mdgY2UiZ0nJj6FCXjCp9haJYwFaKBmUyKUiONz8kIibv3zbslO3E9phQAeWNSjUynDDDFckpx0ForwrHGRwT7bKsCsYKRukktazC44D/kLlX9k6zFWikL4A9mGE5DfgrBpu+PjqA3/d3Tjk3KOc/wJlLkPEH2aBms41TuOCAmiLDcuNxxq23n0D9W81wvw5T9VDHisYobRdo3jtF5rgm5b27XDtp42ZVBvoncD8+tgOKDzxICjAz/BTdtr+SZxpSoPDlUpO5fKdl48/nhC5VIlvR6idFIR2LqWv1P0/g59cvtp+Y9UlFITuqZTXCHW0ITUEgDgJ001rDnXRaA7o26oPjQvVMdx6UPA5G+SINUaT56BLW4eBLYNZ1aWwDA4WFgu4wPOzqd73aFKCat78PZUzHKzwLoHqV/Ty2AAqHtp7WecTCuzQAM/CKDxu/tZtyvGktS8aPdZAlNb1b7qIRrGLO+/IiWppsN1P3ueBNT6JMCTthJ4my3fkGksnjRb/jLOiCt9QJFpmJcFKDxl+zThh5XqLGChacJuKiE0bM1mQ7sDKKU3pqx4RCijUolBr7gkhT190UaOlgiagjr9ss4N2zKIn9D9XT36GwCvuNVJ6ZN7siSf7KnL0KOgpt5uOmoYCVnSbljepODePwiyKzRguFxMvfMP4BVB
*/