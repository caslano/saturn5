
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FUTURE_STATUS_HPP
#define BOOST_FIBERS_FUTURE_STATUS_HPP

#include <future>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

namespace boost {
namespace fibers {

enum class future_status {
    ready = 1,
    timeout,
    deferred
};

}}

#endif // BOOST_FIBERS_FUTURE_STATUS_HPP

/* future_status.hpp
m/LulOwKzlE5MnVb9wYc86vveZaEDmuUCcNcxnFErgtqadT2yYY1s6MLou9BjGPFtXHvmfVUSGnU20UXbiLsA04Xxrrk4hq5rTD2WUG5qekx6HZe7tpiFfS7D7cWqhp7yXjmnm4TVFRi1sZyY2anGsXOylxFCbdYY/7cpKxxil3CXrNkUMlRwEy2A4MDriuGc77lFO8YR7nO7NxSA57rzUBUFXoIbxth3BMvqhf2gAtKxJubpO/saNq6VSDRaUFdSEPcBk670XM5GOFAomyK0wJ9tbxB3cQCRvk2ga5IWVvdaSh3cIR7OI5k/42/bzWREonKIY9AS0q0OwQI0mRRL1vOoMopgdkoITUqFBcaVL1a4RPNPMLXlUBtyzAOBsgl/aumXJdrKCnJTMK4igUsJalQyKFCASSX1KB9IlF8bSoHZtNr//CV//LIpKqNHXMZIzQPTeYuHlsaJdpIKJVSSM9UgzGvbExzAJZkiYqtRY3IZpt4h4f+flOuQvfGrO/Y5MblrG3tw0jujx1J79BH1WlKKY6gpEsiUSpUezR4po3KNOehrvswVw2byYKVTK/hGqUdUmKP3F88L6LNGfvICE2Hw1kzQojXHYXM2JJpUoJiS2RgLanXnFc/zJcPgMxphQCLXNSs1LeKEkaR
*/