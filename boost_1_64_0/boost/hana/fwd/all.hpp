/*!
@file
Forward declares `boost::hana::all`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ALL_HPP
#define BOOST_HANA_FWD_ALL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all the keys of the structure are true-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a false-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/all.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto all = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct all_impl : all_impl<S, when<true>> { };

    struct all_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr all_t all{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ALL_HPP

/* all.hpp
cgfujDj26Q6jSu5qwB2MoHv0RdRRi53115Ojv4HZeg2s/53Mxg4tQKy6qntclsS4Tri37F69WfuOrXtHs6V2tH9XqlBWO2wVGjR6/qhnLOFhzdrQLG/eYzQYynEke1QcEva1/N3UoG10hQOW8Izt4SKLPLFWnA9cneECm1LaGV7XESpRgxFJKbUGD0oht0VxvRkqeVMptYVwvHKhtEMpzQy5bYrrvVDJeyF3Zv5fapofMwLIbNGHfMdyvIQDJsU9LLwOAmah0JW47rngizXKBSqrcTaiEsvXtKQcareUoG5TcqbQyalql3YlATT3C5AlUn8Q0/qHaEqCmD4gREt/EIf0DzEtCWLGgBCtfSH2AhcqHZKvU/b2H3VpWnWVs3lF5X94aZHfLA1vyfVtksEA0Wxr2CPX/w7P1J5sdRqZym+v05r5F+8GI/5aqpuAv1YZ0csD1rZbOawh+IlmOZtRm4O8uzksFVnxFEIpgFNU95FoQlRTsiaVlMeLKFopB93htVI/LanSF1mhwD1FI4Kut00SRXtDy63AjVg0vMu+I485Lh0Z34S4DcZl9CGUGpFJCWrQKCYLISbxGN+AEnPI3aCXbE1zDnG2hC60KRfi5BCan6lEQhdmIWd+tlKaxSXTEhPJMfWA5/a6VwmcmckieTfLuvvajb24R18wiXzgHB1sk7B20e2OUDHWuIROSzOVYgu6LM6q00owxEBD1YpqZ3NlRFnC/vojmk0pyhyAaJmcOhJNNv6riZYliEZSzbfy3R6a7wjPn6y41HBBltP1ulLyB+eTIZcKkQXBpTypqybKjDD74qut7m/skZm6fgJsSMpDLAQGyCQGh+RtT6ICMGAFonDIef1e50zS8voOpeQl5zOQfoprv/O5kKtTKXkdvZZ8UKcVYOhyw7Vg8wRBswYgaJZSlD0AQbO5YkjQVVgw/zqChtfmCRrGaOqI0XRyaH6uUvpBeJ1dsF5PTuRppq9+Qk7srS8Ibixtj+OAKsWPO93N4EL3/lDx60CheBe6K1VDxdhe3vyncv3uGNd3KMV/INu/p5TuJdt3KsUvke0xU3PETGV2z1SwXftPi9X/2RSE1DdC9bDGfwKD1Z+WCSUkop4be0g+jy/mefysdZp2n7RonM35OE4JJdAvl5VD1/dyd1mGHJperoKZzIrnTDcOG5d5Gt7yWxsO+y0NzX6pYV9gtPdBAPK+WT3S5rVfNtKmPnmR6Au70I1Bzegf16D5R3ubEnWWss4P9DpUnrfK/nHehxLF97L4NhRT1UUVgJAbfkp15hab8lSw0ybfuhuVsWqjUgiHkvA8Ob9jfXq4WM5v+fywcBHfZvDtibVTldacAzktD9PwQHussrdRmhJeZDx7nra5MEMLvmEMvI1hZvJsEx0m25YYZJtxlXywXR4+DATMdrvV1S5NCy+UgQfA2gm2be0Y5ZmcLgG0UZIBLm+eAPVOdKhsk2Vbmg4B8IoMyjPhGkdJ8AlbsNUWjBqFPXo4yEzE5YZ5YHz07ScVwuX28C15YngbTQYcCKQQDxa24o7g27bwfJnNZgCHKcRhx9rTgMPzv9NxGBLDIUocTlkVszdjLEDB1HM437r4o4cze+DhBFeDvTga2QZMlOeBEJ4blmtUhypX4Cha4tylTljPeV0cMYJbwrfYzR3ha/RB/YlzthKZpTLHRiOv7aKO4AFbeEWHbDPTWIC5Cy92zMB4nXvk4XhiF4789vWTwoWOBZjP8UpLjsoq5ifnYybzjMFjtrUHoyMx5EKDgfQGri2CUhwvWs1yu9T80qQxT5xd48j8qCGTaOndQ86KDzlmgXk7Nuy5SVMHxhRDbDV0z9vEAtIf3WIotjTi3GM=
*/