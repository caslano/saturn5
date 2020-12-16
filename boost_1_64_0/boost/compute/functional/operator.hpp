//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_OPERATORS_HPP
#define BOOST_COMPUTE_FUNCTIONAL_OPERATORS_HPP

#include <string>

namespace boost {
namespace compute {
namespace detail {

template<class Expr1, class Expr2, class Result>
struct invoked_binary_operator
{
    typedef Result result_type;

    invoked_binary_operator(const std::string &op,
                            const Expr1 &arg1,
                            const Expr2 &arg2)
        : m_op(op),
          m_expr1(arg1),
          m_expr2(arg2)
    {
    }

    std::string op() const
    {
        return m_op;
    }

    Expr1 arg1() const
    {
        return m_expr1;
    }

    Expr2 arg2() const
    {
        return m_expr2;
    }

    std::string m_op;
    Expr1 m_expr1;
    Expr2 m_expr2;
};

} // end detail namespace

/// \internal_
#define BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(name, op, return_type, arg_type) \
    template<class arg_type> \
    class name : public function<return_type (arg_type, arg_type)> \
    { \
    public: \
        name() : function<return_type (arg_type, arg_type)>(BOOST_PP_STRINGIZE(name)) { } \
        \
        template<class Arg1, class Arg2> \
        detail::invoked_binary_operator<Arg1, Arg2, T> \
        operator()(const Arg1 &x, const Arg2 &y) const \
        { \
        return detail::invoked_binary_operator<Arg1, Arg2, T>(op, x, y); \
        } \
    };

// arithmetic operations
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(plus, "+", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(minus, "-", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(multiplies, "*", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(divides, "/", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(modulus, "%", T, T)

// comparisons
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(equal_to, "==", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(not_equal_to, "!=", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(greater, ">", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(less, "<", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(greater_equal, ">=", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(less_equal, "<=", T, T)

// logical operators
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(logical_and, "&&", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(logical_or, "||", T, T)

// bitwise operations
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(bit_and, "&", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(bit_or, "|", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(bit_xor, "^", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(shift_left, "<<", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(shift_right, ">>", T, T)

} // end compute namespace
} // end boost namespace
#endif // BOOST_COMPUTE_FUNCTIONAL_OPERATORS_HPP

/* operator.hpp
Vygt+o6LBHI+/bbH7jozftKdxuVin5h8PhO4P4FXewY7nkeD273zBdIy5O/NzKlMHVCYs/8WxckH1Kq9XikIzGm+1XI4L+zpvk1wBtTsbvSyD43AvdnnE+F8DgKHzH/CBgs0isi5JO+LfHbf4Tl+/HivrRx98k6H+wv1bT6n9N8XO5R070z4IdoK+CAf1p7N9zBnWHvuvpc5w9oz+4DlJPL6IHNse8FPYNdxvJxsoAz+u/fGr7bw/Y9ZtylOb9DnUvC5tOKQ0U9b1xnlw3dSYzzKR3HIj43ryvkoDg8ejAvGrSsg0mh8mDnsBsj7My2BuzaH2uR7X4Jjx0cusFBVeuywdNgDZyvFIR0kOTvMCS0R+Qrteo4vA1GrXQhqF+bsxRyq0KBQd/YTnB6pJKJgLX4QcYLQQQppNhBnsh+J+JWWojQXYBvEHKdSBaduOAXqyJym5STqOGs5iTpuRpzD67ht+Yk67kYcrmOQz33PCfek4Y/zUf7uf88+Wh/zGBVwgY53VHyLT3isGC4Hs+BoOcC+gsBt3lvAMH75XHfqkiVGcZUmJmfGj/tjXU43bxm8y79tmd/69ujjjPllZyvxmdtVV/oXML82XoXvJK/8ffaXZTnvfofxqZOtycmTbJP+Sn1vH+v28XgQ1qK/VZzg4tNHPQ8U7t18GG8Z3GfQx7rvppckvDSU7naj8tp0GaO4mvNopC1lzKvfbAhvvSQyr2V5tHecSq92NMXj9LDWeYbhEYc+L0KenhnjbfIInCuyHvScyYvLw5zNZyU4dIbdF5zazQ2Hy9uD7TmUQ1E+ZWyvZ2sejHneN6O43Jrjy5xDp6ZwFyCW995sPrRMV7Gcn2NwGtEljrZL4C4LygNnt4bTHVExapu30rhvM+7DW1scFUEe+ScMxy0N2Pf10xrnKwu8t7VvOeQ6Srz1jDhYT579Usxxr8WR5oVjAcvVczktF7ODKk3pYM/4eRqnuZOuq89tLCrXXu6H3XNcSvH9G38b0KXnSuGVrcZr6+GcNrV3gXGT5lF7sY/85rmTnEH5ZKjqe8Grxp9/Ew7pfJbbQVTddx+n05TtRWPMj9M25t/baBw9Is56tgzH2naN81xK49w+zDm/4XDbsP0nOC7mqdMU/BYrlyOUMyzEIf+a03dtt1ree+a5MeL0z6LPK6ivwb1crcB2E7hvi1AMtkO/eXbi8ELZ30fvoF8M7t+/B75jcLL/Fb5v8HAGznc7Ne5j2nAsZfN7Kh63j/mtjZO7ZfHCpc3vn8U4HTOyfXy1iwOfoXsmx+46M+a3Q9lmvdUlIo5f6/FZE6djOWGXtwjczasfyqVdXubuXONQbp/39Yl767icwZcBdUlwbAz47WvGeVZ95iy3Pva1rzWM15u/P4mE1LmtFJfjsff5fai4fCrWeQL3Y+IM9FEqL+r3I6b8resM43H5oTMeFPJ1IWhG74p9t3mM1Zij4rLmMa78FDf7jNO2I+QYclIoXL0TumN+S+myDXqCMbLoCJ6Myr5/m4ijyt6M01B55Bq/89jMHULEqHmMzxSnSoU5zTHFoVmpXMWfosM4ltnZExc3nOoyTTk7c1tGnJIi5OCIxL0DcTGgxdI8r3tGNIe04gO4LgrjgyrZX0/THHqpm8oX9IWoJwenPQt7f2MaJykukO7tJOYaGTaEwpyEkZ4ot6R5bzfJwYZ6H3J0wZjH0zvzthK81bmiH61DErx1StDydjTPXnDrw8aJeLTCuNvkncZOsM/OnuonHM7dCW2RxL3KlmuZsRQvqGvWKQ3Liw/kWCcmuWH24XV9nuaR9cRtsa/bgkNESl+fmMPdRPkFXuP2koedJ79uZ152oYjH3Uk8+KIYnr0=
*/