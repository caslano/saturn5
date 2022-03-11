//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_LOGICAL_HPP
#define BOOST_COMPUTE_FUNCTIONAL_LOGICAL_HPP

namespace boost {
namespace compute {
namespace detail {

template<class Predicate, class Expr>
class invoked_unary_negate_function
{
public:
    typedef int result_type;

    invoked_unary_negate_function(const Predicate &pred,
                                  const Expr &expr)
        : m_pred(pred),
          m_expr(expr)
    {
    }

    Predicate pred() const
    {
        return m_pred;
    }

    Expr expr() const
    {
        return m_expr;
    }

private:
    Predicate m_pred;
    Expr m_expr;
};

template<class Predicate, class Expr1, class Expr2>
class invoked_binary_negate_function
{
public:
    typedef int result_type;

    invoked_binary_negate_function(const Predicate &pred,
                                   const Expr1 &expr1,
                                   const Expr2 &expr2)
        : m_pred(pred),
          m_expr1(expr1),
          m_expr2(expr2)
    {
    }

    Predicate pred() const
    {
        return m_pred;
    }

    Expr1 expr1() const
    {
        return m_expr1;
    }

    Expr2 expr2() const
    {
        return m_expr2;
    }

private:
    Predicate m_pred;
    Expr1 m_expr1;
    Expr2 m_expr2;
};

} // end detail namespace

/// \internal_
template<class Arg, class Result>
struct unary_function
{
    typedef Arg argument_type;
    typedef Result result_type;
};

/// \internal_
template<class Arg1, class Arg2, class Result>
struct binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

/// \internal_
template<class Arg1, class Arg2, class Arg3, class Result>
struct ternary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Arg3 third_argument_type;
    typedef Result result_type;
};

/// The unary_negate function adaptor negates a unary function.
///
/// \see not1()
template<class Predicate>
class unary_negate : public unary_function<void, int>
{
public:
    explicit unary_negate(Predicate pred)
        : m_pred(pred)
    {
    }

    /// \internal_
    template<class Arg>
    detail::invoked_unary_negate_function<Predicate, Arg>
    operator()(const Arg &arg) const
    {
        return detail::invoked_unary_negate_function<
                   Predicate,
                   Arg
                >(m_pred, arg);
    }

private:
    Predicate m_pred;
};

/// The binnary_negate function adaptor negates a binary function.
///
/// \see not2()
template<class Predicate>
class binary_negate : public binary_function<void, void, int>
{
public:
    explicit binary_negate(Predicate pred)
        : m_pred(pred)
    {
    }

    /// \internal_
    template<class Arg1, class Arg2>
    detail::invoked_binary_negate_function<Predicate, Arg1, Arg2>
    operator()(const Arg1 &arg1, const Arg2 &arg2) const
    {
        return detail::invoked_binary_negate_function<
                   Predicate,
                   Arg1,
                   Arg2
                >(m_pred, arg1, arg2);
    }

private:
    Predicate m_pred;
};

/// Returns a unary_negate adaptor around \p predicate.
///
/// \param predicate the unary function to wrap
///
/// \return a unary_negate wrapper around \p predicate
template<class Predicate>
inline unary_negate<Predicate> not1(const Predicate &predicate)
{
    return unary_negate<Predicate>(predicate);
}

/// Returns a binary_negate adaptor around \p predicate.
///
/// \param predicate the binary function to wrap
///
/// \return a binary_negate wrapper around \p predicate
template<class Predicate>
inline binary_negate<Predicate> not2(const Predicate &predicate)
{
    return binary_negate<Predicate>(predicate);
}

/// The logical_not function negates its argument and returns it.
///
/// \see not1(), not2()
template<class T>
struct logical_not : public unary_function<T, int>
{
    /// \internal_
    template<class Expr>
    detail::invoked_function<int, boost::tuple<Expr> >
    operator()(const Expr &expr) const
    {
        return detail::invoked_function<int, boost::tuple<Expr> >(
            "!", std::string(), boost::make_tuple(expr)
        );
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_LOGICAL_HPP

/* logical.hpp
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
*/