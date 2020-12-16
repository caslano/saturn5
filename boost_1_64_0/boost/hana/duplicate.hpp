/*!
@file
Defines `boost::hana::duplicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DUPLICATE_HPP
#define BOOST_HANA_DUPLICATE_HPP

#include <boost/hana/fwd/duplicate.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_>
    constexpr decltype(auto) duplicate_t::operator()(W_&& w) const {
        using W = typename hana::tag_of<W_>::type;
        using Duplicate = BOOST_HANA_DISPATCH_IF(duplicate_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::duplicate(w) requires 'w' to be a Comonad");
    #endif

        return Duplicate::apply(static_cast<W_&&>(w));
    }
    //! @endcond

    template <typename W, bool condition>
    struct duplicate_impl<W, when<condition>> : default_ {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::extend(static_cast<X&&>(x), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DUPLICATE_HPP

/* duplicate.hpp
w/fEFnG8M/h8+WIe9XYN62V/XIx3TpuF1L9J9O9oby46pHxHPv0q3i+6xfhnH/2RyFbqA/16xcW4I5znFecz5HscD/W8gvOxg+f48iF5f2JrOP3sufQL19GvSpfn9PQyzi/9ueVsf6b63mYh93k+46YUxmWqf8NzuSaR7+0U0A/mvrlDv+7UW9z/+6lnjNe2Mj5awnFE2vi8ajXrUePmEsYdrG95Jt/3SuF9o+WMH/m8yiebcaTC/Uc/+MBq6SefqWM8yX0UmCPvd920yHlZ8iivl8l1sc/kvhiR1+fTrp/k/aQQ9T08b6436z+ygOcs74NN5zrdCWOcwHN9mkP26xTtaSTHdWS217geloTTjnH/LFHt5St8LsL9sYv9PsY4IieZzzeZHqN/4yjhOLmeIYm0R6xn+Wz5foKZ8zktW+bfs5LzTr2Ipt6+xjjzFO1NhZP6OotxH/VqSyXvZ/dx3WbTz+L5spNx1THaJ58q3i8L5fnGOGwK78PlcP5vruN+y6Sd5/pspb5sYdw1bQ79GZ4Ldy7QH+Y5nHOWz7cmqM9pGG9UelNPqH8G7oNdnNdSxnd23n9hHH6M/Uq9Tn9M1c8yvhf2LJ+XUN9Pq+/Hsf6BAT6n+Cr9uzU8Hwvo5xyi3m2kn8H13aE+163mOc51m/K0GrdyXWgHprBfOdSfaep7SF58vhNB+8R+nErn/qR9WcX187vE/qp6PMh1DmfcGc33FU5S79T3urmOx+bS/6K+Lm+if0C7fJ36voT7qWQ/55XPcVwX6I98wPHQTy15R66zD9f3NW/aq/O0P7Q3WWqczec0IStZXvUXOD8V1PsB9b3ZZRxPBOPZc9R/xou2MO5f3jdO3cRznfm3sV9naHem0O873EQ/nPpzkvq/hX5BTT7L5wuxcNxfZXyo+melYry+1N9xP9B/2c55XV5E/U4R8jrXO4Hn1DTm26m+F5cl3xOs+RjjD/b/cgfteS5w11dEPXHy+SL12vE9Pi9T3+vic/tFC2hHwljPOu7vPDmu64W0S/upny/weQTj6AMX6M+8wfiB788foT4eCGd+fp+TJed5WwafI+5iXMj5Gximn8h44/Rsxuf0W/bkMR7g+T0QxvhcfV+7Usqja/he40mOy49+cQL9l2e4XmcYV7K9i4w/YtX3HguFeGr8fRM+D0gSMkVAfL9bT7iOl6jvNr6HbrbJ9bjeIWS9Nqm3p5bL65d5Xs9X/93EBcZDh6nnqTxP1fj5JPUxylvme5fxPPfPkioh0930g5p53qj+83qek1zfJSv4/GuAflgW803mPp/N84zjTXBIv3J+Dss/Tftn4PnAeOEmxj9erlSIIPe8rGX+nfQHeF7cmkh7RH/HznVYRX8ysFJI+fuK3O987hiygOe6el/eQr/USX88T/bTxfMjIZt+Df2ROxb6bZuor5E8X1+gnv+M8SjP84vqc2WeK7sYF+/bxfVivkCej1tt7B/1K5L2+chFPg9YQf86nHGMmc9zXzYwfqF+ct8oz/B9TepLDect9vOMY6Kkvp1hHBCZTH1bqz7P43eeo9P/zPNQjaNp107OUeT1FXzfwcC4bRKfs6yl3c6n/0Y92MP+Lbqo3ldXpNxGfXubdoj6d6uBcR7bO8L9cofz5GKcEHKW/qr67xbU9/VD+X7NWwrnifE//djpFYxHmc8m+wu/hOvyGM8P7p/YfN5PYb/3pPA5E+PTyCx5Dm6jvrvoPyXE8b6mwuc1A4xruN/n5PA7/QFbAvcv1+eEnX4c5QO0h6eZr2IS10e114xnfPLph1BfXOr7sdTzHN73TI1nP9nejDVyX0xj3GzjeXlptfq+BN8b4vssV6lP02lXLvH9zIM=
*/