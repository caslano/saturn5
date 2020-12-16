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
MwdebczCbovjLYPC09PypFzCfDiuyXdVC7OTb/FZNVafrOTdcSrVbE1HcqE11WxtE1GzBNSfz2KqqTrVFKRq9ZhFY6qQ1CuXiRGm6M8g+h3t6CcQ/bXCqvhr2nmzTc9/Z9HpATp9KTs03vyNWL6G62NYRIW5mT1oKULOwDixUV7lJrgNKUL53TZD+n4oX2rKTW1OXmT01aKTWHlj6CsavtRMZ1/b+N7/sb62p+Mvwzb+Q0damjQxKUHKEx34omlOoP8bi/5HC2V1X8LHxFfrB2SSboSjh8AxyYzjU4/oqcsyLMfMDBikCr4nwR9pT/ctJvgnAf4U3CbCeN+/RzzpAMb3kXsxDcndxqimwY6NA9m346zWVFzetcQJ4bBrB0r0cSK9oAUrrJP8H5+Bxak2dcmwi0c5tYNgnaXICbDl9X9IU1/7VdexFzCrzJDd74wyzRSNjgq4NUoxNctUeFBb8iVMl8En2S/4iV+UqpJWKZ9amFLlwpSOCxOvG2lbkJ8MeZvba78Qcaf/kziRt3HvoQ6ftNmItpOJkf24UVICtS6K/qK+ZzCypO3QOdpOqX7jWFkah8pSFY0jIUooS+PQpVGlzYM0fTbshvsMTdf7Sm1GRzB/uHIaw9spUeSyjiyKfGP7NjWbNiqDRu3e/3q7N6tXy98qcDyHdmjnlzsFPwm/0IWXl2BvZ35e/TaXgE7lpkvFplPhe7dGiqZLjSm8yYl6ZpU+NIrw5JOZGwpHd9IW78NBjHpmeqC8hXLbvhbTW+VdoSYCbYBU6oO6shRhk8HLcJhfzw/o0rF7Kynko8RLIf6oigzAxcH8n0IbKRlHQifgNXaoFxznQBIx2JRyHoxD0jQL/P3YpJB3cvj3ehxJJr/HOBWxsH5yADpgbd4MywSeov9nhHQbjSBvV/TrJeLbXFqXV8xBLTdtu7xdK62SsdGhmZNqhZSxEZpasw0m0ML1Rxx/eUQ8kSItoWZ75bvd8hBG5y1z7Rgqoq2EGqioUtfQ0JP6H1iE2UUFpJANuo7pSF1CQI8b0Esp8G9eDK+Xn8AR3J/CVqG53fT6ibh5r0AJPZFAqdLQoPcnqQYdTy38SAP1SHeSSyTcJRNyjFZkSjiMhCASUmYnCSHF7fzfFFJCxH9ro+nbG3xeFpa+fVwbq7587lk1uD/oSuAB6Ohu4dwf/NBaBoj7jrkMrs/e1lp9+lWEV59HWlvr80LjmtwfjAiCv+5EWfjt0aa19f5H3R6Fqc/xivhfrQQWGa2dHx9wgFWCcWdvLTwpkgA4SyRI0pFc0K7a4E7B/ngBHq5upZtb0RpcmdceCeUjoRzNsy3TWCNvJ5P9+bo7PD0B4NviRIzL64iDSi914OOCIXBGdlI4443NMJyDitFzsWLbZEsikozjZDzgFigZN0TJeGYg/m2UkIwvpAdB5CKobj6zjK1lZaab3UbyPu7HMo6/kVJ9s9b6L/T7dy1oytzZ09z/Wdz/mVI62isfFPnUXJFEzRPsaDN2OlzADTMxUjTM1LSiC0h7vBdKbfGI+OyfmRtZjxu1XuBKM+PqEKl0eBvjBdY4umySr6PQhykQ72lqU63FljanFrv+mM0ImSTP7wHmc5j5MRGC5Y5blou7zobW8OI47mrLt8bfN83kA+c/2vA3l/hbGMv8TWL+drokfw/h14MNTj9/Yi3zSf52gAojbcsKIXGgWpdji7Y+LFfG8PA5JL5/CnwrBb7VOr43Pqsen1087Gxx4I0V2IXIcGl70okNOFhmMvcSTjQkNAlpiK1mVwSsZpey46gmcpkiVYvzh6Bz4oMy3UOVeu5R6rk3mgSeDeWea+AUPXclnWjeKtOPkXJWPU3gd9uBv+k=
*/