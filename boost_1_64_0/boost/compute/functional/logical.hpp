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
6TdoGwMvGnO5m4rj1ayMhaTxpbmFfm+j4Df6c41TGTgu8TZj/NR/0NKiDPuSR1Xw8bD5PvyXGOffsw7b/7rHK6yS1UXC/F6ExPR+aeubEvMWcp777LkdZ2Oen2P5/nkecdrz1RVUqk8u0tqMebRN0C1WRFybrYjjBw1xoIMijo4BvMO4fQaf4+ZGHBQYnL2Yk5Nol7Mar6/THBpMzDlIcAbzVTLgZN9KcigZse6xHBMLpG5xjgXCtpniVJrsFL/LrbBi2JhoRLwj0ZjYN5xhY+LA8FJjIvuO5cRjohZxTFxog6fGRMNwUmOiaTipMdEynNSYmDWc1JjIDSc1JjYNx46JrQjnMQH9HHSMm9gK6H35nXXPEtr8+8DpYrMnEI4znh8EnJ5TraYc+ifM1TSry3Op2f/Dba8tLx2hJsH4utZFh/JppmY/0WsfyvPJ8pqree6hfLe9diQ7Erj18/wf7kh2BH4at05xyVo5NXIjgvmscDTBq2yB7Eb8Xn2qrdZ7NHnd6DrwfTccP3eL1j8C39v/y3XNhL4670WH8LmVZN9unv//8keIxmcet03yfWux32jzWJLnWisTvO8m6+daTKzJ8msiPdptFeuZa8nvpHxyjqnRgG2TO4Oa1zzcp5ZDImw5OXMqw5qTYc6W4XAybC+0vhI49CrGgFZ3Z5yhiDmYcWsXcRpfBSdp92RfY9zaPbuMpeyeM9hDYJ6ye2C7AGd1D5vo64xx2txOOx8R+CCHxStj4tdu6vvUqcs2YkyNyO/uSsTk8ZmxmTbtMNGeDlFGLoV9oxq49PTVKHQyyke7ATxXjWHdCZwKt9FZok8F1r838/mzmi4g0zfWWKJ0I+jn62suqzz2Y90xHKsWUabXnYd408dn2ifHtS8HYS+TmBccKmrAD9RvXfQ7koAM+0FvdLhP9hTm/Df57942P4tOHAq3Rod9XtOc1d5yFW9uHXO+xvmIkdLAnqTkVEnQBtPGmXDuwGefksdJtdelv6Tm9AYbCx1p628pnE6PaXTMreV8X1zioamozjbW2o7kId4C77HVdzxu9vfzR4nv7uiPIph1bnpjstsgF6/yHN+VmHOQZmH7Yw798WZwkv2xx7jtjzm081sE50g6n8ZbJSfOZ/ZtEtf5YP3zdnAO7fcd5g3t9+Y7wEn3O+Oq37GeYZz7U75n8U6Ps/j0sEf8WmB2vIR3j0aQz0MuWnLHxk7IjT1u+wPg/v1TUMRbFuOBgxmKY3g8FJjc3MuxJ3kfxu17fZv8296wvPP1wMGm3PrFQrnc78nDj3Xp1sPCN2zFQUY2N4HRNpyIR4/vcvuN65A9AngIcLGG890XeIzea1Vv+b+Qv/uSYC7dFJgrCWPZixgLuUHGA+bef13EWHkxfw+1Rvu/jDGfF49BgXHNud67Ardlab3bY/TerCzL9nv4uy3LrsBCWdAm72XM5rUdMPd+Le91vI+/27z2P8JYVO+PMpast8B9WXis0B1Kwu48TvFwyE9myYXLEjGPfgfc3bAu52uB1951bon7KB7i95eqSdxHpuCytf7M6fddjObjmIv+Csxv8peZc9qzlLfCXebA9ylvhfvMYRP/omqXKYppMre60B6lT3dCe2vsWIlBzn+lsIVV8g1yoiz2BH6jOOS7QTrRcyBTv1OcgdwT29TYWWwfE/aXgN3t2CjHP2f/578q3Mf5PNMeUCnk/bLZv0c80JCX4XTd0BugDv9WuPKfa/4BmLf1qr2ICXW/3HKOMQf2zR89J+zdrpfxC5cnnNUv6vMfz/MXNZxJ2C0rvYE199kulua0j03Itsn+5NOSe5+UJyETaJvz+LSqJqOHsRd1bKbany9Z4veYGMNbNks=
*/