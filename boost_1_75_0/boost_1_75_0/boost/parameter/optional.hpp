// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_OPTIONAL_HPP
#define BOOST_PARAMETER_OPTIONAL_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.  In order for
    // a treated function to participate in overload resolution:
    //
    //   - The actual argument type matched by every keyword tag
    //     associated with a predicate must satisfy that predicate
    //
    //   - If a keyword k is specified without an optional<...> or
    //     required<...> wrapper, it is treated as though
    //     optional<k> were specified.
    template <
        typename Tag
      , typename Predicate = ::boost::parameter::aux::use_default
    >
    struct optional
    {
        typedef Tag key_type;
        typedef Predicate predicate;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_optional
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag, typename Predicate>
    struct is_optional< ::boost::parameter::optional<Tag,Predicate> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* optional.hpp
V89x1IWnmdc36OyRXb3TdY9PZdYbMD6Ob2E2HTBN4X38seNzISlPcm3yNfNMQc66YloTZ/rP+vXiC86ThLfMYvlRohywj8UTZR4cy4O6eXrbel+mNYG6xjqgaa0zXV8dfyCUsvBJcZZ9A2WRUnGlfUtKIUuxgU65yB+qaetaHSc9yWlnYPFC8XlxCbJQ3KEspRlZ5OUATWkTMcWbCqz9xG0UPpVd+4XbRGXql3Bp/ixlbaRB9cyfWoc0g/o6nd2sHv1lTdCMMRC0rIWZwSzc3kgsjO9/TbOjx1GH9Wy2O8T+qHjFn0ufxSysNlkbUpclXJs4MyNhoHef0AamFuzKg8nueUvsGoOQ47zrIqz2GzLV4M9r2kxkaj2fj7QZElTt2KWn3zvlphTp/knbyW0qKtXmndaorGHcV22eOKhh3Ve7mrg9BUvEvMhX2HaV+BWVb7H9TSJWPb+2Jt05V3QC5sG5rA6aWD7VbUo6KNDvjXWzNqIA9cYdWYMp/K1lXvY/EsxSFXs5oChYqSoV188kaKA0KiRAlWydn2BnI5HsbM05OXQqyLXbL1FdViK5O+BdDS2RlcwgsAya/ySSGmmZM/9FJF3NMk6fu9iGaj7SUXBxsK46zVG0OWHf6ko/EbCRKq43knay0SJuOpIBGX3s3mHERj7yzn3ciIt8lNl9IDVxEhC5pFSW7LC50KheBlkcPHO/oR6SPB5p4USP
*/