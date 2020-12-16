/*!
@file
Defines operators for Searchables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/at_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Derived>
    struct searchable_operators {
        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) & {
            return hana::at_key(static_cast<Derived&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) && {
            return hana::at_key(static_cast<Derived&&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) const& {
            return hana::at_key(static_cast<Derived const&>(*this),
                                static_cast<Key&&>(key));
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

/* searchable.hpp
v3GPc7AyVzv5vcexc8JxeOvovA2/0kZmgjayCL9SVqtr6RBl3Q1DWS5zLqT8w4aYc7MLmyvSQe26DlPqGuk38kC3ji49yp9Yl97d761Lj/Z765q9qbyqa+ZQu31Zu7mdtDs2QT3jErS7Q4Ly46ndwazdCdSuVz0TE9Qzierxs3r26aSeyQnqmaKsq3dInkI/Jd8bZ64lbCflLeECfM/PSop4LCKyyVI+5+fp7cxmOs3v5PF0L6WudCU9kNJ0rmOfo1i65ASlviLlnKUP0j/9oXMW8qmxz1jMx6uZL5jiS5LsW9vuc5g0xYesB8X/wPkqCppn+4nf2q6p2je/kHzBKI2Ns3W+uR2dxVT5kz2LSUt/e8DGMjI/3TueVQ3j0/iOzh7dZer8br/NTwZw/2LzO05zs1Gen7M2ww4z/A/59VGAD35eRjEsXHNpumXQPKqxNmgu5QtifC6lt0BxLZtLem+c0UQPO24EPzObpsxjXQ1FATJgvTzme1uPN9i3U+hJznk6zfmBSc65NX8fWO8EKnP8Fz/pslTG0mVblD1WAOVYXZ7vuwb9FF+QvqfYifibflS/dmC5we/2H9RwZqb6uFI9lObfp4omor+LVP9l6ud5ypl6mPWR6kO/6G/6Ufs4n9MsnTFP7/ZHaNaa003RLBa7nE/rnJdi0xTDLcyhWXpbwaHZsmnFNYqvG/l12fRaW8N8mmxfN/xXUUjroaftN8VpVqXXWsSZqJBQk14VftiblbF4bbrie9eH/L6qyEemrzNGuTgNWD+P9ZKh+H5t7+FT1t+JtWSUGeDB0wd6+PTu4OEfNohijpHPj1HfjuSjttWHbKsP2VYfss33IZNybTLJtWiScs2QGamkO1Is5PYBjr1tod+UBxdQDOe4v7Nz89qaAJ5UCOAeMK5g2G/Lq1Dsy+y9EOp37YXayV6wiNrJTdQODptb5JkotWCnUXfCvplRJwL8xogKRd8StCmf7zTexw+bkQRYGt+MTtzPhawtpNiZvN+JSb6U7WEOI7iFo8MJR4fSXBxBOFpG5eTfhw9w3jU4SrEdHO03f7j8PobqOJbVsUT57ji/YzPMp/igx9N3J1DZ8YnGvQjnWk0dbIYIQnNE47T7fJLS9sl+/Ch9PoXaPjUp2iCkU1J9c+BQhe7OoLrPpLonJaoboUsUAuIgfvZGepAT0zqT7nqc42f+e1TmCIr5z+2u5zEbw6wdzDIcHxf42dywOyKH8D2w0oYaz/hiv6n/XULjb6NvZd7UdKYLUlk1nq2E9VXsiJdTv1by8kifnO5OFyOt1ie/QTlXfVdbOjPl+z3iAV/r532S5ZT7wUr+S0obNyr5tyj3i29W8tX3HW71k32H8jlt3c7yVip5qwjvpxPeR6PcNsh5JkN5Y5vPoaLD34VvZS13sz7S967YvvdS21jX6jmBXX4F8pDvosP7LPwr/eL4f8CiaaWMWtdDfjpjY+W8y3YTjyDNeZFK/4+5+0V1KHeGlTo0G2d0x5PNzV3K3DzN8o5T8p6leTuR5o3vhfiPygNW+8290PP0vaQV9a2DF/203qiPLym0hzrMuij/FZYvYSptvqbkgw8xfoR7wdbY+rL1zsoDzvLxlomNF+QreFnD+qaubcAwPnec9LVsDpFPtjr3edz7nM9R/0bimx6Ebw/eRnAVFz3ER6iL4/pihU98Qum7SNbu1decp7OZnOxgPPJzKjckg75TeN4XHniQMHWO1rN+oQ6Uced/Y+GJ8tNQ3+eKjfk7e17UPLxFwvK+UPJ+RLoAeb27wHcItwni4/cWPxN93+VB37/63WvwN0pbuHxamaPPFVxome78u5R8X6Z1P0Cpj/qbr/D+1EzCrbk=
*/